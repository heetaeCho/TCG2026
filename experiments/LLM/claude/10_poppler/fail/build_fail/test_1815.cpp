#include <gtest/gtest.h>
#include <memory>

// We need to include the necessary headers for JBIG2Bitmap
// Based on the known dependencies, JBIG2Bitmap is defined in JBIG2Stream.cc
// but we need the header that declares it

// Forward declarations and minimal includes needed
#include "JBIG2Stream.h"

// If JBIG2Stream.h doesn't exist as a standalone header, we may need to
// include what's available. The class is in JBIG2Stream.cc but typically
// there's a corresponding header.

class JBIG2BitmapTest_1815 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with valid dimensions
TEST_F(JBIG2BitmapTest_1815, ConstructWithValidDimensions_1815) {
    JBIG2Bitmap bitmap(0, 10, 20);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 20);
}

// Test construction with zero dimensions
TEST_F(JBIG2BitmapTest_1815, ConstructWithZeroDimensions_1815) {
    JBIG2Bitmap bitmap(0, 0, 0);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test construction with width zero, non-zero height
TEST_F(JBIG2BitmapTest_1815, ConstructWithZeroWidth_1815) {
    JBIG2Bitmap bitmap(0, 0, 5);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 5);
}

// Test construction with non-zero width, zero height
TEST_F(JBIG2BitmapTest_1815, ConstructWithZeroHeight_1815) {
    JBIG2Bitmap bitmap(0, 5, 0);
    EXPECT_EQ(bitmap.getWidth(), 5);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test copy constructor
TEST_F(JBIG2BitmapTest_1815, CopyConstruction_1815) {
    JBIG2Bitmap original(0, 15, 25);
    EXPECT_TRUE(original.isOk());
    JBIG2Bitmap copy(&original);
    EXPECT_EQ(copy.getWidth(), 15);
    EXPECT_EQ(copy.getHeight(), 25);
    EXPECT_TRUE(copy.isOk());
}

// Test getWidth
TEST_F(JBIG2BitmapTest_1815, GetWidth_1815) {
    JBIG2Bitmap bitmap(1, 100, 200);
    EXPECT_EQ(bitmap.getWidth(), 100);
}

// Test getHeight
TEST_F(JBIG2BitmapTest_1815, GetHeight_1815) {
    JBIG2Bitmap bitmap(1, 100, 200);
    EXPECT_EQ(bitmap.getHeight(), 200);
}

// Test getDataSize for a known bitmap
TEST_F(JBIG2BitmapTest_1815, GetDataSize_1815) {
    JBIG2Bitmap bitmap(0, 8, 1);
    EXPECT_TRUE(bitmap.isOk());
    // Data size should be at least lineSize * height
    EXPECT_GT(bitmap.getDataSize(), 0);
}

// Test getLineSize
TEST_F(JBIG2BitmapTest_1815, GetLineSize_1815) {
    JBIG2Bitmap bitmap(0, 8, 10);
    EXPECT_TRUE(bitmap.isOk());
    // Line size should be at least ceil(width / 8)
    EXPECT_GE(bitmap.getLineSize(), 1);
}

// Test getLineSize with width not multiple of 8
TEST_F(JBIG2BitmapTest_1815, GetLineSizeNonMultipleOf8_1815) {
    JBIG2Bitmap bitmap(0, 9, 10);
    EXPECT_TRUE(bitmap.isOk());
    // 9 bits needs at least 2 bytes
    EXPECT_GE(bitmap.getLineSize(), 2);
}

// Test clearToZero and verify pixels are zero
TEST_F(JBIG2BitmapTest_1815, ClearToZero_1815) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            EXPECT_EQ(bitmap.getPixel(x, y), 0);
        }
    }
}

// Test clearToOne and verify pixels are one
TEST_F(JBIG2BitmapTest_1815, ClearToOne_1815) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            EXPECT_EQ(bitmap.getPixel(x, y), 1);
        }
    }
}

// Test setPixel and getPixel
TEST_F(JBIG2BitmapTest_1815, SetAndGetPixel_1815) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    // Adjacent pixels should still be zero
    EXPECT_EQ(bitmap.getPixel(4, 5), 0);
    EXPECT_EQ(bitmap.getPixel(6, 5), 0);
    EXPECT_EQ(bitmap.getPixel(5, 4), 0);
    EXPECT_EQ(bitmap.getPixel(5, 6), 0);
}

// Test clearPixel
TEST_F(JBIG2BitmapTest_1815, ClearPixel_1815) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    bitmap.clearPixel(3, 3);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
    // Adjacent pixels should still be one
    EXPECT_EQ(bitmap.getPixel(2, 3), 1);
    EXPECT_EQ(bitmap.getPixel(4, 3), 1);
}

// Test getPixel out of bounds returns 0
TEST_F(JBIG2BitmapTest_1815, GetPixelOutOfBounds_1815) {
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

// Test setPixel at corners
TEST_F(JBIG2BitmapTest_1815, SetPixelAtCorners_1815) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.setPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    
    bitmap.setPixel(9, 0);
    EXPECT_EQ(bitmap.getPixel(9, 0), 1);
    
    bitmap.setPixel(0, 9);
    EXPECT_EQ(bitmap.getPixel(0, 9), 1);
    
    bitmap.setPixel(9, 9);
    EXPECT_EQ(bitmap.getPixel(9, 9), 1);
}

// Test getDataPtr returns non-null for valid bitmap
TEST_F(JBIG2BitmapTest_1815, GetDataPtrNonNull_1815) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_NE(bitmap.getDataPtr(), nullptr);
}

// Test expand increases height
TEST_F(JBIG2BitmapTest_1815, ExpandIncreasesHeight_1815) {
    JBIG2Bitmap bitmap(0, 10, 5);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getHeight(), 5);
    bitmap.expand(10, 0);
    EXPECT_EQ(bitmap.getHeight(), 10);
}

// Test expand with pixel value 0 fills with zeros
TEST_F(JBIG2BitmapTest_1815, ExpandWithZeroFill_1815) {
    JBIG2Bitmap bitmap(0, 8, 2);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    bitmap.expand(4, 0);
    EXPECT_EQ(bitmap.getHeight(), 4);
    // Original rows should still be one
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(0, 1), 1);
    // New rows should be zero
    EXPECT_EQ(bitmap.getPixel(0, 2), 0);
    EXPECT_EQ(bitmap.getPixel(0, 3), 0);
}

// Test expand with pixel value 1 fills with ones
TEST_F(JBIG2BitmapTest_1815, ExpandWithOneFill_1815) {
    JBIG2Bitmap bitmap(0, 8, 2);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    bitmap.expand(4, 1);
    EXPECT_EQ(bitmap.getHeight(), 4);
    // New rows should be one
    EXPECT_EQ(bitmap.getPixel(0, 2), 1);
    EXPECT_EQ(bitmap.getPixel(0, 3), 1);
}

// Test duplicateRow
TEST_F(JBIG2BitmapTest_1815, DuplicateRow_1815) {
    JBIG2Bitmap bitmap(0, 8, 4);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    // Set all pixels in row 0
    for (int x = 0; x < 8; x++) {
        bitmap.setPixel(x, 0);
    }
    // Duplicate row 0 to row 2
    bitmap.duplicateRow(2, 0);
    for (int x = 0; x < 8; x++) {
        EXPECT_EQ(bitmap.getPixel(x, 2), 1);
    }
    // Row 1 should still be zero
    for (int x = 0; x < 8; x++) {
        EXPECT_EQ(bitmap.getPixel(x, 1), 0);
    }
}

// Test getSlice basic functionality
TEST_F(JBIG2BitmapTest_1815, GetSlice_1815) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    
    auto slice = bitmap.getSlice(4, 4, 4, 4);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 4);
        EXPECT_EQ(slice->getHeight(), 4);
        // Pixel at (5,5) in original should be at (1,1) in slice
        EXPECT_EQ(slice->getPixel(1, 1), 1);
        EXPECT_EQ(slice->getPixel(0, 0), 0);
    }
}

// Test getType returns correct segment type
TEST_F(JBIG2BitmapTest_1815, GetType_1815) {
    JBIG2Bitmap bitmap(0, 10, 10);
    // JBIG2Bitmap should return its specific segment type
    // Just verify it returns some type without crashing
    auto type = bitmap.getType();
    (void)type; // We just verify it doesn't crash
}

// Test 1x1 bitmap
TEST_F(JBIG2BitmapTest_1815, SmallestBitmap_1815) {
    JBIG2Bitmap bitmap(0, 1, 1);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 1);
    EXPECT_EQ(bitmap.getHeight(), 1);
    
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    
    bitmap.setPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    
    bitmap.clearPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
}

// Test large bitmap
TEST_F(JBIG2BitmapTest_1815, LargeBitmap_1815) {
    JBIG2Bitmap bitmap(0, 1000, 1000);
    if (bitmap.isOk()) {
        EXPECT_EQ(bitmap.getWidth(), 1000);
        EXPECT_EQ(bitmap.getHeight(), 1000);
        bitmap.clearToZero();
        EXPECT_EQ(bitmap.getPixel(999, 999), 0);
        bitmap.setPixel(999, 999);
        EXPECT_EQ(bitmap.getPixel(999, 999), 1);
    }
}

// Test combine operation
TEST_F(JBIG2BitmapTest_1815, CombineOR_1815) {
    JBIG2Bitmap bitmap1(0, 8, 8);
    JBIG2Bitmap bitmap2(1, 4, 4);
    EXPECT_TRUE(bitmap1.isOk());
    EXPECT_TRUE(bitmap2.isOk());
    
    bitmap1.clearToZero();
    bitmap2.clearToOne();
    
    // Combine bitmap2 into bitmap1 at position (2, 2) with OR operation (0)
    bitmap1.combine(bitmap2, 2, 2, 0);
    
    // Pixels in the combined region should be 1
    EXPECT_EQ(bitmap1.getPixel(2, 2), 1);
    EXPECT_EQ(bitmap1.getPixel(5, 5), 1);
    
    // Pixels outside the combined region should still be 0
    EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap1.getPixel(7, 7), 0);
}

// Test getDataSize is consistent with dimensions
TEST_F(JBIG2BitmapTest_1815, DataSizeConsistency_1815) {
    JBIG2Bitmap bitmap(0, 16, 8);
    EXPECT_TRUE(bitmap.isOk());
    int lineSize = bitmap.getLineSize();
    int height = bitmap.getHeight();
    EXPECT_EQ(bitmap.getDataSize(), lineSize * height);
}

// Test segment number in construction doesn't affect bitmap properties
TEST_F(JBIG2BitmapTest_1815, DifferentSegmentNumbers_1815) {
    JBIG2Bitmap bitmap1(0, 10, 10);
    JBIG2Bitmap bitmap2(42, 10, 10);
    EXPECT_EQ(bitmap1.getWidth(), bitmap2.getWidth());
    EXPECT_EQ(bitmap1.getHeight(), bitmap2.getHeight());
    EXPECT_EQ(bitmap1.getLineSize(), bitmap2.getLineSize());
}

// Test getPixelPtr and nextPixel for sequential access
TEST_F(JBIG2BitmapTest_1815, PixelPtrIteration_1815) {
    JBIG2Bitmap bitmap(0, 8, 1);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    bitmap.setPixel(3, 0);
    bitmap.setPixel(7, 0);
    
    JBIG2BitmapPtr ptr;
    bitmap.getPixelPtr(0, 0, &ptr);
    
    // Read through the row
    for (int x = 0; x < 8; x++) {
        int pixel = bitmap.nextPixel(&ptr);
        if (x == 3 || x == 7) {
            EXPECT_EQ(pixel, 1) << "Pixel at x=" << x << " should be 1";
        } else {
            EXPECT_EQ(pixel, 0) << "Pixel at x=" << x << " should be 0";
        }
    }
}

// Test bitmap with width that's not a multiple of 8
TEST_F(JBIG2BitmapTest_1815, NonByteAlignedWidth_1815) {
    JBIG2Bitmap bitmap(0, 13, 5);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 13);
    EXPECT_EQ(bitmap.getHeight(), 5);
    // Line size should accommodate 13 bits = 2 bytes minimum
    EXPECT_GE(bitmap.getLineSize(), 2);
    
    bitmap.clearToZero();
    bitmap.setPixel(12, 4);
    EXPECT_EQ(bitmap.getPixel(12, 4), 1);
}

// Test copy preserves pixel data
TEST_F(JBIG2BitmapTest_1815, CopyPreservesPixels_1815) {
    JBIG2Bitmap original(0, 8, 8);
    EXPECT_TRUE(original.isOk());
    original.clearToZero();
    original.setPixel(3, 3);
    original.setPixel(7, 7);
    
    JBIG2Bitmap copy(&original);
    EXPECT_EQ(copy.getPixel(3, 3), 1);
    EXPECT_EQ(copy.getPixel(7, 7), 1);
    EXPECT_EQ(copy.getPixel(0, 0), 0);
}

// Verify defines
TEST_F(JBIG2BitmapTest_1815, HuffmanDefines_1815) {
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffe);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffd);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffff);
}
