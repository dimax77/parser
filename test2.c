#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

int main(){
    char * string = "\n";
    char * res = strtok_r(string, "/", &string);
    int new = atoi(res);
    printf ("Res: %d\n", new);
    return 0;
}