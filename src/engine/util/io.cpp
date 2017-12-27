#include "engine/util/io.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

/** Loads a file into a list of lines. */
std::vector<char *> load_file_by_lines(const char *filename) {
  std::vector<char *> lines;

  std::string line;
  std::ifstream f(filename);
  while (getline(f, line)) {
    char *c_line = (char *)malloc(line.length() + 2);
    line.copy(c_line, line.length());
    c_line[line.length()] = '\n';
    c_line[line.length() + 1] = 0;
    lines.push_back(c_line);
  }

  return lines;
}
