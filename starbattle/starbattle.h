#ifndef STARBATTLE_STARBATTLE_H_
#define STARBATTLE_STARBATTLE_H_

#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <random>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "maze/maze.h"

namespace starbattle {

namespace internal {

struct BoardEdge {
  int v;
  int color;
  bool star;
};
static_assert(maze::grid::GraphEdge<BoardEdge>);

struct BoardData {
  int color;
  bool star;
};

}  // namespace internal

class Board {
 public:
  explicit Board(int n, maze::grid::Graph<internal::BoardEdge> graph,
                 std::vector<internal::BoardData> data)
      : n_(n), graph_(std::move(graph)), data_(std::move(data)) {}

  const internal::BoardData& GetBoardData(const maze::grid::Cell& cell) const;
  int GetN() const { return n_; }

  friend std::ostream& operator<<(std::ostream& os, const Board& board);

 private:
  int n_;
  maze::grid::Graph<internal::BoardEdge> graph_;
  std::vector<internal::BoardData> data_;

  friend class BoardRandomizer;
};

class BoardRandomizer {
 public:
  template <std::uniform_random_bit_generator G>
  inline static Board GenerateBoard(int n, G& gen) {
    auto graph = maze::grid::ConstructGraph<internal::BoardEdge>(n, n);

    // Choose Stars
    std::vector<int> stars;
    absl::flat_hash_set<int> local_seen;

    CHECK_EQ(ChooseStars(n, gen, stars, local_seen), true);
    for (int star : stars) {
      auto [star_x, star_y] = maze::grid::FromFlatIdx(star, n);
      LOG(INFO) << star_x << " " << star_y;
    }

    auto data = FloodFill(n, graph, stars, gen);

    return Board(n, std::move(graph), std::move(data));
  }

 private:
  // Randomized backtracking algorithm that randomly picks Star positions to
  // form a solution to a Board
  template <std::uniform_random_bit_generator G>
  inline static bool ChooseStars(int n, G& gen, std::vector<int>& stars,
                                 absl::flat_hash_set<int>& seen) {
    if (std::ssize(stars) >= n) return true;

    std::vector<int> star_cands(n * n);
    std::iota(star_cands.begin(), star_cands.end(), 0);
    std::shuffle(star_cands.begin(), star_cands.end(), gen);

    for (auto star_cand : star_cands) {
      if (seen.contains(star_cand)) continue;
      // let's try adding it
      const auto [star_x, star_y] = maze::grid::FromFlatIdx(star_cand, n);
      // Keeps track of newly added seen, so we can correctly undo if this
      // search iteration introduced it
      absl::flat_hash_set<int> undo_log;
      undo_log.insert(star_cand);
      stars.push_back(star_cand);
      seen.insert(star_cand);

      for (int i = 0; i < n; ++i) {
        int col_flat_idx = maze::grid::ToFlatIdx({i, star_y}, n);
        int row_flat_idx = maze::grid::ToFlatIdx({star_x, i}, n);
        if (auto [_, inserted] = seen.insert(col_flat_idx); inserted) {
          undo_log.insert(col_flat_idx);
        }
        if (auto [_, inserted] = seen.insert(row_flat_idx); inserted) {
          undo_log.insert(row_flat_idx);
        }
      }
      for (const auto& [x_d, y_d] : maze::grid::kEightWayDirections) {
        const auto cell = maze::grid::Cell{star_x + x_d, star_y + y_d};
        if (maze::grid::OutOfBounds(cell, n, n)) continue;
        int flat_idx = maze::grid::ToFlatIdx(cell, n);
        if (auto [_, inserted] = seen.insert(flat_idx); inserted) {
          undo_log.insert(flat_idx);
        }
      }

      if (ChooseStars(n, gen, stars, seen)) {
        return true;
      }

      // Backtrack and continue
      stars.pop_back();
      absl::erase_if(seen,
                     [&undo_log](int elem) { return undo_log.contains(elem); });
    };

    return false;
  }

  template <std::uniform_random_bit_generator G>
  inline static std::vector<internal::BoardData> FloodFill(
      int n, maze::grid::Graph<internal::BoardEdge> graph,
      std::vector<int> stars, G& gen) {
    std::vector<internal::BoardData> board_data(
        n * n, internal::BoardData{.color = -1, .star = false});
    std::vector<std::vector<int>> queue_of(stars.size());

    for (size_t i = 0; i < stars.size(); ++i) {
      board_data[stars[i]].star = true;
      queue_of[i].emplace_back(stars[i]);
    }

    int next_queue = 0;
    int colored = 0;

    while (colored < n * n) {
      // randomly dequeue
      auto color = next_queue++ % queue_of.size();
      auto& queue = queue_of[color];
      if (queue.size() == 0) continue;

      auto random_idx =
          std::uniform_int_distribution<int>(0, queue.size() - 1)(gen);
      auto u = queue[random_idx];
      std::swap(queue[random_idx], queue.back());
      queue.pop_back();

      if (board_data[u].color != -1) continue;
      board_data[u].color = color;
      ++colored;

      for (const auto& edge : graph[u]) {
        if (board_data[edge.v].color != -1) continue;
        queue.emplace_back(edge.v);
      }
    }

    return board_data;
  }
};
}  // namespace starbattle

#endif
