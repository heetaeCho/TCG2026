#include <gtest/gtest.h>

#include "Stream.h"

#include <optional>



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(bool, isEncoder, (), (const, override));

};



class CMYKGrayEncoderTest_230 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mock_stream;

    std::unique_ptr<CMYKGrayEncoder> encoder;



    void SetUp() override {

        mock_stream = std::make_unique<MockStream>();

        encoder = std::make_unique<CMYKGrayEncoder>(mock_stream.get());

    }

};



TEST_F(CMYKGrayEncoderTest_230, GetKind_ReturnsStrWeird_230) {

    EXPECT_EQ(encoder->getKind(), strWeird);

}



TEST_F(CMYKGrayEncoderTest_230, Rewind_DelegatesToStream_230) {

    EXPECT_CALL(*mock_stream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(encoder->rewind());

}



TEST_F(CMYKGrayEncoderTest_230, GetChar_DelegatesToStream_230) {

    EXPECT_CALL(*mock_stream, getChar()).WillOnce(::testing::Return(42));

    EXPECT_EQ(encoder->getChar(), 42);

}



TEST_F(CMYKGrayEncoderTest_230, LookChar_DelegatesToStream_230) {

    EXPECT_CALL(*mock_stream, lookChar()).WillOnce(::testing::Return(84));

    EXPECT_EQ(encoder->lookChar(), 84);

}



TEST_F(CMYKGrayEncoderTest_230, GetPSFilter_DelegatesToStream_230) {

    std::optional<std::string> expected = "some_filter";

    EXPECT_CALL(*mock_stream, getPSFilter(1, "ind")).WillOnce(::testing::Return(expected));

    EXPECT_EQ(encoder->getPSFilter(1, "ind"), expected);

}



TEST_F(CMYKGrayEncoderTest_230, IsBinary_DelegatesToStream_230) {

    EXPECT_CALL(*mock_stream, isBinary(true)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(encoder->isBinary(true));

}



TEST_F(CMYKGrayEncoderTest_230, IsEncoder_ReturnsTrue_230) {

    EXPECT_TRUE(encoder->isEncoder());

}
