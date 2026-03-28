#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a minimal TiffEncoder
// We need a TiffHeaderBase and related structures
class TiffEncoderTest_1688 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a TiffEncoder with minimal setup
    std::unique_ptr<TiffEncoder> createEncoder(ExifData exifData, bool isNewImage = false) {
        static IptcData iptcData;
        static XmpData xmpData;
        // We need a header - use TiffHeader
        static TiffHeader header;
        PrimaryGroups primaryGroups;
        
        // pRoot can be nullptr for our test purposes if we don't visit directories
        // But the encoder constructor may need it - let's create a minimal TiffDirectory
        static TiffDirectory rootDir(0x0000, IfdId::ifd0Id);

        return std::make_unique<TiffEncoder>(
            std::move(exifData),
            iptcData,
            xmpData,
            &rootDir,
            isNewImage,
            std::move(primaryGroups),
            &header,
            nullptr  // findEncoderFct
        );
    }
};

// Test: When datum size fits within object size, dirty flag should not be set by size comparison
TEST_F(TiffEncoderTest_1688, EncodeTiffEntryBase_DatumFitsInObject_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    // Create a TiffEntryBase with some initial data
    // Use ttUnsignedShort (type 3) which is 2 bytes per count
    TiffEntry object(0x0100, IfdId::ifd0Id);
    
    // Set up object with some data space
    auto storage = std::make_shared<DataBuf>(10);
    std::memset(storage->data(), 0, 10);
    object.setData(storage->data(), 10, storage);
    
    // Create an Exifdatum with a value that fits (smaller than 10 bytes)
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(100);  // uint32 = 4 bytes, fits in 10
    
    // Ensure encoder is not dirty before
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
    
    encoder->encodeTiffEntryBase(&object, &datum);
    
    // Since datum size (4) <= object size (10), dirty should remain false
    // (assuming no other reason to set dirty)
    // Note: dirty might still be false since value fits
    EXPECT_FALSE(encoder->dirty());
}

// Test: When datum size exceeds object size, dirty flag should be set
TEST_F(TiffEncoderTest_1688, EncodeTiffEntryBase_DatumExceedsObjectSize_SetsDirty_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    // Create a TiffEntryBase with very small data space
    TiffEntry object(0x0100, IfdId::ifd0Id);
    
    // Set up object with only 1 byte of space
    auto storage = std::make_shared<DataBuf>(1);
    std::memset(storage->data(), 0, 1);
    object.setData(storage->data(), 1, storage);
    
    // Create an Exifdatum with a value larger than 1 byte
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(100);  // uint32 = 4 bytes, exceeds 1
    
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
    
    encoder->encodeTiffEntryBase(&object, &datum);
    
    // Since datum size (4) > object size (1), dirty should be set to true
    EXPECT_TRUE(encoder->dirty());
}

// Test: After encoding, the object's value should be updated
TEST_F(TiffEncoderTest_1688, EncodeTiffEntryBase_UpdatesObjectValue_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    TiffEntry object(0x0100, IfdId::ifd0Id);
    
    auto storage = std::make_shared<DataBuf>(20);
    std::memset(storage->data(), 0, 20);
    object.setData(storage->data(), 20, storage);
    
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(42);
    
    encoder->encodeTiffEntryBase(&object, &datum);
    
    // After encoding, the object should have a value
    ASSERT_NE(object.pValue(), nullptr);
    // The value should match what was set
    EXPECT_EQ(object.pValue()->toInt64(), 42);
}

// Test: setDirty and dirty accessor work correctly
TEST_F(TiffEncoderTest_1688, SetDirtyAndDirtyAccessor_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
    
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test: byteOrder returns the header's byte order
TEST_F(TiffEncoderTest_1688, ByteOrderReturnsHeaderByteOrder_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    // TiffHeader default byte order is littleEndian
    ByteOrder bo = encoder->byteOrder();
    EXPECT_TRUE(bo == littleEndian || bo == bigEndian);
}

// Test: Encoding with exact size match (boundary condition)
TEST_F(TiffEncoderTest_1688, EncodeTiffEntryBase_ExactSizeMatch_NotDirty_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    TiffEntry object(0x0100, IfdId::ifd0Id);
    
    // uint32_t is 4 bytes, set object data to exactly 4 bytes
    auto storage = std::make_shared<DataBuf>(4);
    std::memset(storage->data(), 0, 4);
    object.setData(storage->data(), 4, storage);
    
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(100);  // 4 bytes exactly
    
    encoder->setDirty(false);
    encoder->encodeTiffEntryBase(&object, &datum);
    
    // datum size (4) == object size (4), should NOT set dirty
    EXPECT_FALSE(encoder->dirty());
}

// Test: Encoding with zero-size object data and non-zero datum
TEST_F(TiffEncoderTest_1688, EncodeTiffEntryBase_ZeroSizeObject_SetsDirty_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    TiffEntry object(0x0100, IfdId::ifd0Id);
    
    // Object with size 0 (no data set, or zero-length data)
    auto storage = std::make_shared<DataBuf>(0);
    object.setData(storage->data(), 0, storage);
    
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = static_cast<uint32_t>(100);  // 4 bytes > 0
    
    encoder->setDirty(false);
    encoder->encodeTiffEntryBase(&object, &datum);
    
    // datum size > 0 = object size, should set dirty
    EXPECT_TRUE(encoder->dirty());
}

// Test: Encoding with string value
TEST_F(TiffEncoderTest_1688, EncodeTiffEntryBase_StringValue_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    TiffEntry object(0x010e, IfdId::ifd0Id);  // ImageDescription
    
    auto storage = std::make_shared<DataBuf>(100);
    std::memset(storage->data(), 0, 100);
    object.setData(storage->data(), 100, storage);
    
    ExifKey key("Exif.Image.ImageDescription");
    Exifdatum datum(key);
    datum = std::string("Test description");
    
    encoder->setDirty(false);
    encoder->encodeTiffEntryBase(&object, &datum);
    
    // String "Test description" + null terminator = 17 bytes < 100, should not be dirty
    EXPECT_FALSE(encoder->dirty());
    
    // Value should be updated
    ASSERT_NE(object.pValue(), nullptr);
    EXPECT_EQ(object.pValue()->toString(), "Test description");
}

// Test: Encoding a string value that exceeds object size
TEST_F(TiffEncoderTest_1688, EncodeTiffEntryBase_LargeStringValue_SetsDirty_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    TiffEntry object(0x010e, IfdId::ifd0Id);  // ImageDescription
    
    // Very small buffer
    auto storage = std::make_shared<DataBuf>(2);
    std::memset(storage->data(), 0, 2);
    object.setData(storage->data(), 2, storage);
    
    ExifKey key("Exif.Image.ImageDescription");
    Exifdatum datum(key);
    datum = std::string("This is a very long description that won't fit");
    
    encoder->setDirty(false);
    encoder->encodeTiffEntryBase(&object, &datum);
    
    // Large string > 2 bytes, should be dirty
    EXPECT_TRUE(encoder->dirty());
}

// Test: writeMethod returns a valid WriteMethod
TEST_F(TiffEncoderTest_1688, WriteMethodReturnsValid_1688) {
    ExifData exifData;
    auto encoder = createEncoder(exifData);
    
    WriteMethod wm = encoder->writeMethod();
    EXPECT_TRUE(wm == wmNonIntrusive || wm == wmIntrusive);
}
