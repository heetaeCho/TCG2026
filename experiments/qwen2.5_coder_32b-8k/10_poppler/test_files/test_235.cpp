#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



// Mocking the Stream class to use as a dependency in CMYKGrayEncoder

class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const, override));

};



class CMYKGrayEncoderTest_235 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<CMYKGrayEncoder> encoder;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        encoder = std::make_unique<CMYKGrayEncoder>(mockStream.get());

    }

};



TEST_F(CMYKGrayEncoderTest_235, RewindCallsStreamRewind_235) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(true));

    bool result = encoder->rewind();

    EXPECT_TRUE(result);

}



TEST_F(CMYKGrayEncoderTest_235, IsEncoderReturnsTrue_235) {

    EXPECT_TRUE(encoder->isEncoder());

}



TEST_F(CMYKGrayEncoderTest_235, GetKindDelegatesToStream_235) {

    StreamKind expectedKind = streamCCITTFax;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(::testing::Return(expectedKind));

    StreamKind result = encoder->getKind();

    EXPECT_EQ(result, expectedKind);

}



TEST_F(CMYKGrayEncoderTest_235, GetCharDelegatesToStream_235) {

    int expectedResult = 10;

    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(expectedResult));

    int result = encoder->getChar();

    EXPECT_EQ(result, expectedResult);

}



TEST_F(CMYKGrayEncoderTest_235, LookCharDelegatesToStream_235) {

    int expectedResult = 10;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(::testing::Return(expectedResult));

    int result = encoder->lookChar();

    EXPECT_EQ(result, expectedResult);

}



TEST_F(CMYKGrayEncoderTest_235, GetPSFilterDelegatesToStream_235) {

    std::optional<std::string> expectedValue = "filter";

    EXPECT_CALL(*mockStream, getPSFilter(1, "indent")).WillOnce(::testing::Return(expectedValue));

    std::optional<std::string> result = encoder->getPSFilter(1, "indent");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), expectedValue.value());

}



TEST_F(CMYKGrayEncoderTest_235, IsBinaryDelegatesToStream_235) {

    bool expectedResult = true;

    EXPECT_CALL(*mockStream, isBinary(true)).WillOnce(::testing::Return(expectedResult));

    bool result = encoder->isBinary(true);

    EXPECT_EQ(result, expectedResult);

}
