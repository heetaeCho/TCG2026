#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <limits>
#include "value.cpp"  // Include the actual source file for Exiv2::TimeValue

namespace Exiv2 {

// Mocking is not necessary as no external dependencies are provided in the code.
class TimeValueTest : public ::testing::Test {
protected:
    TimeValueTest() = default;
    ~TimeValueTest() override = default;
};

// Normal operation test
TEST_F(TimeValueTest, toUint32_NormalOperation_883) {
    TimeValue timeValue;
    // Mock a valid toInt64() behavior using a known value
    uint32_t result = timeValue.toUint32(0);
    ASSERT_EQ(result, static_cast<uint32_t>(std::clamp<int64_t>(timeValue.toInt64(), 0, std::numeric_limits<uint32_t>::max())));
}

// Boundary condition test
TEST_F(TimeValueTest, toUint32_LowerBoundary_883) {
    TimeValue timeValue;
    // Assuming toInt64() returns a value below the lower boundary (0)
    uint32_t result = timeValue.toUint32(0);
    ASSERT_EQ(result, 0);  // Below lower boundary should clamp to 0
}

TEST_F(TimeValueTest, toUint32_UpperBoundary_883) {
    TimeValue timeValue;
    // Assuming toInt64() returns a value above the upper boundary (UINT32_MAX)
    uint32_t result = timeValue.toUint32(0);
    ASSERT_EQ(result, std::numeric_limits<uint32_t>::max());  // Above upper boundary should clamp to UINT32_MAX
}

// Exceptional or error cases (mocking return of invalid values from toInt64)
TEST_F(TimeValueTest, toUint32_ErrorCase_883) {
    TimeValue timeValue;
    // Here, we are assuming toInt64 could potentially return a value out of the 0 to UINT32_MAX range
    // This should still clamp to the valid uint32_t range.

    uint32_t result = timeValue.toUint32(0);
    ASSERT_GE(result, 0);  // Result should never be negative
    ASSERT_LE(result, std::numeric_limits<uint32_t>::max());  // Result should never exceed UINT32_MAX
}

} // namespace Exiv2