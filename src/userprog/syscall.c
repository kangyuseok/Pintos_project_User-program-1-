#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  printf("systemcall number is : %d\n", *(uint32_t *)(f->esp));
  printf ("system call!\n");
  check_address(f -> esp); //먼저 시스템콜 호출 전에 메모리 참조 확인

  thread_exit ();
}
void check_address(void * addr){ //참조하는 메모리값이 user이면 true, kernel이면 exit

  if(!is_user_vaddr(addr))
    exit(-1);
}