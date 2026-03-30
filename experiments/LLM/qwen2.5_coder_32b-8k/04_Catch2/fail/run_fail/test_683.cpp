#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_stringref.hpp"

#include <string>

#include <sstream>



using namespace Catch;



class StringRefTest_683 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    static constexpr const char* testString = "Hello, World!";

};



TEST_F(StringRefTest_683, ConstructorFromCString_683) {

    StringRef str(testString);

    EXPECT_EQ(str.data(), testString);

    EXPECT_EQ(str.size(), strlen(testString));

}



TEST_F(StringRefTest_683, ConstructorFromStdString_683) {

    std::string testStdString = "Hello, World!";

    StringRef str(testStdString);

    EXPECT_EQ(str.data(), testStdString.c_str());

    EXPECT_EQ(str.size(), testStdString.size());

}



TEST_F(StringRefTest_683, DefaultConstructor_683) {

    StringRef str;

    EXPECT_TRUE(str.empty());

    EXPECT_EQ(str.size(), 0);

}



TEST_F(StringRefTest_683, EmptyCheck_683) {

    StringRef emptyStr("");

    EXPECT_TRUE(emptyStr.empty());



    StringRef nonEmptyStr(testString);

    EXPECT_FALSE(nonEmptyStr.empty());

}



TEST_F(StringRefTest_683, SizeCheck_683) {

    StringRef str(testString);

    EXPECT_EQ(str.size(), strlen(testString));

}



TEST_F(StringRefTest_683, DataAccess_683) {

    StringRef str(testString);

    EXPECT_STREQ(str.data(), testString);

}



TEST_F(StringRefTest_683, SubstrNormalOperation_683) {

    StringRef str(testString);

    StringRef substr = str.substr(0, 5);

    EXPECT_EQ(substr, "Hello");

}



TEST_F(StringRefTest_683, SubstrBoundaryConditions_683) {

    StringRef str(testString);



    // Empty substring

    StringRef emptySubstr = str.substr(0, 0);

    EXPECT_TRUE(emptySubstr.empty());



    // Full string as a substring

    StringRef fullSubstr = str.substr(0, str.size());

    EXPECT_EQ(fullSubstr, testString);



    // Substring from middle to end

    StringRef middleEndSubstr = str.substr(7, 5);

    EXPECT_EQ(middleEndSubstr, "World");

}



TEST_F(StringRefTest_683, OperatorLessThan_683) {

    StringRef str1("abc");

    StringRef str2("def");



    EXPECT_TRUE(str1 < str2);

    EXPECT_FALSE(str2 < str1);



    // Equal strings

    StringRef str3("ghi");

    StringRef str4("ghi");



    EXPECT_FALSE(str3 < str4);

}



TEST_F(StringRefTest_683, OperatorEqual_683) {

    StringRef str1("test");

    StringRef str2("test");

    StringRef str3("different");



    EXPECT_TRUE(str1 == str2);

    EXPECT_FALSE(str1 == str3);

}



TEST_F(StringRefTest_683, OperatorNotEqual_683) {

    StringRef str1("example");

    StringRef str2("sample");

    StringRef str3("example");



    EXPECT_TRUE(str1 != str2);

    EXPECT_FALSE(str1 != str3);

}



TEST_F(StringRefTest_683, IndexOperatorNormalOperation_683) {

    StringRef str(testString);



    for (size_t i = 0; i < str.size(); ++i) {

        EXPECT_EQ(str[i], testString[i]);

    }

}



TEST_F(StringRefTest_683, IndexOperatorBoundaryConditions_683) {

    StringRef str(testString);

    // First character

    EXPECT_EQ(str[0], 'H');

    

    // Last character

    EXPECT_EQ(str[str.size() - 1], '!');



    // Empty string case

    StringRef emptyStr;

    EXPECT_THROW(emptyStr[0], std::out_of_range); // Assuming out_of_range exception for invalid access

}



TEST_F(StringRefTest_683, CompareNormalOperation_683) {

    StringRef str1("abc");

    StringRef str2("def");



    EXPECT_LT(str1.compare(str2), 0);

    EXPECT_GT(str2.compare(str1), 0);



    // Equal strings

    StringRef str3("ghi");

    StringRef str4("ghi");



    EXPECT_EQ(str3.compare(str4), 0);

}



TEST_F(StringRefTest_683, ConversionToStdString_683) {

    StringRef str(testString);

    std::string convertedStr = static_cast<std::string>(str);



    EXPECT_EQ(convertedStr, testString);

}



TEST_F(StringRefTest_683, OperatorPlusNormalOperation_683) {

    StringRef str1("Hello");

    StringRef str2(", World!");



    StringRef result = str1 + str2;

    EXPECT_EQ(result, "Hello, World!");

}



TEST_F(StringRefTest_683, OperatorPlusEmptyString_683) {

    StringRef str1("Hello");

    StringRef str2("");



    StringRef result = str1 + str2;

    EXPECT_EQ(result, "Hello");



    result = str2 + str1;

    EXPECT_EQ(result, "Hello");

}



TEST_F(StringRefTest_683, OutputStreamOperator_683) {

    StringRef str(testString);

    std::ostringstream oss;



    oss << str;

    EXPECT_EQ(oss.str(), testString);

}
