#include "resources.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    const char fname[] = "data/restored.jpg";
    int res = rc_restore(fname, data_lena_jpg, data_lena_jpg_len);
    
    if(res) {
        std::cout << "Resource was successfully written to " << fname << "!\n";
        return 0;
    } else {
        std::cout << "Failed to write resource to " << fname << "!\n";
        return 1;
    }
}