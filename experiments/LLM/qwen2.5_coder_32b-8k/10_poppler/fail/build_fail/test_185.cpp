#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <memory>



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (const, override));

    MOCK_METHOD(const bool, isBinary, (bool last), (const, override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

};



class RunLengthStreamTest_185 : public Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<RunLengthStream> runLengthStream;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        runLengthStream = std::make_unique<RunLengthStream>(std::move(mockStream));

    }

};



TEST_F(RunLengthStreamTest_185, Rewind_ReturnsTrue_185) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(runLengthStream->rewind());

}



TEST_F(RunLengthStreamTest_185, GetPSFilter_ReturnsEmptyOptional_185) {

    EXPECT_CALL(*mockStream, getPSFilter(_, _)).WillOnce(Return(std::optional<std::string>()));

    auto result = runLengthStream->getPSFilter(0, "");

    EXPECT_FALSE(result.has_value());

}



TEST_F(RunLengthStreamTest_185, IsBinary_ReturnsFalse_185) {

    EXPECT_CALL(*mockStream, isBinary(_)).WillOnce(Return(false));

    EXPECT_FALSE(runLengthStream->isBinary(true));

}



TEST_F(RunLengthStreamTest_185, LookChar_ReturnsEOF_185) {

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(EOF));

    EXPECT_EQ(runLengthStream->lookChar(), EOF);

}



TEST_F(RunLengthStreamTest_185, GetKind_ReturnsExpectedValue_185) {

    StreamKind expectedKind = streamKind::type1;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(Return(expectedKind));

    EXPECT_EQ(runLengthStream->getKind(), expectedKind);

}



TEST_F(RunLengthStreamTest_185, GetChar_ReturnsEOF_WhenBufferIsEmptyAndFillBufFails_185) {

    EXPECT_CALL(*mockStream, lookChar()).WillRepeatedly(Return(0)); // Simulate no data in buffer

    EXPECT_CALL(*mockStream, getChars(_, _)).WillOnce(Return(false)); // Simulate fillBuf failure

    EXPECT_EQ(runLengthStream->getChar(), EOF);

}



TEST_F(RunLengthStreamTest_185, GetChar_ReturnsValidCharacter_WhenBufferHasData_185) {

    EXPECT_CALL(*mockStream, lookChar()).WillRepeatedly(Return(0)); // Simulate no data in buffer

    EXPECT_CALL(*mockStream, getChars(_, _)).WillOnce([](int nChars, unsigned char * buffer) -> bool {

        buffer[0] = 'A';

        return true;

    }); // Simulate fillBuf success

    EXPECT_EQ(runLengthStream->getChar(), 'A');

}



TEST_F(RunLengthStreamTest_185, GetChar_ReturnsEOF_AfterBufferExhaustionAndFillBufFails_185) {

    EXPECT_CALL(*mockStream, lookChar()).WillRepeatedly(Return(0)); // Simulate no data in buffer

    EXPECT_CALL(*mockStream, getChars(_, _)).WillOnce([](int nChars, unsigned char * buffer) -> bool {

        buffer[0] = 'A';

        return true;

    }).WillOnce(Return(false)); // Simulate fillBuf success then failure



    EXPECT_EQ(runLengthStream->getChar(), 'A');

    EXPECT_EQ(runLengthStream->getChar(), EOF);

}
