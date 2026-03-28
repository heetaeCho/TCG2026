// File: ./TestProjects/yaml-cpp/test/convert_bool_decode_test_623.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

TEST(ConvertBoolDecodeTest_623, DecodesLowercaseTrueTokens_623) {
  const char* kTrueTokens[] = {"y", "yes", "true", "on"};
  for (const auto& token : kTrueTokens) {
    YAML::Node node(token);
    bool out = false;

    const bool ok = YAML::convert<bool>::decode(node, out);

    EXPECT_TRUE(ok) << "token: " << token;
    EXPECT_TRUE(out) << "token: " << token;
  }
}

TEST(ConvertBoolDecodeTest_623, DecodesLowercaseFalseTokens_623) {
  const char* kFalseTokens[] = {"n", "no", "false", "off"};
  for (const auto& token : kFalseTokens) {
    YAML::Node node(token);
    bool out = true;

    const bool ok = YAML::convert<bool>::decode(node, out);

    EXPECT_TRUE(ok) << "token: " << token;
    EXPECT_FALSE(out) << "token: " << token;
  }
}

TEST(ConvertBoolDecodeTest_623, DecodesUppercaseTrueAndFalseTokens_623) {
  struct Case {
    const char* token;
    bool expected;
  };
  const Case kCases[] = {
      {"Y", true},   {"YES", true},   {"TRUE", true}, {"ON", true},
      {"N", false},  {"NO", false},   {"FALSE", false}, {"OFF", false},
  };

  for (const auto& c : kCases) {
    YAML::Node node(c.token);
    bool out = !c.expected;

    const bool ok = YAML::convert<bool>::decode(node, out);

    EXPECT_TRUE(ok) << "token: " << c.token;
    EXPECT_EQ(out, c.expected) << "token: " << c.token;
  }
}

TEST(ConvertBoolDecodeTest_623, DecodesCapitalizedTrueAndFalseTokens_623) {
  struct Case {
    const char* token;
    bool expected;
  };
  const Case kCases[] = {
      {"Y", true},     // single-letter "Y"/"N" are covered in other tests too, keep minimal here
      {"Yes", true},   {"True", true}, {"On", true},
      {"N", false},
      {"No", false},   {"False", false}, {"Off", false},
  };

  for (const auto& c : kCases) {
    YAML::Node node(c.token);
    bool out = !c.expected;

    const bool ok = YAML::convert<bool>::decode(node, out);

    EXPECT_TRUE(ok) << "token: " << c.token;
    EXPECT_EQ(out, c.expected) << "token: " << c.token;
  }
}

TEST(ConvertBoolDecodeTest_623, ReturnsFalseForInvalidScalar_623) {
  const char* kInvalid[] = {"maybe", "0", "1", "enabled", "disabled", ""};
  for (const auto& token : kInvalid) {
    YAML::Node node(token);
    bool out = false;

    const bool ok = YAML::convert<bool>::decode(node, out);

    EXPECT_FALSE(ok) << "token: " << token;
  }
}

TEST(ConvertBoolDecodeTest_623, ReturnsFalseForMixedCaseScalar_623) {
  // These are intentionally "mixed-case" spellings, which are commonly rejected by "flexible case"
  // rules (e.g., only allow lower/upper/capitalized forms).
  const char* kMixedCase[] = {"tRuE", "yEs", "oFf", "nO"};
  for (const auto& token : kMixedCase) {
    YAML::Node node(token);
    bool out = false;

    const bool ok = YAML::convert<bool>::decode(node, out);

    EXPECT_FALSE(ok) << "token: " << token;
  }
}

TEST(ConvertBoolDecodeTest_623, ReturnsFalseForScalarWithWhitespace_623) {
  const char* kWhitespacey[] = {" true", "true ", " yes", "no ", "\ttrue", "false\n"};
  for (const auto& token : kWhitespacey) {
    YAML::Node node(token);
    bool out = false;

    const bool ok = YAML::convert<bool>::decode(node, out);

    EXPECT_FALSE(ok) << "token: " << token;
  }
}

TEST(ConvertBoolDecodeTest_623, ReturnsFalseForNonScalarNodes_623) {
  {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back("true");
    bool out = false;
    EXPECT_FALSE(YAML::convert<bool>::decode(seq, out));
  }
  {
    YAML::Node map(YAML::NodeType::Map);
    map["k"] = "true";
    bool out = false;
    EXPECT_FALSE(YAML::convert<bool>::decode(map, out));
  }
  {
    YAML::Node nullNode;  // default-constructed is not a scalar
    bool out = false;
    EXPECT_FALSE(YAML::convert<bool>::decode(nullNode, out));
  }
}

}  // namespace