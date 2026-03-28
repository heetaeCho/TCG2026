#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const override));

    MOCK_METHOD(bool, isEncoder, (), (const override));



protected:

    bool fillBuf() override { return true; }

    int getChar() override { return 0; }

};



class CMYKGrayEncoderTest_231 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mock_stream;

    std::unique_ptr<CMYKGrayEncoder> encoder;



    void SetUp() override {

        mock_stream = std::make_unique<MockStream>();

        encoder = std::make_unique<CMYKGrayEncoder>(mock_stream.get());

    }

};



TEST_F(CMYKGrayEncoderTest_231, GetCharReturnsEOFWhenBufferIsEmptyAndFillBufFails_231) {

    EXPECT_CALL(*mock_stream, fillBuf()).WillOnce(testing::Return(false));

    int result = encoder->getChar();

    ASSERT_EQ(result, EOF);

}



TEST_F(CMYKGrayEncoderTest_231, GetCharReturnsValidCharacterWhenBufferIsNotEmpty_231) {

    EXPECT_CALL(*mock_stream, fillBuf()).WillOnce(testing::Return(true));

    int result = encoder->getChar();

    ASSERT_GE(result, 0);

    ASSERT_LE(result, 255);

}



TEST_F(CMYKGrayEncoderTest_231, RewindDelegatesToUnderlyingStream_231) {

    EXPECT_CALL(*mock_stream, rewind()).WillOnce(testing::Return(true));

    bool result = encoder->rewind();

    ASSERT_TRUE(result);

}



TEST_F(CMYKGrayEncoderTest_231, GetKindDelegatesToUnderlyingStream_231) {

    StreamKind expected_kind = streamRaw;

    EXPECT_CALL(*mock_stream, getKind()).WillOnce(testing::Return(expected_kind));

    StreamKind result = encoder->getKind();

    ASSERT_EQ(result, expected_kind);

}



TEST_F(CMYKGrayEncoderTest_231, LookCharDelegatesToUnderlyingStream_231) {

    int expected_char = 42;

    EXPECT_CALL(*mock_stream, lookChar()).WillOnce(testing::Return(expected_char));

    int result = encoder->lookChar();

    ASSERT_EQ(result, expected_char);

}



TEST_F(CMYKGrayEncoderTest_231, GetPSFilterDelegatesToUnderlyingStream_231) {

    std::optional<std::string> expected_filter = "filter";

    EXPECT_CALL(*mock_stream, getPSFilter(testing::_, testing::_)).WillOnce(testing::Return(expected_filter));

    auto result = encoder->getPSFilter(0, "");

    ASSERT_EQ(result, expected_filter);

}



TEST_F(CMYKGrayEncoderTest_231, IsBinaryDelegatesToUnderlyingStream_231) {

    EXPECT_CALL(*mock_stream, isBinary(testing::_)).WillOnce(testing::Return(true));

    bool result = encoder->isBinary(true);

    ASSERT_TRUE(result);

}



TEST_F(CMYKGrayEncoderTest_231, IsEncoderReturnsTrue_231) {

    bool result = encoder->isEncoder();

    ASSERT_TRUE(result);

}
