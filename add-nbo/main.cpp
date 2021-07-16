#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    // These variables will store numbers read from files.
    uint32_t num1 = 0;
    uint32_t num2 = 0;

    // If user inputs 1 file or more than 3 files,
    // let user know how to use this program.
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    // <file1> and <file2> open
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");

    // Active if files were opened normally.
    if (fp1 && fp2)
    {
        // Read file 1 and store to num1 in 1 count and uint32 size.
        fread(&num1, sizeof(uint32_t), 1, fp1);
        // ntohl function will change NBO to HBO in 4 bytes size.
        num1 = ntohl(num1);
        // Close file 1
        fclose(fp1);

        // Read file 2 and store to num2 in 1 count and uint32 size.
        fread(&num2, sizeof(uint32_t), 1, fp2);
        num2 = ntohl(num2);
        // Close file 2
        fclose(fp2);

        // Print values <file1>, <file2> and <file1> + <file2>.
        printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", num1, num1, num2, num2, num1+num2, num1+num2);
    }

    // If file 1 was opened normally, but file 2 was not opened.
    else if (fp1)
    {
        printf("The <file2> was not opened.\n");
        fclose(fp1);
    }

    // If file 2 was opened normally, but file 1 was not opened.
    else if (fp2)
    {
        printf("The <file1> was not opened.\n");
        fclose(fp2);
    }

    // If two files were not opened.
    else
    {
        printf("The files were not opened.\n");
    }

    return 0;
}
