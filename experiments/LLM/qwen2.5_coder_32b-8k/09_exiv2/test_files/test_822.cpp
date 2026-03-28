#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include <sstream>



using namespace Exiv2;



class CommentValueTest_822 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(CommentValueTest_822, WriteWithUndefinedCharset_822) {

    CommentValue commentValue("Sample comment");

    std::ostringstream os;

    commentValue.write(os);

    EXPECT_EQ(os.str(), "Sample comment");

}



TEST_F(CommentValueTest_822, WriteWithAsciiCharset_822) {

    CommentValue commentValue("Sample comment");

    commentValue.read("charset=ascii Sample comment");

    std::ostringstream os;

    commentValue.write(os);

    EXPECT_EQ(os.str(), "charset=ascii Sample comment");

}



TEST_F(CommentValueTest_822, WriteWithUnicodeCharset_822) {

    CommentValue commentValue("Sample comment");

    commentValue.read("charset=unicode Sample comment");

    std::ostringstream os;

    commentValue.write(os);

    EXPECT_EQ(os.str(), "charset=unicode Sample comment");

}



TEST_F(CommentValueTest_822, WriteWithEmptyComment_822) {

    CommentValue commentValue("");

    std::ostringstream os;

    commentValue.write(os);

    EXPECT_EQ(os.str(), "");

}



TEST_F(CommentValueTest_822, WriteWithSpecialCharacters_822) {

    CommentValue commentValue("Special !@#$%^&*() Characters");

    std::ostringstream os;

    commentValue.write(os);

    EXPECT_EQ(os.str(), "Special !@#$%^&*() Characters");

}



TEST_F(CommentValueTest_822, WriteWithLongComment_822) {

    CommentValue commentValue("This is a very long comment that exceeds typical lengths to test edge cases in the implementation.");

    std::ostringstream os;

    commentValue.write(os);

    EXPECT_EQ(os.str(), "This is a very long comment that exceeds typical lengths to test edge cases in the implementation.");

}



TEST_F(CommentValueTest_822, WriteWithCharsetDetection_822) {

    CommentValue commentValue("charset=jis Sample comment");

    std::ostringstream os;

    commentValue.write(os);

    EXPECT_EQ(os.str(), "charset=jis Sample comment");

}
