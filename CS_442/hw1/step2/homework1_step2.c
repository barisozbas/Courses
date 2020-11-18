#include <stdio.h>

void secret1()
{
    printf("now inside first secret()!\n");
}

void secret2()
{
    printf("now inside second secret()!\n");
}

void entrance()
{
	int doNotTouch[44];
    
    doNotTouch[53] = doNotTouch[51];
    doNotTouch[54] = doNotTouch[50];
    doNotTouch[55] = doNotTouch[51];
    doNotTouch[50] = &secret1;
    doNotTouch[52] = &secret2;
	
    printf("now inside entrance()!\n");
}

int main (int argc, char *argv[])
{
    entrance();
    return 0;
}

