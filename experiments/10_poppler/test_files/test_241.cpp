#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using ::testing::NiceMock;

using ::testing::_;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

};



class RGBGrayEncoderTest_241 : public ::testing::Test {

protected:

    NiceMock<MockStream> mockStream;

    std::unique_ptr<RGBGrayEncoder> encoder;



    void SetUp() override {

        encoder = std::make_unique<RGBGrayEncoder>(&mockStream);

    }

};



TEST_F(RGBGrayEncoderTest_241, IsEncoder_ReturnsTrue_241) {

    EXPECT_TRUE(encoder->isEncoder());

}



TEST_F(RGBGrayEncoderTest_241, Rewind_CallsUnderlyingStreamRewind_241) {

    EXPECT_CALL(mockStream, rewind()).Times(1);

    encoder->rewind();

}



TEST_F(RGBGrayEncoderTest_241, GetKind_DelegatesToUnderlyingStream_241) {

    StreamKind expectedKind = strFile;

    EXPECT_CALL(mockStream, getKind()).WillOnce(::testing::Return(expectedKind));

    EXPECT_EQ(encoder->getKind(), expectedKind);

}



TEST_F(RGBGrayEncoderTest_241, GetChar_DelegatesToUnderlyingStream_241) {

    int expectedChar = 'A';

    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(encoder->getChar(), expectedChar);

}



TEST_F(RGBGrayEncoderTest_241, LookChar_DelegatesToUnderlyingStream_241) {

    int expectedChar = 'B';

    EXPECT_CALL(mockStream, lookChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(encoder->lookChar(), expectedChar);

}



TEST_F(RGBGrayEncoderTest_241, GetPSFilter_DelegatesToUnderlyingStream_241) {

    std::optional<std::string> expectedResult = "filter";

    EXPECT_CALL(mockStream, getPSFilter(::_, _)).WillOnce(::testing::Return(expectedResult));

    EXPECT_EQ(encoder->getPSFilter(0, ""), expectedResult);

}



TEST_F(RGBGrayEncoderTest_241, IsBinary_DelegatesToUnderlyingStream_241) {

    bool expectedBinary = true;

    EXPECT_CALL(mockStream, isBinary(_)).WillOnce(::testing::Return(expectedBinary));

    EXPECT_EQ(encoder->isBinary(true), expectedBinary);

}
