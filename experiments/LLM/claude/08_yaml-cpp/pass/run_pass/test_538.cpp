#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterAliasTest_538 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Writing a simple alias produces valid output
TEST_F(EmitterAliasTest_538, WriteSimpleAlias_538) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("myalias");
    ASSERT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*myalias"), std::string::npos);
}

// Test: Emitter remains in good state after writing alias
TEST_F(EmitterAliasTest_538, EmitterGoodAfterAlias_538) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("test");
    EXPECT_TRUE(emitter.good());
}

// Test: Writing alias with anchor set should produce error
TEST_F(EmitterAliasTest_538, AliasWithAnchorIsInvalid_538) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anc") << YAML::Alias("test");
    EXPECT_FALSE(emitter.good());
    EXPECT_EQ(emitter.GetLastError(), "invalid alias");
}

// Test: Writing alias with tag set should produce error
TEST_F(EmitterAliasTest_538, AliasWithTagIsInvalid_538) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("!foo") << YAML::Alias("test");
    EXPECT_FALSE(emitter.good());
    EXPECT_EQ(emitter.GetLastError(), "invalid alias");
}

// Test: Alias output to stream
TEST_F(EmitterAliasTest_538, WriteAliasToStream_538) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::Alias("ref");
    ASSERT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("*ref"), std::string::npos);
}

// Test: Alias in a sequence
TEST_F(EmitterAliasTest_538, AliasInSequence_538) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("item") << "hello";
    emitter << YAML::Alias("item");
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*item"), std::string::npos);
}

// Test: Alias in a map value
TEST_F(EmitterAliasTest_538, AliasInMapValue_538) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "original" << YAML::Value << YAML::Anchor("val") << "data";
    emitter << YAML::Key << "copy" << YAML::Value << YAML::Alias("val");
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*val"), std::string::npos);
}

// Test: Alias as map key
TEST_F(EmitterAliasTest_538, AliasAsMapKey_538) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << YAML::Alias("key") << YAML::Value << "value";
    emitter << YAML::EndMap;
    // This should work if state allows it
    // We just test it doesn't crash - validity depends on implementation
    // At minimum the alias text should appear if good
    if (emitter.good()) {
        std::string output(emitter.c_str());
        EXPECT_NE(output.find("*key"), std::string::npos);
    }
}

// Test: size() returns non-zero after writing alias
TEST_F(EmitterAliasTest_538, SizeNonZeroAfterAlias_538) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("ref");
    ASSERT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test: c_str() is not null after writing alias
TEST_F(EmitterAliasTest_538, CStrNotNullAfterAlias_538) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("myref");
    ASSERT_TRUE(emitter.good());
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Test: Writing to emitter after error does nothing (emitter stays bad)
TEST_F(EmitterAliasTest_538, WriteAfterErrorStaysBad_538) {
    YAML::Emitter emitter;
    // Force error: alias with anchor
    emitter << YAML::Anchor("a") << YAML::Alias("b");
    ASSERT_FALSE(emitter.good());
    // Try writing more
    emitter << "something";
    EXPECT_FALSE(emitter.good());
}

// Test: Alias with alphanumeric content
TEST_F(EmitterAliasTest_538, AliasAlphanumericContent_538) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("abc123");
    ASSERT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*abc123"), std::string::npos);
}

// Test: Multiple aliases in a sequence
TEST_F(EmitterAliasTest_538, MultipleAliasesInSequence_538) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Alias("a");
    emitter << YAML::Alias("b");
    emitter << YAML::Alias("c");
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*a"), std::string::npos);
    EXPECT_NE(output.find("*b"), std::string::npos);
    EXPECT_NE(output.find("*c"), std::string::npos);
}

// Test: Alias in flow sequence
TEST_F(EmitterAliasTest_538, AliasInFlowSequence_538) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << YAML::Alias("x");
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*x"), std::string::npos);
}

// Test: Alias with single character name
TEST_F(EmitterAliasTest_538, AliasSingleChar_538) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("a");
    ASSERT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*a"), std::string::npos);
}

// Test: Emitter error message is "invalid alias" when anchor+alias
TEST_F(EmitterAliasTest_538, ErrorMessageInvalidAlias_538) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor") << YAML::Alias("alias");
    EXPECT_FALSE(emitter.good());
    std::string err = emitter.GetLastError();
    EXPECT_NE(err.find("invalid alias"), std::string::npos);
}
