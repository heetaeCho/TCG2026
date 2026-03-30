#include <gtest/gtest.h>

#include "UTF.h"



// Test fixture for UTF tests with TEST_ID 1280

class UTFTest_1280 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(UTFTest_1280, HasUnicodeByteOrderMarkAndLengthIsEven_ReturnsTrueForValidInput_1280) {

    std::string validInput = "\xFE\xFFabcde";

    validInput += 'f'; // Make the length even

    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(validInput));

}



TEST_F(UTFTest_1280, HasUnicodeByteOrderMarkAndLengthIsEven_ReturnsFalseForOddLength_1280) {

    std::string oddLengthInput = "\xFE\xFFabcde";

    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(oddLengthInput));

}



TEST_F(UTFTest_1280, HasUnicodeByteOrderMarkAndLengthIsEven_ReturnsFalseForMissingBOM_1280) {

    std::string missingBOMInput = "abcde";

    missingBOMInput += 'f'; // Make the length even

    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(missingBOMInput));

}



TEST_F(UTFTest_1280, HasUnicodeByteOrderMarkAndLengthIsEven_ReturnsFalseForEmptyString_1280) {

    std::string emptyInput = "";

    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(emptyInput));

}



TEST_F(UTFTest_1280, HasUnicodeByteOrderMarkAndLengthIsEven_ReturnsTrueForOnlyBOMWithEvenLength_1280) {

    std::string onlyBOMInput = "\xFE\xFF";

    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(onlyBOMInput));

}



TEST_F(UTFTest_1280, HasUnicodeByteOrderMarkAndLengthIsEven_ReturnsFalseForOnlyBOMWithOddLength_1280) {

    std::string onlyBOMInput = "\xFE";

    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(onlyBOMInput));

}
