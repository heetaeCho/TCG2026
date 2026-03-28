#include <gtest/gtest.h>
#include <memory>

// Include necessary headers from the project
#include "JBIG2Stream.h"

class JBIG2SymbolDictTest_1824 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(JBIG2SymbolDictTest_1824, ConstructorWithZeroSize_1824) {
    JBIG2SymbolDict dict(0, 0);
    EXPECT_EQ(dict.getSize(), 0u);
}

TEST_F(JBIG2SymbolDictTest_1824, ConstructorWithNonZeroSize_1824) {
    JBIG2SymbolDict dict(1, 5);
    EXPECT_EQ(dict.getSize(), 5u);
}

TEST_F(JBIG2SymbolDictTest_1824, GetSizeReturnsCorrectValue_1824) {
    JBIG2SymbolDict dict(0, 10);
    EXPECT_EQ(dict.getSize(), 10u);
}

TEST_F(JBIG2SymbolDictTest_1824, GetSizeAfterConstruction_1824) {
    JBIG2SymbolDict dict(42, 3);
    EXPECT_EQ(dict.getSize(), 3u);
}

TEST_F(JBIG2SymbolDictTest_1824, IsOkAfterConstruction_1824) {
    JBIG2SymbolDict dict(0, 5);
    EXPECT_TRUE(dict.isOk());
}

TEST_F(JBIG2SymbolDictTest_1824, IsOkWithZeroSize_1824) {
    JBIG2SymbolDict dict(0, 0);
    EXPECT_TRUE(dict.isOk());
}

TEST_F(JBIG2SymbolDictTest_1824, GetBitmapReturnsNullInitially_1824) {
    JBIG2SymbolDict dict(0, 5);
    // Before setting any bitmap, getBitmap should return nullptr
    JBIG2Bitmap *bmp = dict.getBitmap(0);
    EXPECT_EQ(bmp, nullptr);
}

TEST_F(JBIG2SymbolDictTest_1824, GetBitmapAtVariousIndicesInitiallyNull_1824) {
    JBIG2SymbolDict dict(0, 3);
    for (unsigned int i = 0; i < 3; ++i) {
        EXPECT_EQ(dict.getBitmap(i), nullptr);
    }
}

TEST_F(JBIG2SymbolDictTest_1824, SetAndGetBitmap_1824) {
    JBIG2SymbolDict dict(0, 3);
    auto bitmap = std::make_unique<JBIG2Bitmap>(0, 10, 10);
    JBIG2Bitmap *rawPtr = bitmap.get();
    dict.setBitmap(0, std::move(bitmap));
    EXPECT_EQ(dict.getBitmap(0), rawPtr);
}

TEST_F(JBIG2SymbolDictTest_1824, SetBitmapAtMultipleIndices_1824) {
    JBIG2SymbolDict dict(0, 3);
    auto bmp0 = std::make_unique<JBIG2Bitmap>(0, 5, 5);
    auto bmp1 = std::make_unique<JBIG2Bitmap>(0, 8, 8);
    auto bmp2 = std::make_unique<JBIG2Bitmap>(0, 12, 12);

    JBIG2Bitmap *raw0 = bmp0.get();
    JBIG2Bitmap *raw1 = bmp1.get();
    JBIG2Bitmap *raw2 = bmp2.get();

    dict.setBitmap(0, std::move(bmp0));
    dict.setBitmap(1, std::move(bmp1));
    dict.setBitmap(2, std::move(bmp2));

    EXPECT_EQ(dict.getBitmap(0), raw0);
    EXPECT_EQ(dict.getBitmap(1), raw1);
    EXPECT_EQ(dict.getBitmap(2), raw2);
}

TEST_F(JBIG2SymbolDictTest_1824, GenericRegionStatsInitiallyNull_1824) {
    JBIG2SymbolDict dict(0, 5);
    EXPECT_EQ(dict.getGenericRegionStats(), nullptr);
}

TEST_F(JBIG2SymbolDictTest_1824, RefinementRegionStatsInitiallyNull_1824) {
    JBIG2SymbolDict dict(0, 5);
    EXPECT_EQ(dict.getRefinementRegionStats(), nullptr);
}

TEST_F(JBIG2SymbolDictTest_1824, LargeSizeConstruction_1824) {
    JBIG2SymbolDict dict(0, 1000);
    EXPECT_EQ(dict.getSize(), 1000u);
}

TEST_F(JBIG2SymbolDictTest_1824, SizeRemainsConstantAfterSetBitmap_1824) {
    JBIG2SymbolDict dict(0, 5);
    auto bitmap = std::make_unique<JBIG2Bitmap>(0, 10, 10);
    dict.setBitmap(2, std::move(bitmap));
    EXPECT_EQ(dict.getSize(), 5u);
}

TEST_F(JBIG2SymbolDictTest_1824, OverwriteBitmapAtSameIndex_1824) {
    JBIG2SymbolDict dict(0, 3);
    auto bmp1 = std::make_unique<JBIG2Bitmap>(0, 5, 5);
    auto bmp2 = std::make_unique<JBIG2Bitmap>(0, 8, 8);

    JBIG2Bitmap *raw2 = bmp2.get();

    dict.setBitmap(0, std::move(bmp1));
    dict.setBitmap(0, std::move(bmp2));

    EXPECT_EQ(dict.getBitmap(0), raw2);
    EXPECT_EQ(dict.getSize(), 3u);
}
