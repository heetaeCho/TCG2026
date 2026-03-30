#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <optional>



// Mocking Stream class to use as a dependency for RunLengthEncoder

class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char* indent), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const, override));

};



// Test fixture for RunLengthEncoder

class RunLengthEncoderTest_225 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<RunLengthEncoder> runLengthEncoder;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        runLengthEncoder = std::make_unique<RunLengthEncoder>(mockStream.get());

    }

};



// Test to verify isEncoder function returns true

TEST_F(RunLengthEncoderTest_225, IsEncoder_ReturnsTrue_225) {

    EXPECT_TRUE(runLengthEncoder->isEncoder());

}



// Test for rewind function

TEST_F(RunLengthEncoderTest_225, Rewind_DelegatesToStream_225) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(runLengthEncoder->rewind());



    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(runLengthEncoder->rewind());

}



// Test for getKind function

TEST_F(RunLengthEncoderTest_225, GetKind_DelegatesToStream_225) {

    StreamKind expectedKind = streamDCT;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(::testing::Return(expectedKind));

    EXPECT_EQ(runLengthEncoder->getKind(), expectedKind);

}



// Test for getChar function

TEST_F(RunLengthEncoderTest_225, GetChar_DelegatesToStream_225) {

    int expectedChar = 65;

    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(runLengthEncoder->getChar(), expectedChar);

}



// Test for lookChar function

TEST_F(RunLengthEncoderTest_225, LookChar_DelegatesToStream_225) {

    int expectedChar = 66;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(runLengthEncoder->lookChar(), expectedChar);

}



// Test for getPSFilter function

TEST_F(RunLengthEncoderTest_225, GetPSFilter_DelegatesToStream_225) {

    std::optional<std::string> expectedFilter = "filter";

    EXPECT_CALL(*mockStream, getPSFilter(1, "indent")).WillOnce(::testing::Return(expectedFilter));

    EXPECT_EQ(runLengthEncoder->getPSFilter(1, "indent"), expectedFilter);

}



// Test for isBinary function

TEST_F(RunLengthEncoderTest_225, IsBinary_DelegatesToStream_225) {

    EXPECT_CALL(*mockStream, isBinary(true)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(runLengthEncoder->isBinary(true));



    EXPECT_CALL(*mockStream, isBinary(false)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(runLengthEncoder->isBinary(false));

}
