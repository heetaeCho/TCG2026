#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <memory>

#include "Stream.h"



using namespace testing;



class RunLengthStreamTest_184 : public Test {

protected:

    std::unique_ptr<Stream> mockStream;

    std::unique_ptr<RunLengthStream> runLengthStream;



    void SetUp() override {

        mockStream = std::make_unique<NiceMock<StrictMock<Stream>>>();

        runLengthStream = std::make_unique<RunLengthStream>(std::move(mockStream));

    }

};



TEST_F(RunLengthStreamTest_184, GetKind_ReturnsCorrectValue_184) {

    EXPECT_EQ(runLengthStream->getKind(), strRunLength);

}



TEST_F(RunLengthStreamTest_184, Rewind_CallsBaseRewind_184) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(runLengthStream->rewind());

}



TEST_F(RunLengthStreamTest_184, GetPSFilter_ForwardsToBase_184) {

    const int psLevel = 1;

    const char* indent = " ";

    std::optional<std::string> expected = "filter";

    

    EXPECT_CALL(*mockStream, getPSFilter(psLevel, indent)).WillOnce(Return(expected));

    EXPECT_EQ(runLengthStream->getPSFilter(psLevel, indent), expected);

}



TEST_F(RunLengthStreamTest_184, IsBinary_ForwardsToBase_184) {

    bool last = true;

    bool expectedResult = true;

    

    EXPECT_CALL(*mockStream, isBinary(last)).WillOnce(Return(expectedResult));

    EXPECT_EQ(runLengthStream->isBinary(last), expectedResult);

}



TEST_F(RunLengthStreamTest_184, GetChar_ForwardsToBase_184) {

    int expectedResult = 10;

    

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(expectedResult));

    EXPECT_EQ(runLengthStream->getChar(), expectedResult);

}



TEST_F(RunLengthStreamTest_184, LookChar_ForwardsToBase_184) {

    int expectedResult = 20;

    

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(expectedResult));

    EXPECT_EQ(runLengthStream->lookChar(), expectedResult);

}
