// TEST_ID: 568
#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include <yaml-cpp/yaml.h>

namespace {

class NodeEndTest_568 : public ::testing::Test {
protected:
  static std::size_t CountByIterating(const YAML::Node& n) {
    std::size_t count = 0;
    for (auto it = n.begin(); it != n.end(); ++it) {
      ++count;
    }
    return count;
  }
};

TEST_F(NodeEndTest_568, DefaultNode_BeginEqualsEndAndSizeZero_568) {
  const YAML::Node n;

  // Boundary/empty container behavior: no elements to iterate.
  EXPECT_EQ(n.size(), 0u);
  EXPECT_TRUE(n.begin() == n.end());

  // Also ensure end() is stable across calls.
  EXPECT_TRUE(n.end() == n.end());
}

TEST_F(NodeEndTest_568, ScalarNode_BeginEqualsEndAndSizeZero_568) {
  const YAML::Node n(std::string("hello"));

  // Scalar nodes should not be iterable as a sequence/map (no elements).
  EXPECT_EQ(n.size(), 0u);
  EXPECT_TRUE(n.begin() == n.end());
}

TEST_F(NodeEndTest_568, SequenceWithElements_EndReachedAfterIteratingSizeSteps_568) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(1);
  seq.push_back(2);
  seq.push_back(3);

  ASSERT_EQ(seq.size(), 3u);

  // Normal operation: end() should be reachable after iterating size() elements.
  std::size_t count = 0;
  auto it = seq.begin();
  for (; it != seq.end(); ++it) {
    ++count;
  }

  EXPECT_EQ(count, seq.size());
  EXPECT_TRUE(it == seq.end());
  EXPECT_FALSE(seq.begin() == seq.end());
}

TEST_F(NodeEndTest_568, MapWithElements_EndReachedAfterIteratingSizeSteps_568) {
  YAML::Node m(YAML::NodeType::Map);
  m.force_insert("a", 1);
  m.force_insert("b", 2);

  ASSERT_EQ(m.size(), 2u);

  // Normal operation: map iteration should terminate at end() and count should match size().
  const std::size_t count = CountByIterating(m);
  EXPECT_EQ(count, m.size());
  EXPECT_FALSE(m.begin() == m.end());
}

TEST_F(NodeEndTest_568, ConstNode_EndIsCallableAndComparable_568) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(42);

  const YAML::Node cseq = seq;

  // Compile-time/const correctness + basic observable behavior.
  auto b = cseq.begin();
  auto e = cseq.end();

  EXPECT_FALSE(b == e);

  // Iterating one element should reach end().
  ++b;
  EXPECT_TRUE(b == e);
}

}  // namespace