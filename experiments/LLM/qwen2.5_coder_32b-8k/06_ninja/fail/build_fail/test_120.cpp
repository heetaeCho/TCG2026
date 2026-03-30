#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern void RandomCommand(char** s);



namespace {



class RandomCommandTest_120 : public ::testing::Test {

protected:

    char* generatedString;



    virtual void SetUp() override {

        generatedString = nullptr;

    }



    virtual void TearDown() override {

        delete[] generatedString;

    }

};



TEST_F(RandomCommandTest_120, GeneratesNonNullString_120) {

    RandomCommand(&generatedString);

    EXPECT_NE(generatedString, nullptr);

}



TEST_F(RandomCommandTest_120, StringLengthInRange_120) {

    RandomCommand(&generatedString);

    int len = strlen(generatedString);

    EXPECT_GE(len, 5);

    EXPECT_LE(len, 100);

}



TEST_F(RandomCommandTest_120, StringIsProperlyNullTerminated_120) {

    RandomCommand(&generatedString);

    int len = strlen(generatedString);

    EXPECT_EQ(generatedString[len], '\0');

}



TEST_F(RandomCommandTest_120, StringContainsPrintableCharactersOnly_120) {

    RandomCommand(&generatedString);

    for (int i = 0; generatedString[i] != '\0'; ++i) {

        EXPECT_GE(static_cast<unsigned char>(generatedString[i]), 32);

        EXPECT_LE(static_cast<unsigned char>(generatedString[i]), 127);

    }

}



} // namespace
