#include <gtest/gtest.h>

#include "regex_yaml.h"

#include "exp.h"



namespace YAML {

    class NotPrintableTest : public ::testing::Test {

    protected:

        const RegEx& not_printable = Exp::NotPrintable();

    };



    TEST_F(NotPrintableTest, MatchesNonPrintableCharacters_126) {

        EXPECT_TRUE(not_printable.Matches('\x01'));

        EXPECT_TRUE(not_printable.Matches('\x07'));

        EXPECT_TRUE(not_printable.Matches('\x0B'));

        EXPECT_TRUE(not_printable.Matches('\x1F'));

        EXPECT_TRUE(not_printable.Matches('\xC2\x80'));

    }



    TEST_F(NotPrintableTest, MatchesNonPrintableRange_126) {

        for (char ch = '\x01'; ch <= '\x08'; ++ch) {

            EXPECT_TRUE(not_printable.Matches(ch));

        }

        EXPECT_TRUE(not_printable.Matches('\x0B'));

        EXPECT_TRUE(not_printable.Matches('\x0C'));

        EXPECT_TRUE(not_printable.Matches('\x7F'));



        for (char ch = '\xC2\x80'; ch <= '\xC2\x9F'; ++ch) {

            EXPECT_TRUE(not_printable.Matches(ch));

        }

    }



    TEST_F(NotPrintableTest, DoesNotMatchPrintableCharacters_126) {

        EXPECT_FALSE(not_printable.Matches('a'));

        EXPECT_FALSE(not_printable.Matches('0'));

        EXPECT_FALSE(not_printable.Matches(' '));

        EXPECT_FALSE(not_printable.Matches('\n'));

        EXPECT_FALSE(not_printable.Matches('\r'));

    }



    TEST_F(NotPrintableTest, DoesNotMatchExtendedASCII_126) {

        for (char ch = '\xC3\x80'; ch <= '\xC3\xBF'; ++ch) {

            EXPECT_FALSE(not_printable.Matches(ch));

        }

    }



    TEST_F(NotPrintableTest, MatchesEmptyString_126) {

        EXPECT_EQ(not_printable.Match(""), 0);

    }



    TEST_F(NotPrintableTest, MatchNonPrintableSingleCharacter_126) {

        EXPECT_EQ(not_printable.Match("\x01"), 1);

        EXPECT_EQ(not_printable.Match("\x7F"), 1);

        EXPECT_EQ(not_printable.Match("\xC2\x80"), 1);

    }



    TEST_F(NotPrintableTest, MatchNonPrintableMultipleCharacters_126) {

        std::string test_string = "\x01abc\x7Fxyz";

        EXPECT_EQ(not_printable.Match(test_string), 1); // Matches the first character

    }



    TEST_F(NotPrintableTest, MatchNoNonPrintables_126) {

        std::string test_string = "abcdefg";

        EXPECT_EQ(not_printable.Match(test_string), -1);

    }



    TEST_F(NotPrintableTest, MatchAllNonPrintables_126) {

        std::string test_string = "\x01\x02\x03\x04\x05\x06\x07\x08\x0B\x0C\x7F";

        EXPECT_EQ(not_printable.Match(test_string), 1);

    }



    TEST_F(NotPrintableTest, MatchMixedCharacters_126) {

        std::string test_string = "abc\x01defg";

        EXPECT_EQ(not_printable.Match(test_string), 3); // Matches the '\x01'

    }

}


