#include <gtest/gtest.h>

#include "Stream.h"



using namespace testing;



class RGBGrayEncoderTest_236 : public Test {

protected:

    StrictMock<MockStream> mockStream;

    RGBGrayEncoder encoder{&mockStream};



    class MockStream : public Stream {

    public:

        MOCK_METHOD(bool, rewind, (), (override));

        MOCK_METHOD(int, getChar, (), (override));

        MOCK_METHOD(int, lookChar, (), (override));

        MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

        MOCK_METHOD(bool, isBinary, (bool), (const, override));

        MOCK_METHOD(bool, isEncoder, (), (const, override));

    };

};



TEST_F(RGBGrayEncoderTest_236, GetKindReturnsStrWeird_236) {

    EXPECT_EQ(encoder.getKind(), strWeird);

}



TEST_F(RGBGrayEncoderTest_236, RewindCallsBaseRewind_236) {

    EXPECT_CALL(mockStream, rewind());

    encoder.rewind();

}



TEST_F(RGBGrayEncoderTest_236, GetCharDelegatesToBaseGetChar_236) {

    int expectedChar = 42;

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(encoder.getChar(), expectedChar);

}



TEST_F(RGBGrayEncoderTest_236, LookCharDelegatesToBaseLookChar_236) {

    int expectedChar = 42;

    EXPECT_CALL(mockStream, lookChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(encoder.lookChar(), expectedChar);

}



TEST_F(RGBGrayEncoderTest_236, GetPSFilterDelegatesToBaseGetPSFilter_236) {

    std::optional<std::string> expectedResult = "expectedResult";

    int psLevel = 1;

    const char* indent = "indent";

    EXPECT_CALL(mockStream, getPSFilter(psLevel, indent)).WillOnce(Return(expectedResult));

    EXPECT_EQ(encoder.getPSFilter(psLevel, indent), expectedResult);

}



TEST_F(RGBGrayEncoderTest_236, IsBinaryDelegatesToBaseIsBinary_236) {

    bool last = true;

    bool expectedResult = false;

    EXPECT_CALL(mockStream, isBinary(last)).WillOnce(Return(expectedResult));

    EXPECT_EQ(encoder.isBinary(last), expectedResult);

}



TEST_F(RGBGrayEncoderTest_236, IsEncoderReturnsTrue_236) {

    EXPECT_TRUE(encoder.isEncoder());

}
