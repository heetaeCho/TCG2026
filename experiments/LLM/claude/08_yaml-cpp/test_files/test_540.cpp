#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterWriteTagTest_540 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Writing a verbatim tag on a fresh emitter
TEST_F(EmitterWriteTagTest_540, WriteVerbatimTag_540) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// Test: Writing a tag followed by a scalar value
TEST_F(EmitterWriteTagTest_540, WriteTagWithScalar_540) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!foo") << "bar";
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!foo"), std::string::npos);
    EXPECT_NE(output.find("bar"), std::string::npos);
}

// Test: Writing two consecutive tags should cause an error (duplicate tag)
TEST_F(EmitterWriteTagTest_540, WriteDuplicateTagCausesError_540) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!foo");
    emitter << YAML::VerbatimTag("!bar");
    EXPECT_FALSE(emitter.good());
    std::string err = emitter.GetLastError();
    EXPECT_NE(err.find("invalid tag"), std::string::npos);
}

// Test: After error, Write returns the emitter (chain is safe)
TEST_F(EmitterWriteTagTest_540, WriteAfterErrorReturnsSelf_540) {
    YAML::Emitter emitter;
    // Force an error by writing duplicate tags
    emitter << YAML::VerbatimTag("!foo");
    emitter << YAML::VerbatimTag("!bar");
    EXPECT_FALSE(emitter.good());
    // Writing another tag after error should still return without crash
    emitter << YAML::VerbatimTag("!baz");
    EXPECT_FALSE(emitter.good());
}

// Test: Writing a local tag (primary handle)
TEST_F(EmitterWriteTagTest_540, WriteLocalTag_540) {
    YAML::Emitter emitter;
    emitter << YAML::LocalTag("mytype") << "value";
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("mytype"), std::string::npos);
}

// Test: Writing a secondary tag with prefix
TEST_F(EmitterWriteTagTest_540, WriteSecondaryTag_540) {
    YAML::Emitter emitter;
    emitter << YAML::SecondaryTag("int") << "42";
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("int"), std::string::npos);
}

// Test: Writing tag in a sequence context
TEST_F(EmitterWriteTagTest_540, WriteTagInSequence_540) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::VerbatimTag("!item") << "value1";
    emitter << "value2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!item"), std::string::npos);
}

// Test: Writing tag in a map context
TEST_F(EmitterWriteTagTest_540, WriteTagInMap_540) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << YAML::VerbatimTag("!val") << "tagged_value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!val"), std::string::npos);
    EXPECT_NE(output.find("tagged_value"), std::string::npos);
}

// Test: Emitter with stream - tag is written to the ostream
TEST_F(EmitterWriteTagTest_540, WriteTagToStream_540) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::VerbatimTag("!custom") << "data";
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = ss.str();
    EXPECT_NE(output.find("!custom"), std::string::npos);
    EXPECT_NE(output.find("data"), std::string::npos);
}

// Test: Fresh emitter is in good state
TEST_F(EmitterWriteTagTest_540, FreshEmitterIsGood_540) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

// Test: Size returns non-zero after writing tag and scalar
TEST_F(EmitterWriteTagTest_540, SizeAfterWriteTag_540) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!t") << "v";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: c_str returns non-null after writing tag
TEST_F(EmitterWriteTagTest_540, CStrNonNullAfterTag_540) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!t") << "v";
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Test: Writing a tag with empty content for verbatim tag
TEST_F(EmitterWriteTagTest_540, WriteVerbatimTagEmptyContent_540) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("") << "value";
    // Empty verbatim tag may or may not be valid depending on implementation
    // Just verify it doesn't crash; check good() state
    // If not good, error should mention invalid tag
    if (!emitter.good()) {
        std::string err = emitter.GetLastError();
        EXPECT_NE(err.find("invalid tag"), std::string::npos);
    }
}

// Test: Writing tag on a map key
TEST_F(EmitterWriteTagTest_540, WriteTagOnMapKey_540) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << YAML::VerbatimTag("!keytype") << "mykey";
    emitter << YAML::Value << "myval";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!keytype"), std::string::npos);
}

// Test: Writing a local tag with special characters
TEST_F(EmitterWriteTagTest_540, WriteLocalTagSpecialChars_540) {
    YAML::Emitter emitter;
    emitter << YAML::LocalTag("my-type.v1") << "value";
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("my-type.v1"), std::string::npos);
}

// Test: Tag followed by a null value
TEST_F(EmitterWriteTagTest_540, WriteTagWithNull_540) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!nullable") << YAML::Null;
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!nullable"), std::string::npos);
}

// Test: Multiple tagged scalars in a sequence
TEST_F(EmitterWriteTagTest_540, MultipleTaggedScalarsInSequence_540) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::VerbatimTag("!a") << "val1";
    emitter << YAML::VerbatimTag("!b") << "val2";
    emitter << YAML::VerbatimTag("!c") << "val3";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("!a"), std::string::npos);
    EXPECT_NE(output.find("!b"), std::string::npos);
    EXPECT_NE(output.find("!c"), std::string::npos);
}

// Test: Chaining - Write returns reference to the emitter
TEST_F(EmitterWriteTagTest_540, WriteChainingReturnsEmitter_540) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = (emitter << YAML::VerbatimTag("!t"));
    EXPECT_EQ(&ref, &emitter);
}
