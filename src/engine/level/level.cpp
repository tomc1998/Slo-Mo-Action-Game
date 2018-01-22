#include "level.hpp"
#include <fstream>
#include <iostream>
#include <json.hpp>

Level::Level() : ecs() {}

Level::Level(std::string path) {
  using namespace nlohmann;
  std::ifstream i(path);
  json j;
  i >> j;

  name = j["name"].get<std::string>();
  std::cout << j.dump(4) << std::endl;
}
