#include <gtest/gtest.h>
#include "yaml-cpp/null.h"

// Test that two _Null objects compared with != return false
TEST(NullOperatorTest_24, NotEqualReturnsFalse_24) {
    YAML::_Null a;
    YAML::_Null b;
    EXPECT_FALSE(a != b);
}

// Test that a _Null object compared with itself returns false
TEST(NullOperatorTest_24, NotEqualSameObjectReturnsFalse_24) {
    YAML::_Null a;
    EXPECT_FALSE(a != a);
}

// Test using the global Null constant if available
TEST(NullOperatorTest_24, GlobalNullNotEqualReturnsFalse_24) {
    YAML::_Null n1;
    YAML::_Null n2;
    bool result = (n1 != n2);
    EXPECT_EQ(result, false);
}

// Test that the result type is bool
TEST(NullOperatorTest_24, ResultTypeIsBool_24) {
    YAML::_Null a;
    YAML::_Null b;
    auto result = (a != b);
    static_assert(std::is_same<decltype(result), bool>::value, "Result should be bool");
    EXPECT_FALSE(result);
}

// Test repeated comparisons yield consistent results
TEST(NullOperatorTest_24, RepeatedComparisonConsistent_24) {
    YAML::_Null a;
    YAML::_Null b;
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(a != b);
    }
}

// Test with const _Null objects
TEST(NullOperatorTest_24, ConstNullObjectsNotEqual_24) {
    const YAML::_Null a;
    const YAML::_Null b;
    EXPECT_FALSE(a != b);
}

// Test that temporary _Null objects also compare correctly
TEST(NullOperatorTest_24, TemporaryNullObjectsNotEqual_24) {
    EXPECT_FALSE(YAML::_Null() != YAML::_Null());
}
