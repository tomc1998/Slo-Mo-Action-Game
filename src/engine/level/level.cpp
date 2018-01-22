#include "level.hpp"
#include <fstream>
#include <iostream>
#include <json.hpp>

#include "parse_comp_game_entity.cpp"

Level::Level() : ecs() {}

Level::Level(std::string path) {
  using namespace nlohmann;
  std::ifstream i(path);
  json j;
  i >> j;

  name = j["name"].get<std::string>();
  std::cout << j.dump(4) << std::endl;

  CompGameEntity e = j["entities"][0]["comp_game_entity"];
  std::cout << e.pos.x << " " << e.pos.y << std::endl;
}
