// File: within_abs_factory_test_205.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Public Catch2 matcher headers (interface only)
#include "catch2/matchers/catch_matchers_floating_point.hpp"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinAbsMatcher;

namespace {

// ---------- Type & construction ----------

TEST(WithinAbsFactory_205, ReturnsMatcherType_205) {
  // Verify the factory returns the expected public matcher type.
  static_assert(std::is_same<decltype(WithinAbs(0.0, 1.0)), WithinAbsMatcher>::value,
                "WithinAbs must return WithinAbsMatcher");
  SUCCEED();
}

TEST(WithinAbsFactory_205, FactoryAndDirectConstructionBehaveTheSame_205) {
  // Compare observable behavior between factory-created and directly-constructed matcher.
  auto viaFactory = WithinAbs(2.0, 0.5);
  WithinAbsMatcher direct{2.0, 0.5};

  EXPECT_EQ(viaFactory.match(2.0), direct.match(2.0));
  EXPECT_EQ(viaFactory.match(1.6), direct.match(1.6));
  EXPECT_EQ(viaFactory.match(2.6), direct.match(2.6));
  EXPECT_EQ(viaFactory.describe(), direct.describe());
}

// ---------- Matching behavior (black-box) ----------

TEST(WithinAbsFactory_205, ExactMatchWithZeroMargin_205) {
  auto m = WithinAbs(3.5, 0.0);
  EXPECT_TRUE(m.match(3.5));         // exact target must match
  EXPECT_FALSE(m.match(3.5000001));  // any deviation should fail when margin is zero
}

TEST(WithinAbsFactory_205, MatchesInsidePositiveMargin_205) {
  auto m = WithinAbs(10.0, 0.25);
  EXPECT_TRUE(m.match(9.8));   // 0.2 away
  EXPECT_TRUE(m.match(10.24)); // 0.24 away
  EXPECT_FALSE(m.match(10.26)); // 0.26 away (outside)
}

TEST(WithinAbsFactory_205, MatchesOnBoundary_205) {
  auto m = WithinAbs(10.0, 0.25);
  EXPECT_TRUE(m.match(9.75));  // exactly target - margin
  EXPECT_TRUE(m.match(10.25)); // exactly target + margin
}

// ---------- Description (human-readable) ----------

TEST(WithinAbsFactory_205, DescriptionMentionsTargetAndMargin_205) {
  auto m = WithinAbs(1.25, 0.75);
  std::string desc = m.describe();

  // Don’t depend on exact wording; verify the observable presence of parameters.
  EXPECT_NE(desc.find("1.25"), std::string::npos);
  EXPECT_NE(desc.find("0.75"), std::string::npos);
  EXPECT_FALSE(desc.empty());
}

} // namespace
