#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <optional>



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(bool, isEncoder, (), (const, override));

};



class RunLengthEncoderTest_222 : public ::testing::Test {

protected:

    MockStream mockStream;

    RunLengthEncoder runLengthEncoder;



    RunLengthEncoderTest_222() : runLengthEncoder(&mockStream) {}

};



TEST_F(RunLengthEncoderTest_222, LookChar_ReturnsEOFWhenBufferEmptyAndFillBufFails_222) {

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(EOF));

    EXPECT_EQ(runLengthEncoder.lookChar(), EOF);

}



TEST_F(RunLengthEncoderTest_222, LookChar_ReturnsCurrentCharacterWhenBufferNotEmpty_222) {

    char testChar = 'A';

    EXPECT_CALL(mockStream, getChar()).WillOnce(Return(testChar));

    runLengthEncoder.getChar(); // To fill the buffer

    EXPECT_EQ(runLengthEncoder.lookChar(), testChar);

}



TEST_F(RunLengthEncoderTest_222, Rewind_ReturnsTrueAndResetsBuffer_222) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(runLengthEncoder.rewind());

}



TEST_F(RunLengthEncoderTest_222, GetKind_ForwardsToMockStream_222) {

    StreamKind expectedKind = streamKindRaw;

    EXPECT_CALL(mockStream, getKind()).WillOnce(Return(expectedKind));

    EXPECT_EQ(runLengthEncoder.getKind(), expectedKind);

}



TEST_F(RunLengthEncoderTest_222, GetPSFilter_ForwardsToMockStream_222) {

    int psLevel = 1;

    const char* indent = "  ";

    std::optional<std::string> expectedResult = "filter";

    EXPECT_CALL(mockStream, getPSFilter(psLevel, indent)).WillOnce(Return(expectedResult));

    EXPECT_EQ(runLengthEncoder.getPSFilter(psLevel, indent), expectedResult);

}



TEST_F(RunLengthEncoderTest_222, IsBinary_ForwardsToMockStream_222) {

    bool last = true;

    EXPECT_CALL(mockStream, isBinary(last)).WillOnce(Return(true));

    EXPECT_TRUE(runLengthEncoder.isBinary(last));

}



TEST_F(RunLengthEncoderTest_222, IsEncoder_ReturnsTrue_222) {

    EXPECT_TRUE(runLengthEncoder.isEncoder());

}
