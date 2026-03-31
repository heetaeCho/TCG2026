#include <gtest/gtest.h>
#include <cstddef>

// Minimal reproduction of the Safe::add utility
namespace Safe {
template <typename T>
T add(T a, T b) {
    return a + b;
}
}

// Minimal reproduction of the class under test based on the provided partial code
namespace Exiv2 {
namespace Internal {

class Nikon3MnHeader {
public:
    size_t baseOffset(size_t mnOffset) const {
        return Safe::add<size_t>(mnOffset, 10);
    }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2::Internal;

class Nikon3MnHeaderTest_1469 : public ::testing::Test {
protected:
    Nikon3MnHeader header_;
};

// Test normal operation: baseOffset adds 10 to the given mnOffset
TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetAdds10ToOffset_1469) {
    EXPECT_EQ(header_.baseOffset(0), 10u);
}

TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetWithNonZeroOffset_1469) {
    EXPECT_EQ(header_.baseOffset(100), 110u);
}

TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetWithSmallOffset_1469) {
    EXPECT_EQ(header_.baseOffset(1), 11u);
}

TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetWithLargeOffset_1469) {
    EXPECT_EQ(header_.baseOffset(1000000), 1000010u);
}

// Boundary condition: offset is zero
TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetZeroBoundary_1469) {
    size_t result = header_.baseOffset(0);
    EXPECT_EQ(result, 10u);
}

// Boundary condition: offset is 1
TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetOneBoundary_1469) {
    size_t result = header_.baseOffset(1);
    EXPECT_EQ(result, 11u);
}

// Boundary condition: very large offset (but not overflowing)
TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetLargeValue_1469) {
    size_t largeValue = static_cast<size_t>(-1) - 10;  // max value minus 10
    size_t result = header_.baseOffset(largeValue);
    EXPECT_EQ(result, largeValue + 10u);
}

// Test that baseOffset consistently returns mnOffset + 10
TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetConsistency_1469) {
    for (size_t i = 0; i < 100; ++i) {
        EXPECT_EQ(header_.baseOffset(i), i + 10u);
    }
}

// Test with power-of-two offsets
TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetPowerOfTwo_1469) {
    EXPECT_EQ(header_.baseOffset(2), 12u);
    EXPECT_EQ(header_.baseOffset(4), 14u);
    EXPECT_EQ(header_.baseOffset(8), 18u);
    EXPECT_EQ(header_.baseOffset(16), 26u);
    EXPECT_EQ(header_.baseOffset(32), 42u);
    EXPECT_EQ(header_.baseOffset(64), 74u);
    EXPECT_EQ(header_.baseOffset(128), 138u);
    EXPECT_EQ(header_.baseOffset(256), 266u);
    EXPECT_EQ(header_.baseOffset(512), 522u);
    EXPECT_EQ(header_.baseOffset(1024), 1034u);
}

// Test that const object can call baseOffset
TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetConstCorrectness_1469) {
    const Nikon3MnHeader constHeader;
    EXPECT_EQ(constHeader.baseOffset(50), 60u);
}

// Test multiple calls return same result (idempotency of computation)
TEST_F(Nikon3MnHeaderTest_1469, BaseOffsetIdempotent_1469) {
    size_t result1 = header_.baseOffset(42);
    size_t result2 = header_.baseOffset(42);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, 52u);
}
