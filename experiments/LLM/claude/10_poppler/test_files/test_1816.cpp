#include <gtest/gtest.h>
#include <memory>

// We need to include the necessary headers for JBIG2Bitmap
// Based on the dependency information, JBIG2Bitmap is defined in JBIG2Stream.cc
// but we need the header that declares it
#include "JBIG2Stream.h"

class JBIG2BitmapTest_1816 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test basic construction with valid dimensions
TEST_F(JBIG2BitmapTest_1816, ConstructWithValidDimensions_1816) {
    JBIG2Bitmap bitmap(0, 10, 20);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 20);
}

// Test construction with zero width and height
TEST_F(JBIG2BitmapTest_1816, ConstructWithZeroDimensions_1816) {
    JBIG2Bitmap bitmap(0, 0, 0);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test construction with width=1, height=1
TEST_F(JBIG2BitmapTest_1816, ConstructWithMinimalDimensions_1816) {
    JBIG2Bitmap bitmap(0, 1, 1);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 1);
    EXPECT_EQ(bitmap.getHeight(), 1);
}

// Test getLineSize returns reasonable value
TEST_F(JBIG2BitmapTest_1816, GetLineSizeForWidth8_1816) {
    JBIG2Bitmap bitmap(0, 8, 1);
    EXPECT_TRUE(bitmap.isOk());
    // 8 pixels should fit in 1 byte
    EXPECT_GE(bitmap.getLineSize(), 1);
}

// Test getLineSize for larger width
TEST_F(JBIG2BitmapTest_1816, GetLineSizeForWidth16_1816) {
    JBIG2Bitmap bitmap(0, 16, 1);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_GE(bitmap.getLineSize(), 2);
}

// Test getLineSize for width that is not multiple of 8
TEST_F(JBIG2BitmapTest_1816, GetLineSizeForNonByteAlignedWidth_1816) {
    JBIG2Bitmap bitmap(0, 9, 1);
    EXPECT_TRUE(bitmap.isOk());
    // 9 pixels should need at least 2 bytes
    EXPECT_GE(bitmap.getLineSize(), 2);
}

// Test getDataSize returns non-negative value
TEST_F(JBIG2BitmapTest_1816, GetDataSizePositive_1816) {
    JBIG2Bitmap bitmap(0, 10, 20);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_GE(bitmap.getDataSize(), 0);
}

// Test getDataPtr returns non-null for valid bitmap
TEST_F(JBIG2BitmapTest_1816, GetDataPtrNonNull_1816) {
    JBIG2Bitmap bitmap(0, 10, 20);
    if (bitmap.isOk()) {
        EXPECT_NE(bitmap.getDataPtr(), nullptr);
    }
}

// Test clearToZero makes all pixels zero
TEST_F(JBIG2BitmapTest_1816, ClearToZero_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(5, 5), 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(9, 9), 0);
}

// Test clearToOne makes all pixels one
TEST_F(JBIG2BitmapTest_1816, ClearToOne_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    EXPECT_EQ(bitmap.getPixel(9, 9), 1);
}

// Test setPixel and getPixel
TEST_F(JBIG2BitmapTest_1816, SetAndGetPixel_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.setPixel(3, 4);
    EXPECT_EQ(bitmap.getPixel(3, 4), 1);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
    EXPECT_EQ(bitmap.getPixel(4, 4), 0);
}

// Test clearPixel
TEST_F(JBIG2BitmapTest_1816, ClearPixel_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    
    bitmap.clearPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 0);
    EXPECT_EQ(bitmap.getPixel(4, 5), 1);
}

// Test getPixel with out-of-bounds coordinates
TEST_F(JBIG2BitmapTest_1816, GetPixelOutOfBounds_1816) {
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

// Test copy constructor
TEST_F(JBIG2BitmapTest_1816, CopyConstructor_1816) {
    JBIG2Bitmap original(0, 10, 10);
    EXPECT_TRUE(original.isOk());
    original.clearToZero();
    original.setPixel(3, 3);
    
    JBIG2Bitmap copy(&original);
    EXPECT_TRUE(copy.isOk());
    EXPECT_EQ(copy.getWidth(), original.getWidth());
    EXPECT_EQ(copy.getHeight(), original.getHeight());
    EXPECT_EQ(copy.getPixel(3, 3), 1);
    EXPECT_EQ(copy.getPixel(0, 0), 0);
}

// Test getSlice
TEST_F(JBIG2BitmapTest_1816, GetSliceBasic_1816) {
    JBIG2Bitmap bitmap(0, 20, 20);
    EXPECT_TRUE(bitmap.isOk());
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
TEST_F(JBIG2BitmapTest_1816, GetSliceWithOffset_1816) {
    JBIG2Bitmap bitmap(0, 20, 20);
    EXPECT_TRUE(bitmap.isOk());
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
TEST_F(JBIG2BitmapTest_1816, ExpandIncreasesHeight_1816) {
    JBIG2Bitmap bitmap(0, 10, 5);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getHeight(), 5);
    
    bitmap.expand(10, 0);
    EXPECT_EQ(bitmap.getHeight(), 10);
    EXPECT_EQ(bitmap.getWidth(), 10);
}

// Test expand with pixel=0 fills new rows with zeros
TEST_F(JBIG2BitmapTest_1816, ExpandWithZeroFill_1816) {
    JBIG2Bitmap bitmap(0, 10, 5);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToOne();
    
    bitmap.expand(10, 0);
    // Original pixels should still be set
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    // New rows should be zero
    EXPECT_EQ(bitmap.getPixel(0, 9), 0);
}

// Test expand with pixel=1 fills new rows with ones
TEST_F(JBIG2BitmapTest_1816, ExpandWithOneFill_1816) {
    JBIG2Bitmap bitmap(0, 10, 5);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.expand(10, 1);
    // Original pixels should still be zero
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    // New rows should be one
    EXPECT_EQ(bitmap.getPixel(0, 9), 1);
}

// Test duplicateRow
TEST_F(JBIG2BitmapTest_1816, DuplicateRow_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Set some pixels in row 2
    bitmap.setPixel(3, 2);
    bitmap.setPixel(7, 2);
    
    // Duplicate row 2 to row 5
    bitmap.duplicateRow(5, 2);
    
    EXPECT_EQ(bitmap.getPixel(3, 5), 1);
    EXPECT_EQ(bitmap.getPixel(7, 5), 1);
    EXPECT_EQ(bitmap.getPixel(0, 5), 0);
}

// Test getType returns correct segment type
TEST_F(JBIG2BitmapTest_1816, GetTypeReturnsBitmapType_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    // The type should correspond to bitmap segment type
    // Just verify it returns without crashing
    auto type = bitmap.getType();
    (void)type;
}

// Test setPixel at boundary positions
TEST_F(JBIG2BitmapTest_1816, SetPixelAtBoundaries_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Top-left corner
    bitmap.setPixel(0, 0);
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    
    // Top-right corner
    bitmap.setPixel(9, 0);
    EXPECT_EQ(bitmap.getPixel(9, 0), 1);
    
    // Bottom-left corner
    bitmap.setPixel(0, 9);
    EXPECT_EQ(bitmap.getPixel(0, 9), 1);
    
    // Bottom-right corner
    bitmap.setPixel(9, 9);
    EXPECT_EQ(bitmap.getPixel(9, 9), 1);
}

// Test large bitmap construction
TEST_F(JBIG2BitmapTest_1816, LargeBitmapConstruction_1816) {
    JBIG2Bitmap bitmap(0, 1000, 1000);
    if (bitmap.isOk()) {
        EXPECT_EQ(bitmap.getWidth(), 1000);
        EXPECT_EQ(bitmap.getHeight(), 1000);
        EXPECT_GE(bitmap.getLineSize(), 125); // At least 1000/8 bytes
    }
}

// Test getLineSize relationship with width
TEST_F(JBIG2BitmapTest_1816, LineSizeRelationshipWithWidth_1816) {
    for (int w = 1; w <= 32; w++) {
        JBIG2Bitmap bitmap(0, w, 1);
        if (bitmap.isOk()) {
            int expectedMinLineSize = (w + 7) / 8;
            EXPECT_GE(bitmap.getLineSize(), expectedMinLineSize);
        }
    }
}

// Test getDataSize is consistent with dimensions
TEST_F(JBIG2BitmapTest_1816, DataSizeConsistentWithDimensions_1816) {
    JBIG2Bitmap bitmap(0, 10, 20);
    if (bitmap.isOk()) {
        EXPECT_GE(bitmap.getDataSize(), bitmap.getLineSize() * bitmap.getHeight());
    }
}

// Test combine OR operation (combOp = 0)
TEST_F(JBIG2BitmapTest_1816, CombineOR_1816) {
    JBIG2Bitmap bitmap1(0, 10, 10);
    JBIG2Bitmap bitmap2(1, 10, 10);
    EXPECT_TRUE(bitmap1.isOk());
    EXPECT_TRUE(bitmap2.isOk());
    
    bitmap1.clearToZero();
    bitmap2.clearToZero();
    
    bitmap1.setPixel(3, 3);
    bitmap2.setPixel(5, 5);
    
    bitmap1.combine(bitmap2, 0, 0, 0); // OR operation
    
    EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
    EXPECT_EQ(bitmap1.getPixel(5, 5), 1);
}

// Test combine with offset
TEST_F(JBIG2BitmapTest_1816, CombineWithOffset_1816) {
    JBIG2Bitmap bitmap1(0, 20, 20);
    JBIG2Bitmap bitmap2(1, 5, 5);
    EXPECT_TRUE(bitmap1.isOk());
    EXPECT_TRUE(bitmap2.isOk());
    
    bitmap1.clearToZero();
    bitmap2.clearToZero();
    bitmap2.setPixel(0, 0);
    
    bitmap1.combine(bitmap2, 10, 10, 0);
    
    EXPECT_EQ(bitmap1.getPixel(10, 10), 1);
    EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
}

// Test pixel pointer navigation
TEST_F(JBIG2BitmapTest_1816, PixelPtrNavigation_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    bitmap.setPixel(3, 5);
    
    JBIG2BitmapPtr ptr;
    bitmap.getPixelPtr(0, 5, &ptr);
    
    // Navigate to pixel 3 in row 5
    for (int i = 0; i < 3; i++) {
        int pixel = bitmap.nextPixel(&ptr);
        EXPECT_EQ(pixel, 0);
    }
    int pixel = bitmap.nextPixel(&ptr);
    EXPECT_EQ(pixel, 1);
}

// Test width=1 bitmap
TEST_F(JBIG2BitmapTest_1816, SingleWidthBitmap_1816) {
    JBIG2Bitmap bitmap(0, 1, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.setPixel(0, 5);
    EXPECT_EQ(bitmap.getPixel(0, 5), 1);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
}

// Test height=1 bitmap
TEST_F(JBIG2BitmapTest_1816, SingleHeightBitmap_1816) {
    JBIG2Bitmap bitmap(0, 10, 1);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    bitmap.setPixel(5, 0);
    EXPECT_EQ(bitmap.getPixel(5, 0), 1);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
}

// Test Huffman defines
TEST_F(JBIG2BitmapTest_1816, HuffmanDefines_1816) {
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffe);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffd);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffff);
}

// Test multiple set and clear operations
TEST_F(JBIG2BitmapTest_1816, MultipleSetClearOperations_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    bitmap.clearToZero();
    
    // Set pixel, verify, clear pixel, verify
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    
    bitmap.clearPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 0);
    
    // Set again
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
}

// Test clearToZero after clearToOne
TEST_F(JBIG2BitmapTest_1816, ClearToZeroAfterClearToOne_1816) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_TRUE(bitmap.isOk());
    
    bitmap.clearToOne();
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            EXPECT_EQ(bitmap.getPixel(x, y), 1);
        }
    }
    
    bitmap.clearToZero();
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            EXPECT_EQ(bitmap.getPixel(x, y), 0);
        }
    }
}

// Test segment number in construction
TEST_F(JBIG2BitmapTest_1816, ConstructionWithDifferentSegNums_1816) {
    JBIG2Bitmap bitmap1(0, 10, 10);
    JBIG2Bitmap bitmap2(42, 10, 10);
    JBIG2Bitmap bitmap3(UINT_MAX, 10, 10);
    
    // All should construct successfully with same dimensions
    if (bitmap1.isOk()) {
        EXPECT_EQ(bitmap1.getWidth(), 10);
    }
    if (bitmap2.isOk()) {
        EXPECT_EQ(bitmap2.getWidth(), 10);
    }
    if (bitmap3.isOk()) {
        EXPECT_EQ(bitmap3.getWidth(), 10);
    }
}
