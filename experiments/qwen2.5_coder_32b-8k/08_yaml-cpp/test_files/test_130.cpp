#include <gtest/gtest.h>

#include "yaml-cpp/src/exp.h"

#include "yaml-cpp/src/regex_yaml.h"



namespace YAML {

    namespace Exp {

        class DocIndicatorTest : public ::testing::Test {

        protected:

            const RegEx& doc_indicator = DocIndicator();

        };



        TEST_F(DocIndicatorTest_130, MatchesDocStart_130) {

            EXPECT_TRUE(doc_indicator.Matches("---"));

        }



        TEST_F(DocIndicatorTest_130, MatchesDocEnd_130) {

            EXPECT_TRUE(doc_indicator.Matches("..."));

        }



        TEST_F(DocIndicatorTest_130, DoesNotMatchOtherStrings_130) {

            EXPECT_FALSE(doc_indicator.Matches("test"));

            EXPECT_FALSE(doc_indicator.Matches("----"));

            EXPECT_FALSE(doc_indicator.Matches(".."));

        }



        TEST_F(DocIndicatorTest_130, MatchesDocStartWithSpaces_130) {

            EXPECT_TRUE(doc_indicator.Matches(" ---"));

            EXPECT_TRUE(doc_indicator.Matches("--- "));

        }



        TEST_F(DocIndicatorTest_130, MatchesDocEndWithSpaces_130) {

            EXPECT_TRUE(doc_indicator.Matches(" ..."));

            EXPECT_TRUE(doc_indicator.Matches("... "));

        }



        TEST_F(DocIndicatorTest_130, DoesNotMatchEmptyString_130) {

            EXPECT_FALSE(doc_indicator.Matches(""));

        }

    }

}
