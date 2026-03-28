#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_stringref.hpp"



using namespace Catch;



class StringRefTest_684 : public ::testing::Test {

protected:

    StringRef emptyStringRef;

    StringRef nonEmptyStringRef1;

    StringRef nonEmptyStringRef2;



    void SetUp() override {

        emptyStringRef = StringRef();

        nonEmptyStringRef1 = StringRef("Hello");

        nonEmptyStringRef2 = StringRef("World");

    }

};



TEST_F(StringRefTest_684, EmptyStringReturnsCorrectSize_684) {

    EXPECT_EQ(emptyStringRef.size(), 0);

}



TEST_F(StringRefTest_684, NonEmptyStringReturnsCorrectSize_684) {

    EXPECT_EQ(nonEmptyStringRef1.size(), 5);

}



TEST_F(StringRefTest_684, EmptyStringIsEmptyCheck_684) {

    EXPECT_TRUE(emptyStringRef.empty());

}



TEST_F(StringRefTest_684, NonEmptyStringIsEmptyCheck_684) {

    EXPECT_FALSE(nonEmptyStringRef1.empty());

}



TEST_F(StringRefTest_684, StringEqualityOperatorTrue_684) {

    StringRef anotherHello("Hello");

    EXPECT_TRUE(nonEmptyStringRef1 == anotherHello);

}



TEST_F(StringRefTest_684, StringEqualityOperatorFalse_684) {

    EXPECT_FALSE(nonEmptyStringRef1 == nonEmptyStringRef2);

}



TEST_F(StringRefTest_684, StringInequalityOperatorTrue_684) {

    EXPECT_TRUE(nonEmptyStringRef1 != nonEmptyStringRef2);

}



TEST_F(StringRefTest_684, StringInequalityOperatorFalse_684) {

    StringRef anotherHello("Hello");

    EXPECT_FALSE(nonEmptyStringRef1 != anotherHello);

}



TEST_F(StringRefTest_684, StringConcatenationOperator_684) {

    std::string result = nonEmptyStringRef1 + nonEmptyStringRef2;

    EXPECT_EQ(result, "HelloWorld");

}



TEST_F(StringRefTest_684, SubstrOnNonEmptyString_684) {

    auto substrResult = nonEmptyStringRef1.substr(1, 3);

    StringRef expected("ell");

    EXPECT_TRUE(substrResult == expected);

}



TEST_F(StringRefTest_684, SubstrWithZeroLength_684) {

    auto substrResult = nonEmptyStringRef1.substr(2, 0);

    StringRef expected("");

    EXPECT_TRUE(substrResult == expected);

}



TEST_F(StringRefTest_684, CompareOperatorEqualStrings_684) {

    StringRef anotherHello("Hello");

    EXPECT_EQ(nonEmptyStringRef1.compare(anotherHello), 0);

}



TEST_F(StringRefTest_684, CompareOperatorFirstStringLess_684) {

    EXPECT_LT(nonEmptyStringRef1.compare(nonEmptyStringRef2), 0);

}



TEST_F(StringRefTest_684, CompareOperatorSecondStringLess_684) {

    EXPECT_GT(nonEmptyStringRef2.compare(nonEmptyStringRef1), 0);

}



TEST_F(StringRefTest_684, LessThanOperatorTrue_684) {

    EXPECT_TRUE(nonEmptyStringRef1 < nonEmptyStringRef2);

}



TEST_F(StringRefTest_684, LessThanOperatorFalse_684) {

    EXPECT_FALSE(nonEmptyStringRef2 < nonEmptyStringRef1);

}



TEST_F(StringRefTest_684, OperatorStreamInsertionNonEmptyString_684) {

    std::ostringstream oss;

    oss << nonEmptyStringRef1;

    EXPECT_EQ(oss.str(), "Hello");

}



TEST_F(StringRefTest_684, OperatorStreamInsertionEmptyString_684) {

    std::ostringstream oss;

    oss << emptyStringRef;

    EXPECT_EQ(oss.str(), "");

}



TEST_F(StringRefTest_684, ConversionToStdStringNonEmptyString_684) {

    std::string result = static_cast<std::string>(nonEmptyStringRef1);

    EXPECT_EQ(result, "Hello");

}



TEST_F(StringRefTest_684, ConversionToStdStringEmptyString_684) {

    std::string result = static_cast<std::string>(emptyStringRef);

    EXPECT_EQ(result, "");

}
