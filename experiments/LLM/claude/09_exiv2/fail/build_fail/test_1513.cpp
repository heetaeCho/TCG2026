#include <gtest/gtest.h>
#include <memory>
#include <cstdint>

// Include necessary exiv2 headers
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewOlympus2Mn2Test_1513 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that the function returns a non-null pointer
TEST_F(NewOlympus2Mn2Test_1513, ReturnsNonNullPointer_1513) {
    auto result = newOlympus2Mn2(0x0001, IfdId::ifd0Id, IfdId::olympus2Id);
    ASSERT_NE(result, nullptr);
}

// Test with tag value of 0
TEST_F(NewOlympus2Mn2Test_1513, TagZero_1513) {
    auto result = newOlympus2Mn2(0x0000, IfdId::ifd0Id, IfdId::olympus2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test that the returned object has the correct tag
TEST_F(NewOlympus2Mn2Test_1513, CorrectTag_1513) {
    uint16_t expectedTag = 0x927c;
    auto result = newOlympus2Mn2(expectedTag, IfdId::exifId, IfdId::olympus2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test with different tag values
TEST_F(NewOlympus2Mn2Test_1513, DifferentTagValues_1513) {
    uint16_t tag1 = 0x0001;
    uint16_t tag2 = 0x00FF;
    uint16_t tag3 = 0xFFFF;

    auto result1 = newOlympus2Mn2(tag1, IfdId::ifd0Id, IfdId::olympus2Id);
    auto result2 = newOlympus2Mn2(tag2, IfdId::ifd0Id, IfdId::olympus2Id);
    auto result3 = newOlympus2Mn2(tag3, IfdId::ifd0Id, IfdId::olympus2Id);

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_NE(result3, nullptr);

    EXPECT_EQ(result1->tag(), tag1);
    EXPECT_EQ(result2->tag(), tag2);
    EXPECT_EQ(result3->tag(), tag3);
}

// Test with maximum uint16_t tag value (boundary)
TEST_F(NewOlympus2Mn2Test_1513, MaxTagValue_1513) {
    uint16_t maxTag = UINT16_MAX;
    auto result = newOlympus2Mn2(maxTag, IfdId::ifd0Id, IfdId::olympus2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), maxTag);
}

// Test that multiple calls create independent objects
TEST_F(NewOlympus2Mn2Test_1513, IndependentInstances_1513) {
    auto result1 = newOlympus2Mn2(0x0001, IfdId::ifd0Id, IfdId::olympus2Id);
    auto result2 = newOlympus2Mn2(0x0002, IfdId::ifd0Id, IfdId::olympus2Id);

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test with various group parameters
TEST_F(NewOlympus2Mn2Test_1513, DifferentGroupParameters_1513) {
    auto result1 = newOlympus2Mn2(0x927c, IfdId::exifId, IfdId::olympus2Id);
    auto result2 = newOlympus2Mn2(0x927c, IfdId::ifd0Id, IfdId::olympus2Id);

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
}

// Test the mnHeader via the TiffIfdMakernote interface if accessible
TEST_F(NewOlympus2Mn2Test_1513, HasValidMnHeader_1513) {
    auto result = newOlympus2Mn2(0x927c, IfdId::exifId, IfdId::olympus2Id);
    ASSERT_NE(result, nullptr);
    // The object should be properly constructed with an Olympus2MnHeader
    // We verify it's usable by checking it doesn't crash on basic operations
    EXPECT_EQ(result->tag(), 0x927c);
}
