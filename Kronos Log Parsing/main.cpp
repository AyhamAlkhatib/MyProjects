// "Copyright 2023 Ayham Alkhatib"
#include "Kronos.hpp"
int main(int argc, char* argv[]) {
  std::fstream file_obj;
  std::string file_name = argv[1];
  file_obj.open(file_name);
  std::string fileOut = file_name;
  fileOut += ".rpt";
  std::ofstream file_out(fileOut);
  std::regex start("\\(log.c.166\\) server started");
  std::regex end("oejs.AbstractConnector:Started SelectChannelConnector");
  // File string
  std::string file_str;
  std::string time1;
  std::string time2;
  int lineNumber = 1;
  bool isEndTime = false;
  bool state = false;
  bool firstEntry = true;
  while (getline(file_obj, file_str)) {
    if (regex_search(file_str, start)) {
      regexStart(start, state, firstEntry, lineNumber, file_name,
       time1, file_str, file_out);
    }
    if (regex_search(file_str, end)) {
      regexEnd(state, isEndTime, file_str, time2,
        file_name, lineNumber, file_out);
    }
    if (isEndTime) {
      isEndTime = false;
      boost::gregorian::date d1 = boost::gregorian::from_simple_string(calGeorgianDate(time1));
      boost::gregorian::date d2 = boost::gregorian::from_simple_string(calGeorgianDate(time2));
      int hours = std::stoi(convertDuaration(time1, HOURS));
      int minutes = std::stoi(convertDuaration(time1, MINUTES));
      int seconds = std::stoi(convertDuaration(time1, SECONDS));
      boost::posix_time::ptime t1(d1, boost::posix_time::time_duration(hours, minutes, seconds));

      hours = std::stoi(convertDuaration(time2, HOURS));
      minutes = std::stoi(convertDuaration(time2, MINUTES));
      seconds = std::stoi(convertDuaration(time2, SECONDS));
      boost::posix_time::ptime t2(d2, boost::posix_time::time_duration(hours, minutes, seconds));

      boost::posix_time::time_duration td = t2 - t1;
      file_out << " Boot Time: " << td.total_milliseconds() << "ms" << std::endl << std::endl;
    }
    lineNumber++;
  }
  if (regex_search(file_str, start)) {
      file_out << "**** Incomplete boot ****";
    }
  file_obj.close();
  file_out.close();
  return 0;
}
