#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/FlateEncoder.h"

#include <optional>

#include <string>



class FlateEncoderTest_1654 : public ::testing::Test {

protected:

    class MockStream : public Stream {

    public:

        MOCK_METHOD(bool, rewind, (), (override));

        MOCK_METHOD(int, getChar, (), (override));

        MOCK_METHOD(int, lookChar, (), (override));

        MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

        MOCK_METHOD(bool, isBinary, (bool), (const override));

        MOCK_METHOD(StreamKind, getKind, (), (const override));

    };



    MockStream mockStream;

    FlateEncoder flateEncoder{&mockStream};



    FlateEncoderTest_1654() = default;

    ~FlateEncoderTest_1654() override = default;



    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(FlateEncoderTest_1654, IsEncoder_ReturnsTrue_1654) {

    EXPECT_TRUE(flateEncoder.isEncoder());

}



TEST_F(FlateEncoderTest_1654, Rewind_DelegatesToStream_1654) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(flateEncoder.rewind());

}



TEST_F(FlateEncoderTest_1654, GetChar_DelegatesToStream_1654) {

    const int mockChar = 42;

    EXPECT_CALL(mockStream, getChar()).WillOnce(::testing::Return(mockChar));

    EXPECT_EQ(flateEncoder.getChar(), mockChar);

}



TEST_F(FlateEncoderTest_1654, LookChar_DelegatesToStream_1654) {

    const int mockChar = 42;

    EXPECT_CALL(mockStream, lookChar()).WillOnce(::testing::Return(mockChar));

    EXPECT_EQ(flateEncoder.lookChar(), mockChar);

}



TEST_F(FlateEncoderTest_1654, GetPSFilter_DelegatesToStream_1654) {

    const std::optional<std::string> mockResult = "mock filter";

    EXPECT_CALL(mockStream, getPSFilter(::testing::_, ::testing::_)).WillOnce(::testing::Return(mockResult));

    EXPECT_EQ(flateEncoder.getPSFilter(0, ""), mockResult);

}



TEST_F(FlateEncoderTest_1654, IsBinary_DelegatesToStream_1654) {

    const bool mockBinary = true;

    EXPECT_CALL(mockStream, isBinary(::testing::_)).WillOnce(::testing::Return(mockBinary));

    EXPECT_EQ(flateEncoder.isBinary(), mockBinary);

}



TEST_F(FlateEncoderTest_1654, GetKind_DelegatesToStream_1654) {

    const StreamKind mockKind = streamCCITTFax;

    EXPECT_CALL(mockStream, getKind()).WillOnce(::testing::Return(mockKind));

    EXPECT_EQ(flateEncoder.getKind(), mockKind);

}
