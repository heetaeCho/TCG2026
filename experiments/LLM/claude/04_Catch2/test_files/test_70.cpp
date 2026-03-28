#include <gtest/gtest.h>
#include "catch2/internal/catch_stream_end_stop.hpp"
#include "catch2/internal/catch_stringref.hpp"

namespace {

TEST(StreamEndStopTest_70, DefaultConstruction_70) {
    Catch::StreamEndStop stop;
    (void)stop; // Should compile and construct without issues
}

TEST(StreamEndStopTest_70, UnaryPlusOperatorReturnsStringRef_70) {
    Catch::StreamEndStop stop;
    Catch::StringRef result = +stop;
    (void)result;
}

TEST(StreamEndStopTest_70, UnaryPlusOperatorReturnsEmptyStringRef_70) {
    Catch::StreamEndStop stop;
    Catch::StringRef result = +stop;
    EXPECT_TRUE(result.empty());
}

TEST(StreamEndStopTest_70, UnaryPlusOperatorReturnsDefaultStringRef_70) {
    Catch::StreamEndStop stop;
    Catch::StringRef result = +stop;
    Catch::StringRef defaultRef;
    EXPECT_EQ(result.size(), defaultRef.size());
}

TEST(StreamEndStopTest_70, ConstexprUsage_70) {
    constexpr Catch::StreamEndStop stop{};
    constexpr Catch::StringRef result = +stop;
    EXPECT_TRUE(result.empty());
}

TEST(StreamEndStopTest_70, MultipleCalls_70) {
    Catch::StreamEndStop stop;
    Catch::StringRef result1 = +stop;
    Catch::StringRef result2 = +stop;
    EXPECT_EQ(result1.size(), result2.size());
    EXPECT_TRUE(result1.empty());
    EXPECT_TRUE(result2.empty());
}

TEST(StreamEndStopTest_70, CopyConstruction_70) {
    Catch::StreamEndStop stop1;
    Catch::StreamEndStop stop2 = stop1;
    Catch::StringRef result1 = +stop1;
    Catch::StringRef result2 = +stop2;
    EXPECT_EQ(result1.size(), result2.size());
}

TEST(StreamEndStopTest_70, ReturnedStringRefSizeIsZero_70) {
    Catch::StreamEndStop stop;
    Catch::StringRef result = +stop;
    EXPECT_EQ(result.size(), 0u);
}

} // namespace
