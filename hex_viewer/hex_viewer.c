#include "hex_viewer.h"

#define row_length 16

int hex_viewer(char *str)
{
    FILE *fp = fopen(str, "r");
    if (!fp)
    {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    int c[row_length];
    int num = 0;
    while (!feof(fp))
    {
        memset(c, 0, row_length * sizeof(int));
        int row_length_actually = row_length;
        for (int i = 0; i < row_length_actually; i++)
        {
            if ((c[i] = fgetc(fp)) != EOF)
            {
                num++;
            }

            else
            {
                row_length_actually = i;
                break;
            }
        }
        printf("%.8x| ", num);
        for (int i = 0; i < row_length; i++)
        {
            if (0 == c[i] || -1 == c[i]) printf("   ");
            else printf("%.2x ", c[i]);
        }
        printf("| ");
        for (int i = 0; i < row_length_actually; i++)
        {
            printf("%c", (iscntrl(c[i])) ? '.' : c[i]);
        }
        printf("\n");
    }

    if (ferror(fp))
        puts("I/O error when reading");

    /*
    else if(feof(fp))
       puts("\nEND of file reached successfully");
    */

    fclose(fp);
    return 0;
}