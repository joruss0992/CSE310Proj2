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


    // Time to read the csv file!
    ifstream occFile;  // ifStream variable to read through the file
    occFile.open("Occupation-Dist-All-1999.csv");  // Opens Occupation.csv file
    
    
    string line = "";   // Line will hold the value of each line in file
    int count = 5;  // Count will be used to skip through the first 5 lines of OCC.csv file
    int index = 0;  // Index used to save the value of current line/ SOC iteration
    bool skip = false;  // Bool to help keep track if first 5 lines have been skipped or not
    while (getline(occFile, line)){ // While there is input from the file, the current line is saved in line variable
        string occ;     // occ hold job title
        string code;    // code holds soc code
        string preT;    // preT holds string value of total workers before being converted to integer
        int t;
        string preF;    // preF holds string value of female workers before being converted to integer
        int f;
        string preM;    // preM holds string value of male workers before being converted to integer
        int m;

        // Skips the first 5 lines
        // -----------------------------------------------
        if(count != 0 && skip == false){
            count --;
            continue;
        }
        // -----------------------------------------------
        skip = true;    // Ensures no other lines are skipped

        int current = 0;    // current holds the value of current position in line being anylized in for loop
        bool occ_quoted = false;    // Bool occupation_quoted handles case where the title contains commas       
        

        for(int i =0; i<line.size(); i++){  // From beginning to end of line...
            current = i+1;  // Current is initialized as one position more than i
            if(line[0] == '"' && occ_quoted == false){  // If the job title contains any commas ','; ie the line starts with a "
                occ_quoted = true;                      // Boolean occ_quoted saves this line's state
                while(line[current] != '"')             // Current is shifted though array until other " is found
                    current++;
            i = current+1;                              // Index i is shifted to the end of the job title so no commas are deleted
            }

            // Once the values total, female, and male are reached this function formats the values to be convertable strings; ie with no "" or ,
            if(line[i] == '"'){     // If a "" is located...
                line.erase(i, 1);   // It is deleted
                while(line[current] != '"'){    // Current scans through the rest of the number
                    if(line[current] == ',')    // Deleting any commas it finds
                        line.erase(current, 1);
                    current++;
                }
                line.erase(current, 1);         // Then deletes the other "" at the end of the number
                i = current;        // i is iterated to catch up to current so next section can be scanned
            }
        }


        string empty = "";  // Holds empty values while scanning through line
        stringstream inputString(line);     // Initializing scanning variable

        if(occ_quoted == true){     // If the current line's occupation contained commas, there are "" around that section still so
            getline(inputString, empty, '"');
            getline(inputString, occ, '"');     // occupation title is extracted from between the ""'s
            getline(inputString, empty, ',');
            getline(inputString, code, ',');    // Following string values are saved, all seperated by commas
            getline(inputString, preT, ',');
            getline(inputString, preF, ',');
            getline(inputString, preM);
            t = std::stoi(preT);    // pre values are converted from string to integer
            f = std::stoi(preF);
            m = std::stoi(preM);
        }
        else{       // Else, the line's occupation contained no commas and can be scanned through comma by comma
            getline(inputString, occ, ',');
            getline(inputString, code, ',');
            getline(inputString, preT, ',');
            getline(inputString, preF, ',');
            getline(inputString, preM);
            t = std::stoi(preT);
            f = std::stoi(preF);
            m = std::stoi(preM);
        }


            for(int i = 0; i<occ.size(); i++){      // occ is saved char by char into the occupation char[] for indexed position in SOC array
                soc[index].occupation[i] = occ[i];
            }
            for(int i = 0; i<code.size(); i++){
                soc[index].SOC_code[i] = code[i];   // code is saved into the SOC_code char[] for indexed position in SOC array
            }
            soc[index].total = t;   // Number values are saved into indexed position of SOC array
            soc[index].female = f;
            soc[index].male = m;

        occ_quoted = false;     // Reset before iterating to next line so new instance can be recognized
        index++;    // Current index incremented to keep track of current line and accompanying SOC array position
    }
    
    /*  Unworking portion commented away
    ----------------------------------
    SOC * socPointer;
    socPointer = soc;

    BUILD_MAX_HEAP(soc, NUM_OCC);   // Code returns error : undefined reference, couldn't get it to work :_(
    -----------------------------------
    */

    return 0;
}
