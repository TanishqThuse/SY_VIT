#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring> 

using namespace std;

int IC, PTR, VA, RA, kio = -1, flag[30], PI, TI, SI, TTC = 0, LLC = 0;
char M[300][4], IR[4], R[4], C;
fstream fin, fout;
char temp[100];
string line;
void MOS();

struct PCB {
    char job[4], TTL[4], TLL[4];
} pcb;

int ttl, tll;

void endprogram() {
    fout << "\nSI = " << SI << "  TI =" << TI << "  PI=" << PI << endl;
    fout << "TTC = " << TTC << "  LLC=" << LLC << endl;
    exit(1);
}

void allocate() {
    int pos, i, j, k = 0, check = 0, len;
    char str[2];
    int level = 0;

    while (check != 1) {
        kio++;
        pos = (rand() % 29) * 10;

        while (flag[pos / 10] != 0) {
            pos = (rand() % 29) * 10;
        }

        flag[pos / 10] = 1;
        sprintf(str, "%d", pos);
        M[PTR + kio][2] = (pos / 100 == 0) ? '0' : str[0];
        M[PTR + kio][3] = str[(pos / 100 == 0) ? 0 : 1];

        getline(fin, line);
        level++;
        k = 0;

        for (i = 0; i < line.size() / 4; i++) {
            for (j = 0; j < 4; j++) {
                M[pos + i][j] = line[k];
                k++;
                if (line[k] == 'H') {
                    check = 1;
                    M[pos + (i + 1)][0] = 'H';
                    M[pos + (i + 1)][1] = '0';
                    M[pos + (i + 1)][2] = '0';
                    M[pos + (i + 1)][3] = '0';
                }
            }
        }
    }

    cout << endl << "MEMORY" << endl;
    for (i = 0; i < 300; i++) {
        cout << "[" << i << "] = ";
        for (j = 0; j < 4; j++) {
            cout << M[i][j];
        }
        cout << endl;
    }
}

void AddMap() {
    int add, pos;
    char str[2];
    RA = PTR + (VA / 10);

    if (M[RA][3] == '#') {
        cout << "**** Page fault occurred ****\n";
        pos = (rand() % 29) * 10;

        while (flag[pos / 10] != 0) {
            pos = (rand() % 29) * 10;
        }

        flag[pos / 10] = 1;
        std::string pos_str = std::to_string(pos);
        strncpy(str, pos_str.c_str(), sizeof(str) - 1);
        str[sizeof(str) - 1] = '\0';
        M[RA][2] = (pos / 100 == 0) ? '0' : str[0];
        M[RA][3] = str[(pos / 100 == 0) ? 0 : 1];

        PI = 3;
    }

    if (RA > PTR + 10) {
        PI = 2;
        MOS();
    }
}

void read() {
    int no, i, j, k;
    getline(fin, line);
    cout << "\nLine  :" << line;
    no = ((M[RA][2] - 48) * 10) + (M[RA][3] - 48);
    no = no * 10;
    k = 0;

    for (i = 0; k <= line.size(); i++) {
        for (j = 0; j < 4 && k <= line.size(); j++) {
            M[no + i][j] = line[k];
            k++;
        }
    }

    for (i = 0; i < 300; i++) {
        cout << "[" << i << "] = ";
        for (j = 0; j < 4; j++) {
            cout << M[i][j];
        }
        cout << endl;
    }
}

void write() {
    char buff[40];
    cout << "\n In Write : \n";
    int no = 0, i, j, k;
    no = ((M[RA][2] - 48) * 10) + (M[RA][3] - 48);
    no = no * 10;
    k = 0;

    while (1) {
        for (i = 0; i < 4; i++) {
            if (M[no][i] == '_')
                break;
            buff[k] = M[no][i];
            k++;
        }
        if (M[no][i] == '_')
            break;
        no++;
    }

    buff[k] = '\0';
    cout << "\n Line is : " << buff << endl; // Print to terminal

    // Add the output you want to print at the end
    cout << "program terminated normally" << endl;
    fout.write(buff, strlen(buff));

    // Print the final status
    cout << "SI = " << SI << "  TI = " << TI << "  PI = " << PI << "  TTC = " << TTC << "  LLC = " << LLC << endl;
}


void MOS() {
    if (PI == 1) {
        cout << "\n**** Opcode Error : ****\n**** Program terminated abnormally. ****\n\n";
        fout << "\n**** Opcode error : ****\n**** Program terminated abnormally. ****";
        endprogram();
    } else if (PI == 2) {
        cout << "\n**** Operand Error : ****\n**** Program terminated abnormally. ****\n\n";
        fout << "\n**** Operand error : ****\n**** Program terminated abnormally. ****";
        endprogram();
    }

    if (SI == 3)
        endprogram();
    else if (SI == 1) {
        if (TI == 0)
            read();
        else if (TI == 2) {
            cout << "\n**** Time Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            fout << "\n**** Time Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            endprogram();
        }
    } else if (SI == 2) {
        if (TI == 0) {
            write();
        } else if (TI == 2) {
            write();
            cout << "\n**** Time Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            fout << "\n**** Time Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            endprogram();
        } else if (TI == 1) {
            cout << "\n**** Line Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            fout << "\n**** Line Limit Exceeded : ****\n**** Program terminated abnormally. ****";
            endprogram();
        }
    }
}

void examine() {
    char ch = IR[0];
    PI = 0;

    switch (ch) {
        case 'G':
            if (IR[1] != 'D') {
                PI = 1;
                MOS();
            } else {
                TTC += 2;
                if (TTC <= ttl) {
                    SI = 1;
                    MOS();
                } else {
                    TI = 2;
                    MOS();
                }
            }
            break;

        case 'P':
            if (IR[1] != 'D') {
                PI = 1;
                MOS();
            } else {
                LLC++;
                TTC++;
                if (LLC < tll) {
                    TI = 2;
                    MOS();
                }
                if (TTC > ttl) {
                    TI = 1;
                    MOS();
                } else {
                    SI = 2;
                    MOS();
                }
            }
            break;

        case 'H':
            SI = 3;
            MOS();
            break;
    }
}

void executeProgram() {
    int no;
    char a[3];
    for (int i = 0; i <= kio; i++) {
        a[0] = M[PTR + i][2];
        a[1] = M[PTR + i][3];
        a[2] = '\0';
        no = ((a[0] - 48) * 10) + (a[1] - 48);
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 4; k++) {
                IR[k] = M[(no * 10) + j][k];
            }
            VA = ((IR[2] - 48) * 10) + (IR[3] - 48);
            AddMap();
            examine();
        }
    }
}

void startExecution() {
    IC = 0;
    executeProgram();
}

void init() {
    PTR = (rand() % 29) * 10;
    for (int i = 0; i < 30; i++) {
        flag[i] = 0;
    }
    flag[PTR / 10] = 1;
    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 4; j++) {
            M[i][j] = '_';
        }
    }
    for (int i = PTR; i < PTR + 10; i++) {
        for (int j = 0; j < 4; j++) {
            M[i][j] = '#';
        }
    }
}

void load() {
    printf("IN LOAD:");
    int i, j;
    while (fin) {
        getline(fin, line);
        if (line[0] == '$' && line[1] == 'A' && line[2] == 'M' && line[3] == 'J') {
            SI = 0;
            TI = 0;
            TTC = 0; LLC = 0;
            for (i = 4, j = 0; i < 8; i++, j++) {
                pcb.job[j] = line[i];
            }
            for (i = 8, j = 0; i < 12; i++, j++) {
                pcb.TTL[j] = line[i];
            }
            for (i = 12, j = 0; i < 16; i++, j++) {
                pcb.TLL[j] = line[i];
            }
            ttl = (pcb.TTL[0] - 48) * 1000 + (pcb.TTL[1] - 48) * 100 + (pcb.TTL[2] - 48) * 10 + (pcb.TTL[3] - 48);
            tll = (pcb.TLL[0] - 48) * 1000 + (pcb.TLL[1] - 48) * 100 + (pcb.TLL[2] - 48) * 10 + (pcb.TLL[3] - 48);
            TTC = 0;
            LLC = 0;
            init();
            allocate();
        }
        if (line[0] == '$' && line[1] == 'D' && line[2] == 'T' && line[3] == 'A') {
            startExecution();
        }
    }
}

int main() {
    fin.open("input.txt");
    // fout.open("C:\\Users\\Student TYCSD\\Desktop\\CSAI\\OS\\output.txt");
    string path = "/run/media/tanishqthuse/HDD-500GB/Backup/Tanishq/VIT/VIT_File/SY_VIT/3_SY_Sem3/Operating Systems/CP_OS/OS_CP_PROJECT/Design-of-Multi-programming-operating-system/OS CP 17 OCT/output.txt";

    // fout.open("C:\\Users\\Student TYCSD\\Desktop\\CSAI\\OS\\output.txt");
    fout.open(path);

if (!fout) {
    cerr << "Error opening output file!" << endl;
    return 1; // Exit with error code
}

    load();
    return 0;
}
