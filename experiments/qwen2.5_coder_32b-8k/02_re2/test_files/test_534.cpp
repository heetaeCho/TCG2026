#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "absl/strings/string_view.h"

#include "re2/util/utf.h"



namespace re2 {



void ConvertLatin1ToUTF8(absl::string_view latin1, std::string* utf);



class ConvertLatin1ToUTF8Test_534 : public ::testing::Test {

protected:

    std::string result;

};



TEST_F(ConvertLatin1ToUTF8Test_534, EmptyString_ConvertsCorrectly_534) {

    absl::string_view input = "";

    ConvertLatin1ToUTF8(input, &result);

    EXPECT_EQ(result, "");

}



TEST_F(ConvertLatin1ToUTF8Test_534, SingleByteCharacters_ConvertsCorrectly_534) {

    absl::string_view input = "abc";

    ConvertLatin1ToUTF8(input, &result);

    EXPECT_EQ(result, "abc");

}



TEST_F(ConvertLatin1ToUTF8Test_534, FullLatin1Range_ConvertsCorrectly_534) {

    std::string input(256, '\0');

    for (int i = 0; i < 256; ++i) {

        input[i] = static_cast<char>(i);

    }

    ConvertLatin1ToUTF8(absl::string_view(input), &result);

    EXPECT_EQ(result, input);

}



TEST_F(ConvertLatin1ToUTF8Test_534, HighByteCharacters_ConvertsCorrectly_534) {

    absl::string_view input = "\xC0\xC1\xFF";

    ConvertLatin1ToUTF8(input, &result);

    std::string expected = "\xC3\x80\xC3\x81\xC3\xBF";  // UTF-8 representation of \xC0, \xC1, and \xFF

    EXPECT_EQ(result, expected);

}



TEST_F(ConvertLatin1ToUTF8Test_534, MixedCharacters_ConvertsCorrectly_534) {

    absl::string_view input = "a\xC2b";

    ConvertLatin1ToUTF8(input, &result);

    std::string expected = "a\xc3\x82b";  // UTF-8 representation of \xC2

    EXPECT_EQ(result, expected);

}



}  // namespace re2
