#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using ::testing::Eq;



class CommentValueTest_821 : public ::testing::Test {

protected:

    std::string testComment = "This is a test comment.";

    CommentValue commentValue;



    void SetUp() override {

        commentValue.read(testComment);

    }

};



TEST_F(CommentValueTest_821, CopyToBufferSameByteOrder_821) {

    byte buffer[100];

    size_t result = commentValue.copy(buffer, littleEndian);



    EXPECT_EQ(result, testComment.size());

    EXPECT_EQ(std::string(reinterpret_cast<char*>(buffer), result), testComment);

}



TEST_F(CommentValueTest_821, CopyToBufferDifferentByteOrder_821) {

    std::string unicodePrefix = "\x00\x00\xFE\xFF";

    std::string expectedUnicodeComment = unicodePrefix + "T\x00h\x00i\x00s\x00 \x00i\x00s\x00 \x00a\x00 \x00t\x00e\x00s\x00t\x00 \x00c\x00o\x00m\x00m\x00e\x00n\x00t\x00.";

    byte buffer[200];

    size_t result = commentValue.copy(buffer, bigEndian);



    EXPECT_EQ(result, expectedUnicodeComment.size());

    EXPECT_EQ(std::string(reinterpret_cast<char*>(buffer), result), expectedUnicodeComment);

}



TEST_F(CommentValueTest_821, CopyToBufferEmptyString_821) {

    CommentValue emptyComment;

    byte buffer[100];

    size_t result = emptyComment.copy(buffer, littleEndian);



    EXPECT_EQ(result, 0);

}



TEST_F(CommentValueTest_821, CopyToBufferBoundaryCondition_821) {

    std::string largeComment(LARGE_INT, 'A');

    CommentValue largeCommentValue;

    largeCommentValue.read(largeComment);

    byte buffer[LARGE_INT + 1];

    size_t result = largeCommentValue.copy(buffer, littleEndian);



    EXPECT_EQ(result, largeComment.size());

    EXPECT_EQ(std::string(reinterpret_cast<char*>(buffer), result), largeComment);

}



TEST_F(CommentValueTest_821, CharsetDetectionUnicode_821) {

    std::string unicodePrefix = "\x00\x00\xFE\xFF";

    std::string unicodeComment = unicodePrefix + "T\x00h\x00i\x00s\x00 \x00i\x00s\x00 \x00a\x00 \x00t\x00e\x00s\x00t\x00 \x00c\x00o\x00m\x00m\x00e\x00n\x00t\x00.";

    CommentValue unicodeCommentValue;

    unicodeCommentValue.read(unicodeComment);

    

    EXPECT_EQ(unicodeCommentValue.charsetId(), CharsetId::unicode);

}



TEST_F(CommentValueTest_821, CharsetDetectionAscii_821) {

    std::string asciiComment = "This is an ASCII comment.";

    CommentValue asciiCommentValue;

    asciiCommentValue.read(asciiComment);



    EXPECT_EQ(asciiCommentValue.charsetId(), CharsetId::ascii);

}
