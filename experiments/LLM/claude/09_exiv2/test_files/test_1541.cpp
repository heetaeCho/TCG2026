#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMisc2bSelectorTest_1541 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that when pRoot is nullptr, function returns -1
TEST_F(SonyMisc2bSelectorTest_1541, NullRootReturnsNegativeOne_1541) {
    int result = sonyMisc2bSelector(0, nullptr, 0, nullptr);
    EXPECT_EQ(result, -1);
}

// Test with tag=0 and no valid data
TEST_F(SonyMisc2bSelectorTest_1541, NullRootWithArbitraryTag_1541) {
    int result = sonyMisc2bSelector(0x9404, nullptr, 0, nullptr);
    EXPECT_EQ(result, -1);
}

// Test with tag and size but null root
TEST_F(SonyMisc2bSelectorTest_1541, NullRootWithNonZeroSize_1541) {
    byte data[10] = {0};
    int result = sonyMisc2bSelector(0x1234, data, sizeof(data), nullptr);
    EXPECT_EQ(result, -1);
}

// Test with various tag values and null pRoot - all should return -1
TEST_F(SonyMisc2bSelectorTest_1541, NullRootVariousTags_1541) {
    EXPECT_EQ(sonyMisc2bSelector(0, nullptr, 0, nullptr), -1);
    EXPECT_EQ(sonyMisc2bSelector(1, nullptr, 0, nullptr), -1);
    EXPECT_EQ(sonyMisc2bSelector(0xFFFF, nullptr, 0, nullptr), -1);
}

// Test that first three parameters are effectively unused (tag, pData, size)
// Since pRoot is nullptr, getExifValue will fail regardless
TEST_F(SonyMisc2bSelectorTest_1541, FirstThreeParamsIgnoredWhenNullRoot_1541) {
    byte data[100] = {};
    // Fill data with various patterns
    for (int i = 0; i < 100; i++) data[i] = static_cast<byte>(i);
    
    int result1 = sonyMisc2bSelector(0, nullptr, 0, nullptr);
    int result2 = sonyMisc2bSelector(0x9404, data, 100, nullptr);
    int result3 = sonyMisc2bSelector(0xFFFF, data, 50, nullptr);
    
    EXPECT_EQ(result1, -1);
    EXPECT_EQ(result2, -1);
    EXPECT_EQ(result3, -1);
}

// Verify that the function consistently returns -1 for null pRoot
TEST_F(SonyMisc2bSelectorTest_1541, ConsistentReturnForNullRoot_1541) {
    for (uint16_t tag = 0; tag < 100; tag++) {
        EXPECT_EQ(sonyMisc2bSelector(tag, nullptr, 0, nullptr), -1)
            << "Failed for tag=" << tag;
    }
}

// Test with zero-length data and null root
TEST_F(SonyMisc2bSelectorTest_1541, ZeroSizeDataNullRoot_1541) {
    byte data[1] = {0};
    int result = sonyMisc2bSelector(0, data, 0, nullptr);
    EXPECT_EQ(result, -1);
}
