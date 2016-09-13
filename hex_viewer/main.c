#include <stdio.h>
#include <stdlib.h>
#include "hex_viewer.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Usage: ./hex_viewer [file]\n");
        exit(1);
    }
    hex_viewer(argv[1]);
    return 0;
}