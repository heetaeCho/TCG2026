#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.h"



using namespace testing;



class JBIG2SymbolDictTest_1830 : public ::testing::Test {

protected:

    std::unique_ptr<JBIG2SymbolDict> symbol_dict;



    void SetUp() override {

        symbol_dict = std::make_unique<JBIG2SymbolDict>(42, 10);

    }

};



TEST_F(JBIG2SymbolDictTest_1830, GetGenericRegionStats_ReturnsNonNullPointer_1830) {

    EXPECT_NE(symbol_dict->getGenericRegionStats(), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1830, SetAndGetGenericRegionStats_CorrectlySetsAndReturns_1830) {

    auto stats = std::make_unique<JArithmeticDecoderStats>();

    JArithmeticDecoderStats* raw_stats_ptr = stats.get();

    symbol_dict->setGenericRegionStats(std::move(stats));

    EXPECT_EQ(symbol_dict->getGenericRegionStats(), raw_stats_ptr);

}



TEST_F(JBIG2SymbolDictTest_1830, SetAndGetRefinementRegionStats_CorrectlySetsAndReturns_1830) {

    auto stats = std::make_unique<JArithmeticDecoderStats>();

    JArithmeticDecoderStats* raw_stats_ptr = stats.get();

    symbol_dict->setRefinementRegionStats(std::move(stats));

    EXPECT_EQ(symbol_dict->getRefinementRegionStats(), raw_stats_ptr);

}



TEST_F(JBIG2SymbolDictTest_1830, GetBitmap_OutOfBounds_ReturnsNullPointer_1830) {

    EXPECT_EQ(symbol_dict->getBitmap(15), nullptr); // Assuming size is 10, index 15 is out of bounds

}



TEST_F(JBIG2SymbolDictTest_1830, SetAndGetBitmap_CorrectlySetsAndReturns_1830) {

    auto bitmap = std::make_unique<JBIG2Bitmap>();

    JBIG2Bitmap* raw_bitmap_ptr = bitmap.get();

    symbol_dict->setBitmap(5, std::move(bitmap));

    EXPECT_EQ(symbol_dict->getBitmap(5), raw_bitmap_ptr);

}



TEST_F(JBIG2SymbolDictTest_1830, IsOk_DefaultState_ReturnsTrue_1830) {

    EXPECT_TRUE(symbol_dict->isOk());

}
