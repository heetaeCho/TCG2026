// test/emittermanip_secondarytag_test.cpp
#include <gtest/gtest.h>

#include <string>

// Prefer the umbrella header if available in your codebase.
// If your build doesn't provide yaml-cpp/yaml.h, switch to the specific headers
// that define YAML::Emitter, YAML::BeginSeq/EndSeq, and YAML::SecondaryTag.
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/emittermanip.h>

namespace {

class SecondaryTagTest_18 : public ::testing::Test {};

TEST_F(SecondaryTagTest_18, EmitsNamedHandleTagInOutput_18) {
  YAML::Emitter out;
  out << YAML::SecondaryTag("foo") << "bar";

  const std::string s = out.c_str();
  // For a named-handle tag with empty handle, YAML tag syntax is typically "!<content>"
  // or "!content" depending on escaping. We only assert the observable presence.
  EXPECT_NE(s.find("!"), std::string::npos) << s;
  EXPECT_NE(s.find("foo"), std::string::npos) << s;
}

TEST_F(SecondaryTagTest_18, TagAppliesToNextEmittedNodeOnly_18) {
  YAML::Emitter out;
  out << YAML::BeginSeq;
  out << YAML::SecondaryTag("foo") << "a";
  out << "b";
  out << YAML::EndSeq;

  const std::string s = out.c_str();

  // We expect the tag marker/content to appear exactly once in the emitted YAML.
  // (i.e., it should not "stick" to subsequent nodes.)
  const auto first_bang = s.find("!");
  ASSERT_NE(first_bang, std::string::npos) << s;

  const auto second_bang = s.find("!", first_bang + 1);
  EXPECT_EQ(second_bang, std::string::npos) << s;

  EXPECT_NE(s.find("foo"), std::string::npos) << s;
}

TEST_F(SecondaryTagTest_18, EmptyContentDoesNotCrashAndProducesOutput_18) {
  YAML::Emitter out;
  EXPECT_NO_THROW(out << YAML::SecondaryTag("") << "x");

  const std::string s = out.c_str();
  EXPECT_FALSE(s.empty());
  // Some YAML emitters may still output a tag marker when content is empty.
  // We only require it to be usable and produce output.
}

TEST_F(SecondaryTagTest_18, SpecialCharactersInContentAreReflectedInOutput_18) {
  const std::string content = "a:b";
  YAML::Emitter out;
  out << YAML::SecondaryTag(content) << "v";

  const std::string s = out.c_str();
  EXPECT_NE(s.find("!"), std::string::npos) << s;

  // Tag may be emitted as "!a:b", "!<a:b>", or otherwise escaped, but the raw content
  // is commonly preserved as a substring.
  EXPECT_NE(s.find("a:b"), std::string::npos) << s;
}

}  // namespace
