#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



// Assuming the function PrintJSONString is declared in a header file named json.h

#include "json.h"

#include <cstdio>



using ::testing::_;

using ::testing::StrEq;



class PrintJSONStringTest_116 : public ::testing::Test {

protected:

    void SetUp() override {

        // Redirect stdout to capture the output of PrintJSONString

        testing::internal::CaptureStdout();

    }



    void TearDown() override {

        // Stop capturing stdout

        capturedOutput = testing::internal::GetCapturedStdout();

    }



    std::string capturedOutput;

};



TEST_F(PrintJSONStringTest_116, NormalOperation_116) {

    PrintJSONString("Hello, World!");

    EXPECT_EQ(capturedOutput, "\"Hello, World!\"");

}



TEST_F(PrintJSONStringTest_116, EmptyString_116) {

    PrintJSONString("");

    EXPECT_EQ(capturedOutput, "\"\"");

}



TEST_F(PrintJSONStringTest_116, StringWithQuotes_116) {

    PrintJSONString("Hello \"World\"!");

    EXPECT_EQ(capturedOutput, "\"Hello \\\"World\\\"!\"");

}



TEST_F(PrintJSONStringTest_116, StringWithBackslash_116) {

    PrintJSONString("C:\\path\\to\\file");

    EXPECT_EQ(capturedOutput, "\"C:\\\\path\\\\to\\\\file\"");

}



TEST_F(PrintJSONStringTest_116, StringWithSpecialCharacters_116) {

    PrintJSONString("\b\f\n\r\t");

    EXPECT_EQ(capturedOutput, "\"\\b\\f\\n\\r\\t\"");

}
