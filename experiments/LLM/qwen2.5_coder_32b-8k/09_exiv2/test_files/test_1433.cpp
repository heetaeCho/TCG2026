#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MnHeaderTest_1433 : public ::testing::Test {

protected:

    MnHeader mnHeader;

};



TEST_F(MnHeaderTest_1433, IfdOffsetReturnsZero_1433) {

    EXPECT_EQ(mnHeader.ifdOffset(), 0);

}



TEST_F(MnHeaderTest_1433, SetByteOrderDoesNotThrow_1433) {

    EXPECT_NO_THROW(mnHeader.setByteOrder(ByteOrder::bigEndian));

}



TEST_F(MnHeaderTest_1433, ByteOrderReturnsSetOrder_1433) {

    mnHeader.setByteOrder(ByteOrder::littleEndian);

    EXPECT_EQ(mnHeader.byteOrder(), ByteOrder::littleEndian);



    mnHeader.setByteOrder(ByteOrder::bigEndian);

    EXPECT_EQ(mnHeader.byteOrder(), ByteOrder::bigEndian);

}



TEST_F(MnHeaderTest_1433, BaseOffsetReturnsZeroForAnyInput_1433) {

    EXPECT_EQ(mnHeader.baseOffset(0), 0);

    EXPECT_EQ(mnHeader.baseOffset(123), 0);

    EXPECT_EQ(mnHeader.baseOffset(456789), 0);

}



TEST_F(MnHeaderTest_1433, SizeReturnsZero_1433) {

    EXPECT_EQ(mnHeader.size(), 0);

}



TEST_F(MnHeaderTest_1433, WriteDoesNotThrowAndReturnsZero_1433) {

    class MockIoWrapper : public IoWrapper {

    public:

        MOCK_METHOD(void, write(const byte* data, size_t length), (override));

    };



    MockIoWrapper mockIoWrapper;

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0);



    EXPECT_NO_THROW(EXPECT_EQ(mnHeader.write(mockIoWrapper, ByteOrder::bigEndian), 0));

}



TEST_F(MnHeaderTest_1433, ReadDoesNotThrowAndReturnsFalse_1433) {

    const byte data[] = {0x00};

    EXPECT_NO_THROW(EXPECT_FALSE(mnHeader.read(data, sizeof(data), ByteOrder::bigEndian)));

}
