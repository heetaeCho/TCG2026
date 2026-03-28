#include <gtest/gtest.h>

#include "exp.h"



namespace YAML {

    namespace Exp {

        TEST_F(HexTest_125, MatchesValidHexDigits_125) {

            EXPECT_TRUE(Hex().Matches('0'));

            EXPECT_TRUE(Hex().Matches('9'));

            EXPECT_TRUE(Hex().Matches('A'));

            EXPECT_TRUE(Hex().Matches('F'));

            EXPECT_TRUE(Hex().Matches('a'));

            EXPECT_TRUE(Hex().Matches('f'));

        }



        TEST_F(HexTest_125, MatchesInvalidHexDigits_125) {

            EXPECT_FALSE(Hex().Matches('G'));

            EXPECT_FALSE(Hex().Matches('g'));

            EXPECT_FALSE(Hex().Matches('-'));

            EXPECT_FALSE(Hex().Matches(' '));

            EXPECT_FALSE(Hex().Matches('\n'));

        }



        TEST_F(HexTest_125, MatchesValidHexStrings_125) {

            EXPECT_TRUE(Hex().Matches("0"));

            EXPECT_TRUE(Hex().Matches("9"));

            EXPECT_TRUE(Hex().Matches("A"));

            EXPECT_TRUE(Hex().Matches("F"));

            EXPECT_TRUE(Hex().Matches("a"));

            EXPECT_TRUE(Hex().Matches("f"));

        }



        TEST_F(HexTest_125, MatchesInvalidHexStrings_125) {

            EXPECT_FALSE(Hex().Matches("G"));

            EXPECT_FALSE(Hex().Matches("g"));

            EXPECT_FALSE(Hex().Matches("-"));

            EXPECT_FALSE(Hex().Matches(" "));

            EXPECT_FALSE(Hex().Matches("\n"));

        }



        TEST_F(HexTest_125, MatchesEmptyString_125) {

            EXPECT_FALSE(Hex().Matches(""));

        }



        TEST_F(HexTest_125, MatchValidHexDigits_125) {

            EXPECT_EQ(Hex().Match("0"), 1);

            EXPECT_EQ(Hex().Match("9"), 1);

            EXPECT_EQ(Hex().Match("A"), 1);

            EXPECT_EQ(Hex().Match("F"), 1);

            EXPECT_EQ(Hex().Match("a"), 1);

            EXPECT_EQ(Hex().Match("f"), 1);

        }



        TEST_F(HexTest_125, MatchInvalidHexDigits_125) {

            EXPECT_EQ(Hex().Match("G"), -1);

            EXPECT_EQ(Hex().Match("g"), -1);

            EXPECT_EQ(Hex().Match("-"), -1);

            EXPECT_EQ(Hex().Match(" "), -1);

            EXPECT_EQ(Hex().Match("\n"), -1);

        }



        TEST_F(HexTest_125, MatchEmptyString_125) {

            EXPECT_EQ(Hex().Match(""), -1);

        }

    }

}
