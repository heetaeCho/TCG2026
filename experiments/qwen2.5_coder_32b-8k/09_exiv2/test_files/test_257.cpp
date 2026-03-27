#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryElementTest : public ::testing::Test {

protected:

    TiffBinaryElement element;

};



TEST_F(TiffBinaryElementTest_257, DefaultByteOrder_257) {

    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);

}



TEST_F(TiffBinaryElementTest_257, SetAndGetByteOrder_257) {

    ByteOrder testByteOrder = littleEndian;

    element.setElByteOrder(testByteOrder);

    EXPECT_EQ(element.elByteOrder(), testByteOrder);

}



TEST_F(TiffBinaryElementTest_257, BoundaryConditionInvalidByteOrder_257) {

    ByteOrder invalidBO = static_cast<ByteOrder>(-1); // Assuming -1 is not a valid ByteOrder

    element.setElByteOrder(invalidBO);

    EXPECT_EQ(element.elByteOrder(), invalidBO);

}
