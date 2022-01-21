// Submitted By CSB19047

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>
#define MAX_RETRIES 10
union semun
{
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int initsem(key_t key, int nsems) 
{
    int i;
    union semun arg;
    struct semid_ds buf;
    struct sembuf sb;
    int semid;
    semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);
    if (semid >= 0)
    {
        sb.sem_op = 1;
        sb.sem_flg = 0;
        arg.val = 1;
        printf("press return\n");
        getchar();
        for (sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++)
        {
            if (semop(semid, &sb, 1) == -1)
            {
                int e = errno;
                semctl(semid, 0, IPC_RMID);
                errno = e;
                return -1; 
            }
        }
    }
    else if (errno == EEXIST)
    { 
        int ready = 0;
        semid = semget(key, nsems, 0); 
        if (semid < 0)
            return semid; 
        
        arg.buf = &buf;
        for (i = 0; i < MAX_RETRIES && !ready; i++)
        {
            semctl(semid, nsems - 1, IPC_STAT, arg);
            if (arg.buf->sem_otime != 0)
            {
                ready = 1;
            }
            else
            {
                sleep(1);
            }
        }
        if (!ready)
        {
            errno = ETIME;
            return -1;
        }
    }
    else
    {
        return semid; 
    }
    return semid;
}

int main(void)
{
    key_t key,message;
    int semid;
    struct sembuf sb;
    
    key = ftok("program1.c", 'J');
    semid = initsem(key, 2);
    message = ftok("program1.c", 'S');
    int smid = shmget(message,1024,0644|IPC_CREAT);
    sb.sem_flg = SEM_UNDO;

    printf("Program 1 is trying to write... \n");
    sb.sem_num = 0;
    sb.sem_op = -1; 
    semop(semid, &sb, 1);

    printf("Got inside critical section \n");
    char *buf = shmat(smid,(void*)0,0);
    snprintf(buf,6,"%s","Hello");
    shmdt(buf);

    printf("Program1 writing is completed\n");
    printf("Press Enter to exit critical section: \n");
    getchar();

    sb.sem_op = 1;
    semop(semid, &sb, 1);

    printf("Waiting for program 2...\n");
    sleep(1);
    sb.sem_num=1;
    sb.sem_op=-1;
    semop(semid, &sb, 1);
    sb.sem_op=1;
    semop(semid, &sb, 1);
    printf("Program 2 done ..\n");


    printf("Press Enter to delete semaphore: ");
    getchar();
    semctl(semid, 0, IPC_RMID);
    return 0;
}