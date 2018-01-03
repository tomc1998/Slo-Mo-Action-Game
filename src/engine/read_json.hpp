#pragma once
#include "json.hpp"
using json = nlohmann::json;

void from_json(const json &j, Animation &a) {

  spp::sparse_hash_map<std::string, InterpolationType> interp_map =
  { {"LINEAR", LINEAR} };

  // Loops through all the part ids
  for (u32 part_id=0; part_id < j.size(); part_id++) {

    // Creates a json variable that stores the posx keys etc for this part
    const json &keys = j.at(std::to_string(part_id));

    const json &posx = keys.at("posx");
    for (u32 ii = 0; ii < posx.size(); ii++) {
      a.posx_keys.push_back(
          Keyframe(posx[ii].at("value"), posx[ii].at("timestamp"),
                   interp_map[posx[ii].at("interpolation")], part_id));
    }

    const json &posy = keys.at("posy");
    for (u32 ii = 0; ii < posy.size(); ii++) {
      a.posy_keys.push_back(
          Keyframe(posy[ii].at("value"), posy[ii].at("timestamp"),
                   interp_map[posy[ii].at("interpolation")], part_id));
    }

    const json &scale = keys.at("scale");
    for (u32 ii = 0; ii < scale.size(); ii++) {
      a.scale_keys.push_back(
          Keyframe(scale[ii].at("value"), scale[ii].at("timestamp"),
                   interp_map[scale[ii].at("interpolation")], part_id));
    }

    const json &rot = keys.at("rotation");
    for (u32 ii = 0; ii < rot.size(); ii++) {
      a.rot_keys.push_back(
          Keyframe(rot[ii].at("value"), rot[ii].at("timestamp"),
                   interp_map[rot[ii].at("interpolation")], part_id));
    }
  }
}
