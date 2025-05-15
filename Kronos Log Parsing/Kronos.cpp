// "Copyright 2023 Ayham Alkhatib"
#include "Kronos.hpp"
void regexStart(std::regex start, bool& state, bool& firstEntry, int& lineNumber,
    std::string file_name, std::string& time1, std::string file_str, std::ofstream& file_out) {
      if (!firstEntry && !state) {
        file_out << "**** Incomplete boot ****" << std::endl << std::endl;
      } else {
        state = false;
      }
        file_out  << "=== Device boot ===" << std::endl;
        std::string time;
      // Extracting the date and the hour
      for (int i = 0; i < 19; i++) {
          time += file_str[i];
      }
      time1 = time;
      // Parsing the date.
      std::stringstream ss(time);
      boost::posix_time::time_facet* ofacet =
          new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S");
      boost::posix_time::time_input_facet* ifacet =
          new boost::posix_time::time_input_facet("%Y-%m-%d %H:%M:%S");
      ss.imbue(std::locale(ss.getloc(), ifacet));
      file_out.imbue(std::locale(file_out.getloc(), ofacet));
      // Creating an oTime var to print out
      boost::posix_time::ptime oTime;
      ss >> oTime;
      file_out << lineNumber << "(" << file_name << "): " << oTime << " Boot Start" << std::endl;
      firstEntry = false;
}

void regexEnd(bool& state, bool& isEndTime, std::string file_str, std::string& time2,
   std::string file_name, int& lineNumber, std::ofstream& file_out) {
    state = true;
      isEndTime = true;
      std::string time;
      for (int i = 0; i < 19; i++) {
          time += file_str[i];
      }
      time2 = time;
      // Parsing the date.
      std::stringstream ss(time);
      boost::posix_time::time_facet* ofacet =
          new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S");
      boost::posix_time::time_input_facet* ifacet =
          new boost::posix_time::time_input_facet("%Y-%m-%d %H:%M:%S");
      ss.imbue(std::locale(ss.getloc(), ifacet));
      file_out.imbue(std::locale(file_out.getloc(), ofacet));
      // Creating an oTime var to print out
      boost::posix_time::ptime oTime;
      ss >> oTime;
      file_out  << lineNumber << "(" << file_name << "): "
        << oTime << " Boot Completed" << std::endl;
}

std::string convertDuaration(std::string time, Duration dur) {
    if (dur == HOURS) {
        std::string hour;
        for (int i = 11; i < 13; i++)
            hour += time[i];
        return hour;
    } else if (dur == MINUTES) {
        std::string minute;
        for (int i = 14; i < 16; i++)
            minute += time[i];
        return minute;
    } else {
        std::string seconds;
        for (int i = 17; i < 19; i++)
            seconds += time[i];
        return seconds;
    }
}
std::string calGeorgianDate(std::string time) {
    std::string georgianDate;
    for (int i = 0; i < 10; i++) {
        georgianDate += time[i];
    }
    return georgianDate;
}


