#include <stdio.h>

void secret()
{
    printf("now inside secret()!\n");
}

void entrance()
{
	int doNotTouch[4];
	
    doNotTouch[12] = doNotTouch[10];
    doNotTouch[13] = doNotTouch[11];
    doNotTouch[10] = &secret;
    
    printf("now inside entrance()!\n");
}

int main (int argc, char *argv[])
{
    entrance();
    return 0;
}
