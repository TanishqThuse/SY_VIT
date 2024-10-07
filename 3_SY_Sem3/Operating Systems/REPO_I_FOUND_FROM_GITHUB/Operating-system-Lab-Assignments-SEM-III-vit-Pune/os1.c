#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MEM_SIZE 100
#define BUFFER_SIZE 40

// Data structure representing the operating system
struct OS
{
    char M[MEM_SIZE][4]; 
    char IR[4];          
    char R[4];           
    int IC;              
    int SI;              
    bool C;              
    char buffer[BUFFER_SIZE];

    FILE *infile;
    FILE *outfile;
};

// Initialize the OS
void init(struct OS *os)
{
    for (int i = 0; i < MEM_SIZE; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            os->M[i][j] = ' ';
        }
    }
    os->IR[0] = ' ';
    os->R[0] = ' ';
    os->C = false;
}

// Machine Operating System
void MOS(struct OS *os)
{
    if (os->SI == 1)
    { // Read Mode
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            os->buffer[i] = '\0';
        }
        fgets(os->buffer, BUFFER_SIZE, os->infile); // reads data from input.txt and store it in buffer

        int k = 0;
        int i = os->IR[2] - '0'; // determinig starting position in physical memory
        i = i * 10;

        for (int l = 0; l < 10; ++l)
        {
            for (int j = 0; j < 4; ++j)
            {
                os->M[i][j] = os->buffer[k];
                k++;
            }
            if (k == BUFFER_SIZE)
            {
                break;
            }
            i++;
        }

        for (int i = 0; i < MEM_SIZE; i++)
        {
            printf("M[%d]\t", i);
            for (int j = 0; j < 4; j++)
            {
                printf("%c", os->M[i][j]);
            }
            printf("\n");
        }
    }
    else if (os->SI == 2)
    { // Write Mode
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            os->buffer[i] = '\0';
        }
        int k = 0;
        int i = os->IR[2] - '0';
        i = i * 10;

        for (int l = 0; l < 10; ++l)
        {
            for (int j = 0; j < 4; ++j)
            {
                os->buffer[k] = os->M[i][j];
                fputc(os->buffer[k], os->outfile);
                k++;
            }
            if (k == BUFFER_SIZE)
            {
                break;
            }
            i++;
        }

        fputc('\n', os->outfile);
    }
    else if (os->SI == 3)
    { // Terminate
        fputc('\n', os->outfile);
    }
}

// Execution
void Execute(struct OS *os)
{
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            os->IR[i] = os->M[os->IC][i];
        }
        os->IC++;

        if (os->IR[0] == 'G' && os->IR[1] == 'D')
        { // GD
            os->SI = 1;
            MOS(os);
        }
        else if (os->IR[0] == 'P' && os->IR[1] == 'D')
        { // PD
            os->SI = 2;
            MOS(os);
        }
        else if (os->IR[0] == 'H')
        { // H
            os->SI = 3;
            MOS(os);
            break;
        }
        else if (os->IR[0] == 'L' && os->IR[1] == 'R')
        { // LR
            int i = (os->IR[2] - '0') * 10 + (os->IR[3] - '0');
            for (int j = 0; j <= 3; j++)
            {
                os->R[j] = os->M[i][j];
            }
        }
        else if (os->IR[0] == 'S' && os->IR[1] == 'R')
        { // SR
            int i = (os->IR[2] - '0') * 10 + (os->IR[3] - '0');
            for (int j = 0; j <= 3; j++)
            {
                os->M[i][j] = os->R[j];
            }
        }
        else if (os->IR[0] == 'C' && os->IR[1] == 'R')
        { // CR
            int i = (os->IR[2] - '0') * 10 + (os->IR[3] - '0');
            int count = 0;

            for (int j = 0; j <= 3; j++)
            {
                if (os->M[i][j] == os->R[j])
                {
                    count++;
                }
            }

            if (count == 4)
            {
                os->C = true;
            }
        }
        else if (os->IR[0] == 'B' && os->IR[1] == 'T')
        { // BT
            if (os->C == true)
            {
                int i = (os->IR[2] - '0') * 10 + (os->IR[3] - '0');
                os->IC = i;
            }
        }
    }
}

// Load function
void LOAD(struct OS *os)
{
    printf("Reading Data...\n");
    int x = 0;
    do
    {
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            os->buffer[i] = '\0';
        }
        fgets(os->buffer, BUFFER_SIZE, os->infile);

        // Remove trailing newline character
        os->buffer[strcspn(os->buffer, "\n")] = '\0';

        if (os->buffer[0] == '$' && os->buffer[1] == 'A' && os->buffer[2] == 'M' && os->buffer[3] == 'J')
        {
            init(os);
        }
        else if (os->buffer[0] == '$' && os->buffer[1] == 'D' && os->buffer[2] == 'T' && os->buffer[3] == 'A')
        {
            os->IC = 0;
            Execute(os);
        }
        else if (os->buffer[0] == '$' && os->buffer[1] == 'E' && os->buffer[2] == 'N' && os->buffer[3] == 'D')
        {
            x = 0;
            continue;
        }
        else
        {
            int k = 0;
            for (; x < MEM_SIZE; ++x)
            {
                for (int j = 0; j < 4; ++j)
                {
                    os->M[x][j] = os->buffer[k];
                    k++;
                }
                if (k == BUFFER_SIZE || os->buffer[k] == ' ' || os->buffer[k] == '\n')
                {
                    break;
                }
            }
        }
        fputs(os->buffer, os->outfile);
    } while (!feof(os->infile));
}

int main()
{
    struct OS os;

    os.infile = fopen("input.txt", "r");
    os.outfile = fopen("output.txt", "w");

    if (os.infile == NULL)
    {
        printf("Failure\n");
        return 1;
    }
    else
    {
        printf("File Exists\n");
    }

    LOAD(&os);
    fclose(os.outfile);

    return 0;
}
