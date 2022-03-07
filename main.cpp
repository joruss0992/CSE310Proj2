// Jacob Russ
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>

#include "maxheap.h"
#include "bst.h"
#include "hashtable.h"
#include "utilities.h"

using namespace std;


int main(){
    struct SOC soc[NUM_OCC];
    std::locale loc;


    // Time to read the csv file!
    ifstream occFile;  
    occFile.open("Occupation-Dist-All-1999.csv");  // Opens Occupation.csv file
    
    
    string line = "";
    int count = 5;
    int index = 0;
    bool skip = false;
    while (getline(occFile, line)){
        string occ;
        string code;
        string preT;
        int t;
        string preF;
        int f;
        string preM;
        int m;
        string temp = "";

        if(count != 0 && skip == false){                     // Skips the first 5 lines
            count --;
            continue;
        }
        skip = true;

        int current = 0;
        bool occ_quoted = false;


        cout << line << endl;

        
        
        
        for(int i =0; i<line.size(); i++){
            current = i+1;
            
            if(line[0] == '"' && occ_quoted == false){  // If the job title contains any commas ',' ie the line starts with a "
                occ_quoted = true;                      // Boolean occ_quoted saves this lines state
                while(line[current] != '"')
                    current++;
            i = current+1;                              // Index i is shifted to the end of the job title so no commas are deleted
            }

            if(line[i] == '"'){
                line.erase(i, 1);
                while(line[current] != '"'){
                    if(line[current] == ',')
                        line.erase(current, 1);
                    current++;
                }
                line.erase(current, 1);
                i = current;
            }
        }


        string empty = "";

        stringstream inputString(line);

        if(occ_quoted == true){
            getline(inputString, empty, '"');
            getline(inputString, occ, '"');
            getline(inputString, empty, ',');
            getline(inputString, code, ',');
            getline(inputString, preT, ',');
            getline(inputString, preF, ',');
            getline(inputString, preM);
            t = std::stoi(preT);
            f = std::stoi(preF);
            m = std::stoi(preM);
        }
        else{
            getline(inputString, occ, ',');
            getline(inputString, code, ',');
            getline(inputString, preT, ',');
            getline(inputString, preF, ',');
            getline(inputString, preM);
            t = std::stoi(preT);
            f = std::stoi(preF);
            m = std::stoi(preM);
        }


            for(int i = 0; i<occ.size(); i++){
                soc[index].occupation[i] = occ[i];
            }
            for(int i = 0; i<code.size(); i++){
                soc[index].SOC_code[i] = code[i];
            }
            soc[index].total = t;
            soc[index].female = f;
            soc[index].male = m;

        occ_quoted = false;
        index++;


    }
    
   
    cout << endl;

    return 0;
}
