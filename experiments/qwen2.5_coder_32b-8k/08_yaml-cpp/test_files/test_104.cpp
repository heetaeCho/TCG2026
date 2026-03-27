#include <gtest/gtest.h>

#include "stringsource.h"



using namespace YAML;



class StringCharSourceTest_104 : public ::testing::Test {

protected:

    const char* testString = "Hello, World!";

    std::size_t testSize = 13;

    StringCharSource source;



    void SetUp() override {

        source = StringCharSource(testString, testSize);

    }

};



TEST_F(StringCharSourceTest_104, ConstructorInitializesCorrectly_104) {

    EXPECT_EQ(static_cast<bool>(source), true);

}



TEST_F(StringCharSourceTest_104, OperatorNotReturnsFalseWhenValid_104) {

    EXPECT_FALSE(!source);

}



TEST_F(StringCharSourceTest_104, OperatorBoolReturnsTrueWhenValid_104) {

    EXPECT_TRUE(static_cast<bool>(source));

}



TEST_F(StringCharSourceTest_104, OperatorArrayAccessValidIndex_104) {

    EXPECT_EQ(source[0], 'H');

    EXPECT_EQ(source[7], 'W');

    EXPECT_EQ(source[testSize - 1], '!');

}



TEST_F(StringCharSourceTest_104, OperatorArrayAccessBoundaryCondition_104) {

    EXPECT_THROW((void)(source[testSize]), std::out_of_range);

}



TEST_F(StringCharSourceTest_104, OperatorIncrementPrefix_104) {

    ++source;

    EXPECT_EQ(source[0], 'e');

}



TEST_F(StringCharSourceTest_104, OperatorPlusOperatorBoundaryCondition_104) {

    auto newSource = source + static_cast<int>(testSize);

    EXPECT_FALSE(static_cast<bool>(newSource));

}



TEST_F(StringCharSourceTest_104, OperatorPlusEqualBoundaryCondition_104) {

    source += testSize;

    EXPECT_FALSE(static_cast<bool>(source));

}
