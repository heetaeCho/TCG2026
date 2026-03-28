#include <gtest/gtest.h>
#include "yaml-cpp/null.h"

TEST(YamlNullEqualityTest_23, TwoNullObjectsAreEqual_23) {
    YAML::_Null a;
    YAML::_Null b;
    EXPECT_TRUE(a == b);
}

TEST(YamlNullEqualityTest_23, SameNullObjectIsEqualToItself_23) {
    YAML::_Null a;
    EXPECT_TRUE(a == a);
}

TEST(YamlNullEqualityTest_23, NullConstObjectsAreEqual_23) {
    const YAML::_Null a;
    const YAML::_Null b;
    EXPECT_TRUE(a == b);
}

TEST(YamlNullEqualityTest_23, DefaultConstructedNullsAreEqual_23) {
    EXPECT_TRUE(YAML::_Null() == YAML::_Null());
}

TEST(YamlNullEqualityTest_23, GlobalNullSentinelEquality_23) {
    // If YAML::Null is defined as a global _Null instance, test it
    // This tests that the global Null object equals itself and other _Null instances
    YAML::_Null local;
    EXPECT_TRUE(YAML::Null == YAML::Null);
    EXPECT_TRUE(YAML::Null == local);
    EXPECT_TRUE(local == YAML::Null);
}
