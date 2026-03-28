// TEST_ID: 567
#include <gtest/gtest.h>

#include <iterator>   // std::distance
#include <string>

#include <yaml-cpp/yaml.h>

namespace {

TEST(NodeBeginTest_567, DefaultConstructedNodeBeginEqualsEnd_567) {
  const YAML::Node n;  // default constructed; should be safe to call begin()

  // Observable behavior: begin() should be a "default/empty" iterator and
  // should compare equal to end() for an empty node.
  EXPECT_EQ(n.begin(), n.end());

  // Iteration should produce zero elements.
  std::size_t count = 0;
  for (auto it = n.begin(); it != n.end(); ++it) {
    (void)*it;  // ensure dereference is not accidentally required by the loop body
    ++count;
  }
  EXPECT_EQ(count, 0u);
}

TEST(NodeBeginTest_567, BeginOnScalarIsEmptyRange_567) {
  const YAML::Node n = YAML::Load("hello");  // scalar

  // Scalars are not sequences/maps; iteration should be empty.
  EXPECT_EQ(n.begin(), n.end());
  EXPECT_EQ(std::distance(n.begin(), n.end()), 0);
}

TEST(NodeBeginTest_567, BeginOnEmptySequenceEqualsEnd_567) {
  const YAML::Node n = YAML::Load("[]");  // empty sequence

  EXPECT_TRUE(n.IsSequence());
  EXPECT_EQ(n.size(), 0u);
  EXPECT_EQ(n.begin(), n.end());
  EXPECT_EQ(std::distance(n.begin(), n.end()), 0);
}

TEST(NodeBeginTest_567, BeginOnNonEmptySequenceProvidesIterableRange_567) {
  const YAML::Node n = YAML::Load("[1, 2, 3]");  // non-empty sequence

  EXPECT_TRUE(n.IsSequence());
  ASSERT_EQ(n.size(), 3u);

  // begin() should not equal end() for a non-empty sequence.
  EXPECT_NE(n.begin(), n.end());

  // The iterator range length should match size().
  EXPECT_EQ(static_cast<std::size_t>(std::distance(n.begin(), n.end())), n.size());

  // Iteration should be well-formed and count elements.
  std::size_t count = 0;
  for (auto it = n.begin(); it != n.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, n.size());
}

TEST(NodeBeginTest_567, ConstBeginCompilesAndBehavesSameAsNonConst_567) {
  YAML::Node n = YAML::Load("[10, 20]");
  const YAML::Node& cn = n;

  // Both should be iterable and have the same distance.
  EXPECT_NE(cn.begin(), cn.end());
  EXPECT_EQ(std::distance(cn.begin(), cn.end()), std::distance(n.begin(), n.end()));
  EXPECT_EQ(static_cast<std::size_t>(std::distance(cn.begin(), cn.end())), cn.size());
}

TEST(NodeBeginTest_567, InvalidNodeBeginReturnsEmptyIteratorRange_567) {
  // Create an "invalid" node through observable API behavior: indexing into an
  // undefined node commonly yields an invalid node (Zombie) in yaml-cpp.
  const YAML::Node undefined;          // default constructed (no underlying node)
  const YAML::Node invalid = undefined["missing_key"];

  // We don't assume internal state, only that begin/end are safe and form an empty range.
  EXPECT_EQ(invalid.begin(), invalid.end());

  std::size_t count = 0;
  for (auto it = invalid.begin(); it != invalid.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, 0u);
}

}  // namespace