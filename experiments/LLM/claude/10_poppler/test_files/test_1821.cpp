#include <gtest/gtest.h>
#include <memory>

// We need to include the necessary headers for JBIG2Bitmap
// Based on the known dependencies, we need to set up minimal includes
#include "JBIG2Stream.h"

// Test fixture for JBIG2Bitmap
class JBIG2BitmapTest_1821 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Construction with valid dimensions
TEST_F(JBIG2BitmapTest_1821, ConstructWithValidDimensions_1821) {
    JBIG2Bitmap bitmap(0, 10, 20);
    EXPECT_TRUE(bitmap.isOk());
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 20);
}

// Test: getDataSize returns height * lineSize
TEST_F(JBIG2BitmapTest_1821, GetDataSizeReturnsCorrectValue_1821) {
    JBIG2Bitmap bitmap(0, 10, 20);
    if (bitmap.isOk()) {
        int expectedSize = bitmap.getHeight() * bitmap.getLineSize();
        EXPECT_EQ(bitmap.getDataSize(), expectedSize);
    }
}

// Test: Construction with zero dimensions
TEST_F(JBIG2BitmapTest_1821, ConstructWithZeroDimensions_1821) {
    JBIG2Bitmap bitmap(0, 0, 0);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 0);
    EXPECT_EQ(bitmap.getDataSize(), 0);
}

// Test: Construction with zero width
TEST_F(JBIG2BitmapTest_1821, ConstructWithZeroWidth_1821) {
    JBIG2Bitmap bitmap(0, 0, 10);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 10);
}

// Test: Construction with zero height
TEST_F(JBIG2BitmapTest_1821, ConstructWithZeroHeight_1821) {
    JBIG2Bitmap bitmap(0, 10, 0);
    EXPECT_EQ(bitmap.getWidth(), 10);
    EXPECT_EQ(bitmap.getHeight(), 0);
    EXPECT_EQ(bitmap.getDataSize(), 0);
}

// Test: Copy constructor from another bitmap
TEST_F(JBIG2BitmapTest_1821, CopyConstructor_1821) {
    JBIG2Bitmap original(0, 16, 16);
    if (original.isOk()) {
        JBIG2Bitmap copy(&original);
        EXPECT_EQ(copy.getWidth(), original.getWidth());
        EXPECT_EQ(copy.getHeight(), original.getHeight());
        EXPECT_EQ(copy.getDataSize(), original.getDataSize());
    }
}

// Test: setPixel and getPixel
TEST_F(JBIG2BitmapTest_1821, SetAndGetPixel_1821) {
    JBIG2Bitmap bitmap(0, 32, 32);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        EXPECT_EQ(bitmap.getPixel(5, 5), 0);
        bitmap.setPixel(5, 5);
        EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    }
}

// Test: clearPixel
TEST_F(JBIG2BitmapTest_1821, ClearPixel_1821) {
    JBIG2Bitmap bitmap(0, 32, 32);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.setPixel(10, 10);
        EXPECT_EQ(bitmap.getPixel(10, 10), 1);
        bitmap.clearPixel(10, 10);
        EXPECT_EQ(bitmap.getPixel(10, 10), 0);
    }
}

// Test: clearToZero sets all pixels to zero
TEST_F(JBIG2BitmapTest_1821, ClearToZero_1821) {
    JBIG2Bitmap bitmap(0, 16, 16);
    if (bitmap.isOk()) {
        bitmap.setPixel(0, 0);
        bitmap.setPixel(5, 5);
        bitmap.setPixel(15, 15);
        bitmap.clearToZero();
        EXPECT_EQ(bitmap.getPixel(0, 0), 0);
        EXPECT_EQ(bitmap.getPixel(5, 5), 0);
        EXPECT_EQ(bitmap.getPixel(15, 15), 0);
    }
}

// Test: clearToOne sets all pixels to one
TEST_F(JBIG2BitmapTest_1821, ClearToOne_1821) {
    JBIG2Bitmap bitmap(0, 16, 16);
    if (bitmap.isOk()) {
        bitmap.clearToOne();
        EXPECT_EQ(bitmap.getPixel(0, 0), 1);
        EXPECT_EQ(bitmap.getPixel(5, 5), 1);
        EXPECT_EQ(bitmap.getPixel(15, 15), 1);
    }
}

// Test: getPixel out of bounds returns 0
TEST_F(JBIG2BitmapTest_1821, GetPixelOutOfBounds_1821) {
    JBIG2Bitmap bitmap(0, 10, 10);
    if (bitmap.isOk()) {
        EXPECT_EQ(bitmap.getPixel(-1, 0), 0);
        EXPECT_EQ(bitmap.getPixel(0, -1), 0);
        EXPECT_EQ(bitmap.getPixel(10, 0), 0);
        EXPECT_EQ(bitmap.getPixel(0, 10), 0);
        EXPECT_EQ(bitmap.getPixel(100, 100), 0);
    }
}

// Test: getDataPtr returns non-null for valid bitmap
TEST_F(JBIG2BitmapTest_1821, GetDataPtrNonNull_1821) {
    JBIG2Bitmap bitmap(0, 16, 16);
    if (bitmap.isOk()) {
        EXPECT_NE(bitmap.getDataPtr(), nullptr);
    }
}

// Test: getLineSize is at least ceil(width / 8)
TEST_F(JBIG2BitmapTest_1821, GetLineSizeAtLeastWidthDiv8_1821) {
    JBIG2Bitmap bitmap(0, 17, 10);
    if (bitmap.isOk()) {
        // line size should be at least ceil(17/8) = 3 bytes
        EXPECT_GE(bitmap.getLineSize(), 3);
    }
}

// Test: getLineSize for width that is a multiple of 8
TEST_F(JBIG2BitmapTest_1821, GetLineSizeMultipleOf8_1821) {
    JBIG2Bitmap bitmap(0, 8, 10);
    if (bitmap.isOk()) {
        EXPECT_GE(bitmap.getLineSize(), 1);
    }
}

// Test: 1x1 bitmap
TEST_F(JBIG2BitmapTest_1821, SmallBitmap1x1_1821) {
    JBIG2Bitmap bitmap(0, 1, 1);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        EXPECT_EQ(bitmap.getPixel(0, 0), 0);
        bitmap.setPixel(0, 0);
        EXPECT_EQ(bitmap.getPixel(0, 0), 1);
        EXPECT_EQ(bitmap.getWidth(), 1);
        EXPECT_EQ(bitmap.getHeight(), 1);
    }
}

// Test: duplicateRow copies a row
TEST_F(JBIG2BitmapTest_1821, DuplicateRow_1821) {
    JBIG2Bitmap bitmap(0, 16, 4);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.setPixel(3, 0);
        bitmap.setPixel(7, 0);
        bitmap.duplicateRow(2, 0);
        EXPECT_EQ(bitmap.getPixel(3, 2), 1);
        EXPECT_EQ(bitmap.getPixel(7, 2), 1);
        EXPECT_EQ(bitmap.getPixel(0, 2), 0);
    }
}

// Test: expand increases height
TEST_F(JBIG2BitmapTest_1821, ExpandIncreasesHeight_1821) {
    JBIG2Bitmap bitmap(0, 16, 10);
    if (bitmap.isOk()) {
        int origHeight = bitmap.getHeight();
        bitmap.expand(20, 0);
        EXPECT_EQ(bitmap.getHeight(), 20);
        EXPECT_GT(bitmap.getHeight(), origHeight);
    }
}

// Test: expand with pixel=0 fills new rows with 0
TEST_F(JBIG2BitmapTest_1821, ExpandFillsWithZero_1821) {
    JBIG2Bitmap bitmap(0, 16, 2);
    if (bitmap.isOk()) {
        bitmap.clearToOne();
        bitmap.expand(4, 0);
        // Original rows should be 1, new rows should be 0
        EXPECT_EQ(bitmap.getPixel(0, 0), 1);
        EXPECT_EQ(bitmap.getPixel(0, 2), 0);
        EXPECT_EQ(bitmap.getPixel(0, 3), 0);
    }
}

// Test: expand with pixel=1 fills new rows with 1
TEST_F(JBIG2BitmapTest_1821, ExpandFillsWithOne_1821) {
    JBIG2Bitmap bitmap(0, 16, 2);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.expand(4, 1);
        // Original rows should be 0, new rows should be 1
        EXPECT_EQ(bitmap.getPixel(0, 0), 0);
        EXPECT_EQ(bitmap.getPixel(0, 2), 1);
        EXPECT_EQ(bitmap.getPixel(0, 3), 1);
    }
}

// Test: getSlice returns a valid sub-bitmap
TEST_F(JBIG2BitmapTest_1821, GetSlice_1821) {
    JBIG2Bitmap bitmap(0, 32, 32);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.setPixel(5, 5);
        auto slice = bitmap.getSlice(4, 4, 8, 8);
        if (slice) {
            EXPECT_EQ(slice->getWidth(), 8);
            EXPECT_EQ(slice->getHeight(), 8);
            // pixel at (5,5) in original should be at (1,1) in slice
            EXPECT_EQ(slice->getPixel(1, 1), 1);
            EXPECT_EQ(slice->getPixel(0, 0), 0);
        }
    }
}

// Test: combine with OR operation (combOp=1)
TEST_F(JBIG2BitmapTest_1821, CombineOR_1821) {
    JBIG2Bitmap bitmap1(0, 16, 16);
    JBIG2Bitmap bitmap2(1, 16, 16);
    if (bitmap1.isOk() && bitmap2.isOk()) {
        bitmap1.clearToZero();
        bitmap2.clearToZero();
        bitmap2.setPixel(3, 3);
        bitmap1.combine(bitmap2, 0, 0, 1); // OR
        EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
        EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
    }
}

// Test: combine with AND operation (combOp=2)
TEST_F(JBIG2BitmapTest_1821, CombineAND_1821) {
    JBIG2Bitmap bitmap1(0, 16, 16);
    JBIG2Bitmap bitmap2(1, 16, 16);
    if (bitmap1.isOk() && bitmap2.isOk()) {
        bitmap1.clearToOne();
        bitmap2.clearToZero();
        bitmap2.setPixel(3, 3);
        bitmap1.combine(bitmap2, 0, 0, 2); // AND
        EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
        EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
    }
}

// Test: getType returns appropriate segment type
TEST_F(JBIG2BitmapTest_1821, GetType_1821) {
    JBIG2Bitmap bitmap(0, 10, 10);
    // Just verify we can call getType without crashing
    auto type = bitmap.getType();
    (void)type; // suppress unused warning
    SUCCEED();
}

// Test: Large bitmap dimensions
TEST_F(JBIG2BitmapTest_1821, LargeBitmap_1821) {
    JBIG2Bitmap bitmap(0, 1000, 1000);
    if (bitmap.isOk()) {
        EXPECT_EQ(bitmap.getWidth(), 1000);
        EXPECT_EQ(bitmap.getHeight(), 1000);
        EXPECT_EQ(bitmap.getDataSize(), bitmap.getHeight() * bitmap.getLineSize());
    }
}

// Test: Pixel boundary - first and last pixel
TEST_F(JBIG2BitmapTest_1821, PixelBoundaryFirstAndLast_1821) {
    JBIG2Bitmap bitmap(0, 100, 100);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.setPixel(0, 0);
        bitmap.setPixel(99, 99);
        EXPECT_EQ(bitmap.getPixel(0, 0), 1);
        EXPECT_EQ(bitmap.getPixel(99, 99), 1);
        EXPECT_EQ(bitmap.getPixel(1, 0), 0);
        EXPECT_EQ(bitmap.getPixel(98, 99), 0);
    }
}

// Test: nextPixel via JBIG2BitmapPtr
TEST_F(JBIG2BitmapTest_1821, NextPixelIteration_1821) {
    JBIG2Bitmap bitmap(0, 8, 1);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        bitmap.setPixel(0, 0);
        bitmap.setPixel(3, 0);
        bitmap.setPixel(7, 0);

        JBIG2BitmapPtr ptr;
        bitmap.getPixelPtr(0, 0, &ptr);

        int pixel0 = bitmap.nextPixel(&ptr);
        EXPECT_EQ(pixel0, 1); // pixel at x=0

        int pixel1 = bitmap.nextPixel(&ptr);
        EXPECT_EQ(pixel1, 0); // pixel at x=1

        int pixel2 = bitmap.nextPixel(&ptr);
        EXPECT_EQ(pixel2, 0); // pixel at x=2

        int pixel3 = bitmap.nextPixel(&ptr);
        EXPECT_EQ(pixel3, 1); // pixel at x=3
    }
}

// Test: Huffman defines
TEST_F(JBIG2BitmapTest_1821, HuffmanDefinesValues_1821) {
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeU);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdU);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffU);
}

// Test: Combine with offset
TEST_F(JBIG2BitmapTest_1821, CombineWithOffset_1821) {
    JBIG2Bitmap bitmap1(0, 32, 32);
    JBIG2Bitmap bitmap2(1, 8, 8);
    if (bitmap1.isOk() && bitmap2.isOk()) {
        bitmap1.clearToZero();
        bitmap2.clearToZero();
        bitmap2.setPixel(0, 0);
        bitmap1.combine(bitmap2, 10, 10, 1); // OR at offset (10,10)
        EXPECT_EQ(bitmap1.getPixel(10, 10), 1);
        EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
        EXPECT_EQ(bitmap1.getPixel(9, 10), 0);
    }
}

// Test: Width exactly 8 bits
TEST_F(JBIG2BitmapTest_1821, Width8Bits_1821) {
    JBIG2Bitmap bitmap(0, 8, 1);
    if (bitmap.isOk()) {
        bitmap.clearToZero();
        for (int x = 0; x < 8; x++) {
            bitmap.setPixel(x, 0);
        }
        for (int x = 0; x < 8; x++) {
            EXPECT_EQ(bitmap.getPixel(x, 0), 1);
        }
    }
}

// Test: isOk for a normal bitmap
TEST_F(JBIG2BitmapTest_1821, IsOkNormalBitmap_1821) {
    JBIG2Bitmap bitmap(0, 100, 100);
    EXPECT_TRUE(bitmap.isOk());
}
