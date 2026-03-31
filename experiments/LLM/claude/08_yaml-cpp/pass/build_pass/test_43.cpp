#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTagTest_43 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Writing a tag to a scalar value produces valid output
TEST_F(EmitterTagTest_43, WriteTagWithScalar_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!foo") << "bar";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
    // The output should contain the tag
    EXPECT_NE(output.find("!foo"), std::string::npos);
    EXPECT_NE(output.find("bar"), std::string::npos);
}

// Test: Writing a tag in a sequence
TEST_F(EmitterTagTest_43, WriteTagInSequence_43) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::VerbatimTag("!int") << 42;
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!int"), std::string::npos);
}

// Test: Writing a tag in a map key
TEST_F(EmitterTagTest_43, WriteTagInMapKey_43) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << YAML::VerbatimTag("!str") << "key";
    emitter << YAML::Value << "value";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!str"), std::string::npos);
    EXPECT_NE(output.find("key"), std::string::npos);
}

// Test: Writing a tag in a map value
TEST_F(EmitterTagTest_43, WriteTagInMapValue_43) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::VerbatimTag("!custom") << "value";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!custom"), std::string::npos);
}

// Test: Emitter is good after writing tag
TEST_F(EmitterTagTest_43, EmitterGoodAfterTag_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!tag") << "value";
    EXPECT_TRUE(emitter.good());
}

// Test: Writing tag to a stream-based emitter
TEST_F(EmitterTagTest_43, WriteTagToStream_43) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::VerbatimTag("!mytag") << "hello";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = ss.str();
    EXPECT_NE(output.find("!mytag"), std::string::npos);
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test: Tag with empty content string
TEST_F(EmitterTagTest_43, WriteTagWithEmptyString_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!empty") << "";
    // Should still be valid
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!empty"), std::string::npos);
}

// Test: Multiple tags in a sequence
TEST_F(EmitterTagTest_43, MultipleTagsInSequence_43) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::VerbatimTag("!first") << "a";
    emitter << YAML::VerbatimTag("!second") << "b";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!first"), std::string::npos);
    EXPECT_NE(output.find("!second"), std::string::npos);
}

// Test: VerbatimTag produces verbatim tag output
TEST_F(EmitterTagTest_43, VerbatimTagOutput_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    // Verbatim tags typically produce !<...> syntax
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// Test: Tag before a null value
TEST_F(EmitterTagTest_43, WriteTagBeforeNull_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!null") << YAML::Null;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!null"), std::string::npos);
}

// Test: Tag before a boolean value
TEST_F(EmitterTagTest_43, WriteTagBeforeBool_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!bool") << true;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!bool"), std::string::npos);
}

// Test: Tag before a sequence (collection tag)
TEST_F(EmitterTagTest_43, WriteTagBeforeSequence_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!seq") << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!seq"), std::string::npos);
}

// Test: Tag before a map (collection tag)
TEST_F(EmitterTagTest_43, WriteTagBeforeMap_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!map") << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!map"), std::string::npos);
}

// Test: LocalTag (secondary handle-based tag)
TEST_F(EmitterTagTest_43, WriteLocalTag_43) {
    YAML::Emitter emitter;
    emitter << YAML::LocalTag("foo") << "bar";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("foo"), std::string::npos);
}

// Test: SecondaryTag
TEST_F(EmitterTagTest_43, WriteSecondaryTag_43) {
    YAML::Emitter emitter;
    emitter << YAML::SecondaryTag("str") << "hello";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("str"), std::string::npos);
}

// Test: size returns non-zero after writing tag and value
TEST_F(EmitterTagTest_43, SizeAfterTagWrite_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!t") << "v";
    ASSERT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: c_str returns non-null after writing tag and value
TEST_F(EmitterTagTest_43, CStrAfterTagWrite_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!t") << "v";
    ASSERT_TRUE(emitter.good());
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Test: Tag with special characters in tag URI
TEST_F(EmitterTagTest_43, WriteTagWithSpecialCharacters_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:example.com,2023:type/subtype") << "data";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:example.com,2023:type/subtype"), std::string::npos);
}

// Test: Tag followed by integer value
TEST_F(EmitterTagTest_43, WriteTagBeforeInteger_43) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!int") << 123;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!int"), std::string::npos);
    EXPECT_NE(output.find("123"), std::string::npos);
}

// Test: Operator<< with _Tag returns reference to the same emitter
TEST_F(EmitterTagTest_43, OperatorReturnsSameEmitter_43) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = (emitter << YAML::VerbatimTag("!tag"));
    EXPECT_EQ(&ref, &emitter);
}

// Test: Flow sequence with tags
TEST_F(EmitterTagTest_43, WriteTagInFlowSequence_43) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << YAML::VerbatimTag("!a") << "x";
    emitter << YAML::VerbatimTag("!b") << "y";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!a"), std::string::npos);
    EXPECT_NE(output.find("!b"), std::string::npos);
}

// Test: Flow map with tags
TEST_F(EmitterTagTest_43, WriteTagInFlowMap_43) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << YAML::VerbatimTag("!k") << "key";
    emitter << YAML::Value << YAML::VerbatimTag("!v") << "val";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!k"), std::string::npos);
    EXPECT_NE(output.find("!v"), std::string::npos);
}
