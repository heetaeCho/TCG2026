#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;



class StringRefTest_9 : public ::testing::Test {

protected:

    std::string testString = "Hello, World!";

    StringRef stringRef;

    

    void SetUp() override {

        stringRef = StringRef(testString);

    }

};



TEST_F(StringRefTest_9, Substr_ReturnsCorrectSubstring_NormalOperation_9) {

    StringRef subStr = stringRef.substr(0, 5);

    EXPECT_EQ(std::string(subStr.data(), subStr.size()), "Hello");

}



TEST_F(StringRefTest_9, Substr_ReturnsFullStringWhenStartIsZeroAndLengthIsGreaterThanOrEqualToSize_9) {

    StringRef subStr = stringRef.substr(0, testString.size() + 1);

    EXPECT_EQ(std::string(subStr.data(), subStr.size()), testString);

}



TEST_F(StringRefTest_9, Substr_ReturnsEmptyStringRefWhenStartIsGreaterThanSize_9) {

    StringRef subStr = stringRef.substr(testString.size() + 1, 5);

    EXPECT_TRUE(subStr.empty());

}



TEST_F(StringRefTest_9, Substr_ReturnsCorrectSubstring_WhenLengthExceedsAvailableCharacters_9) {

    StringRef subStr = stringRef.substr(7, 20);

    EXPECT_EQ(std::string(subStr.data(), subStr.size()), "World!");

}



TEST_F(StringRefTest_9, Empty_ReturnsTrueForDefaultConstructedStringRef_9) {

    StringRef emptyString;

    EXPECT_TRUE(emptyString.empty());

}



TEST_F(StringRefTest_9, Size_ReturnsCorrectSize_9) {

    EXPECT_EQ(stringRef.size(), testString.size());

}



TEST_F(StringRefTest_9, Data_ReturnsPointerToUnderlyingData_9) {

    EXPECT_EQ(std::string(stringRef.data()), testString);

}



TEST_F(StringRefTest_9, OperatorLessThan_ReturnsTrueWhenLhsIsLexicographicallySmaller_9) {

    StringRef smallerString("Hello");

    EXPECT_TRUE(smallerString < stringRef);

}



TEST_F(StringRefTest_9, Compare_ReturnsNegativeWhenLhsIsLexicographicallySmaller_9) {

    StringRef smallerString("Hello");

    EXPECT_LT(smallerString.compare(stringRef), 0);

}



TEST_F(StringRefTest_9, OperatorEqual_ReturnsTrueForIdenticalStrings_9) {

    StringRef sameString(testString);

    EXPECT_TRUE(sameString == stringRef);

}



TEST_F(StringRefTest_9, OperatorNotEqual_ReturnsFalseForIdenticalStrings_9) {

    StringRef sameString(testString);

    EXPECT_FALSE(sameString != stringRef);

}



TEST_F(StringRefTest_9, OperatorPlus_ConcatenatesTwoStringRefObjects_9) {

    StringRef anotherString("!");

    StringRef result = stringRef + anotherString;

    EXPECT_EQ(std::string(result.data(), result.size()), "Hello, World!!!");

}
