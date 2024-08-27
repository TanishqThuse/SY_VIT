#include <iostream>
#include <fstream>
using namespace std;

class OS {
private:
    char M[100][4];     // Physical Memory
    char IR[4];         // Instruction Register (4 bytes)
    char R[4];          // General Purpose Register (4 bytes)
    int IC;             // Instruction Counter Register (2 bytes)
    int SI;             // Interrupt
    bool C;             // Toggle (1 byte)
    char buffer[40];

public:
    void init();
    void LOAD();
    void Execute();
    void MOS();
    void ReadData();
    void WriteData();
    void Terminate();
    void LoadInstruction();
    void StoreInstruction();
    void CompareRegisters();
    void BranchIfTrue();
    void ClearBuffer();
    void PrintMemory();

    fstream infile;
    fstream outfile;
};

// Initialize everything to 0
void OS::init() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 4; j++) {
            M[i][j] = ' ';
        }
    }
    for (int i = 0; i < 4; i++) {
        IR[i] = ' ';
        R[i] = ' ';
    }
    C = false;
}

// Clear the buffer
void OS::ClearBuffer() {
    for (int i = 0; i < 40; i++) {
        buffer[i] = '\0';
    }
}

// Print the memory
void OS::PrintMemory() {
    for (int i = 0; i < 100; i++) {
        cout << "M[" << i << "]\t";
        for (int j = 0; j < 4; j++) {
            cout << M[i][j];
        }
        cout << endl;
    }
}

// Master Mode
void OS::MOS() {
    ClearBuffer();
    if (SI == 1) { // Read Mode
        infile.getline(buffer, 40);
        ReadData();
    } else if (SI == 2) { // Write Mode
        WriteData();
    } else if (SI == 3) { // Terminate
        Terminate();
    }
}

// Read data into memory
void OS::ReadData() {
    int k = 0;
    int i = (IR[2] - '0') * 10;

    for (int l = 0; l < 10; ++l) {
        for (int j = 0; j < 4; ++j) {
            M[i][j] = buffer[k++];
        }
        if (k == 40) break;
        i++;
    }
    PrintMemory();
}

// Write data from memory to output
void OS::WriteData() {
    ClearBuffer();
    int k = 0;
    int i = (IR[2] - '0') * 10;

    for (int l = 0; l < 10; ++l) {
        for (int j = 0; j < 4; ++j) {
            buffer[k] = M[i][j];
            outfile << buffer[k++];
        }
        if (k == 40) break;
        i++;
    }
    outfile << "\n";
    PrintMemory();
}

// Terminate the program
void OS::Terminate() {
    outfile << "\n\n";
}

// Execution
void OS::Execute() {
    while (true) {
        LoadInstruction();
        IC++;

        if (IR[0] == 'G' && IR[1] == 'D') { // GD
            SI = 1;
            MOS();
        } else if (IR[0] == 'P' && IR[1] == 'D') { // PD
            SI = 2;
            MOS();
        } else if (IR[0] == 'H') { // H
            SI = 3;
            MOS();
            break;
        } else if (IR[0] == 'L' && IR[1] == 'R') { // LR
            LoadInstruction();
        } else if (IR[0] == 'S' && IR[1] == 'R') { // SR
            StoreInstruction();
        } else if (IR[0] == 'C' && IR[1] == 'R') { // CR
            CompareRegisters();
        } else if (IR[0] == 'B' && IR[1] == 'T') { // BT
            BranchIfTrue();
        }
    }
}

// Load instruction into the register
void OS::LoadInstruction() {
    for (int i = 0; i < 4; i++) {
        IR[i] = M[IC][i];
    }
}

// Store instruction from register to memory
void OS::StoreInstruction() {
    int i = (IR[2] - '0') * 10 + (IR[3] - '0');
    for (int j = 0; j < 4; j++) {
        M[i][j] = R[j];
    }
}

// Compare registers
void OS::CompareRegisters() {
    int i = (IR[2] - '0') * 10 + (IR[3] - '0');
    C = true; // Assume they are equal initially
    for (int j = 0; j < 4; j++) {
        if (M[i][j] != R[j]) {
            C = false; // Set C to false if any character differs
            break;
        }
    }
}

// Branch if true
void OS::BranchIfTrue() {
    if (C) {
        int i = (IR[2] - '0') * 10 + (IR[3] - '0');
        IC = i;
    }
}

// Load Function
void OS::LOAD() {
    cout << "Reading Data..." << endl;
    int x = 0;

    do {
        ClearBuffer();
        infile.getline(buffer, 40);
        
        for (int k = 0; k < 40; k++) {
            cout << buffer[k];
        }

        if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J') {
            init();
        } else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A') {
            IC = 0;
            Execute();
        } else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D') {
            continue;
        } else {
            int k = 0;
            for (; x < 100; ++x) {
                for (int j = 0; j < 4; ++j) {
                    M[x][j] = buffer[k++];
                }
                if (k == 40 || buffer[k] == ' ' || buffer[k] == '\n') {
                    break;
                }
            }
        }
    } while (!infile.eof());
}

int main() {
    OS os;

    os.infile.open("input.txt", ios::in);
    os.outfile.open("output.txt", ios::out);

    if (!os.infile) {
        cout << "Failure" << endl;
    } else {
        cout << "File Exists" << endl;
    }

    os.LOAD();

    return 0;
}
