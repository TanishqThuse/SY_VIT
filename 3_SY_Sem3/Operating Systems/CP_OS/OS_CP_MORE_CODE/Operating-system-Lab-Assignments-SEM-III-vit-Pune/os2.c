#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *fin;
FILE *fout;
int IC, PTR, VA, RA, kio = -1, flag[30], PI, TI, SI, TTC = 0, LLC = 0, ttl, tll;
char M[300][4], IR[4], R[4], C;
char page[10][4];
FILE *fin, *fout;
char temp[100];
char line[100];

void MOS();

struct PCB
{
    char job[4];
    char TTL[4];
    char TLL[4];
} pcb;



void endprogram()
{
    fprintf(fout, "\nSI = %d  TI = %d  PI = %d\n", SI, TI, PI); //for output.txt
    fprintf(fout, "TTC = %d  LLC = %d\n", TTC, LLC);
    printf("\nSI = %d  TI = %d  PI = %d\n", SI, TI, PI); // for console
    printf("TTC = %d  LLC = %d\n", TTC, LLC);
    exit(1);
}

void allocate()
{
    int pos, i, j, k = 0, check = 0, len;
    char str[2];
    int level = 0;

    while (check != 1)
    {
        printf("TEMP  %d\n", kio);
        kio++;

        printf("Cnt1  %d\n", level);
        pos = (rand() % 29) * 10;
        printf("Pos1   %d\n", pos);

        while (flag[pos / 10] != 0)
        {
            printf("In while pos\n");
            pos = (rand() % 29) * 10;
            printf("Pos2  %d\n", pos);
            printf("cnt2  %d\n", level);
        }

        flag[pos / 10] = 1;
        sprintf(str, "%d", pos);

        if (pos / 100 == 0)
        {
            M[PTR + kio][2] = '0';
            M[PTR + kio][3] = str[0];
        }
        else
        {
            M[PTR + kio][2] = str[0];
            M[PTR + kio][3] = str[1];
            printf("Cnt3  %d\n", level);
        }

        fgets(line, sizeof(line), fin);
        printf("%sLine2\n", line);
        level++;
        k = 0;

        for (i = 0; i < strlen(line) / 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                M[pos + i][j] = line[k];
                k++;

                if (line[k] == 'H')
                {
                    check = 1;
                    M[pos + (i + 1)][0] = 'H';
                    M[pos + (i + 1)][1] = '0';
                    M[pos + (i + 1)][2] = '0';
                    M[pos + (i + 1)][3] = '0';
                }
            }
        }
    }

    printf("\nMEMORY\n");
    for (i = 0; i < 300; i++)
    {
        printf("[%d] = ", i);
        for (j = 0; j < 4; j++)
        {
            printf("%c", M[i][j]);
        }
        printf("\n");
    }
}

void AddMap()
{
    int add, pos;
    char str[2];
    RA = PTR + (VA / 10); 

    if (M[RA][3] == '#')
    {
        printf("**** Page fault occurred ****\n");

        pos = (rand() % 29) * 10;
        printf("POS1   %d\n", pos);

        while (flag[pos / 10] != 0)
        {
            printf("in while pos\n");
            pos = (rand() % 29) * 10;
            printf("POS2  %d\n", pos);
        }

        flag[pos / 10] = 1;
        sprintf(str, "%d", pos);

        if (pos / 100 == 0)
        {
            M[RA][2] = '0';
            M[RA][3] = str[0];
        }
        else
        {
            M[RA][2] = str[0];
            M[RA][3] = str[1];
        }

        PI = 3;
    }

    if (RA > PTR + 10)
    {
        printf("OPERAND ERROR");
        PI = 2;
        MOS();
    }
}

void read()
{
    int no;

    fgets(line, sizeof(line), fin);
    printf("\nLine  :%s", line);

    no = ((M[RA][2] - '0') * 10) + (M[RA][3] - '0');
    no = no * 10;
    int k = 0;

    for (int i = 0; k <= strlen(line); i++)
    {
        for (int j = 0; j < 4 && k <= strlen(line); j++)
        {
            printf("Count  :%d\n%d\n", no + i, j);
            M[no + i][j] = line[k];
            k++;
        }
    }

    
}

void write()
{
    char buffer[40];
    printf("\n In Write : \n");

    int no = 0, i, j, k;

    no = ((M[RA][2] - '0') * 10) + (M[RA][3] - '0');
    no = no * 10;
    k = 0;

    while (1)
    {
        for (i = 0; i < 4; i++)
        {
            if (M[no][i] == '_')
                break;
            buffer[k] = M[no][i];
            k++;
        }
        if (M[no][i] == '_')
            break;
        no++;
    }

    buffer[k] = '\0';
    printf("\n Line is : %s\n", buffer);
    fprintf(fout, "%s", buffer);

    printf("program terminated normally\n");
    fprintf(fout, "\n-----------------------------------------------------------------------------------\n");
    fprintf(fout, "\nprogram terminated normally\n");
}

void MOS()
{
    if (PI == 1)
    {
        printf("\n**** Opcode Error : ***\n*** Program terminated abnormally. ****\n\n");
        fprintf(fout, "\n**** Opcode error : ***\n*** Program terminated abnormally. ****");
        endprogram();
    }
    else if (PI == 2)
    {
        printf("\n**** Operand Error : ***\n*** Program terminated abnormally. ****\n\n");
        fprintf(fout, "\n**** Operand error : ***\n*** Program terminated abnormally. ****");
        endprogram();
    }

    if (SI == 3)
        endprogram();
    else if (SI == 1)
    {
        if (TI == 0)
            read();
        else if (TI == 2)
        {
            printf("\n**** Time Limit Exceeded : ***\n*** Program terminated abnormally. ****");
            fprintf(fout, "\n**** Time Limit Exceeded : ***\n*** Program terminated abnormally. ****");
            endprogram();
        }
    }
    else if (SI == 2)
    {
        printf("\nIN SI=2");
        if (TI == 0)
        {
            printf("\nIN TI=0");
            write();
        }
        else if (TI == 2)
        {
            printf("\nIN TI=0");
            write();
            printf("\n**** Time Limit Exceeded : ***\n*** Program terminated abnormally. ****");
            fprintf(fout, "\n**** Time Limit Exceeded : ***\n*** Program terminated abnormally. ****");
            endprogram();
        }
        else if (TI == 1)
        {
            printf("\n**** Line Limit Exceeded : ***\n*** Program terminated abnormally. ****");
            fprintf(fout, "\n**** Line Limit Exceeded : ***\n*** Program terminated abnormally. ****");
            endprogram();
        }
    }
}

void examine()
{
    char ch;
    ch = IR[0];
    // TI = 0;
    PI = 0;

    switch (ch)
    {
    case 'G':
        printf("\nSI = %d  TI = %d  PI = %d\n", SI, TI, PI);
        printf("TTC = %d  LLC = %d\n", TTC, LLC);

        if (IR[1] != 'D')
        {
            PI = 1;
            MOS();
        }
        else
        {
            TTC = TTC + 2;

            if (TTC <= ttl)
            {
                SI = 1;
                MOS();
            }
            else
            {
                TI = 2;
                MOS();
            }
        }

        printf("\nSI = %d  TI = %d  PI = %d\n", SI, TI, PI);
        printf("TTC = %d  LLC = %d\n", TTC, LLC);
        break;

    case 'P':
        SI = 2;
        printf("\nSI = %d  TI = %d  PI = %d\n", SI, TI, PI);
        printf("TTC = %d  LLC = %d\n", TTC, LLC);

        if (IR[1] != 'D')
        {
            PI = 1;
            MOS();
        }
        else
        {
            LLC = LLC + 1;
            TTC = TTC + 1;

            printf("%d :llc\n", LLC);
            printf("%d :ttc\n", TTC);

            if (LLC < tll)
            {
                TI = 0;
                MOS();
            }

            if (TTC > ttl)
            {
                TI = 1;
                MOS();
            }
            else
            {
                SI = 2;
                MOS();
            }
        }

        printf("\nTTC = %d  LLC = %d\n", TTC, LLC);
        printf("SI = %d  TI = %d  PI = %d\n", SI, TI, PI);
        break;

    case 'H':
        SI = 3;
        MOS();
        break;
    }
}

void executeProgram()
{
    int no;
    char a[3];
    int i, j, k;

    for (i = 0; i <= kio; i++)
    {
        printf("PTR  %d\n", PTR);
        a[0] = M[PTR + i][2];
        a[1] = M[PTR + i][3];
        a[2] = '\0';
        no = ((a[0] - '0') * 10) + (a[1] - '0');
        printf("\nno  %d\n", no);

        for (j = 0; j < 10; j++)
        {
            for (k = 0; k < 4; k++)
            {
                IR[k] = M[(no * 10) + j][k];
            }

            printf("IR  %s\n", IR);

            VA = ((IR[2] - '0') * 10) + (IR[3] - '0');
            AddMap();
            examine();
        }

        printf("\nA  %s\n", a);
    }
}

void startExecution()
{
    IC = 0;
    executeProgram();
}

void init()
{
    int i, j;
    srand(time(NULL)); // Initialize the random number generator

    PTR = (rand() % 29) * 10;
    printf("PTR   %d\n", PTR);

    for (i = 0; i < 30; i++)
    {
        flag[i] = 0;
    }

    flag[PTR / 10] = 1;

    for (i = 0; i < 300; i++)
    {
        for (j = 0; j < 4; j++)
        {
            M[i][j] = '_';
        }
    }

    for (i = PTR; i < PTR + 10; i++)
    {
        for (j = 0; j < 4; j++)
        {
            M[i][j] = '#';
        }
    }
}

int load()
{
    int i, j, k;
    printf("IN LOAD\n");

    if (fin == NULL || fout == NULL)
    {
        printf("Failed to open files.\n");
        return 1;
    }
    else
    {
        while (fgets(line, sizeof(line), fin))
    {
        printf("In while %s\n", line);
        printf("%sline1\n", line);

        if (line[0] == '$' && line[1] == 'A' && line[2] == 'M' && line[3] == 'J')
        {
            SI = 0;
            TI = 0;
            TTC = 0;
            LLC = 0;

            for (i = 4, j = 0; i < 8; i++, j++)
            {
                pcb.job[j] = line[i];
            }

            for (i = 8, j = 0; i < 12; i++, j++)
            {
                pcb.TTL[j] = line[i];
            }

            for (i = 12, j = 0; i < 16; i++, j++)
            {
                pcb.TLL[j] = line[i];
            }

            ttl = (pcb.TTL[0] - '0') * 1000 + (pcb.TTL[1] - '0') * 100 + (pcb.TTL[2] - '0') * 10 + (pcb.TTL[3] - '0');
            tll = (pcb.TLL[0] - '0') * 1000 + (pcb.TLL[1] - '0') * 100 + (pcb.TLL[2] - '0') * 10 + (pcb.TLL[3] - '0');

            printf(" TTL = %d\n", ttl);
            printf(" TLL = %d\n", tll);

            TTC = 0;
            LLC = 0;
            init();
            allocate();
        }

        if (line[0] == '$' && line[1] == 'D' && line[2] == 'T' && line[3] == 'A')
        {
            startExecution();
        }
    }
    }
}

int main()
{
    //FILE *fin, *fout;

    fin = fopen("input1.txt", "r");
    fout = fopen("output1.txt", "w");

    if (fin == NULL || fout == NULL)
    {
        printf("Failed to open files.\n");
        return 1;
    }

    load();

    fclose(fin);
    fclose(fout);

    return 0;
}
