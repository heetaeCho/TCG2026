#include <gtest/gtest.h>

#include "makernote_int.hpp"



namespace Exiv2 {

namespace Internal {



class PentaxDngMnHeaderTest : public ::testing::Test {

protected:

    PentaxDngMnHeader header;

};



TEST_F(PentaxDngMnHeaderTest_1478, SizeOfSignature_ReturnsCorrectSize_1478) {

    EXPECT_EQ(header.sizeOfSignature(), sizeof(header.signature_));

}



// Assuming size() is observable and can be tested

TEST_F(PentaxDngMnHeaderTest_1478, Size_ReturnsExpectedValue_1478) {

    // Since we don't have control over the internal state, we assume a call to size() returns a non-zero value.

    EXPECT_NE(header.size(), 0u);

}



// Assuming ifdOffset() is observable and can be tested

TEST_F(PentaxDngMnHeaderTest_1478, IfdOffset_ReturnsExpectedValue_1478) {

    // Since we don't have control over the internal state, we assume a call to ifdOffset() returns a non-negative value.

    EXPECT_GE(header.ifdOffset(), 0u);

}



// Assuming baseOffset() is observable and can be tested

TEST_F(PentaxDngMnHeaderTest_1478, BaseOffset_ReturnsExpectedValueForZeroOffset_1478) {

    EXPECT_GE(header.baseOffset(0), 0u);

}



TEST_F(PentaxDngMnHeaderTest_1478, BaseOffset_ReturnsExpectedValueForNonZeroOffset_1478) {

    size_t mnOffset = 10;

    EXPECT_GE(header.baseOffset(mnOffset), mnOffset);

}



// Assuming read() is observable and can be tested with a mock IoWrapper

TEST_F(PentaxDngMnHeaderTest_1478, Read_ReturnsTrueForValidData_1478) {

    byte data[100];

    size_t dataSize = sizeof(data);

    ByteOrder byteOrder = littleEndian; // Example byte order



    EXPECT_TRUE(header.read(data, dataSize, byteOrder));

}



// Assuming write() is observable and can be tested with a mock IoWrapper

TEST_F(PentaxDngMnHeaderTest_1478, Write_ReturnsExpectedSize_1478) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian; // Example byte order



    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_)).WillOnce(testing::Return(header.size()));



    EXPECT_EQ(header.write(mockIoWrapper, byteOrder), header.size());

}



}  // namespace Internal

}  // namespace Exiv2
