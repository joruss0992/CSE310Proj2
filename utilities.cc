#include "utilities.h"

void FIND_QUERY(char query[]){
    printf("%c\n" , query[0]);
}

void transform(std::string line, char chared[], int size){  // Dont think I ended up needing this...
    for(int i = 0; i < size; i++){
        chared[i] = line[i];
    }
}


void removeQuotes(std::string& line){
    int current = 0;    // current holds the value of current position in line being anylized in for loop
        for(int i =0; i<line.size(); i++){  // From beginning to end of the current line...
            current = i+1;  // Current is initialized as one position more than i
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
}

void saveEarnings(std::string& line, int& year, int& male_total, int& male_with_earnings, int& male_earnings, int& male_earnings_moe, 
int& female_total, int& female_with_earnings, int& female_earnings, int& female_earnings_moe, bool isN){
    std::string y = "";
    std::string mT= "";
    std::string mW= "";
    std::string mE= "";
    std::string mM= "";
    std::string fT= "";
    std::string fW= "";
    std::string fE= "";
    std::string fM= "";
    std::stringstream inputString(line);     // Initializing scanning variable

    // Else, the line's occupation contained no commas and can be scanned through comma by comma
    std::getline(inputString, y, ',');
    std::getline(inputString, mT, ',');
    std::getline(inputString, mW, ',');
    std::getline(inputString, mE, ',');
    std::getline(inputString, mM, ',');
    std::getline(inputString, fT, ',');
    std::getline(inputString, fW, ',');
    std::getline(inputString, fE, ',');
    std::getline(inputString, fM, ',');
    
    if(y == "N" || mT == "N" || mW == "N" || mE == "N" || mM == "N" || 
    fT == "N" || fW == "N" || fE == "N" || fM == "N"){
        isN = true;
        if(y == "N")
            year = -1;
        else
            year = std::stoi(y);

        if(mT == "N")
            male_total = -1;
        else
            male_total = std::stoi(mT);

        if(mW == "N")
            male_with_earnings = -1;
        else
            male_with_earnings = std::stoi(mW);

        if(mE == "N")
            male_earnings = -1;
        else 
            male_earnings = std::stoi(mE);

        if(mM == "N")
            male_earnings_moe = -1;
        else
            male_earnings_moe = std::stoi(mM);

        if(mT == "N")
            female_total = -1;
        else
            female_total = std::stoi(fT);

        if(mW == "N")
            female_with_earnings = -1;
        else
            female_with_earnings = std::stoi(fW);

        if(mE == "N")
            female_earnings = -1;
        else 
            female_earnings = std::stoi(fE);

        if(mM == "N")
            female_earnings_moe = -1;
        else
            female_earnings_moe = std::stoi(fM);
        return;
    }

    year = std::stoi(y);
    male_total = std::stoi(mT);
    male_with_earnings = std::stoi(mW);
    male_earnings = std::stoi(mE);
    male_earnings_moe = std::stoi(mM);
    female_total = std::stoi(fT);
    female_with_earnings = std::stoi(fW);
    female_earnings = std::stoi(fE);
    female_earnings_moe = std::stoi(fM);

    // std::cout << year << std::endl;
    // std::cout << male_total << std::endl;
    // std::cout << male_with_earnings << std::endl;
    // std::cout << male_earnings << std::endl;
    // std::cout << male_earnings_moe << std::endl;
    // std::cout << female_total << std::endl;
    // std::cout << female_with_earnings << std::endl;
    // std::cout << female_earnings << std::endl;
    // std::cout << female_earnings_moe << std::endl;

}

// void findN(std::string& y, std::string& mT, std::string& mW, std::string& mE, std::string& mM,
//     std::string& fT, std::string& fW, std::string& fE, std::string& fM){
        
//     }

void findYear(std::string& temp, int& year1, int& year2){
    std::string trash = "";
    std::string y1 = "";
    std::string y2 = "";
    std::stringstream inputString(temp);     // Initializing scanning variable

    // Else, the line's occupation contained no commas and can be scanned through comma by comma
    std::getline(inputString, trash, ' ');
    std::getline(inputString, trash, ' ');
    std::getline(inputString, y1, ' ');
    year1 = std::stoi(y1);
    std::getline(inputString, y2, ' ');
    year2 = std::stoi(y2);
}

void findRatio(std::string& ratio, struct earnings earnings[], int year1, int year2){
    int start = 0;
    float   b = 0,
            a = 0, 
            c = 0;

    while(earnings[start].year != year1){
        start++;
    }  // Now "start" is at year1's position in the earnings array
    
    std::cout << "\nThe female-to-male earnings ratio for " << year1 << "-" << year2 << ":" << std::endl;

    while(earnings[start].year != year2 + 1){
        a = earnings[start].female_earnings;
        b = earnings[start].male_earnings;
        c = a / b * 100 - .05;
        c = std::floor(100 * c) / 100;
        std::cout << "\t" << earnings[start].year << ": " << std::fixed << std::setprecision(1) << c << "%" << std::endl;
        start--;
    }

}
