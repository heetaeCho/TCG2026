#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const override));

};



class LZWEncoderTest_226 : public ::testing::Test {

protected:

    MockStream mockStream;

    LZWEncoder encoder;



    LZWEncoderTest_226() : encoder(&mockStream) {}

};



TEST_F(LZWEncoderTest_226, GetKind_ReturnsStrWeird_226) {

    EXPECT_EQ(encoder.getKind(), strWeird);

}



TEST_F(LZWEncoderTest_226, Rewind_DelegatesToStream_226) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(encoder.rewind());

}



TEST_F(LZWEncoderTest_226, GetChar_DelegatesToStream_226) {

    int expectedChar = 42;

    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(encoder.getChar(), expectedChar);

}



TEST_F(LZWEncoderTest_226, LookChar_DelegatesToStream_226) {

    int expectedChar = 99;

    EXPECT_CALL(mockStream, lookChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(encoder.lookChar(), expectedChar);

}



TEST_F(LZWEncoderTest_226, GetPSFilter_DelegatesToStream_226) {

    std::optional<std::string> expectedResult = "filterResult";

    EXPECT_CALL(mockStream, getPSFilter(::testing::_, ::testing::_)).WillOnce(::testing::Return(expectedResult));

    EXPECT_EQ(encoder.getPSFilter(0, ""), expectedResult);

}



TEST_F(LZWEncoderTest_226, IsBinary_DelegatesToStream_226) {

    bool last = true;

    bool expectedResult = false;

    EXPECT_CALL(mockStream, isBinary(last)).WillOnce(::testing::Return(expectedResult));

    EXPECT_EQ(encoder.isBinary(last), expectedResult);

}



TEST_F(LZWEncoderTest_226, IsEncoder_ReturnsTrue_226) {

    EXPECT_TRUE(encoder.isEncoder());

}
