#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "basicio.hpp"

#include "error.hpp"



using namespace Exiv2;

using namespace testing;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

};



class RemoteIoTest : public Test {

protected:

    MockBasicIo mockSrc;

    RemoteIo remoteIo;

};



TEST_F(RemoteIoTest, Transfer_Success_608) {

    EXPECT_CALL(mockSrc, open()).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, write(_)).WillOnce(Return(10u));

    EXPECT_CALL(mockSrc, close());



    EXPECT_NO_THROW(remoteIo.transfer(mockSrc));

}



TEST_F(RemoteIoTest, Transfer_OpenFailure_608) {

    EXPECT_CALL(mockSrc, open()).WillOnce(Return(-1));



    EXPECT_THROW({

        try {

            remoteIo.transfer(mockSrc);

        } catch (const Error& e) {

            EXPECT_EQ(e.code(), ErrorCode::kerErrorMessage);

            throw;

        }

    }, Error);

}



TEST_F(RemoteIoTest, Transfer_WriteFailure_608) {

    EXPECT_CALL(mockSrc, open()).WillOnce(Return(0));

    EXPECT_CALL(mockSrc, write(_)).WillOnce(Return(0u));

    EXPECT_CALL(mockSrc, close());



    EXPECT_NO_THROW(remoteIo.transfer(mockSrc));

}
