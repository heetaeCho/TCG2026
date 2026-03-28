#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffBinaryElementTest_363 : public ::testing::Test {

protected:

    TiffBinaryElement element;

};



TEST_F(TiffBinaryElementTest_363, DefaultCountIsZero_363) {

    EXPECT_EQ(element.doCount(), 0);

}



TEST_F(TiffBinaryElementTest_363, SetElDefUpdatesCount_363) {

    ArrayDef def = {1, ttUndefined, 5};

    element.setElDef(def);

    EXPECT_EQ(element.doCount(), 5);

}



TEST_F(TiffBinaryElementTest_363, ElDefReturnsCorrectDefinition_363) {

    ArrayDef def = {1, ttUndefined, 5};

    element.setElDef(def);

    const ArrayDef* retrievedDef = element.elDef();

    ASSERT_NE(retrievedDef, nullptr);

    EXPECT_EQ(*retrievedDef, def);

}



TEST_F(TiffBinaryElementTest_363, ElByteOrderInitiallyInvalid_363) {

    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);

}



TEST_F(TiffBinaryElementTest_363, SetElByteOrderUpdatesCorrectly_363) {

    element.setElByteOrder(bigEndian);

    EXPECT_EQ(element.elByteOrder(), bigEndian);



    element.setElByteOrder(littleEndian);

    EXPECT_EQ(element.elByteOrder(), littleEndian);

}
