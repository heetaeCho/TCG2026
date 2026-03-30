#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(bool, hasGetChars, (), (const, override));

    MOCK_METHOD(int, getChars, (int nChars, unsigned char *buffer), (override));

};



class StreamTest_119 : public ::testing::Test {

protected:

    MockStream mockStream;

};



TEST_F(StreamTest_119, doGetChars_NormalOperation_119) {

    unsigned char buffer[5];

    EXPECT_CALL(mockStream, hasGetChars()).WillOnce(Return(true));

    EXPECT_CALL(mockStream, getChars(3, NotNull())).WillOnce(DoAll(SetArrayArgument<1>(buffer, buffer + 3), Return(3)));



    int result = mockStream.doGetChars(3, buffer);

    EXPECT_EQ(result, 3);

}



TEST_F(StreamTest_119, doGetChars_BoundaryCondition_ZeroChars_119) {

    unsigned char buffer[5];

    EXPECT_CALL(mockStream, hasGetChars()).WillOnce(Return(true));

    EXPECT_CALL(mockStream, getChars(0, NotNull())).Times(0);



    int result = mockStream.doGetChars(0, buffer);

    EXPECT_EQ(result, 0);

}



TEST_F(StreamTest_119, doGetChars_BoundaryCondition_MaxIntChars_119) {

    unsigned char* largeBuffer = new unsigned char[INT_MAX];

    EXPECT_CALL(mockStream, hasGetChars()).WillOnce(Return(true));

    EXPECT_CALL(mockStream, getChars(INT_MAX, NotNull())).Times(0);



    int result = mockStream.doGetChars(INT_MAX, largeBuffer);

    delete[] largeBuffer;

}



TEST_F(StreamTest_119, doGetChars_ErrorCase_EOFBeforeNChars_119) {

    unsigned char buffer[5];

    EXPECT_CALL(mockStream, hasGetChars()).WillOnce(Return(false));

    EXPECT_CALL(mockStream, getChar())

        .WillOnce(Return('a'))

        .WillOnce(Return(EOF));



    int result = mockStream.doGetChars(3, buffer);

    EXPECT_EQ(result, 1);

    EXPECT_EQ(buffer[0], 'a');

}



TEST_F(StreamTest_119, doGetChars_ErrorCase_AllEOFs_119) {

    unsigned char buffer[5];

    EXPECT_CALL(mockStream, hasGetChars()).WillOnce(Return(false));

    EXPECT_CALL(mockStream, getChar())

        .Times(3)

        .WillRepeatedly(Return(EOF));



    int result = mockStream.doGetChars(3, buffer);

    EXPECT_EQ(result, 0);

}



TEST_F(StreamTest_119, doGetChars_UseGetCharsWhenAvailable_119) {

    unsigned char buffer[5];

    EXPECT_CALL(mockStream, hasGetChars()).WillOnce(Return(true));

    EXPECT_CALL(mockStream, getChars(3, NotNull())).WillOnce(Return(3));



    int result = mockStream.doGetChars(3, buffer);

    EXPECT_EQ(result, 3);

}



TEST_F(StreamTest_119, doGetChars_UseGetCharWhenGetCharsNotAvailable_119) {

    unsigned char buffer[5];

    EXPECT_CALL(mockStream, hasGetChars()).WillOnce(Return(false));

    EXPECT_CALL(mockStream, getChar())

        .Times(3)

        .WillRepeatedly(Return('a'));



    int result = mockStream.doGetChars(3, buffer);

    EXPECT_EQ(result, 3);

    EXPECT_EQ(buffer[0], 'a');

    EXPECT_EQ(buffer[1], 'a');

    EXPECT_EQ(buffer[2], 'a');

}
