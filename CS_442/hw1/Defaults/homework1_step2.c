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
    // can only modify this section BEGIN
    // cant call secret(), maybe use secret (pointer to function)
	
	// can only modify this section END
    printf("now inside entrance()!\n");
}

int main (int argc, char *argv[])
{
    entrance();
    return 0;
}

