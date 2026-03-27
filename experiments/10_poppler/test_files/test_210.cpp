#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

};



class ASCIIHexEncoderTest : public Test {

protected:

    MockStream mockStream;

    std::unique_ptr<ASCIIHexEncoder> encoder;



    void SetUp() override {

        encoder = std::make_unique<ASCIIHexEncoder>(&mockStream);

    }

};



TEST_F(ASCIIHexEncoderTest_210, LookChar_ReturnsEOF_WhenBufferIsEmptyAndFillBufFails_210) {

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(EOF));

    EXPECT_EQ(encoder->lookChar(), EOF);

}



TEST_F(ASCIIHexEncoderTest_210, LookChar_ReturnsFirstByteOfBuffer_WhenBufferHasData_210) {

    const int expectedByte = 0xAB;

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(expectedByte));

    encoder->getChar(); // To fill the buffer

    EXPECT_EQ(encoder->lookChar(), expectedByte);

}



TEST_F(ASCIIHexEncoderTest_210, LookChar_ReturnsSameByteOnConsecutiveCalls_WhenBufferHasData_210) {

    const int expectedByte = 0xCD;

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(expectedByte));

    encoder->getChar(); // To fill the buffer

    EXPECT_EQ(encoder->lookChar(), expectedByte);

    EXPECT_EQ(encoder->lookChar(), expectedByte);

}



TEST_F(ASCIIHexEncoderTest_210, LookChar_ReturnsNextByteAfterGetCharIsCalled_210) {

    const int firstByte = 0xEF;

    const int secondByte = 0x90;

    EXPECT_CALL(mockStream, getChar())

        .WillOnce(Return(firstByte))

        .WillOnce(Return(secondByte));

    encoder->getChar(); // To fill the buffer with firstByte

    encoder->getChar(); // Consume firstByte and fetch secondByte

    EXPECT_EQ(encoder->lookChar(), secondByte);

}



TEST_F(ASCIIHexEncoderTest_210, Rewind_ResetBufferAndReturnsTrue_210) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(true));

    encoder->getChar(); // To fill the buffer

    EXPECT_TRUE(encoder->rewind());

    EXPECT_EQ(encoder->lookChar(), EOF);

}
