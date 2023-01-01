#include <utils/parse_json.h>

#include <iostream>
#include <fstream>

Json::Value ReadJsonFile(std::string path) {
  std::ifstream ifs(path);
  Json::Value root;

  if (ifs.is_open()) {
    ifs >> root;
    ifs.close();
  } else {
    std::cerr << "Error opening json file.";
  }

  return root;
}