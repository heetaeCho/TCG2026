#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "UTF.h"



class UTFTest_1527 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if necessary

    }



    void TearDown() override {

        // Cleanup can be done here if necessary

    }

};



TEST_F(UTFTest_1527, EmptyStringReturnsEmptyWithBom_1527) {

    std::string_view utf8 = "";

    std::string result = utf8ToUtf16WithBom(utf8);

    EXPECT_EQ(result, "\376\377");

}



TEST_F(UTFTest_1527, SingleAsciiCharacterConversion_1527) {

    std::string_view utf8 = "A";

    std::string result = utf8ToUtf16WithBom(utf8);

    EXPECT_EQ(result, "\376\377\x00A");

}



TEST_F(UTFTest_1527, MultiAsciiCharactersConversion_1527) {

    std::string_view utf8 = "Hello";

    std::string result = utf8ToUtf16WithBom(utf8);

    EXPECT_EQ(result, "\376\377H\x00e\x00l\x00l\x00o\x00");

}



TEST_F(UTFTest_1527, SingleUnicodeCharacterConversion_1527) {

    std::string_view utf8 = "\u00E9"; // 'é'

    std0376\377\xC3\xA9" is incorrect. It should be the UTF-16 representation

    std::string result = utf8ToUtf16WithBom(utf8);

    EXPECT_EQ(result, "\376\377\xA9\x00");

}



TEST_F(UTFTest_1527, MultiUnicodeCharactersConversion_1527) {

    std::string_view utf8 = "café";

    std::string result = utf8ToUtf16WithBom(utf8);

    EXPECT_EQ(result, "\376\377c\x00a\x00f\x00\xA9\x00");

}



TEST_F(UTFTest_1527, MixedCharactersConversion_1527) {

    std::string_view utf8 = "Hello café";

    std::string result = utf8ToUtf16WithBom(utf8);

    EXPECT_EQ(result, "\376\377H\x00e\x00l\x00l\x00o\x00 \x00c\x00a\x00f\x00\xA9\x00");

}

```


