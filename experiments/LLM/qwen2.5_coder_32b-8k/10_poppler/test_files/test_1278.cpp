#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/UTF.h"



class UTFUtilsTest_1278 : public ::testing::Test {

protected:

    std::string_view unicodeByteOrderMark = "\xef\xbb\xbf";

};



TEST_F(UTFUtilsTest_1278, HasUnicodeByteOrderMark_ReturnsTrueForValidBOM_1278) {

    std::string input = "\xef\xbb\xbfSome text";

    EXPECT_TRUE(hasUnicodeByteOrderMark(input));

}



TEST_F(UTFUtilsTest_1278, HasUnicodeByteOrderMark_ReturnsFalseForMissingBOM_1278) {

    std::string input = "Some text without BOM";

    EXPECT_FALSE(hasUnicodeByteOrderMark(input));

}



TEST_F(UTFUtilsTest_1278, HasUnicodeByteOrderMark_ReturnsTrueForExactBOMOnly_1278) {

    std::string input = "\xef\xbb\xbf";

    EXPECT_TRUE(hasUnicodeByteOrderMark(input));

}



TEST_F(UTFUtilsTest_1278, HasUnicodeByteOrderMark_ReturnsFalseForPartialBOM_1278) {

    std::string input = "\xef\xbb";

    EXPECT_FALSE(hasUnicodeByteOrderMark(input));

}



TEST_F(UTFUtilsTest_1278, HasUnicodeByteOrderMark_ReturnsFalseForDifferentPrefix_1278) {

    std::string input = "\xef\xbe\xbfSome text";

    EXPECT_FALSE(hasUnicodeByteOrderMark(input));

}
