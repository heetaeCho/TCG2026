#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace YAML {

class EmitterCommentTest_541 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Writing a simple comment to the emitter
TEST_F(EmitterCommentTest_541, WriteSimpleComment_541) {
    Emitter emitter;
    ASSERT_TRUE(emitter.good());
    
    emitter << Comment("this is a comment");
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// Test: Comment output contains the '#' character
TEST_F(EmitterCommentTest_541, CommentContainsHashSymbol_541) {
    Emitter emitter;
    emitter << Comment("hello");
    
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("#"), std::string::npos);
}

// Test: Writing an empty comment
TEST_F(EmitterCommentTest_541, WriteEmptyComment_541) {
    Emitter emitter;
    ASSERT_TRUE(emitter.good());
    
    emitter << Comment("");
    
    EXPECT_TRUE(emitter.good());
}

// Test: Writing a comment with spaces
TEST_F(EmitterCommentTest_541, WriteCommentWithSpaces_541) {
    Emitter emitter;
    emitter << Comment("  spaced comment  ");
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("spaced comment"), std::string::npos);
}

// Test: Writing a comment after a scalar value
TEST_F(EmitterCommentTest_541, WriteCommentAfterScalar_541) {
    Emitter emitter;
    emitter << "value";
    emitter << Comment("a comment after value");
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("value"), std::string::npos);
    EXPECT_NE(output.find("a comment after value"), std::string::npos);
}

// Test: Writing multiple comments
TEST_F(EmitterCommentTest_541, WriteMultipleComments_541) {
    Emitter emitter;
    emitter << Comment("first comment");
    emitter << Comment("second comment");
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("first comment"), std::string::npos);
    EXPECT_NE(output.find("second comment"), std::string::npos);
}

// Test: Writing comment to a stream-backed emitter
TEST_F(EmitterCommentTest_541, WriteCommentToStream_541) {
    std::stringstream ss;
    Emitter emitter(ss);
    
    emitter << Comment("stream comment");
    
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("stream comment"), std::string::npos);
}

// Test: Comment in a sequence
TEST_F(EmitterCommentTest_541, WriteCommentInSequence_541) {
    Emitter emitter;
    emitter << BeginSeq;
    emitter << "item1";
    emitter << Comment("comment in seq");
    emitter << "item2";
    emitter << EndSeq;
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("comment in seq"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
}

// Test: Comment in a map
TEST_F(EmitterCommentTest_541, WriteCommentInMap_541) {
    Emitter emitter;
    emitter << BeginMap;
    emitter << Key << "key1" << Value << "val1";
    emitter << Comment("map comment");
    emitter << Key << "key2" << Value << "val2";
    emitter << EndMap;
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("map comment"), std::string::npos);
}

// Test: Write returns reference to same emitter (chaining)
TEST_F(EmitterCommentTest_541, WriteCommentReturnsSelf_541) {
    Emitter emitter;
    Emitter& ref = (emitter << Comment("chained"));
    
    EXPECT_EQ(&ref, &emitter);
}

// Test: Comment with special characters
TEST_F(EmitterCommentTest_541, WriteCommentWithSpecialCharacters_541) {
    Emitter emitter;
    emitter << Comment("special: !@#$%^&*()");
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("special"), std::string::npos);
}

// Test: Comment with newline characters (multiline)
TEST_F(EmitterCommentTest_541, WriteCommentWithNewlines_541) {
    Emitter emitter;
    emitter << Comment("line1\nline2");
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("line1"), std::string::npos);
    EXPECT_NE(output.find("line2"), std::string::npos);
}

// Test: SetPreCommentIndent affects comment output
TEST_F(EmitterCommentTest_541, SetPreCommentIndentAffectsOutput_541) {
    Emitter emitter;
    emitter.SetPreCommentIndent(4);
    emitter << "value" << Comment("indented comment");
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("indented comment"), std::string::npos);
}

// Test: SetPostCommentIndent affects comment output
TEST_F(EmitterCommentTest_541, SetPostCommentIndentAffectsOutput_541) {
    Emitter emitter;
    emitter.SetPostCommentIndent(3);
    emitter << Comment("post indent comment");
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("post indent comment"), std::string::npos);
}

// Test: Emitter size increases after writing comment
TEST_F(EmitterCommentTest_541, SizeIncreasesAfterComment_541) {
    Emitter emitter;
    std::size_t initialSize = emitter.size();
    emitter << Comment("some comment");
    
    EXPECT_GT(emitter.size(), initialSize);
}

// Test: Writing a very long comment
TEST_F(EmitterCommentTest_541, WriteVeryLongComment_541) {
    Emitter emitter;
    std::string longComment(1000, 'x');
    emitter << Comment(longComment);
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find(std::string(100, 'x')), std::string::npos);
}

// Test: Comment before a document
TEST_F(EmitterCommentTest_541, WriteCommentBeforeDocument_541) {
    Emitter emitter;
    emitter << Comment("doc comment");
    emitter << BeginDoc;
    emitter << "value";
    emitter << EndDoc;
    
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("doc comment"), std::string::npos);
}

// Test: Emitter good state is maintained through comment writes
TEST_F(EmitterCommentTest_541, GoodStateAfterMultipleComments_541) {
    Emitter emitter;
    for (int i = 0; i < 10; ++i) {
        emitter << Comment("comment " + std::to_string(i));
    }
    EXPECT_TRUE(emitter.good());
}

}  // namespace YAML
