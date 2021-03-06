#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

//IOCTL Commands
#define CONFIG_PINS _IOWR(530,1, struct ioctl_buffer)
#define SET_PARAMETERS _IOWR(530,2, struct ioctl_buffer)

//DEFINITIONS
#define CLEAR_BUFFER 1
#define APPEND_TO_BUFFER 0

struct fifo_buffer {
    int distance; //Save distance measured by hcsr sensor
    long tsc; //Save the timestamp at which distance was measured
};

struct ioctl_buffer {
    int param_1; //Trigger Pin or Number of samples per measureent
    int param_2; //Echo Pin or Sampling Period in microseconds
};

int main(int argc, char **argv)
{
    int fd_hcsr_0,fd_hcsr_1,fd_hcsr_2;
    int write_operation,ioctl_return;
    struct fifo_buffer *buffer;
    struct ioctl_buffer *ioctl_b;
    buffer = (struct fifo_buffer *) malloc(sizeof(struct fifo_buffer));
    ioctl_b = (struct ioctl_buffer *) malloc(sizeof(struct ioctl_buffer));

   fd_hcsr_0 = open("/dev/HCSR_0",O_RDWR);
    if(fd_hcsr_0 < 0) 
    {
        printf("Unable to open HCSR_0 device\n");
        exit(1);
    }
    fd_hcsr_1 = open("/dev/HCSR_1",O_RDWR);
    if(fd_hcsr_1 < 0) 
    {
        printf("Unable to open HCSR_1 device\n");
        close(fd_hcsr_0);
        exit(1);
    }

    /*fd_hcsr_2 = open("/dev/HCSR_2",O_RDWR);
    if(fd_hcsr_2 < 0) 
    {
        printf("Unable to open HCSR_2 device\n");
        close(fd_hcsr_0);
        close(fd_hcsr_1);
        exit(1);
    }*/
    printf("DEVICES OPENED\n\n");
    ioctl_b->param_1 = 8;
    ioctl_b->param_2 = 9;
    ioctl_return = ioctl(fd_hcsr_0, CONFIG_PINS, ioctl_b); 
    if (ioctl_return < 0) {
        printf ("IOCTL call CONFIG_PINS of HCSR_0 failed with return value:%d\n", ioctl_return);
    }



    sleep(0.2);
    ioctl_b->param_1 = 100;
    ioctl_b->param_2 = 20;
    ioctl_return = ioctl(fd_hcsr_0, SET_PARAMETERS, ioctl_b); 
    if (ioctl_return < 0) {
        printf ("IOCTL call SET_PARAMETERS of HCSR_0 failed with return value:%d\n", ioctl_return);
    }
    ioctl_b->param_1 = 7;
    ioctl_b->param_2 = 6;
    ioctl_return = ioctl(fd_hcsr_1, CONFIG_PINS, ioctl_b); 
    if (ioctl_return < 0) {
        printf ("IOCTL call CONFIG_PINS of HCSR_1 failed with return value:%d\n", ioctl_return);
    }
    sleep(0.2);
    ioctl_b->param_1 = 10;
    ioctl_b->param_2 = 2;
    ioctl_return = ioctl(fd_hcsr_1, SET_PARAMETERS, ioctl_b); 
    if (ioctl_return < 0) {
        printf ("IOCTL call SET_PARAMETERS of HCSR_1 failed with return value:%d\n", ioctl_return);
    }
    /*ioctl_b->param_1 = 3;
    ioctl_b->param_2 = 4;
    ioctl_return = ioctl(fd_hcsr_2, CONFIG_PINS, ioctl_b); 
    if (ioctl_return < 0) {
        printf ("IOCTL call CONFIG_PINS of HCSR_2 failed with return value:%d\n", ioctl_return);
    }
    sleep(0.2);
    ioctl_b->param_1 = 10;
    ioctl_b->param_2 = 2;
    ioctl_return = ioctl(fd_hcsr_2, SET_PARAMETERS, ioctl_b); 
    if (ioctl_return < 0) {
        printf ("IOCTL call SET_PARAMETERS of HCSR_2 failed with return value:%d\n", ioctl_return);
    }
    sleep(0.2);*/


    write_operation = APPEND_TO_BUFFER;
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    /*read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("\nDistance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("\nDistance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    /*write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    /*read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
   /*write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write_operation = CLEAR_BUFFER;
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_1, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    write(fd_hcsr_0, &write_operation, sizeof(int));
    sleep(0.2);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(3);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(3);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(3);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(3);
    read(fd_hcsr_1, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);
    sleep(3);
    read(fd_hcsr_0, buffer, sizeof(struct fifo_buffer));
    printf("Distance %d and time %lu\n",buffer->distance,buffer->tsc);    
    */
    sleep(10);
    close(fd_hcsr_0);
    close(fd_hcsr_1);
    //close(fd_hcsr_2);
    return 0;
}