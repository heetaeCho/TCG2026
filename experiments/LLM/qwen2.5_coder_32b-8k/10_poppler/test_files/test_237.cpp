#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using ::testing::_;

using ::testing::Return;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(bool, isEncoder, (), (const, override));

};



class RGBGrayEncoderTest : public ::testing::Test {

protected:

    MockStream mockStream;

    std::unique_ptr<RGBGrayEncoder> encoder;



    void SetUp() override {

        encoder = std::make_unique<RGBGrayEncoder>(&mockStream);

    }

};



TEST_F(RGBGrayEncoderTest_237, RewindReturnsTrue_237) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(encoder->rewind());

}



TEST_F(RGBGrayEncoderTest_237, GetKindCallsBaseMethod_237) {

    StreamKind expectedKind = streamRaw;

    EXPECT_CALL(mockStream, getKind()).WillOnce(Return(expectedKind));

    EXPECT_EQ(encoder->getKind(), expectedKind);

}



TEST_F(RGBGrayEncoderTest_237, LookCharReturnsBaseValue_237) {

    int expectedChar = 42;

    EXPECT_CALL(mockStream, lookChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(encoder->lookChar(), expectedChar);

}



TEST_F(RGBGrayEncoderTest_237, GetPSFilterCallsBaseMethod_237) {

    std::optional<std::string> expectedResult = "filter";

    EXPECT_CALL(mockStream, getPSFilter(1, "indent")).WillOnce(Return(expectedResult));

    EXPECT_EQ(encoder->getPSFilter(1, "indent"), expectedResult);

}



TEST_F(RGBGrayEncoderTest_237, IsBinaryCallsBaseMethod_237) {

    bool expectedBinary = true;

    EXPECT_CALL(mockStream, isBinary(true)).WillOnce(Return(expectedBinary));

    EXPECT_EQ(encoder->isBinary(), expectedBinary);

}



TEST_F(RGBGrayEncoderTest_237, IsEncoderReturnsTrue_237) {

    EXPECT_TRUE(encoder->isEncoder());

}



TEST_F(RGBGrayEncoderTest_237, GetCharFromBuffer_237) {

    char buffer[] = {0x1A, 0x2B};

    encoder->bufPtr = reinterpret_cast<unsigned char*>(buffer);

    encoder->bufEnd = reinterpret_cast<unsigned char*>(buffer + sizeof(buffer));



    EXPECT_EQ(encoder->getChar(), 0x1A);

    EXPECT_EQ(encoder->getChar(), 0x2B);

}



TEST_F(RGBGrayEncoderTest_237, GetCharBufferExhausted_237) {

    encoder->bufPtr = encoder->bufEnd;



    EXPECT_CALL(mockStream, fillBuf()).WillOnce(Return(false));

    EXPECT_EQ(encoder->getChar(), EOF);

}
