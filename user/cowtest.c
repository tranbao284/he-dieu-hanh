#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void simpletest() {
  printf("simple: ");

  int *p = (int *) sbrk(4096);
  if(p == (void*)-1){
    printf("sbrk failed\n");
    exit(1);
  }

  *p = 1;

  int pid = fork();
  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // child
    *p = 2;
    exit(0);
  } else {
    wait(0);
    if(*p != 1){
      printf("FAIL\n");
      exit(1);
    }
  }

  printf("ok\n");
}

void threetest() {
  printf("three: ");

  int *p = (int *) sbrk(4096);
  if(p == (void*)-1){
    printf("sbrk failed\n");
    exit(1);
  }

  *p = 1;

  int pid1 = fork();
  if(pid1 < 0){
    printf("fork failed\n");
    exit(1);
  }

  if(pid1 == 0){
    int pid2 = fork();
    if(pid2 < 0){
      printf("fork failed\n");
      exit(1);
    }

    if(pid2 == 0){
      *p = 3;
      exit(0);
    }
    wait(0);
    exit(0);
  }

  wait(0);

  if(*p != 1){
    printf("FAIL\n");
    exit(1);
  }

  printf("ok\n");
}

int main(int argc, char *argv[]) {
  simpletest();
  threetest();

  printf("ALL COW TESTS PASSED\n");
  exit(0);
}
