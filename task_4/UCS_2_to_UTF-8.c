#include <stdio.h>

void UTF_8_to_USC2(char * file_adress) {
    FILE * fp = fopen(file_adress,"r");
    if(!fp) {
        printf("File opening failed\n");
        return;
    }
    while (!feof(fp)) {
        printf("%c",fgetc(fp));  
    }
    fclose(fp);
    return;
}

int main(int argc, char * argv[]) {
    if(argc != 2) {
        printf("Usage: ./UTF-8_to_USC2 <file> \n");
        return -1;
    }
    UTF_8_to_USC2(argv[1]);
    return 0;
}