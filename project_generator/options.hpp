#pragma once

#include <string>

class options {
public:
  std::string project_name;
  bool create_files;
  bool update_build;
  options(int argc, char *argv[]);

private:
  void parse_option(char option);
};
