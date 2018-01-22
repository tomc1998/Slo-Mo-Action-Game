#include "level.hpp"
#include <fstream>
#include <iostream>
#include <json.hpp>

#include "parse_comp_game_entity.cpp"
#include "parse_resources.cpp"

Level::Level() : ecs() {}

Level::Level(std::string path, ResourceManager &res_man) {
  using namespace nlohmann;
  std::ifstream i(path);
  json j;
  i >> j;

  this->name = j["name"].get<std::string>();

  auto res_map = parse_resources(j["resources"], res_man);
}
