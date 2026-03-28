#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <optional>



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(const bool, isBinary, (bool), (const override));

    MOCK_METHOD(StreamKind, getKind, (), (const override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

};



class FixedLengthEncoderTest_207 : public Test {

protected:

    MockStream mockStream;

    std::unique_ptr<FixedLengthEncoder> encoder;



    void SetUp() override {

        encoder = std::make_unique<FixedLengthEncoder>(&mockStream, 10);

    }

};



TEST_F(FixedLengthEncoderTest_207, IsEncoderReturnsTrue_207) {

    EXPECT_TRUE(encoder->isEncoder());

}



TEST_F(FixedLengthEncoderTest_207, RewindDelegatesToStream_207) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(encoder->rewind());

}



TEST_F(FixedLengthEncoderTest_207, GetCharDelegatesToStream_207) {

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(42));

    EXPECT_EQ(encoder->getChar(), 42);

}



TEST_F(FixedLengthEncoderTest_207, LookCharDelegatesToStream_207) {

    EXPECT_CALL(mockStream, lookChar()).WillOnce(Return(99));

    EXPECT_EQ(encoder->lookChar(), 99);

}



TEST_F(FixedLengthEncoderTest_207, IsBinaryDelegatesToStream_207) {

    bool unnamed = true;

    EXPECT_CALL(mockStream, isBinary(unnamed)).WillOnce(Return(true));

    EXPECT_TRUE(encoder->isBinary(unnamed));

}



TEST_F(FixedLengthEncoderTest_207, GetKindDelegatesToStream_207) {

    StreamKind expectedKind = streamDCTDecode;

    EXPECT_CALL(mockStream, getKind()).WillOnce(Return(expectedKind));

    EXPECT_EQ(encoder->getKind(), expectedKind);

}



TEST_F(FixedLengthEncoderTest_207, GetPSFilterDelegatesToStream_207) {

    int psLevel = 1;

    const char* indent = "  ";

    std::optional<std::string> expectedFilter = "DCTDecode";

    EXPECT_CALL(mockStream, getPSFilter(psLevel, indent)).WillOnce(Return(expectedFilter));

    EXPECT_EQ(encoder->getPSFilter(psLevel, indent), expectedFilter);

}



TEST_F(FixedLengthEncoderTest_207, GetPSFilterReturnsNulloptWhenNotSupported_207) {

    int psLevel = 1;

    const char* indent = "  ";

    std::optional<std::string> expectedFilter = std::nullopt;

    EXPECT_CALL(mockStream, getPSFilter(psLevel, indent)).WillOnce(Return(expectedFilter));

    EXPECT_EQ(encoder->getPSFilter(psLevel, indent), expectedFilter);

}
