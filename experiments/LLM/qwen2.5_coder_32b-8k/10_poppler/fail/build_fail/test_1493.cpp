#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockBaseStream : public Stream {

public:

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));

};



class BaseStreamStreamTest_1493 : public ::testing::Test {

protected:

    std::unique_ptr<MockBaseStream> mockBaseStream;

    std::unique_ptr<BaseStreamStream> baseStreamStream;



    void SetUp() override {

        mockBaseStream = std::make_unique<MockBaseStream>();

        baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockBaseStream));

    }

};



TEST_F(BaseStreamStreamTest_1493, UnfilteredRewind_DelegatesToBaseStream_1493) {

    EXPECT_CALL(*mockBaseStream, getBaseStream()).WillOnce(Return(mockBaseStream.get()));

    EXPECT_CALL(*mockBaseStream->getBaseStream(), unfilteredRewind()).WillOnce(Return(true));



    bool result = baseStreamStream->unfilteredRewind();



    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest_1493, UnfilteredRewind_ReturnsFalseIfBaseStreamFails_1493) {

    EXPECT_CALL(*mockBaseStream, getBaseStream()).WillOnce(Return(mockBaseStream.get()));

    EXPECT_CALL(*mockBaseStream->getBaseStream(), unfilteredRewind()).WillOnce(Return(false));



    bool result = baseStreamStream->unfilteredRewind();



    EXPECT_FALSE(result);

}



TEST_F(BaseStreamStreamTest_1493, GetBaseStream_DelegatesToBaseStream_1493) {

    BaseStream* expectedBaseStream = mockBaseStream.get();

    EXPECT_CALL(*mockBaseStream, getBaseStream()).WillOnce(Return(expectedBaseStream));



    BaseStream* result = baseStreamStream->getBaseStream();



    EXPECT_EQ(result, expectedBaseStream);

}
