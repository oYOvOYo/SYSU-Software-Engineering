#include <stdio.h>

#define UCS_SIZE 2
#define UTF_SIZE 3

void UCS_2_to_UTF_8(char * file_adress) {
    FILE * fp = fopen(file_adress, "r"); // read from file 
    FILE * out = fopen("UTF-8", "w"); // write to target

    if(!fp) { // check whether the file can be open 
        printf("File opening failed\n"); 
        return;
    }

    char UCS[UCS_SIZE]; // store UCS-2
    char UTF[UTF_SIZE]; // store UTF-8
    size_t UTF_length; // store UTF-8 length
    unsigned long Unicode; // store Unicde
    int break_flag = 0; 

    // check the file is Bid Endian or Little Endian
    // Bid Endian : FE FF Little Endian FF FE,  true means Bid Endian 
    int endian = ((unsigned char)fgetc(fp) < (unsigned char)fgetc(fp)); 

    while (!feof(fp)) {
    // for every word, read and write to file     
    for (size_t i = 0; i < UCS_SIZE; i++) {
        UCS[i] = fgetc(fp); // store every two byte in a char type
        if(feof(fp)) {
            break_flag = 1;
            break;
        } 
    }
    if(break_flag) break;

    // change UCS-2 to Unicode
    Unicode = 0;
    if(endian) {
        for (size_t i = 0; i < UCS_SIZE; i++) {
            Unicode = (Unicode << 8); // 8 bit  
            Unicode += (unsigned char)UCS[i]; 
        }
    } else {
        for (size_t i = UCS_SIZE-1; i >= 0; i--) {
            Unicode = (Unicode << 8); // 8 bit
            Unicode += (unsigned char)UCS[i]; 
        }
    }
    
    

    //change Unicode to UTF-8 
    if ( Unicode <= 0x0000007F ) {  
        // * U-00000000 - U-0000007F:  0xxxxxxx  
        *UTF = (Unicode & 0x7F);
        UTF_length = 1;   
    } else if ( Unicode >= 0x00000080 && Unicode <= 0x000007FF ) {  
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx  
        *(UTF+1) = (Unicode & 0x3F) | 0x80;  
        *UTF = ((Unicode >> 6) & 0x1F) | 0xC0;
        UTF_length = 2;  
    } else if ( Unicode >= 0x00000800 && Unicode <= 0x0000FFFF ) {  
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx  
        *(UTF+2) = (Unicode & 0x3F) | 0x80;  
        *(UTF+1) = ((Unicode >>  6) & 0x3F) | 0x80;  
        *UTF = ((Unicode >> 12) & 0x0F) | 0xE0; 
        UTF_length = 3; 
    }
    
    // write UTF-8 to file
    if(endian) {
        for (size_t i = 0; i < UTF_length; i++) {
            fputc((unsigned char)UTF[i], out);
        }
    } else {
        for (size_t i = UTF_length-1; i >= 0; i--) {
            fputc(UTF[i], out);
        }
    }

    }
    fclose(fp);
    fclose(out);
    return;
}

int main(int argc, char * argv[]) {
    if(argc != 2) {
        printf("Usage: ./UCS_2_to_UTF_8 <file> \n");
        return -1;
    }
    
    UCS_2_to_UTF_8(argv[1]);
    return 0;
}