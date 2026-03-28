#include <gtest/gtest.h>

#include "stringsource.h"



using namespace YAML;



class StringCharSourceTest_106 : public ::testing::Test {

protected:

    const char* testString = "Hello, World!";

    std::size_t testSize = 13;

    StringCharSource source;



    void SetUp() override {

        source = StringCharSource(testString, testSize);

    }

};



TEST_F(StringCharSourceTest_106, OperatorBool_ReturnsTrueForNonEmptyString_106) {

    EXPECT_TRUE(static_cast<bool>(source));

}



TEST_F(StringCharSourceTest_106, OperatorBool_ReturnsFalseWhenOffsetExceedsSize_106) {

    for (std::size_t i = 0; i < testSize; ++i) {

        ++source;

    }

    EXPECT_FALSE(static_cast<bool>(source));

}



TEST_F(StringCharSourceTest_106, OperatorIndex_ReturnsCorrectCharacter_106) {

    for (std::size_t i = 0; i < testSize; ++i) {

        EXPECT_EQ(source[i], testString[i]);

    }

}



TEST_F(StringCharSourceTest_106, OperatorExclamation_ReturnsFalseForNonEmptyString_106) {

    EXPECT_FALSE(!source);

}



TEST_F(StringCharSourceTest_106, OperatorExclamation_ReturnsTrueWhenOffsetExceedsSize_106) {

    for (std::size_t i = 0; i < testSize; ++i) {

        ++source;

    }

    EXPECT_TRUE(!source);

}



TEST_F(StringCharSourceTest_106, OperatorIncrement_IncrementsOffsetCorrectly_106) {

    char expectedChar = 'H';

    for (std::size_t i = 0; i < testSize; ++i) {

        EXPECT_EQ(source[i], expectedChar);

        ++source;

        if (i + 1 < testSize) {

            expectedChar = testString[i + 1];

        }

    }

}



TEST_F(StringCharSourceTest_106, OperatorPlus_ReturnsNewStringCharSourceWithOffset_106) {

    auto newSource = source + 5;

    EXPECT_EQ(newSource[0], ' ');

    EXPECT_EQ(newSource[1], 'W');

}



TEST_F(StringCharSourceTest_106, OperatorPlusEqual_IncrementsOffsetCorrectly_106) {

    source += 7;

    EXPECT_EQ(source[0], 'W');

    EXPECT_EQ(source[1], 'o');

}
