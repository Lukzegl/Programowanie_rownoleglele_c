#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
pid_t pid1 = getpid();

printf("Lukasz_Zeglinski_arg = %s ___ %d\n",argv[0], pid1);
return 0;
}