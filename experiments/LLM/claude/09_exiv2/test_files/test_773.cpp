#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <vector>
#include <cstring>

using namespace Exiv2;

class ExifThumbTest_773 : public ::testing::Test {
protected:
    ExifData exifData_;
};

// Test that setJpegThumbnail sets the Compression tag to 6 (JPEG)
TEST_F(ExifThumbTest_773, SetJpegThumbnailSetsCompression_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0xFF, 0xD8, 0xFF, 0xD9};
    thumb.setJpegThumbnail(buf, sizeof(buf));

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.Compression"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 6);
}

// Test that setJpegThumbnail sets the JPEGInterchangeFormat tag
TEST_F(ExifThumbTest_773, SetJpegThumbnailSetsInterchangeFormat_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0xFF, 0xD8, 0xFF, 0xD9};
    thumb.setJpegThumbnail(buf, sizeof(buf));

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormat"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 0);
}

// Test that setJpegThumbnail sets the JPEGInterchangeFormatLength tag correctly
TEST_F(ExifThumbTest_773, SetJpegThumbnailSetsInterchangeFormatLength_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0xFF, 0xD8, 0xFF, 0xD9};
    thumb.setJpegThumbnail(buf, sizeof(buf));

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormatLength"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), static_cast<int64_t>(sizeof(buf)));
}

// Test that setJpegThumbnail stores the data area correctly
TEST_F(ExifThumbTest_773, SetJpegThumbnailStoresDataArea_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0xFF, 0xD8, 0x01, 0x02, 0x03, 0xFF, 0xD9};
    thumb.setJpegThumbnail(buf, sizeof(buf));

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormat"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->sizeDataArea(), sizeof(buf));

    DataBuf dataBuf = it->dataArea();
    ASSERT_EQ(dataBuf.size(), sizeof(buf));
    EXPECT_EQ(std::memcmp(dataBuf.c_data(), buf, sizeof(buf)), 0);
}

// Test with zero-size buffer
TEST_F(ExifThumbTest_773, SetJpegThumbnailWithZeroSize_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0};
    thumb.setJpegThumbnail(buf, 0);

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormatLength"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 0);
}

// Test with a larger buffer
TEST_F(ExifThumbTest_773, SetJpegThumbnailWithLargerBuffer_773) {
    ExifThumb thumb(exifData_);
    std::vector<byte> buf(1024, 0xAB);
    thumb.setJpegThumbnail(buf.data(), buf.size());

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormatLength"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 1024);

    auto itFormat = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormat"));
    ASSERT_NE(itFormat, exifData_.end());
    EXPECT_EQ(itFormat->sizeDataArea(), 1024u);
}

// Test that calling setJpegThumbnail twice overwrites previous values
TEST_F(ExifThumbTest_773, SetJpegThumbnailOverwritesPrevious_773) {
    ExifThumb thumb(exifData_);

    const byte buf1[] = {0xFF, 0xD8, 0xFF, 0xD9};
    thumb.setJpegThumbnail(buf1, sizeof(buf1));

    const byte buf2[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    thumb.setJpegThumbnail(buf2, sizeof(buf2));

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormatLength"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), static_cast<int64_t>(sizeof(buf2)));

    auto itFormat = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormat"));
    ASSERT_NE(itFormat, exifData_.end());
    DataBuf dataBuf = itFormat->dataArea();
    ASSERT_EQ(dataBuf.size(), sizeof(buf2));
    EXPECT_EQ(std::memcmp(dataBuf.c_data(), buf2, sizeof(buf2)), 0);
}

// Test that compression remains 6 after overwrite
TEST_F(ExifThumbTest_773, SetJpegThumbnailCompressionRemainsAfterOverwrite_773) {
    ExifThumb thumb(exifData_);

    const byte buf1[] = {0xFF, 0xD8};
    thumb.setJpegThumbnail(buf1, sizeof(buf1));

    const byte buf2[] = {0x00};
    thumb.setJpegThumbnail(buf2, sizeof(buf2));

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.Compression"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 6);
}

// Test that all three keys are present in exifData after setting thumbnail
TEST_F(ExifThumbTest_773, SetJpegThumbnailCreatesThreeEntries_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0x01, 0x02};
    thumb.setJpegThumbnail(buf, sizeof(buf));

    EXPECT_NE(exifData_.findKey(ExifKey("Exif.Thumbnail.Compression")), exifData_.end());
    EXPECT_NE(exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormat")), exifData_.end());
    EXPECT_NE(exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormatLength")), exifData_.end());
}

// Test the overload with resolution parameters
TEST_F(ExifThumbTest_773, SetJpegThumbnailWithResolution_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0xFF, 0xD8, 0xFF, 0xD9};
    URational xres(72, 1);
    URational yres(72, 1);
    uint16_t unit = 2; // inches

    thumb.setJpegThumbnail(buf, sizeof(buf), xres, yres, unit);

    auto itComp = exifData_.findKey(ExifKey("Exif.Thumbnail.Compression"));
    ASSERT_NE(itComp, exifData_.end());
    EXPECT_EQ(itComp->toInt64(0), 6);

    auto itLen = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormatLength"));
    ASSERT_NE(itLen, exifData_.end());
    EXPECT_EQ(itLen->toInt64(0), static_cast<int64_t>(sizeof(buf)));
}

// Test erase removes thumbnail data
TEST_F(ExifThumbTest_773, EraseRemovesThumbnailData_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0xFF, 0xD8, 0xFF, 0xD9};
    thumb.setJpegThumbnail(buf, sizeof(buf));

    // Verify entries exist
    ASSERT_NE(exifData_.findKey(ExifKey("Exif.Thumbnail.Compression")), exifData_.end());

    thumb.erase();

    // After erase, thumbnail-related keys should be gone
    EXPECT_EQ(exifData_.findKey(ExifKey("Exif.Thumbnail.Compression")), exifData_.end());
    EXPECT_EQ(exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormat")), exifData_.end());
    EXPECT_EQ(exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormatLength")), exifData_.end());
}

// Test with single byte buffer
TEST_F(ExifThumbTest_773, SetJpegThumbnailWithSingleByte_773) {
    ExifThumb thumb(exifData_);
    const byte buf[] = {0x42};
    thumb.setJpegThumbnail(buf, sizeof(buf));

    auto it = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormatLength"));
    ASSERT_NE(it, exifData_.end());
    EXPECT_EQ(it->toInt64(0), 1);

    auto itFormat = exifData_.findKey(ExifKey("Exif.Thumbnail.JPEGInterchangeFormat"));
    ASSERT_NE(itFormat, exifData_.end());
    DataBuf dataBuf = itFormat->dataArea();
    ASSERT_EQ(dataBuf.size(), 1u);
    EXPECT_EQ(dataBuf.c_data()[0], 0x42);
}

// Test ExifData operator[] creates entry if not present
TEST_F(ExifThumbTest_773, ExifDataOperatorBracketCreatesEntry_773) {
    EXPECT_TRUE(exifData_.empty());

    ExifThumb thumb(exifData_);
    const byte buf[] = {0xFF, 0xD8, 0xFF, 0xD9};
    thumb.setJpegThumbnail(buf, sizeof(buf));

    EXPECT_FALSE(exifData_.empty());
    EXPECT_GE(exifData_.count(), 3u);
}
