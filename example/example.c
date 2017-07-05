#include "resources.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    const char fname[] = "data/restored.jpg";
    int res = rc_restore(fname, data_lena_jpg, data_lena_jpg_len);
    
    if(res) {
        printf("Resource was successfully written to %s!\n", fname);
        return 0;
    } else {
        printf("Failed to write resource to %s!\n", fname);
        return 1;
    }
}