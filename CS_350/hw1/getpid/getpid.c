#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

int main(){

int sysPID = syscall(SYS_getpid);
int getPID = getpid();

printf("SYS_getpid = %d\n", sysPID);
printf("getPID = %d\n", getPID);

assert(sysPID == (int)getPID);

return 0;

}