#include <gtest/gtest.h>

#include "exp.h"



namespace YAML {

    namespace Exp {

        TEST(EndScalarInFlowTest_146, MatchesColonFollowedByBlankOrBreak_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_TRUE(endScalar.Matches(": "));

        }



        TEST(EndScalarInFlowTest_146, MatchesColonFollowedByComma_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_TRUE(endScalar.Matches(":,"));

        }



        TEST(EndScalarInFlowTest_146, MatchesColonFollowedByCloseBracket_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_TRUE(endScalar.Matches(":]"));

        }



        TEST(EndScalarInFlowTest_146, MatchesColonFollowedByCloseCurlyBrace_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_TRUE(endScalar.Matches(":}"));

        }



        TEST(EndScalarInFlowTest_146, MatchesCommaFollowedByOpenBracket_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_TRUE(endScalar.Matches(",["));

        }



        TEST(EndScalarInFlowTest_146, MatchesCommaFollowedByCloseBracket_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_TRUE(endScalar.Matches(",]"));

        }



        TEST(EndScalarInFlowTest_146, MatchesCommaFollowedByOpenCurlyBrace_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_TRUE(endScalar.Matches(",{"));

        }



        TEST(EndScalarInFlowTest_146, MatchesCommaFollowedByCloseCurlyBrace_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_TRUE(endScalar.Matches("},"));

        }



        TEST(EndScalarInFlowTest_146, DoesNotMatchSingleColon_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_FALSE(endScalar.Matches(":"));

        }



        TEST(EndScalarInFlowTest_146, DoesNotMatchRandomString_146) {

            const RegEx& endScalar = EndScalarInFlow();

            EXPECT_FALSE(endScalar.Matches("random_string"));

        }

    }

}
