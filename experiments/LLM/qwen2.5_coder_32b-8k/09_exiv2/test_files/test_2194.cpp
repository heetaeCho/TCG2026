#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include "types.hpp"



using namespace Exiv2::Internal;



class SigmaMnHeaderTest : public ::testing::Test {

protected:

    SigmaMnHeader header;

};



TEST_F(SigmaMnHeaderTest, ConstructorInitializesCorrectly_2194) {

    EXPECT_EQ(header.sizeOfSignature(), header.size());

}



TEST_F(SigmaMnHeaderTest, ReadWithNullPointerThrows_2194) {

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(header.read(pData, size, byteOrder), std::exception);

}



TEST_F(SigmaMnHeaderTest, ReadWithZeroSizeReturnsFalse_2194) {

    const byte* pData = reinterpret_cast<const byte*>("dummy");

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_FALSE(header.read(pData, size, byteOrder));

}



TEST_F(SigmaMnHeaderTest, ReadWithValidDataReturnsTrue_2194) {

    const byte validData[] = {0x01, 0x02};

    size_t size = sizeof(validData);

    ByteOrder byteOrder = littleEndian;



    EXPECT_TRUE(header.read(validData, size, byteOrder));

}



TEST_F(SigmaMnHeaderTest, SetByteOrderUpdatesCorrectly_2194) {

    ByteOrder newByteOrder = bigEndian;

    header.setByteOrder(newByteOrder);



    EXPECT_EQ(header.byteOrder(), newByteOrder);

}



TEST_F(SigmaMnHeaderTest, IfdOffsetReturnsNonNegativeValue_2194) {

    EXPECT_GE(header.ifdOffset(), 0);

}



TEST_F(SigmaMnHeaderTest, SizeOfSignatureIsConsistent_2194) {

    size_t expectedSize = header.size();

    EXPECT_EQ(expectedSize, SigmaMnHeader::sizeOfSignature());

}
