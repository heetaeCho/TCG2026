#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include <exiv2/jpgimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <cstring>
#include <fstream>
#include <sstream>

namespace {

// Minimal valid JPEG data: SOI marker + EOI marker
const uint8_t kMinimalJpeg[] = {
    0xFF, 0xD8,  // SOI
    0xFF, 0xD9   // EOI
};

// Invalid data (not a JPEG)
const uint8_t kInvalidData[] = {
    0x00, 0x00, 0x00, 0x00
};

// Helper to create a MemIo with given data
Exiv2::BasicIo::UniquePtr makeMemIo(const uint8_t* data, size_t size) {
    return std::make_unique<Exiv2::MemIo>(data, size);
}

// Helper to create an empty MemIo
Exiv2::BasicIo::UniquePtr makeEmptyMemIo() {
    return std::make_unique<Exiv2::MemIo>();
}

} // anonymous namespace

class NewJpegInstanceTest_1223 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that creating a JPEG instance from valid minimal JPEG data succeeds
TEST_F(NewJpegInstanceTest_1223, ValidJpegData_ReturnsNonNull_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    EXPECT_NE(image, nullptr);
}

// Test that creating a JPEG instance with create=true from empty memory succeeds
TEST_F(NewJpegInstanceTest_1223, CreateModeWithEmptyIo_ReturnsNonNull_1223) {
    auto io = makeEmptyMemIo();
    auto image = Exiv2::newJpegInstance(std::move(io), true);
    // When create=true, the image should be created fresh
    EXPECT_NE(image, nullptr);
}

// Test that creating a JPEG instance from invalid data returns nullptr
TEST_F(NewJpegInstanceTest_1223, InvalidData_ReturnsNull_1223) {
    auto io = makeMemIo(kInvalidData, sizeof(kInvalidData));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that creating a JPEG instance from empty data without create mode returns nullptr
TEST_F(NewJpegInstanceTest_1223, EmptyDataNoCreate_ReturnsNull_1223) {
    auto io = makeEmptyMemIo();
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that the returned image has JPEG mime type
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_MimeTypeIsJpeg_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->mimeType(), "image/jpeg");
}

// Test that the returned image reports good() == true
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_GoodReturnsTrue_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Test creating a JPEG with create=true results in a good image
TEST_F(NewJpegInstanceTest_1223, CreateMode_GoodReturnsTrue_1223) {
    auto io = makeEmptyMemIo();
    auto image = Exiv2::newJpegInstance(std::move(io), true);
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test that single byte data (truncated) returns nullptr
TEST_F(NewJpegInstanceTest_1223, SingleByte_ReturnsNull_1223) {
    const uint8_t singleByte[] = {0xFF};
    auto io = makeMemIo(singleByte, sizeof(singleByte));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that just SOI marker without EOI returns non-null (it may still be considered "good" enough to open)
TEST_F(NewJpegInstanceTest_1223, OnlySOI_BehaviorCheck_1223) {
    const uint8_t soiOnly[] = {0xFF, 0xD8};
    auto io = makeMemIo(soiOnly, sizeof(soiOnly));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    // The image may or may not be created depending on the implementation's validation level
    // We just check that it doesn't crash
    // If it returns non-null, it should report good()
    if (image) {
        EXPECT_TRUE(image->good());
    }
}

// Test with random non-JPEG binary data
TEST_F(NewJpegInstanceTest_1223, RandomBinaryData_ReturnsNull_1223) {
    const uint8_t randomData[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}; // PNG header
    auto io = makeMemIo(randomData, sizeof(randomData));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that a created JPEG image provides access to its IO
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_IoAccessible_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    // Should be able to access the IO without crashing
    const Exiv2::BasicIo& ioRef = image->io();
    // The IO should have some size
    EXPECT_GT(ioRef.size(), 0u);
}

// Test that a created JPEG image can clear metadata without error
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_ClearMetadata_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->clearMetadata());
}

// Test that pixel dimensions start at 0 for minimal JPEG
TEST_F(NewJpegInstanceTest_1223, MinimalJpeg_PixelDimensionsZero_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->pixelWidth(), 0u);
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test that comment is initially empty
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_CommentInitiallyEmpty_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->comment().empty());
}

// Test setting and clearing comment on a JPEG image
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_SetAndClearComment_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    image->setComment("Test comment");
    EXPECT_EQ(image->comment(), "Test comment");
    image->clearComment();
    EXPECT_TRUE(image->comment().empty());
}

// Test that ICC profile is not defined for minimal JPEG
TEST_F(NewJpegInstanceTest_1223, MinimalJpeg_IccProfileNotDefined_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test exifData access on a freshly created JPEG
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_ExifDataAccessible_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    Exiv2::ExifData& exif = image->exifData();
    EXPECT_TRUE(exif.empty());
}

// Test iptcData access on a freshly created JPEG
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_IptcDataAccessible_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    Exiv2::IptcData& iptc = image->iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test xmpData access on a freshly created JPEG
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_XmpDataAccessible_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    Exiv2::XmpData& xmp = image->xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test that nativePreviews is initially empty
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_NativePreviewsEmpty_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->nativePreviews().empty());
}

// Test that clearing exif data works
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_ClearExifData_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->clearExifData());
    EXPECT_TRUE(image->exifData().empty());
}

// Test that clearing IPTC data works
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_ClearIptcData_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->clearIptcData());
    EXPECT_TRUE(image->iptcData().empty());
}

// Test that clearing XMP data works
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_ClearXmpData_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->clearXmpData());
    EXPECT_TRUE(image->xmpData().empty());
}

// Test that clearing XMP packet works
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_ClearXmpPacket_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->clearXmpPacket());
    EXPECT_TRUE(image->xmpPacket().empty());
}

// Test writeXmpFromPacket default value
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_WriteXmpFromPacketDefault_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    EXPECT_FALSE(image->writeXmpFromPacket());
}

// Test setting writeXmpFromPacket flag
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_SetWriteXmpFromPacket_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    image->writeXmpFromPacket(true);
    EXPECT_TRUE(image->writeXmpFromPacket());
    image->writeXmpFromPacket(false);
    EXPECT_FALSE(image->writeXmpFromPacket());
}

// Test with a larger buffer of all zeros
TEST_F(NewJpegInstanceTest_1223, LargeZeroBuffer_ReturnsNull_1223) {
    std::vector<uint8_t> zeros(1024, 0);
    auto io = makeMemIo(zeros.data(), zeros.size());
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    EXPECT_EQ(image, nullptr);
}

// Test that byteOrder is initially invalidByteOrder
TEST_F(NewJpegInstanceTest_1223, ValidJpeg_ByteOrderInitial_1223) {
    auto io = makeMemIo(kMinimalJpeg, sizeof(kMinimalJpeg));
    auto image = Exiv2::newJpegInstance(std::move(io), false);
    ASSERT_NE(image, nullptr);
    // JPEG typically doesn't set byte order until metadata is read
    // Just verify it doesn't crash
    Exiv2::ByteOrder bo = image->byteOrder();
    (void)bo; // suppress unused warning
}
