#include <gtest/gtest.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;



class FujiMnHeaderTest : public ::testing::Test {

protected:

    FujiMnHeader header;

};



TEST_F(FujiMnHeaderTest_1456, DefaultConstructorSetsByteOrderLittleEndian_1456) {

    EXPECT_EQ(header.byteOrder(), littleEndian);

}



TEST_F(FujiMnHeaderTest_1456, ReadMethodReturnsFalseOnInvalidData_1456) {

    const byte* data = nullptr;

    size_t dataSize = 0;

    ByteOrder bo = littleEndian;

    EXPECT_FALSE(header.read(data, dataSize, bo));

}



TEST_F(FujiMnHeaderTest_1456, ReadMethodReturnsTrueOnValidData_1456) {

    const byte validData[] = {0x49, 0x49, 0x2A, 0x00}; // Example valid TIFF header

    size_t dataSize = sizeof(validData);

    ByteOrder bo = littleEndian;

    EXPECT_TRUE(header.read(validData, dataSize, bo));

}



TEST_F(FujiMnHeaderTest_1456, SizeOfSignatureReturnsCorrectValue_1456) {

    EXPECT_EQ(FujiMnHeader::sizeOfSignature(), 8);

}



TEST_F(FujiMnHeaderTest_1456, BaseOffsetCalculation_1456) {

    size_t mnOffset = 10;

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset + FujiMnHeader::sizeOfSignature());

}



TEST_F(FujiMnHeaderTest_1456, WriteMethodReturnsCorrectSize_1456) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(size_t, write(const byte* data, size_t length), (override));

    };



    MockIoWrapper mockIoWrapper;

    ByteOrder bo = littleEndian;



    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_))

        .WillOnce(::testing::Return(FujiMnHeader::size()));



    EXPECT_EQ(header.write(mockIoWrapper, bo), FujiMnHeader::size());

}
