#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

};



class ASCIIHexEncoderTest_208 : public ::testing::Test {

protected:

    MockStream mockStream;

    std::unique_ptr<ASCIIHexEncoder> encoder;



    void SetUp() override {

        encoder = std::make_unique<ASCIIHexEncoder>(&mockStream);

    }

};



TEST_F(ASCIIHexEncoderTest_208, GetKindReturnsStrWeird_208) {

    EXPECT_EQ(encoder->getKind(), strWeird);

}



TEST_F(ASCIIHexEncoderTest_208, RewindDelegatesToUnderlyingStream_208) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(encoder->rewind());

}



TEST_F(ASCIIHexEncoderTest_208, GetCharDelegatesToUnderlyingStream_208) {

    int expectedChar = 42;

    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(encoder->getChar(), expectedChar);

}



TEST_F(ASCIIHexEncoderTest_208, LookCharDelegatesToUnderlyingStream_208) {

    int expectedChar = 42;

    EXPECT_CALL(mockStream, lookChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(encoder->lookChar(), expectedChar);

}



TEST_F(ASCIIHexEncoderTest_208, GetPSFilterDelegatesToUnderlyingStream_208) {

    std::optional<std::string> expectedResult = "filter";

    EXPECT_CALL(mockStream, getPSFilter(::testing::_, ::testing::_)).WillOnce(::testing::Return(expectedResult));

    EXPECT_EQ(encoder->getPSFilter(1, "indent"), expectedResult);

}



TEST_F(ASCIIHexEncoderTest_208, IsBinaryDelegatesToUnderlyingStream_208) {

    bool expectedBinary = true;

    EXPECT_CALL(mockStream, isBinary(true)).WillOnce(::testing::Return(expectedBinary));

    EXPECT_EQ(encoder->isBinary(), expectedBinary);

}



TEST_F(ASCIIHexEncoderTest_208, IsEncoderReturnsTrue_208) {

    EXPECT_TRUE(encoder->isEncoder());

}
