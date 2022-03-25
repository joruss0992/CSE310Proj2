#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <locale>


// If you need to write a function that doesn't have to do with your data structure it should go there
void FIND_QUERY(char query[]);

void removeQuotes(std::string& line);

void saveEarnings(std::string& line, int& year, int& male_total, int& male_with_earnings, int& male_earnings, int& male_earnings_moe, 
int& female_total, int& female_with_earnings, int& female_earnings, int& female_earnings_moe, bool isN);

void transform(std::string line, char chared[], int size);

void findYear(std::string& temp, int& year1, int& year2);

void findRatio(std::string& ratio, struct earnings earnings[], int year1, int year2);


// void findN(std::string& y, std::string& mT, std::string& mW, std::string& mE, std::string& mM,
//     std::string& fT, std::string& fW, std::string& fE, std::string& fM);
