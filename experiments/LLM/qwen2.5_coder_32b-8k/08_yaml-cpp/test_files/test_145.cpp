#include <gtest/gtest.h>

#include "exp.h"



namespace YAML {

    namespace Exp {



        class RegExTest_145 : public ::testing::Test {

        protected:

            const RegEx& endScalarRegex = EndScalar();

        };



        TEST_F(RegExTest_145, MatchesColonOnly_145) {

            EXPECT_TRUE(endScalarRegex.Matches(":"));

        }



        TEST_F(RegExTest_145, MatchesColonFollowedBySpace_145) {

            EXPECT_TRUE(endScalarRegex.Matches(": "));

        }



        TEST_F(RegExTest_145, MatchesColonFollowedByTab_145) {

            EXPECT_TRUE(endScalarRegex.Matches(":\t"));

        }



        TEST_F(RegExTest_145, MatchesColonFollowedByNewline_145) {

            EXPECT_TRUE(endScalarRegex.Matches(":\n"));

        }



        TEST_F(RegExTest_145, MatchesOnlySpace_145) {

            EXPECT_FALSE(endScalarRegex.Matches(" "));

        }



        TEST_F(RegExTest_145, MatchesEmptyString_145) {

            EXPECT_FALSE(endScalarRegex.Matches(""));

        }



        TEST_F(RegExTest_145, MatchesColonFollowedByCharacter_145) {

            EXPECT_FALSE(endScalarRegex.Matches(":a"));

        }



        TEST_F(RegExTest_145, MatchesJustACharacter_145) {

            EXPECT_FALSE(endScalarRegex.Matches("a"));

        }



    }

}
