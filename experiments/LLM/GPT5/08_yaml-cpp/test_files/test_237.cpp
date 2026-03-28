// TEST_ID: 237
// File: test/node/detail/node_ref_test_237.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace YAML {
namespace detail {

class NodeRefTest_237 : public ::testing::Test {
protected:
  node MakeNode() { return node(); }
};

TEST_F(NodeRefTest_237, RefStableAcrossCalls_237) {
  node n;
  const node_ref* p1 = n.ref();
  const node_ref* p2 = n.ref();
  EXPECT_EQ(p1, p2);
}

TEST_F(NodeRefTest_237, RefCallableOnConstNode_237) {
  const node n;
  const node_ref* p1 = n.ref();
  const node_ref* p2 = n.ref();
  EXPECT_EQ(p1, p2);
}

TEST_F(NodeRefTest_237, SetRefMakesRefsMatch_237) {
  node a;
  node b;

  const node_ref* before_a = a.ref();
  const node_ref* before_b = b.ref();

  // Exercise
  a.set_ref(b);

  // Observable behavior through the public interface:
  // a should now refer to the same ref as b.
  EXPECT_EQ(a.ref(), before_b);

  // b's ref pointer should remain stable across calls.
  EXPECT_EQ(b.ref(), before_b);

  // And a's ref should reflect a change if it previously differed.
  // (If they were already equal, this still holds.)
  EXPECT_EQ(a.ref(), b.ref());
  (void)before_a;  // avoid unused warnings in builds where it's not referenced
}

TEST_F(NodeRefTest_237, SetRefWithSelfKeepsRefStable_237) {
  node a;
  const node_ref* before = a.ref();

  // Exercise
  a.set_ref(a);

  // Ref should remain stable/consistent.
  EXPECT_EQ(a.ref(), before);
  EXPECT_EQ(a.ref(), a.ref());
}

TEST_F(NodeRefTest_237, RefRemainsCallableAfterOtherOperations_237) {
  node a;
  node b;

  const node_ref* before_a = a.ref();

  // Perform a few public operations that should not make calling ref() invalid.
  a.add_dependency(b);
  a.set_data(b);
  a.set_mark(a.mark());  // round-trip: use observable mark() to set_mark()

  // ref() should still be callable and stable across calls.
  const node_ref* after_a_1 = a.ref();
  const node_ref* after_a_2 = a.ref();
  EXPECT_EQ(after_a_1, after_a_2);

  // We do not assume whether these operations change the ref pointer;
  // but we can still verify ref() remains consistent and usable.
  (void)before_a;
}

}  // namespace detail
}  // namespace YAML