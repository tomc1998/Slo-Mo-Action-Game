/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/waypoint_graph.hpp"
#include <json.hpp>
#include <stdexcept>

using namespace nlohmann;

void to_json(json& j, const CompWaypointGraph& c) {
  throw std::runtime_error("Serialisation of waypoint graph not yet supported");
}

void from_json(const json& j, CompWaypointGraph& c) {
  std::vector<Vec2> waypoints;
  spp::sparse_hash_map<u32, std::vector<u32>> connections;
  const json &j_waypoints = j["waypoints"];
  for (u32 ii = 0; ii < j_waypoints.size(); ++ii) {
    const auto& w = j_waypoints[ii];
    waypoints.push_back(w["pos"]);
    std::vector<u32> w_connections = w["connections"];
    connections[ii] = w_connections;
  }
  c.init(waypoints, connections);
}

