#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "JBIG2Stream.h"



class JBIG2SymbolDictTest_1831 : public ::testing::Test {

protected:

    std::unique_ptr<JBIG2SymbolDict> symbolDict;



    void SetUp() override {

        symbolDict = std::make_unique<JBIG2SymbolDict>(0, 0);

    }

};



TEST_F(JBIG2SymbolDictTest_1831, GetRefinementRegionStats_ReturnsNonNullPointer_1831) {

    EXPECT_NE(symbolDict->getRefinementRegionStats(), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1831, SetAndGetGenericRegionStats_CorrectlySetsAndReturns_1831) {

    auto stats = std::make_unique<JArithmeticDecoderStats>();

    symbolDict->setGenericRegionStats(std::move(stats));

    EXPECT_NE(symbolDict->getGenericRegionStats(), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1831, SetAndGetRefinementRegionStats_CorrectlySetsAndReturns_1831) {

    auto stats = std::make_unique<JArithmeticDecoderStats>();

    symbolDict->setRefinementRegionStats(std::move(stats));

    EXPECT_NE(symbolDict->getRefinementRegionStats(), nullptr);

}



TEST_F(JBIG2SymbolDictTest_1831, IsOk_ReturnsTrueByDefault_1831) {

    EXPECT_TRUE(symbolDict->isOk());

}
