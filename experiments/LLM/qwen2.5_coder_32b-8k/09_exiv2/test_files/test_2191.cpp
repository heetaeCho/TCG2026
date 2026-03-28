#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"

#include "types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class PentaxDngMnHeaderTest_2191 : public ::testing::Test {

protected:

    PentaxDngMnHeader header;

};



TEST_F(PentaxDngMnHeaderTest_2191, ReadReturnsFalseForNullData_2191) {

    EXPECT_FALSE(header.read(nullptr, 0, invalidByteOrder));

}



TEST_F(PentaxDngMnHeaderTest_2191, ReadReturnsTrueForValidData_2191) {

    byte data[] = {0x00, 0x01, 0x02, 0x03};

    EXPECT_TRUE(header.read(data, sizeof(data), littleEndian));

}



TEST_F(PentaxDngMnHeaderTest_2191, SizeOfSignatureReturnsNonZeroValue_2191) {

    EXPECT_NE(PentaxDngMnHeader::sizeOfSignature(), 0u);

}



TEST_F(PentaxDngMnHeaderTest_2191, BaseOffsetReturnsCorrectValue_2191) {

    size_t mnOffset = 10;

    EXPECT_EQ(header.baseOffset(mnOffset), header.size() + mnOffset);

}



TEST_F(PentaxDngMnHeaderTest_2191, SetByteOrderAndGetByteOrderConsistent_2191) {

    ByteOrder byteOrder = littleEndian;

    header.setByteOrder(byteOrder);

    EXPECT_EQ(header.byteOrder(), byteOrder);

}



TEST_F(PentaxDngMnHeaderTest_2191, IfdOffsetReturnsNonZeroValue_2191) {

    EXPECT_NE(header.ifdOffset(), 0u);

}



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(bool, write, (const byte* data, size_t size), (override));

};



TEST_F(PentaxDngMnHeaderTest_2191, WriteCallsWriteMethodOfIoWrapper_2191) {

    MockIoWrapper mockIo;

    EXPECT_CALL(mockIo, write(::testing::_, header.size())).WillOnce(::testing::Return(true));



    header.write(mockIo, littleEndian);

}
