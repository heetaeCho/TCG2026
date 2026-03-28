// File: test_tiffvisitor_setgo_1627.cpp

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

namespace Exiv2::Internal {

class TiffVisitorTest_1627 : public ::testing::Test {};

TEST_F(TiffVisitorTest_1627, DefaultGoFlagsAreTrueForFirstTwoEvents_1627) {
  TiffVisitor v;

  // The interface exposes GoEvent but not its enumerator names here; use the first
  // two ordinal values, consistent with the default initialization shown.
  EXPECT_TRUE(v.go(static_cast<GoEvent>(0)));
  EXPECT_TRUE(v.go(static_cast<GoEvent>(1)));
}

TEST_F(TiffVisitorTest_1627, SetGoDisablesSpecifiedEvent_1627) {
  TiffVisitor v;

  v.setGo(static_cast<GoEvent>(0), false);
  EXPECT_FALSE(v.go(static_cast<GoEvent>(0)));
}

TEST_F(TiffVisitorTest_1627, SetGoDoesNotAffectOtherEvent_1627) {
  TiffVisitor v;

  v.setGo(static_cast<GoEvent>(0), false);

  // Changing event 0 should not change event 1.
  EXPECT_FALSE(v.go(static_cast<GoEvent>(0)));
  EXPECT_TRUE(v.go(static_cast<GoEvent>(1)));
}

TEST_F(TiffVisitorTest_1627, SetGoCanReEnableEventAfterDisable_1627) {
  TiffVisitor v;

  v.setGo(static_cast<GoEvent>(0), false);
  EXPECT_FALSE(v.go(static_cast<GoEvent>(0)));

  v.setGo(static_cast<GoEvent>(0), true);
  EXPECT_TRUE(v.go(static_cast<GoEvent>(0)));
}

TEST_F(TiffVisitorTest_1627, SetGoAllowsIndependentConfigurationOfFirstTwoEvents_1627) {
  TiffVisitor v;

  v.setGo(static_cast<GoEvent>(0), false);
  v.setGo(static_cast<GoEvent>(1), true);

  EXPECT_FALSE(v.go(static_cast<GoEvent>(0)));
  EXPECT_TRUE(v.go(static_cast<GoEvent>(1)));

  v.setGo(static_cast<GoEvent>(1), false);
  EXPECT_FALSE(v.go(static_cast<GoEvent>(1)));
}

}  // namespace Exiv2::Internal