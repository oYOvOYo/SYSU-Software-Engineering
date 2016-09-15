#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_LENGTH 16
#define CTRL_CHAR '.'

int hex_viewer(char* str);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Usage: ./hex_viewer [file]\n");
        exit(1);
    }
    return hex_viewer(argv[1]);
}



int hex_viewer(char *str)
{
    // Open File 
    FILE *fp = fopen(str, "r");
    if (!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    // Storage 
    char c[ROW_LENGTH];
    size_t num = 0;

    // Read 
    while (!feof(fp)) {
        memset(c, 0, ROW_LENGTH * sizeof(char));
        printf("%08x  ", num);

        size_t row_length_actually = ROW_LENGTH;
        for (size_t i = 0; i < row_length_actually; i++)
        {
            if ((c[i] = fgetc(fp)) != EOF) {
                num++;
            } else {
                row_length_actually = i;
                break;
            }
        }
        for (int i = 0; i < ROW_LENGTH; i++)
        {
            if (0 == c[i] || -1 == c[i]) printf("   ");
            else printf("%02x ", c[i]);

            if(7 == i%8) putchar(' ');
        }
        printf("|");
        for (int i = 0; i < row_length_actually; i++)
        {
            printf("%c", (iscntrl(c[i])) ? CTRL_CHAR : c[i]);
        }
        printf("|\n");
    }
    printf("%08x\n", num-16);
    

    if (ferror(fp))
        puts("I/O error when reading");

    /*
    else if(feof(fp))
       puts("\nEND of file reached successfully");
    */

    // Close FIle
    fclose(fp);
    return 0;
}