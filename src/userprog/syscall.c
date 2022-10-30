#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "threads/vaddr.h"
static void syscall_handler (struct intr_frame *);
void check_address(void * addr);
tid_t exec(const char* file);
void exit(int status);
int wait(tid_t pid);
int write(int fd, const void * buffer, unsigned size);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
  printf("systemcall number is : %d\n", *(uint32_t *)(f->esp));
  printf ("system call!\n");
  //printf("%s\n", thread_name()); //echo
  void *esp = f->esp;
  //check_address(f -> esp); //먼저 시스템콜 호출 전에 메모리 참조 확인
  switch(*(uint32_t *)(f ->esp)){
    case SYS_HALT:
      shutdown_power_off();
      break;
    case SYS_EXIT:
      check_address(esp+4);
      exit((int)*(uint32_t*)(esp+4));
      break;
    case SYS_EXEC:
      check_address(esp+4);
      f->eax=(uint32_t)exec((const char*)*(uint32_t *)(esp+4));
      break;
    case SYS_WAIT:
      check_address(esp+4);
      f->eax = (uint32_t)wait((tid_t)*(uint32_t *)(esp+4));
      break;
    case SYS_WRITE:
      //check_address(esp+4);
      f->eax = write((int)*(uint32_t *)(esp+4), (void *)*(uint32_t *)(esp+8), (unsigned)*(uint32_t *)(esp+12));
      break;
    case SYS_READ:
      break;
  }



  thread_exit ();
}
void check_address(void * addr){ //참조하는 메모리값이 user이면 true, kernel이면 exit

  if(!is_user_vaddr(addr))
    exit(-1);
}
void exit(int status){
  struct thread* a = thread_current();
  printf("%s : exit(%d)\n",thread_name(), status);
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
  printf("echo this?\n");
  if(fd==1){
    putbuf(buffer, size);
    return size;
  }
  return -1;
}