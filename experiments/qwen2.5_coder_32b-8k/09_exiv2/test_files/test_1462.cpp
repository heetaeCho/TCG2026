#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class Nikon2MnHeaderTest : public ::testing::Test {

protected:

    Nikon2MnHeader header;

};



TEST_F(Nikon2MnHeaderTest, IfdOffsetDefaultValue_1462) {

    EXPECT_EQ(header.ifdOffset(), 0U);

}



TEST_F(Nikon2MnHeaderTest, ReadFunctionReturnsFalseOnZeroSize_1462) {

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian; // Assuming a default value for ByteOrder

    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest, ReadFunctionReturnsFalseOnNullPointer_1462) {

    const byte* pData = nullptr;

    size_t size = 10; // Non-zero size

    ByteOrder byteOrder = littleEndian; // Assuming a default value for ByteOrder

    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(Nikon2MnHeaderTest, SizeOfSignatureReturnsExpectedValue_1462) {

    EXPECT_EQ(Nikon2MnHeader::sizeOfSignature(), 6U); // Assuming the signature size is 6 bytes

}



TEST_F(Nikon2MnHeaderTest, WriteFunctionReturnsZeroOnNullIoWrapper_1462) {

    IoWrapper* ioWrapper = nullptr;

    ByteOrder byteOrder = littleEndian; // Assuming a default value for ByteOrder

    EXPECT_EQ(header.write(*ioWrapper, byteOrder), 0U);

}



TEST_F(Nikon2MnHeaderTest, SizeFunctionReturnsZero_1462) {

    EXPECT_EQ(header.size(), 0U); // Assuming the size is zero by default

}
