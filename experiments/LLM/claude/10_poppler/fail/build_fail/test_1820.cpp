#include <gtest/gtest.h>
#include <memory>

// We need to include the necessary headers for JBIG2Bitmap
// Based on the dependency information, JBIG2Bitmap is defined in JBIG2Stream.cc
// but we need the header
#include "JBIG2Stream.h"

class JBIG2BitmapTest_1820 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with valid dimensions
TEST_F(JBIG2BitmapTest_1820, ConstructWithValidDimensions_1820) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 10);
}

// Test construction with zero dimensions
TEST_F(JBIG2BitmapTest_1820, ConstructWithZeroDimensions_1820) {
    JBIG2Bitmap bitmap(0, 0, 0);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test construction with width=1, height=1 (minimum non-zero)
TEST_F(JBIG2BitmapTest_1820, ConstructWithMinimalDimensions_1820) {
    JBIG2Bitmap bitmap(0, 1, 1);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 1);
    EXPECT_EQ(bitmap.getHeight(), 1);
}

// Test copy constructor
TEST_F(JBIG2BitmapTest_1820, CopyConstruction_1820) {
    JBIG2Bitmap original(0, 20, 15);
    EXPECT_TRUE(original.isOk());
    
    JBIG2Bitmap copy(&original);
    EXPECT_TRUE(copy.isOk());
    EXPECT_EQ(copy.getWidth(), 20);
    EXPECT_EQ(copy.getHeight(), 15);
}

// Test getWidth and getHeight
TEST_F(JBIG2BitmapTest_1820, GetWidthAndHeight_1820) {
    JBIG2Bitmap bitmap(0, 100, 200);
    EXPECT_EQ(bitmap.getWidth(), 100);
    EXPECT_EQ(bitmap.getHeight(), 200);
}

// Test clearToZero sets all pixels to zero
TEST_F(JBIG2BitmapTest_1820, ClearToZero_1820) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_TRUE(bitmap.isOk());
    
    // Set some pixels first
    bitmap.setPixel(0, 0);
    bitmap.setPixel(3, 3);
    
    bitmap.clearToZero();
    
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
    EXPECT_EQ(bitmap.getPixel(7, 7), 0);
}

// Test clearToOne sets all pixels to one
TEST_F(JBIG2BitmapTest_1820, ClearToOne_1820) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToOne();
    
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(3, 3), 1);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
}

// Test setPixel and getPixel
TEST_F(JBIG2BitmapTest_1820, SetAndGetPixel_1820) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    
    bitmap.setPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    
    // Unset pixel should be 0
    EXPECT_EQ(bitmap.getPixel(1, 1), 0);
}

// Test clearPixel
TEST_F(JBIG2BitmapTest_1820, ClearPixel_1820) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToOne();
    EXPECT_EQ(bitmap.getPixel(3, 3), 1);
    
    bitmap.clearPixel(3, 3);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
}

// Test getPixel with out-of-bounds coordinates
TEST_F(JBIG2BitmapTest_1820, GetPixelOutOfBounds_1820) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_TRUE(bitmap.isOk());
    
    // Out of bounds should return 0
    EXPECT_EQ(bitmap.getPixel(-1, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, -1), 0);
    EXPECT_EQ(bitmap.getPixel(8, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, 8), 0);
    EXPECT_EQ(bitmap.getPixel(100, 100), 0);
}

// Test getDataPtr returns non-null for valid bitmap
TEST_F(JBIG2BitmapTest_1820, GetDataPtr_1820) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_NE(bitmap.getDataPtr(), nullptr);
}

// Test getDataSize
TEST_F(JBIG2BitmapTest_1820, GetDataSize_1820) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_GT(bitmap.getDataSize(), 0);
}

// Test getLineSize
TEST_F(JBIG2BitmapTest_1820, GetLineSize_1820) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_GT(bitmap.getLineSize(), 0);
}

// Test getLineSize for different widths
TEST_F(JBIG2BitmapTest_1820, GetLineSizeVariousWidths_1820) {
    // 1 pixel wide - line size should be at least 1 byte
    JBIG2Bitmap bitmap1(0, 1, 1);
    if (bitmap1.isOk()) {
        EXPECT_GE(bitmap1.getLineSize(), 1);
    }
    
    // 8 pixels wide - line size should be at least 1 byte
    JBIG2Bitmap bitmap8(0, 8, 1);
    if (bitmap8.isOk()) {
        EXPECT_GE(bitmap8.getLineSize(), 1);
    }
    
    // 9 pixels wide - line size should be at least 2 bytes
    JBIG2Bitmap bitmap9(0, 9, 1);
    if (bitmap9.isOk()) {
        EXPECT_GE(bitmap9.getLineSize(), 2);
    }
}

// Test expand functionality
TEST_F(JBIG2BitmapTest_1820, ExpandHeight_1820) {
    JBIG2Bitmap bitmap(0, 8, 4);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getHeight(), 4);
    
    bitmap.expand(8, 0);
    EXPECT_EQ(bitmap.getHeight(), 8);
    EXPECT_EQ(bitmap.getWidth(), 8);
}

// Test expand with pixel=1 fills new rows
TEST_F(JBIG2BitmapTest_1820, ExpandWithOnes_1820) {
    JBIG2Bitmap bitmap(0, 8, 2);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    bitmap.expand(4, 1);
    
    EXPECT_EQ(bitmap.getHeight(), 4);
    // New rows (2,3) should be filled with 1s
    EXPECT_EQ(bitmap.getPixel(0, 2), 1);
    EXPECT_EQ(bitmap.getPixel(0, 3), 1);
}

// Test expand with pixel=0 fills new rows with zeros
TEST_F(JBIG2BitmapTest_1820, ExpandWithZeros_1820) {
    JBIG2Bitmap bitmap(0, 8, 2);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToOne();
    bitmap.expand(4, 0);
    
    EXPECT_EQ(bitmap.getHeight(), 4);
    // New rows should be filled with 0s
    EXPECT_EQ(bitmap.getPixel(0, 2), 0);
    EXPECT_EQ(bitmap.getPixel(0, 3), 0);
    // Old rows should still be 1s
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(0, 1), 1);
}

// Test duplicateRow
TEST_F(JBIG2BitmapTest_1820, DuplicateRow_1820) {
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
}

// Test getSlice
TEST_F(JBIG2BitmapTest_1820, GetSlice_1820) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    bitmap.setPixel(4, 4);
    
    auto slice = bitmap.getSlice(0, 0, 8, 8);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 8);
        EXPECT_EQ(slice->getHeight(), 8);
        EXPECT_EQ(slice->getPixel(4, 4), 1);
        EXPECT_EQ(slice->getPixel(0, 0), 0);
    }
}

// Test getSlice with offset
TEST_F(JBIG2BitmapTest_1820, GetSliceWithOffset_1820) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    bitmap.setPixel(10, 10);
    
    auto slice = bitmap.getSlice(8, 8, 8, 8);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 8);
        EXPECT_EQ(slice->getHeight(), 8);
        EXPECT_EQ(slice->getPixel(2, 2), 1);
    }
}

// Test getSegmentType
TEST_F(JBIG2BitmapTest_1820, GetType_1820) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_TRUE(bitmap.isOk());
    // Just verify it returns without crashing
    auto type = bitmap.getType();
    (void)type;
}

// Test setPixel at boundary positions
TEST_F(JBIG2BitmapTest_1820, SetPixelBoundary_1820) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Set pixel at corners
    bitmap.setPixel(0, 0);
    bitmap.setPixel(7, 0);
    bitmap.setPixel(0, 7);
    bitmap.setPixel(7, 7);
    
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(7, 0), 1);
    EXPECT_EQ(bitmap.getPixel(0, 7), 1);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
    
    // Middle should still be 0
    EXPECT_EQ(bitmap.getPixel(4, 4), 0);
}

// Test large bitmap
TEST_F(JBIG2BitmapTest_1820, LargeBitmap_1820) {
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

// Test bitmap with non-byte-aligned width
TEST_F(JBIG2BitmapTest_1820, NonByteAlignedWidth_1820) {
    JBIG2Bitmap bitmap(0, 13, 5);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    
    bitmap.setPixel(12, 4);
    EXPECT_EQ(bitmap.getPixel(12, 4), 1);
    EXPECT_EQ(bitmap.getPixel(11, 4), 0);
}

// Test combine operation
TEST_F(JBIG2BitmapTest_1820, CombineOR_1820) {
    JBIG2Bitmap bitmap1(0, 8, 8);
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
TEST_F(JBIG2BitmapTest_1820, CombineWithOffset_1820) {
    JBIG2Bitmap bitmap1(0, 16, 16);
    JBIG2Bitmap bitmap2(1, 4, 4);
    EXPECT_TRUE(bitmap1.isOk());
    EXPECT_TRUE(bitmap2.isOk());
    
    bitmap1.clearToZero();
    bitmap2.clearToOne();
    
    bitmap1.combine(bitmap2, 4, 4, 0);
    
    // Pixel at (4,4) should be set after combining
    EXPECT_EQ(bitmap1.getPixel(4, 4), 1);
    // Pixel outside combined area should be 0
    EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
}

// Test pixel pointer iteration
TEST_F(JBIG2BitmapTest_1820, PixelPointerIteration_1820) {
    JBIG2Bitmap bitmap(0, 8, 1);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    bitmap.setPixel(3, 0);
    bitmap.setPixel(7, 0);
    
    JBIG2BitmapPtr ptr;
    bitmap.getPixelPtr(0, 0, &ptr);
    
    // Read through pixels
    for (int x = 0; x < 8; x++) {
        int pixel = bitmap.nextPixel(&ptr);
        if (x == 3 || x == 7) {
            EXPECT_EQ(pixel, 1) << "Pixel at x=" << x << " should be 1";
        } else {
            EXPECT_EQ(pixel, 0) << "Pixel at x=" << x << " should be 0";
        }
    }
}

// Test data size relationship to dimensions
TEST_F(JBIG2BitmapTest_1820, DataSizeConsistency_1820) {
    JBIG2Bitmap bitmap(0, 32, 10);
    EXPECT_TRUE(bitmap.isOk());
    
    int lineSize = bitmap.getLineSize();
    int dataSize = bitmap.getDataSize();
    
    // Data size should be at least lineSize * height
    EXPECT_GE(dataSize, lineSize * bitmap.getHeight());
}

// Test copy preserves pixel data
TEST_F(JBIG2BitmapTest_1820, CopyPreservesPixelData_1820) {
    JBIG2Bitmap original(0, 16, 16);
    EXPECT_TRUE(original.isOk());
    
    original.clearToZero();
    original.setPixel(5, 5);
    original.setPixel(10, 10);
    
    JBIG2Bitmap copy(&original);
    EXPECT_TRUE(copy.isOk());
    
    EXPECT_EQ(copy.getPixel(5, 5), 1);
    EXPECT_EQ(copy.getPixel(10, 10), 1);
    EXPECT_EQ(copy.getPixel(0, 0), 0);
}

// Test Huffman defines
TEST_F(JBIG2BitmapTest_1820, HuffmanDefines_1820) {
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeU);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdU);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffU);
}

// Test setPixel then clearPixel
TEST_F(JBIG2BitmapTest_1820, SetThenClearPixel_1820) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    
    bitmap.setPixel(2, 2);
    EXPECT_EQ(bitmap.getPixel(2, 2), 1);
    
    bitmap.clearPixel(2, 2);
    EXPECT_EQ(bitmap.getPixel(2, 2), 0);
}

// Test multiple set/clear cycles
TEST_F(JBIG2BitmapTest_1820, MultipleClearCycles_1820) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_TRUE(bitmap.isOk());
    
    for (int i = 0; i < 3; i++) {
        bitmap.clearToOne();
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                EXPECT_EQ(bitmap.getPixel(x, y), 1);
            }
        }
        
        bitmap.clearToZero();
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                EXPECT_EQ(bitmap.getPixel(x, y), 0);
            }
        }
    }
}

// Test segment number
TEST_F(JBIG2BitmapTest_1820, SegmentNumber_1820) {
    JBIG2Bitmap bitmap(42, 8, 8);
    EXPECT_TRUE(bitmap.isOk());
    // The segment number is passed to the constructor; we can verify through getSegNum if available
    // but based on the interface, we just verify construction works
    EXPECT_EQ(bitmap.getWidth(), 8);
    EXPECT_EQ(bitmap.getHeight(), 8);
}

// Test width=1 bitmap operations
TEST_F(JBIG2BitmapTest_1820, SingleColumnBitmap_1820) {
    JBIG2Bitmap bitmap(0, 1, 10);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    
    bitmap.setPixel(0, 5);
    EXPECT_EQ(bitmap.getPixel(0, 5), 1);
    EXPECT_EQ(bitmap.getPixel(0, 4), 0);
    EXPECT_EQ(bitmap.getPixel(0, 6), 0);
}

// Test height=1 bitmap operations
TEST_F(JBIG2BitmapTest_1820, SingleRowBitmap_1820) {
    JBIG2Bitmap bitmap(0, 32, 1);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToZero();
    
    for (int x = 0; x < 32; x += 2) {
        bitmap.setPixel(x, 0);
    }
    
    for (int x = 0; x < 32; x++) {
        if (x % 2 == 0) {
            EXPECT_EQ(bitmap.getPixel(x, 0), 1);
        } else {
            EXPECT_EQ(bitmap.getPixel(x, 0), 0);
        }
    }
}
