#include <gtest/gtest.h>

#include "UTF.h"



using namespace std::literals;



TEST(HasUnicodeByteOrderMarkLETest_1023, NormalOperationWithBOM_1023) {

    EXPECT_TRUE(hasUnicodeByteOrderMarkLE("\377\376"sv));

}



TEST(HasUnicodeByteOrderMarkLETest_1023, NormalOperationWithoutBOM_1023) {

    EXPECT_FALSE(hasUnicodeByteOrderMarkLE("Hello, World!"sv));

}



TEST(HasUnicodeByteOrderMarkLETest_1023, BoundaryConditionEmptyString_1023) {

    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(""sv));

}



TEST(HasUnicodeByteOrderMarkLETest_1023, BoundaryConditionSingleCharacter_1023) {

    EXPECT_FALSE(hasUnicodeByteOrderMarkLE("\377"sv));

}



TEST(HasUnicodeByteOrderMarkLETest_1023, ExceptionalCaseInvalidUTF8_1023) {

    // This is not strictly an exceptional case as the function deals with byte sequences

    // but it's a scenario where the input does not match the BOM.

    EXPECT_FALSE(hasUnicodeByteOrderMarkLE("\xFF\xFE\xFF"sv));

}
