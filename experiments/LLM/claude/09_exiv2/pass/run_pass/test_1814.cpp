#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/crwimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <memory>
#include <fstream>
#include <cstring>

using namespace Exiv2;

// Helper: create a MemIo with arbitrary (non-CRW) data
static std::unique_ptr<BasicIo> makeMemIoWithData(const std::vector<byte>& data) {
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    return io;
}

// Helper: create an empty MemIo
static std::unique_ptr<BasicIo> makeEmptyMemIo() {
    return std::make_unique<MemIo>();
}

// ============================================================
// Test fixture
// ============================================================
class CrwImageTest_1814 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ------------------------------------------------------------------
// Test: Construction with empty MemIo (create = true)
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ConstructWithEmptyIoCreateTrue_1814) {
    auto io = makeEmptyMemIo();
    ASSERT_NO_THROW(CrwImage img(std::move(io), true));
}

// ------------------------------------------------------------------
// Test: Construction with empty MemIo (create = false)
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ConstructWithEmptyIoCreateFalse_1814) {
    auto io = makeEmptyMemIo();
    ASSERT_NO_THROW(CrwImage img(std::move(io), false));
}

// ------------------------------------------------------------------
// Test: mimeType returns expected CRW MIME type
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, MimeTypeReturnsCrwMime_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    std::string mime = img.mimeType();
    EXPECT_EQ(mime, "image/x-canon-crw");
}

// ------------------------------------------------------------------
// Test: pixelWidth initially returns 0
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, PixelWidthInitiallyZero_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_EQ(img.pixelWidth(), 0u);
}

// ------------------------------------------------------------------
// Test: pixelHeight initially returns 0
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, PixelHeightInitiallyZero_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// ------------------------------------------------------------------
// Test: setIptcData does not throw (CRW doesn't support IPTC, 
//       but the method should be callable)
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, SetIptcDataDoesNotThrow_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    IptcData iptc;
    EXPECT_NO_THROW(img.setIptcData(iptc));
}

// ------------------------------------------------------------------
// Test: readMetadata on empty MemIo should throw (not a CRW image)
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ReadMetadataEmptyIoThrows_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// ------------------------------------------------------------------
// Test: readMetadata on garbage data should throw
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ReadMetadataGarbageDataThrows_1814) {
    std::vector<byte> garbage(256, 0xAB);
    auto io = makeMemIoWithData(garbage);
    CrwImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// ------------------------------------------------------------------
// Test: readMetadata on small garbage data should throw
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ReadMetadataSmallGarbageThrows_1814) {
    std::vector<byte> small_data = {0x00, 0x01, 0x02, 0x03};
    auto io = makeMemIoWithData(small_data);
    CrwImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// ------------------------------------------------------------------
// Test: readMetadata with single byte throws
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ReadMetadataSingleByteThrows_1814) {
    std::vector<byte> one_byte = {0xFF};
    auto io = makeMemIoWithData(one_byte);
    CrwImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// ------------------------------------------------------------------
// Test: readMetadata throws the correct error code for non-CRW data
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ReadMetadataThrowsCorrectErrorCode_1814) {
    std::vector<byte> not_crw(512, 0x00);
    auto io = makeMemIoWithData(not_crw);
    CrwImage img(std::move(io), false);
    try {
        img.readMetadata();
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        // Should be either kerNotACrwImage or kerFailedToReadImageData
        EXPECT_TRUE(e.code() == ErrorCode::kerNotACrwImage ||
                    e.code() == ErrorCode::kerFailedToReadImageData);
    }
}

// ------------------------------------------------------------------
// Test: good() on freshly created CrwImage with MemIo
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, GoodOnFreshImage_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    // MemIo should be "good" even if empty
    EXPECT_TRUE(img.good());
}

// ------------------------------------------------------------------
// Test: exifData is initially empty
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ExifDataInitiallyEmpty_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_TRUE(img.exifData().empty());
}

// ------------------------------------------------------------------
// Test: comment is initially empty
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, CommentInitiallyEmpty_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_TRUE(img.comment().empty());
}

// ------------------------------------------------------------------
// Test: clearMetadata doesn't throw
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ClearMetadataNoThrow_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_NO_THROW(img.clearMetadata());
}

// ------------------------------------------------------------------
// Test: setExifData and clearExifData
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, SetAndClearExifData_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    ExifData exif;
    EXPECT_NO_THROW(img.setExifData(exif));
    EXPECT_NO_THROW(img.clearExifData());
    EXPECT_TRUE(img.exifData().empty());
}

// ------------------------------------------------------------------
// Test: setComment and clearComment
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, SetAndClearComment_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_NO_THROW(img.setComment("Test comment"));
    EXPECT_EQ(img.comment(), "Test comment");
    EXPECT_NO_THROW(img.clearComment());
    EXPECT_TRUE(img.comment().empty());
}

// ------------------------------------------------------------------
// Test: writeMetadata on empty MemIo should throw (no valid CRW data)
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, WriteMetadataEmptyIoThrows_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), false);
    EXPECT_THROW(img.writeMetadata(), Error);
}

// ------------------------------------------------------------------
// Test: io() returns a reference to the underlying IO object
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, IoReturnsValidReference_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_NO_THROW(img.io());
}

// ------------------------------------------------------------------
// Test: readMetadata with data that has CRW-like header but is truncated
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ReadMetadataTruncatedCrwHeaderThrows_1814) {
    // CRW files start with a CIFF header. 
    // Byte order mark (II = little endian) + HEAP magic
    // This is intentionally incomplete/corrupted
    std::vector<byte> partial_crw = {
        'I', 'I',        // Byte order
        0x1A, 0x00,      // Header length (26)
        'H', 'E', 'A', 'P',  // HEAP signature
        'C', 'C', 'D', 'R',  // CCDR type
        // Truncated - missing the rest
    };
    auto io = makeMemIoWithData(partial_crw);
    CrwImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// ------------------------------------------------------------------
// Test: Image type is CRW
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ImageTypeIsCrw_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_EQ(img.imageType(), ImageType::crw);
}

// ------------------------------------------------------------------
// Test: xmpData is initially empty
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, XmpDataInitiallyEmpty_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_TRUE(img.xmpData().empty());
}

// ------------------------------------------------------------------
// Test: iptcData is initially empty
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, IptcDataInitiallyEmpty_1814) {
    auto io = makeEmptyMemIo();
    CrwImage img(std::move(io), true);
    EXPECT_TRUE(img.iptcData().empty());
}

// ------------------------------------------------------------------
// Test: readMetadata with random large data (not CRW) should throw
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, ReadMetadataLargeRandomDataThrows_1814) {
    std::vector<byte> large_data(8192);
    for (size_t i = 0; i < large_data.size(); ++i) {
        large_data[i] = static_cast<byte>(i & 0xFF);
    }
    auto io = makeMemIoWithData(large_data);
    CrwImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// ------------------------------------------------------------------
// Test: writeMetadata on garbage data should throw
// ------------------------------------------------------------------
TEST_F(CrwImageTest_1814, WriteMetadataGarbageDataThrows_1814) {
    std::vector<byte> garbage(128, 0xCD);
    auto io = makeMemIoWithData(garbage);
    CrwImage img(std::move(io), false);
    EXPECT_THROW(img.writeMetadata(), Error);
}
