#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class TiffRwStateTest_280 : public ::testing::Test {

protected:

    ByteOrder byteOrder = littleEndian;

    size_t baseOffset = 1024;

    TiffRwState state;



    TiffRwStateTest_280() : state(byteOrder, baseOffset) {}

};



TEST_F(TiffRwStateTest_280, BaseOffset_ReturnsCorrectValue_280) {

    EXPECT_EQ(state.baseOffset(), baseOffset);

}



TEST_F(TiffRwStateTest_280, ByteOrder_ReturnsLittleEndian_280) {

    EXPECT_EQ(state.byteOrder(), littleEndian);

}



TEST_F(TiffRwStateTest_280, BaseOffset_ZeroBoundary_280) {

    TiffRwState zeroBaseOffsetState(byteOrder, 0);

    EXPECT_EQ(zeroBaseOffsetState.baseOffset(), 0);

}



TEST_F(TiffRwStateTest_280, ByteOrder_ReturnsBigEndian_280) {

    ByteOrder bigEndianByteOrder = bigEndian;

    TiffRwState bigEndianState(bigEndianByteOrder, baseOffset);

    EXPECT_EQ(bigEndianState.byteOrder(), bigEndian);

}
