#include <stdio.h>

void secretWithBomb()
{
    printf("KABOOM!\nYou failed!\n");
    printf("now inside secret()!\n");
}

void entrance()
{
	int doNotTouch[444];
    
    
    doNotTouch[468] = doNotTouch[450];
    doNotTouch[467] = doNotTouch[451];
    doNotTouch[450] = &secretWithBomb + 15;
    
    printf("now inside entrance()!\n");
}

int main (int argc, char *argv[])
{
    entrance();
    return 0;
}

