#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependency Stream

class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(bool, isEncoder, () const, (override));

};



class RunLengthEncoderTest_221 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<RunLengthEncoder> runLengthEncoder;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        runLengthEncoder = std::make_unique<RunLengthEncoder>(mockStream.get());

    }

};



TEST_F(RunLengthEncoderTest_221, GetCharReturnsEOFWhenBufferIsEmptyAndFillBufFails_221) {

    EXPECT_CALL(*mockStream, getChar()).WillRepeatedly(::testing::Return(EOF));

    EXPECT_EQ(runLengthEncoder->getChar(), EOF);

}



TEST_F(RunLengthEncoderTest_221, GetCharReturnsValidCharacterWhenBufferIsNotEmpty_221) {

    const int expectedChar = 42;

    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(runLengthEncoder->getChar(), (expectedChar & 0xff));

}



TEST_F(RunLengthEncoderTest_221, RewindCallsRewindOnUnderlyingStream_221) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(runLengthEncoder->rewind());

}



TEST_F(RunLengthEncoderTest_221, GetKindReturnsFilterStreamKind_221) {

    StreamKind expectedKind = filterStream;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(::testing::Return(expectedKind));

    EXPECT_EQ(runLengthEncoder->getKind(), expectedKind);

}



TEST_F(RunLengthEncoderTest_221, LookCharCallsLookCharOnUnderlyingStream_221) {

    const int expectedChar = 42;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(::testing::Return(expectedChar));

    EXPECT_EQ(runLengthEncoder->lookChar(), (expectedChar & 0xff));

}



TEST_F(RunLengthEncoderTest_221, GetPSFilterCallsGetPSFilterOnUnderlyingStream_221) {

    int psLevel = 3;

    const char* indent = "indent";

    std::optional<std::string> expectedFilter = "filterString";

    EXPECT_CALL(*mockStream, getPSFilter(psLevel, indent)).WillOnce(::testing::Return(expectedFilter));

    EXPECT_EQ(runLengthEncoder->getPSFilter(psLevel, indent), expectedFilter);

}



TEST_F(RunLengthEncoderTest_221, IsBinaryCallsIsBinaryOnUnderlyingStream_221) {

    bool last = true;

    EXPECT_CALL(*mockStream, isBinary(last)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(runLengthEncoder->isBinary(last));

}



TEST_F(RunLengthEncoderTest_221, IsEncoderReturnsTrue_221) {

    EXPECT_TRUE(runLengthEncoder->isEncoder());

}
