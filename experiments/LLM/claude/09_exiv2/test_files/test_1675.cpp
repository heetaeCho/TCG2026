#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a minimal TiffEncoder for testing
// We need: ExifData, IptcData, XmpData, TiffComponent* pRoot, bool isNewImage,
//          PrimaryGroups, TiffHeaderBase*, FindEncoderFct

class TiffEncoderVisitIfdMakernoteTest_1675 : public ::testing::Test {
protected:
    IptcData iptcData_;
    XmpData xmpData_;

    std::unique_ptr<TiffEncoder> createEncoder(ExifData exifData, bool isNewImage = false) {
        // We need a TiffHeaderBase and a root component.
        // Use TiffImage's default header and encoder factory
        static auto header = std::make_unique<TiffHeaderBase>(42, 8, littleEndian, 0);
        PrimaryGroups primaryGroups;
        
        return std::make_unique<TiffEncoder>(
            std::move(exifData),
            iptcData_,
            xmpData_,
            nullptr,  // pRoot
            isNewImage,
            std::move(primaryGroups),
            header.get(),
            nullptr  // findEncoderFct
        );
    }
};

// Test: When no ByteOrder key exists in ExifData, object byte order should remain unchanged
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, NoByteOrderKey_ObjectUnchanged_1675) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
    EXPECT_FALSE(encoder->dirty());
}

// Test: When ByteOrder key exists with a different valid byte order, object byte order changes and dirty is set
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, DifferentByteOrder_SetsNewOrderAndDirty_1675) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "MM";  // bigEndian
    
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
    EXPECT_TRUE(encoder->dirty());
}

// Test: When ByteOrder key exists with same byte order, object byte order stays same and dirty is NOT set
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, SameByteOrder_NoDirtyFlag_1675) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";  // littleEndian
    
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
    EXPECT_FALSE(encoder->dirty());
}

// Test: When ByteOrder key has invalid value, byte order remains unchanged
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, InvalidByteOrderString_NoChange_1675) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "XX";  // invalid
    
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
    EXPECT_FALSE(encoder->dirty());
}

// Test: del_ is true by default, so ByteOrder and Offset keys should be erased
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, DelTrue_ErasesbyteOrderAndOffset_1675) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "MM";
    exifData["Exif.MakerNote.Offset"] = "100";
    
    // Verify keys exist before
    ASSERT_NE(exifData.findKey(ExifKey("Exif.MakerNote.ByteOrder")), exifData.end());
    ASSERT_NE(exifData.findKey(ExifKey("Exif.MakerNote.Offset")), exifData.end());
    
    // Note: del_ defaults to true, but we can't directly access exifData_ inside TiffEncoder
    // The encoder takes exifData by value (move), so we can't check the original.
    // We check the encoder's byte order instead to verify the method ran.
    
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    // The byte order should have been changed
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
    EXPECT_TRUE(encoder->dirty());
}

// Test: encoder byteOrder() returns the object's byte order after visiting
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, EncoderByteOrderUpdatedToObjectByteOrder_1675) {
    ExifData exifData;
    
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(bigEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    EXPECT_EQ(encoder->byteOrder(), bigEndian);
}

// Test: When ByteOrder key changes the object's byte order, encoder byteOrder reflects the new order
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, EncoderByteOrderReflectsChangedOrder_1675) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "MM";  // bigEndian
    
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(littleEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    // Object should now be bigEndian, and encoder should reflect that
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
    EXPECT_EQ(encoder->byteOrder(), bigEndian);
}

// Test: Empty string for ByteOrder value should result in invalid byte order, no change
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, EmptyByteOrderString_NoChange_1675) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "";
    
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(bigEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    EXPECT_EQ(makernote.byteOrder(), bigEndian);
    EXPECT_FALSE(encoder->dirty());
}

// Test: Setting byte order from big to little endian
TEST_F(TiffEncoderVisitIfdMakernoteTest_1675, ChangeFromBigToLittleEndian_1675) {
    ExifData exifData;
    exifData["Exif.MakerNote.ByteOrder"] = "II";  // littleEndian
    
    auto encoder = createEncoder(exifData);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote.setByteOrder(bigEndian);
    
    encoder->visitIfdMakernote(&makernote);
    
    EXPECT_EQ(makernote.byteOrder(), littleEndian);
    EXPECT_TRUE(encoder->dirty());
}
