#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <optional>

#include <string>



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char* indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const, override));

    MOCK_METHOD(bool, isEncoder, () const, (override));



protected:

    MOCK_METHOD(bool, fillBuf, (), (override));

};



class RGBGrayEncoderTest : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<RGBGrayEncoder> encoder;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        encoder = std::make_unique<RGBGrayEncoder>(mockStream.get());

    }

};



TEST_F(RGBGrayEncoderTest_238, LookCharReturnsEOFWhenBufferIsEmptyAndFillBufFails_238) {

    EXPECT_CALL(*mockStream, fillBuf()).WillOnce(Return(false));

    int result = encoder->lookChar();

    EXPECT_EQ(result, EOF);

}



TEST_F(RGBGrayEncoderTest_238, LookCharReturnsCurrentBufferByteWhenBufferIsNotEmpty_238) {

    char dummyByte = 0x5A;

    mockStream->bufPtr = &dummyByte;

    mockStream->bufEnd = &dummyByte + 1;

    int result = encoder->lookChar();

    EXPECT_EQ(result, static_cast<int>(dummyByte));

}



TEST_F(RGBGrayEncoderTest_238, RewindDelegatesToStreamRewind_238) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));

    bool result = encoder->rewind();

    EXPECT_TRUE(result);

}



TEST_F(RGBGrayEncoderTest_238, GetKindDelegatesToStreamGetKind_238) {

    StreamKind dummyKind = streamRaw;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(Return(dummyKind));

    StreamKind result = encoder->getKind();

    EXPECT_EQ(result, dummyKind);

}



TEST_F(RGBGrayEncoderTest_238, GetCharDelegatesToStreamGetChar_238) {

    int dummyChar = 0x5A;

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(dummyChar));

    int result = encoder->getChar();

    EXPECT_EQ(result, dummyChar);

}



TEST_F(RGBGrayEncoderTest_238, GetPSFilterDelegatesToStreamGetPSFilter_238) {

    std::optional<std::string> dummyFilter = "dummyFilter";

    EXPECT_CALL(*mockStream, getPSFilter(1, "indent")).WillOnce(Return(dummyFilter));

    auto result = encoder->getPSFilter(1, "indent");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result.value(), dummyFilter.value());

}



TEST_F(RGBGrayEncoderTest_238, IsBinaryDelegatesToStreamIsBinary_238) {

    bool dummyResult = true;

    EXPECT_CALL(*mockStream, isBinary(true)).WillOnce(Return(dummyResult));

    bool result = encoder->isBinary();

    EXPECT_EQ(result, dummyResult);

}



TEST_F(RGBGrayEncoderTest_238, IsEncoderReturnsTrue_238) {

    EXPECT_TRUE(encoder->isEncoder());

}
