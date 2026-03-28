#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;



// Mock IoWrapper for testing interactions

class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t count), (override));

};



class PentaxDngMnHeaderTest_1483 : public ::testing::Test {

protected:

    MockIoWrapper mockIoWrapper;

    PentaxDngMnHeader header;

};



TEST_F(PentaxDngMnHeaderTest_1483, WriteReturnsSignatureSize_1483) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(10));

    size_t result = header.write(mockIoWrapper, littleEndian);

    EXPECT_EQ(result, header.sizeOfSignature());

}



TEST_F(PentaxDngMnHeaderTest_1483, WriteCallsIoWrapperWithCorrectSize_1483) {

    EXPECT_CALL(mockIoWrapper, write(_, header.sizeOfSignature())).Times(1);

    header.write(mockIoWrapper, littleEndian);

}



TEST_F(PentaxDngMnHeaderTest_1483, WriteHandlesBigEndian_1483) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(header.sizeOfSignature()));

    size_t result = header.write(mockIoWrapper, bigEndian);

    EXPECT_EQ(result, header.sizeOfSignature());

}



TEST_F(PentaxDngMnHeaderTest_1483, WriteHandlesLittleEndian_1483) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).WillOnce(::testing::Return(header.sizeOfSignature()));

    size_t result = header.write(mockIoWrapper, littleEndian);

    EXPECT_EQ(result, header.sizeOfSignature());

}
