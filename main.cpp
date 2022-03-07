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


        /*
        cout << line << endl;
        if(index == 497)
            cout << "stop" << endl;

        for(int i =0; i<size; i++){
            char line_current = line[i+1];
            char line_prev = line[i];
            if(line[i] == '"'){
                current = i+1;
                if(isdigit(line[current], loc) == false && small == false){   // Checks if "section" is a the title of an occupation, ie: not a number
                    while(line[current] != '"'){
                        temp = temp +line[current];
                        current++;
                    }
                    occ = temp;
                    i = current;
                    temp = "";
                    occ_quoted = true;
                }
                else if(small == true){     //  Case when the second number in sequence is smaller than 1,000
                    current++;
                    while(line[current] != ','){
                        temp = temp +line[current];
                        current++;
                    }
                    if(place == 0)
                        preT = temp;
                    else if(place == 1)
                        preF = temp;
                    else
                        preM = temp;
                    temp = "";
                    i = current-1;
                    place++;
                    // line_current = line[i+1];
                    // line_prev = line[i];
                    small = false;
                    if(isdigit(line[i+2], loc) == true){
                        i--;
                        small = true;
                    }
                }
                else{                                       // "section" begins the number values of the line
                    while(line[current] != '"'){
                        temp = temp +line[current];
                        current++;
                    }
                    if(place == 0)
                        preT = temp;
                    else if(place == 1)
                        preF = temp;
                    else
                        preM = temp;
                    temp = "";
                    i = current;
                    place++;
                    // line_current = line[i+1];
                    // line_prev = line[i];
            
                    if(isdigit(line[i+2], loc) == true){
                        i--;
                        small = true;
                    }
                }
            }

            // Section handles asigning value to soc code when first section is in quotes
            // Needs to be fixed!!
            //  ------------------------------------------
            if(occ_quoted == true && place == 0){
                current = i + 2;
                while(line[current] != ','){
                    temp = temp +line[current];
                    current++;
                }
                i = current;
                code = temp;
                temp = "";  

                line_current = line[i+1];
                line_prev = line[i];
                cout << "";
            }
            if(occ_quoted == true && isdigit(line[i+1], loc) == true){
                // The number is super small!
                superSmall = true;
                cout << "-------------------------" << endl;    // REMOVE
                cout << "This section is a super small case!" << endl;
                break;
            }
            // ----------------------------------------------
        }

        // If there is no "" found, I just handle the input normally
        // cout << "testing the current position" << endl;
        





        if(superSmall == true)
            preT, preF, preM = "";
        

        if(preT.size() != 0 && preF.size() != 0 && preM.size() != 0){
            // Now I need to remove the ',' from the integer strings and convert the string to integer
            for(int i = 0; i < preT.size(); i++){
                if(preT[i] == ',')
                    preT.erase(i, 1);
            }
            t = std::stoi(preT);

            for(int i = 0; i < preF.size(); i++){
                if(preF[i] == ',')
                    preF.erase(i, 1);
            }
            f = std::stoi(preF);

            for(int i = 0; i < preM.size(); i++){
                if(preM[i] == ',')
                    preM.erase(i, 1);
            }
            m = std::stoi(preM);
            soc[index].total = t;
            soc[index].female = f;
            soc[index].male = m;

            cout << t << endl << f << endl << m << endl;
            line = "";
            index++;
        }
        */
    }
    
   
    cout << endl;

    return 0;
}
