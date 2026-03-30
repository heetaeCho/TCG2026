#include <gtest/gtest.h>

#include "stringsource.h"



namespace YAML {

class StringCharSourceTest_103 : public ::testing::Test {

protected:

    static constexpr const char* testString = "HelloWorld";

    static constexpr std::size_t testSize = 10;

    StringCharSource source;



    StringCharSourceTest_103() : source(testString, testSize) {}

};



TEST_F(StringCharSourceTest_103, OperatorBool_ReturnsTrueForNonEmptyString_103) {

    EXPECT_TRUE(static_cast<bool>(source));

}



TEST_F(StringCharSourceTest_103, OperatorBool_ReturnsFalseForEmptyString_103) {

    StringCharSource emptySource("", 0);

    EXPECT_FALSE(static_cast<bool>(emptySource));

}



TEST_F(StringCharSourceTest_103, OperatorNot_ReturnsTrueForEmptyString_103) {

    StringCharSource emptySource("", 0);

    EXPECT_TRUE(!emptySource);

}



TEST_F(StringCharSourceTest_103, OperatorNot_ReturnsFalseForNonEmptyString_103) {

    EXPECT_FALSE(!source);

}



TEST_F(StringCharSourceTest_103, OperatorBracket_ReturnsCorrectCharacter_103) {

    for (std::size_t i = 0; i < testSize; ++i) {

        EXPECT_EQ(source[i], testString[i]);

    }

}



TEST_F(StringCharSourceTest_103, OperatorBracket_OutOfBoundsAccess_ReturnsNull_103) {

    // Assuming out-of-bounds access returns null character

    EXPECT_EQ(source[testSize], '\0');

}



TEST_F(StringCharSourceTest_103, OperatorPlus_ReturnsCorrectOffsetStringCharSource_103) {

    StringCharSource offsetSource = source + 5;

    for (std::size_t i = 0; i < testSize - 5; ++i) {

        EXPECT_EQ(offsetSource[i], testString[5 + i]);

    }

}



TEST_F(StringCharSourceTest_103, OperatorPlus_OutOfBoundsOffset_ReturnsEmptyStringCharSource_103) {

    StringCharSource offsetSource = source + 20;

    EXPECT_FALSE(static_cast<bool>(offsetSource));

}



TEST_F(StringCharSourceTest_103, OperatorIncrement_IncrementsOffset_103) {

    ++source;

    for (std::size_t i = 0; i < testSize - 1; ++i) {

        EXPECT_EQ(source[i], testString[1 + i]);

    }

}



TEST_F(StringCharSourceTest_103, OperatorIncrement_IncrementPastEnd_ReturnsEmptyStringCharSource_103) {

    for (std::size_t i = 0; i < testSize; ++i) {

        ++source;

    }

    EXPECT_FALSE(static_cast<bool>(source));

}



TEST_F(StringCharSourceTest_103, OperatorPlusEquals_IncrementsOffset_103) {

    source += 5;

    for (std::size_t i = 0; i < testSize - 5; ++i) {

        EXPECT_EQ(source[i], testString[5 + i]);

    }

}



TEST_F(StringCharSourceTest_103, OperatorPlusEquals_OutOfBoundsOffset_ReturnsEmptyStringCharSource_103) {

    source += 20;

    EXPECT_FALSE(static_cast<bool>(source));

}

} // namespace YAML
