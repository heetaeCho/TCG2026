#include <gtest/gtest.h>

#include "stringsource.h"



namespace YAML {

    class StringCharSourceTest_105 : public ::testing::Test {

    protected:

        static constexpr const char* testString = "Hello, World!";

        std::size_t testSize = 13;

        StringCharSource source;



        void SetUp() override {

            source = StringCharSource(testString, testSize);

        }

    };



    TEST_F(StringCharSourceTest_105, InitialOffsetIsZero_105) {

        EXPECT_EQ(source[0], 'H');

    }



    TEST_F(StringCharSourceTest_105, OperatorPlusIncreasesOffset_105) {

        StringCharSource newSource = source + 7;

        EXPECT_EQ(newSource[0], 'W');

    }



    TEST_F(StringCharSourceTest_105, OperatorPlusWithNegativeDoesNotDecreaseBelowZero_105) {

        StringCharSource newSource = source + (-10);

        EXPECT_EQ(newSource[0], 'H');

    }



    TEST_F(StringCharSourceTest_105, OperatorBoolReturnsTrueWhenValid_105) {

        EXPECT_TRUE(static_cast<bool>(source));

    }



    TEST_F(StringCharSourceTest_105, OperatorNotReturnsFalseWhenValid_105) {

        EXPECT_FALSE(!source);

    }



    TEST_F(StringCharSourceTest_105, AccessPastEndReturnsNullChar_105) {

        EXPECT_EQ(source[testSize], '\0');

    }



    TEST_F(StringCharSourceTest_105, OperatorPlusWithLargeValueSetsOffsetToEnd_105) {

        StringCharSource newSource = source + 20;

        EXPECT_EQ(newSource[0], '\0');

    }



    TEST_F(StringCharSourceTest_105, OperatorIncrementIncreasesOffset_105) {

        ++source;

        EXPECT_EQ(source[0], 'e');

    }



    TEST_F(StringCharSourceTest_105, OperatorPlusEqualsIncreasesOffset_105) {

        source += 7;

        EXPECT_EQ(source[0], 'W');

    }

}
