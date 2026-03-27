#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



class StreamMock : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, doGetChars, (int nChars, unsigned char *buffer), (override));

};



TEST_F(StreamTest_120, FillString_EmptyStringOnRewindFail_120) {

    StreamMock stream;

    std::string result;



    EXPECT_CALL(stream, rewind()).WillOnce(testing::Return(false));



    stream.fillString(result);



    EXPECT_TRUE(result.empty());

}



TEST_F(StreamTest_120, FillString_ReadZeroChars_120) {

    StreamMock stream;

    std::string result;



    EXPECT_CALL(stream, rewind()).WillOnce(testing::Return(true));

    EXPECT_CALL(stream, doGetChars(4096, testing::_)).WillOnce(testing::Return(0));



    stream.fillString(result);



    EXPECT_TRUE(result.empty());

}



TEST_F(StreamTest_120, FillString_ReadSomeChars_120) {

    StreamMock stream;

    std::string result;



    unsigned char buffer[4096] = { 'H', 'e', 'l', 'l', 'o' };

    

    EXPECT_CALL(stream, rewind()).WillOnce(testing::Return(true));

    EXPECT_CALL(stream, doGetChars(4096, testing::_))

        .WillOnce(testing::DoAll(testing::SetArrayArgument<1>(buffer, buffer + 5), testing::Return(5)));



    stream.fillString(result);



    EXPECT_EQ("Hello", result);

}



TEST_F(StreamTest_120, FillString_ReadMultipleBuffers_120) {

    StreamMock stream;

    std::string result;



    unsigned char buffer1[4096] = { 'H', 'e', 'l', 'l', 'o' };

    unsigned char buffer2[4096] = { ' ', 'W', 'o', 'r', 'l', 'd' };



    EXPECT_CALL(stream, rewind()).WillOnce(testing::Return(true));

    EXPECT_CALL(stream, doGetChars(4096, testing::_))

        .WillOnce(testing::DoAll(testing::SetArrayArgument<1>(buffer1, buffer1 + 5), testing::Return(5)))

        .WillOnce(testing::DoAll(testing::SetArrayArgument<1>(buffer2, buffer2 + 6), testing::Return(6)))

        .WillOnce(testing::Return(0));



    stream.fillString(result);



    EXPECT_EQ("Hello World", result);

}



TEST_F(StreamTest_120, FillString_ReadBoundaryChars_120) {

    StreamMock stream;

    std::string result;



    unsigned char buffer[4096] = { 'A' };



    EXPECT_CALL(stream, rewind()).WillOnce(testing::Return(true));

    EXPECT_CALL(stream, doGetChars(4096, testing::_))

        .WillOnce(testing::DoAll(testing::SetArrayArgument<1>(buffer, buffer + 1), testing::Return(1)));



    stream.fillString(result);



    EXPECT_EQ("A", result);

}



TEST_F(StreamTest_120, FillString_ReadMaxBufferChars_120) {

    StreamMock stream;

    std::string result;



    unsigned char buffer[4096];

    for (int i = 0; i < 4096; ++i) {

        buffer[i] = 'A';

    }



    EXPECT_CALL(stream, rewind()).WillOnce(testing::Return(true));

    EXPECT_CALL(stream, doGetChars(4096, testing::_))

        .WillOnce(testing::DoAll(testing::SetArrayArgument<1>(buffer, buffer + 4096), testing::Return(4096)));



    stream.fillString(result);



    EXPECT_EQ(std::string(4096, 'A'), result);

}
