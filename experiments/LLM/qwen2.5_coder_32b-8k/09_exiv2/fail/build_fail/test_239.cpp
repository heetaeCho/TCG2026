#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffEntryBaseTest_239 : public ::testing::Test {

protected:

    TiffEntryBase* tiffEntry;



    void SetUp() override {

        tiffEntry = new TiffEntryBase(1, ifdExif, ttShort);

    }



    void TearDown() override {

        delete tiffEntry;

    }

};



TEST_F(TiffEntryBaseTest_239, SetIdxAndGetIdx_NormalOperation_239) {

    tiffEntry->setIdx(5);

    EXPECT_EQ(tiffEntry->idx(), 5);

}



TEST_F(TiffEntryBaseTest_239, SetIdxBoundaryCondition_Zero_239) {

    tiffEntry->setIdx(0);

    EXPECT_EQ(tiffEntry->idx(), 0);

}



TEST_F(TiffEntryBaseTest_239, SetIdxBoundaryCondition_Negative_239) {

    tiffEntry->setIdx(-1);

    EXPECT_EQ(tiffEntry->idx(), -1);

}



// Assuming TiffType is an enum and ttShort is a valid value

TEST_F(TiffEntryBaseTest_239, TiffType_ReturnsCorrectValue_239) {

    EXPECT_EQ(tiffEntry->tiffType(), ttShort);

}
