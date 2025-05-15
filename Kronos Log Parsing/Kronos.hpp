// "Copyright 2023 Ayham Alkhatib"
#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <locale>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>

typedef enum {HOURS, MINUTES, SECONDS} Duration;
std::string convertDuaration(std::string time, Duration dur);
std::string calGeorgianDate(std::string time);
void regexStart(std::regex start, bool& state, bool& firstEntry, int& lineNumber,
   std::string file_name, std::string& time1, std::string file_str, std::ofstream& file_out);

void regexEnd(bool& state, bool& isEndTime, std::string file_str, std::string& time2,
   std::string file_name, int& lineNumber, std::ofstream& file_out);
