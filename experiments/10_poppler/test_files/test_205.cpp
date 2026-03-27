#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Stream.h"



class FixedLengthEncoderTest : public ::testing::Test {

protected:

    class MockStream : public Stream {

    public:

        MOCK_METHOD(bool, rewind, (), (override));

        MOCK_METHOD(int, getChar, (), (override));

        MOCK_METHOD(int, lookChar, (), (override));

        MOCK_METHOD(bool, isBinary, (bool), (const override));

        MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    };



    std::unique_ptr<MockStream> mockStream;

    FixedLengthEncoder* encoder;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        encoder = new FixedLengthEncoder(mockStream.get(), 10);

    }



    void TearDown() override {

        delete encoder;

    }

};



TEST_F(FixedLengthEncoderTest_205, GetKindReturnsStrWeird_205) {

    EXPECT_EQ(encoder->getKind(), strWeird);

}



TEST_F(FixedLengthEncoderTest_205, RewindDelegatesToStream_205) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(encoder->rewind());

}



TEST_F(FixedLengthEncoderTest_205, GetCharDelegatesToStream_205) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(42));

    EXPECT_EQ(encoder->getChar(), 42);

}



TEST_F(FixedLengthEncoderTest_205, LookCharDelegatesToStream_205) {

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(::testing::Return(42));

    EXPECT_EQ(encoder->lookChar(), 42);

}



TEST_F(FixedLengthEncoderTest_205, IsBinaryDelegatesToStream_205) {

    EXPECT_CALL(*mockStream, isBinary(::testing::_)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(encoder->isBinary(false));

}



TEST_F(FixedLengthEncoderTest_205, GetPSFilterDelegatesToStream_205) {

    std::optional<std::string> expected("expected");

    EXPECT_CALL(*mockStream, getPSFilter(::testing::_, ::testing::_)).WillOnce(::testing::Return(expected));

    EXPECT_EQ(encoder->getPSFilter(1, "indent"), expected);

}



TEST_F(FixedLengthEncoderTest_205, IsEncoderReturnsTrue_205) {

    EXPECT_TRUE(encoder->isEncoder());

}
