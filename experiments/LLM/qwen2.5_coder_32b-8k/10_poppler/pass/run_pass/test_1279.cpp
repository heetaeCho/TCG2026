#include <gtest/gtest.h>

#include "UTF.h"



class UTFTest_1279 : public ::testing::Test {

protected:

    // No setup or teardown required for this simple function.

};



TEST_F(UTFTest_1279, HasUnicodeByteOrderMarkLE_EmptyString_1279) {

    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(""));

}



TEST_F(UTFTest_1279, HasUnicodeByteOrderMarkLE_ShortString_1279) {

    EXPECT_FALSE(hasUnicodeByteOrderMarkLE("fe"));

}



TEST_F(UTFTest_1279, HasUnicodeByteOrderMarkLE_CorrectLittleEndianBOM_1279) {

    std::string bom = "\xef\xbb\xbf";

    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(bom));

}



TEST_F(UTFTest_1279, HasUnicodeByteOrderMarkLE_IncorrectBOM_1279) {

    std::string incorrect_bom = "\xff\xfe";

    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(incorrect_bom));

}



TEST_F(UTFTest_1279, HasUnicodeByteOrderMarkLE_StringWithBOMAtStart_1279) {

    std::string str_with_bom = "\xef\xbb\xbfHello, World!";

    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(str_with_bom));

}



TEST_F(UTFTest_1279, HasUnicodeByteOrderMarkLE_StringWithoutBOM_1279) {

    std::string str_without_bom = "Hello, World!";

    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(str_without_bom));

}
