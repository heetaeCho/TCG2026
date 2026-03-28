// TEST_ID: 23
//
// Unit tests for yaml-cpp/null.h (operator== for YAML::_Null)
//
// Notes:
// - We treat the implementation as a black box.
// - Observable behavior: equality comparison result.
// - We avoid relying on any private state.
// - We only use the public interface as exposed by including yaml-cpp headers.

#include <gtest/gtest.h>

#include <yaml-cpp/null.h>

namespace {

TEST(NullEqualityTest_23, SameObjectIsEqual_23) {
  YAML::_Null n;
  EXPECT_TRUE(n == n);
}

TEST(NullEqualityTest_23, TwoDistinctNullObjectsAreEqual_23) {
  YAML::_Null a;
  YAML::_Null b;
  EXPECT_TRUE(a == b);
}

TEST(NullEqualityTest_23, EqualityIsSymmetric_23) {
  YAML::_Null a;
  YAML::_Null b;
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
}

TEST(NullEqualityTest_23, EqualityIsReflexiveForConstRefs_23) {
  const YAML::_Null a{};
  const YAML::_Null& ra = a;
  EXPECT_TRUE(ra == ra);
}

TEST(NullEqualityTest_23, EqualityWorksWithTemporaries_23) {
  EXPECT_TRUE(YAML::_Null{} == YAML::_Null{});
}

TEST(NullEqualityTest_23, EqualityIsConsistentAcrossRepeatedCalls_23) {
  YAML::_Null a;
  YAML::_Null b;

  // Repeated checks should be consistent (no observable statefulness).
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(a == b);
}

}  // namespace
