#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include "Error.h"



using namespace testing;



class StreamMock : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, doGetChars, (int nChars, unsigned char *buffer), (override));

    MOCK_METHOD(int, lookChar, (), (override));

};



TEST_F(StreamTest_122, ToUnsignedChars_NormalOperation_122) {

    StreamMock stream;

    std::vector<unsigned char> expected = {0x01, 0x02, 0x03};

    

    EXPECT_CALL(stream, rewind()).WillOnce(Return(true));

    EXPECT_CALL(stream, doGetChars(4096, _)).WillOnce(DoAll(SetArrayArgument<1>(expected.begin(), expected.end()), Return(expected.size())));

    EXPECT_CALL(stream, lookChar()).WillOnce(Return(EOF));



    std::vector<unsigned char> result = stream.toUnsignedChars();

    

    ASSERT_EQ(result, expected);

}



TEST_F(StreamTest_122, ToUnsignedChars_EmptyStream_122) {

    StreamMock stream;

    

    EXPECT_CALL(stream, rewind()).WillOnce(Return(true));

    EXPECT_CALL(stream, doGetChars(4096, _)).WillOnce(Return(0));



    std::vector<unsigned char> result = stream.toUnsignedChars();

    

    ASSERT_TRUE(result.empty());

}



TEST_F(StreamTest_122, ToUnsignedChars_RewindFailure_122) {

    StreamMock stream;

    

    EXPECT_CALL(stream, rewind()).WillOnce(Return(false));

    EXPECT_CALL(stream, doGetChars(_, _)).Times(0);



    std::vector<unsigned char> result = stream.toUnsignedChars();

    

    ASSERT_TRUE(result.empty());

}



TEST_F(StreamTest_122, ToUnsignedChars_MultipleReads_122) {

    StreamMock stream;

    std::vector<unsigned char> expectedPart1 = {0x01, 0x02, 0x03};

    std::vector<unsigned char> expectedPart2 = {0x04, 0x05, 0x06};

    std::vector<unsigned char> expectedFull(expectedPart1.begin(), expectedPart1.end());

    expectedFull.insert(expectedFull.end(), expectedPart2.begin(), expectedPart2.end());



    EXPECT_CALL(stream, rewind()).WillOnce(Return(true));

    EXPECT_CALL(stream, doGetChars(4096, _))

        .WillOnce(DoAll(SetArrayArgument<1>(expectedPart1.begin(), expectedPart1.end()), Return(expectedPart1.size())))

        .WillOnce(DoAll(SetArrayArgument<1>(expectedPart2.begin(), expectedPart2.end()), Return(expectedPart2.size())));

    EXPECT_CALL(stream, lookChar())

        .WillOnce(Return(0x04))

        .WillOnce(Return(EOF));



    std::vector<unsigned char> result = stream.toUnsignedChars();

    

    ASSERT_EQ(result, expectedFull);

}



TEST_F(StreamTest_122, ToUnsignedChars_SizeIncrement_122) {

    StreamMock stream;

    std::vector<unsigned char> expectedPart1(4096, 0x01);

    std::vector<unsigned char> expectedPart2(8192, 0x02);

    std::vector<unsigned char> expectedFull(expectedPart1.begin(), expectedPart1.end());

    expectedFull.insert(expectedFull.end(), expectedPart2.begin(), expectedPart2.end());



    EXPECT_CALL(stream, rewind()).WillOnce(Return(true));

    EXPECT_CALL(stream, doGetChars(4096, _))

        .WillOnce(DoAll(SetArrayArgument<1>(expectedPart1.begin(), expectedPart1.end()), Return(expectedPart1.size())))

        .WillOnce(DoAll(SetArrayArgument<1>(expectedPart2.begin(), expectedPart2.end()), Return(expectedPart2.size())));

    EXPECT_CALL(stream, lookChar())

        .WillOnce(Return(0x02))

        .WillOnce(Return(EOF));



    std::vector<unsigned char> result = stream.toUnsignedChars();

    

    ASSERT_EQ(result, expectedFull);

}



TEST_F(StreamTest_122, ToUnsignedChars_SizeOverflow_122) {

    StreamMock stream;

    std::vector<unsigned char> expectedPart1(4096, 0x01);

    std::vector<unsigned char> expectedPart2 = {0x02}; // This would cause overflow if size increment was applied



    EXPECT_CALL(stream, rewind()).WillOnce(Return(true));

    EXPECT_CALL(stream, doGetChars(4096, _))

        .WillOnce(DoAll(SetArrayArgument<1>(expectedPart1.begin(), expectedPart1.end()), Return(expectedPart1.size())))

        .WillOnce(DoAll(SetArrayArgument<1>(expectedPart2.begin(), expectedPart2.end()), Return(expectedPart2.size())));

    EXPECT_CALL(stream, lookChar())

        .WillOnce(Return(0x02))

        .WillOnce(Return(EOF));



    std::vector<unsigned char> result = stream.toUnsignedChars();

    

    ASSERT_EQ(result, expectedPart1); // Only first part is returned due to size overflow

}
