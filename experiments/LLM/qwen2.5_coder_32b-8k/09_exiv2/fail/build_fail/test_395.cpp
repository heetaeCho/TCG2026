#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryArrayTest_395 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or states here

        arrayCfg = ArrayCfg{};

        arrayDef = ArrayDef{};

        tba = new TiffBinaryArray(0x123, IfdId::ExifIFD, arrayCfg, &arrayDef, 1);

    }



    void TearDown() override {

        // Clean up any resources here

        delete tba;

    }



    ArrayCfg arrayCfg;

    ArrayDef arrayDef;

    TiffBinaryArray* tba;

};



TEST_F(TiffBinaryArrayTest_395, DoSize_EmptyElements_395) {

    EXPECT_EQ(tba->doSize(), 0);

}



TEST_F(TiffBinaryArrayTest_395, DoSize_OneElement_395) {

    arrayCfg.hasFillers_ = false;

    tba->addElement(1, arrayDef);

    EXPECT_EQ(tba->doSize(), arrayCfg.tagStep());

}



TEST_F(TiffBinaryArrayTest_395, DoSize_MultipleElements_395) {

    arrayCfg.hasFillers_ = false;

    tba->addElement(1, arrayDef);

    tba->addElement(2, arrayDef);

    EXPECT_EQ(tba->doSize(), 2 * arrayCfg.tagStep());

}



TEST_F(TiffBinaryArrayTest_395, DoSize_FillersEnabled_395) {

    arrayCfg.hasFillers_ = true;

    arrayDef.size = [](uint16_t tag, IfdId group) { return 10; };

    tba->addElement(2, arrayDef);

    EXPECT_EQ(tba->doSize(), std::max<size_t>(2 * arrayCfg.tagStep(), 10));

}



TEST_F(TiffBinaryArrayTest_395, DoSize_ConfigNotSet_395) {

    tba->arrayCfg_ = nullptr;

    EXPECT_EQ(tba->doSize(), TiffEntryBase::doSize());

}



TEST_F(TiffBinaryArrayTest_395, DoSize_DecodedFalse_395) {

    tba->decoded_ = false;

    EXPECT_EQ(tba->doSize(), TiffEntryBase::doSize());

}
