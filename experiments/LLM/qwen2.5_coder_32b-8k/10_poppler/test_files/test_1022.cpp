#include <gtest/gtest.h>

#include "UTF.h"



class UTFTest_1022 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



TEST_F(UTFTest_1022, HasUnicodeByteOrderMark_ReturnsTrueForBOMString_1022) {

    std::string_view bomString = "\376\377SomeText";

    EXPECT_TRUE(hasUnicodeByteOrderMark(bomString));

}



TEST_F(UTFTest_1022, HasUnicodeByteOrderMark_ReturnsFalseForNonBOMString_1022) {

    std::string_view nonBomString = "SomeText\376\377";

    EXPECT_FALSE(hasUnicodeByteOrderMark(nonBomString));

}



TEST_F(UTFTest_1022, HasUnicodeByteOrderMark_ReturnsFalseForEmptyString_1022) {

    std::string_view emptyString = "";

    EXPECT_FALSE(hasUnicodeByteOrderMark(emptyString));

}



TEST_F(UTFTest_1022, HasUnicodeByteOrderMark_ReturnsTrueForExactBOMOnly_1022) {

    std::string_view exactBom = "\376\377";

    EXPECT_TRUE(hasUnicodeByteOrderMark(exactBom));

}



TEST_F(UTFTest_1022, HasUnicodeByteOrderMark_ReturnsFalseForShorterStringThanBOM_1022) {

    std::string_view shortString = "\376";

    EXPECT_FALSE(hasUnicodeByteOrderMark(shortString));

}
