#include <gtest/gtest.h>
#include <memory>
#include <cstdint>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for newSony2Mn2
class NewSony2Mn2Test_1532 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that newSony2Mn2 returns a non-null pointer
TEST_F(NewSony2Mn2Test_1532, ReturnsNonNullPointer_1532) {
    uint16_t tag = 0x0001;
    IfdId group = ifdIdNotSet;
    IfdId mnGroup = ifdIdNotSet;
    
    auto result = newSony2Mn2(tag, group, mnGroup);
    ASSERT_NE(result, nullptr);
}

// Test that the returned TiffIfdMakernote has the correct tag
TEST_F(NewSony2Mn2Test_1532, ReturnsCorrectTag_1532) {
    uint16_t tag = 0x0042;
    IfdId group = ifdIdNotSet;
    IfdId mnGroup = ifdIdNotSet;
    
    auto result = newSony2Mn2(tag, group, mnGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with tag value of zero
TEST_F(NewSony2Mn2Test_1532, TagZero_1532) {
    uint16_t tag = 0x0000;
    IfdId group = ifdIdNotSet;
    IfdId mnGroup = ifdIdNotSet;
    
    auto result = newSony2Mn2(tag, group, mnGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value
TEST_F(NewSony2Mn2Test_1532, MaxTagValue_1532) {
    uint16_t tag = 0xFFFF;
    IfdId group = ifdIdNotSet;
    IfdId mnGroup = ifdIdNotSet;
    
    auto result = newSony2Mn2(tag, group, mnGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test that each call returns a unique object
TEST_F(NewSony2Mn2Test_1532, ReturnsUniqueObjects_1532) {
    uint16_t tag = 0x0001;
    IfdId group = ifdIdNotSet;
    IfdId mnGroup = ifdIdNotSet;
    
    auto result1 = newSony2Mn2(tag, group, mnGroup);
    auto result2 = newSony2Mn2(tag, group, mnGroup);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}

// Test with different group IDs
TEST_F(NewSony2Mn2Test_1532, DifferentGroupIds_1532) {
    uint16_t tag = 0x0010;
    IfdId group = ifd0Id;
    IfdId mnGroup = sony2Id;
    
    auto result = newSony2Mn2(tag, group, mnGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with Sony-specific typical tag value
TEST_F(NewSony2Mn2Test_1532, SonyTypicalTag_1532) {
    uint16_t tag = 0x9404;
    IfdId group = sony1Id;
    IfdId mnGroup = sony2Id;
    
    auto result = newSony2Mn2(tag, group, mnGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x9404);
}

// Test that the returned object is a valid TiffIfdMakernote (can be used polymorphically)
TEST_F(NewSony2Mn2Test_1532, ReturnedObjectIsValidTiffComponent_1532) {
    uint16_t tag = 0x0001;
    IfdId group = ifdIdNotSet;
    IfdId mnGroup = ifdIdNotSet;
    
    auto result = newSony2Mn2(tag, group, mnGroup);
    ASSERT_NE(result, nullptr);
    
    // The object should be usable as a TiffIfdMakernote
    TiffIfdMakernote* rawPtr = result.get();
    EXPECT_NE(rawPtr, nullptr);
}

// Test multiple consecutive calls for stability
TEST_F(NewSony2Mn2Test_1532, MultipleCallsStability_1532) {
    for (uint16_t i = 0; i < 100; ++i) {
        auto result = newSony2Mn2(i, ifdIdNotSet, ifdIdNotSet);
        ASSERT_NE(result, nullptr) << "Failed at iteration " << i;
        EXPECT_EQ(result->tag(), i) << "Tag mismatch at iteration " << i;
    }
}

// Test with exifId as group
TEST_F(NewSony2Mn2Test_1532, ExifIdGroup_1532) {
    uint16_t tag = 0x927C; // MakerNote tag
    IfdId group = exifId;
    IfdId mnGroup = sony2Id;
    
    auto result = newSony2Mn2(tag, group, mnGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x927C);
}

}  // namespace
