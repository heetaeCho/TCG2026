#include <gtest/gtest.h>

#include "regeximpl.h"



namespace YAML {

    class RegExTest_108 : public ::testing::Test {

    protected:

        RegExTest_108() {}

        virtual ~RegExTest_108() {}



        void SetUp() override {

            // Setup code if needed

        }



        void TearDown() override {

            // Teardown code if needed

        }

    };



    TEST_F(RegExTest_108, MatchesSingleCharacter_108) {

        RegEx regEx('a');

        EXPECT_TRUE(regEx.Matches('a'));

        EXPECT_FALSE(regEx.Matches('b'));

    }



    TEST_F(RegExTest_108, MatchesCharRange_108) {

        RegEx regEx('a', 'c');

        EXPECT_TRUE(regEx.Matches('a'));

        EXPECT_TRUE(regEx.Matches('b'));

        EXPECT_TRUE(regEx.Matches('c'));

        EXPECT_FALSE(regEx.Matches('d'));

    }



    TEST_F(RegExTest_108, MatchesEmptyString_108) {

        RegEx regEx("");

        EXPECT_TRUE(regEx.Matches(""));

        EXPECT_FALSE(regEx.Matches("a"));

    }



    TEST_F(RegExTest_108, MatchesFullString_108) {

        RegEx regEx("abc", REGEX_MATCH);

        EXPECT_TRUE(regEx.Matches("abc"));

        EXPECT_FALSE(regEx.Matches("abcd"));

        EXPECT_FALSE(regEx.Matches("ab"));

    }



    TEST_F(RegExTest_108, MatchesOperatorNot_108) {

        RegEx regEx('a');

        RegEx notRegEx = !regEx;

        EXPECT_TRUE(notRegEx.Matches('b'));

        EXPECT_FALSE(notRegEx.Matches('a'));

    }



    TEST_F(RegExTest_108, MatchesOperatorOr_108) {

        RegEx regEx1('a');

        RegEx regEx2('b');

        RegEx orRegEx = regEx1 | regEx2;

        EXPECT_TRUE(orRegEx.Matches('a'));

        EXPECT_TRUE(orRegEx.Matches('b'));

        EXPECT_FALSE(orRegEx.Matches('c'));

    }



    TEST_F(RegExTest_108, MatchesOperatorAnd_108) {

        RegEx regEx1('a');

        RegEx regEx2('a');

        RegEx andRegEx = regEx1 & regEx2;

        EXPECT_TRUE(andRegEx.Matches('a'));

        EXPECT_FALSE(andRegEx.Matches('b'));

    }



    TEST_F(RegExTest_108, MatchesOperatorSeq_108) {

        RegEx regEx1('a');

        RegEx regEx2('b');

        RegEx seqRegEx = regEx1 + regEx2;

        EXPECT_TRUE(seqRegEx.Matches("ab"));

        EXPECT_FALSE(seqRegEx.Matches("ba"));

        EXPECT_FALSE(seqRegEx.Matches("abc"));

    }



    TEST_F(RegExTest_108, MatchesBoundaryConditions_108) {

        RegEx regEx('a');

        EXPECT_FALSE(regEx.Matches('\0'));

        EXPECT_TRUE(regEx.Matches('a'));

    }

}
