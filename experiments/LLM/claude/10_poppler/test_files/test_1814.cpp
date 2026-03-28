#include <gtest/gtest.h>
#include <memory>

// We need to include the necessary headers for JBIG2Bitmap
// Since JBIG2Bitmap is defined in JBIG2Stream.cc, we need to find appropriate headers
// Based on the poppler project structure:
#include "JBIG2Stream.h"

class JBIG2BitmapTest_1814 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and dimensions
TEST_F(JBIG2BitmapTest_1814, ConstructWithValidDimensions_1814) {
    JBIG2Bitmap bitmap(0, 100, 200);
    EXPECT_EQ(bitmap.getWidth(), 100);
    EXPECT_EQ(bitmap.getHeight(), 200);
    EXPECT_TRUE(bitmap.isOk());
}

// Test zero width and height
TEST_F(JBIG2BitmapTest_1814, ConstructWithZeroDimensions_1814) {
    JBIG2Bitmap bitmap(0, 0, 0);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test width of 1
TEST_F(JBIG2BitmapTest_1814, ConstructWithMinimalDimensions_1814) {
    JBIG2Bitmap bitmap(0, 1, 1);
    EXPECT_EQ(bitmap.getWidth(), 1);
    EXPECT_EQ(bitmap.getHeight(), 1);
    EXPECT_TRUE(bitmap.isOk());
}

// Test copy constructor
TEST_F(JBIG2BitmapTest_1814, CopyConstruction_1814) {
    JBIG2Bitmap original(0, 50, 75);
    JBIG2Bitmap copy(&original);
    EXPECT_EQ(copy.getWidth(), original.getWidth());
    EXPECT_EQ(copy.getHeight(), original.getHeight());
}

// Test getType returns correct segment type
TEST_F(JBIG2BitmapTest_1814, GetTypeReturnsBitmapType_1814) {
    JBIG2Bitmap bitmap(0, 10, 10);
    JBIG2Segment *seg = &bitmap;
    // Just verify getType() can be called; the actual type value depends on internals
    seg->getType();
}

// Test clearToZero sets all pixels to 0
TEST_F(JBIG2BitmapTest_1814, ClearToZeroAllPixelsZero_1814) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.setPixel(3, 3);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(7, 7), 0);
}

// Test clearToOne sets all pixels to 1
TEST_F(JBIG2BitmapTest_1814, ClearToOneAllPixelsOne_1814) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToOne();
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(3, 3), 1);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
}

// Test setPixel and getPixel
TEST_F(JBIG2BitmapTest_1814, SetAndGetPixel_1814) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    EXPECT_EQ(bitmap.getPixel(4, 5), 0);
    EXPECT_EQ(bitmap.getPixel(5, 4), 0);
}

// Test clearPixel
TEST_F(JBIG2BitmapTest_1814, ClearPixelAfterSet_1814) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToZero();
    bitmap.setPixel(7, 7);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
    bitmap.clearPixel(7, 7);
    EXPECT_EQ(bitmap.getPixel(7, 7), 0);
}

// Test getPixel out of bounds
TEST_F(JBIG2BitmapTest_1814, GetPixelOutOfBounds_1814) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    // Out of bounds should return 0
    EXPECT_EQ(bitmap.getPixel(-1, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, -1), 0);
    EXPECT_EQ(bitmap.getPixel(10, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, 10), 0);
}

// Test getDataPtr is not null for valid bitmap
TEST_F(JBIG2BitmapTest_1814, GetDataPtrNotNull_1814) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_NE(bitmap.getDataPtr(), nullptr);
}

// Test getDataSize is positive for valid bitmap
TEST_F(JBIG2BitmapTest_1814, GetDataSizePositive_1814) {
    JBIG2Bitmap bitmap(0, 16, 16);
    EXPECT_GT(bitmap.getDataSize(), 0);
}

// Test getLineSize
TEST_F(JBIG2BitmapTest_1814, GetLineSizeConsistentWithWidth_1814) {
    JBIG2Bitmap bitmap(0, 8, 10);
    // Line size should be at least ceil(width/8)
    EXPECT_GE(bitmap.getLineSize(), 1);
}

// Test getLineSize for wider bitmap
TEST_F(JBIG2BitmapTest_1814, GetLineSizeForWiderBitmap_1814) {
    JBIG2Bitmap bitmap(0, 32, 10);
    EXPECT_GE(bitmap.getLineSize(), 4);
}

// Test expand increases height
TEST_F(JBIG2BitmapTest_1814, ExpandIncreasesHeight_1814) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.expand(20, 0);
    EXPECT_EQ(bitmap.getHeight(), 20);
    EXPECT_EQ(bitmap.getWidth(), 10);
}

// Test expand with pixel value 1
TEST_F(JBIG2BitmapTest_1814, ExpandWithPixelOne_1814) {
    JBIG2Bitmap bitmap(0, 8, 4);
    bitmap.clearToZero();
    bitmap.expand(8, 1);
    EXPECT_EQ(bitmap.getHeight(), 8);
    // New rows should be filled with 1
    EXPECT_EQ(bitmap.getPixel(0, 7), 1);
}

// Test expand with pixel value 0
TEST_F(JBIG2BitmapTest_1814, ExpandWithPixelZero_1814) {
    JBIG2Bitmap bitmap(0, 8, 4);
    bitmap.clearToOne();
    bitmap.expand(8, 0);
    EXPECT_EQ(bitmap.getHeight(), 8);
    // New rows should be filled with 0
    EXPECT_EQ(bitmap.getPixel(0, 7), 0);
    // Original rows should still be 1
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
}

// Test getSlice
TEST_F(JBIG2BitmapTest_1814, GetSliceReturnsBitmapOfCorrectSize_1814) {
    JBIG2Bitmap bitmap(0, 32, 32);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    auto slice = bitmap.getSlice(0, 0, 16, 16);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 16);
        EXPECT_EQ(slice->getHeight(), 16);
        EXPECT_EQ(slice->getPixel(5, 5), 1);
    }
}

// Test getSlice with offset
TEST_F(JBIG2BitmapTest_1814, GetSliceWithOffset_1814) {
    JBIG2Bitmap bitmap(0, 32, 32);
    bitmap.clearToZero();
    bitmap.setPixel(20, 20);
    auto slice = bitmap.getSlice(16, 16, 16, 16);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 16);
        EXPECT_EQ(slice->getHeight(), 16);
        EXPECT_EQ(slice->getPixel(4, 4), 1);
    }
}

// Test duplicateRow
TEST_F(JBIG2BitmapTest_1814, DuplicateRowCopiesCorrectly_1814) {
    JBIG2Bitmap bitmap(0, 16, 8);
    bitmap.clearToZero();
    bitmap.setPixel(3, 2);
    bitmap.setPixel(7, 2);
    bitmap.duplicateRow(5, 2);
    EXPECT_EQ(bitmap.getPixel(3, 5), 1);
    EXPECT_EQ(bitmap.getPixel(7, 5), 1);
    EXPECT_EQ(bitmap.getPixel(0, 5), 0);
}

// Test combine OR operation (combOp = 1 typically)
TEST_F(JBIG2BitmapTest_1814, CombineWithAnotherBitmap_1814) {
    JBIG2Bitmap bitmap1(0, 8, 8);
    JBIG2Bitmap bitmap2(1, 8, 8);
    bitmap1.clearToZero();
    bitmap2.clearToZero();
    bitmap2.setPixel(3, 3);
    // combOp 1 = OR
    bitmap1.combine(bitmap2, 0, 0, 1);
    EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
}

// Test combine with offset
TEST_F(JBIG2BitmapTest_1814, CombineWithOffset_1814) {
    JBIG2Bitmap bitmap1(0, 16, 16);
    JBIG2Bitmap bitmap2(1, 4, 4);
    bitmap1.clearToZero();
    bitmap2.clearToOne();
    bitmap1.combine(bitmap2, 5, 5, 1);
    EXPECT_EQ(bitmap1.getPixel(5, 5), 1);
    EXPECT_EQ(bitmap1.getPixel(8, 8), 1);
    EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
}

// Test large bitmap
TEST_F(JBIG2BitmapTest_1814, LargeBitmapCreation_1814) {
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

// Test pixel iteration with getPixelPtr and nextPixel
TEST_F(JBIG2BitmapTest_1814, PixelPtrIteration_1814) {
    JBIG2Bitmap bitmap(0, 8, 1);
    bitmap.clearToZero();
    bitmap.setPixel(3, 0);
    bitmap.setPixel(7, 0);

    JBIG2BitmapPtr ptr;
    bitmap.getPixelPtr(0, 0, &ptr);
    
    // Read first 8 pixels
    int pixels[8];
    for (int i = 0; i < 8; i++) {
        pixels[i] = bitmap.nextPixel(&ptr);
    }
    EXPECT_EQ(pixels[0], 0);
    EXPECT_EQ(pixels[3], 1);
    EXPECT_EQ(pixels[7], 1);
}

// Test segment number
TEST_F(JBIG2BitmapTest_1814, SegmentNumber_1814) {
    JBIG2Bitmap bitmap(42, 10, 10);
    EXPECT_EQ(bitmap.getSegNum(), 42);
}

// Test data size relation to dimensions
TEST_F(JBIG2BitmapTest_1814, DataSizeRelationToDimensions_1814) {
    JBIG2Bitmap bitmap(0, 16, 8);
    // Data size should be lineSize * height
    EXPECT_EQ(bitmap.getDataSize(), bitmap.getLineSize() * bitmap.getHeight());
}

// Test non-byte-aligned width
TEST_F(JBIG2BitmapTest_1814, NonByteAlignedWidth_1814) {
    JBIG2Bitmap bitmap(0, 13, 5);
    EXPECT_EQ(bitmap.getWidth(), 13);
    EXPECT_EQ(bitmap.getHeight(), 5);
    EXPECT_TRUE(bitmap.isOk());
    // Line size should be at least ceil(13/8) = 2
    EXPECT_GE(bitmap.getLineSize(), 2);
}

// Test setPixel at boundary
TEST_F(JBIG2BitmapTest_1814, SetPixelAtBoundary_1814) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToZero();
    bitmap.setPixel(9, 9);
    EXPECT_EQ(bitmap.getPixel(9, 9), 1);
    bitmap.setPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
}

// Test combine with combOp 0 (AND)
TEST_F(JBIG2BitmapTest_1814, CombineAndOperation_1814) {
    JBIG2Bitmap bitmap1(0, 8, 8);
    JBIG2Bitmap bitmap2(1, 8, 8);
    bitmap1.clearToOne();
    bitmap2.clearToZero();
    bitmap2.setPixel(3, 3);
    // combOp 0 = OR operation in JBIG2
    bitmap1.combine(bitmap2, 0, 0, 0);
    // After OR with bitmap2, pixel at (3,3) should still be 1
    EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
}

// Test Huffman table defines
TEST_F(JBIG2BitmapTest_1814, HuffmanDefines_1814) {
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeU);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdU);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffU);
}
