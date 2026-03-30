#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <optional>



using namespace ::testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char *), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

};



class ASCIIHexEncoderTest_213 : public ::testing::Test {

protected:

    MockStream mockStream;

    std::unique_ptr<ASCIIHexEncoder> encoder;



    void SetUp() override {

        encoder = std::make_unique<ASCIIHexEncoder>(&mockStream);

    }

};



TEST_F(ASCIIHexEncoderTest_213, IsEncoder_ReturnsTrue_213) {

    EXPECT_TRUE(encoder->isEncoder());

}



TEST_F(ASCIIHexEncoderTest_213, Rewind_DelegatesToStream_213) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(encoder->rewind());

}



TEST_F(ASCIIHexEncoderTest_213, GetKind_DelegatesToStream_213) {

    StreamKind expectedKind = streamString;

    EXPECT_CALL(mockStream, getKind()).WillOnce(Return(expectedKind));

    EXPECT_EQ(expectedKind, encoder->getKind());

}



TEST_F(ASCIIHexEncoderTest_213, GetChar_DelegatesToStream_213) {

    int expectedChar = 'A';

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(expectedChar, encoder->getChar());

}



TEST_F(ASCIIHexEncoderTest_213, LookChar_DelegatesToStream_213) {

    int expectedChar = 'B';

    EXPECT_CALL(mockStream, lookChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(expectedChar, encoder->lookChar());

}



TEST_F(ASCIIHexEncoderTest_213, GetPSFilter_DelegatesToStream_213) {

    std::string filterName = "filter";

    EXPECT_CALL(mockStream, getPSFilter(1, StrEq("  "))).WillOnce(Return(std::optional<std::string>(filterName)));

    EXPECT_EQ(filterName, encoder->getPSFilter(1, "  ").value());

}



TEST_F(ASCIIHexEncoderTest_213, IsBinary_DelegatesToStream_213) {

    bool isBinaryFlag = true;

    EXPECT_CALL(mockStream, isBinary(true)).WillOnce(Return(isBinaryFlag));

    EXPECT_EQ(isBinaryFlag, encoder->isBinary(true));

}
