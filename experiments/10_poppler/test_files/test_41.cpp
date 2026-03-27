#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>

#include <cstring>



extern "C" {

    char *getLine(char *buf, int size, FILE *f);

}



class GetLineTest_41 : public ::testing::Test {

protected:

    FILE* tempFile;



    void SetUp() override {

        // Create a temporary file and open it for reading and writing

        tempFile = tmpfile();

        if (!tempFile) {

            FAIL() << "Failed to create temporary file";

        }

    }



    void TearDown() override {

        fclose(tempFile);

    }



    void writeToFile(const std::string& content) {

        rewind(tempFile);

        fputs(content.c_str(), tempFile);

        rewind(tempFile);

    }

};



TEST_F(GetLineTest_41, NormalOperation_41) {

    char buffer[10];

    writeToFile("Hello\nWorld");

    EXPECT_STREQ(getLine(buffer, sizeof(buffer), tempFile), "Hello");

}



TEST_F(GetLineTest_41, CarriageReturnNewlineHandling_41) {

    char buffer[10];

    writeToFile("Hello\r\nWorld");

    EXPECT_STREQ(getLine(buffer, sizeof(buffer), tempFile), "Hello\r");

}



TEST_F(GetLineTest_41, SingleCharacterLine_41) {

    char buffer[10];

    writeToFile("A\nBCD");

    EXPECT_STREQ(getLine(buffer, sizeof(buffer), tempFile), "A");

}



TEST_F(GetLineTest_41, EmptyLineHandling_41) {

    char buffer[10];

    writeToFile("\nHello");

    EXPECT_STREQ(getLine(buffer, sizeof(buffer), tempFile), "");

}



TEST_F(GetLineTest_41, EndOfFileHandling_41) {

    char buffer[10];

    writeToFile("");

    EXPECT_EQ(getLine(buffer, sizeof(buffer), tempFile), nullptr);

}



TEST_F(GetLineTest_41, LineLongerThanBuffer_41) {

    char buffer[6];

    writeToFile("HelloWorld\n");

    EXPECT_STREQ(getLine(buffer, sizeof(buffer), tempFile), "Hello");

}



TEST_F(GetLineTest_41, BufferSizeOne_41) {

    char buffer[1];

    writeToFile("A\nBCD");

    EXPECT_EQ(getLine(buffer, sizeof(buffer), tempFile), nullptr);

}
