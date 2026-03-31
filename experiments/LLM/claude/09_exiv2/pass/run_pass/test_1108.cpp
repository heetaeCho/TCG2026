#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <fstream>
#include <cstring>
#include <vector>

using namespace Exiv2;

// Helper to create a temporary file with given content
class TempFile {
public:
    TempFile(const std::string& name, const std::vector<byte>& content) : path_(name) {
        std::ofstream ofs(path_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
        }
        ofs.close();
    }
    ~TempFile() {
        std::remove(path_.c_str());
    }
    const std::string& path() const { return path_; }
private:
    std::string path_;
};

// Minimal JPEG: SOI marker + APP0 + EOI
static std::vector<byte> createMinimalJpeg() {
    // Minimal valid JPEG: FF D8 FF E0 00 02 FF D9
    return {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
            0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
            0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
            0x00, 0x00, 0xFF, 0xD9};
}

// ==================== Tests for ImageFactory::open (string path) ====================

class ImageFactoryOpenPathTest_1108 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ImageFactoryOpenPathTest_1108, OpenValidJpegFile_1108) {
    auto jpegData = createMinimalJpeg();
    TempFile tmp("test_valid_jpeg_1108.jpg", jpegData);
    
    EXPECT_NO_THROW({
        auto image = ImageFactory::open(tmp.path());
        ASSERT_NE(image, nullptr);
    });
}

TEST_F(ImageFactoryOpenPathTest_1108, OpenNonExistentFileThrows_1108) {
    EXPECT_THROW({
        auto image = ImageFactory::open("/nonexistent/path/to/file_1108.jpg");
    }, Error);
}

TEST_F(ImageFactoryOpenPathTest_1108, OpenEmptyFileThrows_1108) {
    TempFile tmp("test_empty_1108.dat", {});
    
    EXPECT_THROW({
        auto image = ImageFactory::open(tmp.path());
    }, Error);
}

TEST_F(ImageFactoryOpenPathTest_1108, OpenUnknownImageTypeThrows_1108) {
    std::vector<byte> randomData = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                     0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
    TempFile tmp("test_unknown_1108.dat", randomData);
    
    EXPECT_THROW({
        auto image = ImageFactory::open(tmp.path());
    }, Error);
}

// ==================== Tests for ImageFactory::open (byte* data, size_t size) ====================

class ImageFactoryOpenDataTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryOpenDataTest_1108, OpenValidJpegFromMemory_1108) {
    auto jpegData = createMinimalJpeg();
    
    EXPECT_NO_THROW({
        auto image = ImageFactory::open(jpegData.data(), jpegData.size());
        ASSERT_NE(image, nullptr);
    });
}

TEST_F(ImageFactoryOpenDataTest_1108, OpenUnknownDataThrows_1108) {
    std::vector<byte> randomData = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    
    EXPECT_THROW({
        auto image = ImageFactory::open(randomData.data(), randomData.size());
    }, Error);
}

TEST_F(ImageFactoryOpenDataTest_1108, OpenEmptyDataThrows_1108) {
    EXPECT_THROW({
        auto image = ImageFactory::open(static_cast<const byte*>(nullptr), 0);
    }, Error);
}

TEST_F(ImageFactoryOpenDataTest_1108, OpenSingleByteDataThrows_1108) {
    byte singleByte = 0xFF;
    EXPECT_THROW({
        auto image = ImageFactory::open(&singleByte, 1);
    }, Error);
}

// ==================== Tests for ImageFactory::open (BasicIo::UniquePtr) ====================

class ImageFactoryOpenIoTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryOpenIoTest_1108, OpenValidJpegViaIo_1108) {
    auto jpegData = createMinimalJpeg();
    TempFile tmp("test_io_jpeg_1108.jpg", jpegData);
    
    auto io = ImageFactory::createIo(tmp.path(), false);
    ASSERT_NE(io, nullptr);
    
    EXPECT_NO_THROW({
        auto image = ImageFactory::open(std::move(io));
        ASSERT_NE(image, nullptr);
    });
}

TEST_F(ImageFactoryOpenIoTest_1108, OpenMemoryIoWithValidJpeg_1108) {
    auto jpegData = createMinimalJpeg();
    auto io = std::make_unique<MemIo>(jpegData.data(), jpegData.size());
    
    EXPECT_NO_THROW({
        auto image = ImageFactory::open(std::move(io));
        ASSERT_NE(image, nullptr);
    });
}

TEST_F(ImageFactoryOpenIoTest_1108, OpenMemoryIoWithInvalidData_1108) {
    std::vector<byte> invalidData = {0x00, 0x01, 0x02, 0x03};
    auto io = std::make_unique<MemIo>(invalidData.data(), invalidData.size());
    
    EXPECT_THROW({
        auto image = ImageFactory::open(std::move(io));
    }, Error);
}

// ==================== Tests for ImageFactory::getType ====================

class ImageFactoryGetTypeTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryGetTypeTest_1108, GetTypeFromJpegFile_1108) {
    auto jpegData = createMinimalJpeg();
    TempFile tmp("test_gettype_jpeg_1108.jpg", jpegData);
    
    ImageType type = ImageFactory::getType(tmp.path());
    EXPECT_EQ(type, ImageType::jpeg);
}

TEST_F(ImageFactoryGetTypeTest_1108, GetTypeFromJpegMemory_1108) {
    auto jpegData = createMinimalJpeg();
    
    ImageType type = ImageFactory::getType(jpegData.data(), jpegData.size());
    EXPECT_EQ(type, ImageType::jpeg);
}

TEST_F(ImageFactoryGetTypeTest_1108, GetTypeFromUnknownData_1108) {
    std::vector<byte> unknownData = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    
    EXPECT_THROW({
        ImageFactory::getType(unknownData.data(), unknownData.size());
    }, Error);
}

TEST_F(ImageFactoryGetTypeTest_1108, GetTypeFromNonExistentFile_1108) {
    EXPECT_THROW({
        ImageFactory::getType("/does/not/exist_1108.jpg");
    }, Error);
}

// ==================== Tests for ImageFactory::create ====================

class ImageFactoryCreateTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryCreateTest_1108, CreateJpegImage_1108) {
    TempFile tmp("test_create_jpeg_1108.jpg", {});
    
    EXPECT_NO_THROW({
        auto image = ImageFactory::create(ImageType::jpeg, tmp.path());
        ASSERT_NE(image, nullptr);
    });
}

TEST_F(ImageFactoryCreateTest_1108, CreateExvImage_1108) {
    TempFile tmp("test_create_exv_1108.exv", {});
    
    EXPECT_NO_THROW({
        auto image = ImageFactory::create(ImageType::exv, tmp.path());
        ASSERT_NE(image, nullptr);
    });
}

TEST_F(ImageFactoryCreateTest_1108, CreateWithMemoryIo_1108) {
    EXPECT_NO_THROW({
        auto image = ImageFactory::create(ImageType::jpeg);
        ASSERT_NE(image, nullptr);
    });
}

// ==================== Tests for ImageFactory::checkMode ====================

class ImageFactoryCheckModeTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryCheckModeTest_1108, JpegExifSupportIsReadWrite_1108) {
    AccessMode mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdExif);
    EXPECT_EQ(mode, amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1108, JpegIptcSupportIsReadWrite_1108) {
    AccessMode mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdIptc);
    EXPECT_EQ(mode, amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1108, JpegXmpSupportIsReadWrite_1108) {
    AccessMode mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdXmp);
    EXPECT_EQ(mode, amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1108, JpegCommentSupportIsReadWrite_1108) {
    AccessMode mode = ImageFactory::checkMode(ImageType::jpeg, MetadataId::mdComment);
    EXPECT_EQ(mode, amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1108, CrwIptcSupportIsNone_1108) {
    AccessMode mode = ImageFactory::checkMode(ImageType::crw, MetadataId::mdIptc);
    EXPECT_EQ(mode, amNone);
}

TEST_F(ImageFactoryCheckModeTest_1108, MrwExifSupportIsRead_1108) {
    AccessMode mode = ImageFactory::checkMode(ImageType::mrw, MetadataId::mdExif);
    EXPECT_EQ(mode, amRead);
}

TEST_F(ImageFactoryCheckModeTest_1108, GifExifSupportIsNone_1108) {
    AccessMode mode = ImageFactory::checkMode(ImageType::gif, MetadataId::mdExif);
    EXPECT_EQ(mode, amNone);
}

TEST_F(ImageFactoryCheckModeTest_1108, TgaAllSupportIsNone_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::tga, MetadataId::mdExif), amNone);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::tga, MetadataId::mdIptc), amNone);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::tga, MetadataId::mdXmp), amNone);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::tga, MetadataId::mdComment), amNone);
}

TEST_F(ImageFactoryCheckModeTest_1108, BmpAllSupportIsNone_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::bmp, MetadataId::mdExif), amNone);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::bmp, MetadataId::mdIptc), amNone);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::bmp, MetadataId::mdXmp), amNone);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::bmp, MetadataId::mdComment), amNone);
}

TEST_F(ImageFactoryCheckModeTest_1108, EpsOnlyXmpReadWrite_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::eps, MetadataId::mdExif), amNone);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::eps, MetadataId::mdIptc), amNone);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::eps, MetadataId::mdXmp), amReadWrite);
    EXPECT_EQ(ImageFactory::checkMode(ImageType::eps, MetadataId::mdComment), amNone);
}

TEST_F(ImageFactoryCheckModeTest_1108, Cr2CommentSupportIsNone_1108) {
    AccessMode mode = ImageFactory::checkMode(ImageType::cr2, MetadataId::mdComment);
    EXPECT_EQ(mode, amNone);
}

TEST_F(ImageFactoryCheckModeTest_1108, WebPExifIsReadWrite_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::webp, MetadataId::mdExif), amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1108, WebPIptcIsNone_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::webp, MetadataId::mdIptc), amNone);
}

TEST_F(ImageFactoryCheckModeTest_1108, WebPXmpIsReadWrite_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::webp, MetadataId::mdXmp), amReadWrite);
}

// ==================== Tests for ImageFactory::createIo ====================

class ImageFactoryCreateIoTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryCreateIoTest_1108, CreateIoForExistingFile_1108) {
    auto jpegData = createMinimalJpeg();
    TempFile tmp("test_createio_1108.jpg", jpegData);
    
    auto io = ImageFactory::createIo(tmp.path(), false);
    ASSERT_NE(io, nullptr);
}

TEST_F(ImageFactoryCreateIoTest_1108, CreateIoForNonExistentPath_1108) {
    // createIo should still return an io object (FileIo), even if the file doesn't exist yet
    auto io = ImageFactory::createIo("/tmp/nonexistent_createio_test_1108.dat", false);
    ASSERT_NE(io, nullptr);
}

// ==================== Tests for ImageFactory::checkType ====================

class ImageFactoryCheckTypeTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryCheckTypeTest_1108, CheckTypeJpegWithJpegData_1108) {
    auto jpegData = createMinimalJpeg();
    MemIo memIo(jpegData.data(), jpegData.size());
    memIo.open();
    
    bool result = ImageFactory::checkType(ImageType::jpeg, memIo, false);
    EXPECT_TRUE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1108, CheckTypeJpegWithNonJpegData_1108) {
    std::vector<byte> nonJpeg = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};  // PNG header
    MemIo memIo(nonJpeg.data(), nonJpeg.size());
    memIo.open();
    
    bool result = ImageFactory::checkType(ImageType::jpeg, memIo, false);
    EXPECT_FALSE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1108, CheckTypePngWithPngData_1108) {
    // Minimal PNG signature
    std::vector<byte> pngData = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
                                  // IHDR chunk
                                  0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
                                  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
                                  0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53,
                                  0xDE};
    MemIo memIo(pngData.data(), pngData.size());
    memIo.open();
    
    bool result = ImageFactory::checkType(ImageType::png, memIo, false);
    EXPECT_TRUE(result);
}

// ==================== Roundtrip test ====================

class ImageFactoryRoundtripTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryRoundtripTest_1108, OpenJpegAndReadMetadata_1108) {
    auto jpegData = createMinimalJpeg();
    TempFile tmp("test_roundtrip_1108.jpg", jpegData);
    
    auto image = ImageFactory::open(tmp.path());
    ASSERT_NE(image, nullptr);
    
    EXPECT_NO_THROW({
        image->readMetadata();
    });
}

TEST_F(ImageFactoryRoundtripTest_1108, CreateJpegAndWriteMetadata_1108) {
    std::string path = "/tmp/test_create_write_1108.jpg";
    
    auto image = ImageFactory::create(ImageType::jpeg, path);
    ASSERT_NE(image, nullptr);
    
    EXPECT_NO_THROW({
        image->writeMetadata();
    });
    
    std::remove(path.c_str());
}

// ==================== Tests for PGF support ====================

class ImageFactoryPgfSupportTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryPgfSupportTest_1108, PgfCommentSupportIsReadWrite_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::pgf, MetadataId::mdComment), amReadWrite);
}

TEST_F(ImageFactoryPgfSupportTest_1108, PgfExifSupportIsReadWrite_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::pgf, MetadataId::mdExif), amReadWrite);
}

// ==================== Tests for RAF support ====================

class ImageFactoryRafSupportTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryRafSupportTest_1108, RafExifIsRead_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::raf, MetadataId::mdExif), amRead);
}

TEST_F(ImageFactoryRafSupportTest_1108, RafCommentIsNone_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::raf, MetadataId::mdComment), amNone);
}

// ==================== Tests for BMFF support ====================

class ImageFactoryBmffSupportTest_1108 : public ::testing::Test {};

TEST_F(ImageFactoryBmffSupportTest_1108, BmffExifIsRead_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::bmff, MetadataId::mdExif), amRead);
}

TEST_F(ImageFactoryBmffSupportTest_1108, BmffCommentIsNone_1108) {
    EXPECT_EQ(ImageFactory::checkMode(ImageType::bmff, MetadataId::mdComment), amNone);
}

// ==================== Edge case: open with byte data of size 0 ====================

TEST(ImageFactoryEdgeCaseTest_1108, OpenZeroSizeDataThrows_1108) {
    byte dummy = 0;
    EXPECT_THROW({
        ImageFactory::open(&dummy, 0);
    }, Error);
}
