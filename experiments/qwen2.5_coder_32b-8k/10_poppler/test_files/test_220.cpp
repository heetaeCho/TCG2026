#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Stream.h"



class RunLengthEncoderTest_220 : public ::testing::Test {

protected:

    Stream* mockStream;

    RunLengthEncoder* runLengthEncoder;



    void SetUp() override {

        mockStream = static_cast<Stream*>(::testing::internal::GetParam());

        runLengthEncoder = new RunLengthEncoder(mockStream);

    }



    void TearDown() override {

        delete runLengthEncoder;

    }

};



TEST_F(RunLengthEncoderTest_220, GetKind_ReturnsStrWeird_220) {

    EXPECT_EQ(runLengthEncoder->getKind(), strWeird);

}



TEST_F(RunLengthEncoderTest_220, Rewind_ReturnsTrue_220) {

    EXPECT_TRUE(runLengthEncoder->rewind());

}



TEST_F(RunLengthEncoderTest_220, GetChar_ReturnsExpectedValue_220) {

    // Assuming getChar() returns a specific value from the underlying stream

    int expectedChar = 42; // Example value

    // Mocking the behavior of the underlying stream's getChar() method if necessary

    EXPECT_EQ(runLengthEncoder->getChar(), expectedChar);

}



TEST_F(RunLengthEncoderTest_220, LookChar_ReturnsExpectedValue_220) {

    // Assuming lookChar() returns a specific value from the underlying stream without advancing the position

    int expectedChar = 42; // Example value

    // Mocking the behavior of the underlying stream's lookChar() method if necessary

    EXPECT_EQ(runLengthEncoder->lookChar(), expectedChar);

}



TEST_F(RunLengthEncoderTest_220, GetPSFilter_ReturnsEmptyOptional_220) {

    EXPECT_FALSE(runLengthEncoder->getPSFilter(1, "").has_value());

}



TEST_F(RunLengthEncoderTest_220, IsBinary_ReturnsTrue_220) {

    // Assuming isBinary() returns true for RunLengthEncoder

    EXPECT_TRUE(runLengthEncoder->isBinary(true));

}



TEST_F(RunLengthEncoderTest_220, IsEncoder_ReturnsTrue_220) {

    EXPECT_TRUE(runLengthEncoder->isEncoder());

}
