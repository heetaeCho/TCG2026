#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



namespace Exiv2 { namespace Internal {



class PentaxDngMnHeaderTest_1481 : public ::testing::Test {

protected:

    PentaxDngMnHeader header;

};



TEST_F(PentaxDngMnHeaderTest_1481, IfdOffset_ReturnsSizeOfSignature_1481) {

    EXPECT_EQ(header.ifdOffset(), PentaxDngMnHeader::sizeOfSignature());

}



// Assuming size() returns a value that can be tested

TEST_F(PentaxDngMnHeaderTest_1481, Size_ReturnsExpectedValue_1481) {

    EXPECT_GT(header.size(), 0u); // Assuming size is always positive

}



TEST_F(PentaxDngMnHeaderTest_1481, BaseOffset_CalculatesCorrectly_1481) {

    size_t mnOffset = 10;

    EXPECT_EQ(header.baseOffset(mnOffset), mnOffset + header.ifdOffset());

}



// Assuming read() and write() can be tested with mock IoWrapper and byte data

class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));

};



TEST_F(PentaxDngMnHeaderTest_1481, Read_ReturnsTrueForValidData_1481) {

    const byte data[] = {0x01, 0x02, 0x03};

    size_t dataSize = sizeof(data);

    ByteOrder byteOrder = littleEndian;

    EXPECT_TRUE(header.read(data, dataSize, byteOrder));

}



TEST_F(PentaxDngMnHeaderTest_1481, Write_ReturnsExpectedSize_1481) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t expectedSize = header.write(mockIoWrapper, byteOrder);

    EXPECT_EQ(expectedSize, header.size());

}



TEST_F(PentaxDngMnHeaderTest_1481, Write_CallsMockWriteMethod_1481) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian;

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_))

        .Times(1);

    header.write(mockIoWrapper, byteOrder);

}



}} // namespace Exiv2::Internal
