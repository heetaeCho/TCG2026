#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// A concrete TiffEntry subclass for testing
// TiffEntry should be available from tiffcomposite_int.hpp

namespace {

// A simple FindDecoderFct that returns nullptr (use standard decoder)
DecoderFct findDecoderFct(const std::string& /*make*/, uint16_t /*tag*/, IfdId /*group*/) {
    return nullptr;
}

class TiffDecoderDecodeStdTiffEntryTest_1663 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_.clear();
        iptcData_.clear();
        xmpData_.clear();
    }

    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
};

TEST_F(TiffDecoderDecodeStdTiffEntryTest_1663, DecodeStdTiffEntry_AddsToExifData_1663) {
    // Create a TiffEntry with a known tag in IFD0 (e.g., ImageDescription = 0x010e)
    TiffEntry entry(0x010e, IfdId::ifd0Id);

    // Set a value on the entry
    auto value = Value::create(asciiString);
    value->read("Test Image Description");
    entry.setValue(std::move(value));

    // Create decoder
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findDecoderFct);

    // Call decodeStdTiffEntry
    decoder.decodeStdTiffEntry(&entry);

    // Verify the entry was added to exifData
    EXPECT_FALSE(exifData_.empty());
    EXPECT_EQ(exifData_.count(), 1u);

    // Find the key
    ExifKey key("Exif.Image.ImageDescription");
    auto it = exifData_.findKey(key);
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "Test Image Description");
}

TEST_F(TiffDecoderDecodeStdTiffEntryTest_1663, DecodeStdTiffEntry_MultipleEntries_1663) {
    // Add two different entries
    TiffEntry entry1(0x010e, IfdId::ifd0Id); // ImageDescription
    auto value1 = Value::create(asciiString);
    value1->read("Description");
    entry1.setValue(std::move(value1));

    TiffEntry entry2(0x010f, IfdId::ifd0Id); // Make
    auto value2 = Value::create(asciiString);
    value2->read("TestMake");
    entry2.setValue(std::move(value2));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findDecoderFct);

    decoder.decodeStdTiffEntry(&entry1);
    decoder.decodeStdTiffEntry(&entry2);

    EXPECT_EQ(exifData_.count(), 2u);

    ExifKey key1("Exif.Image.ImageDescription");
    auto it1 = exifData_.findKey(key1);
    ASSERT_NE(it1, exifData_.end());
    EXPECT_EQ(it1->toString(), "Description");

    ExifKey key2("Exif.Image.Make");
    auto it2 = exifData_.findKey(key2);
    ASSERT_NE(it2, exifData_.end());
    EXPECT_EQ(it2->toString(), "TestMake");
}

TEST_F(TiffDecoderDecodeStdTiffEntryTest_1663, DecodeStdTiffEntry_NumericValue_1663) {
    // Test with a numeric tag (e.g., Orientation = 0x0112, SHORT type)
    TiffEntry entry(0x0112, IfdId::ifd0Id); // Orientation

    auto value = Value::create(unsignedShort);
    value->read("1");
    entry.setValue(std::move(value));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findDecoderFct);
    decoder.decodeStdTiffEntry(&entry);

    EXPECT_EQ(exifData_.count(), 1u);

    ExifKey key("Exif.Image.Orientation");
    auto it = exifData_.findKey(key);
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(), 1);
}

TEST_F(TiffDecoderDecodeStdTiffEntryTest_1663, DecodeStdTiffEntry_ExifIfdTag_1663) {
    // Test with a tag from the Exif IFD (e.g., ExposureTime = 0x829a)
    TiffEntry entry(0x829a, IfdId::exifId); // ExposureTime

    auto value = Value::create(unsignedRational);
    value->read("1/100");
    entry.setValue(std::move(value));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findDecoderFct);
    decoder.decodeStdTiffEntry(&entry);

    EXPECT_EQ(exifData_.count(), 1u);

    ExifKey key("Exif.Photo.ExposureTime");
    auto it = exifData_.findKey(key);
    ASSERT_NE(it, exifData_.end());
}

TEST_F(TiffDecoderDecodeStdTiffEntryTest_1663, DecodeStdTiffEntry_EmptyStringValue_1663) {
    TiffEntry entry(0x010e, IfdId::ifd0Id); // ImageDescription

    auto value = Value::create(asciiString);
    value->read("");
    entry.setValue(std::move(value));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findDecoderFct);
    decoder.decodeStdTiffEntry(&entry);

    EXPECT_EQ(exifData_.count(), 1u);

    ExifKey key("Exif.Image.ImageDescription");
    auto it = exifData_.findKey(key);
    ASSERT_NE(it, exifData_.end());
}

TEST_F(TiffDecoderDecodeStdTiffEntryTest_1663, DecodeStdTiffEntry_GPSTag_1663) {
    // Test with GPS IFD tag (e.g., GPSVersionID = 0x0000)
    TiffEntry entry(0x0000, IfdId::gpsId); // GPSVersionID

    auto value = Value::create(unsignedByte);
    value->read("2 2 0 0");
    entry.setValue(std::move(value));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findDecoderFct);
    decoder.decodeStdTiffEntry(&entry);

    EXPECT_EQ(exifData_.count(), 1u);

    ExifKey key("Exif.GPSInfo.GPSVersionID");
    auto it = exifData_.findKey(key);
    ASSERT_NE(it, exifData_.end());
}

TEST_F(TiffDecoderDecodeStdTiffEntryTest_1663, DecodeStdTiffEntry_NullValue_1663) {
    // Entry with no value set - pValue() returns nullptr
    TiffEntry entry(0x010e, IfdId::ifd0Id);
    // Don't set any value

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findDecoderFct);

    // This should handle nullptr pValue gracefully
    // The behavior depends on implementation - it may add with null or skip
    decoder.decodeStdTiffEntry(&entry);

    // Just verify no crash occurred; count may be 0 or 1 depending on impl
    SUCCEED();
}

}  // namespace
