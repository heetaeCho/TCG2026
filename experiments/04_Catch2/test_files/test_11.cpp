#include <gtest/gtest.h>

#include <Catch2/internal/catch_stringref.hpp>

#include <string>



class StringRefTest_11 : public ::testing::Test {

protected:

    Catch::StringRef emptyString;

    Catch::StringRef singleCharString;

    Catch::StringRef multiCharString;



    void SetUp() override {

        emptyString = Catch::StringRef();

        singleCharString = Catch::StringRef("A");

        multiCharString = Catch::StringRef("Hello, World!");

    }

};



TEST_F(StringRefTest_11, EmptyConstructorCreatesEmptyString_11) {

    EXPECT_TRUE(emptyString.empty());

    EXPECT_EQ(emptyString.size(), 0);

}



TEST_F(StringRefTest_11, CharPtrConstructorSetsCorrectValues_11) {

    const char* testStr = "Hello";

    Catch::StringRef str(testStr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), strlen(testStr));

    EXPECT_STREQ(str.data(), testStr);

}



TEST_F(StringRefTest_11, StdStringConstructorSetsCorrectValues_11) {

    std::string testStr = "Hello";

    Catch::StringRef str(testStr);

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.size(), testStr.size());

    EXPECT_STREQ(str.data(), testStr.c_str());

}



TEST_F(StringRefTest_11, SubstrReturnsCorrectSubstring_11) {

    auto substr = multiCharString.substr(0, 5);

    EXPECT_EQ(substr, "Hello");

    EXPECT_EQ(substr.size(), 5);



    auto fullsubstr = multiCharString.substr(0, multiCharString.size());

    EXPECT_EQ(fullsubstr, multiCharString);

    EXPECT_EQ(fullsubstr.size(), multiCharString.size());



    auto endsubstr = multiCharString.substr(multiCharString.size() - 1, 1);

    EXPECT_EQ(endsubstr, "!");

    EXPECT_EQ(endsubstr.size(), 1);

}



TEST_F(StringRefTest_11, SubstrHandlesBoundaryConditions_11) {

    auto emptySubstr = multiCharString.substr(multiCharString.size(), 10);

    EXPECT_TRUE(emptySubstr.empty());

    EXPECT_EQ(emptySubstr.size(), 0);



    auto fullSizeSubstr = multiCharString.substr(7, multiCharString.size() - 7);

    EXPECT_EQ(fullSizeSubstr, "World!");

}



TEST_F(StringRefTest_11, CompareFunctionWorksCorrectly_11) {

    Catch::StringRef sameStr("Hello, World!");

    Catch::StringRef smallerStr("Hello");

    Catch::StringRef largerStr("Hello, Universe!");



    EXPECT_EQ(multiCharString.compare(sameStr), 0);

    EXPECT_GT(multiCharString.compare(smallerStr), 0);

    EXPECT_LT(multiCharString.compare(largerStr), 0);

}



TEST_F(StringRefTest_11, EqualityOperatorWorksCorrectly_11) {

    Catch::StringRef sameStr("Hello, World!");

    Catch::StringRef differentStr("Goodbye!");



    EXPECT_TRUE(multiCharString == sameStr);

    EXPECT_FALSE(multiCharString == differentStr);

}



TEST_F(StringRefTest_11, InequalityOperatorWorksCorrectly_11) {

    Catch::StringRef sameStr("Hello, World!");

    Catch::StringRef differentStr("Goodbye!");



    EXPECT_FALSE(multiCharString != sameStr);

    EXPECT_TRUE(multiCharString != differentStr);

}



TEST_F(StringRefTest_11, LessThanOperatorWorksCorrectly_11) {

    Catch::StringRef smallerStr("Hello");

    Catch::StringRef largerStr("Hello, Universe!");



    EXPECT_TRUE(multiCharString < largerStr);

    EXPECT_FALSE(multiCharString < smallerStr);

}



TEST_F(StringRefTest_11, ArrayOperatorReturnsCorrectCharacter_11) {

    EXPECT_EQ(singleCharString[0], 'A');

    EXPECT_EQ(multiCharString[0], 'H');

    EXPECT_EQ(multiCharString[multiCharString.size() - 1], '!');

}



TEST_F(StringRefTest_11, ConversionToStdStringWorksCorrectly_11) {

    std::string str = static_cast<std::string>(multiCharString);

    EXPECT_EQ(str, "Hello, World!");

}
