#include <stdio.h> // for FILE, fopen, feof, printf, putchar...c
#include <stdlib.h> // for exit, EXIT_FAILURE
#include <ctype.h> // for isprint

#define ROW_BYTE 16
#define LINE_HEAD_SIZE_DEFAULT 8

const char CONTROL_CHAR_DISPLAY = '.';
int hex_viewer(char *file_adress) {
    // Open File 
    FILE *fp = fopen(file_adress, "rb");
    if (!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    // Storage 
    char c[ROW_BYTE] = {0};
    size_t read_number = 0;
    size_t ROW_BYTE_actually = ROW_BYTE; // read number in actually  

    // Read 
    for(read_number = 0; !feof(fp); read_number++) {
        c[read_number % ROW_BYTE] = fgetc(fp);
        if (feof(fp)) {
            if (0 == read_number % ROW_BYTE) break; // if first one is EOF, break
            ROW_BYTE_actually = read_number % ROW_BYTE; // read number in actually, not include EOF

            read_number+= ROW_BYTE - ROW_BYTE_actually -1; // for this row must have ROW_BYTE number char 
        }
        if (0 == read_number % 16) 
            printf("%08x  ", (unsigned int)read_number);
        if (15 == read_number % 16) { // prinf the date
            for (int n = 0; n < ROW_BYTE_actually; n++) {
                printf("%0*x ", 2, (unsigned char)c[n]); // unsigned char to avoid ffffxx
                if(7 == n % 8) putchar(' '); // style 
            }
            for (int n = ROW_BYTE_actually; n < ROW_BYTE;n++) {
                 printf("   ");
                 if(7 == n % 8) putchar(' ');// style 
            }
            printf("|");
            for (int i = 0; i < ROW_BYTE_actually; i++) {
                printf("%c", (isprint(c[i])? c[i]:CONTROL_CHAR_DISPLAY)); // only isprint(char) could show 
            }
            printf("|\n");
        }
    }

    printf("%08x\n", (unsigned int)(read_number- ROW_BYTE + ROW_BYTE_actually )); // finally line
    
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
