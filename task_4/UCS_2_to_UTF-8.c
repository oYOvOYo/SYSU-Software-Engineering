#include <stdio.h>
#include <locale.h>

void UTF_8_to_USC2(char * file_adress) {
    FILE * fp = fopen(file_adress,"r");
    if(!fp) {
        printf("File opening failed\n");
        return;
    }

    char ch[2]; // store UCS_2
    int endian = ((unsigned char)fgetc(fp) < (unsigned char)fgetc(fp));

    while (!feof(fp)) {
        printf("%lc", ((unsigned char)fgetc(fp)<<8)+(unsigned char)fgetc(fp));
        if(feof(fp)) break;
    }
    printf("\n");
    fclose(fp);
    return;
}

int main(int argc, char * argv[]) {
    setlocale(LC_ALL, "");

    if(argc != 2) {
        printf("Usage: ./UTF-8_to_USC2 <file> \n");
        return -1;
    }
    UTF_8_to_USC2(argv[1]);
    
    printf("%lc",0x24B62);
    return 0;
}