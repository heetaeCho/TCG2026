#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <vector>
#include <cstring>

using namespace Exiv2;

class ExifThumbTest_774 : public ::testing::Test {
protected:
    ExifData exifData;
};

// Test that erase() on empty ExifData does not crash
TEST_F(ExifThumbTest_774, EraseOnEmptyExifData_774) {
    ExifThumb thumb(exifData);
    EXPECT_NO_THROW(thumb.erase());
    EXPECT_TRUE(exifData.empty());
}

// Test that erase() removes IFD1 entries
TEST_F(ExifThumbTest_774, EraseRemovesIfd1Entries_774) {
    // Set a JPEG thumbnail which should add IFD1 entries
    const byte jpegData[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0xFF, 0xD9
    };
    ExifThumb thumb(exifData);
    thumb.setJpegThumbnail(jpegData, sizeof(jpegData));

    // Verify something was added
    EXPECT_FALSE(exifData.empty());

    // Erase should remove IFD1 entries
    thumb.erase();

    // After erase, check that no IFD1 entries remain
    bool hasIfd1 = false;
    for (const auto& datum : exifData) {
        if (datum.ifdId() == IfdId::ifd1Id) {
            hasIfd1 = true;
            break;
        }
    }
    EXPECT_FALSE(hasIfd1);
}

// Test that erase() does not remove non-IFD1 entries
TEST_F(ExifThumbTest_774, EraseDoesNotRemoveNonIfd1Entries_774) {
    // Add an IFD0 entry (e.g., Exif.Image.Make)
    exifData["Exif.Image.Make"] = "TestCamera";

    size_t countBefore = exifData.count();
    EXPECT_GT(countBefore, 0u);

    ExifThumb thumb(exifData);
    thumb.erase();

    // IFD0 entries should still be present
    size_t countAfter = exifData.count();
    EXPECT_EQ(countBefore, countAfter);

    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, exifData.end());
}

// Test that erase() called twice does not crash
TEST_F(ExifThumbTest_774, EraseCalledTwice_774) {
    const byte jpegData[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0xFF, 0xD9
    };
    ExifThumb thumb(exifData);
    thumb.setJpegThumbnail(jpegData, sizeof(jpegData));

    EXPECT_NO_THROW(thumb.erase());
    EXPECT_NO_THROW(thumb.erase());
}

// Test setJpegThumbnail with buffer adds entries
TEST_F(ExifThumbTest_774, SetJpegThumbnailFromBuffer_774) {
    const byte jpegData[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0xFF, 0xD9
    };
    ExifThumb thumb(exifData);
    thumb.setJpegThumbnail(jpegData, sizeof(jpegData));

    // After setting thumbnail, there should be some data
    EXPECT_FALSE(exifData.empty());
}

// Test setJpegThumbnail with buffer and resolution
TEST_F(ExifThumbTest_774, SetJpegThumbnailFromBufferWithResolution_774) {
    const byte jpegData[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0xFF, 0xD9
    };
    URational xres = {72, 1};
    URational yres = {72, 1};
    uint16_t unit = 2; // inches

    ExifThumb thumb(exifData);
    thumb.setJpegThumbnail(jpegData, sizeof(jpegData), xres, yres, unit);

    EXPECT_FALSE(exifData.empty());

    // Check that IFD1 entries exist
    bool hasIfd1 = false;
    for (const auto& datum : exifData) {
        if (datum.ifdId() == IfdId::ifd1Id) {
            hasIfd1 = true;
            break;
        }
    }
    EXPECT_TRUE(hasIfd1);
}

// Test setJpegThumbnail with zero-size buffer
TEST_F(ExifThumbTest_774, SetJpegThumbnailZeroSize_774) {
    const byte jpegData[] = {0xFF, 0xD8};
    ExifThumb thumb(exifData);
    // Setting with zero size - should not crash
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData, 0));
}

// Test that erase after setJpegThumbnail with resolution cleans up properly
TEST_F(ExifThumbTest_774, EraseAfterSetWithResolution_774) {
    const byte jpegData[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0xFF, 0xD9
    };
    URational xres = {300, 1};
    URational yres = {300, 1};
    uint16_t unit = 2;

    ExifThumb thumb(exifData);
    thumb.setJpegThumbnail(jpegData, sizeof(jpegData), xres, yres, unit);
    EXPECT_FALSE(exifData.empty());

    thumb.erase();

    // No IFD1 entries should remain
    bool hasIfd1 = false;
    for (const auto& datum : exifData) {
        if (datum.ifdId() == IfdId::ifd1Id) {
            hasIfd1 = true;
            break;
        }
    }
    EXPECT_FALSE(hasIfd1);
}

// Test that ExifThumb can be constructed from ExifData with existing entries
TEST_F(ExifThumbTest_774, ConstructWithExistingData_774) {
    exifData["Exif.Image.Make"] = "TestMake";
    exifData["Exif.Image.Model"] = "TestModel";

    EXPECT_NO_THROW({
        ExifThumb thumb(exifData);
    });
}

// Test mixed IFD entries - erase only removes IFD1
TEST_F(ExifThumbTest_774, EraseMixedIfdEntries_774) {
    // Add entries from different IFDs
    exifData["Exif.Image.Make"] = "Camera";           // IFD0
    exifData["Exif.Photo.ExposureTime"] = "1/100";     // ExifIFD

    const byte jpegData[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0xFF, 0xD9
    };
    ExifThumb thumb(exifData);
    thumb.setJpegThumbnail(jpegData, sizeof(jpegData));

    size_t totalBefore = exifData.count();

    thumb.erase();

    // IFD0 and ExifIFD entries should still exist
    auto makeIt = exifData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_NE(makeIt, exifData.end());

    auto exposureIt = exifData.findKey(ExifKey("Exif.Photo.ExposureTime"));
    EXPECT_NE(exposureIt, exifData.end());

    // Total count should be less (IFD1 entries removed)
    // but at least IFD0 and ExifIFD entries remain
    EXPECT_GE(exifData.count(), 2u);
}

// Test that setting thumbnail replaces previous thumbnail
TEST_F(ExifThumbTest_774, SetThumbnailReplacesExisting_774) {
    const byte jpegData1[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0xFF, 0xD9
    };
    const byte jpegData2[] = {
        0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x04, 0x00, 0x00, 0xFF, 0xD9
    };

    ExifThumb thumb(exifData);
    thumb.setJpegThumbnail(jpegData1, sizeof(jpegData1));
    EXPECT_FALSE(exifData.empty());

    // Set again with different data
    EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData2, sizeof(jpegData2)));
    EXPECT_FALSE(exifData.empty());
}
