#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffimage_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "exiv2/tags.hpp"

namespace Exiv2 {
namespace Internal {

// Test fixture for TiffMapping
class TiffMappingTest_1163 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that findDecoder returns a non-null function pointer for default/unknown make
TEST_F(TiffMappingTest_1163, FindDecoderReturnsNonNullForUnknownMake_1163) {
    auto decoder = TiffMapping::findDecoder("UnknownMake", 0x0001, IfdId::ifd0Id);
    ASSERT_NE(decoder, nullptr);
}

// Test that findDecoder returns the default decoder (decodeStdTiffEntry) for an unmatched entry
TEST_F(TiffMappingTest_1163, FindDecoderReturnsDefaultForUnmatchedEntry_1163) {
    auto decoder = TiffMapping::findDecoder("", 0xFFFF, IfdId::ifd0Id);
    ASSERT_NE(decoder, nullptr);
    // The default decoder should be decodeStdTiffEntry
    EXPECT_EQ(decoder, &TiffDecoder::decodeStdTiffEntry);
}

// Test findDecoder with empty make string
TEST_F(TiffMappingTest_1163, FindDecoderWithEmptyMake_1163) {
    auto decoder = TiffMapping::findDecoder("", 0x0100, IfdId::ifd0Id);
    ASSERT_NE(decoder, nullptr);
}

// Test findDecoder with a known make like "OLYMPUS"
TEST_F(TiffMappingTest_1163, FindDecoderWithKnownMakeOlympus_1163) {
    auto decoder = TiffMapping::findDecoder("OLYMPUS", 0x0100, IfdId::ifd0Id);
    ASSERT_NE(decoder, nullptr);
}

// Test findDecoder with a known make like "Canon"
TEST_F(TiffMappingTest_1163, FindDecoderWithKnownMakeCanon_1163) {
    auto decoder = TiffMapping::findDecoder("Canon", 0x0100, IfdId::ifd0Id);
    ASSERT_NE(decoder, nullptr);
}

// Test findDecoder with tag 0 and ifd0Id
TEST_F(TiffMappingTest_1163, FindDecoderWithTagZero_1163) {
    auto decoder = TiffMapping::findDecoder("", 0x0000, IfdId::ifd0Id);
    ASSERT_NE(decoder, nullptr);
}

// Test findDecoder with maximum tag value
TEST_F(TiffMappingTest_1163, FindDecoderWithMaxTag_1163) {
    auto decoder = TiffMapping::findDecoder("", 0xFFFFFFFF, IfdId::ifd0Id);
    ASSERT_NE(decoder, nullptr);
    // Unlikely to match, so should be default
    EXPECT_EQ(decoder, &TiffDecoder::decodeStdTiffEntry);
}

// Test findDecoder with various IfdId groups
TEST_F(TiffMappingTest_1163, FindDecoderWithExifIfd_1163) {
    auto decoder = TiffMapping::findDecoder("", 0x0100, IfdId::exifId);
    ASSERT_NE(decoder, nullptr);
}

// Test findDecoder with ifd1Id group
TEST_F(TiffMappingTest_1163, FindDecoderWithIfd1Id_1163) {
    auto decoder = TiffMapping::findDecoder("", 0x0100, IfdId::ifd1Id);
    ASSERT_NE(decoder, nullptr);
}

// Test findDecoder consistency - same inputs should return same decoder
TEST_F(TiffMappingTest_1163, FindDecoderIsConsistent_1163) {
    auto decoder1 = TiffMapping::findDecoder("Nikon", 0x0100, IfdId::ifd0Id);
    auto decoder2 = TiffMapping::findDecoder("Nikon", 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(decoder1, decoder2);
}

// Test findDecoder with different makes for the same tag returns potentially different decoders
TEST_F(TiffMappingTest_1163, FindDecoderDifferentMakesSameTag_1163) {
    auto decoder1 = TiffMapping::findDecoder("Canon", 0x0100, IfdId::ifd0Id);
    auto decoder2 = TiffMapping::findDecoder("OLYMPUS", 0x0100, IfdId::ifd0Id);
    // Both should be non-null; they may or may not be the same
    ASSERT_NE(decoder1, nullptr);
    ASSERT_NE(decoder2, nullptr);
}

// Test findEncoder returns non-null for unknown make
TEST_F(TiffMappingTest_1163, FindEncoderReturnsNonNullForUnknownMake_1163) {
    auto encoder = TiffMapping::findEncoder("UnknownMake", 0x0001, IfdId::ifd0Id);
    ASSERT_NE(encoder, nullptr);
}

// Test findEncoder with empty make
TEST_F(TiffMappingTest_1163, FindEncoderWithEmptyMake_1163) {
    auto encoder = TiffMapping::findEncoder("", 0x0100, IfdId::ifd0Id);
    ASSERT_NE(encoder, nullptr);
}

// Test findEncoder with maximum tag value
TEST_F(TiffMappingTest_1163, FindEncoderWithMaxTag_1163) {
    auto encoder = TiffMapping::findEncoder("", 0xFFFFFFFF, IfdId::ifd0Id);
    ASSERT_NE(encoder, nullptr);
}

// Test findEncoder consistency
TEST_F(TiffMappingTest_1163, FindEncoderIsConsistent_1163) {
    auto encoder1 = TiffMapping::findEncoder("Nikon", 0x0100, IfdId::ifd0Id);
    auto encoder2 = TiffMapping::findEncoder("Nikon", 0x0100, IfdId::ifd0Id);
    EXPECT_EQ(encoder1, encoder2);
}

// Test findEncoder with known make
TEST_F(TiffMappingTest_1163, FindEncoderWithKnownMake_1163) {
    auto encoder = TiffMapping::findEncoder("Canon", 0x0100, IfdId::ifd0Id);
    ASSERT_NE(encoder, nullptr);
}

// Test findDecoder with a very long make string
TEST_F(TiffMappingTest_1163, FindDecoderWithLongMakeString_1163) {
    std::string longMake(1000, 'A');
    auto decoder = TiffMapping::findDecoder(longMake, 0x0100, IfdId::ifd0Id);
    ASSERT_NE(decoder, nullptr);
    // Long unrecognized make should return default
    EXPECT_EQ(decoder, &TiffDecoder::decodeStdTiffEntry);
}

// Test findDecoder with different groups for the same make and tag
TEST_F(TiffMappingTest_1163, FindDecoderDifferentGroupsSameMakeTag_1163) {
    auto decoder1 = TiffMapping::findDecoder("Canon", 0x0100, IfdId::ifd0Id);
    auto decoder2 = TiffMapping::findDecoder("Canon", 0x0100, IfdId::exifId);
    // Both non-null, may be the same or different
    ASSERT_NE(decoder1, nullptr);
    ASSERT_NE(decoder2, nullptr);
}

}  // namespace Internal
}  // namespace Exiv2
