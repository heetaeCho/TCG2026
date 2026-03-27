#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryArrayTest_313 : public ::testing::Test {

protected:

    ArrayCfg mockArrayCfg;

    ArrayDef mockArrayDef;

    ArraySet mockArraySet[2];

    const ArraySet* pMockArraySet = mockArraySet;

    size_t setSize = 2;

    CfgSelFct cfgSelFct;



    void SetUp() override {

        // Initialize mock data

        mockArrayCfg.elTiffType_ = TiffType::tiffByte; // Example type

        mockArrayDef = {}; // Example definition



        // Set up array set with two entries

        mockArraySet[0].cfg_.group_ = IfdId::exifIFD;

        mockArraySet[0].def_ = &mockArrayDef;

        mockArraySet[0].defSize_ = 1;



        mockArraySet[1].cfg_.group_ = IfdId::gpsIFD;

        mockArraySet[1].def_ = &mockArrayDef;

        mockArraySet[1].defSize_ = 1;

    }

};



TEST_F(TiffBinaryArrayTest_313, InitializeWithValidGroup_313) {

    TiffBinaryArray tba(0x0112, IfdId::exifIFD, pMockArraySet, setSize, cfgSelFct);

    EXPECT_TRUE(tba.initialize(IfdId::exifIFD));

}



TEST_F(TiffBinaryArrayTest_313, InitializeWithInvalidGroup_313) {

    TiffBinaryArray tba(0x0112, IfdId::exifIFD, pMockArraySet, setSize, cfgSelFct);

    EXPECT_FALSE(tba.initialize(IfdId::unknown));

}



TEST_F(TiffBinaryArrayTest_313, InitializeAlreadyInitialized_313) {

    TiffBinaryArray tba(0x0112, IfdId::exifIFD, pMockArraySet, setSize, cfgSelFct);

    tba.initialize(IfdId::exifIFD); // First initialization

    EXPECT_TRUE(tba.initialize(IfdId::exifIFD)); // Second call should still return true

}



TEST_F(TiffBinaryArrayTest_313, InitializeBoundaryConditionEmptySet_313) {

    ArraySet emptyArraySet[0];

    TiffBinaryArray tba(0x0112, IfdId::exifIFD, emptyArraySet, 0, cfgSelFct);

    EXPECT_FALSE(tba.initialize(IfdId::exifIFD));

}



TEST_F(TiffBinaryArrayTest_313, InitializeBoundaryConditionSingleEntryMatch_313) {

    ArraySet singleArraySet[1];

    singleArraySet[0].cfg_.group_ = IfdId::exifIFD;

    singleArraySet[0].def_ = &mockArrayDef;

    singleArraySet[0].defSize_ = 1;



    TiffBinaryArray tba(0x0112, IfdId::exifIFD, singleArraySet, 1, cfgSelFct);

    EXPECT_TRUE(tba.initialize(IfdId::exifIFD));

}



TEST_F(TiffBinaryArrayTest_313, InitializeBoundaryConditionSingleEntryNoMatch_313) {

    ArraySet singleArraySet[1];

    singleArraySet[0].cfg_.group_ = IfdId::gpsIFD;

    singleArraySet[0].def_ = &mockArrayDef;

    singleArraySet[0].defSize_ = 1;



    TiffBinaryArray tba(0x0112, IfdId::exifIFD, singleArraySet, 1, cfgSelFct);

    EXPECT_FALSE(tba.initialize(IfdId::exifIFD));

}
