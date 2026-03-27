#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const, override));

};



class ASCII85EncoderTest_214 : public ::testing::Test {

protected:

    MockStream mockStream;

    ASCII85Encoder encoder{&mockStream};

};



TEST_F(ASCII85EncoderTest_214, GetKindReturnsStrWeird_214) {

    EXPECT_EQ(encoder.getKind(), strWeird);

}



TEST_F(ASCII85EncoderTest_214, RewindDelegatesToStream_214) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(encoder.rewind());

}



TEST_F(ASCII85EncoderTest_214, GetCharDelegatesToStream_214) {

    int expectedChar = 42;

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(encoder.getChar(), expectedChar);

}



TEST_F(ASCII85EncoderTest_214, LookCharDelegatesToStream_214) {

    int expectedChar = 42;

    EXPECT_CALL(mockStream, lookChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(encoder.lookChar(), expectedChar);

}



TEST_F(ASCII85EncoderTest_214, GetPSFilterDelegatesToStream_214) {

    std::string expectedFilter = "filter";

    int psLevel = 3;

    const char* indent = "indent";

    EXPECT_CALL(mockStream, getPSFilter(psLevel, indent)).WillOnce(Return(expectedFilter));

    EXPECT_EQ(encoder.getPSFilter(psLevel, indent), expectedFilter);

}



TEST_F(ASCII85EncoderTest_214, IsBinaryDelegatesToStream_214) {

    bool last = true;

    bool isBinaryResult = false;

    EXPECT_CALL(mockStream, isBinary(last)).WillOnce(Return(isBinaryResult));

    EXPECT_EQ(encoder.isBinary(last), isBinaryResult);

}



TEST_F(ASCII85EncoderTest_214, IsEncoderReturnsTrue_214) {

    EXPECT_TRUE(encoder.isEncoder());

}
