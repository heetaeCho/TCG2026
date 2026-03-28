#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterCommentTest_44 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that writing a comment to a fresh emitter produces valid output
TEST_F(EmitterCommentTest_44, WriteCommentToFreshEmitter_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("This is a comment");
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("This is a comment"), std::string::npos);
}

// Test that the comment operator returns a reference to the same emitter
TEST_F(EmitterCommentTest_44, CommentOperatorReturnsSameEmitter_44) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = (emitter << YAML::Comment("test"));
    EXPECT_EQ(&ref, &emitter);
}

// Test writing an empty comment
TEST_F(EmitterCommentTest_44, WriteEmptyComment_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("");
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    // Should contain the comment marker '#'
    EXPECT_NE(output.find("#"), std::string::npos);
}

// Test writing a comment before a scalar
TEST_F(EmitterCommentTest_44, CommentBeforeScalar_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("before scalar");
    emitter << "hello";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("before scalar"), std::string::npos);
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test writing a comment after a scalar
TEST_F(EmitterCommentTest_44, CommentAfterScalar_44) {
    YAML::Emitter emitter;
    emitter << "hello";
    emitter << YAML::Comment("after scalar");
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
    EXPECT_NE(output.find("after scalar"), std::string::npos);
}

// Test writing multiple comments
TEST_F(EmitterCommentTest_44, MultipleComments_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("first comment");
    emitter << "value1";
    emitter << YAML::Comment("second comment");
    emitter << "value2";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("first comment"), std::string::npos);
    EXPECT_NE(output.find("second comment"), std::string::npos);
}

// Test comment in a sequence
TEST_F(EmitterCommentTest_44, CommentInSequence_44) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Comment("seq comment");
    emitter << "item1";
    emitter << "item2";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("seq comment"), std::string::npos);
    EXPECT_NE(output.find("item1"), std::string::npos);
}

// Test comment in a map
TEST_F(EmitterCommentTest_44, CommentInMap_44) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Comment("map comment");
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("map comment"), std::string::npos);
    EXPECT_NE(output.find("key1"), std::string::npos);
}

// Test comment with special characters
TEST_F(EmitterCommentTest_44, CommentWithSpecialCharacters_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("special: {chars} [here] # more");
    emitter << "value";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("special"), std::string::npos);
}

// Test comment output to stream
TEST_F(EmitterCommentTest_44, CommentToOutputStream_44) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::Comment("stream comment");
    emitter << "value";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = ss.str();
    EXPECT_NE(output.find("stream comment"), std::string::npos);
}

// Test comment contains hash character
TEST_F(EmitterCommentTest_44, CommentOutputContainsHash_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("my comment");
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("#"), std::string::npos);
}

// Test that emitter remains good after writing comment
TEST_F(EmitterCommentTest_44, EmitterGoodAfterComment_44) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
    emitter << YAML::Comment("check good");
    EXPECT_TRUE(emitter.good());
}

// Test size is non-zero after writing a comment
TEST_F(EmitterCommentTest_44, SizeNonZeroAfterComment_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("non-empty");
    EXPECT_GT(emitter.size(), 0u);
}

// Test comment before a flow sequence
TEST_F(EmitterCommentTest_44, CommentBeforeFlowSequence_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("before flow seq");
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << "a" << "b" << "c";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("before flow seq"), std::string::npos);
}

// Test comment before a flow map
TEST_F(EmitterCommentTest_44, CommentBeforeFlowMap_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("before flow map");
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("before flow map"), std::string::npos);
}

// Test comment with very long text
TEST_F(EmitterCommentTest_44, CommentWithLongText_44) {
    YAML::Emitter emitter;
    std::string longComment(1000, 'x');
    emitter << YAML::Comment(longComment);
    emitter << "value";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find(std::string(100, 'x')), std::string::npos);
}

// Test comment between map entries
TEST_F(EmitterCommentTest_44, CommentBetweenMapEntries_44) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::Comment("between entries");
    emitter << YAML::Key << "key2" << YAML::Value << "val2";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("between entries"), std::string::npos);
}

// Test comment between sequence items
TEST_F(EmitterCommentTest_44, CommentBetweenSequenceItems_44) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << YAML::Comment("between items");
    emitter << "item2";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("between items"), std::string::npos);
}

// Test that c_str output matches what is written to the stream
TEST_F(EmitterCommentTest_44, CStrMatchesStreamOutput_44) {
    std::stringstream ss;
    YAML::Emitter emitterStream(ss);
    emitterStream << YAML::Comment("match test");
    emitterStream << "value";

    YAML::Emitter emitterDefault;
    emitterDefault << YAML::Comment("match test");
    emitterDefault << "value";

    EXPECT_EQ(std::string(emitterDefault.c_str()), ss.str());
}

// Test a comment with newlines in the content
TEST_F(EmitterCommentTest_44, CommentWithNewlines_44) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("line1\nline2\nline3");
    emitter << "value";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("line1"), std::string::npos);
}

// Test pre-comment and post-comment indent settings with comment
TEST_F(EmitterCommentTest_44, CommentWithCustomIndent_44) {
    YAML::Emitter emitter;
    emitter.SetPreCommentIndent(4);
    emitter.SetPostCommentIndent(2);
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << YAML::Comment("indented comment");
    emitter << "item2";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("indented comment"), std::string::npos);
}
