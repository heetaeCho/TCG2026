#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, error, (), (const override));

};



TEST_F(MockBasicIoTest_973, NormalOperation_ReadExactBytes_973) {

    MockBasicIo mockIo;

    DataBuf buffer(10);

    byte testData[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

    EXPECT_CALL(mockIo, read(buffer.data(), buffer.size())).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(testData, testData + 10),

        Return(10)

    ));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));



    EXPECT_NO_THROW(readChunk(buffer, mockIo));

}



TEST_F(MockBasicIoTest_973, BoundaryCondition_EmptyBuffer_973) {

    MockBasicIo mockIo;

    DataBuf buffer(0);

    EXPECT_CALL(mockIo, read(buffer.data(), buffer.size())).WillOnce(Return(0));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));



    EXPECT_NO_THROW(readChunk(buffer, mockIo));

}



TEST_F(MockBasicIoTest_973, ExceptionalCase_IoError_973) {

    MockBasicIo mockIo;

    DataBuf buffer(10);

    EXPECT_CALL(mockIo, read(buffer.data(), buffer.size())).WillOnce(Return(10));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(true));



    EXPECT_THROW(readChunk(buffer, mockIo), Error);

}



TEST_F(MockBasicIoTest_973, ExceptionalCase_ReadLessThanExpected_973) {

    MockBasicIo mockIo;

    DataBuf buffer(10);

    EXPECT_CALL(mockIo, read(buffer.data(), buffer.size())).WillOnce(Return(5));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));



    EXPECT_THROW(readChunk(buffer, mockIo), Error);

}



TEST_F(MockBasicIoTest_973, ExternalInteraction_ReadCallVerification_973) {

    MockBasicIo mockIo;

    DataBuf buffer(10);

    byte testData[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

    EXPECT_CALL(mockIo, read(buffer.data(), buffer.size())).WillOnce(testing::DoAll(

        testing::SetArrayArgument<0>(testData, testData + 10),

        Return(10)

    ));

    EXPECT_CALL(mockIo, error()).WillRepeatedly(Return(false));



    EXPECT_NO_THROW(readChunk(buffer, mockIo));

}
