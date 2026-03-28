#include <gtest/gtest.h>
#include <memory>
#include <cstring>

// We need to include the necessary headers for JBIG2Bitmap
// Since JBIG2Bitmap is defined in JBIG2Stream.cc, we need to find the right way to include it
// Based on the project structure, we'll include the relevant headers

// Forward declarations and minimal includes needed
#include "JBIG2Stream.h"

class JBIG2BitmapTest_1819 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with valid dimensions
TEST_F(JBIG2BitmapTest_1819, ConstructValidBitmap_1819) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 10);
}

// Test construction with zero dimensions
TEST_F(JBIG2BitmapTest_1819, ConstructZeroWidthBitmap_1819) {
    JBIG2Bitmap bitmap(0, 0, 10);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 10);
}

TEST_F(JBIG2BitmapTest_1819, ConstructZeroHeightBitmap_1819) {
    JBIG2Bitmap bitmap(0, 10, 0);
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test clearToZero sets all pixels to 0
TEST_F(JBIG2BitmapTest_1819, ClearToZero_1819) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    
    // Set some pixels first
    bitmap.setPixel(0, 0);
    bitmap.setPixel(5, 5);
    bitmap.setPixel(15, 15);
    
    // Clear to zero
    bitmap.clearToZero();
    
    // All pixels should be 0
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(5, 5), 0);
    EXPECT_EQ(bitmap.getPixel(15, 15), 0);
}

// Test clearToOne sets all pixels to 1
TEST_F(JBIG2BitmapTest_1819, ClearToOne_1819) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToOne();
    
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    EXPECT_EQ(bitmap.getPixel(15, 15), 1);
}

// Test setPixel and getPixel
TEST_F(JBIG2BitmapTest_1819, SetAndGetPixel_1819) {
    JBIG2Bitmap bitmap(0, 32, 32);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Set a pixel
    bitmap.setPixel(5, 10);
    EXPECT_EQ(bitmap.getPixel(5, 10), 1);
    
    // Neighboring pixels should still be 0
    EXPECT_EQ(bitmap.getPixel(4, 10), 0);
    EXPECT_EQ(bitmap.getPixel(6, 10), 0);
    EXPECT_EQ(bitmap.getPixel(5, 9), 0);
    EXPECT_EQ(bitmap.getPixel(5, 11), 0);
}

// Test clearPixel
TEST_F(JBIG2BitmapTest_1819, ClearPixel_1819) {
    JBIG2Bitmap bitmap(0, 32, 32);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Set a pixel then clear it
    bitmap.setPixel(7, 3);
    EXPECT_EQ(bitmap.getPixel(7, 3), 1);
    
    bitmap.clearPixel(7, 3);
    EXPECT_EQ(bitmap.getPixel(7, 3), 0);
}

// Test clearPixel on already clear pixel
TEST_F(JBIG2BitmapTest_1819, ClearPixelAlreadyClear_1819) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Clear an already-clear pixel
    bitmap.clearPixel(3, 3);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
}

// Test clearPixel does not affect neighboring pixels
TEST_F(JBIG2BitmapTest_1819, ClearPixelDoesNotAffectNeighbors_1819) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    
    bitmap.clearPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 0);
    EXPECT_EQ(bitmap.getPixel(4, 5), 1);
    EXPECT_EQ(bitmap.getPixel(6, 5), 1);
    EXPECT_EQ(bitmap.getPixel(5, 4), 1);
    EXPECT_EQ(bitmap.getPixel(5, 6), 1);
}

// Test pixel at boundary positions
TEST_F(JBIG2BitmapTest_1819, SetPixelAtBoundaries_1819) {
    JBIG2Bitmap bitmap(0, 32, 32);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Top-left corner
    bitmap.setPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    
    // Top-right corner
    bitmap.setPixel(31, 0);
    EXPECT_EQ(bitmap.getPixel(31, 0), 1);
    
    // Bottom-left corner
    bitmap.setPixel(0, 31);
    EXPECT_EQ(bitmap.getPixel(0, 31), 1);
    
    // Bottom-right corner
    bitmap.setPixel(31, 31);
    EXPECT_EQ(bitmap.getPixel(31, 31), 1);
}

// Test getPixel out of bounds returns 0
TEST_F(JBIG2BitmapTest_1819, GetPixelOutOfBounds_1819) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    
    // Out of bounds should return 0
    EXPECT_EQ(bitmap.getPixel(-1, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, -1), 0);
    EXPECT_EQ(bitmap.getPixel(10, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, 10), 0);
    EXPECT_EQ(bitmap.getPixel(100, 100), 0);
}

// Test getWidth and getHeight
TEST_F(JBIG2BitmapTest_1819, GetDimensions_1819) {
    JBIG2Bitmap bitmap(0, 100, 200);
    EXPECT_EQ(bitmap.getWidth(), 100);
    EXPECT_EQ(bitmap.getHeight(), 200);
}

// Test getLineSize
TEST_F(JBIG2BitmapTest_1819, GetLineSize_1819) {
    // For width 8, line size should be at least 1 byte
    JBIG2Bitmap bitmap1(0, 8, 1);
    EXPECT_GE(bitmap1.getLineSize(), 1);
    
    // For width 9, line size should be at least 2 bytes
    JBIG2Bitmap bitmap2(0, 9, 1);
    EXPECT_GE(bitmap2.getLineSize(), 2);
    
    // For width 1, line size should be at least 1 byte
    JBIG2Bitmap bitmap3(0, 1, 1);
    EXPECT_GE(bitmap3.getLineSize(), 1);
}

// Test getDataPtr is not null for valid bitmap
TEST_F(JBIG2BitmapTest_1819, GetDataPtr_1819) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_NE(bitmap.getDataPtr(), nullptr);
}

// Test getDataSize
TEST_F(JBIG2BitmapTest_1819, GetDataSize_1819) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getDataSize(), bitmap.getLineSize() * bitmap.getHeight());
}

// Test copy constructor
TEST_F(JBIG2BitmapTest_1819, CopyConstructor_1819) {
    JBIG2Bitmap original(0, 16, 16);
    EXPECT_TRUE(original.isOk());
    original.clearToZero();
    original.setPixel(3, 5);
    original.setPixel(10, 12);
    
    JBIG2Bitmap copy(&original);
    EXPECT_TRUE(copy.isOk());
    EXPECT_EQ(copy.getWidth(), original.getWidth());
    EXPECT_EQ(copy.getHeight(), original.getHeight());
    EXPECT_EQ(copy.getPixel(3, 5), 1);
    EXPECT_EQ(copy.getPixel(10, 12), 1);
    EXPECT_EQ(copy.getPixel(0, 0), 0);
}

// Test expand increases height
TEST_F(JBIG2BitmapTest_1819, ExpandIncreasesHeight_1819) {
    JBIG2Bitmap bitmap(0, 16, 8);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    bitmap.setPixel(3, 3);
    
    bitmap.expand(16, 0);
    EXPECT_EQ(bitmap.getHeight(), 16);
    // Original pixel should still be set
    EXPECT_EQ(bitmap.getPixel(3, 3), 1);
    // New area filled with 0
    EXPECT_EQ(bitmap.getPixel(3, 12), 0);
}

// Test expand with pixel=1 fills new rows
TEST_F(JBIG2BitmapTest_1819, ExpandWithPixelOne_1819) {
    JBIG2Bitmap bitmap(0, 16, 4);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.expand(8, 1);
    EXPECT_EQ(bitmap.getHeight(), 8);
    // New area should be filled with 1
    EXPECT_EQ(bitmap.getPixel(0, 6), 1);
    EXPECT_EQ(bitmap.getPixel(15, 7), 1);
}

// Test getSlice
TEST_F(JBIG2BitmapTest_1819, GetSlice_1819) {
    JBIG2Bitmap bitmap(0, 32, 32);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    bitmap.setPixel(10, 10);
    
    auto slice = bitmap.getSlice(0, 0, 16, 16);
    EXPECT_NE(slice, nullptr);
    EXPECT_EQ(slice->getWidth(), 16);
    EXPECT_EQ(slice->getHeight(), 16);
    EXPECT_EQ(slice->getPixel(5, 5), 1);
}

// Test duplicateRow
TEST_F(JBIG2BitmapTest_1819, DuplicateRow_1819) {
    JBIG2Bitmap bitmap(0, 16, 8);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Set some pixels in row 2
    bitmap.setPixel(3, 2);
    bitmap.setPixel(7, 2);
    bitmap.setPixel(11, 2);
    
    // Duplicate row 2 to row 5
    bitmap.duplicateRow(5, 2);
    
    EXPECT_EQ(bitmap.getPixel(3, 5), 1);
    EXPECT_EQ(bitmap.getPixel(7, 5), 1);
    EXPECT_EQ(bitmap.getPixel(11, 5), 1);
    EXPECT_EQ(bitmap.getPixel(0, 5), 0);
}

// Test getType returns correct segment type
TEST_F(JBIG2BitmapTest_1819, GetType_1819) {
    JBIG2Bitmap bitmap(0, 8, 8);
    // The type should be jbig2SegBitmap (based on JBIG2 standard)
    JBIG2SegmentType type = bitmap.getType();
    EXPECT_EQ(type, jbig2SegBitmap);
}

// Test setPixel at byte-aligned positions (multiple of 8)
TEST_F(JBIG2BitmapTest_1819, SetPixelByteAligned_1819) {
    JBIG2Bitmap bitmap(0, 32, 4);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Test positions at byte boundaries
    bitmap.setPixel(0, 0);
    bitmap.setPixel(8, 0);
    bitmap.setPixel(16, 0);
    bitmap.setPixel(24, 0);
    
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(8, 0), 1);
    EXPECT_EQ(bitmap.getPixel(16, 0), 1);
    EXPECT_EQ(bitmap.getPixel(24, 0), 1);
    
    // Between them should be 0
    EXPECT_EQ(bitmap.getPixel(1, 0), 0);
    EXPECT_EQ(bitmap.getPixel(7, 0), 0);
    EXPECT_EQ(bitmap.getPixel(9, 0), 0);
}

// Test clearPixel at all bit positions within a byte
TEST_F(JBIG2BitmapTest_1819, ClearPixelAllBitPositions_1819) {
    JBIG2Bitmap bitmap(0, 16, 1);
    EXPECT_TRUE(bitmap.isOk());
    
    for (int x = 0; x < 8; x++) {
        bitmap.clearToOne();
        bitmap.clearPixel(x, 0);
        EXPECT_EQ(bitmap.getPixel(x, 0), 0) << "Failed at x=" << x;
        // Check neighbors within byte are still 1
        for (int nx = 0; nx < 8; nx++) {
            if (nx != x) {
                EXPECT_EQ(bitmap.getPixel(nx, 0), 1) << "Neighbor affected at x=" << x << " nx=" << nx;
            }
        }
    }
}

// Test single pixel width bitmap
TEST_F(JBIG2BitmapTest_1819, SinglePixelWidth_1819) {
    JBIG2Bitmap bitmap(0, 1, 1);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    
    bitmap.setPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    
    bitmap.clearPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
}

// Test large bitmap
TEST_F(JBIG2BitmapTest_1819, LargeBitmap_1819) {
    JBIG2Bitmap bitmap(0, 1000, 1000);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.setPixel(999, 999);
        EXPECT_EQ(bitmap.getPixel(999, 999), 1);
        EXPECT_EQ(bitmap.getPixel(0, 0), 0);
        EXPECT_EQ(bitmap.getPixel(500, 500), 0);
    }
}

// Test non-byte-aligned width
TEST_F(JBIG2BitmapTest_1819, NonByteAlignedWidth_1819) {
    // Width 13 is not a multiple of 8
    JBIG2Bitmap bitmap(0, 13, 5);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.setPixel(12, 4);
    EXPECT_EQ(bitmap.getPixel(12, 4), 1);
    EXPECT_EQ(bitmap.getPixel(11, 4), 0);
}

// Test JBIG2BitmapPtr usage with getPixelPtr and nextPixel
TEST_F(JBIG2BitmapTest_1819, PixelPtrIteration_1819) {
    JBIG2Bitmap bitmap(0, 16, 4);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    bitmap.setPixel(3, 0);
    bitmap.setPixel(7, 0);
    
    JBIG2BitmapPtr ptr;
    bitmap.getPixelPtr(0, 0, &ptr);
    
    // Iterate through first row and check pixels
    for (int x = 0; x < 16; x++) {
        int pixel = bitmap.nextPixel(&ptr);
        if (x == 3 || x == 7) {
            EXPECT_EQ(pixel, 1) << "Expected 1 at x=" << x;
        } else {
            EXPECT_EQ(pixel, 0) << "Expected 0 at x=" << x;
        }
    }
}

// Test combine operation (OR)
TEST_F(JBIG2BitmapTest_1819, CombineOR_1819) {
    JBIG2Bitmap bitmap1(0, 16, 16);
    JBIG2Bitmap bitmap2(1, 8, 8);
    EXPECT_TRUE(bitmap1.isOk());
    EXPECT_TRUE(bitmap2.isOk());
    
    bitmap1.clearToZero();
    bitmap2.clearToZero();
    bitmap2.setPixel(3, 3);
    
    // combOp 0 is typically OR
    bitmap1.combine(bitmap2, 0, 0, 0);
    EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
}

// Test combine with offset
TEST_F(JBIG2BitmapTest_1819, CombineWithOffset_1819) {
    JBIG2Bitmap bitmap1(0, 16, 16);
    JBIG2Bitmap bitmap2(1, 4, 4);
    EXPECT_TRUE(bitmap1.isOk());
    EXPECT_TRUE(bitmap2.isOk());
    
    bitmap1.clearToZero();
    bitmap2.clearToZero();
    bitmap2.setPixel(0, 0);
    
    bitmap1.combine(bitmap2, 5, 5, 0);
    EXPECT_EQ(bitmap1.getPixel(5, 5), 1);
    EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
}

// Test clearPixel after clearToOne on multiple positions
TEST_F(JBIG2BitmapTest_1819, ClearMultiplePixels_1819) {
    JBIG2Bitmap bitmap(0, 24, 8);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    
    bitmap.clearPixel(0, 0);
    bitmap.clearPixel(7, 0);
    bitmap.clearPixel(8, 0);
    bitmap.clearPixel(15, 0);
    bitmap.clearPixel(16, 0);
    bitmap.clearPixel(23, 0);
    
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(7, 0), 0);
    EXPECT_EQ(bitmap.getPixel(8, 0), 0);
    EXPECT_EQ(bitmap.getPixel(15, 0), 0);
    EXPECT_EQ(bitmap.getPixel(16, 0), 0);
    EXPECT_EQ(bitmap.getPixel(23, 0), 0);
    
    // Pixels that were not cleared should still be 1
    EXPECT_EQ(bitmap.getPixel(1, 0), 1);
    EXPECT_EQ(bitmap.getPixel(6, 0), 1);
    EXPECT_EQ(bitmap.getPixel(9, 0), 1);
    EXPECT_EQ(bitmap.getPixel(14, 0), 1);
}
