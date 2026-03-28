#include <gtest/gtest.h>
#include <memory>

// We need to include the necessary headers. Since JBIG2Stream.cc contains
// the implementation, we need to include the relevant header.
// Based on the project structure, we include the header that declares these types.

// Forward declarations and minimal definitions needed for compilation
// Since the actual implementation is in JBIG2Stream.cc, we need to work with
// whatever headers are available.

#include "JBIG2Stream.h"

// If JBIG2Stream.h doesn't exist as a separate header, the classes might be
// declared within the .cc file. In that case, we may need alternative includes.
// The test assumes proper header availability.

class JBIG2BitmapTest_1813 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and type
TEST_F(JBIG2BitmapTest_1813, GetTypeReturnsBitmap_1813) {
    JBIG2Bitmap bitmap(0, 10, 10);
    EXPECT_EQ(bitmap.getType(), jbig2SegBitmap);
}

// Test construction with various dimensions
TEST_F(JBIG2BitmapTest_1813, ConstructWithValidDimensions_1813) {
    JBIG2Bitmap bitmap(1, 100, 200);
    EXPECT_EQ(bitmap.getWidth(), 100);
    EXPECT_EQ(bitmap.getHeight(), 200);
    EXPECT_TRUE(bitmap.isOk());
}

// Test construction with zero dimensions
TEST_F(JBIG2BitmapTest_1813, ConstructWithZeroDimensions_1813) {
    JBIG2Bitmap bitmap(0, 0, 0);
    EXPECT_EQ(bitmap.getWidth(), 0);
    EXPECT_EQ(bitmap.getHeight(), 0);
}

// Test construction with width=1, height=1
TEST_F(JBIG2BitmapTest_1813, ConstructWithMinimalDimensions_1813) {
    JBIG2Bitmap bitmap(0, 1, 1);
    EXPECT_EQ(bitmap.getWidth(), 1);
    EXPECT_EQ(bitmap.getHeight(), 1);
    EXPECT_TRUE(bitmap.isOk());
}

// Test copy constructor
TEST_F(JBIG2BitmapTest_1813, CopyConstruction_1813) {
    JBIG2Bitmap original(0, 50, 60);
    JBIG2Bitmap copy(&original);
    EXPECT_EQ(copy.getWidth(), 50);
    EXPECT_EQ(copy.getHeight(), 60);
    EXPECT_EQ(copy.getType(), jbig2SegBitmap);
}

// Test clearToZero sets all pixels to 0
TEST_F(JBIG2BitmapTest_1813, ClearToZeroSetsAllPixelsZero_1813) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.setPixel(0, 0);
    bitmap.setPixel(3, 3);
    bitmap.setPixel(7, 7);
    bitmap.clearToZero();
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(3, 3), 0);
    EXPECT_EQ(bitmap.getPixel(7, 7), 0);
}

// Test clearToOne sets all pixels to 1
TEST_F(JBIG2BitmapTest_1813, ClearToOneSetsAllPixelsOne_1813) {
    JBIG2Bitmap bitmap(0, 8, 8);
    bitmap.clearToOne();
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(3, 3), 1);
    EXPECT_EQ(bitmap.getPixel(7, 7), 1);
}

// Test setPixel and getPixel
TEST_F(JBIG2BitmapTest_1813, SetPixelAndGetPixel_1813) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 1);
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(4, 5), 0);
    EXPECT_EQ(bitmap.getPixel(6, 5), 0);
}

// Test clearPixel
TEST_F(JBIG2BitmapTest_1813, ClearPixel_1813) {
    JBIG2Bitmap bitmap(0, 16, 16);
    bitmap.clearToOne();
    bitmap.clearPixel(5, 5);
    EXPECT_EQ(bitmap.getPixel(5, 5), 0);
    EXPECT_EQ(bitmap.getPixel(4, 5), 1);
}

// Test getPixel out of bounds returns 0
TEST_F(JBIG2BitmapTest_1813, GetPixelOutOfBoundsReturnsZero_1813) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToOne();
    EXPECT_EQ(bitmap.getPixel(-1, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, -1), 0);
    EXPECT_EQ(bitmap.getPixel(10, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, 10), 0);
}

// Test getLineSize
TEST_F(JBIG2BitmapTest_1813, GetLineSizeConsistentWithWidth_1813) {
    JBIG2Bitmap bitmap(0, 8, 1);
    int lineSize = bitmap.getLineSize();
    EXPECT_GE(lineSize, 1);  // At least 1 byte for 8 pixels

    JBIG2Bitmap bitmap2(0, 9, 1);
    int lineSize2 = bitmap2.getLineSize();
    EXPECT_GE(lineSize2, 2);  // At least 2 bytes for 9 pixels
}

// Test getDataPtr is not null for valid bitmap
TEST_F(JBIG2BitmapTest_1813, GetDataPtrNotNull_1813) {
    JBIG2Bitmap bitmap(0, 10, 10);
    if (bitmap.isOk()) {
        EXPECT_NE(bitmap.getDataPtr(), nullptr);
    }
}

// Test getDataSize is consistent
TEST_F(JBIG2BitmapTest_1813, GetDataSizeConsistentWithDimensions_1813) {
    JBIG2Bitmap bitmap(0, 16, 16);
    if (bitmap.isOk()) {
        int dataSize = bitmap.getDataSize();
        EXPECT_GE(dataSize, bitmap.getLineSize() * bitmap.getHeight());
    }
}

// Test expand increases height
TEST_F(JBIG2BitmapTest_1813, ExpandIncreasesHeight_1813) {
    JBIG2Bitmap bitmap(0, 10, 5);
    EXPECT_EQ(bitmap.getHeight(), 5);
    bitmap.expand(10, 0);
    EXPECT_EQ(bitmap.getHeight(), 10);
}

// Test expand with pixel value 0
TEST_F(JBIG2BitmapTest_1813, ExpandWithZeroPixel_1813) {
    JBIG2Bitmap bitmap(0, 8, 2);
    bitmap.clearToOne();
    bitmap.expand(4, 0);
    EXPECT_EQ(bitmap.getHeight(), 4);
    // New rows should be filled with 0
    EXPECT_EQ(bitmap.getPixel(0, 2), 0);
    EXPECT_EQ(bitmap.getPixel(0, 3), 0);
    // Original rows should still be 1
    EXPECT_EQ(bitmap.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap.getPixel(0, 1), 1);
}

// Test expand with pixel value 1
TEST_F(JBIG2BitmapTest_1813, ExpandWithOnePixel_1813) {
    JBIG2Bitmap bitmap(0, 8, 2);
    bitmap.clearToZero();
    bitmap.expand(4, 1);
    EXPECT_EQ(bitmap.getHeight(), 4);
    // New rows should be filled with 1
    EXPECT_EQ(bitmap.getPixel(0, 2), 1);
    EXPECT_EQ(bitmap.getPixel(0, 3), 1);
    // Original rows should still be 0
    EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap.getPixel(0, 1), 0);
}

// Test getSlice returns valid sub-bitmap
TEST_F(JBIG2BitmapTest_1813, GetSliceReturnsValidSubBitmap_1813) {
    JBIG2Bitmap bitmap(0, 20, 20);
    bitmap.clearToZero();
    bitmap.setPixel(5, 5);
    bitmap.setPixel(6, 6);

    auto slice = bitmap.getSlice(4, 4, 8, 8);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 8);
        EXPECT_EQ(slice->getHeight(), 8);
        // Pixel at (5,5) in original maps to (1,1) in slice
        EXPECT_EQ(slice->getPixel(1, 1), 1);
        // Pixel at (6,6) in original maps to (2,2) in slice
        EXPECT_EQ(slice->getPixel(2, 2), 1);
        // Other pixels should be 0
        EXPECT_EQ(slice->getPixel(0, 0), 0);
    }
}

// Test duplicateRow copies row content
TEST_F(JBIG2BitmapTest_1813, DuplicateRowCopiesContent_1813) {
    JBIG2Bitmap bitmap(0, 16, 4);
    bitmap.clearToZero();
    bitmap.setPixel(3, 0);
    bitmap.setPixel(7, 0);

    bitmap.duplicateRow(2, 0);

    EXPECT_EQ(bitmap.getPixel(3, 2), 1);
    EXPECT_EQ(bitmap.getPixel(7, 2), 1);
    EXPECT_EQ(bitmap.getPixel(0, 2), 0);
}

// Test combine with OR operation (combOp = 0 typically means OR)
TEST_F(JBIG2BitmapTest_1813, CombineBitmaps_1813) {
    JBIG2Bitmap bitmap1(0, 8, 8);
    bitmap1.clearToZero();

    JBIG2Bitmap bitmap2(1, 4, 4);
    bitmap2.clearToOne();

    bitmap1.combine(bitmap2, 0, 0, 0);  // OR combine at (0,0)

    // Pixels in the combined region should be 1
    EXPECT_EQ(bitmap1.getPixel(0, 0), 1);
    EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
    // Pixels outside the combined region should remain 0
    EXPECT_EQ(bitmap1.getPixel(4, 4), 0);
    EXPECT_EQ(bitmap1.getPixel(7, 7), 0);
}

// Test combine at offset position
TEST_F(JBIG2BitmapTest_1813, CombineAtOffset_1813) {
    JBIG2Bitmap bitmap1(0, 16, 16);
    bitmap1.clearToZero();

    JBIG2Bitmap bitmap2(1, 4, 4);
    bitmap2.clearToOne();

    bitmap1.combine(bitmap2, 5, 5, 0);

    EXPECT_EQ(bitmap1.getPixel(5, 5), 1);
    EXPECT_EQ(bitmap1.getPixel(8, 8), 1);
    EXPECT_EQ(bitmap1.getPixel(4, 4), 0);
    EXPECT_EQ(bitmap1.getPixel(9, 9), 0);
}

// Test setPixel at boundary positions
TEST_F(JBIG2BitmapTest_1813, SetPixelAtBoundaries_1813) {
    JBIG2Bitmap bitmap(0, 32, 32);
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

// Test large bitmap
TEST_F(JBIG2BitmapTest_1813, LargeBitmap_1813) {
    JBIG2Bitmap bitmap(0, 1000, 1000);
    if (bitmap.isOk()) {
        EXPECT_EQ(bitmap.getWidth(), 1000);
        EXPECT_EQ(bitmap.getHeight(), 1000);
        bitmap.clearToZero();
        bitmap.setPixel(999, 999);
        EXPECT_EQ(bitmap.getPixel(999, 999), 1);
        EXPECT_EQ(bitmap.getPixel(0, 0), 0);
    }
}

// Test pixel pointer iteration
TEST_F(JBIG2BitmapTest_1813, PixelPtrIteration_1813) {
    JBIG2Bitmap bitmap(0, 8, 1);
    bitmap.clearToZero();
    bitmap.setPixel(0, 0);
    bitmap.setPixel(3, 0);
    bitmap.setPixel(7, 0);

    JBIG2BitmapPtr ptr;
    bitmap.getPixelPtr(0, 0, &ptr);

    int pixel0 = bitmap.nextPixel(&ptr);
    EXPECT_EQ(pixel0, 1);  // pixel at x=0

    int pixel1 = bitmap.nextPixel(&ptr);
    EXPECT_EQ(pixel1, 0);  // pixel at x=1

    int pixel2 = bitmap.nextPixel(&ptr);
    EXPECT_EQ(pixel2, 0);  // pixel at x=2

    int pixel3 = bitmap.nextPixel(&ptr);
    EXPECT_EQ(pixel3, 1);  // pixel at x=3
}

// Test Huffman constants are defined correctly
TEST_F(JBIG2BitmapTest_1813, HuffmanConstantsAreDefined_1813) {
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeU);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdU);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffU);
}

// Test segment type enum values
TEST_F(JBIG2BitmapTest_1813, SegmentTypeEnumValues_1813) {
    EXPECT_EQ(jbig2SegBitmap, 0);
    EXPECT_EQ(jbig2SegSymbolDict, 1);
    EXPECT_EQ(jbig2SegPatternDict, 2);
    EXPECT_EQ(jbig2SegCodeTable, 3);
}

// Test bitmap with width not multiple of 8
TEST_F(JBIG2BitmapTest_1813, NonByteAlignedWidth_1813) {
    JBIG2Bitmap bitmap(0, 13, 5);
    if (bitmap.isOk()) {
        EXPECT_EQ(bitmap.getWidth(), 13);
        EXPECT_EQ(bitmap.getHeight(), 5);
        bitmap.clearToZero();
        bitmap.setPixel(12, 4);
        EXPECT_EQ(bitmap.getPixel(12, 4), 1);
        EXPECT_EQ(bitmap.getPixel(11, 4), 0);
    }
}

// Test getSlice with full bitmap extent
TEST_F(JBIG2BitmapTest_1813, GetSliceFullExtent_1813) {
    JBIG2Bitmap bitmap(0, 10, 10);
    bitmap.clearToOne();

    auto slice = bitmap.getSlice(0, 0, 10, 10);
    if (slice) {
        EXPECT_EQ(slice->getWidth(), 10);
        EXPECT_EQ(slice->getHeight(), 10);
        EXPECT_EQ(slice->getPixel(0, 0), 1);
        EXPECT_EQ(slice->getPixel(9, 9), 1);
    }
}

// Test combine with AND operation (combOp = 1)
TEST_F(JBIG2BitmapTest_1813, CombineAndOperation_1813) {
    JBIG2Bitmap bitmap1(0, 8, 8);
    bitmap1.clearToOne();

    JBIG2Bitmap bitmap2(1, 8, 8);
    bitmap2.clearToZero();
    bitmap2.setPixel(3, 3);

    bitmap1.combine(bitmap2, 0, 0, 1);  // AND combine

    EXPECT_EQ(bitmap1.getPixel(3, 3), 1);
    EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
}

// Test combine with XOR operation (combOp = 2)
TEST_F(JBIG2BitmapTest_1813, CombineXorOperation_1813) {
    JBIG2Bitmap bitmap1(0, 8, 8);
    bitmap1.clearToOne();

    JBIG2Bitmap bitmap2(1, 8, 8);
    bitmap2.clearToOne();

    bitmap1.combine(bitmap2, 0, 0, 2);  // XOR combine

    EXPECT_EQ(bitmap1.getPixel(0, 0), 0);
    EXPECT_EQ(bitmap1.getPixel(7, 7), 0);
}
