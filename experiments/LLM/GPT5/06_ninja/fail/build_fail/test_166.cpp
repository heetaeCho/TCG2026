// File: graph_matches_test_166.cc

#include "gtest/gtest.h"

#include "graph.h"
#include "string_piece.h"

#include <string>
#include <vector>

// Forward declaration of the `matches` struct as implemented in graph.cc.
// We only declare the interface; definitions live in the production code.
struct matches {
 public:
  std::vector<StringPiece>::iterator i_;

  explicit matches(std::vector<StringPiece>::iterator i);
  bool operator()(const Node* node) const;
};

class MatchesTest_166 : public ::testing::Test {
 protected:
  Node MakeNode(const std::string& path) {
    // slash_bits are not relevant to matches; keep it simple.
    return Node(path, /*slash_bits=*/0u);
  }
};

// Verifies that matches returns true when the Node path exactly matches
// the StringPiece pointed to by the iterator.
TEST_F(MatchesTest_166, ReturnsTrueWhenPathMatches_166) {
  std::vector<StringPiece> patterns;
  patterns.emplace_back("out.txt");

  matches predicate(patterns.begin());

  Node node = MakeNode("out.txt");
  EXPECT_TRUE(predicate(&node));
}

// Verifies that matches returns false when the Node path differs from
// the StringPiece pointed to by the iterator.
TEST_F(MatchesTest_166, ReturnsFalseWhenPathDoesNotMatch_166) {
  std::vector<StringPiece> patterns;
  patterns.emplace_back("foo.txt");

  matches predicate(patterns.begin());

  Node node = MakeNode("bar.txt");
  EXPECT_FALSE(predicate(&node));
}

// Verifies that matches uses the *iterator value* (not hard-coded to the
// first element) by using an iterator into the middle of a pattern vector.
TEST_F(MatchesTest_166, UsesIteratorPositionCorrectly_166) {
  std::vector<StringPiece> patterns;
  patterns.emplace_back("first");
  patterns.emplace_back("second");
  patterns.emplace_back("third");

  // Use iterator pointing to "second"
  auto it = patterns.begin() + 1;
  matches predicate(it);

  Node matching_node   = MakeNode("second");
  Node nonmatching_node = MakeNode("third");

  EXPECT_TRUE(predicate(&matching_node));
  EXPECT_FALSE(predicate(&nonmatching_node));
}

// Verifies behavior with empty paths and empty StringPieces as a boundary case.
TEST_F(MatchesTest_166, HandlesEmptyPathAndEmptyPattern_166) {
  std::vector<StringPiece> patterns;
  patterns.emplace_back("");  // empty StringPiece

  matches predicate(patterns.begin());

  Node empty_path_node      = MakeNode("");
  Node non_empty_path_node  = MakeNode("nonempty");

  EXPECT_TRUE(predicate(&empty_path_node));
  EXPECT_FALSE(predicate(&non_empty_path_node));
}
