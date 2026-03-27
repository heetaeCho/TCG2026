// TEST_ID: 235
#include <gtest/gtest.h>

#include <set>
#include <vector>

#include "yaml-cpp/node/detail/node.h"

namespace {

using Node = YAML::detail::node;
using Less = Node::less;

TEST(NodeLessTest_235, IrreflexiveForSameObject_235) {
  Node a;
  Less less;

  // Strict ordering should never say an element is less than itself.
  EXPECT_FALSE(less(&a, &a));
}

TEST(NodeLessTest_235, AntisymmetricForTwoDistinctObjects_235) {
  Node a;
  Node b;
  Less less;

  const bool ab = less(&a, &b);
  const bool ba = less(&b, &a);

  // A strict comparator must not report both directions as "less".
  EXPECT_FALSE(ab && ba);

  // Also verify repeatability (pure comparator behavior for same inputs).
  EXPECT_EQ(ab, less(&a, &b));
  EXPECT_EQ(ba, less(&b, &a));
}

TEST(NodeLessTest_235, UsableAsStdSetComparatorAndProducesSortedIteration_235) {
  Node a;
  Node b;
  Node c;
  Less less;

  std::set<const Node*, Less> s(less);

  // Insert node pointers; set should be able to order them without crashing.
  s.insert(&a);
  s.insert(&b);
  s.insert(&c);

  // The set may deduplicate if two nodes compare equivalent, so size is [1, 3].
  ASSERT_GE(s.size(), 1u);
  ASSERT_LE(s.size(), 3u);

  // Verify the iteration order is consistent with the comparator.
  // For any consecutive elements x then y, y must not be "less than" x.
  for (auto it = s.begin(); it != s.end(); ++it) {
    auto next = std::next(it);
    if (next == s.end()) break;
    const Node* x = *it;
    const Node* y = *next;

    EXPECT_FALSE(less(y, x));

    // If x != y (always true in a set), then either x<y or they are equivalent.
    // But std::set should not contain equivalent distinct keys, so x<y should hold.
    EXPECT_TRUE(less(x, y));
  }
}

}  // namespace