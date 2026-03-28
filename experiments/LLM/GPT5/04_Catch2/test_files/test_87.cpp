// File: catch_tostring_convert_memberptr_tests.cpp

#include <gtest/gtest.h>

// Include the header under test
#include "Catch2/src/catch2/catch_tostring.hpp"

namespace {

// A simple class to obtain data member pointers
struct Sample {
    int    i{};
    double d{};
};

} // namespace

// TEST_ID: 87
TEST(ConvertMemberPtrTest_87, NullMemberPointer_ReturnsLiteralNullptr_87) {
    int Sample::* pm_int = nullptr;

    const std::string s = Catch::convert(pm_int);

    EXPECT_EQ(s, "nullptr");
}

// TEST_ID: 87
TEST(ConvertMemberPtrTest_87, NonNull_IntMember_ReturnsNonEmptyAndNotNullptr_87) {
    int Sample::* pm_int = &Sample::i;

    const std::string s = Catch::convert(pm_int);

    EXPECT_FALSE(s.empty());
    EXPECT_NE(s, std::string("nullptr"));
}

// TEST_ID: 87
TEST(ConvertMemberPtrTest_87, CallingTwiceWithSamePointer_IsDeterministic_87) {
    double Sample::* pm_double = &Sample::d;

    const std::string s1 = Catch::convert(pm_double);
    const std::string s2 = Catch::convert(pm_double);

    // Do not assert on formatting/content; only that it is stable for the same input
    EXPECT_EQ(s1, s2);
    EXPECT_FALSE(s1.empty());
    EXPECT_NE(s1, std::string("nullptr"));
}
