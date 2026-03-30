#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <memory>



using namespace ::testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (const, override));

    MOCK_METHOD(const bool, isBinary, (bool last), (const, override));

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

};



class RunLengthStreamTest_186 : public ::testing::Test {

protected:

    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        runLengthStream = std::make_unique<RunLengthStream>(std::move(mockStream));

    }



    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<RunLengthStream> runLengthStream;

};



TEST_F(RunLengthStreamTest_186, LookChar_ReturnsEOF_WhenBufferIsEmptyAndFillBufFails_186) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(EOF));

    int result = runLengthStream->lookChar();

    EXPECT_EQ(result, EOF);

}



TEST_F(RunLengthStreamTest_186, LookChar_ReturnsFirstCharacter_WhenBufferHasData_186) {

    unsigned char buffer[2] = { 'A', 0 };

    EXPECT_CALL(*mockStream, getChars(1, _))

        .WillOnce([&](int nChars, unsigned char* buffer){

            memcpy(buffer, &buffer[0], nChars);

            return true;

        });

    int result = runLengthStream->lookChar();

    EXPECT_EQ(result, 'A');

}



TEST_F(RunLengthStreamTest_186, LookChar_ReturnsSameCharacterOnSubsequentCalls_WhenBufferHasData_186) {

    unsigned char buffer[2] = { 'B', 0 };

    EXPECT_CALL(*mockStream, getChars(1, _))

        .WillOnce([&](int nChars, unsigned char* buffer){

            memcpy(buffer, &buffer[0], nChars);

            return true;

        });

    int firstResult = runLengthStream->lookChar();

    int secondResult = runLengthStream->lookChar();

    EXPECT_EQ(firstResult, 'B');

    EXPECT_EQ(secondResult, 'B');

}



TEST_F(RunLengthStreamTest_186, LookChar_ReturnsEOF_AfterExhaustingBufferAndFillBufFails_186) {

    unsigned char buffer[2] = { 'C', 0 };

    EXPECT_CALL(*mockStream, getChars(1, _))

        .WillOnce([&](int nChars, unsigned char* buffer){

            memcpy(buffer, &buffer[0], nChars);

            return true;

        })

        .WillOnce(Return(false));

    runLengthStream->lookChar();  // Consume the first character

    int result = runLengthStream->lookChar();

    EXPECT_EQ(result, EOF);

}
