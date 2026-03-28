// TEST_ID: 255
#include <gtest/gtest.h>

#include <cstddef>
#include <iterator>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

// Helper: create a default/empty memory holder (works when shared_memory_holder is default-constructible)
static YAML::detail::shared_memory_holder MakeMemory_255() {
  return YAML::detail::shared_memory_holder();
}

static std::size_t CountFromBeginToEnd_255(const node& n) {
  std::size_t count = 0;
  for (auto it = n.begin(); it != n.end(); ++it) {
    ++count;
  }
  return count;
}

}  // namespace

// Verifies that begin() is usable on an empty node and matches end() when size() is zero.
TEST(NodeBeginTest_255, EmptyNodeBeginEqualsEndWhenSizeZero_255) {
  node n;

  const node& cn = n;
  if (cn.size() == 0u) {
    EXPECT_TRUE(cn.begin() == cn.end());
    EXPECT_EQ(0u, CountFromBeginToEnd_255(cn));
  } else {
    // If an empty-constructed node is considered "defined" with non-zero size by implementation,
    // we still require begin/end to be a valid range matching size().
    EXPECT_EQ(cn.size(), CountFromBeginToEnd_255(cn));
  }
}

// Verifies begin() produces an iterable range whose length matches size() after push_back() operations.
// This treats node as a black box: we only compare public size() vs observed iteration length.
TEST(NodeBeginTest_255, BeginIteratesOverAllElementsAfterPushBack_255) {
  node seq;
  seq.set_type(YAML::NodeType::Sequence);

  node child1;
  child1.set_scalar("a");
  node child2;
  child2.set_scalar("b");

  auto mem = MakeMemory_255();
  seq.push_back(child1, mem);
  seq.push_back(child2, mem);

  const node& cseq = seq;
  EXPECT_GE(cseq.size(), 2u);
  EXPECT_EQ(cseq.size(), CountFromBeginToEnd_255(cseq));
  EXPECT_TRUE(cseq.begin() != cseq.end());
}

// Boundary: single element sequence should have begin()!=end() and exactly one increment reaches end().
TEST(NodeBeginTest_255, SingleElementSequenceBeginAdvancesToEnd_255) {
  node seq;
  seq.set_type(YAML::NodeType::Sequence);

  node child;
  child.set_scalar("only");

  auto mem = MakeMemory_255();
  seq.push_back(child, mem);

  const node& cseq = seq;
  ASSERT_EQ(cseq.size(), CountFromBeginToEnd_255(cseq));

  auto it = cseq.begin();
  ASSERT_TRUE(it != cseq.end());
  ++it;
  EXPECT_TRUE(it == cseq.end());
}

// Verifies begin() behavior is consistent after set_ref(): the observable iteration length matches rhs.
TEST(NodeBeginTest_255, BeginRangeMatchesAfterSetRef_255) {
  node rhs;
  rhs.set_type(YAML::NodeType::Sequence);

  node a;
  a.set_scalar("x");
  node b;
  b.set_scalar("y");

  auto mem = MakeMemory_255();
  rhs.push_back(a, mem);
  rhs.push_back(b, mem);

  node lhs;
  lhs.set_ref(rhs);

  const node& crhs = rhs;
  const node& clhs = lhs;

  EXPECT_EQ(crhs.size(), clhs.size());
  EXPECT_EQ(CountFromBeginToEnd_255(crhs), CountFromBeginToEnd_255(clhs));
}

// Verifies begin() behavior is consistent after set_data(): the observable iteration length matches rhs.
TEST(NodeBeginTest_255, BeginRangeMatchesAfterSetData_255) {
  node rhs;
  rhs.set_type(YAML::NodeType::Sequence);

  node a;
  a.set_scalar("p");
  node b;
  b.set_scalar("q");
  node c;
  c.set_scalar("r");

  auto mem = MakeMemory_255();
  rhs.push_back(a, mem);
  rhs.push_back(b, mem);
  rhs.push_back(c, mem);

  node lhs;
  lhs.set_data(rhs);

  const node& crhs = rhs;
  const node& clhs = lhs;

  EXPECT_EQ(crhs.size(), clhs.size());
  EXPECT_EQ(CountFromBeginToEnd_255(crhs), CountFromBeginToEnd_255(clhs));
}

// Basic const-correctness / compilation-level test: begin() is callable on const node.
// (Also validates that begin/end form a valid range without throwing.)
TEST(NodeBeginTest_255, BeginCallableOnConstNode_255) {
  node n;
  const node& cn = n;

  // Just exercise the API; if iteration is possible, ensure it terminates at end().
  auto it = cn.begin();
  auto ed = cn.end();
  // Do not assume empty/non-empty; only assume it is a valid range.
  std::size_t steps = 0;
  for (; it != ed && steps < cn.size() + 2u; ++it) {  // +2 guard in case size()==0
    ++steps;
  }
  EXPECT_TRUE(it == ed);
}