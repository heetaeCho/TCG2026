#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

namespace {

// Helper to create a minimal valid JPEG file for testing
std::string createTempJpegFile(const std::string& filename) {
    // Minimal JPEG: SOI marker + EOI marker
    const unsigned char minimalJpeg[] = {
        0xFF, 0xD8, // SOI
        0xFF, 0xD9  // EOI
    };
    std::ofstream ofs(filename, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(minimalJpeg), sizeof(minimalJpeg));
    ofs.close();
    return filename;
}

void removeTempFile(const std::string& filename) {
    std::remove(filename.c_str());
}

class ExifThumbTest_770 : public ::testing::Test {
protected:
    Exiv2::ExifData exifData;

    void SetUp() override {
        // ExifData starts empty
    }

    void TearDown() override {
    }
};

// Test: Constructing ExifThumb from ExifData does not throw
TEST_F(ExifThumbTest_770, Construction_770) {
    EXPECT_NO_THROW(Exiv2::ExifThumb thumb(exifData));
}

// Test: setJpegThumbnail with a valid file path (4-arg version with resolution)
TEST_F(ExifThumbTest_770, SetJpegThumbnailFromFileWithResolution_770) {
    std::string tempFile = "test_thumb_770.jpg";
    createTempJpegFile(tempFile);

    Exiv2::ExifThumb thumb(exifData);
    Exiv2::URational xres = {72, 1};
    Exiv2::URational yres = {72, 1};
    uint16_t unit = 2; // inches

    EXPECT_NO_THROW(thumb.setJpegThumbnail(tempFile, xres, yres, unit));

    removeTempFile(tempFile);
}

// Test: setJpegThumbnail with a valid file path (1-arg version, no resolution)
TEST_F(ExifThumbTest_770, SetJpegThumbnailFromFile_770) {
    std::string tempFile = "test_thumb2_770.jpg";
    createTempJpegFile(tempFile);

    Exiv2::ExifThumb thumb(exifData);

    EXPECT_NO_THROW(thumb.setJpegThumbnail(tempFile));

    removeTempFile(tempFile);
}

// Test: setJpegThumbnail with a buffer (4-arg version with resolution)
TEST_F(ExifThumbTest_770, SetJpegThumbnailFromBufferWithResolution_770) {
    const unsigned char jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    Exiv2::ExifThumb thumb(exifData);
    Exiv2::URational xres = {72, 1};
    Exiv2::URational yres = {72, 1};
    uint16_t unit = 2;

    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData, sizeof(jpegData), xres, yres, unit));
}

// Test: setJpegThumbnail with a buffer (2-arg version, no resolution)
TEST_F(ExifThumbTest_770, SetJpegThumbnailFromBuffer_770) {
    const unsigned char jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    Exiv2::ExifThumb thumb(exifData);

    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData, sizeof(jpegData)));
}

// Test: setJpegThumbnail with non-existent file should throw
TEST_F(ExifThumbTest_770, SetJpegThumbnailFromNonExistentFileThrows_770) {
    Exiv2::ExifThumb thumb(exifData);
    Exiv2::URational xres = {72, 1};
    Exiv2::URational yres = {72, 1};
    uint16_t unit = 2;

    EXPECT_THROW(thumb.setJpegThumbnail("nonexistent_file_770.jpg", xres, yres, unit), Exiv2::Error);
}

// Test: setJpegThumbnail with non-existent file (simple overload) should throw
TEST_F(ExifThumbTest_770, SetJpegThumbnailFromNonExistentFileSimpleThrows_770) {
    Exiv2::ExifThumb thumb(exifData);

    EXPECT_THROW(thumb.setJpegThumbnail("nonexistent_file2_770.jpg"), Exiv2::Error);
}

// Test: erase thumbnail from empty ExifData does not throw
TEST_F(ExifThumbTest_770, EraseOnEmptyExifData_770) {
    Exiv2::ExifThumb thumb(exifData);

    EXPECT_NO_THROW(thumb.erase());
}

// Test: Set thumbnail then erase it
TEST_F(ExifThumbTest_770, SetThenEraseThumbnail_770) {
    const unsigned char jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    Exiv2::ExifThumb thumb(exifData);

    thumb.setJpegThumbnail(jpegData, sizeof(jpegData));
    EXPECT_NO_THROW(thumb.erase());
}

// Test: setJpegThumbnail with zero-size buffer
TEST_F(ExifThumbTest_770, SetJpegThumbnailWithEmptyBuffer_770) {
    const unsigned char dummyByte = 0;
    Exiv2::ExifThumb thumb(exifData);

    // Setting a thumbnail with zero size - should not crash
    EXPECT_NO_THROW(thumb.setJpegThumbnail(&dummyByte, 0));
}

// Test: setJpegThumbnail with zero-size buffer and resolution
TEST_F(ExifThumbTest_770, SetJpegThumbnailWithEmptyBufferAndResolution_770) {
    const unsigned char dummyByte = 0;
    Exiv2::ExifThumb thumb(exifData);
    Exiv2::URational xres = {300, 1};
    Exiv2::URational yres = {300, 1};
    uint16_t unit = 2;

    EXPECT_NO_THROW(thumb.setJpegThumbnail(&dummyByte, 0, xres, yres, unit));
}

// Test: Setting thumbnail multiple times overwrites previous
TEST_F(ExifThumbTest_770, SetThumbnailMultipleTimes_770) {
    const unsigned char jpegData1[] = {0xFF, 0xD8, 0xFF, 0xD9};
    const unsigned char jpegData2[] = {0xFF, 0xD8, 0x00, 0x01, 0xFF, 0xD9};
    Exiv2::ExifThumb thumb(exifData);

    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData1, sizeof(jpegData1)));
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData2, sizeof(jpegData2)));
}

// Test: Different resolution units
TEST_F(ExifThumbTest_770, SetJpegThumbnailWithDifferentUnits_770) {
    const unsigned char jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    Exiv2::ExifThumb thumb(exifData);
    Exiv2::URational xres = {72, 1};
    Exiv2::URational yres = {72, 1};

    // Unit 1 = No absolute unit
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData, sizeof(jpegData), xres, yres, 1));

    // Unit 2 = Inch
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData, sizeof(jpegData), xres, yres, 2));

    // Unit 3 = Centimeter
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData, sizeof(jpegData), xres, yres, 3));
}

// Test: Verify that after setting thumbnail via file, ExifThumbC can read it back
TEST_F(ExifThumbTest_770, ThumbnailAccessibleAfterSet_770) {
    const unsigned char jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    Exiv2::ExifThumb thumb(exifData);
    Exiv2::URational xres = {72, 1};
    Exiv2::URational yres = {72, 1};

    thumb.setJpegThumbnail(jpegData, sizeof(jpegData), xres, yres, 2);

    // Use the const interface (ExifThumbC) to read back
    Exiv2::ExifThumbC thumbC(exifData);
    Exiv2::DataBuf buf = thumbC.copy();
    // The thumbnail should have been set, so buffer should not be empty
    EXPECT_FALSE(buf.empty());
    EXPECT_EQ(buf.size(), sizeof(jpegData));
}

// Test: After erase, thumbnail should be empty
TEST_F(ExifThumbTest_770, ThumbnailEmptyAfterErase_770) {
    const unsigned char jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    Exiv2::ExifThumb thumb(exifData);

    thumb.setJpegThumbnail(jpegData, sizeof(jpegData));
    thumb.erase();

    Exiv2::ExifThumbC thumbC(exifData);
    Exiv2::DataBuf buf = thumbC.copy();
    EXPECT_TRUE(buf.empty());
}

// Test: Large thumbnail buffer
TEST_F(ExifThumbTest_770, SetLargeThumbnailBuffer_770) {
    // Create a larger buffer that starts with JPEG SOI
    std::vector<unsigned char> largeJpeg(65536);
    largeJpeg[0] = 0xFF;
    largeJpeg[1] = 0xD8;
    largeJpeg[largeJpeg.size() - 2] = 0xFF;
    largeJpeg[largeJpeg.size() - 1] = 0xD9;

    Exiv2::ExifThumb thumb(exifData);
    EXPECT_NO_THROW(thumb.setJpegThumbnail(largeJpeg.data(), largeJpeg.size()));
}

// Test: Resolution with zero denominator
TEST_F(ExifThumbTest_770, SetThumbnailWithZeroDenominatorResolution_770) {
    const unsigned char jpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
    Exiv2::ExifThumb thumb(exifData);
    Exiv2::URational xres = {72, 0};
    Exiv2::URational yres = {72, 0};

    // This should still work; the class stores whatever rational is given
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData, sizeof(jpegData), xres, yres, 2));
}

}  // namespace
