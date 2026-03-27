#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueEscapeToUnicodeTest_13 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueEscapeToUnicodeTest_13, ControlCharacterEscaping_13) {

    EXPECT_EQ(value.escapeToUnicode('\0'), "\\u0000");

    EXPECT_EQ(value.escapeToUnicode('\x1f'), "\\u001f");

}



TEST_F(ValueEscapeToUnicodeTest_13, PrintableCharacterNoEscaping_13) {

    EXPECT_EQ(value.escapeToUnicode('A'), "");

    EXPECT_EQ(value.escapeToUnicode(' '), "");

    EXPECT_EQ(value.escapeToUnicode('~'), "");

}



TEST_F(ValueEscapeToUnicodeTest_13, BoundaryConditionLowestControlChar_13) {

    EXPECT_EQ(value.escapeToUnicode('\0'), "\\u0000");

}



TEST_F(ValueEscapeToUnicodeTest_13, BoundaryConditionHighestControlChar_13) {

    EXPECT_EQ(value.escapeToUnicode('\x1f'), "\\u001f");

}



TEST_F(ValueEscapeToUnicodeTest_13, ExtendedASCIICharacterNoEscaping_13) {

    EXPECT_EQ(value.escapeToUnicode('\x80'), "");

    EXPECT_EQ(value.escapeToUnicode('\xff'), "");

}
