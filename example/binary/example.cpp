#include "resource.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    const char fname[] = "restored.jpg";
    int res = rc_restore(fname, lena_jpg, lena_jpg_len);
    
    if(res) {
        std::cout << "Resource was successfully written to " << fname << "!\n";
        return 0;
    } else {
        std::cout << "Failed to write resource to " << fname << "!\n";
        return 1;
    }
}