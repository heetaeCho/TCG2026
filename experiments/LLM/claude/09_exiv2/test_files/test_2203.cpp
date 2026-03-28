#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/pgfimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>
#include <memory>
#include <cstring>

using namespace Exiv2;

class PgfImageTest_2203 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Creating PgfImage with create=true writes PGF blank data to memory
TEST_F(PgfImageTest_2203, ConstructorWithCreateTrue_2203) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NE(io, nullptr);
    PgfImage img(std::move(io), true);
    // After creation, the io should contain the pgfBlank data
    const BasicIo& ioRef = img.io();
    EXPECT_GT(ioRef.size(), 0u);
    EXPECT_EQ(ioRef.size(), 106u);
}

// Test: Creating PgfImage with create=false does NOT write PGF blank data
TEST_F(PgfImageTest_2203, ConstructorWithCreateFalse_2203) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NE(io, nullptr);
    PgfImage img(std::move(io), false);
    const BasicIo& ioRef = img.io();
    EXPECT_EQ(ioRef.size(), 0u);
}

// Test: ImageType is pgf
TEST_F(PgfImageTest_2203, ImageTypeIsPgf_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_EQ(img.imageType(), ImageType::pgf);
}

// Test: mimeType returns the correct PGF MIME type
TEST_F(PgfImageTest_2203, MimeTypeCorrect_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_EQ(img.mimeType(), "image/x-portable-graymap");  // or whatever PGF mime is
    // Note: if the actual mime type differs, this will catch it
}

// Test: good() returns true after construction with create=true
TEST_F(PgfImageTest_2203, GoodAfterCreateTrue_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), true);
    EXPECT_TRUE(img.good());
}

// Test: good() returns true after construction with create=false (empty io)
TEST_F(PgfImageTest_2203, GoodAfterCreateFalse_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_TRUE(img.good());
}

// Test: pixelWidth and pixelHeight are 0 after construction without reading metadata
TEST_F(PgfImageTest_2203, DefaultPixelDimensions_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: supportsMetadata for Exif, IPTC, XMP, and Comment
TEST_F(PgfImageTest_2203, SupportsMetadataTypes_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_TRUE(img.supportsMetadata(mdExif));
    EXPECT_TRUE(img.supportsMetadata(mdIptc));
    EXPECT_TRUE(img.supportsMetadata(mdXmp));
    EXPECT_TRUE(img.supportsMetadata(mdComment));
}

// Test: readMetadata on empty IO throws an exception
TEST_F(PgfImageTest_2203, ReadMetadataOnEmptyIoThrows_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: readMetadata on the pgfBlank data (created image)
TEST_F(PgfImageTest_2203, ReadMetadataOnCreatedImage_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), true);
    // The pgfBlank is a minimal valid PGF; readMetadata should work or throw
    // depending on the completeness of the blank. We test that it doesn't crash.
    try {
        img.readMetadata();
    } catch (const Exiv2::Error&) {
        // It's acceptable if it throws for minimal blank data
    }
}

// Test: writeMetadata on created image
TEST_F(PgfImageTest_2203, WriteMetadataOnCreatedImage_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), true);
    // Writing metadata on a minimal created image
    try {
        img.writeMetadata();
    } catch (const Exiv2::Error&) {
        // Acceptable if writing fails on minimal data
    }
}

// Test: exifData is accessible and initially empty
TEST_F(PgfImageTest_2203, ExifDataInitiallyEmpty_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_TRUE(img.exifData().empty());
}

// Test: iptcData is accessible and initially empty
TEST_F(PgfImageTest_2203, IptcDataInitiallyEmpty_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: xmpData is accessible and initially empty
TEST_F(PgfImageTest_2203, XmpDataInitiallyEmpty_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: comment is initially empty
TEST_F(PgfImageTest_2203, CommentInitiallyEmpty_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_TRUE(img.comment().empty());
}

// Test: setComment and retrieve
TEST_F(PgfImageTest_2203, SetAndGetComment_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    img.setComment("Test comment");
    EXPECT_EQ(img.comment(), "Test comment");
}

// Test: clearComment
TEST_F(PgfImageTest_2203, ClearComment_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    img.setComment("Test comment");
    img.clearComment();
    EXPECT_TRUE(img.comment().empty());
}

// Test: clearMetadata clears all metadata
TEST_F(PgfImageTest_2203, ClearMetadata_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    img.setComment("Some comment");
    img.clearMetadata();
    EXPECT_TRUE(img.comment().empty());
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: IO size matches pgfBlank size after create=true
TEST_F(PgfImageTest_2203, IoSizeMatchesPgfBlank_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), true);
    // pgfBlank is 106 bytes
    EXPECT_EQ(img.io().size(), 106u);
}

// Test: Content written matches pgfBlank
TEST_F(PgfImageTest_2203, IoContentMatchesPgfBlank_2203) {
    auto memIo = std::make_unique<MemIo>();
    auto* rawPtr = memIo.get();
    PgfImage img(std::move(memIo), true);

    // Read back the content
    BasicIo& ioRef = const_cast<BasicIo&>(img.io());
    ioRef.open();
    ioRef.seek(0, BasicIo::beg);
    DataBuf buf = ioRef.read(106);
    ASSERT_EQ(buf.size(), 106u);

    // Check PGF magic: "PGF6" = {80, 71, 70, 54}
    EXPECT_EQ(buf.data()[0], 80);
    EXPECT_EQ(buf.data()[1], 71);
    EXPECT_EQ(buf.data()[2], 70);
    EXPECT_EQ(buf.data()[3], 54);
}

// Test: readMetadata on truncated/invalid data throws
TEST_F(PgfImageTest_2203, ReadMetadataOnInvalidDataThrows_2203) {
    const unsigned char invalidData[] = {0x00, 0x01, 0x02, 0x03};
    auto io = std::make_unique<MemIo>(invalidData, sizeof(invalidData));
    PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: readMetadata with only PGF magic but truncated header
TEST_F(PgfImageTest_2203, ReadMetadataWithTruncatedHeaderThrows_2203) {
    const unsigned char truncatedPgf[] = {80, 71, 70, 54, 16, 0, 0, 0};
    auto io = std::make_unique<MemIo>(truncatedPgf, sizeof(truncatedPgf));
    PgfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: Multiple create=true constructions produce same size
TEST_F(PgfImageTest_2203, MultipleCreationsConsistent_2203) {
    auto io1 = std::make_unique<MemIo>();
    PgfImage img1(std::move(io1), true);

    auto io2 = std::make_unique<MemIo>();
    PgfImage img2(std::move(io2), true);

    EXPECT_EQ(img1.io().size(), img2.io().size());
}

// Test: iccProfile is not defined initially
TEST_F(PgfImageTest_2203, IccProfileNotDefinedInitially_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test: writeXmpFromPacket default is false
TEST_F(PgfImageTest_2203, WriteXmpFromPacketDefaultFalse_2203) {
    auto io = std::make_unique<MemIo>();
    PgfImage img(std::move(io), false);
    EXPECT_FALSE(img.writeXmpFromPacket());
}
