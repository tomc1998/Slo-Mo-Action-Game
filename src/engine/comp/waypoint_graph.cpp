#include "engine/vec.hpp"
#include "waypoint_graph.hpp"
#include <sparsepp/spp.h>
#include <vector>

void CompWaypointGraph::find_distances(
    spp::sparse_hash_map<u32, std::vector<Vec2>> &connections) {

  u32 waypoint_count = this->waypoints.size();

  // Vector to store the current temporary label for each vertex
  std::vector<f32> temp_labels(waypoint_count);

  for (u32 ii = 0; ii < waypoint_count; ii++) {
    this->distances[ii * waypoint_count + ii] = 0;

    u32 pos = ii;
    std::fill(temp_labels.begin(), temp_labels.end(), 9999999);
    temp_labels[pos] = 0;
    // Only n-1 permanent labels have to be found
    for (u32 jj = 0; jj < waypoint_count - 1; jj++) {
      // Change temp labels
      for (const auto &conn : connections[pos]) {
        f32 distance =
            temp_labels[pos] + (waypoints[pos] - waypoints[conn]).len();

        if (temp_labels[conn] < distance) {
          temp_labels[conn] = distance;
        }
      }
      // Set permanent label
      pos = *std::min_element(temp_labels.begin(), temp_labels.end());
      if (std::find(connections[ii].begin(), connections[ii].end(), pos) !=
          connections[ii].end()) {
        this->distances[ii * waypoint_count + pos] = temp_labels[pos];
      } else {
        this->distances[ii * waypoint_count + pos] = -1 * temp_labels[pos];
      }
    }
  }
}

CompWaypointGraph::CompWaypointGraph(
    EntityId entity_id, std::vector<Vec2> &waypoints,
    spp::sparse_hash_map<u32, std::vector<u32>> &connections) {

  this->entity_id = entity_id;

  // Copy the waypoint data
  this->waypoints.reserve(waypoints.size());
  for (u32 ii = 0; ii < waypoints.size(); ii++) {
    this->waypoints[ii] = waypoints[ii];
  }

  find_distances(connections);
}

void CompWaypointGraph::get_path(Vec2 start, Vec2 end, std::vector<u32> &path) {
  f32 waypoint_count = this->waypoints.size();
  u32 start_waypoint;
  u32 end_waypoint;

  // Minimum distances from the actual start and end to a waypoint
  f32 min_start_distance = 1000000.0;
  f32 min_end_distance = 1000000.0;

  // Find the start and end waypoints
  for (u32 ii = 0; ii < waypoint_count; ii++) {
    f32 start_distance = (start - this->waypoints[ii]).len2();
    f32 end_distance = (end - this->waypoints[ii]).len2();

    if (start_distance < min_start_distance) {
      min_start_distance = start_distance;
      start_waypoint = ii;
    }

    if (end_distance < min_end_distance) {
      min_end_distance = end_distance;
      end_waypoint = ii;
    }
  }

  // Backtraces from the end waypoint to the start waypoint to find the path
  // distance_left initialised to -1 so the loop runs at least once
  f32 distance_left = -1.0;
  for (u32 ii = 0; distance_left != 0.0; ii++) {
    path.push_back(this->waypoints[end_waypoint]);
    distance_left =
        this->distances[start_waypoint * waypoint_count + end_waypoint];

    // Find the previous vertex in the path
    for (u32 jj = 0; jj < waypoint_count; jj++) {

      // Make sure we do not visit the same vertex
      if (jj != end_waypoint &&
          // Check that going back down through this vertex gives us the correct
          // distance left
          (distance_left -
           this->distances[end_waypoint * waypoint_count + jj]) ==
              (this->distances[start_waypoint * waypoint_count + jj]) &&
          // Check it is a direct connection (non-directs are negative
          this->distances[end_waypoint * waypoint_count + jj] >= 0.0) {

        end_waypoint = jj;
        distance_left =
            this->distances[start_waypoint * waypoint_count + end_waypoint];
        break;
      }
    }
  }
  //The path is generated from back to front, so it needs to be reversed
  std::reverse(path.begin(), path.end());
}
