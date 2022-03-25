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



void removeQuotes(std::string& line);

void saveEarnings(std::string& line, int& year, int& male_total, int& male_with_earnings, int& male_earnings, int& male_earnings_moe, 
int& female_total, int& female_with_earnings, int& female_earnings, int& female_earnings_moe, bool isN);

void transform(std::string line, char chared[], int size);

void findYear(std::string& temp, int& year1, int& year2);

void findRatio(std::string& ratio, struct earnings earnings[], int year1, int year2);
