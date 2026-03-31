#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/jp2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <sstream>

using namespace Exiv2;

class Jp2ImageTest_2153 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<Jp2Image> createJp2ImageFromMemory(bool create = true) {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<Jp2Image>(std::move(io), create);
    }

    std::unique_ptr<Jp2Image> createJp2ImageFromBlankData() {
        // Create with create=true to write Jp2Blank data
        auto io = std::make_unique<MemIo>();
        auto img = std::make_unique<Jp2Image>(std::move(io), true);
        return img;
    }
};

// Test that Jp2Image can be constructed with create=true
TEST_F(Jp2ImageTest_2153, ConstructWithCreateTrue_2153) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(Jp2Image img(std::move(io), true));
}

// Test that Jp2Image can be constructed with create=false
TEST_F(Jp2ImageTest_2153, ConstructWithCreateFalse_2153) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(Jp2Image img(std::move(io), false));
}

// Test that when create=true, data is written to IO
TEST_F(Jp2ImageTest_2153, CreateTrueWritesData_2153) {
    auto io = std::make_unique<MemIo>();
    auto rawIo = io.get();
    Jp2Image img(std::move(io), true);
    // The IO should have the Jp2Blank data written (249 bytes)
    EXPECT_GT(rawIo->size(), 0u);
    EXPECT_EQ(rawIo->size(), 249u);
}

// Test that when create=false, no data is written to IO
TEST_F(Jp2ImageTest_2153, CreateFalseDoesNotWriteData_2153) {
    auto io = std::make_unique<MemIo>();
    auto rawIo = io.get();
    Jp2Image img(std::move(io), false);
    EXPECT_EQ(rawIo->size(), 0u);
}

// Test mimeType returns the correct JPEG2000 MIME type
TEST_F(Jp2ImageTest_2153, MimeTypeReturnsCorrectValue_2153) {
    auto img = createJp2ImageFromMemory(true);
    std::string mime = img->mimeType();
    EXPECT_EQ(mime, "image/jp2");
}

// Test that good() returns true after creation with create=true
TEST_F(Jp2ImageTest_2153, GoodAfterCreation_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_TRUE(img->good());
}

// Test that imageType is jp2
TEST_F(Jp2ImageTest_2153, ImageTypeIsJp2_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_EQ(img->imageType(), ImageType::jp2);
}

// Test setComment does not throw (it's overridden to be a no-op or throw)
TEST_F(Jp2ImageTest_2153, SetCommentOverride_2153) {
    auto img = createJp2ImageFromMemory(true);
    // setComment is overridden - test it doesn't crash
    ASSERT_NO_THROW(img->setComment("test comment"));
}

// Test that exifData can be accessed
TEST_F(Jp2ImageTest_2153, ExifDataAccessible_2153) {
    auto img = createJp2ImageFromMemory(true);
    ASSERT_NO_THROW(img->exifData());
}

// Test that iptcData can be accessed
TEST_F(Jp2ImageTest_2153, IptcDataAccessible_2153) {
    auto img = createJp2ImageFromMemory(true);
    ASSERT_NO_THROW(img->iptcData());
}

// Test that xmpData can be accessed
TEST_F(Jp2ImageTest_2153, XmpDataAccessible_2153) {
    auto img = createJp2ImageFromMemory(true);
    ASSERT_NO_THROW(img->xmpData());
}

// Test that pixel dimensions are initially zero
TEST_F(Jp2ImageTest_2153, InitialPixelDimensionsAreZero_2153) {
    auto img = createJp2ImageFromMemory(false);
    EXPECT_EQ(img->pixelWidth(), 0u);
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// Test that readMetadata can be called on a created image
TEST_F(Jp2ImageTest_2153, ReadMetadataOnCreatedImage_2153) {
    auto img = createJp2ImageFromMemory(true);
    // Reading metadata on a minimal blank JP2 should not crash
    // It may throw due to incomplete data, but should not segfault
    try {
        img->readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected - the blank image may not have enough metadata
    }
}

// Test that readMetadata throws on empty IO (create=false)
TEST_F(Jp2ImageTest_2153, ReadMetadataThrowsOnEmptyIo_2153) {
    auto img = createJp2ImageFromMemory(false);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that writeMetadata can be called on a created image
TEST_F(Jp2ImageTest_2153, WriteMetadataOnCreatedImage_2153) {
    auto img = createJp2ImageFromMemory(true);
    // First read, then write
    try {
        img->readMetadata();
        ASSERT_NO_THROW(img->writeMetadata());
    } catch (const Exiv2::Error&) {
        // If readMetadata fails, writeMetadata may also fail
    }
}

// Test writeMetadata throws on empty IO
TEST_F(Jp2ImageTest_2153, WriteMetadataThrowsOnEmptyIo_2153) {
    auto img = createJp2ImageFromMemory(false);
    EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

// Test clearMetadata
TEST_F(Jp2ImageTest_2153, ClearMetadata_2153) {
    auto img = createJp2ImageFromMemory(true);
    ASSERT_NO_THROW(img->clearMetadata());
}

// Test that supports EXIF metadata
TEST_F(Jp2ImageTest_2153, SupportsExifMetadata_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_TRUE(img->supportsMetadata(mdExif));
}

// Test that supports IPTC metadata
TEST_F(Jp2ImageTest_2153, SupportsIptcMetadata_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_TRUE(img->supportsMetadata(mdIptc));
}

// Test that supports XMP metadata
TEST_F(Jp2ImageTest_2153, SupportsXmpMetadata_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_TRUE(img->supportsMetadata(mdXmp));
}

// Test printStructure does not crash
TEST_F(Jp2ImageTest_2153, PrintStructureDoesNotCrash_2153) {
    auto img = createJp2ImageFromMemory(true);
    std::ostringstream oss;
    try {
        img->printStructure(oss, kpsNone, 0);
    } catch (const Exiv2::Error&) {
        // May throw on minimal data
    }
}

// Test setExifData and clearExifData
TEST_F(Jp2ImageTest_2153, SetAndClearExifData_2153) {
    auto img = createJp2ImageFromMemory(true);
    ExifData exifData;
    ASSERT_NO_THROW(img->setExifData(exifData));
    ASSERT_NO_THROW(img->clearExifData());
}

// Test setIptcData and clearIptcData
TEST_F(Jp2ImageTest_2153, SetAndClearIptcData_2153) {
    auto img = createJp2ImageFromMemory(true);
    IptcData iptcData;
    ASSERT_NO_THROW(img->setIptcData(iptcData));
    ASSERT_NO_THROW(img->clearIptcData());
}

// Test setXmpData and clearXmpData
TEST_F(Jp2ImageTest_2153, SetAndClearXmpData_2153) {
    auto img = createJp2ImageFromMemory(true);
    XmpData xmpData;
    ASSERT_NO_THROW(img->setXmpData(xmpData));
    ASSERT_NO_THROW(img->clearXmpData());
}

// Test IO reference is accessible
TEST_F(Jp2ImageTest_2153, IoAccessible_2153) {
    auto img = createJp2ImageFromMemory(true);
    ASSERT_NO_THROW(img->io());
}

// Test that ICC profile is initially not defined
TEST_F(Jp2ImageTest_2153, IccProfileNotInitiallyDefined_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_FALSE(img->iccProfileDefined());
}

// Test clearIccProfile does not crash
TEST_F(Jp2ImageTest_2153, ClearIccProfile_2153) {
    auto img = createJp2ImageFromMemory(true);
    ASSERT_NO_THROW(img->clearIccProfile());
}

// Test that the IO size after create=true matches Jp2Blank size
TEST_F(Jp2ImageTest_2153, IoSizeMatchesJp2Blank_2153) {
    auto io = std::make_unique<MemIo>();
    auto rawIo = io.get();
    Jp2Image img(std::move(io), true);
    EXPECT_EQ(rawIo->size(), 249u);
}

// Test comment is empty initially
TEST_F(Jp2ImageTest_2153, CommentInitiallyEmpty_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_TRUE(img->comment().empty());
}

// Test xmpPacket is initially empty
TEST_F(Jp2ImageTest_2153, XmpPacketInitiallyEmpty_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_TRUE(img->xmpPacket().empty());
}

// Test byteOrder is initially invalid
TEST_F(Jp2ImageTest_2153, ByteOrderInitiallyInvalid_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_EQ(img->byteOrder(), invalidByteOrder);
}

// Test setByteOrder
TEST_F(Jp2ImageTest_2153, SetByteOrder_2153) {
    auto img = createJp2ImageFromMemory(true);
    img->setByteOrder(bigEndian);
    EXPECT_EQ(img->byteOrder(), bigEndian);
    img->setByteOrder(littleEndian);
    EXPECT_EQ(img->byteOrder(), littleEndian);
}

// Test nativePreviews is initially empty
TEST_F(Jp2ImageTest_2153, NativePreviewsInitiallyEmpty_2153) {
    auto img = createJp2ImageFromMemory(true);
    EXPECT_TRUE(img->nativePreviews().empty());
}
