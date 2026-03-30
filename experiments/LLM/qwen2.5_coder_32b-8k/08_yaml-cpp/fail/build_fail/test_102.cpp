#include <gtest/gtest.h>

#include "stringsource.h"



class StringCharSourceTest : public ::testing::Test {

protected:

    YAML::StringCharSource emptySource;

    YAML::StringCharSource singleCharSource;

    YAML::StringCharSource multiCharSource;



    StringCharSourceTest()

        : emptySource("", 0),

          singleCharSource("A", 1),

          multiCharSource("ABC", 3) {}

};



TEST_F(StringCharSourceTest_102, DefaultConstructor_IsFalse_102) {

    YAML::StringCharSource defaultSource;

    EXPECT_FALSE(defaultSource);

}



TEST_F(StringCharSourceTest_102, EmptyString_IsFalse_102) {

    EXPECT_FALSE(emptySource);

}



TEST_F(StringCharSourceTest_102, SingleCharacterString_IsTrue_102) {

    EXPECT_TRUE(singleCharSource);

}



TEST_F(StringCharSourceTest_102, MultipleCharactersString_IsTrue_102) {

    EXPECT_TRUE(multiCharSource);

}



TEST_F(StringCharSourceTest_102, AccessSingleCharacter_ReturnsCorrectValue_102) {

    EXPECT_EQ(singleCharSource[0], 'A');

}



TEST_F(StringCharSourceTest_102, AccessMultipleCharacters_ReturnsCorrectValues_102) {

    EXPECT_EQ(multiCharSource[0], 'A');

    EXPECT_EQ(multiCharSource[1], 'B');

    EXPECT_EQ(multiCharSource[2], 'C');

}



TEST_F(StringCharSourceTest_102, AccessOutOfBound_ReturnsNullCharacter_102) {

    EXPECT_EQ(singleCharSource[1], '\0');

    EXPECT_EQ(multiCharSource[3], '\0');

}



TEST_F(StringCharSourceTest_102, IncrementOperator_DecrementsRemainingCharactersCount_102) {

    YAML::StringCharSource source = multiCharSource;

    EXPECT_TRUE(source);

    ++source;

    EXPECT_TRUE(source);

    ++source;

    EXPECT_TRUE(source);

    ++source;

    EXPECT_FALSE(source);

}



TEST_F(StringCharSourceTest_102, PlusOperator_ReturnsCorrectOffset_102) {

    YAML::StringCharSource source = multiCharSource + 1;

    EXPECT_EQ(source[0], 'B');

    EXPECT_EQ(source[1], 'C');



    source = multiCharSource + 3;

    EXPECT_FALSE(source);

}



TEST_F(StringCharSourceTest_102, PlusEqualsOperator_ReturnsCorrectOffset_102) {

    YAML::StringCharSource source = multiCharSource;

    source += 1;

    EXPECT_EQ(source[0], 'B');

    EXPECT_EQ(source[1], 'C');



    source += 2;

    EXPECT_FALSE(source);

}



TEST_F(StringCharSourceTest_102, LogicalNotOperator_ReturnsTrueIfEmpty_102) {

    EXPECT_TRUE(!emptySource);

    EXPECT_FALSE(!singleCharSource);

    EXPECT_FALSE(!multiCharSource);

}
