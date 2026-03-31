#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/jp2image.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>

#include <cstring>
#include <fstream>
#include <sstream>

namespace {

// Minimal valid JP2 file header bytes
// JP2 signature box: 0x0000000C 'jP  ' followed by 0x0D0A870A
// Then a file type box
const unsigned char kMinimalJp2Header[] = {
    // Signature box (12 bytes)
    0x00, 0x00, 0x00, 0x0C, // Box length = 12
    0x6A, 0x50, 0x20, 0x20, // Box type = 'jP  '
    0x0D, 0x0A, 0x87, 0x0A, // Signature
    // File type box (20 bytes)
    0x00, 0x00, 0x00, 0x14, // Box length = 20
    0x66, 0x74, 0x79, 0x70, // Box type = 'ftyp'
    0x6A, 0x70, 0x32, 0x20, // Brand = 'jp2 '
    0x00, 0x00, 0x00, 0x00, // Minor version
    0x6A, 0x70, 0x32, 0x20, // Compatibility = 'jp2 '
};

class Jp2ImageTest_88 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a MemIo with given data
    static Exiv2::BasicIo::UniquePtr createMemIo(const unsigned char* data, size_t size) {
        return std::make_unique<Exiv2::MemIo>(data, size);
    }

    // Helper to create an empty MemIo
    static Exiv2::BasicIo::UniquePtr createEmptyMemIo() {
        return std::make_unique<Exiv2::MemIo>();
    }
};

// Test: newJp2Instance with valid JP2 data returns non-null image
TEST_F(Jp2ImageTest_88, NewJp2InstanceWithValidData_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    // With minimal header, the image should be created (good() depends on io state)
    // The io is valid and open, so good() should return true
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Test: newJp2Instance with create=true on empty MemIo
TEST_F(Jp2ImageTest_88, NewJp2InstanceCreateMode_88) {
    auto io = createEmptyMemIo();
    auto image = Exiv2::newJp2Instance(std::move(io), true);
    // When create=true, the image should be created with an empty/new io
    // Whether this returns null depends on whether good() is true
    // We just verify it doesn't crash
    // If it returns non-null, it should be good
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: newJp2Instance with invalid/empty data and create=false
TEST_F(Jp2ImageTest_88, NewJp2InstanceWithEmptyDataNoCreate_88) {
    auto io = createEmptyMemIo();
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    // Empty io with no create might not be "good"
    // This could return nullptr if good() is false
    // We just check it doesn't crash; behavior depends on implementation
}

// Test: newJp2Instance with garbage data returns either null or non-good image
TEST_F(Jp2ImageTest_88, NewJp2InstanceWithGarbageData_88) {
    const unsigned char garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    auto io = createMemIo(garbage, sizeof(garbage));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    // With garbage data, the io is still valid (MemIo), so good() could be true
    // but readMetadata would fail later. The factory might still return non-null.
    // We just verify no crash.
}

// Test: Jp2Image MIME type
TEST_F(Jp2ImageTest_88, Jp2ImageMimeType_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_EQ(image->mimeType(), "image/jp2");
    }
}

// Test: Jp2Image initial pixel dimensions are zero
TEST_F(Jp2ImageTest_88, Jp2ImageInitialPixelDimensions_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_EQ(image->pixelWidth(), 0u);
        EXPECT_EQ(image->pixelHeight(), 0u);
    }
}

// Test: Jp2Image comment is initially empty
TEST_F(Jp2ImageTest_88, Jp2ImageInitialComment_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_TRUE(image->comment().empty());
    }
}

// Test: Jp2Image setComment and clearComment
TEST_F(Jp2ImageTest_88, Jp2ImageSetAndClearComment_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        image->setComment("test comment");
        EXPECT_EQ(image->comment(), "test comment");
        image->clearComment();
        EXPECT_TRUE(image->comment().empty());
    }
}

// Test: Jp2Image setExifData and clearExifData
TEST_F(Jp2ImageTest_88, Jp2ImageSetAndClearExifData_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        Exiv2::ExifData exifData;
        image->setExifData(exifData);
        image->clearExifData();
        EXPECT_TRUE(image->exifData().empty());
    }
}

// Test: Jp2Image setIptcData and clearIptcData
TEST_F(Jp2ImageTest_88, Jp2ImageSetAndClearIptcData_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        Exiv2::IptcData iptcData;
        image->setIptcData(iptcData);
        image->clearIptcData();
        EXPECT_TRUE(image->iptcData().empty());
    }
}

// Test: Jp2Image setXmpData and clearXmpData
TEST_F(Jp2ImageTest_88, Jp2ImageSetAndClearXmpData_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        Exiv2::XmpData xmpData;
        image->setXmpData(xmpData);
        image->clearXmpData();
        EXPECT_TRUE(image->xmpData().empty());
    }
}

// Test: Jp2Image clearMetadata clears all metadata
TEST_F(Jp2ImageTest_88, Jp2ImageClearMetadata_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        image->setComment("some comment");
        image->clearMetadata();
        EXPECT_TRUE(image->comment().empty());
        EXPECT_TRUE(image->exifData().empty());
        EXPECT_TRUE(image->iptcData().empty());
        EXPECT_TRUE(image->xmpData().empty());
    }
}

// Test: Jp2Image ICC profile is initially not defined
TEST_F(Jp2ImageTest_88, Jp2ImageInitialIccProfile_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_FALSE(image->iccProfileDefined());
    }
}

// Test: Jp2Image clearIccProfile
TEST_F(Jp2ImageTest_88, Jp2ImageClearIccProfile_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        image->clearIccProfile();
        EXPECT_FALSE(image->iccProfileDefined());
    }
}

// Test: Jp2Image io() returns a valid reference
TEST_F(Jp2ImageTest_88, Jp2ImageIoReference_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        const Exiv2::BasicIo& ioRef = image->io();
        // Just verify we can call size on the io reference
        EXPECT_GE(ioRef.size(), sizeof(kMinimalJp2Header));
    }
}

// Test: Jp2Image good() returns true for valid io
TEST_F(Jp2ImageTest_88, Jp2ImageGoodWithValidIo_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test: readMetadata on minimal (incomplete) JP2 throws or handles gracefully
TEST_F(Jp2ImageTest_88, Jp2ImageReadMetadataOnMinimalData_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        // Minimal header is not a complete JP2 file, readMetadata should throw
        EXPECT_THROW(image->readMetadata(), Exiv2::Error);
    }
}

// Test: newJp2Instance with single byte data
TEST_F(Jp2ImageTest_88, NewJp2InstanceWithSingleByte_88) {
    const unsigned char singleByte[] = {0xFF};
    auto io = createMemIo(singleByte, 1);
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    // Should not crash regardless of result
}

// Test: Jp2Image xmpPacket is initially empty
TEST_F(Jp2ImageTest_88, Jp2ImageInitialXmpPacket_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_TRUE(image->xmpPacket().empty());
    }
}

// Test: Jp2Image setXmpPacket and clearXmpPacket
TEST_F(Jp2ImageTest_88, Jp2ImageSetAndClearXmpPacket_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        image->setXmpPacket("<xmp>test</xmp>");
        EXPECT_EQ(image->xmpPacket(), "<xmp>test</xmp>");
        image->clearXmpPacket();
        EXPECT_TRUE(image->xmpPacket().empty());
    }
}

// Test: Jp2Image nativePreviews is initially empty
TEST_F(Jp2ImageTest_88, Jp2ImageInitialNativePreviews_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_TRUE(image->nativePreviews().empty());
    }
}

// Test: Jp2Image writeXmpFromPacket default is false
TEST_F(Jp2ImageTest_88, Jp2ImageWriteXmpFromPacketDefault_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_FALSE(image->writeXmpFromPacket());
    }
}

// Test: Jp2Image setWriteXmpFromPacket
TEST_F(Jp2ImageTest_88, Jp2ImageSetWriteXmpFromPacket_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        image->writeXmpFromPacket(true);
        EXPECT_TRUE(image->writeXmpFromPacket());
        image->writeXmpFromPacket(false);
        EXPECT_FALSE(image->writeXmpFromPacket());
    }
}

// Test: Jp2Image byteOrder default is invalidByteOrder
TEST_F(Jp2ImageTest_88, Jp2ImageDefaultByteOrder_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        EXPECT_EQ(image->byteOrder(), Exiv2::invalidByteOrder);
    }
}

// Test: Jp2Image setByteOrder
TEST_F(Jp2ImageTest_88, Jp2ImageSetByteOrder_88) {
    auto io = createMemIo(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    if (image) {
        image->setByteOrder(Exiv2::bigEndian);
        EXPECT_EQ(image->byteOrder(), Exiv2::bigEndian);
        image->setByteOrder(Exiv2::littleEndian);
        EXPECT_EQ(image->byteOrder(), Exiv2::littleEndian);
    }
}

// Test: newJp2Instance with nullptr-like empty unique_ptr should handle gracefully or not
// This tests edge case of passing a truly empty unique_ptr
// Note: This may cause a crash in real code - we document it as an edge case test
// Commenting out as it would likely segfault
// TEST_F(Jp2ImageTest_88, NewJp2InstanceWithNullIo_88) {
//     Exiv2::BasicIo::UniquePtr io;
//     auto image = Exiv2::newJp2Instance(std::move(io), false);
// }

// Test: Jp2Image large garbage data
TEST_F(Jp2ImageTest_88, NewJp2InstanceWithLargeGarbageData_88) {
    std::vector<unsigned char> largeGarbage(10000, 0xAB);
    auto io = createMemIo(largeGarbage.data(), largeGarbage.size());
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    // Should not crash; image may or may not be null
}

// Test: Jp2Image with truncated JP2 signature box
TEST_F(Jp2ImageTest_88, NewJp2InstanceWithTruncatedSignature_88) {
    // Only first 8 bytes of signature box (incomplete)
    const unsigned char truncated[] = {
        0x00, 0x00, 0x00, 0x0C,
        0x6A, 0x50, 0x20, 0x20,
    };
    auto io = createMemIo(truncated, sizeof(truncated));
    auto image = Exiv2::newJp2Instance(std::move(io), false);
    // Should not crash
}

}  // namespace
