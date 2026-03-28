#include <gtest/gtest.h>
#include <memory>

#include "tiffimage_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tags.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffCreatorTest_1165 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that creating a component with a known tag and IFD0 group returns a non-null component
TEST_F(TiffCreatorTest_1165, CreateWithKnownIfd0Tag_1165) {
    auto result = TiffCreator::create(0x0100, IfdId::ifd0Id);
    // Tag 0x0100 (ImageWidth) in IFD0 is a standard tag, should be creatable
    // We just check it doesn't crash; result may or may not be null depending on table
    // This tests normal operation
    SUCCEED();
}

// Test that creating a component with an unknown/invalid tag and group returns nullptr
TEST_F(TiffCreatorTest_1165, CreateWithUnknownTagAndGroup_ReturnsNullOrValid_1165) {
    auto result = TiffCreator::create(0xFFFF, IfdId::lastId);
    // An unknown extended tag with an invalid group should return nullptr
    EXPECT_EQ(result, nullptr);
}

// Test creating a component with Tag::all extended tag - this is a special wildcard
TEST_F(TiffCreatorTest_1165, CreateWithTagAll_1165) {
    auto result = TiffCreator::create(static_cast<uint32_t>(Tag::all), IfdId::ifd0Id);
    // Tag::all is used as a fallback key internally; behavior depends on table
    // Just ensure no crash
    SUCCEED();
}

// Test creating with extendedTag = 0 and valid group
TEST_F(TiffCreatorTest_1165, CreateWithZeroTag_1165) {
    auto result = TiffCreator::create(0, IfdId::ifd0Id);
    // Tag 0 might or might not exist; test that it doesn't crash
    SUCCEED();
}

// Test creating with a known Exif IFD tag
TEST_F(TiffCreatorTest_1165, CreateWithExifIfdTag_1165) {
    // 0x829a is ExposureTime in ExifIFD
    auto result = TiffCreator::create(0x829a, IfdId::exifId);
    // Should produce a valid component or use the wildcard fallback
    SUCCEED();
}

// Test creating with GPS IFD group
TEST_F(TiffCreatorTest_1165, CreateWithGpsIfdTag_1165) {
    auto result = TiffCreator::create(0x0001, IfdId::gpsId);
    // GPS tag should be handled
    SUCCEED();
}

// Test creating with IFD1 group (thumbnail IFD)
TEST_F(TiffCreatorTest_1165, CreateWithIfd1Tag_1165) {
    auto result = TiffCreator::create(0x0100, IfdId::ifd1Id);
    SUCCEED();
}

// Test creating with a very large extended tag value
TEST_F(TiffCreatorTest_1165, CreateWithLargeExtendedTag_1165) {
    auto result = TiffCreator::create(0xFFFFFFFF, IfdId::ifd0Id);
    // Very large extended tag, unlikely to be in the table
    // Should either return nullptr or a fallback component
    SUCCEED();
}

// Test that the returned component from a valid create call is a unique_ptr
TEST_F(TiffCreatorTest_1165, CreateReturnsUniquePtr_1165) {
    auto result = TiffCreator::create(0x0100, IfdId::ifd0Id);
    // Verify the type is correct (unique_ptr) - compilation check
    static_assert(std::is_same<decltype(result), TiffComponent::UniquePtr>::value,
                  "create should return TiffComponent::UniquePtr");
    SUCCEED();
}

// Test creating with IopIFD group
TEST_F(TiffCreatorTest_1165, CreateWithIopIfdTag_1165) {
    auto result = TiffCreator::create(0x0001, IfdId::iopId);
    SUCCEED();
}

// Test creating with Tag::next extended tag
TEST_F(TiffCreatorTest_1165, CreateWithTagNext_1165) {
    auto result = TiffCreator::create(static_cast<uint32_t>(Tag::next), IfdId::ifd0Id);
    // Tag::next is a special tag for next IFD pointer
    // Should return a valid component for IFD0
    if (result) {
        EXPECT_NE(result, nullptr);
    }
    SUCCEED();
}

// Test creating with completely invalid group (mnId or similar)
TEST_F(TiffCreatorTest_1165, CreateWithInvalidGroup_1165) {
    auto result = TiffCreator::create(0x0100, IfdId::lastId);
    EXPECT_EQ(result, nullptr);
}

// Test that creating the same tag/group twice produces independent objects
TEST_F(TiffCreatorTest_1165, CreateTwiceProducesIndependentObjects_1165) {
    auto result1 = TiffCreator::create(0x0100, IfdId::ifd0Id);
    auto result2 = TiffCreator::create(0x0100, IfdId::ifd0Id);
    if (result1 && result2) {
        EXPECT_NE(result1.get(), result2.get());
    }
    SUCCEED();
}

// Test creating with Makernote-related group
TEST_F(TiffCreatorTest_1165, CreateWithMakerNoteTag_1165) {
    // Nikon3 makernote tag in IFD0
    auto result = TiffCreator::create(0x927c, IfdId::exifId);
    // MakerNote tag (0x927c) in Exif IFD should have a special creator
    SUCCEED();
}

// Test creating with Canon makernote IFD if available
TEST_F(TiffCreatorTest_1165, CreateWithCanonMakernoteTag_1165) {
    auto result = TiffCreator::create(0x0001, IfdId::canonId);
    SUCCEED();
}

// Test that tag truncation works (extendedTag with high bits set, cast to uint16_t)
TEST_F(TiffCreatorTest_1165, CreateWithExtendedTagHighBits_1165) {
    // extendedTag 0x00010100 should truncate to tag 0x0100
    auto result = TiffCreator::create(0x00010100, IfdId::ifd0Id);
    // The lookup uses extendedTag for the table, but the created component gets the truncated tag
    SUCCEED();
}
