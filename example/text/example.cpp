#include "resource.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
    const char fname[] = "restored.txt";
    int res = rc_restore(fname, text_txt, text_txt_len);
    
    if(res) {
        std::cout << "Resource was successfully written to " << fname << "!\n";
        return 0;
    } else {
        std::cout << "Failed to write resource to " << fname << "!\n";
        return 1;
    }
}