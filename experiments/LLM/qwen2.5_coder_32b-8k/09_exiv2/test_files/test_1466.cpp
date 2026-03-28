#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class Nikon3MnHeaderTest_1466 : public ::testing::Test {

protected:

    Nikon3MnHeader header;

};



TEST_F(Nikon3MnHeaderTest_1466, SizeReturnsSizeOfSignature_1466) {

    EXPECT_EQ(header.size(), header.sizeOfSignature());

}



TEST_F(Nikon3MnHeaderTest_1466, ReadFunctionCalledProperly_1466) {

    byte data[10];

    ByteOrder order = littleEndian;

    EXPECT_TRUE(header.read(data, sizeof(data), order));

}



TEST_F(Nikon3MnHeaderTest_1466, SetByteOrderSetsCorrectly_1466) {

    ByteOrder newOrder = bigEndian;

    header.setByteOrder(newOrder);

    EXPECT_EQ(header.byteOrder(), newOrder);

}



TEST_F(Nikon3MnHeaderTest_1466, WriteFunctionCalledProperly_1466) {

    IoWrapper ioWrapper;

    ByteOrder order = littleEndian;

    EXPECT_EQ(header.write(ioWrapper, order), 0U); // Assuming write returns size written

}



TEST_F(Nikon3MnHeaderTest_1466, IfdOffsetReturnsExpectedValue_1466) {

    EXPECT_GE(header.ifdOffset(), 0U);

}



TEST_F(Nikon3MnHeaderTest_1466, BaseOffsetCalculatesCorrectly_1466) {

    size_t mnOffset = 10;

    EXPECT_GE(header.baseOffset(mnOffset), 0U);

}



// Assuming there are no observable exceptional/error cases for these functions

// as the interface does not specify error handling or exceptions.
