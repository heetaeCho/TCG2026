#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <optional>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const, override));

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

};



class ASCIIHexStreamTest_180 : public Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<ASCIIHexStream> asciiHexStream;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        asciiHexStream = std::make_unique<ASCIIHexStream>(std::move(mockStream));

    }

};



TEST_F(ASCIIHexStreamTest_180, RewindCallsUnderlyingRewind_180) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));



    bool result = asciiHexStream->rewind();

    EXPECT_TRUE(result);

}



TEST_F(ASCIIHexStreamTest_180, LookCharReturnsMockedValue_180) {

    const int mockValue = 42;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(mockValue));



    int result = asciiHexStream->lookChar();

    EXPECT_EQ(result, mockValue);

}



TEST_F(ASCIIHexStreamTest_180, GetPSFilterDelegatesToUnderlyingStream_180) {

    const int psLevel = 1;

    const char* indent = " ";

    std::optional<std::string> expected = "filter";

    EXPECT_CALL(*mockStream, getPSFilter(psLevel, indent)).WillOnce(Return(expected));



    auto result = asciiHexStream->getPSFilter(psLevel, indent);

    EXPECT_EQ(result, expected);

}



TEST_F(ASCIIHexStreamTest_180, IsBinaryDelegatesToUnderlyingStream_180) {

    bool last = true;

    const bool expected = true;

    EXPECT_CALL(*mockStream, isBinary(last)).WillOnce(Return(expected));



    auto result = asciiHexStream->isBinary(last);

    EXPECT_EQ(result, expected);

}



TEST_F(ASCIIHexStreamTest_180, GetKindDelegatesToUnderlyingStream_180) {

    const StreamKind expected = streamNone;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(Return(expected));



    auto result = asciiHexStream->getKind();

    EXPECT_EQ(result, expected);

}



TEST_F(ASCIIHexStreamTest_180, GetCharReturnsEOFWhenBufferIsEOF_180) {

    asciiHexStream->buf = EOF;



    int result = asciiHexStream->getChar();

    EXPECT_EQ(result, EOF);

}



TEST_F(ASCIIHexStreamTest_180, GetCharDelegatesToLookCharAndResetsBuf_180) {

    const int mockValue = 42;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(mockValue));



    asciiHexStream->buf = 5; // arbitrary non-EOF value

    int result = asciiHexStream->getChar();

    

    EXPECT_EQ(result, mockValue);

    EXPECT_EQ(asciiHexStream->buf, EOF);

}



TEST_F(ASCIIHexStreamTest_180, GetCharHandlesLookCharReturningEOF_180) {

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(EOF));



    int result = asciiHexStream->getChar();

    EXPECT_EQ(result, EOF);

}
