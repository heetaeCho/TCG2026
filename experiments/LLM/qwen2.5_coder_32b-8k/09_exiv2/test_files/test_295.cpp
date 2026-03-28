#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffBinaryElementTest : public ::testing::Test {

protected:

    TiffBinaryElement element;

};



TEST_F(TiffBinaryElementTest_295, DoClone_ReturnsNewInstance_295) {

    TiffBinaryElement* clonedElement = element.doClone();

    EXPECT_NE(&element, clonedElement);

    delete clonedElement;

}



TEST_F(TiffBinaryElementTest_295, SetAndGetElDef_CorrectlySetsAndGets_295) {

    ArrayDef def = {10, ttUnsignedByte, 5};

    element.setElDef(def);

    EXPECT_EQ(element.elDef(), &def);

}



TEST_F(TiffBinaryElementTest_295, SetAndGetElByteOrder_CorrectlySetsAndGets_295) {

    ByteOrder byteOrder = littleEndian;

    element.setElByteOrder(byteOrder);

    EXPECT_EQ(element.elByteOrder(), byteOrder);

}
