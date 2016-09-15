#include <stdio.h> // for puts, FILE, fopen, feof, printf, putchar...c
#include <stdlib.h> // for exit, EXIT_FAILURE
#include <string.h> // for memset
#include <ctype.h> // for iscntrl

#define ROW_BYTE 16
#define LINE_HEAD_SIZE_DEFAULT 8

const char CONTROL_CHAR_DISPLAY = '.';
int hex_viewer(char *file_adress)
{
    // Open File 
    FILE *fp = fopen(file_adress, "rb");
    if (!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    // Storage 
    char c[ROW_BYTE] = {0};
    size_t read_number = 0;
    size_t ROW_BYTE_actually = ROW_BYTE;

    // Read 
    for(read_number = 0; !feof(fp); read_number++) {
        c[read_number % ROW_BYTE] = fgetc(fp);
        if (feof(fp)) {
            if(0 == read_number % ROW_BYTE)break;
            ROW_BYTE_actually = read_number % ROW_BYTE;
            memset(c+ROW_BYTE_actually, EOF,ROW_BYTE - ROW_BYTE_actually);
            read_number+= ROW_BYTE - ROW_BYTE_actually -1;
        }
        if (0 == read_number % 16) 
            printf("%08x  ", (unsigned int)read_number);
        if(15 == read_number % 16) {
            for (int i = 0; i < ROW_BYTE; i++) {
            if (EOF == c[i]) {
                printf("   ");
            } else {
                printf("%0*x ", 2, (unsigned char)c[i]);
            } 
            
            if(7 == i%8) putchar(' ');
            }
            printf("|");
            for (int i = 0; i < ROW_BYTE_actually; i++) {
            printf("%c", (isprint(c[i])) ? CONTROL_CHAR_DISPLAY : c[i]);
            }
        printf("|\n");
        }
        
    }
    printf("%08x\n", (unsigned int)(read_number-ROW_BYTE + ROW_BYTE_actually));

    // Close FIle
    fclose(fp);
    return 0;
}


int main(int argc, char* argv[]) {
	
	if (argc < 2 || argc > 3) {
		printf("Usage: ./hex_viewer <file> [<num>]\n");
		return -1;
	}
	
	hex_viewer(argv[1]);

	return 0;
}
