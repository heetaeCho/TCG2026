#include <gtest/gtest.h>

#include "JBIG2Stream.cc"



class JBIG2SymbolDictTest_1827 : public ::testing::Test {

protected:

    void SetUp() override {

        symbolDict = std::make_unique<JBIG2SymbolDict>(0, 10);

    }



    std::unique_ptr<JBIG2SymbolDict> symbolDict;

};



TEST_F(JBIG2SymbolDictTest_1827, IsOk_ReturnsTrueByDefault_1827) {

    EXPECT_TRUE(symbolDict->isOk());

}



TEST_F(JBIG2SymbolDictTest_1827, GetSize_ReturnsConstructedSize_1827) {

    EXPECT_EQ(symbolDict->getSize(), 10u);

}



TEST_F(JBIG2SymbolDictTest_1827, SetAndGetBitmap_ValidIndex_1827) {

    auto bitmap = std::make_unique<JBIG2Bitmap>();

    symbolDict->setBitmap(5, std::move(bitmap));

    EXPECT_NE(symbolDict->getBitmap(5), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1827, GetBitmap_OutOfBounds_ReturnsNull_1827) {

    EXPECT_EQ(symbolDict->getBitmap(10), nullptr); // Out of bounds

    EXPECT_EQ(symbolDict->getBitmap(20), nullptr); // Far out of bounds

}



TEST_F(JBIG2SymbolDictTest_1827, SetGenericRegionStats_ValidPointer_1827) {

    auto stats = std::make_unique<JArithmeticDecoderStats>();

    symbolDict->setGenericRegionStats(std::move(stats));

    EXPECT_NE(symbolDict->getGenericRegionStats(), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1827, SetRefinementRegionStats_ValidPointer_1827) {

    auto stats = std::make_unique<JArithmeticDecoderStats>();

    symbolDict->setRefinementRegionStats(std::move(stats));

    EXPECT_NE(symbolDict->getRefinementRegionStats(), nullptr);

}
