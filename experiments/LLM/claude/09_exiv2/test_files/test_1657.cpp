#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper function to create a TiffDecoder with required dependencies
class TiffDecoderVisitIfdMakernoteTest_1657 : public ::testing::Test {
protected:
    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;

    void SetUp() override {
        exifData_.clear();
    }
};

// Test that visitIfdMakernote sets the MakerNote.Offset in ExifData
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, SetsOffsetInExifData_1657) {
    // Create a TiffIfdMakernote object
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    // Create a TiffDecoder
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    
    // Visit the makernote
    decoder.visitIfdMakernote(&makernote);
    
    // Check that the offset key exists
    auto it = exifData_.findKey(ExifKey("Exif.MakerNote.Offset"));
    ASSERT_NE(it, exifData_.end());
    
    // The mnOffset should be the default (0 since it's value-initialized)
    EXPECT_EQ(it->toInt64(0), static_cast<int64_t>(makernote.mnOffset()));
}

// Test that visitIfdMakernote sets ByteOrder to "II" for littleEndian
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, SetsLittleEndianByteOrder_1657) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote);
    
    auto it = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "II");
}

// Test that visitIfdMakernote sets ByteOrder to "MM" for bigEndian
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, SetsBigEndianByteOrder_1657) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(bigEndian);
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote);
    
    auto it = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "MM");
}

// Test that visitIfdMakernote does NOT set ByteOrder for invalidByteOrder
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, DoesNotSetByteOrderForInvalid_1657) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // Default byte order should be invalidByteOrder based on the header
    // (imageByteOrder_ is initialized to invalidByteOrder)
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote);
    
    // Offset should still be set
    auto offsetIt = exifData_.findKey(ExifKey("Exif.MakerNote.Offset"));
    ASSERT_NE(offsetIt, exifData_.end());
    
    // ByteOrder should NOT be set for invalidByteOrder
    auto byteOrderIt = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
    EXPECT_EQ(byteOrderIt, exifData_.end());
}

// Test that the offset value matches what mnOffset() returns
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, OffsetMatchesMnOffset_1657) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    size_t expectedOffset = makernote.mnOffset();
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote);
    
    auto it = exifData_.findKey(ExifKey("Exif.MakerNote.Offset"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), static_cast<int64_t>(static_cast<uint32_t>(expectedOffset)));
}

// Test calling visitIfdMakernote twice overwrites previous values
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, CalledTwiceOverwritesValues_1657) {
    TiffIfdMakernote makernote1(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote1.setByteOrder(littleEndian);
    
    TiffIfdMakernote makernote2(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote2.setByteOrder(bigEndian);
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote1);
    
    // Verify first call set "II"
    auto it = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "II");
    
    decoder.visitIfdMakernote(&makernote2);
    
    // After second call, ByteOrder should be "MM"
    it = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toString(), "MM");
}

// Test that both Offset and ByteOrder are set together for littleEndian
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, BothFieldsSetForLittleEndian_1657) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote);
    
    auto offsetIt = exifData_.findKey(ExifKey("Exif.MakerNote.Offset"));
    ASSERT_NE(offsetIt, exifData_.end());
    
    auto byteOrderIt = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
    ASSERT_NE(byteOrderIt, exifData_.end());
    EXPECT_EQ(byteOrderIt->toString(), "II");
}

// Test that both Offset and ByteOrder are set together for bigEndian
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, BothFieldsSetForBigEndian_1657) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(bigEndian);
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote);
    
    auto offsetIt = exifData_.findKey(ExifKey("Exif.MakerNote.Offset"));
    ASSERT_NE(offsetIt, exifData_.end());
    
    auto byteOrderIt = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
    ASSERT_NE(byteOrderIt, exifData_.end());
    EXPECT_EQ(byteOrderIt->toString(), "MM");
}

// Test with invalidByteOrder: only Offset is set, not ByteOrder
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, OnlyOffsetSetForInvalidByteOrder_1657) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // byteOrder() should return invalidByteOrder by default
    ASSERT_EQ(makernote.byteOrder(), invalidByteOrder);
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote);
    
    // Offset should be present
    auto offsetIt = exifData_.findKey(ExifKey("Exif.MakerNote.Offset"));
    EXPECT_NE(offsetIt, exifData_.end());
    
    // ByteOrder should not be present
    auto byteOrderIt = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
    EXPECT_EQ(byteOrderIt, exifData_.end());
}

// Test offset is stored as uint32_t (check cast behavior)
TEST_F(TiffDecoderVisitIfdMakernoteTest_1657, OffsetStoredAsUint32_1657) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullptr);
    decoder.visitIfdMakernote(&makernote);
    
    auto it = exifData_.findKey(ExifKey("Exif.MakerNote.Offset"));
    ASSERT_NE(it, exifData_.end());
    
    // The offset should be a valid uint32_t value
    int64_t val = it->toInt64(0);
    EXPECT_GE(val, 0);
    EXPECT_LE(val, static_cast<int64_t>(std::numeric_limits<uint32_t>::max()));
}
