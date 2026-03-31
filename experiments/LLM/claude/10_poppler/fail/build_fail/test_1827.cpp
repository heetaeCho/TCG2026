#include <gtest/gtest.h>
#include <memory>

// Include necessary poppler headers
#include "JBIG2Stream.h"
#include "Object.h"
#include "Stream.h"

// Since JBIG2SymbolDict and related classes are defined in JBIG2Stream.cc (not a header),
// we need to include the .cc file to access the internal classes for testing.
// This is a common pattern for testing internal/translation-unit-local classes.
#include "JBIG2Stream.cc"

class JBIG2SymbolDictTest_1827 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly constructed JBIG2SymbolDict reports isOk
TEST_F(JBIG2SymbolDictTest_1827, ConstructorCreatesOkDict_1827) {
    JBIG2SymbolDict dict(0, 5);
    EXPECT_TRUE(dict.isOk());
}

// Test getSize returns the size passed to constructor
TEST_F(JBIG2SymbolDictTest_1827, GetSizeReturnsConstructorSize_1827) {
    JBIG2SymbolDict dict(0, 10);
    EXPECT_EQ(dict.getSize(), 10u);
}

// Test getSize with zero size
TEST_F(JBIG2SymbolDictTest_1827, GetSizeZero_1827) {
    JBIG2SymbolDict dict(0, 0);
    EXPECT_EQ(dict.getSize(), 0u);
}

// Test getType returns the correct segment type for symbol dict
TEST_F(JBIG2SymbolDictTest_1827, GetTypeReturnsSymbolDict_1827) {
    JBIG2SymbolDict dict(1, 5);
    EXPECT_EQ(dict.getType(), jbig2SegSymbolDict);
}

// Test setBitmap and getBitmap round-trip
TEST_F(JBIG2SymbolDictTest_1827, SetAndGetBitmap_1827) {
    JBIG2SymbolDict dict(0, 3);
    auto bitmap = std::make_unique<JBIG2Bitmap>(0, 10, 10);
    JBIG2Bitmap *rawPtr = bitmap.get();
    dict.setBitmap(0, std::move(bitmap));
    EXPECT_EQ(dict.getBitmap(0), rawPtr);
}

// Test getBitmap returns nullptr for unset index
TEST_F(JBIG2SymbolDictTest_1827, GetBitmapUnsetReturnsNull_1827) {
    JBIG2SymbolDict dict(0, 3);
    EXPECT_EQ(dict.getBitmap(0), nullptr);
}

// Test setting bitmap at different indices
TEST_F(JBIG2SymbolDictTest_1827, SetBitmapAtMultipleIndices_1827) {
    JBIG2SymbolDict dict(0, 3);
    auto bmp0 = std::make_unique<JBIG2Bitmap>(0, 5, 5);
    auto bmp2 = std::make_unique<JBIG2Bitmap>(0, 8, 8);
    JBIG2Bitmap *raw0 = bmp0.get();
    JBIG2Bitmap *raw2 = bmp2.get();
    dict.setBitmap(0, std::move(bmp0));
    dict.setBitmap(2, std::move(bmp2));
    EXPECT_EQ(dict.getBitmap(0), raw0);
    EXPECT_EQ(dict.getBitmap(1), nullptr);
    EXPECT_EQ(dict.getBitmap(2), raw2);
}

// Test generic region stats initially null
TEST_F(JBIG2SymbolDictTest_1827, GenericRegionStatsInitiallyNull_1827) {
    JBIG2SymbolDict dict(0, 1);
    EXPECT_EQ(dict.getGenericRegionStats(), nullptr);
}

// Test refinement region stats initially null
TEST_F(JBIG2SymbolDictTest_1827, RefinementRegionStatsInitiallyNull_1827) {
    JBIG2SymbolDict dict(0, 1);
    EXPECT_EQ(dict.getRefinementRegionStats(), nullptr);
}

// Test setGenericRegionStats and getGenericRegionStats
TEST_F(JBIG2SymbolDictTest_1827, SetAndGetGenericRegionStats_1827) {
    JBIG2SymbolDict dict(0, 1);
    auto stats = std::make_unique<JArithmeticDecoderStats>(2);
    JArithmeticDecoderStats *rawStats = stats.get();
    dict.setGenericRegionStats(std::move(stats));
    EXPECT_EQ(dict.getGenericRegionStats(), rawStats);
}

// Test setRefinementRegionStats and getRefinementRegionStats
TEST_F(JBIG2SymbolDictTest_1827, SetAndGetRefinementRegionStats_1827) {
    JBIG2SymbolDict dict(0, 1);
    auto stats = std::make_unique<JArithmeticDecoderStats>(2);
    JArithmeticDecoderStats *rawStats = stats.get();
    dict.setRefinementRegionStats(std::move(stats));
    EXPECT_EQ(dict.getRefinementRegionStats(), rawStats);
}

// Test with large size
TEST_F(JBIG2SymbolDictTest_1827, LargeSize_1827) {
    JBIG2SymbolDict dict(0, 1000);
    EXPECT_EQ(dict.getSize(), 1000u);
    EXPECT_TRUE(dict.isOk());
}

// Test segment number preservation (via base class)
TEST_F(JBIG2SymbolDictTest_1827, SegmentNumberPreserved_1827) {
    JBIG2SymbolDict dict(42, 5);
    EXPECT_EQ(dict.getSegNum(), 42u);
}

// Test that setting both stats types works independently
TEST_F(JBIG2SymbolDictTest_1827, BothStatsTypesIndependent_1827) {
    JBIG2SymbolDict dict(0, 1);
    auto genStats = std::make_unique<JArithmeticDecoderStats>(2);
    auto refStats = std::make_unique<JArithmeticDecoderStats>(3);
    JArithmeticDecoderStats *rawGen = genStats.get();
    JArithmeticDecoderStats *rawRef = refStats.get();
    dict.setGenericRegionStats(std::move(genStats));
    dict.setRefinementRegionStats(std::move(refStats));
    EXPECT_EQ(dict.getGenericRegionStats(), rawGen);
    EXPECT_EQ(dict.getRefinementRegionStats(), rawRef);
    EXPECT_NE(dict.getGenericRegionStats(), dict.getRefinementRegionStats());
}

// Test Huffman defines have correct values
TEST_F(JBIG2SymbolDictTest_1827, HuffmanDefineValues_1827) {
    EXPECT_EQ(jbig2HuffmanOOB, 0xfffffffeu);
    EXPECT_EQ(jbig2HuffmanLOW, 0xfffffffdu);
    EXPECT_EQ(jbig2HuffmanEOT, 0xffffffffu);
}

// Test overwriting a bitmap at the same index
TEST_F(JBIG2SymbolDictTest_1827, OverwriteBitmapAtIndex_1827) {
    JBIG2SymbolDict dict(0, 2);
    auto bmp1 = std::make_unique<JBIG2Bitmap>(0, 5, 5);
    auto bmp2 = std::make_unique<JBIG2Bitmap>(0, 10, 10);
    JBIG2Bitmap *raw2 = bmp2.get();
    dict.setBitmap(0, std::move(bmp1));
    dict.setBitmap(0, std::move(bmp2));
    EXPECT_EQ(dict.getBitmap(0), raw2);
}
