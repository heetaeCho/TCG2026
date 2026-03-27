#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "absl/strings/string_view.h"



namespace re2 {



class IsValidUTF8Test_516 : public ::testing::Test {

protected:

    RegexpStatus status;

};



TEST_F(IsValidUTF8Test_516, ValidUTF8String_516) {

    absl::string_view s = "valid utf-8";

    EXPECT_TRUE(IsValidUTF8(s, &status));

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(IsValidUTF8Test_516, EmptyString_516) {

    absl::string_view s = "";

    EXPECT_TRUE(IsValidUTF8(s, &status));

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(IsValidUTF8Test_516, InvalidUTF8String_516) {

    // Example of invalid UTF-8: overlong encoding for ASCII character

    absl::string_view s = "\xc0\xaf";

    EXPECT_FALSE(IsValidUTF8(s, &status));

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

}



TEST_F(IsValidUTF8Test_516, SingleByteCharacter_516) {

    absl::string_view s = "a";

    EXPECT_TRUE(IsValidUTF8(s, &status));

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(IsValidUTF8Test_516, MultiByteCharacter_516) {

    // Example of valid multi-byte UTF-8: Chinese character '你'

    absl::string_view s = "\xe4\xbd\xa0";

    EXPECT_TRUE(IsValidUTF8(s, &status));

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(IsValidUTF8Test_516, BoundaryCondition_Utf8MaxCodePoint_516) {

    // Example of valid UTF-8: maximum Unicode code point U+10FFFF

    absl::string_view s = "\xf4\x8f\xbf\xbf";

    EXPECT_TRUE(IsValidUTF8(s, &status));

    EXPECT_EQ(status.code(), kRegexpSuccess);

}



TEST_F(IsValidUTF8Test_516, BoundaryCondition_Utf8OverlongEncoding_516) {

    // Example of invalid UTF-8: overlong encoding for ASCII character

    absl::string_view s = "\xc0\xaf";

    EXPECT_FALSE(IsValidUTF8(s, &status));

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

}



TEST_F(IsValidUTF8Test_516, BoundaryCondition_Utf8ContinuationByteFirst_516) {

    // Example of invalid UTF-8: continuation byte in first position

    absl::string_view s = "\x80";

    EXPECT_FALSE(IsValidUTF8(s, &status));

    EXPECT_EQ(status.code(), kRegexpBadUTF8);

}



}  // namespace re2
