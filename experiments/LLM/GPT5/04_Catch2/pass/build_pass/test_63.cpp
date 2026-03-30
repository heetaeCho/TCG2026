// isFalseTest_tests_63.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_result_type.hpp"

// Verify constexpr usability (part of the interface)
static_assert(Catch::isFalseTest(Catch::ResultDisposition::FalseTest),
              "isFalseTest should be usable in constant expressions");
static_assert(Catch::isFalseTest(Catch::ResultDisposition::Normal |
                                 Catch::ResultDisposition::FalseTest),
              "isFalseTest should evaluate true when FalseTest bit is set");

TEST(IsFalseTest_63, NoFlags_ReturnsFalse_63) {
    const int flags = 0;
    EXPECT_FALSE(Catch::isFalseTest(flags));
}

TEST(IsFalseTest_63, OnlyFalseTestFlag_ReturnsTrue_63) {
    const int flags = Catch::ResultDisposition::FalseTest;
    EXPECT_TRUE(Catch::isFalseTest(flags));
}

TEST(IsFalseTest_63, FalseTestWithNormal_ReturnsTrue_63) {
    const int flags = Catch::ResultDisposition::Normal |
                      Catch::ResultDisposition::FalseTest;
    EXPECT_TRUE(Catch::isFalseTest(flags));
}

TEST(IsFalseTest_63, FalseTestWithMultipleOtherFlags_ReturnsTrue_63) {
    const int flags = Catch::ResultDisposition::ContinueOnFailure |
                      Catch::ResultDisposition::SuppressFail |
                      Catch::ResultDisposition::FalseTest;
    EXPECT_TRUE(Catch::isFalseTest(flags));
}

TEST(IsFalseTest_63, OtherFlagsWithoutFalseTest_ReturnsFalse_63) {
    const int flags = Catch::ResultDisposition::Normal |
                      Catch::ResultDisposition::ContinueOnFailure |
                      Catch::ResultDisposition::SuppressFail;
    EXPECT_FALSE(Catch::isFalseTest(flags));
}

TEST(IsFalseTest_63, IdempotentForSameInput_63) {
    const int flags = Catch::ResultDisposition::FalseTest |
                      Catch::ResultDisposition::SuppressFail;
    // Calling multiple times should yield the same observable result
    const bool first  = Catch::isFalseTest(flags);
    const bool second = Catch::isFalseTest(flags);
    EXPECT_EQ(first, second);
    EXPECT_TRUE(first);
}
