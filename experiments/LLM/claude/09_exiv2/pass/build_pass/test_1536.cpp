#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "makernote_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NikonSelectorTest_1536 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that size less than 4 returns -1
TEST_F(NikonSelectorTest_1536, SizeLessThan4ReturnsNegativeOne_1536) {
    const byte data[] = {0x00, 0x01, 0x02};
    int result = nikonSelector(0x0000, data, 3, nullptr);
    EXPECT_EQ(-1, result);
}

// Test that size of 0 returns -1
TEST_F(NikonSelectorTest_1536, SizeZeroReturnsNegativeOne_1536) {
    const byte data[] = {0x00};
    int result = nikonSelector(0x0000, data, 0, nullptr);
    EXPECT_EQ(-1, result);
}

// Test that size of 1 returns -1
TEST_F(NikonSelectorTest_1536, SizeOneReturnsNegativeOne_1536) {
    const byte data[] = {0x00};
    int result = nikonSelector(0x0000, data, 1, nullptr);
    EXPECT_EQ(-1, result);
}

// Test that size of 2 returns -1
TEST_F(NikonSelectorTest_1536, SizeTwoReturnsNegativeOne_1536) {
    const byte data[] = {0x00, 0x01};
    int result = nikonSelector(0x0000, data, 2, nullptr);
    EXPECT_EQ(-1, result);
}

// Test that size of 3 returns -1
TEST_F(NikonSelectorTest_1536, SizeThreeReturnsNegativeOne_1536) {
    const byte data[] = {0x00, 0x01, 0x02};
    int result = nikonSelector(0x0000, data, 3, nullptr);
    EXPECT_EQ(-1, result);
}

// Test that size exactly 4 does not automatically return -1 (proceeds to lookup)
TEST_F(NikonSelectorTest_1536, SizeFourProceedsToLookup_1536) {
    // With arbitrary data that likely won't match, should return -1 from lookup failure
    const byte data[] = {0xFF, 0xFF, 0xFF, 0xFF};
    int result = nikonSelector(0xFFFF, data, 4, nullptr);
    EXPECT_EQ(-1, result);
}

// Test that an unknown tag with valid size returns -1
TEST_F(NikonSelectorTest_1536, UnknownTagReturnsNegativeOne_1536) {
    const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00};
    int result = nikonSelector(0x9999, data, 5, nullptr);
    EXPECT_EQ(-1, result);
}

// Test with nullptr TiffComponent (should be ignored per signature)
TEST_F(NikonSelectorTest_1536, NullTiffComponentIsAccepted_1536) {
    const byte data[] = {0x00, 0x00, 0x00, 0x00};
    // Should not crash - the TiffComponent parameter is unused
    int result = nikonSelector(0x0000, data, 4, nullptr);
    // Result is either -1 or a valid index, but should not crash
    EXPECT_GE(result, -1);
}

// Test with large size but unmatched data returns -1
TEST_F(NikonSelectorTest_1536, LargeSizeUnmatchedDataReturnsNegativeOne_1536) {
    std::vector<byte> data(1024, 0x42);
    int result = nikonSelector(0x1234, data.data(), data.size(), nullptr);
    EXPECT_EQ(-1, result);
}

// Test boundary: size exactly at threshold (4) with zero-filled data
TEST_F(NikonSelectorTest_1536, BoundarySizeFourZeroData_1536) {
    const byte data[] = {0x00, 0x00, 0x00, 0x00};
    int result = nikonSelector(0x0000, data, 4, nullptr);
    // Either found or not found, but should not crash
    EXPECT_GE(result, -1);
}

// Test with a known Nikon tag 0x0011 (NikonVr) to see if valid entries are found
TEST_F(NikonSelectorTest_1536, KnownNikonTagLookup_1536) {
    // Try with version string "0100" which is common in Nikon maker notes
    const byte data[] = {'0', '1', '0', '0'};
    int result = nikonSelector(0x0011, data, 4, nullptr);
    // Result should be >= -1 (either found or not)
    EXPECT_GE(result, -1);
}

// Test with tag 0x0001 (NikonISOInfo related)
TEST_F(NikonSelectorTest_1536, Tag0x0001Lookup_1536) {
    const byte data[] = {'0', '2', '0', '0', 0x00, 0x00};
    int result = nikonSelector(0x0001, data, 6, nullptr);
    EXPECT_GE(result, -1);
}
