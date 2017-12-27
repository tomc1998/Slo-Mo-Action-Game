#pragma once
#include <vector>

/** Load a whole file into memory. Returns null if an error occured. */
std::vector<char *> load_file_by_lines(const char *filename);
