#include <gtest/gtest.h>

#include "UTF.h"



class UTFTest_1024 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(UTFTest_1024, ValidUnicodeByteOrderMarkAndEvenLength_1024) {

    std::string_view testString = "\376\377aa";

    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(testString));

}



TEST_F(UTFTest_1024, ValidUnicodeByteOrderMarkButOddLength_1024) {

    std::string_view testString = "\376\377a";

    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(testString));

}



TEST_F(UTFTest_1024, InvalidUnicodeByteOrderMarkButEvenLength_1024) {

    std::string_view testString = "feffaa"; // Incorrect BOM

    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(testString));

}



TEST_F(UTFTest_1024, EmptyString_1024) {

    std::string_view testString = "";

    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(testString));

}



TEST_F(UTFTest_1024, OnlyUnicodeByteOrderMark_1024) {

    std::string_view testString = "\376\377";

    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(testString)); // Length is 2 but no additional characters

}



TEST_F(UTFTest_1024, LongerStringWithCorrectBOMAndEvenLength_1024) {

    std::string_view testString = "\376\377abcdefgh"; // Length is 12 (even), correct BOM

    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(testString));

}
