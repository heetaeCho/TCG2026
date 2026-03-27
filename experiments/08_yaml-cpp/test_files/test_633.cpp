#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/emitterutils.cpp"

#include "yaml-cpp/ostream_wrapper.h"



namespace YAML {

    namespace Utils {



        class OstreamWrapperMock : public ostream_wrapper {

        public:

            MOCK_METHOD(void, write, (const std::string &str), (override));

            MOCK_METHOD(void, write, (const char *str, std::size_t size), (override));

            MOCK_METHOD(void, set_comment, (), (override));

            MOCK_METHOD(std::size_t, col, () const, (override));

        };



        class WriteCommentTest_633 : public ::testing::Test {

        protected:

            OstreamWrapperMock out;

        };



        TEST_F(WriteCommentTest_633, SingleLineComment_633) {

            EXPECT_CALL(out, col()).WillOnce(::testing::Return(0));

            EXPECT_CALL(out, set_comment());

            EXPECT_CALL(out, write("#"));

            EXPECT_CALL(out, write(" This is a comment"));



            bool result = WriteComment(out, " This is a comment", 17, 0);

            EXPECT_TRUE(result);

        }



        TEST_F(WriteCommentTest_633, MultiLineComment_633) {

            EXPECT_CALL(out, col()).WillOnce(::testing::Return(0)).WillRepeatedly(::testing::Return(4));

            EXPECT_CALL(out, set_comment()).Times(2);

            EXPECT_CALL(out, write("#")).Times(2);

            EXPECT_CALL(out, write(" This is a\n"));

            EXPECT_CALL(out, write("    comment"));



            bool result = WriteComment(out, " This is a\ncomment", 18, 4);

            EXPECT_TRUE(result);

        }



        TEST_F(WriteCommentTest_633, EmptyComment_633) {

            EXPECT_CALL(out, col()).WillOnce(::testing::Return(0));

            EXPECT_CALL(out, set_comment());

            EXPECT_CALL(out, write("#"));



            bool result = WriteComment(out, "", 0, 0);

            EXPECT_TRUE(result);

        }



        TEST_F(WriteCommentTest_633, CommentWithTrailingNewline_633) {

            EXPECT_CALL(out, col()).WillOnce(::testing::Return(0)).WillRepeatedly(::testing::Return(4));

            EXPECT_CALL(out, set_comment()).Times(2);

            EXPECT_CALL(out, write("#")).Times(2);

            EXPECT_CALL(out, write(" This is a comment\n"));

            EXPECT_CALL(out, write("    "));



            bool result = WriteComment(out, " This is a comment\n", 19, 4);

            EXPECT_TRUE(result);

        }



        TEST_F(WriteCommentTest_633, LargePostCommentIndent_633) {

            EXPECT_CALL(out, col()).WillOnce(::testing::Return(0)).WillRepeatedly(::testing::Return(20));

            EXPECT_CALL(out, set_comment()).Times(2);

            EXPECT_CALL(out, write("#")).Times(2);

            EXPECT_CALL(out, write(" This is a\n"));

            EXPECT_CALL(out, write("                    comment"));



            bool result = WriteComment(out, " This is a\ncomment", 18, 20);

            EXPECT_TRUE(result);

        }



    }

}
