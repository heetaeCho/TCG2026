#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;



class IoWrapperMock : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t length), (override));

};



class PanasonicMnHeaderTest_1477 : public ::testing::Test {

protected:

    PanasonicMnHeader header;

    std::unique_ptr<IoWrapperMock> mockIoWrapper = std::make_unique<IoWrapperMock>();

};



TEST_F(PanasonicMnHeaderTest_1477, WriteCallsIoWrapperWriteWithSignature_1477) {

    EXPECT_CALL(*mockIoWrapper, write(header.signature_, header.sizeOfSignature()))

        .Times(1);



    header.write(*mockIoWrapper, littleEndian);

}



TEST_F(PanasonicMnHeaderTest_1477, WriteReturnsSizeOfSignature_1477) {

    EXPECT_CALL(*mockIoWrapper, write(_, _))

        .WillOnce(::testing::Return(header.sizeOfSignature()));



    size_t result = header.write(*mockIoWrapper, littleEndian);

    EXPECT_EQ(result, header.sizeOfSignature());

}



TEST_F(PanasonicMnHeaderTest_1477, WriteWithDifferentByteOrderStillWritesSignature_1477) {

    EXPECT_CALL(*mockIoWrapper, write(header.signature_, header.sizeOfSignature()))

        .Times(1);



    header.write(*mockIoWrapper, bigEndian);

}
