#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class TiffRwStateTest_279 : public ::testing::Test {

protected:

    TiffRwStateTest_279() 

        : littleEndianState(ByteOrder::littleEndian, 0),

          bigEndianState(ByteOrder::bigEndian, 1024) {}



    TiffRwState littleEndianState;

    TiffRwState bigEndianState;

};



TEST_F(TiffRwStateTest_279, ByteOrderReturnsCorrectValueForLittleEndian_279) {

    EXPECT_EQ(littleEndianState.byteOrder(), ByteOrder::littleEndian);

}



TEST_F(TiffRwStateTest_279, ByteOrderReturnsCorrectValueForBigEndian_279) {

    EXPECT_EQ(bigEndianState.byteOrder(), ByteOrder::bigEndian);

}



// Assuming baseOffset() is part of the interface based on known dependencies

TEST_F(TiffRwStateTest_279, BaseOffsetReturnsCorrectInitialValue_279) {

    EXPECT_EQ(littleEndianState.baseOffset(), 0);

}



TEST_F(TiffRwStateTest_279, BaseOffsetReturnsNonZeroValue_279) {

    EXPECT_EQ(bigEndianState.baseOffset(), 1024);

}



// Assuming no exceptional or error cases are observable through the interface
