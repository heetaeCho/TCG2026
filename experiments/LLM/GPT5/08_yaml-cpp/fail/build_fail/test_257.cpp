// TEST_ID: 257
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

// Helper: build a scalar node with given value.
static node MakeScalar(const std::string& s) {
  node n;
  n.set_type(YAML::NodeType::Scalar);
  n.set_scalar(s);
  return n;
}

class NodePushBackTest_257 : public ::testing::Test {
 protected:
  // Many yaml-cpp internals accept a shared_memory_holder; a default-constructed
  // holder (null) is a valid, observable-case input for black-box testing.
  YAML::detail::shared_memory_holder mem_;
};

TEST_F(NodePushBackTest_257, PushBackToEmptySequenceIncreasesSize_257) {
  node parent;
  parent.set_type(YAML::NodeType::Sequence);

  node child;
  child.set_type(YAML::NodeType::Scalar);
  child.set_scalar("a");

  const std::size_t before = parent.size();
  EXPECT_NO_THROW(parent.push_back(child, mem_));
  EXPECT_EQ(parent.size(), before + 1);

  auto it = parent.begin();
  ASSERT_NE(it, parent.end());
  EXPECT_TRUE(it->equals("a", mem_));
}

TEST_F(NodePushBackTest_257, PushBackMultipleElementsPreservesIterationOrder_257) {
  node parent;
  parent.set_type(YAML::NodeType::Sequence);

  node a;
  a.set_type(YAML::NodeType::Scalar);
  a.set_scalar("a");
  node b;
  b.set_type(YAML::NodeType::Scalar);
  b.set_scalar("b");
  node c;
  c.set_type(YAML::NodeType::Scalar);
  c.set_scalar("c");

  EXPECT_NO_THROW(parent.push_back(a, mem_));
  EXPECT_NO_THROW(parent.push_back(b, mem_));
  EXPECT_NO_THROW(parent.push_back(c, mem_));

  EXPECT_EQ(parent.size(), 3u);

  auto it = parent.begin();
  ASSERT_NE(it, parent.end());
  EXPECT_TRUE(it->equals("a", mem_));
  ++it;

  ASSERT_NE(it, parent.end());
  EXPECT_TRUE(it->equals("b", mem_));
  ++it;

  ASSERT_NE(it, parent.end());
  EXPECT_TRUE(it->equals("c", mem_));
  ++it;

  EXPECT_EQ(it, parent.end());
}

TEST_F(NodePushBackTest_257, PushBackUndefinedNodeIsObservableViaIterator_257) {
  node parent;
  parent.set_type(YAML::NodeType::Sequence);

  node undef_child;  // default-constructed; defined-ness is observable via is_defined()

  EXPECT_NO_THROW(parent.push_back(undef_child, mem_));
  EXPECT_EQ(parent.size(), 1u);

  auto it = parent.begin();
  ASSERT_NE(it, parent.end());
  EXPECT_FALSE(it->is_defined());
}

TEST_F(NodePushBackTest_257, PushBackWithNullMemoryHolderDoesNotThrow_257) {
  node parent;
  parent.set_type(YAML::NodeType::Sequence);

  node child;
  child.set_type(YAML::NodeType::Scalar);
  child.set_scalar("x");

  YAML::detail::shared_memory_holder null_mem;  // explicitly null
  EXPECT_NO_THROW(parent.push_back(child, null_mem));
  EXPECT_EQ(parent.size(), 1u);

  auto it = parent.begin();
  ASSERT_NE(it, parent.end());
  EXPECT_TRUE(it->equals("x", null_mem));
}

TEST_F(NodePushBackTest_257, PushBackRepeatedCallsMonotonicallyIncreaseSize_257) {
  node parent;
  parent.set_type(YAML::NodeType::Sequence);

  node one;
  one.set_type(YAML::NodeType::Scalar);
  one.set_scalar("1");
  node two;
  two.set_type(YAML::NodeType::Scalar);
  two.set_scalar("2");

  EXPECT_EQ(parent.size(), 0u);

  EXPECT_NO_THROW(parent.push_back(one, mem_));
  const std::size_t after_one = parent.size();
  EXPECT_EQ(after_one, 1u);

  EXPECT_NO_THROW(parent.push_back(two, mem_));
  const std::size_t after_two = parent.size();
  EXPECT_EQ(after_two, 2u);

  // Boundary-ish: ensure begin/end reflect non-empty container.
  EXPECT_NE(parent.begin(), parent.end());
}

}  // namespace