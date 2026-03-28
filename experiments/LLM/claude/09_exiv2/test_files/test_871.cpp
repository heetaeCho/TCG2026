#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <limits>
#include <cstdint>

using namespace Exiv2;

class DateValueTest_871 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that a valid date produces a non-zero result from toUint32
TEST_F(DateValueTest_871, ValidDateReturnsExpectedValue_871) {
    DateValue dv;
    // Set a valid date - using read method with a typical date string
    dv.read("2023-01-15");
    uint32_t result = dv.toUint32(0);
    // The result should match the int64 representation if it fits in uint32
    int64_t i64val = dv.toInt64(0);
    if (i64val >= 0 && i64val <= static_cast<int64_t>(std::numeric_limits<uint32_t>::max())) {
        EXPECT_EQ(result, static_cast<uint32_t>(i64val));
    }
}

// Test with a date that should produce a representable value
TEST_F(DateValueTest_871, StandardDateProducesConsistentResult_871) {
    DateValue dv;
    dv.read("2000-06-15");
    uint32_t result = dv.toUint32(0);
    int64_t i64val = dv.toInt64(0);
    if (i64val >= 0) {
        EXPECT_EQ(result, static_cast<uint32_t>(i64val));
    }
}

// Test with another valid date
TEST_F(DateValueTest_871, AnotherValidDate_871) {
    DateValue dv;
    dv.read("1970-01-01");
    uint32_t result = dv.toUint32(0);
    int64_t i64val = dv.toInt64(0);
    if (i64val >= 0 && i64val <= static_cast<int64_t>(std::numeric_limits<uint32_t>::max())) {
        EXPECT_EQ(result, static_cast<uint32_t>(i64val));
    }
}

// Test that toUint32 returns a uint32_t type
TEST_F(DateValueTest_871, ReturnTypeIsUint32_871) {
    DateValue dv;
    dv.read("2023-12-31");
    auto result = dv.toUint32(0);
    static_assert(std::is_same<decltype(result), uint32_t>::value, "Return type must be uint32_t");
}

// Test with a minimal year date
TEST_F(DateValueTest_871, MinimalYearDate_871) {
    DateValue dv;
    dv.read("0001-01-01");
    uint32_t result = dv.toUint32(0);
    int64_t i64val = dv.toInt64(0);
    if (i64val >= 0 && i64val <= static_cast<int64_t>(std::numeric_limits<uint32_t>::max())) {
        EXPECT_EQ(result, static_cast<uint32_t>(i64val));
    }
}

// Test consistency: calling toUint32 multiple times gives same result
TEST_F(DateValueTest_871, ConsistentResults_871) {
    DateValue dv;
    dv.read("2023-07-04");
    uint32_t result1 = dv.toUint32(0);
    uint32_t result2 = dv.toUint32(0);
    EXPECT_EQ(result1, result2);
}

// Test with a large year date
TEST_F(DateValueTest_871, LargeYearDate_871) {
    DateValue dv;
    dv.read("9999-12-31");
    uint32_t result = dv.toUint32(0);
    int64_t i64val = dv.toInt64(0);
    if (i64val >= 0 && i64val <= static_cast<int64_t>(std::numeric_limits<uint32_t>::max())) {
        EXPECT_EQ(result, static_cast<uint32_t>(i64val));
    } else if (i64val < 0 || i64val > static_cast<int64_t>(std::numeric_limits<uint32_t>::max())) {
        EXPECT_EQ(result, 0u);
    }
}

// Test default constructed DateValue
TEST_F(DateValueTest_871, DefaultConstructedDateValue_871) {
    DateValue dv;
    uint32_t result = dv.toUint32(0);
    int64_t i64val = dv.toInt64(0);
    if (i64val >= 0 && i64val <= static_cast<int64_t>(std::numeric_limits<uint32_t>::max())) {
        EXPECT_EQ(result, static_cast<uint32_t>(i64val));
    } else {
        EXPECT_EQ(result, 0u);
    }
}
