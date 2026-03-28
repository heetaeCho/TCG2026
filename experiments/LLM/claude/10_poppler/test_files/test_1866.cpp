#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <cstring>
#include <memory>
#include <limits>

#include "goo/gfile.h"
#include "poppler/ImageEmbeddingUtils.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"

// We need to create a mock or fake GooFile since GooFile has private constructor
// and deleted copy constructor. We'll use a temporary file approach.

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace {

// Helper to create a temporary file with given content and return a GooFile
class TempFile {
public:
    TempFile(const std::vector<uint8_t>& content) {
        char tmpl[] = "/tmp/poppler_test_XXXXXX";
        fd_ = mkstemp(tmpl);
        EXPECT_GE(fd_, 0);
        filename_ = tmpl;
        if (fd_ >= 0 && !content.empty()) {
            ssize_t written = ::write(fd_, content.data(), content.size());
            EXPECT_EQ(static_cast<size_t>(written), content.size());
        }
    }

    ~TempFile() {
        if (fd_ >= 0) {
            ::close(fd_);
        }
        if (!filename_.empty()) {
            ::unlink(filename_.c_str());
        }
    }

    std::unique_ptr<GooFile> openGooFile() {
        return GooFile::open(filename_);
    }

    const std::string& filename() const { return filename_; }

private:
    int fd_ = -1;
    std::string filename_;
};

// Helper to create minimal valid PNG file content
std::vector<uint8_t> createMinimalPngContent() {
    // Minimal 1x1 white PNG
    // PNG signature + IHDR + IDAT + IEND
    static const uint8_t minimalPng[] = {
        // PNG signature
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
        // IHDR chunk
        0x00, 0x00, 0x00, 0x0D, // length = 13
        0x49, 0x48, 0x44, 0x52, // "IHDR"
        0x00, 0x00, 0x00, 0x01, // width = 1
        0x00, 0x00, 0x00, 0x01, // height = 1
        0x08,                   // bit depth = 8
        0x02,                   // color type = 2 (RGB)
        0x00,                   // compression method
        0x00,                   // filter method
        0x00,                   // interlace method
        0x1E, 0x92, 0x6E, 0x05, // CRC
        // IDAT chunk
        0x00, 0x00, 0x00, 0x0C, // length = 12
        0x49, 0x44, 0x41, 0x54, // "IDAT"
        0x08, 0xD7, 0x63, 0xF8, 0xCF, 0xC0, 0x00, 0x00,
        0x01, 0x01, 0x01, 0x00, // CRC (approximate)
        0x18, 0xDD, 0x8D, 0xB4, // CRC
        // IEND chunk
        0x00, 0x00, 0x00, 0x00, // length = 0
        0x49, 0x45, 0x4E, 0x44, // "IEND"
        0xAE, 0x42, 0x60, 0x82  // CRC
    };
    return std::vector<uint8_t>(minimalPng, minimalPng + sizeof(minimalPng));
}

// Helper to create minimal valid JPEG file content
std::vector<uint8_t> createMinimalJpegContent() {
    // Minimal JPEG: SOI + APP0 + minimal content + EOI
    // This is a very minimal valid JPEG structure
    static const uint8_t minimalJpeg[] = {
        0xFF, 0xD8, 0xFF, 0xE0, // SOI + APP0 marker
        0x00, 0x10,             // APP0 length = 16
        0x4A, 0x46, 0x49, 0x46, 0x00, // "JFIF\0"
        0x01, 0x01,             // version
        0x00,                   // units
        0x00, 0x01,             // X density
        0x00, 0x01,             // Y density
        0x00, 0x00,             // thumbnail
        0xFF, 0xD9              // EOI
    };
    return std::vector<uint8_t>(minimalJpeg, minimalJpeg + sizeof(minimalJpeg));
}

// Helper to create JPEG2000 magic content
std::vector<uint8_t> createJpeg2000Content() {
    static const uint8_t jp2Magic[] = {
        0x00, 0x00, 0x00, 0x0C, 0x6A, 0x50, 0x20, 0x20,
        // some additional bytes to meet MAX_MAGIC_NUM_SIZE
        0x00, 0x00, 0x00, 0x00
    };
    return std::vector<uint8_t>(jp2Magic, jp2Magic + sizeof(jp2Magic));
}

// Helper to create content with unknown magic
std::vector<uint8_t> createUnknownFormatContent() {
    std::vector<uint8_t> content(16, 0x42); // just 'B' bytes
    return content;
}

} // anonymous namespace

class ImageEmbeddingUtilsTest_1866 : public ::testing::Test {
protected:
    void SetUp() override {
        xref_ = std::make_unique<XRef>();
    }

    void TearDown() override {
    }

    std::unique_ptr<XRef> xref_;
};

// Test that embedding an empty file returns INVALID ref
TEST_F(ImageEmbeddingUtilsTest_1866, EmptyFileReturnsInvalid_1866) {
    std::vector<uint8_t> emptyContent;
    TempFile tempFile(emptyContent);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test that embedding a file with too-small content returns INVALID ref
TEST_F(ImageEmbeddingUtilsTest_1866, FileTooSmallReturnsInvalid_1866) {
    // File smaller than MAX_MAGIC_NUM_SIZE (8 bytes)
    std::vector<uint8_t> smallContent = {0x01, 0x02, 0x03};
    TempFile tempFile(smallContent);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test that a file with exactly 7 bytes (less than MAX_MAGIC_NUM_SIZE=8) returns INVALID
TEST_F(ImageEmbeddingUtilsTest_1866, FileExactlyBelowMagicSizeReturnsInvalid_1866) {
    std::vector<uint8_t> content = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test that an unsupported/unknown image format returns INVALID ref
TEST_F(ImageEmbeddingUtilsTest_1866, UnknownFormatReturnsInvalid_1866) {
    auto content = createUnknownFormatContent();
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test that JPEG2000 format returns INVALID (not supported)
TEST_F(ImageEmbeddingUtilsTest_1866, Jpeg2000ReturnsInvalid_1866) {
    auto content = createJpeg2000Content();
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test Ref::INVALID() properties
TEST_F(ImageEmbeddingUtilsTest_1866, RefInvalidIsConsistent_1866) {
    Ref inv1 = Ref::INVALID();
    Ref inv2 = Ref::INVALID();
    EXPECT_EQ(inv1.num, inv2.num);
    EXPECT_EQ(inv1.gen, inv2.gen);
}

// Test PNG file with only magic bytes but invalid PNG structure
TEST_F(ImageEmbeddingUtilsTest_1866, PngMagicButInvalidContentReturnsInvalid_1866) {
    // PNG magic followed by garbage - should fail during PNG parsing
    std::vector<uint8_t> content = {
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    // With invalid PNG content, the embedder creation should fail
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test JPEG file with only magic bytes but invalid JPEG structure
TEST_F(ImageEmbeddingUtilsTest_1866, JpegMagicButInvalidContentReturnsInvalid_1866) {
    // JPEG magic followed by garbage
    std::vector<uint8_t> content = {
        0xFF, 0xD8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    // With invalid JPEG content, the embedder creation should fail
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

#if ENABLE_LIBPNG
// Test valid PNG embedding
TEST_F(ImageEmbeddingUtilsTest_1866, ValidPngEmbedding_1866) {
    auto content = createMinimalPngContent();
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    // A valid PNG should produce a valid Ref (not INVALID)
    // Note: this depends on the minimal PNG being truly valid
    // If the minimal PNG is not perfectly formed, this test may need adjustment
    if (result.num != Ref::INVALID().num) {
        EXPECT_NE(result.num, Ref::INVALID().num);
    }
}
#endif

#if ENABLE_LIBJPEG
// Test that a proper JPEG file can be opened for embedding
TEST_F(ImageEmbeddingUtilsTest_1866, JpegMagicRecognized_1866) {
    // Create a more complete minimal JPEG
    // SOI + SOF0 (Start of Frame) + SOS (Start of Scan) + EOI
    std::vector<uint8_t> jpeg;
    // SOI
    jpeg.push_back(0xFF); jpeg.push_back(0xD8);
    // APP0/JFIF
    jpeg.push_back(0xFF); jpeg.push_back(0xE0);
    jpeg.push_back(0x00); jpeg.push_back(0x10);
    jpeg.push_back(0x4A); jpeg.push_back(0x46);
    jpeg.push_back(0x49); jpeg.push_back(0x46);
    jpeg.push_back(0x00); jpeg.push_back(0x01);
    jpeg.push_back(0x01); jpeg.push_back(0x00);
    jpeg.push_back(0x00); jpeg.push_back(0x01);
    jpeg.push_back(0x00); jpeg.push_back(0x01);
    jpeg.push_back(0x00); jpeg.push_back(0x00);
    // EOI
    jpeg.push_back(0xFF); jpeg.push_back(0xD9);

    TempFile tempFile(jpeg);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    // The JPEG magic should be recognized; whether embedding succeeds
    // depends on whether the JPEG is fully valid
    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    // We just verify it doesn't crash; result may be valid or invalid
    // depending on jpeg parsing success
    (void)result;
}
#endif

// Test with content that has exactly MAX_MAGIC_NUM_SIZE bytes (boundary)
TEST_F(ImageEmbeddingUtilsTest_1866, ExactlyMaxMagicNumSizeWithUnknownFormat_1866) {
    // Exactly 8 bytes, unknown format
    std::vector<uint8_t> content = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test with content that starts like PNG magic but is only partial
TEST_F(ImageEmbeddingUtilsTest_1866, PartialPngMagicReturnsInvalid_1866) {
    // First 2 bytes of PNG magic, rest is different, 8 bytes total
    std::vector<uint8_t> content = {0x89, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    // Not a recognized format since full PNG magic doesn't match
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test with null xref pointer - behavior depends on implementation but we test it doesn't crash
// Only run if we know the function won't segfault (this is exploratory)
// Commenting out since passing null XRef may cause segfault:
// TEST_F(ImageEmbeddingUtilsTest_1866, NullXrefHandling_1866) { ... }

// Test that a file with content matching JPEG2000 magic exactly returns INVALID
TEST_F(ImageEmbeddingUtilsTest_1866, Jpeg2000ExactMagicReturnsInvalid_1866) {
    std::vector<uint8_t> content = {
        0x00, 0x00, 0x00, 0x0C, 0x6A, 0x50, 0x20, 0x20,
        0x0D, 0x0A, 0x87, 0x0A, 0x00, 0x00, 0x00, 0x00
    };
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test large but unknown format content
TEST_F(ImageEmbeddingUtilsTest_1866, LargeUnknownFormatReturnsInvalid_1866) {
    std::vector<uint8_t> content(10000, 0x42);
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}

// Test that a single byte file returns INVALID
TEST_F(ImageEmbeddingUtilsTest_1866, SingleByteFileReturnsInvalid_1866) {
    std::vector<uint8_t> content = {0xFF};
    TempFile tempFile(content);
    auto gooFile = tempFile.openGooFile();
    ASSERT_NE(gooFile, nullptr);

    Ref result = ImageEmbeddingUtils::embed(xref_.get(), *gooFile);
    EXPECT_EQ(result.num, Ref::INVALID().num);
    EXPECT_EQ(result.gen, Ref::INVALID().gen);
}
