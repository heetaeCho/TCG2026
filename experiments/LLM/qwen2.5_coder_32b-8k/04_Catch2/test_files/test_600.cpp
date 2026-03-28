#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_debug_console.cpp"

#include <sstream>



using namespace Catch;

using ::testing::HasSubstr;



class DebugConsoleTest_600 : public ::testing::Test {

protected:

    std::ostringstream catchCoutStream;

    void SetUp() override {

        // Redirect cout to a stringstream

        catchCoutStream.str("");

        Catch::cout().rdbuf(catchCoutStream.rdbuf());

    }



    void TearDown() override {

        // Restore original cout buffer

        Catch::cout().rdbuf(nullptr);

    }

};



TEST_F(DebugConsoleTest_600, WriteToDebugConsole_OutputMatchesInput_600) {

    std::string testString = "Hello, Debug Console!";

    writeToDebugConsole(testString);

    EXPECT_EQ(catchCoutStream.str(), testString);

}



TEST_F(DebugConsoleTest_600, WriteToDebugConsole_EmptyString_NoOutput_600) {

    std::string emptyString = "";

    writeToDebugConsole(emptyString);

    EXPECT_TRUE(catchCoutStream.str().empty());

}



TEST_F(DebugConsoleTest_600, WriteToDebugConsole_MultipleWrites_ConcatenatedOutput_600) {

    std::string firstString = "First line\n";

    std::string secondString = "Second line";

    writeToDebugConsole(firstString);

    writeToDebugConsole(secondString);

    EXPECT_EQ(catchCoutStream.str(), firstString + secondString);

}



TEST_F(DebugConsoleTest_600, WriteToDebugConsole_SpecialCharacters_OutputIncludesSpecialCharacters_600) {

    std::string specialChars = "Special chars: \t\n\r\\\"'";

    writeToDebugConsole(specialChars);

    EXPECT_EQ(catchCoutStream.str(), specialChars);

}
