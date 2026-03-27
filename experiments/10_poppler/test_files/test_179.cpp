#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class ASCIIHexStreamTest_179 : public ::testing::Test {

protected:

    std::unique_ptr<Stream> mockStream;

    ASCIIHexStream* asciiHexStream;



    void SetUp() override {

        mockStream = std::make_unique<NiceMock<MockStream>>();

        asciiHexStream = new ASCIIHexStream(std::move(mockStream));

    }



    void TearDown() override {

        delete asciiHexStream;

    }

};



// Mock Stream class to be used for testing

class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (override));

    MOCK_METHOD(const bool, isBinary, (bool last), (const, override));

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

    MOCK_METHOD(int, getChar, (), (override));

};



TEST_F(ASCIIHexStreamTest_179, GetKindReturnsCorrectValue_179) {

    EXPECT_EQ(asciiHexStream->getKind(), strASCIIHex);

}



TEST_F(ASCIIHexStreamTest_179, RewindCallsUnderlyingStreamRewind_179) {

    EXPECT_CALL(*mockStream, rewind());

    asciiHexStream->rewind();

}



TEST_F(ASCIIHexStreamTest_179, LookCharCallsUnderlyingStreamLookChar_179) {

    int dummyReturn = 42;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(dummyReturn));

    EXPECT_EQ(asciiHexStream->lookChar(), dummyReturn);

}



TEST_F(ASCIIHexStreamTest_179, GetPSFilterCallsUnderlyingStreamGetPSFilter_179) {

    int psLevel = 2;

    const char* indent = "  ";

    std::optional<std::string> expected("expected");

    EXPECT_CALL(*mockStream, getPSFilter(psLevel, indent)).WillOnce(Return(expected));

    EXPECT_EQ(asciiHexStream->getPSFilter(psLevel, indent), expected);

}



TEST_F(ASCIIHexStreamTest_179, IsBinaryCallsUnderlyingStreamIsBinary_179) {

    bool last = true;

    bool expected = false;

    EXPECT_CALL(*mockStream, isBinary(last)).WillOnce(Return(expected));

    EXPECT_EQ(asciiHexStream->isBinary(last), expected);

}



TEST_F(ASCIIHexStreamTest_179, GetCharCallsUnderlyingStreamGetChar_179) {

    int dummyReturn = 42;

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(dummyReturn));

    EXPECT_EQ(asciiHexStream->getChar(), dummyReturn);

}
