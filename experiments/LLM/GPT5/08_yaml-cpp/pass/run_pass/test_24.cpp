// TEST_ID: 24
//
// File: test/null_operator_neq_test.cpp
#include <gtest/gtest.h>

#include "yaml-cpp/null.h"  // Provides YAML::_Null and operator!=

namespace {

// These tests treat operator!= as a pure black box with only observable behavior.
// We only verify what can be observed: the returned boolean.

TEST(NullOperatorNotEqualTest_24, SameObjectIsNotNotEqual_24) {
  YAML::_Null n;
  EXPECT_FALSE(n != n);
}

TEST(NullOperatorNotEqualTest_24, TwoDistinctNullObjectsAreNotNotEqual_24) {
  YAML::_Null a;
  YAML::_Null b;
  EXPECT_FALSE(a != b);
}

TEST(NullOperatorNotEqualTest_24, ConstNullObjectsAreNotNotEqual_24) {
  const YAML::_Null a{};
  const YAML::_Null b{};
  EXPECT_FALSE(a != b);
}

TEST(NullOperatorNotEqualTest_24, WorksWithTemporaries_24) {
  EXPECT_FALSE(YAML::_Null{} != YAML::_Null{});
}

TEST(NullOperatorNotEqualTest_24, NoThrowGuaranteeIsObservable_24) {
  YAML::_Null a;
  YAML::_Null b;
  EXPECT_NO_THROW({
    (void)(a != b);
  });
}

}  // namespace
