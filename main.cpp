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



int main(int argc,char* argv[]){
    std::locale loc;        // locale variable initialized to help anylize if current char is an int
    struct SOC soc[NUM_OCC];
    int index = 0;  // Index used to save the value of current line/ SOC iteration


    // Section handles reading the query file
    // ----------------------------------------------------------------------
    string query = "";  // Holds string value of current line from input from queries.txt
    int qNum = 0;   // qNum holds the total number of queries being declared ie the first input from the file
    string queries[50];     // String array that will hold all the queries
    int c = 0;  // temp in to keep track of current query (c)

    while(getline(cin, query)){     // While there is input coming (from queries.txt) 
        if(isdigit(query[0], loc) == true){     // Saves the number of queries which is the first line
            qNum = std::stoi(query);
            string queries[qNum];
        }
        else{
            queries[c] = query; // queries are saved line by line into queries array to keep track of each query later
            c++;
        }
    }
    // ----------------------------------------------------------------------
    


    string year = argv[1];
    string occFile = "Occupation-Dist-All-" + year + ".csv";   // Occupation file is dynamically set according to the query

    // Time to read the occupation files!
    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------

    ifstream fileStream;  // ifStream variable to read through the file
    fileStream.open(occFile);  // Opens Occupation.csv file
    if(fileStream.fail()){    // Makes sure the file is acutally open
        cerr << "Error openning file, file not found: file 1" << endl;
        exit(1);
    }


    string line = "";   // Line will hold the value of each line in file
    int count = 5;  // Count will be used to skip through the first 5 lines of OCC.csv file
    bool skip = false;  // Bool to help keep track if first 5 lines have been skipped or not
    while (getline(fileStream, line)){ // While there is input from the file, the current line is saved in line variable
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

        // Next section handles the values in the line that contain ""
        // -----------------------------------------------
        int current = 0;    // current holds the value of current position in line being anylized in for loop
        bool occ_quoted = false;    // Bool occupation_quoted handles case where the title contains commas       
        for(int i =0; i<line.size(); i++){  // From beginning to end of the current line...
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
        // -----------------------------------------------


        // Next section saves the line's comma seperated 
        // values into their respective variables
        // -----------------------------------------------
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
        soc[index].occupation[occ.size()] = '\0';
        for(int i = 0; i<code.size(); i++){
            soc[index].SOC_code[i] = code[i];   // code is saved into the SOC_code char[] for indexed position in SOC array
        }
        soc[index].SOC_code[code.size()] = '\0';

        soc[index].total = t;   // Number values are saved into indexed position of SOC array
        soc[index].female = f;
        soc[index].male = m;

        occ_quoted = false;     // Reset before iterating to next line so new instance can be recognized
        index++;    // Current index incremented to keep track of current line and accompanying SOC array position
        // -----------------------------------------------
        // The next line is iterated to and processed
    }
    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------
    // end of reading and processing occupation file!











    struct earnings earnings[62];
    // struct hash_table_entry hash[];

    ifstream fileStream2;  // ifStream variable to read through the file
    string earnFile = "Earnings-1960-2019.csv";
    fileStream2.open(earnFile);
    if(fileStream2.fail()){    // Makes sure the file is acutally open
        cerr << "Error openning file, file not found" << endl;
        exit(1);
    }


    line = "";   // Line will hold the value of each line in file
    count = 8;  // Count will be used to skip through the first 5 lines of OCC.csv file
    skip = false;  // Bool to help keep track if first 5 lines have been skipped or not
    while (getline(fileStream2, line)){
        int year;
        int male_total = 0;
        int male_with_earnings = 0;
        int male_earnings = 0;
        int male_earnings_moe = 0;
        int female_total = 0;
        int female_with_earnings = 0;
        int female_earnings = 0;
        int female_earnings_moe = 0;
        // char lineChar[line.size()];

        // Skips the first 8 lines
        // -----------------------------------------------
        if(count != 0 && skip == false){
            count --;
            continue;
        }
        // -----------------------------------------------
        skip = true;    // Ensures no other lines are skipped

        // transform(line, lineChar, line.size()); // Converts the string to char array
        bool isN = false;
        removeQuotes(line);
        // cout << line << endl; 
        saveEarnings(line, year, male_total, male_with_earnings, male_earnings, male_earnings_moe, 
        female_total, female_with_earnings, female_earnings, female_earnings_moe, isN);

        
        // saves the values to earnings array at index 0 to 61
        earnings[count].year = year;
        earnings[count].male_total = male_total;
        earnings[count].male_with_earnings = male_with_earnings;
        earnings[count].male_earnings = male_earnings;
        earnings[count].male_earnings_moe = male_earnings_moe;
        earnings[count].female_total = female_total;
        earnings[count].female_with_earnings = female_with_earnings;
        earnings[count].female_earnings = female_earnings;
        earnings[count].female_earnings_moe = female_earnings_moe;
        count++;
    }










    // Section saves value from soc so they can be reset for each query
    // ----------------------------------------
    struct SOC saved[NUM_OCC];
    for(int i = 0; i < NUM_OCC; i++){
        saved[i] = soc[i];
    }
    // ----------------------------------------

    // Next section handles the queries
    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------
    char key = '\0';
    string temp = "";
    int numMax = 0;        // Number of max position the query wants to know
    string nM;             // String version of numMax before convertion

    for(int i = 0; i<qNum; i++){    // for loop iterates through every query
        for(int i = 0; i < NUM_OCC; i++){
            soc[i] = saved[i];
        }

        nM = "";            // nM is string version of numMax before being converted to int
        temp = queries[i];  // temp set as current query being computed




        // This section handles the ratio Query
        //--------------------------------------------------------------
        int year1 = 0;
        int year2 = 0;
        string ratio = "";
        if(queries[i].size() == 20){
            findYear(temp, year1, year2);
            cout << "Query: " << temp << endl;
            findRatio(ratio, earnings, year1, year2);
        }
        //--------------------------------------------------------------
        else if(queries[i][5] == 'o'){
            cout << "Query: " << temp << endl;
            // build_Hash();
        }

        else if(queries[i][5] == ' '){
            cout << "Query: " << temp << endl;
        }



        

        else{   // Else, The query being requested is a find max query
            // This section handles find max total
            //--------------------------------------------------------------
            if(temp[9] == 't'){     // If the 10th char is a t, its asking for total
                key = 't';  // key saved to help differ between looking for total, female and male
                c = 15;     // c is the position the number for how many iterations this query is requesting begins
                while(temp[c] != '\0'){     // This while loop saves...
                    nM = nM + temp[c];
                    c++;
                }
                numMax = std::stoi(nM);     // Then converts that number to numMax, the number of times to run the delete max function

                // cout << "Heap built for total!" << endl << soc[0].occupation << endl;
                BUILD_MAX_HEAP(soc, NUM_OCC, key);      // Build max heap is called
                index = NUM_OCC;
                for(int i = 0; i < numMax; i++){        // Delete max is called numMax times according to the query
                    DELETE_MAX(soc, index, numMax, key);
                    index--;            // Total size of soc[] is decremented
                }
                // cout << endl;           // Line adds formatting to output 
                 
            }
            //--------------------------------------------------------------

            // Following functions act in the same exact way, this time with keys k and m accordingly
            //--------------------------------------------------------------
            else if(temp[9] == 'f'){    // If the 10th char is a f, its asking for female
                key = 'f';
                c = 16;
                while(temp[c] != '\0'){
                    nM = nM + temp[c];
                    c++;
                }
                numMax = std::stoi(nM);
                
                // cout << "Heap built for female!" << endl << soc[0].occupation << endl;
                BUILD_MAX_HEAP(soc, NUM_OCC, key);
                index = NUM_OCC;
                for(int i = 0; i < numMax; i++){
                    DELETE_MAX(soc, index, numMax, key);
                    index--;
                } 
                // cout << endl;
            }
            else{
                key = 'm';  // Else the 10th char is a m, its asking for male
                c = 14;
                while(temp[c] != '\0'){
                    nM = nM + temp[c];
                    c++;
                }
                numMax = std::stoi(nM);

                // cout << "Heap built for male!" << endl << soc[0].occupation << endl;
                BUILD_MAX_HEAP(soc, NUM_OCC, key);
                index = NUM_OCC;
                for(int i = 0; i < numMax; i++){
                    DELETE_MAX(soc, index, numMax, key);
                    index--;
                } 
                // cout << endl;
            }
            //--------------------------------------------------------------
        }
    }
    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------



    return 0;
}
