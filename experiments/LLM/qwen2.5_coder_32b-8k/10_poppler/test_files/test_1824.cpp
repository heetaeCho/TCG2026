#include <gtest/gtest.h>

#include "JBIG2Stream.h"



class JBIG2SymbolDictTest_1824 : public ::testing::Test {

protected:

    std::unique_ptr<JBIG2SymbolDict> symbol_dict;



    void SetUp() override {

        symbol_dict = std::make_unique<JBIG2SymbolDict>(0, 5); // Initialize with a size of 5

    }

};



TEST_F(JBIG2SymbolDictTest_1824, GetSize_ReturnsCorrectInitialSize_1824) {

    EXPECT_EQ(symbol_dict->getSize(), 5);

}



TEST_F(JBIG2SymbolDictTest_1824, SetAndGetBitmap_Successful_1824) {

    auto bitmap = std::make_unique<JBIG2Bitmap>();

    symbol_dict->setBitmap(0, std::move(bitmap));

    EXPECT_NE(symbol_dict->getBitmap(0), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1824, SetBitmap_OutOfBounds_NoCrash_1824) {

    auto bitmap = std::make_unique<JBIG2Bitmap>();

    symbol_dict->setBitmap(10, std::move(bitmap)); // Out of bounds index

    EXPECT_EQ(symbol_dict->getBitmap(10), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1824, GetBitmap_OutOfBounds_ReturnsNullptr_1824) {

    EXPECT_EQ(symbol_dict->getBitmap(10), nullptr); // Out of bounds index

}



TEST_F(JBIG2SymbolDictTest_1824, IsOk_DefaultState_ReturnsTrue_1824) {

    EXPECT_TRUE(symbol_dict->isOk());

}



TEST_F(JBIG2SymbolDictTest_1824, SetAndGetGenericRegionStats_Successful_1824) {

    auto stats = std::make_unique<JArithmeticDecoderStats>();

    symbol_dict->setGenericRegionStats(std::move(stats));

    EXPECT_NE(symbol_dict->getGenericRegionStats(), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1824, SetAndGetRefinementRegionStats_Successful_1824) {

    auto stats = std::make_unique<JArithmeticDecoderStats>();

    symbol_dict->setRefinementRegionStats(std::move(stats));

    EXPECT_NE(symbol_dict->getRefinementRegionStats(), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1824, GetGenericRegionStats_DefaultState_ReturnsNullptr_1824) {

    EXPECT_EQ(symbol_dict->getGenericRegionStats(), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1824, GetRefinementRegionStats_DefaultState_ReturnsNullptr_1824) {

    EXPECT_EQ(symbol_dict->getRefinementRegionStats(), nullptr);

}
