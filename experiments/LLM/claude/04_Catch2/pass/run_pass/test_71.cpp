#include <gtest/gtest.h>
#include "catch2/internal/catch_stream_end_stop.hpp"

// Test fixture for StreamEndStop tests
class StreamEndStopTest_71 : public ::testing::Test {
protected:
    Catch::StreamEndStop endStop;
};

// Test that operator+ with an int returns the original value
TEST_F(StreamEndStopTest_71, IntValueReturnedUnchanged_71) {
    int value = 42;
    const int& result = value + endStop;
    EXPECT_EQ(result, 42);
}

// Test that operator+ with a double returns the original value
TEST_F(StreamEndStopTest_71, DoubleValueReturnedUnchanged_71) {
    double value = 3.14;
    const double& result = value + endStop;
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test that operator+ with a string returns the original value
TEST_F(StreamEndStopTest_71, StringValueReturnedUnchanged_71) {
    std::string value = "hello";
    const std::string& result = value + endStop;
    EXPECT_EQ(result, "hello");
}

// Test that operator+ returns a reference to the same object
TEST_F(StreamEndStopTest_71, ReturnsReferenceToSameObject_71) {
    int value = 100;
    const int& result = value + endStop;
    EXPECT_EQ(&result, &value);
}

// Test with zero value
TEST_F(StreamEndStopTest_71, ZeroIntValueReturnedUnchanged_71) {
    int value = 0;
    const int& result = value + endStop;
    EXPECT_EQ(result, 0);
}

// Test with negative value
TEST_F(StreamEndStopTest_71, NegativeIntValueReturnedUnchanged_71) {
    int value = -99;
    const int& result = value + endStop;
    EXPECT_EQ(result, -99);
}

// Test with empty string
TEST_F(StreamEndStopTest_71, EmptyStringReturnedUnchanged_71) {
    std::string value = "";
    const std::string& result = value + endStop;
    EXPECT_EQ(result, "");
    EXPECT_EQ(&result, &value);
}

// Test with boolean value
TEST_F(StreamEndStopTest_71, BoolValueReturnedUnchanged_71) {
    bool value = true;
    const bool& result = value + endStop;
    EXPECT_EQ(result, true);
}

// Test with const char* (pointer type)
TEST_F(StreamEndStopTest_71, ConstCharPtrReturnedUnchanged_71) {
    const char* value = "test string";
    const auto& result = value + Catch::StreamEndStop{};
    EXPECT_STREQ(result, "test string");
    EXPECT_EQ(&result, &value);
}

// Test with a large value
TEST_F(StreamEndStopTest_71, LargeIntValueReturnedUnchanged_71) {
    long long value = 9223372036854775807LL;
    const long long& result = value + endStop;
    EXPECT_EQ(result, 9223372036854775807LL);
}

// Test with float boundary value
TEST_F(StreamEndStopTest_71, FloatMaxReturnedUnchanged_71) {
    float value = std::numeric_limits<float>::max();
    const float& result = value + endStop;
    EXPECT_FLOAT_EQ(result, std::numeric_limits<float>::max());
}

// Test that StreamEndStop can be default constructed
TEST_F(StreamEndStopTest_71, DefaultConstructible_71) {
    Catch::StreamEndStop s;
    (void)s;  // Should compile and not cause issues
    SUCCEED();
}

// Test with a custom struct
TEST_F(StreamEndStopTest_71, CustomStructReturnedUnchanged_71) {
    struct MyStruct {
        int x;
        double y;
    };
    MyStruct value{10, 20.5};
    const MyStruct& result = value + endStop;
    EXPECT_EQ(result.x, 10);
    EXPECT_DOUBLE_EQ(result.y, 20.5);
    EXPECT_EQ(&result, &value);
}

// Test with temporary StreamEndStop
TEST_F(StreamEndStopTest_71, WorksWithTemporaryStreamEndStop_71) {
    int value = 55;
    const int& result = value + Catch::StreamEndStop{};
    EXPECT_EQ(result, 55);
    EXPECT_EQ(&result, &value);
}
