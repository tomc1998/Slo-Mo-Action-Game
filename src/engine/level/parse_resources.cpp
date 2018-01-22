/**
 * This should only be included once from level.cpp.
 */

#include "engine/resource_manager.hpp"
#include <json.hpp>
#include <sparsepp/spp.h>

using namespace nlohmann;

/** Parse a resource object, and return a mapping of strings (resource names)
 * to i32s (resource handles). This will load in all the resources listed with
 * the provided ResourceManager.
 */
spp::sparse_hash_map<std::string, i32>
parse_resources(json &resources, ResourceManager &res_man) {
  spp::sparse_hash_map<std::string, i32> res_map;
  for (json::iterator it = resources.begin(); it != resources.end(); ++it) {
    std::string res_name = it.key();
    json r = it.value();
    std::string res_type = r["type"].get<std::string>();
    if (res_type == "animation") {
      json d = r["data"];
      std::string anim_file = d["path"];
      u32 anim_len = d["length"];
      std::vector<std::string> parts = d["parts"];
      // First load all the parts
      std::vector<TexHandle> part_textures;
      part_textures.reserve(parts.size());
      for (const auto &p : parts) {
        part_textures.push_back(res_man.load_texture(p.c_str()));
      }

      // Now load the animation
      res_map[res_name] =
          res_man.load_animation(anim_file.c_str(), part_textures);
      std::cout << res_name << " " << res_map[res_name] << std::endl;
    }
  }
  return res_map;
}
