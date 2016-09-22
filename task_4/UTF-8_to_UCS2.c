#include <stdio.h> // for FILE fopen feof fclose 

#define UCS_SIZE 2
#define UTF_SIZE 3

void UTF_8_to_UCS2(char * file_adress) {
    FILE * fp = fopen(file_adress, "r"); // read from file 
    FILE * out = fopen("UCS-2", "w"); // write to target

    if(!fp) { // check whether the file can be open 
        printf("File opening failed\n"); 
        return;
    }

    char UCS[UCS_SIZE] = { 0xFE, 0xFF }; // store UCS-2
    char UTF[UTF_SIZE]; // store UTF-8
    size_t UTF_length; // store UTF-8 length
    unsigned long Unicode; // store Unicde
    int break_flag = 0; 

    // out the file  Bid Endian or Little Endian
    // Bid Endian : FE FF Little Endian FF FE,  this is  Bid Endian
    fputc((unsigned char)UCS[0], out);
    fputc((unsigned char)UCS[1], out);

   
    while (!feof(fp)) {
    Unicode = 0;
    // for every word, read from file and change to Unicode
    UTF[0] = fgetc(fp);
    if  (0 == ((unsigned char)UTF[0] >> 7)) {
        // 0zzzzzzz（00-7F）
        UTF_length = 1;
        Unicode = (unsigned char)UTF[0];
    } else if (6 == ((unsigned char)UTF[0] >> 5)) {
        // 	110yyyyy（C0-DF) 10zzzzzz(80-BF）
        UTF_length = 2;
        UTF[1] = fgetc(fp);
        Unicode = (((unsigned char)UTF[0] & 0x1f) << 6) 
                + ((unsigned char)UTF[1] & 0x3f);
    } else if(14 == ((unsigned char)UTF[0] >> 4)) {
        // 	1110xxxx(E0-EF) 10yyyyyy 10zzzzzz
        UTF_length = 3;
        UTF[1] = fgetc(fp);
        UTF[2] = fgetc(fp);
        Unicode = (((unsigned char)UTF[0] & 0xf) << 12) 
                + (((unsigned char)UTF[1] & 0x3f) << 6)
                + ((unsigned char)UTF[2] & 0x3f);
    } else break;
    
    UCS[0] = (Unicode & 0xff00) >> 8;
    UCS[1] = (Unicode & 0xff);
    fputc((unsigned char)UCS[0], out);
    fputc((unsigned char)UCS[1], out);
    }

    fclose(fp);
    fclose(out);
    return;
}

int main(int argc, char * argv[]) {
    if(argc != 2) {
        printf("Usage: ./UTF-8_to_UCS2 <file> \n");
        return -1;
    }
    UTF_8_to_UCS2(argv[1]);
    return 0;
}