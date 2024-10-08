#include <bits/stdc++.h>
using namespace std;

class os{
    private:
        char memory[100][4];
        char ir[4];
        char reg[4];
        int ictr;
        int si;
        bool cr;
        char buffer[40];

    public:
        void osInit();
        // void showState();
        void load();
        void execute();

        fstream input;
        fstream output;

};



void os::osInit(){
    for(int i = 0; i<100; i++){
        for(int j = 0; j<4; j++){
            memory[i][j] = ' ';
        }
    }

    for(int i = 0; i<4; i++){
        ir[i] = ' ';
        reg[i] = ' ';
    }

    for(int i = 0; i<40; i++){
        buffer[i] = ' ';
    }

    ictr = 0;
    cr = false;
}

void os::execute(){
    while(true){
        for(int i = 0; i<4; i++){
            ir[i] = memory[ictr][i];
        }
        ictr++;

        if(ir[0]=='G' && ir[1]=='D'){
            int loc = (ir[2]-'0')*10+(ir[3]-'0');
            for(int k = 0; k<40; k++){
                buffer[k] = ' ';
            }
            input.getline(buffer, 40);
            int k = 0;
            for(int i = loc; i<((loc+10)/10)*10; i++){
                for(int j = 0; j<4; j++){
                    memory[i][j] = buffer[k];
                    k++;
                }
                if(k==40){
                    break;
                }
            }
        }else if(ir[0]=='P' && ir[1]=='D'){
            int loc = (ir[2]-'0')*10+(ir[3]-'0');
            for(int i = loc; i<((loc+10)/10)*10; i++){
                for(int j = 0; j<4; j++){
                    output<<memory[i][j];
                }
            }
            output<<'\n';
        }else if(ir[0]=='L' && ir[1]=='R'){
            int loc = (ir[2]-'0')*10+(ir[3]-'0');
            for(int i = 0; i<4; i++){
                reg[i] = memory[loc][i];
            }
        }else if(ir[0]=='S' && ir[1]=='R'){
            int loc = (ir[2]-'0')*10+(ir[3]-'0');
            for(int i = 0; i<4; i++){
                memory[loc][i] = reg[i];
            }
        }else if(ir[0]=='B' && ir[1]=='T'){
            int loc = (ir[2]-'0')*10+(ir[3]-'0');
            if(cr){
                ictr = loc;
            }
        }else if(ir[0]=='C' && ir[1]=='R'){
            int loc = (ir[2]-'0')*10+(ir[3]-'0');
            bool flag = true;
            for(int i = 0; i<4; i++){
                if(memory[loc][i] != reg[i]){
                    flag = false;
                    break;
                }
            }

            cr = flag;
        }else if(ir[0]=='H'){
            output<<"\n";
            output<<"\n";
            break;
        }
    }
}

void os::load(){
    int x = 0;
    do{
        for(int i = 0; i<40; i++){
            buffer[i] = ' ';
        }

        input.getline(buffer, 40);

        // for(int i = 0; i<40; i++){
        //     cout<<buffer[i];
        // }
        // cout<<endl;

        if(buffer[0]=='$' && buffer[1]=='A' && buffer[2]=='M' && buffer[3]=='J'){
            osInit();
        }else if(buffer[0]=='$' && buffer[1]=='D' && buffer[2]=='T' && buffer[3]=='A'){
            execute();
        }else if(buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D'){
            x = 0;
            continue;
        }else{
            int k = 0;
            for(int i = x; i<100; i++){
                for(int j = 0; j<4; j++){
                    memory[i][j] = buffer[k];
                    k++;
                }
                if(k==40){
                    break;
                }
                x++;
            }
        }

    }while(!input.eof());
}

int main(){
    os vm;
    vm.input.open("input.txt", ios::in);
    vm.output.open("output.txt", ios::out);

    vm.load();

    return 0;

}
