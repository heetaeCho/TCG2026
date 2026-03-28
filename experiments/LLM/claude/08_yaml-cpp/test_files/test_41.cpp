#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterAliasTest_41 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that writing an alias to the emitter produces valid output
TEST_F(EmitterAliasTest_41, WriteAliasBasic_41) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "anchor_key";
    emitter << YAML::Value << YAML::Anchor("myanchor") << "anchor_value";
    emitter << YAML::Key << "alias_key";
    emitter << YAML::Value << YAML::Alias("myanchor");
    emitter << YAML::EndMap;

    EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*myanchor"), std::string::npos);
}

// Test that the operator<< for _Alias returns a reference to the emitter
TEST_F(EmitterAliasTest_41, OperatorReturnsEmitterReference_41) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = (emitter << YAML::Alias("test"));
    EXPECT_EQ(&ref, &emitter);
}

// Test writing alias with a simple content string
TEST_F(EmitterAliasTest_41, WriteAliasSimpleContent_41) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("simple");
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*simple"), std::string::npos);
}

// Test writing alias to an ostream
TEST_F(EmitterAliasTest_41, WriteAliasToStream_41) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << YAML::Anchor("anc") << "v";
    emitter << YAML::Key << "k2" << YAML::Value << YAML::Alias("anc");
    emitter << YAML::EndMap;

    EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
    std::string output = ss.str();
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// Test alias in a sequence
TEST_F(EmitterAliasTest_41, WriteAliasInSequence_41) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("item") << "value";
    emitter << YAML::Alias("item");
    emitter << YAML::EndSeq;

    EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*item"), std::string::npos);
}

// Test alias with content containing alphanumeric characters
TEST_F(EmitterAliasTest_41, WriteAliasAlphanumericContent_41) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("anchor123");
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*anchor123"), std::string::npos);
}

// Test that emitter is still good after writing an alias
TEST_F(EmitterAliasTest_41, EmitterGoodAfterAlias_41) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
    emitter << YAML::Alias("myalias");
    // The emitter should still be in good state after writing a valid alias
    EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
}

// Test size is non-zero after writing alias
TEST_F(EmitterAliasTest_41, SizeNonZeroAfterAlias_41) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("test");
    EXPECT_GT(emitter.size(), 0u);
}

// Test alias as a map key
TEST_F(EmitterAliasTest_41, WriteAliasAsMapKey_41) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << YAML::Anchor("keyanchor") << "original_key";
    emitter << YAML::Value << "val1";
    emitter << YAML::Key << YAML::Alias("keyanchor");
    emitter << YAML::Value << "val2";
    emitter << YAML::EndMap;

    // Check it produces output (may or may not be valid YAML depending on implementation)
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*keyanchor"), std::string::npos);
}

// Test writing alias with a single character content
TEST_F(EmitterAliasTest_41, WriteAliasSingleCharContent_41) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("a");
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*a"), std::string::npos);
}

// Test writing alias in flow sequence
TEST_F(EmitterAliasTest_41, WriteAliasInFlowSequence_41) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << YAML::Anchor("flowitem") << "val";
    emitter << YAML::Alias("flowitem");
    emitter << YAML::EndSeq;

    EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*flowitem"), std::string::npos);
}

// Test writing alias in flow map
TEST_F(EmitterAliasTest_41, WriteAliasInFlowMap_41) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "k1" << YAML::Value << YAML::Anchor("fm") << "v1";
    emitter << YAML::Key << "k2" << YAML::Value << YAML::Alias("fm");
    emitter << YAML::EndMap;

    EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*fm"), std::string::npos);
}

// Test that the _Alias struct holds the correct content
TEST_F(EmitterAliasTest_41, AliasStructContent_41) {
    YAML::_Alias alias("testcontent");
    EXPECT_EQ(alias.content, "testcontent");
}

// Test writing multiple aliases
TEST_F(EmitterAliasTest_41, WriteMultipleAliases_41) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("first") << "val1";
    emitter << YAML::Anchor("second") << "val2";
    emitter << YAML::Alias("first");
    emitter << YAML::Alias("second");
    emitter << YAML::EndSeq;

    EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*first"), std::string::npos);
    EXPECT_NE(output.find("*second"), std::string::npos);
}

// Test c_str returns non-null after writing alias
TEST_F(EmitterAliasTest_41, CStrNonNullAfterAlias_41) {
    YAML::Emitter emitter;
    emitter << YAML::Alias("check");
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Test writing alias with longer content string
TEST_F(EmitterAliasTest_41, WriteAliasLongContent_41) {
    YAML::Emitter emitter;
    std::string longName = "this_is_a_relatively_long_anchor_name_for_testing";
    emitter << YAML::Alias(longName);
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*" + longName), std::string::npos);
}
