// TEST_ID: 490
#include <gtest/gtest.h>

#include <limits>
#include <memory>

#include "poppler/GfxState.h"

class GfxPatternTest_490 : public ::testing::Test {};

// Normal operation: constructor-provided type is observable via getType().
TEST_F(GfxPatternTest_490, GetTypeReturnsConstructorType_490) {
  const int type = 3;
  const int refNum = 42;

  GfxPattern p(type, refNum);

  EXPECT_EQ(p.getType(), type);
}

// Normal operation: constructor-provided patternRefNum is observable via getPatternRefNum().
TEST_F(GfxPatternTest_490, GetPatternRefNumReturnsConstructorRefNum_490) {
  const int type = 1;
  const int refNum = 99;

  GfxPattern p(type, refNum);

  EXPECT_EQ(p.getPatternRefNum(), refNum);
}

// Boundary: zero values.
TEST_F(GfxPatternTest_490, GettersHandleZeroValues_490) {
  GfxPattern p(0, 0);

  EXPECT_EQ(p.getType(), 0);
  EXPECT_EQ(p.getPatternRefNum(), 0);
}

// Boundary: negative values (if allowed by interface, should be returned unchanged).
TEST_F(GfxPatternTest_490, GettersHandleNegativeValues_490) {
  GfxPattern p(-7, -123);

  EXPECT_EQ(p.getType(), -7);
  EXPECT_EQ(p.getPatternRefNum(), -123);
}

// Boundary: extreme integer values.
TEST_F(GfxPatternTest_490, GettersHandleIntLimits_490) {
  const int minI = (std::numeric_limits<int>::min)();
  const int maxI = (std::numeric_limits<int>::max)();

  GfxPattern p(minI, maxI);

  EXPECT_EQ(p.getType(), minI);
  EXPECT_EQ(p.getPatternRefNum(), maxI);
}

// Observable behavior: copy() returns a (smart) pointer to a pattern that can be queried.
// This test does NOT assume deep-copy internals beyond what is observable: non-null result,
// same observable getter values, and (when possible) a different object address.
TEST_F(GfxPatternTest_490, CopyProducesQueryablePatternWithSameObservableValues_490) {
  const int type = 5;
  const int refNum = 17;

  GfxPattern p(type, refNum);

  // Signature in header is "virtual const std::unique_ptr<GfxPattern> copy();"
  // Treat as black box: just use the returned pointer.
  const std::unique_ptr<GfxPattern> cp = p.copy();

  ASSERT_TRUE(cp != nullptr);
  EXPECT_EQ(cp->getType(), p.getType());
  EXPECT_EQ(cp->getPatternRefNum(), p.getPatternRefNum());

  // If a new object is produced, addresses should differ. If implementation returns a
  // pointer to a shared singleton (unlikely) this will catch it, but still only relies on
  // observable pointer identity.
  EXPECT_NE(cp.get(), &p);
}

// Exceptional / robustness (observable): deleting through base pointer should be safe due to
// virtual destructor. This is a safety/ABI-style test; it passes if no crash/UB is triggered.
TEST_F(GfxPatternTest_490, VirtualDestructorAllowsDeletionThroughBasePointer_490) {
  std::unique_ptr<GfxPattern> p = std::make_unique<GfxPattern>(2, 10);
  ASSERT_TRUE(p != nullptr);
  // Implicitly verifies no crash on destruction at scope exit.
}