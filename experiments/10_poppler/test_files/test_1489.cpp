#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockBaseStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));

};



class BaseStreamStreamTest_1489 : public ::testing::Test {

protected:

    std::unique_ptr<MockBaseStream> mockBaseStream;

    std::unique_ptr<BaseStreamStream> baseStreamStream;



    void SetUp() override {

        mockBaseStream = std::make_unique<MockBaseStream>();

        baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockBaseStream));

    }

};



TEST_F(BaseStreamStreamTest_1489, GetChar_NormalOperation_1489) {

    EXPECT_CALL(*mockBaseStream, getChar()).WillOnce(Return(65));

    int result = baseStreamStream->getChar();

    EXPECT_EQ(result, 65);

}



TEST_F(BaseStreamStreamTest_1489, GetChar_BoundaryCondition_Zero_1489) {

    EXPECT_CALL(*mockBaseStream, getChar()).WillOnce(Return(0));

    int result = baseStreamStream->getChar();

    EXPECT_EQ(result, 0);

}



TEST_F(BaseStreamStreamTest_1489, GetChar_ExceptionalCase_EndOfFile_1489) {

    EXPECT_CALL(*mockBaseStream, getChar()).WillOnce(Return(-1));

    int result = baseStreamStream->getChar();

    EXPECT_EQ(result, -1);

}



TEST_F(BaseStreamStreamTest_1489, GetBaseStream_NormalOperation_1489) {

    BaseStream* mockBasePtr = mockBaseStream.get();

    EXPECT_CALL(*mockBaseStream, getBaseStream()).WillOnce(Return(mockBasePtr));

    BaseStream* result = baseStreamStream->getBaseStream();

    EXPECT_EQ(result, mockBasePtr);

}



TEST_F(BaseStreamStreamTest_1489, GetBaseStream_ExceptionalCase_Null_1489) {

    EXPECT_CALL(*mockBaseStream, getBaseStream()).WillOnce(Return(nullptr));

    BaseStream* result = baseStreamStream->getBaseStream();

    EXPECT_EQ(result, nullptr);

}
