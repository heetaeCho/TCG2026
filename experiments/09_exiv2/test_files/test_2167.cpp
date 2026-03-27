#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class CommentValueTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(CommentValueTest_2167, ConstructorWithEmptyString_2167) {

    CommentValue comment("");

    EXPECT_EQ(comment.comment("UTF-8"), "");

}



TEST_F(CommentValueTest_2167, ConstructorWithNonEmptyString_2167) {

    std::string testComment = "Sample Comment";

    CommentValue comment(testComment);

    EXPECT_EQ(comment.comment("UTF-8"), testComment);

}



TEST_F(CommentValueTest_2167, ReadWithString_2167) {

    CommentValue comment;

    std::string newComment = "New Comment";

    comment.read(newComment);

    EXPECT_EQ(comment.comment("UTF-8"), newComment);

}



TEST_F(CommentValueTest_2167, ReadWithEmptyString_2167) {

    CommentValue comment("Initial Comment");

    comment.read("");

    EXPECT_EQ(comment.comment("UTF-8"), "");

}



TEST_F(CommentValueTest_2167, WriteToStream_2167) {

    std::ostringstream oss;

    std::string testComment = "Sample Comment";

    CommentValue comment(testComment);

    comment.write(oss);

    EXPECT_EQ(oss.str(), testComment);

}



TEST_F(CommentValueTest_2167, DetectCharsetWithEmptyString_2167) {

    CommentValue comment("");

    std::string charset;

    EXPECT_STREQ(comment.detectCharset(charset), "");

    EXPECT_EQ(charset, "");

}



TEST_F(CommentValueTest_2167, DetectCharsetWithNonEmptyString_2167) {

    CommentValue comment("Sample Comment");

    std::string charset;

    EXPECT_STREQ(comment.detectCharset(charset), "UTF-8");

    EXPECT_EQ(charset, "UTF-8");

}



TEST_F(CommentValueTest_2167, CharsetId_2167) {

    CommentValue comment("Sample Comment");

    EXPECT_EQ(comment.charsetId(), CommentValue::CharsetId::utf8);

}
