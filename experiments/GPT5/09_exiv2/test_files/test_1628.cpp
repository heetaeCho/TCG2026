// File: test_tiffvisitor_int_1628.cpp
#include <gtest/gtest.h>

#include <type_traits>

#include "tiffvisitor_int.hpp"

namespace {

using Exiv2::Internal::GoEvent;
using Exiv2::Internal::TiffVisitor;

class TiffVisitorTest_1628 : public ::testing::Test {
 protected:
  TiffVisitor v;
};

TEST(TiffVisitorTraitsTest_1628, IsNotCopyable_1628) {
  EXPECT_FALSE((std::is_copy_constructible_v<TiffVisitor>));
  EXPECT_FALSE((std::is_copy_assignable_v<TiffVisitor>));
}

TEST_F(TiffVisitorTest_1628, DefaultGoIsTrueForFirstTwoEvents_1628) {
  // The header shows a 2-element initialization {true, true}.
  // We only test the first two event values to avoid out-of-range indexing.
  EXPECT_TRUE(v.go(static_cast<GoEvent>(0)));
  EXPECT_TRUE(v.go(static_cast<GoEvent>(1)));

  const TiffVisitor& cv = v;
  EXPECT_TRUE(cv.go(static_cast<GoEvent>(0)));
  EXPECT_TRUE(cv.go(static_cast<GoEvent>(1)));
}

TEST_F(TiffVisitorTest_1628, SetGoCanDisableAndEnableEvent0_1628) {
  EXPECT_TRUE(v.go(static_cast<GoEvent>(0)));

  v.setGo(static_cast<GoEvent>(0), false);
  EXPECT_FALSE(v.go(static_cast<GoEvent>(0)));

  v.setGo(static_cast<GoEvent>(0), true);
  EXPECT_TRUE(v.go(static_cast<GoEvent>(0)));
}

TEST_F(TiffVisitorTest_1628, SetGoCanDisableAndEnableEvent1_1628) {
  EXPECT_TRUE(v.go(static_cast<GoEvent>(1)));

  v.setGo(static_cast<GoEvent>(1), false);
  EXPECT_FALSE(v.go(static_cast<GoEvent>(1)));

  v.setGo(static_cast<GoEvent>(1), true);
  EXPECT_TRUE(v.go(static_cast<GoEvent>(1)));
}

TEST_F(TiffVisitorTest_1628, SetGoDoesNotAffectOtherEvent_1628) {
  // Start from defaults (expected true/true for first two events).
  EXPECT_TRUE(v.go(static_cast<GoEvent>(0)));
  EXPECT_TRUE(v.go(static_cast<GoEvent>(1)));

  v.setGo(static_cast<GoEvent>(0), false);
  EXPECT_FALSE(v.go(static_cast<GoEvent>(0)));
  EXPECT_TRUE(v.go(static_cast<GoEvent>(1)));  // other event unchanged

  v.setGo(static_cast<GoEvent>(1), false);
  EXPECT_FALSE(v.go(static_cast<GoEvent>(0)));
  EXPECT_FALSE(v.go(static_cast<GoEvent>(1)));

  v.setGo(static_cast<GoEvent>(0), true);
  EXPECT_TRUE(v.go(static_cast<GoEvent>(0)));
  EXPECT_FALSE(v.go(static_cast<GoEvent>(1)));
}

TEST_F(TiffVisitorTest_1628, GoIsCallableOnConstObject_1628) {
  const TiffVisitor& cv = v;

  // Verify both const and non-const overloads (if present) are usable and consistent
  // for the first two events.
  EXPECT_EQ(v.go(static_cast<GoEvent>(0)), cv.go(static_cast<GoEvent>(0)));
  EXPECT_EQ(v.go(static_cast<GoEvent>(1)), cv.go(static_cast<GoEvent>(1)));

  v.setGo(static_cast<GoEvent>(0), false);
  EXPECT_EQ(v.go(static_cast<GoEvent>(0)), cv.go(static_cast<GoEvent>(0)));
}

}  // namespace