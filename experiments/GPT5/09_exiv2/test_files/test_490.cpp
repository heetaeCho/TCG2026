#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ostream>
#include <memory>
#include "exiv2/types.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/metadatum.hpp"
#include "exiv2/value.hpp"
#include "exiv2/nikonmn_int.hpp"

// Mocking ExifData for testing
class MockExifData : public Exiv2::ExifData {
public:
    MOCK_METHOD(Exiv2::ExifData::const_iterator, findKey, (const Exiv2::ExifKey& key), (const, override));
};

// Test fixture for Nikon3MakerNote
class Nikon3MakerNoteTest_490 : public ::testing::Test {
protected:
    Exiv2::Internal::Nikon3MakerNote makerNote;
};

// Normal Operation: Testing printFlashMasterDataFl7 with valid input
TEST_F(Nikon3MakerNoteTest_490, PrintFlashMasterDataFl7_ValidInput_490) {
    // Setup
    Exiv2::Value value(Exiv2::unsignedByte);
    MockExifData metadata;

    // Mocking the metadata behavior
    Exiv2::ExifKey key("Exif.NikonFl7.ExternalFlashData2");
    Exiv2::ExifData::const_iterator mockIterator = metadata.findKey(key);
    EXPECT_CALL(metadata, findKey(key))
        .WillOnce(testing::Return(mockIterator));

    // Test
    std::ostringstream os;
    EXPECT_NO_THROW(makerNote.printFlashMasterDataFl7(os, value, &metadata));
    EXPECT_NE(os.str(), "n/a");
}

// Boundary condition: Testing printFlashMasterDataFl7 with invalid type
TEST_F(Nikon3MakerNoteTest_490, PrintFlashMasterDataFl7_InvalidType_490) {
    // Setup
    Exiv2::Value value(Exiv2::unsignedShort);  // Invalid type, expecting unsignedByte
    MockExifData metadata;

    // Test
    std::ostringstream os;
    EXPECT_NO_THROW(makerNote.printFlashMasterDataFl7(os, value, &metadata));
    EXPECT_EQ(os.str(), "(<Value>)");  // Expect the default fallback
}

// Exceptional Case: Testing printFlashMasterDataFl7 with null metadata
TEST_F(Nikon3MakerNoteTest_490, PrintFlashMasterDataFl7_NullMetadata_490) {
    // Setup
    Exiv2::Value value(Exiv2::unsignedByte);

    // Test with null metadata
    std::ostringstream os;
    EXPECT_NO_THROW(makerNote.printFlashMasterDataFl7(os, value, nullptr));
    EXPECT_EQ(os.str(), "(<Value>)");  // Expect default fallback as metadata is null
}

// Boundary Condition: Testing printFlashMasterDataFl7 with missing key in metadata
TEST_F(Nikon3MakerNoteTest_490, PrintFlashMasterDataFl7_MissingKey_490) {
    // Setup
    Exiv2::Value value(Exiv2::unsignedByte);
    MockExifData metadata;

    // Mock the metadata to simulate missing key
    Exiv2::ExifKey key("Exif.NikonFl7.ExternalFlashData2");
    EXPECT_CALL(metadata, findKey(key))
        .WillOnce(testing::Return(metadata.end()));

    // Test
    std::ostringstream os;
    EXPECT_NO_THROW(makerNote.printFlashMasterDataFl7(os, value, &metadata));
    EXPECT_EQ(os.str(), "(<Value>)");  // Expect default fallback
}

// Exceptional Case: Testing printFlashMasterDataFl7 with invalid value count
TEST_F(Nikon3MakerNoteTest_490, PrintFlashMasterDataFl7_InvalidValueCount_490) {
    // Setup
    Exiv2::Value value(Exiv2::unsignedByte);
    MockExifData metadata;

    // Mock the metadata to simulate invalid value count
    EXPECT_CALL(metadata, findKey(testing::_))
        .WillOnce(testing::Return(metadata.end()));

    // Test
    std::ostringstream os;
    EXPECT_NO_THROW(makerNote.printFlashMasterDataFl7(os, value, &metadata));
    EXPECT_EQ(os.str(), "(<Value>)");  // Expect default fallback
}