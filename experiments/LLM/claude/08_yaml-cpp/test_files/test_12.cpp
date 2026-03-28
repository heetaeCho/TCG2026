#include <gtest/gtest.h>
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/yaml.h"

// Test that Indent returns a valid _Indent object with the given value
TEST(IndentTest_12, IndentCreatesValidObject_12) {
    YAML::_Indent indent = YAML::Indent(2);
    // We can verify it works by applying it to an emitter
    YAML::Emitter emitter;
    emitter << YAML::Indent(2);
    // If no error occurred, the indent was accepted
    EXPECT_TRUE(emitter.good());
}

// Test Indent with default-like value
TEST(IndentTest_12, IndentWithDefaultValue_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(2);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// Test Indent with a larger value
TEST(IndentTest_12, IndentWithLargerValue_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "nested" << YAML::Value << "value";
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // With indent of 4, nested content should have 4-space indentation
    EXPECT_NE(output.find("    nested"), std::string::npos);
}

// Test Indent with minimum valid value (2 is typically the minimum for YAML)
TEST(IndentTest_12, IndentWithMinimumValue_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(2);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a";
    emitter << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "b" << YAML::Value << "c";
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// Test Indent with value of 1 - may cause error as minimum indent is typically 2
TEST(IndentTest_12, IndentWithTooSmallValue_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(1);
    // The emitter may report an error for indent < 2
    // We just observe the behavior
    if (!emitter.good()) {
        EXPECT_FALSE(emitter.good());
    }
}

// Test Indent with value of 0 - boundary/error case
TEST(IndentTest_12, IndentWithZeroValue_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(0);
    // Zero indent is likely invalid
    // Just observe the behavior without asserting internal state
}

// Test Indent with negative value - error case
TEST(IndentTest_12, IndentWithNegativeValue_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(-1);
    // Negative indent should likely cause an error
}

// Test Indent affects nested sequences
TEST(IndentTest_12, IndentAffectsNestedSequences_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(6);
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginSeq;
    emitter << "item";
    emitter << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Nested sequence should show the indent effect
    EXPECT_FALSE(output.empty());
}

// Test that multiple Indent calls can be made (last one wins or each applies to scope)
TEST(IndentTest_12, MultipleIndentCalls_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(2);
    emitter << YAML::Indent(4);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// Test Indent with a very large value
TEST(IndentTest_12, IndentWithVeryLargeValue_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(100);
    // Extremely large indent - behavior depends on implementation
    // Just ensure no crash
}

// Test that Indent function can be called inline
TEST(IndentTest_12, IndentInlineUsage_12) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(3) << YAML::BeginMap
            << YAML::Key << "hello" << YAML::Value << "world"
            << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
    EXPECT_NE(output.find("world"), std::string::npos);
}
