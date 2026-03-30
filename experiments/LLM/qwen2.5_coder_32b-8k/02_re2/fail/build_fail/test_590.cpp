#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/re2/util/pcre.h"



namespace re2 {

    namespace {



        class PCRETest_590 : public ::testing::Test {

        protected:

            void SetUp() override {

                // Initialize with a simple pattern

                options.set_match_limit(1000);

                options.set_stack_limit(8 * 1024 * 1024);

                options.set_report_errors(true);



                pcre_ = std::make_unique<PCRE>("abc", options);

            }



            void TearDown() override {

                pcre_.reset();

            }



            std::unique_ptr<PCRE> pcre_;

            PCRE_Options options;

        };



        TEST_F(PCRETest_590, PatternInitialization_590) {

            EXPECT_EQ(pcre_->pattern(), "abc");

        }



        TEST_F(PCRETest_590, NumberOfCapturingGroups_ZeroForSimplePattern_590) {

            EXPECT_EQ(pcre_->NumberOfCapturingGroups(), 0);

        }



        TEST_F(PCRETest_590, HitLimit_DefaultFalse_590) {

            EXPECT_FALSE(pcre_->HitLimit());

        }



        TEST_F(PCRETest_590, ClearHitLimit_NoEffectOnDefault_590) {

            pcre_->ClearHitLimit();

            EXPECT_FALSE(pcre_->HitLimit());

        }



        TEST_F(PCRETest_590, DoMatch_SimplePattern_Success_590) {

            size_t consumed = 0;

            EXPECT_TRUE(pcre_->DoMatch("abc", PCRE::UNANCHORED, &consumed, nullptr, 0));

            EXPECT_EQ(consumed, 3);

        }



        TEST_F(PCRETest_590, DoMatch_PartialPattern_Success_590) {

            size_t consumed = 0;

            EXPECT_TRUE(pcre_->DoMatch("abcde", PCRE::UNANCHORED, &consumed, nullptr, 0));

            EXPECT_EQ(consumed, 3);

        }



        TEST_F(PCRETest_590, DoMatch_UnmatchingPattern_Failure_590) {

            size_t consumed = 0;

            EXPECT_FALSE(pcre_->DoMatch("def", PCRE::UNANCHORED, &consumed, nullptr, 0));

        }



        TEST_F(PCRETest_590, Extract_SimplePattern_Success_590) {

            std::string out;

            EXPECT_TRUE(PCRE::Extract("abc", *pcre_, "\\0", &out));

            EXPECT_EQ(out, "abc");

        }



        TEST_F(PCRETest_590, Extract_UnmatchingPattern_Failure_590) {

            std::string out;

            EXPECT_FALSE(PCRE::Extract("def", *pcre_, "\\0", &out));

        }



        TEST_F(PCRETest_590, QuoteMeta_NoSpecialChars_590) {

            std::string result = PCRE::QuoteMeta("abc");

            EXPECT_EQ(result, "abc");

        }



        TEST_F(PCRETest_590, QuoteMeta_SpecialChars_Escaped_590) {

            std::string result = PCRE::QuoteMeta(".+*?[^]$(){}|\\");

            EXPECT_EQ(result, "\\.\\+\\*\\?\\[\\^\\]\\$\\(\\)\\{\\}\\|\\\\");

        }



        TEST_F(PCRETest_590, CheckRewriteString_ValidPattern_Success_590) {

            std::string error;

            EXPECT_TRUE(pcre_->CheckRewriteString("\\1", &error));

        }



        TEST_F(PCRETest_590, CheckRewriteString_InvalidBackref_Failure_590) {

            std::string error;

            EXPECT_FALSE(pcre_->CheckRewriteString("\\2", &error));

        }



    }  // namespace

}  // namespace re2
