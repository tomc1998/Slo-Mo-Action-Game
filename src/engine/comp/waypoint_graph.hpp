#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include <sparsepp/spp.h>
#include <vector>

/** Component that a vector of the waypoints for an ai and the shortest
 * distances between them */
class CompWaypointGraph {
public:
  EntityId entity_id;
  /** vector of all the positions of waypoints */
  std::vector<Vec2> waypoints;
  /** Vector that represents a nxn matrix where n is the number of waypoints of
   * the distances between all of the shortest distances between waypoints.
   * Negative values indicate non-direct connections, as this allows backtracing
   * routes to be incredibly easy */
  std::vector<f32> distances;

  /** Calculates the distances between each waypoint by taking in a hash map of
   * waypoints (as array indices) and a vector of the waypoints that corresponds
   * to (also as array indices)
   * Non-direct connections will be represented with negative distances*/
  void find_distances(spp::sparse_hash_map<u32, std::vector<Vec2>> &connections);

  /** Gets the shortest path between a start and end point that do not
   * necessarily have to be waypoints
   *
   * @param[out] path Vector of waypoints (as positions) to travel through
   *
   * */
  void get_path(Vec2 start, Vec2 end, std::vector<u32> &path);

  CompWaypointGraph(EntityId entity_id, std::vector<Vec2> &waypoints,
                    spp::sparse_hash_map<u32, std::vector<u32>> &connections);
};
