#include <gtest/gtest.h>
#include <memory>

// We need to include the necessary headers for JBIG2Bitmap
// Since JBIG2Bitmap is defined in JBIG2Stream.cc, we need to find the right way to include it
// Based on the poppler project structure:

// Forward declarations and minimal includes to make JBIG2Bitmap available
// The JBIG2Bitmap class is internal to JBIG2Stream.cc, so we need to work with what's available

// Since JBIG2Bitmap is defined in a .cc file and not a header, we may need to include it directly
// or recreate the test interface. Given the constraints, we'll include the source.

#include "JBIG2Stream.h"

// If JBIG2Bitmap is not accessible via the header, we need to include the .cc
// This is unusual but necessary given the class is defined in the .cc file
#include "JBIG2Stream.cc"

class JBIG2BitmapTest_1818 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction with valid dimensions
TEST_F(JBIG2BitmapTest_1818, ConstructWithValidDimensions_1818) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 10);
}

// Test construction with zero dimensions
TEST_F(JBIG2BitmapTest_1818, ConstructWithZeroDimensions_1818) {
    JBIG2Bitmap bitmap(0, 0, 0);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test construction with width=1, height=1
TEST_F(JBIG2BitmapTest_1818, ConstructWithMinimalDimensions_1818) {
    JBIG2Bitmap bitmap(0, 1, 1);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 1);
    EXPECT_EQ(bitmap.getHeight(), 1);
}

// Test copy construction
TEST_F(JBIG2BitmapTest_1818, CopyConstruction_1818) {
    JBIG2Bitmap original(0, 8, 8);
    original.setPixel(3, 3);
    JBIG2Bitmap copy(&original);
    EXPECT_EQ(copy.getWidth(), 8);
    EXPECT_EQ(copy.getHeight(), 8);
    EXPECT_EQ(copy.getPixel(3, 3), 1);
}

// Test setPixel and getPixel
TEST_F(JBIG2BitmapTest_1818, SetAndGetPixel_1818) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(5, 5), 0);
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
}

// Test clearPixel
TEST_F(JBIG2BitmapTest_1818, ClearPixel_1818) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToZero();
    bitmap.setPixel(7, 7);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
    bitmap.clearPixel(7, 7);
    EXPECT_EQ(bitmap.getPixel(7, 7), 0);
}

// Test clearToZero
TEST_F(JBIG2BitmapTest_1818, ClearToZero_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.setPixel(0, 0);
    bitmap.setPixel(3, 3);
    bitmap.setPixel(7, 7);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
    EXPECT_EQ(bitmap.getPixel(7, 7), 0);
}

// Test clearToOne
TEST_F(JBIG2BitmapTest_1818, ClearToOne_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToZero();
    bitmap.clearToOne();
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(3, 3), 1);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
}

// Test getPixel out of bounds returns 0
TEST_F(JBIG2BitmapTest_1818, GetPixelOutOfBounds_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToOne();
    // Out of bounds should return 0
    EXPECT_EQ(bitmap.getPixel(-1, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, -1), 0);
    EXPECT_EQ(bitmap.getPixel(8, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, 8), 0);
}

// Test setPixel at boundary positions
TEST_F(JBIG2BitmapTest_1818, SetPixelAtBoundaries_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToZero();
    
    // Set corners
    bitmap.setPixel(0, 0);
    bitmap.setPixel(7, 0);
    bitmap.setPixel(0, 7);
    bitmap.setPixel(7, 7);
    
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(7, 0), 1);
    EXPECT_EQ(bitmap.getPixel(0, 7), 1);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
    
    // Middle should still be zero
    EXPECT_EQ(bitmap.getPixel(4, 4), 0);
}

// Test getLineSize
TEST_F(JBIG2BitmapTest_1818, GetLineSize_1818) {
    // 8 pixels wide = 1 byte per line
    JBIG2Bitmap bitmap1(0, 8, 1);
    EXPECT_GE(bitmap1.getLineSize(), 1);
    
    // 9 pixels wide = 2 bytes per line (at minimum)
    JBIG2Bitmap bitmap2(0, 9, 1);
    EXPECT_GE(bitmap2.getLineSize(), 2);
    
    // 16 pixels wide = 2 bytes per line
    JBIG2Bitmap bitmap3(0, 16, 1);
    EXPECT_GE(bitmap3.getLineSize(), 2);
}

// Test getDataPtr is not null for valid bitmap
TEST_F(JBIG2BitmapTest_1818, GetDataPtrNotNull_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_NE(bitmap.getDataPtr(), nullptr);
}

// Test getDataSize
TEST_F(JBIG2BitmapTest_1818, GetDataSize_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_EQ(bitmap.getDataSize(), bitmap.getLineSize() * bitmap.getHeight());
}

// Test getType returns JBIG2 bitmap type
TEST_F(JBIG2BitmapTest_1818, GetType_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    EXPECT_EQ(bitmap.getType(), jbig2SegBitmap);
}

// Test expand increases height
TEST_F(JBIG2BitmapTest_1818, ExpandIncreasesHeight_1818) {
    JBIG2Bitmap bitmap(0, 8, 4);
    bitmap.clearToZero();
    bitmap.setPixel(3, 2);
    
    bitmap.expand(8, 0);
    EXPECT_EQ(bitmap.getHeight(), 8);
    // Original pixel should still be set
    EXPECT_EQ(bitmap.getPixel(3, 2), 1);
    // New area should be cleared to 0
    EXPECT_EQ(bitmap.getPixel(3, 6), 0);
}

// Test expand with pixel=1 fills new rows
TEST_F(JBIG2BitmapTest_1818, ExpandWithPixelOne_1818) {
    JBIG2Bitmap bitmap(0, 8, 4);
    bitmap.clearToZero();
    
    bitmap.expand(8, 1);
    EXPECT_EQ(bitmap.getHeight(), 8);
    // New rows should have pixel value 1
    EXPECT_EQ(bitmap.getPixel(0, 5), 1);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
    // Original rows should still be 0
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
}

// Test duplicateRow
TEST_F(JBIG2BitmapTest_1818, DuplicateRow_1818) {
    JBIG2Bitmap bitmap(0, 8, 4);
    bitmap.clearToZero();
    bitmap.setPixel(0, 0);
    bitmap.setPixel(3, 0);
    bitmap.setPixel(7, 0);
    
    bitmap.duplicateRow(2, 0);
    
    EXPECT_EQ(bitmap.getPixel(0, 2), 1);
    EXPECT_EQ(bitmap.getPixel(3, 2), 1);
    EXPECT_EQ(bitmap.getPixel(7, 2), 1);
    // Other pixels in destination row should match source
    EXPECT_EQ(bitmap.getPixel(1, 2), 0);
}

// Test getSlice
TEST_F(JBIG2BitmapTest_1818, GetSlice_1818) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    bitmap.setPixel(6, 6);
    
    auto slice = bitmap.getSlice(4, 4, 4, 4);
    ASSERT_NE(slice, nullptr);
    EXPECT_EQ(slice->getWidth(), 4);
    EXPECT_EQ(slice->getHeight(), 4);
    // Pixel at (5,5) in original = (1,1) in slice
    EXPECT_EQ(slice->getPixel(1, 1), 1);
    // Pixel at (6,6) in original = (2,2) in slice
    EXPECT_EQ(slice->getPixel(2, 2), 1);
    // Other pixels should be 0
    EXPECT_EQ(slice->getPixel(0, 0), 0);
}

// Test setPixel multiple times on same pixel is idempotent
TEST_F(JBIG2BitmapTest_1818, SetPixelIdempotent_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToZero();
    bitmap.setPixel(3, 3);
    bitmap.setPixel(3, 3);
    EXPECT_EQ(bitmap.getPixel(3, 3), 1);
}

// Test clearPixel on already clear pixel
TEST_F(JBIG2BitmapTest_1818, ClearPixelOnAlreadyClear_1818) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToZero();
    bitmap.clearPixel(3, 3);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
}

// Test wide bitmap (non-byte-aligned width)
TEST_F(JBIG2BitmapTest_1818, NonByteAlignedWidth_1818) {
    JBIG2Bitmap bitmap(0, 13, 5);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.setPixel(12, 4);
    EXPECT_EQ(bitmap.getPixel(12, 4), 1);
    EXPECT_EQ(bitmap.getPixel(11, 4), 0);
}

// Test large bitmap
TEST_F(JBIG2BitmapTest_1818, LargeBitmap_1818) {
    JBIG2Bitmap bitmap(0, 1000, 1000);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.setPixel(999, 999);
        EXPECT_EQ(bitmap.getPixel(999, 999), 1);
        EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    }
}

// Test getPixelPtr and nextPixel
TEST_F(JBIG2BitmapTest_1818, GetPixelPtrAndNextPixel_1818) {
    JBIG2Bitmap bitmap(0, 8, 1);
    bitmap.clearToZero();
    bitmap.setPixel(0, 0);
    bitmap.setPixel(3, 0);
    bitmap.setPixel(7, 0);
    
    JBIG2BitmapPtr ptr;
    bitmap.getPixelPtr(0, 0, &ptr);
    
    // Read first pixel (should be 1)
    int p0 = bitmap.nextPixel(&ptr);
    EXPECT_EQ(p0, 1);
    
    // Read next pixels
    int p1 = bitmap.nextPixel(&ptr);
    EXPECT_EQ(p1, 0);
    
    int p2 = bitmap.nextPixel(&ptr);
    EXPECT_EQ(p2, 0);
    
    int p3 = bitmap.nextPixel(&ptr);
    EXPECT_EQ(p3, 1);
}

// Test combine with OR operation (combOp = 1 typically)
TEST_F(JBIG2BitmapTest_1818, CombineBitmaps_1818) {
    JBIG2Bitmap bitmap1(0, 8, 8);
    JBIG2Bitmap bitmap2(1, 4, 4);
    
    bitmap1.clearToZero();
    bitmap2.clearToZero();
    bitmap2.setPixel(0, 0);
    bitmap2.setPixel(1, 1);
    
    // Combine with OR at position (2, 2)
    bitmap1.combine(bitmap2, 2, 2, 0); // combOp 0 = OR
    
    EXPECT_EQ(bitmap1.getPixel(2, 2), 1);
    EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
    EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
}

// Test Huffman constants are defined correctly
TEST_F(JBIG2BitmapTest_1818, HuffmanConstants_1818) {
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeU);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdU);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffU);
}

// Test single-pixel width bitmap
TEST_F(JBIG2BitmapTest_1818, SinglePixelWidth_1818) {
    JBIG2Bitmap bitmap(0, 1, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.setPixel(0, 5);
    EXPECT_EQ(bitmap.getPixel(0, 5), 1);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, 9), 0);
}

// Test single-pixel height bitmap
TEST_F(JBIG2BitmapTest_1818, SinglePixelHeight_1818) {
    JBIG2Bitmap bitmap(0, 10, 1);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.setPixel(5, 0);
    EXPECT_EQ(bitmap.getPixel(5, 0), 1);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
}

// Test all pixels in a byte boundary
TEST_F(JBIG2BitmapTest_1818, AllPixelsInOneByte_1818) {
    JBIG2Bitmap bitmap(0, 8, 1);
    bitmap.clearToZero();
    
    for (int i = 0; i < 8; i++) {
        bitmap.setPixel(i, 0);
    }
    
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(bitmap.getPixel(i, 0), 1) << "Pixel " << i << " should be 1";
    }
}

// Test clearToZero after clearToOne
TEST_F(JBIG2BitmapTest_1818, ClearToZeroAfterClearToOne_1818) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToOne();
    
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            EXPECT_EQ(bitmap.getPixel(x, y), 1);
        }
    }
    
    bitmap.clearToZero();
    
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            EXPECT_EQ(bitmap.getPixel(x, y), 0);
        }
    }
}
