#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "threads/vaddr.h"
#include <string.h>
static void syscall_handler (struct intr_frame *);
void check_address(void * addr);
tid_t exec(const char* file);
void exit(int status);
int wait(tid_t pid);
int write(int fd, const void * buffer, unsigned size);
int read(int fd, void * buffer, unsigned size);
int fibonacci(int n);
int max_of_four_int(int a, int b, int c, int d);
void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
  //printf("systemcall number is : %d\n", *(uint32_t *)(f->esp));
  //printf ("system call!\n");
  //printf("syscall : %d\n", *(uint32_t *)(f->esp));
  //hex_dump(f->esp, f->esp, 100, 1);
  check_address(f->esp); //먼저 시스템콜 호출 전에 메모리 참조 확인
  switch(*(uint32_t *)(f ->esp)){
    case SYS_HALT:
      shutdown_power_off();
      break;
    case SYS_EXIT:
      check_address(f->esp+4);
      exit((int)*(uint32_t*)(f->esp+4));
      break;
    case SYS_EXEC:
      check_address(f->esp+4);
      f->eax=(uint32_t)exec((const char*)*(uint32_t *)(f->esp+4));
      break;
    case SYS_WAIT:
      check_address(f->esp+4);
      f->eax = (uint32_t)wait((tid_t)*(uint32_t *)(f->esp+4));
      break;
    case SYS_WRITE:
      //check_address(esp+4);
      f->eax = write((int)*(uint32_t *)(f->esp+4), (void *)*(uint32_t *)(f->esp+8), (unsigned)*(uint32_t *)(f->esp+12));
      break;
    case SYS_READ:
      check_address(f->esp+4);
      f->eax = read((int)*(uint32_t *)(f->esp+4), (void *)*(uint32_t *)(f->esp+8), (unsigned)*(uint32_t *)(f->esp+12));
      break;
    case SYS_FIBONACCI:
      check_address(f->esp+4);
      f->eax = fibonacci(*(uint32_t *)(f->esp+4));
      break;
    case SYS_MAX_OF_FOUR_INT:
      check_address(f->esp +4);
      f->eax = max_of_four_int(*(uint32_t *)(f->esp+4), *(uint32_t *)(f->esp+8), *(uint32_t *)(f->esp+12), *(uint32_t *)(f->esp+16));
      break;
  }
  return;
  //thread_exit ();
}
void check_address(void * addr){ //참조하는 메모리값이 user이면 true, kernel이면 exit

  if(!is_user_vaddr(addr))
    exit(-1);
}
void exit(int status){
  struct thread* a = thread_current();
  printf("%s: exit(%d)\n",thread_name(), status);
  a->exit_status=status;
  thread_exit();
}
tid_t exec(const char* file){
  return process_execute(file);
}
int wait(tid_t pid){
  return process_wait((tid_t)pid);
}
int write(int fd, const void * buffer, unsigned size){
  //printf("system call = write\n");
  if(fd==1){
    //printf("buffer = %s, buffer size = %d\n", buffer, strlen(buffer));
    putbuf((char *)buffer, size);
    //printf("echo complete\n");
    //printf("size = %d\n", size);
    return size;
  }
  return -1;
}
int read(int fd, void * buffer, unsigned size){
  if(fd==0){
    int i;
    for(i=0;i<size;i++){
      if(input_getc()=='\0')
        break;
    }
    return i;
  }
  else return -1;
}
int fibonacci(int n){
  if(n==1)return 1;
  if(n==2)return 1;
  
  int sum=0;
  int a=1, b=1;
  for(int i=3;i<=n;i++){
    sum=a+b;
    a=b;
    b=sum;
  }
  return sum;

}
int max_of_four_int(int a, int b, int c, int d){
  int arr[4];
  arr[0]=a;
  arr[1]=b;
  arr[2]=c;
  arr[3]=d;
  if(arr[0]>arr[1])
    arr[1]=arr[0];
  if(arr[1]>arr[2])
    arr[2]=arr[1];
  if(arr[2]>arr[3])
    arr[3]=arr[2];
  return arr[3];
}