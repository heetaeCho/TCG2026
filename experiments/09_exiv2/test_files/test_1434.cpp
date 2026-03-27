#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MnHeaderTest_1434 : public ::testing::Test {

protected:

    MnHeader mnHeader;

};



TEST_F(MnHeaderTest_1434, DefaultByteOrderIsInvalid_1434) {

    EXPECT_EQ(mnHeader.byteOrder(), invalidByteOrder);

}



TEST_F(MnHeaderTest_1434, SetByteOrderToLittleEndian_1434) {

    mnHeader.setByteOrder(littleEndian);

    EXPECT_EQ(mnHeader.byteOrder(), littleEndian);

}



TEST_F(MnHeaderTest_1434, SetByteOrderToBigEndian_1434) {

    mnHeader.setByteOrder(bigEndian);

    EXPECT_EQ(mnHeader.byteOrder(), bigEndian);

}



TEST_F(MnHeaderTest_1434, IfdOffsetReturnsZeroByDefault_1434) {

    EXPECT_EQ(mnHeader.ifdOffset(), 0U);

}



TEST_F(MnHeaderTest_1434, BaseOffsetReturnsInputByDefault_1434) {

    size_t mnOffset = 123;

    EXPECT_EQ(mnHeader.baseOffset(mnOffset), mnOffset);

}
