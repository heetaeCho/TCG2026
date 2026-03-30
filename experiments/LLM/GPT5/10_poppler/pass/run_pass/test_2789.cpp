// PSStack_test_2789.cc
#include <gtest/gtest.h>

#include <cmath>
#include <limits>

// NOTE:
// PSStack is implemented in poppler/Function.cc. If there is a corresponding header
// available in your build (e.g., "Function.h"), prefer including that header instead.
// For this unit-test-only context, we include the implementation file to access PSStack.
#include "Function.cc"

namespace {

class PSStackTest_2789 : public ::testing::Test {
protected:
  PSStackTest_2789() = default;
  ~PSStackTest_2789() override = default;
};

TEST_F(PSStackTest_2789, ConstructorStartsEmpty_2789) {
  PSStack s;
  EXPECT_TRUE(s.empty());
}

TEST_F(PSStackTest_2789, PushPopIntRoundTrip_2789) {
  PSStack s;

  s.pushInt(42);
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.topIsInt());

  int v = s.popInt();
  EXPECT_EQ(v, 42);
  EXPECT_TRUE(s.empty());
}

TEST_F(PSStackTest_2789, PushPopBoolRoundTrip_2789) {
  PSStack s;

  s.pushBool(true);
  EXPECT_FALSE(s.empty());

  bool v = s.popBool();
  EXPECT_TRUE(v);
  EXPECT_TRUE(s.empty());

  s.pushBool(false);
  EXPECT_FALSE(s.empty());

  v = s.popBool();
  EXPECT_FALSE(v);
  EXPECT_TRUE(s.empty());
}

TEST_F(PSStackTest_2789, PushPopRealRoundTrip_2789) {
  PSStack s;

  const double kVal = 3.141592653589793;
  s.pushReal(kVal);

  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.topIsReal());

  const double out = s.popNum();
  EXPECT_NEAR(out, kVal, 1e-12);
  EXPECT_TRUE(s.empty());
}

TEST_F(PSStackTest_2789, TypePredicatesReflectTopAndTopTwo_2789) {
  PSStack s;

  // With one int on stack.
  s.pushInt(7);
  EXPECT_TRUE(s.topIsInt());
  EXPECT_FALSE(s.topIsReal());
  EXPECT_FALSE(s.topTwoAreInts());
  EXPECT_FALSE(s.topTwoAreNums());

  // With two ints on stack.
  s.pushInt(8);
  EXPECT_TRUE(s.topIsInt());
  EXPECT_TRUE(s.topTwoAreInts());
  EXPECT_TRUE(s.topTwoAreNums());
  EXPECT_FALSE(s.topIsReal());

  // Replace top with real; top two should still be numbers, but not both ints.
  s.pop();
  s.pushReal(2.5);
  EXPECT_TRUE(s.topIsReal());
  EXPECT_FALSE(s.topIsInt());
  EXPECT_FALSE(s.topTwoAreInts());
  EXPECT_TRUE(s.topTwoAreNums());
}

TEST_F(PSStackTest_2789, ClearEmptiesStack_2789) {
  PSStack s;

  s.pushInt(1);
  s.pushBool(false);
  s.pushReal(0.25);
  EXPECT_FALSE(s.empty());

  s.clear();
  EXPECT_TRUE(s.empty());

  // Clear should be safe to call repeatedly.
  s.clear();
  EXPECT_TRUE(s.empty());
}

TEST_F(PSStackTest_2789, CopyWithZeroIsNoOp_2789) {
  PSStack s;

  s.pushInt(10);
  s.pushInt(20);

  // Boundary: n = 0 should not change observable content.
  s.copy(0);

  EXPECT_TRUE(s.topIsInt());
  EXPECT_EQ(s.popInt(), 20);
  EXPECT_EQ(s.popInt(), 10);
  EXPECT_TRUE(s.empty());
}

TEST_F(PSStackTest_2789, RollWithZeroIsNoOp_2789) {
  PSStack s;

  s.pushInt(1);
  s.pushInt(2);
  s.pushInt(3);

  // Boundary: j = 0 should not change observable order.
  s.roll(3, 0);

  EXPECT_EQ(s.popInt(), 3);
  EXPECT_EQ(s.popInt(), 2);
  EXPECT_EQ(s.popInt(), 1);
  EXPECT_TRUE(s.empty());
}

TEST_F(PSStackTest_2789, CapacityBoundaryPushExactlyPsStackSizeThenPopAll_2789) {
  PSStack s;

  // Push exactly psStackSize items (boundary).
  for (int i = 0; i < psStackSize; ++i) {
    s.pushInt(i);
  }
  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(s.topIsInt());

  // Pop all and validate LIFO for the values we pushed.
  for (int i = psStackSize - 1; i >= 0; --i) {
    EXPECT_TRUE(s.topIsInt());
    EXPECT_EQ(s.popInt(), i);
  }
  EXPECT_TRUE(s.empty());
}

} // namespace