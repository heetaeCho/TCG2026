#include <gtest/gtest.h>
#include <memory>

// We need to include the necessary headers to use JBIG2Bitmap
// Based on the provided interface, we'll include the relevant header
// Since JBIG2Bitmap is defined in JBIG2Stream.cc, we need to find the right include path

// Forward declarations and minimal includes
// The class is in JBIG2Stream.cc but we need to access it through its header
#include "JBIG2Stream.h"

class JBIG2BitmapTest_1817 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test basic construction with valid dimensions
TEST_F(JBIG2BitmapTest_1817, ConstructWithValidDimensions_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 10);
}

// Test construction with zero dimensions
TEST_F(JBIG2BitmapTest_1817, ConstructWithZeroDimensions_1817) {
    JBIG2Bitmap bitmap(0, 0, 0);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test construction with width=1, height=1
TEST_F(JBIG2BitmapTest_1817, ConstructWithMinimalDimensions_1817) {
    JBIG2Bitmap bitmap(0, 1, 1);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 1);
    EXPECT_EQ(bitmap.getHeight(), 1);
}

// Test getPixel returns 0 for negative x
TEST_F(JBIG2BitmapTest_1817, GetPixelNegativeXReturnsZero_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(-1, 0), 0);
}

// Test getPixel returns 0 for negative y
TEST_F(JBIG2BitmapTest_1817, GetPixelNegativeYReturnsZero_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(0, -1), 0);
}

// Test getPixel returns 0 for x >= width
TEST_F(JBIG2BitmapTest_1817, GetPixelXOutOfBoundsReturnsZero_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(10, 0), 0);
    EXPECT_EQ(bitmap.getPixel(11, 0), 0);
    EXPECT_EQ(bitmap.getPixel(100, 0), 0);
}

// Test getPixel returns 0 for y >= height
TEST_F(JBIG2BitmapTest_1817, GetPixelYOutOfBoundsReturnsZero_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(0, 10), 0);
    EXPECT_EQ(bitmap.getPixel(0, 11), 0);
    EXPECT_EQ(bitmap.getPixel(0, 100), 0);
}

// Test getPixel returns 0 for both x and y out of bounds
TEST_F(JBIG2BitmapTest_1817, GetPixelBothOutOfBoundsReturnsZero_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(-1, -1), 0);
    EXPECT_EQ(bitmap.getPixel(10, 10), 0);
}

// Test clearToZero sets all pixels to 0
TEST_F(JBIG2BitmapTest_1817, ClearToZeroSetsAllPixelsToZero_1817) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToOne();
    bitmap.clearToZero();
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            EXPECT_EQ(bitmap.getPixel(x, y), 0) << "Pixel (" << x << ", " << y << ") should be 0";
        }
    }
}

// Test clearToOne sets all pixels to 1
TEST_F(JBIG2BitmapTest_1817, ClearToOneSetsAllPixelsToOne_1817) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToZero();
    bitmap.clearToOne();
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            EXPECT_EQ(bitmap.getPixel(x, y), 1) << "Pixel (" << x << ", " << y << ") should be 1";
        }
    }
}

// Test setPixel sets a pixel to 1
TEST_F(JBIG2BitmapTest_1817, SetPixelSetsPixelToOne_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
}

// Test clearPixel clears a pixel to 0
TEST_F(JBIG2BitmapTest_1817, ClearPixelSetsPixelToZero_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToOne();
    bitmap.clearPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 0);
}

// Test setPixel at corner positions
TEST_F(JBIG2BitmapTest_1817, SetPixelAtCorners_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    
    // Top-left
    bitmap.setPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    
    // Top-right
    bitmap.setPixel(9, 0);
    EXPECT_EQ(bitmap.getPixel(9, 0), 1);
    
    // Bottom-left
    bitmap.setPixel(0, 9);
    EXPECT_EQ(bitmap.getPixel(0, 9), 1);
    
    // Bottom-right
    bitmap.setPixel(9, 9);
    EXPECT_EQ(bitmap.getPixel(9, 9), 1);
}

// Test that setPixel only affects the targeted pixel
TEST_F(JBIG2BitmapTest_1817, SetPixelDoesNotAffectNeighbors_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    
    EXPECT_EQ(bitmap.getPixel(4, 5), 0);
    EXPECT_EQ(bitmap.getPixel(6, 5), 0);
    EXPECT_EQ(bitmap.getPixel(5, 4), 0);
    EXPECT_EQ(bitmap.getPixel(5, 6), 0);
}

// Test getWidth and getHeight
TEST_F(JBIG2BitmapTest_1817, GetWidthAndHeight_1817) {
    JBIG2Bitmap bitmap(0, 100, 200);
    EXPECT_EQ(bitmap.getWidth(), 100);
    EXPECT_EQ(bitmap.getHeight(), 200);
}

// Test getLineSize is consistent with width
TEST_F(JBIG2BitmapTest_1817, GetLineSizeIsConsistentWithWidth_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    // Line size should be at least ceil(width/8)
    EXPECT_GE(bitmap.getLineSize(), (10 + 7) / 8);
}

// Test getLineSize for various widths
TEST_F(JBIG2BitmapTest_1817, GetLineSizeForVariousWidths_1817) {
    {
        JBIG2Bitmap bitmap(0, 1, 1);
        EXPECT_GE(bitmap.getLineSize(), 1);
    }
    {
        JBIG2Bitmap bitmap(0, 8, 1);
        EXPECT_GE(bitmap.getLineSize(), 1);
    }
    {
        JBIG2Bitmap bitmap(0, 9, 1);
        EXPECT_GE(bitmap.getLineSize(), 2);
    }
    {
        JBIG2Bitmap bitmap(0, 16, 1);
        EXPECT_GE(bitmap.getLineSize(), 2);
    }
}

// Test getDataPtr is not null for valid bitmap
TEST_F(JBIG2BitmapTest_1817, GetDataPtrNotNull_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    if (bitmap.isOk()) {
        EXPECT_NE(bitmap.getDataPtr(), nullptr);
    }
}

// Test getDataSize
TEST_F(JBIG2BitmapTest_1817, GetDataSizeIsPositive_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    if (bitmap.isOk()) {
        EXPECT_GT(bitmap.getDataSize(), 0);
        EXPECT_EQ(bitmap.getDataSize(), bitmap.getLineSize() * bitmap.getHeight());
    }
}

// Test copy constructor
TEST_F(JBIG2BitmapTest_1817, CopyConstructor_1817) {
    JBIG2Bitmap original(0, 10, 10);
    original.clearToZero();
    original.setPixel(3, 3);
    original.setPixel(7, 7);
    
    JBIG2Bitmap copy(&original);
    EXPECT_EQ(copy.getWidth(), original.getWidth());
    EXPECT_EQ(copy.getHeight(), original.getHeight());
    EXPECT_EQ(copy.getPixel(3, 3), 1);
    EXPECT_EQ(copy.getPixel(7, 7), 1);
    EXPECT_EQ(copy.getPixel(0, 0), 0);
}

// Test getSlice returns valid sub-bitmap
TEST_F(JBIG2BitmapTest_1817, GetSliceReturnsValidSubBitmap_1817) {
    JBIG2Bitmap bitmap(0, 20, 20);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    
    auto slice = bitmap.getSlice(0, 0, 10, 10);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 10);
        EXPECT_EQ(slice->getHeight(), 10);
        EXPECT_EQ(slice->getPixel(5, 5), 1);
        EXPECT_EQ(slice->getPixel(0, 0), 0);
    }
}

// Test getSlice with offset
TEST_F(JBIG2BitmapTest_1817, GetSliceWithOffset_1817) {
    JBIG2Bitmap bitmap(0, 20, 20);
    bitmap.clearToZero();
    bitmap.setPixel(15, 15);
    
    auto slice = bitmap.getSlice(10, 10, 10, 10);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 10);
        EXPECT_EQ(slice->getHeight(), 10);
        EXPECT_EQ(slice->getPixel(5, 5), 1);
    }
}

// Test expand increases height
TEST_F(JBIG2BitmapTest_1817, ExpandIncreasesHeight_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    
    bitmap.expand(20, 0);
    EXPECT_EQ(bitmap.getHeight(), 20);
    // Original pixel should still be set
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
}

// Test expand with pixel fill value 0
TEST_F(JBIG2BitmapTest_1817, ExpandWithZeroFill_1817) {
    JBIG2Bitmap bitmap(0, 10, 5);
    bitmap.clearToOne();
    
    bitmap.expand(10, 0);
    EXPECT_EQ(bitmap.getHeight(), 10);
    // New rows should be filled with 0
    EXPECT_EQ(bitmap.getPixel(0, 9), 0);
    // Old rows should still be 1
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
}

// Test expand with pixel fill value 1
TEST_F(JBIG2BitmapTest_1817, ExpandWithOneFill_1817) {
    JBIG2Bitmap bitmap(0, 10, 5);
    bitmap.clearToZero();
    
    bitmap.expand(10, 1);
    EXPECT_EQ(bitmap.getHeight(), 10);
    // New rows should be filled with 1
    EXPECT_EQ(bitmap.getPixel(0, 9), 1);
    // Old rows should still be 0
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
}

// Test duplicateRow
TEST_F(JBIG2BitmapTest_1817, DuplicateRow_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    // Set some pixels in row 3
    bitmap.setPixel(2, 3);
    bitmap.setPixel(5, 3);
    bitmap.setPixel(8, 3);
    
    bitmap.duplicateRow(7, 3);
    
    EXPECT_EQ(bitmap.getPixel(2, 7), 1);
    EXPECT_EQ(bitmap.getPixel(5, 7), 1);
    EXPECT_EQ(bitmap.getPixel(8, 7), 1);
    EXPECT_EQ(bitmap.getPixel(0, 7), 0);
}

// Test getPixel boundary: exactly at w-1 and h-1
TEST_F(JBIG2BitmapTest_1817, GetPixelAtMaxValidCoordinates_1817) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToZero();
    bitmap.setPixel(15, 15);
    EXPECT_EQ(bitmap.getPixel(15, 15), 1);
    EXPECT_EQ(bitmap.getPixel(16, 15), 0); // out of bounds
    EXPECT_EQ(bitmap.getPixel(15, 16), 0); // out of bounds
}

// Test getPixel on non-byte-aligned widths
TEST_F(JBIG2BitmapTest_1817, GetPixelNonByteAlignedWidth_1817) {
    JBIG2Bitmap bitmap(0, 13, 5);
    bitmap.clearToZero();
    bitmap.setPixel(12, 4);
    EXPECT_EQ(bitmap.getPixel(12, 4), 1);
    EXPECT_EQ(bitmap.getPixel(13, 4), 0); // out of bounds
}

// Test setPixel and clearPixel toggling
TEST_F(JBIG2BitmapTest_1817, SetAndClearPixelToggle_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
    bitmap.setPixel(3, 3);
    EXPECT_EQ(bitmap.getPixel(3, 3), 1);
    bitmap.clearPixel(3, 3);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
}

// Test large bitmap
TEST_F(JBIG2BitmapTest_1817, LargeBitmap_1817) {
    JBIG2Bitmap bitmap(0, 1000, 1000);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.setPixel(999, 999);
        EXPECT_EQ(bitmap.getPixel(999, 999), 1);
        EXPECT_EQ(bitmap.getPixel(0, 0), 0);
        EXPECT_EQ(bitmap.getPixel(500, 500), 0);
    }
}

// Test getPixel with very large negative coordinates
TEST_F(JBIG2BitmapTest_1817, GetPixelVeryLargeNegativeCoords_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(-1000, -1000), 0);
}

// Test getPixel with very large positive coordinates
TEST_F(JBIG2BitmapTest_1817, GetPixelVeryLargePositiveCoords_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(1000000, 1000000), 0);
}

// Test width of 1 pixel
TEST_F(JBIG2BitmapTest_1817, SinglePixelWidth_1817) {
    JBIG2Bitmap bitmap(0, 1, 10);
    bitmap.clearToZero();
    bitmap.setPixel(0, 5);
    EXPECT_EQ(bitmap.getPixel(0, 5), 1);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(1, 5), 0); // out of bounds
}

// Test height of 1 pixel
TEST_F(JBIG2BitmapTest_1817, SinglePixelHeight_1817) {
    JBIG2Bitmap bitmap(0, 10, 1);
    bitmap.clearToZero();
    bitmap.setPixel(5, 0);
    EXPECT_EQ(bitmap.getPixel(5, 0), 1);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(5, 1), 0); // out of bounds
}

// Test setting all pixels in a row
TEST_F(JBIG2BitmapTest_1817, SetAllPixelsInRow_1817) {
    JBIG2Bitmap bitmap(0, 16, 4);
    bitmap.clearToZero();
    for (int x = 0; x < 16; x++) {
        bitmap.setPixel(x, 2);
    }
    for (int x = 0; x < 16; x++) {
        EXPECT_EQ(bitmap.getPixel(x, 2), 1) << "Pixel (" << x << ", 2) should be 1";
    }
    // Other rows should be 0
    for (int x = 0; x < 16; x++) {
        EXPECT_EQ(bitmap.getPixel(x, 0), 0);
        EXPECT_EQ(bitmap.getPixel(x, 1), 0);
        EXPECT_EQ(bitmap.getPixel(x, 3), 0);
    }
}

// Test getType returns correct segment type
TEST_F(JBIG2BitmapTest_1817, GetTypeReturnsBitmapType_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    // The type should indicate it's a bitmap segment
    JBIG2SegmentType type = bitmap.getType();
    EXPECT_EQ(type, jbig2SegBitmap);
}

// Test bitmap with width that is exact multiple of 8
TEST_F(JBIG2BitmapTest_1817, WidthMultipleOf8_1817) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToZero();
    // Set last pixel of first byte
    bitmap.setPixel(7, 0);
    EXPECT_EQ(bitmap.getPixel(7, 0), 1);
    EXPECT_EQ(bitmap.getPixel(6, 0), 0);
}

// Test bitmap with width not multiple of 8
TEST_F(JBIG2BitmapTest_1817, WidthNotMultipleOf8_1817) {
    JBIG2Bitmap bitmap(0, 11, 5);
    bitmap.clearToZero();
    bitmap.setPixel(10, 0);
    EXPECT_EQ(bitmap.getPixel(10, 0), 1);
    EXPECT_EQ(bitmap.getPixel(9, 0), 0);
}

// Test multiple set and clear operations on same pixel
TEST_F(JBIG2BitmapTest_1817, MultipleSetClearOnSamePixel_1817) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    
    for (int i = 0; i < 10; i++) {
        bitmap.setPixel(5, 5);
        EXPECT_EQ(bitmap.getPixel(5, 5), 1);
        bitmap.clearPixel(5, 5);
        EXPECT_EQ(bitmap.getPixel(5, 5), 0);
    }
}
