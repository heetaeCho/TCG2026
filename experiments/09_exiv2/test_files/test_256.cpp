#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryElementTest_256 : public ::testing::Test {

protected:

    TiffBinaryElement element;

};



TEST_F(TiffBinaryElementTest_256, ElDefReturnsValidPointer_256) {

    EXPECT_NE(element.elDef(), nullptr);

}



TEST_F(TiffBinaryElementTest_256, DefaultElByteOrderIsInvalid_256) {

    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);

}



TEST_F(TiffBinaryElementTest_256, SetElDefChangesElDef_256) {

    ArrayDef newDef = {10, ttShort, 4};

    element.setElDef(newDef);

    const ArrayDef* def = element.elDef();

    EXPECT_EQ(def->count, newDef.count);

    EXPECT_EQ(def->type, newDef.type);

    EXPECT_EQ(def->size, newDef.size);

}



TEST_F(TiffBinaryElementTest_256, SetElByteOrderChangesByteOrder_256) {

    ByteOrder newByteOrder = littleEndian;

    element.setElByteOrder(newByteOrder);

    EXPECT_EQ(element.elByteOrder(), newByteOrder);

}
