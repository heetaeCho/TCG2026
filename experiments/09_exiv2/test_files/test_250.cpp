#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryArrayTest : public ::testing::Test {

protected:

    // Initialize objects for testing

    const ArrayCfg arrayCfg = {}; // Assuming ArrayCfg can be default constructed

    const ArrayDef arrayDef = {}; // Assuming ArrayDef can be default constructed

    TiffBinaryArray tba1 = TiffBinaryArray(0x0100, IfdId::EXIFIFD, arrayCfg, &arrayDef, 1);

    TiffBinaryArray tba2 = TiffBinaryArray(0x0100, IfdId::EXIFIFD, nullptr, 0, [](IfdId) { return &arrayCfg; });

};



// Test for normal operation of cfg() function

TEST_F(TiffBinaryArrayTest_250, CfgReturnsPointerToConfig_250) {

    EXPECT_EQ(&arrayCfg, tba1.cfg());

}



// Test boundary condition when ArraySet is nullptr in constructor

TEST_F(TiffBinaryArrayTest_250, CfgReturnsNullptrWhenArraySetIsNull_250) {

    EXPECT_EQ(nullptr, tba2.cfg());

}



// Test for normal operation of def() function

TEST_F(TiffBinaryArrayTest_250, DefReturnsPointerToArrayDef_250) {

    EXPECT_EQ(&arrayDef, tba1.def());

}



// Test boundary condition when ArrayDef is nullptr in constructor

TEST_F(TiffBinaryArrayTest_250, DefReturnsNullptrWhenArrayDefIsNull_250) {

    EXPECT_EQ(nullptr, tba2.def());

}



// Test for normal operation of defSize() function

TEST_F(TiffBinaryArrayTest_250, DefSizeReturnsCorrectValue_250) {

    EXPECT_EQ(1, tba1.defSize());

}



// Test boundary condition when defSize is 0 in constructor

TEST_F(TiffBinaryArrayTest_250, DefSizeReturnsZeroWhenDefSizeIsZero_250) {

    EXPECT_EQ(0, tba2.defSize());

}



// Test for normal operation of decoded() function after setting to true

TEST_F(TiffBinaryArrayTest_250, DecodedReturnsTrueAfterSetDecodedToTrue_250) {

    tba1.setDecoded(true);

    EXPECT_TRUE(tba1.decoded());

}



// Test for normal operation of decoded() function after setting to false

TEST_F(TiffBinaryArrayTest_250, DecodedReturnsFalseAfterSetDecodedToFalse_250) {

    tba1.setDecoded(false);

    EXPECT_FALSE(tba1.decoded());

}
