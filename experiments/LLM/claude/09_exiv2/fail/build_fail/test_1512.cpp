#include <gtest/gtest.h>
#include <cstdint>
#include <memory>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewOlympusMn2Test_1512 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the function returns a non-null pointer
TEST_F(NewOlympusMn2Test_1512, ReturnsNonNull_1512) {
    auto result = newOlympusMn2(0x0001, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
}

// Test that the returned object has the correct tag
TEST_F(NewOlympusMn2Test_1512, CorrectTag_1512) {
    uint16_t testTag = 0x927c;
    auto result = newOlympusMn2(testTag, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test with tag value of zero
TEST_F(NewOlympusMn2Test_1512, TagZero_1512) {
    uint16_t testTag = 0x0000;
    auto result = newOlympusMn2(testTag, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test with maximum tag value
TEST_F(NewOlympusMn2Test_1512, MaxTag_1512) {
    uint16_t testTag = 0xFFFF;
    auto result = newOlympusMn2(testTag, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test with typical Exif MakerNote tag (0x927c)
TEST_F(NewOlympusMn2Test_1512, TypicalMakerNoteTag_1512) {
    uint16_t makerNoteTag = 0x927c;
    auto result = newOlympusMn2(makerNoteTag, IfdId::exifId, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), makerNoteTag);
}

// Test that different group parameters produce valid objects
TEST_F(NewOlympusMn2Test_1512, DifferentGroupParams_1512) {
    auto result = newOlympusMn2(0x927c, IfdId::exifId, IfdId::olympus2Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned unique_ptr has sole ownership (moveable)
TEST_F(NewOlympusMn2Test_1512, UniqueOwnership_1512) {
    auto result = newOlympusMn2(0x927c, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    
    // Move the pointer to verify ownership transfer
    auto moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(moved->tag(), 0x927c);
}

// Test multiple calls return independent objects
TEST_F(NewOlympusMn2Test_1512, MultipleCallsReturnIndependentObjects_1512) {
    auto result1 = newOlympusMn2(0x0001, IfdId::ifd0Id, IfdId::olympusId);
    auto result2 = newOlympusMn2(0x0002, IfdId::ifd0Id, IfdId::olympusId);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test with different mnGroup values
TEST_F(NewOlympusMn2Test_1512, DifferentMnGroup_1512) {
    auto result1 = newOlympusMn2(0x927c, IfdId::exifId, IfdId::olympusId);
    auto result2 = newOlympusMn2(0x927c, IfdId::exifId, IfdId::olympusCsId);
    
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
}

// Test that the returned object is a TiffIfdMakernote
TEST_F(NewOlympusMn2Test_1512, ReturnTypeTiffIfdMakernote_1512) {
    auto result = newOlympusMn2(0x927c, IfdId::ifd0Id, IfdId::olympusId);
    ASSERT_NE(result, nullptr);
    
    // Verify it's actually a TiffIfdMakernote by checking the tag
    TiffIfdMakernote* rawPtr = result.get();
    ASSERT_NE(rawPtr, nullptr);
    EXPECT_EQ(rawPtr->tag(), 0x927c);
}
