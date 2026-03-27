#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char *), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(bool, isEncoder, () const, (override));



protected:

    bool fillBuf() override { return false; }

};



class CMYKGrayEncoderTest_232 : public ::testing::Test {

protected:

    MockStream mockStream;

    CMYKGrayEncoder encoder;



    CMYKGrayEncoderTest_232() : encoder(&mockStream) {}

};



TEST_F(CMYKGrayEncoderTest_232, RewindReturnsFalseByDefault_232) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(encoder.rewind());

}



TEST_F(CMYKGrayEncoderTest_232, RewindReturnsTrueWhenMocked_232) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(encoder.rewind());

}



TEST_F(CMYKGrayEncoderTest_232, GetKindDelegatesToMockStream_232) {

    StreamKind expectedKind = streamCCITTFax;

    EXPECT_CALL(mockStream, getKind()).WillOnce(::testing::Return(expectedKind));

    EXPECT_EQ(encoder.getKind(), expectedKind);

}



TEST_F(CMYKGrayEncoderTest_232, LookCharReturnsEOFWhenBufferIsEmptyAndFillBufFails_232) {

    encoder.bufPtr = encoder.bufEnd;

    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(EOF));

    EXPECT_EQ(encoder.lookChar(), EOF);

}



TEST_F(CMYKGrayEncoderTest_232, LookCharReturnsFirstByteWhenBufferHasData_232) {

    encoder.bufPtr = encoder.bufEnd - 1;

    *encoder.bufPtr = 0x42;

    EXPECT_CALL(mockStream, getChar()).Times(0);

    EXPECT_EQ(encoder.lookChar(), 0x42);

}



TEST_F(CMYKGrayEncoderTest_232, GetPSFilterDelegatesToMockStream_232) {

    std::optional<std::string> expectedFilter = "test_filter";

    int psLevel = 1;

    const char* indent = "  ";

    EXPECT_CALL(mockStream, getPSFilter(psLevel, indent)).WillOnce(::testing::Return(expectedFilter));

    EXPECT_EQ(encoder.getPSFilter(psLevel, indent), expectedFilter);

}



TEST_F(CMYKGrayEncoderTest_232, IsBinaryDelegatesToMockStream_232) {

    bool last = true;

    EXPECT_CALL(mockStream, isBinary(last)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(encoder.isBinary(last));

}



TEST_F(CMYKGrayEncoderTest_232, IsEncoderReturnsTrue_232) {

    EXPECT_TRUE(encoder.isEncoder());

}
