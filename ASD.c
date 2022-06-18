#include <stdio.h>

int toBcd(int value);

int main()
{
    int x = 0;
    char    c = toBCD(x);
    printf("%c, c")
}


int toBcd(int value)
{
    return ((value/10) << 4) + (value % 10);
}
main.c:16:17: warning: implicit declaration of function ‘toBCD’ [-Wimplicit-function-declaration]