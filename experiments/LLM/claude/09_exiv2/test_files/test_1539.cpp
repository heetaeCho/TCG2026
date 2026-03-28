#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Sony2010eSelectorTest_1539 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that passing nullptr as pRoot returns -1 (model not found)
TEST_F(Sony2010eSelectorTest_1539, NullRootReturnsNegativeOne_1539) {
    int result = sony2010eSelector(0, nullptr, 0, nullptr);
    EXPECT_EQ(result, -1);
}

// Test that tag parameter doesn't affect the result when pRoot is null
TEST_F(Sony2010eSelectorTest_1539, DifferentTagValuesWithNullRoot_1539) {
    int result1 = sony2010eSelector(0x0000, nullptr, 0, nullptr);
    int result2 = sony2010eSelector(0xFFFF, nullptr, 0, nullptr);
    int result3 = sony2010eSelector(0x1234, nullptr, 0, nullptr);
    EXPECT_EQ(result1, -1);
    EXPECT_EQ(result2, -1);
    EXPECT_EQ(result3, -1);
}

// Test that pData parameter doesn't affect the result when pRoot is null
TEST_F(Sony2010eSelectorTest_1539, DifferentDataWithNullRoot_1539) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = sony2010eSelector(0, data, sizeof(data), nullptr);
    EXPECT_EQ(result, -1);
}

// Test that size parameter doesn't affect the result when pRoot is null
TEST_F(Sony2010eSelectorTest_1539, DifferentSizeWithNullRoot_1539) {
    int result1 = sony2010eSelector(0, nullptr, 0, nullptr);
    int result2 = sony2010eSelector(0, nullptr, 1000, nullptr);
    int result3 = sony2010eSelector(0, nullptr, SIZE_MAX, nullptr);
    EXPECT_EQ(result1, -1);
    EXPECT_EQ(result2, -1);
    EXPECT_EQ(result3, -1);
}

// Test with non-null data and various sizes, null root still returns -1
TEST_F(Sony2010eSelectorTest_1539, NonNullDataNullRootReturnsNegativeOne_1539) {
    byte data[256] = {};
    for (size_t i = 0; i < sizeof(data); ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }
    int result = sony2010eSelector(42, data, sizeof(data), nullptr);
    EXPECT_EQ(result, -1);
}

// Test that the function consistently returns -1 for null pRoot across multiple calls
TEST_F(Sony2010eSelectorTest_1539, ConsistentReturnForNullRoot_1539) {
    for (int i = 0; i < 100; ++i) {
        int result = sony2010eSelector(static_cast<uint16_t>(i), nullptr, static_cast<size_t>(i), nullptr);
        EXPECT_EQ(result, -1) << "Failed on iteration " << i;
    }
}

// Test return value is strictly -1 or 0 (the only two possible return values)
TEST_F(Sony2010eSelectorTest_1539, ReturnValueIsZeroOrMinusOne_1539) {
    int result = sony2010eSelector(0, nullptr, 0, nullptr);
    EXPECT_TRUE(result == 0 || result == -1);
}
