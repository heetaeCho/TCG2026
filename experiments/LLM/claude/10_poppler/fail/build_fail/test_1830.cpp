#include <gtest/gtest.h>
#include <memory>

// Include necessary poppler headers
#include "JBIG2Stream.h"
#include "JArithmeticDecoder.h"

class JBIG2SymbolDictTest_1830 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(JBIG2SymbolDictTest_1830, ConstructorCreatesValidObject_1830) {
    JBIG2SymbolDict dict(0, 10);
    EXPECT_TRUE(dict.isOk());
}

TEST_F(JBIG2SymbolDictTest_1830, GetSizeReturnsCorrectValue_1830) {
    JBIG2SymbolDict dict(1, 5);
    EXPECT_EQ(dict.getSize(), 5u);
}

TEST_F(JBIG2SymbolDictTest_1830, GetSizeZero_1830) {
    JBIG2SymbolDict dict(0, 0);
    EXPECT_EQ(dict.getSize(), 0u);
}

TEST_F(JBIG2SymbolDictTest_1830, GetSizeLargeValue_1830) {
    JBIG2SymbolDict dict(0, 1000);
    EXPECT_EQ(dict.getSize(), 1000u);
}

TEST_F(JBIG2SymbolDictTest_1830, GetTypeReturnsSymbolDict_1830) {
    JBIG2SymbolDict dict(0, 5);
    // JBIG2 symbol dict segment type
    EXPECT_EQ(dict.getType(), jbig2SegSymbolDict);
}

TEST_F(JBIG2SymbolDictTest_1830, GenericRegionStatsInitiallyNull_1830) {
    JBIG2SymbolDict dict(0, 5);
    EXPECT_EQ(dict.getGenericRegionStats(), nullptr);
}

TEST_F(JBIG2SymbolDictTest_1830, RefinementRegionStatsInitiallyNull_1830) {
    JBIG2SymbolDict dict(0, 5);
    EXPECT_EQ(dict.getRefinementRegionStats(), nullptr);
}

TEST_F(JBIG2SymbolDictTest_1830, SetAndGetGenericRegionStats_1830) {
    JBIG2SymbolDict dict(0, 5);
    auto stats = std::make_unique<JArithmeticDecoderStats>(10);
    JArithmeticDecoderStats *rawPtr = stats.get();
    dict.setGenericRegionStats(std::move(stats));
    EXPECT_EQ(dict.getGenericRegionStats(), rawPtr);
}

TEST_F(JBIG2SymbolDictTest_1830, SetAndGetRefinementRegionStats_1830) {
    JBIG2SymbolDict dict(0, 5);
    auto stats = std::make_unique<JArithmeticDecoderStats>(10);
    JArithmeticDecoderStats *rawPtr = stats.get();
    dict.setRefinementRegionStats(std::move(stats));
    EXPECT_EQ(dict.getRefinementRegionStats(), rawPtr);
}

TEST_F(JBIG2SymbolDictTest_1830, GetBitmapReturnsNullBeforeSet_1830) {
    JBIG2SymbolDict dict(0, 5);
    EXPECT_EQ(dict.getBitmap(0), nullptr);
}

TEST_F(JBIG2SymbolDictTest_1830, SetAndGetBitmap_1830) {
    JBIG2SymbolDict dict(0, 5);
    auto bitmap = std::make_unique<JBIG2Bitmap>(0, 10, 10);
    JBIG2Bitmap *rawPtr = bitmap.get();
    dict.setBitmap(0, std::move(bitmap));
    EXPECT_EQ(dict.getBitmap(0), rawPtr);
}

TEST_F(JBIG2SymbolDictTest_1830, SetMultipleBitmaps_1830) {
    JBIG2SymbolDict dict(0, 3);
    auto bmp0 = std::make_unique<JBIG2Bitmap>(0, 5, 5);
    auto bmp1 = std::make_unique<JBIG2Bitmap>(0, 10, 10);
    auto bmp2 = std::make_unique<JBIG2Bitmap>(0, 15, 15);
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

TEST_F(JBIG2SymbolDictTest_1830, IsOkAfterConstruction_1830) {
    JBIG2SymbolDict dict(42, 10);
    EXPECT_TRUE(dict.isOk());
}

TEST_F(JBIG2SymbolDictTest_1830, OverwriteGenericRegionStats_1830) {
    JBIG2SymbolDict dict(0, 5);
    auto stats1 = std::make_unique<JArithmeticDecoderStats>(10);
    dict.setGenericRegionStats(std::move(stats1));

    auto stats2 = std::make_unique<JArithmeticDecoderStats>(20);
    JArithmeticDecoderStats *rawPtr2 = stats2.get();
    dict.setGenericRegionStats(std::move(stats2));
    EXPECT_EQ(dict.getGenericRegionStats(), rawPtr2);
}

TEST_F(JBIG2SymbolDictTest_1830, OverwriteRefinementRegionStats_1830) {
    JBIG2SymbolDict dict(0, 5);
    auto stats1 = std::make_unique<JArithmeticDecoderStats>(10);
    dict.setRefinementRegionStats(std::move(stats1));

    auto stats2 = std::make_unique<JArithmeticDecoderStats>(20);
    JArithmeticDecoderStats *rawPtr2 = stats2.get();
    dict.setRefinementRegionStats(std::move(stats2));
    EXPECT_EQ(dict.getRefinementRegionStats(), rawPtr2);
}

TEST_F(JBIG2SymbolDictTest_1830, HuffmanDefinesCorrectValues_1830) {
    // Verify the #define constants are accessible and have expected values
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeu);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdu);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffu);
}

TEST_F(JBIG2SymbolDictTest_1830, DifferentSegNumbers_1830) {
    JBIG2SymbolDict dict1(0, 5);
    JBIG2SymbolDict dict2(100, 5);
    // Both should be valid regardless of segment number
    EXPECT_TRUE(dict1.isOk());
    EXPECT_TRUE(dict2.isOk());
    EXPECT_EQ(dict1.getSize(), dict2.getSize());
}
