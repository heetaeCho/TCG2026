// File: ./TestProjects/yaml-cpp/test/parse_loadall_string_wrapper_test_582.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

namespace {

class LoadAllStringWrapperTest_582 : public ::testing::Test {
protected:
  static std::vector<YAML::Node> LoadAllViaStream(const std::string& input) {
    std::stringstream ss(input);
    return YAML::LoadAll(ss);  // Uses the istream/stream overload in yaml-cpp.
  }

  static std::vector<YAML::Node> LoadAllViaString(const std::string& input) {
    return YAML::LoadAll(input);  // The wrapper under test.
  }

  static void ExpectSameNodesByDump(const std::string& input) {
    const auto from_stream = LoadAllViaStream(input);
    const auto from_string = LoadAllViaString(input);

    ASSERT_EQ(from_stream.size(), from_string.size())
        << "LoadAll(string) should produce the same number of documents as LoadAll(stream).";

    for (size_t i = 0; i < from_stream.size(); ++i) {
      // Compare observable results via YAML serialization (black-box friendly).
      EXPECT_EQ(YAML::Dump(from_stream[i]), YAML::Dump(from_string[i]))
          << "Mismatch at document index " << i;
    }
  }

  static void ExpectBothThrowYamlException(const std::string& input) {
    // We intentionally only assert the common base class (YAML::Exception),
    // avoiding assumptions about exact derived exception types.
    EXPECT_THROW((void)LoadAllViaStream(input), YAML::Exception);
    EXPECT_THROW((void)LoadAllViaString(input), YAML::Exception);
  }
};

}  // namespace

TEST_F(LoadAllStringWrapperTest_582, SingleDocumentMappingMatchesStream_582) {
  const std::string input =
      "a: 1\n"
      "b: test\n"
      "c:\n"
      "  - 10\n"
      "  - 20\n";
  ExpectSameNodesByDump(input);
}

TEST_F(LoadAllStringWrapperTest_582, MultipleDocumentsSeparatedByMarkerMatchesStream_582) {
  const std::string input =
      "a: 1\n"
      "---\n"
      "b: 2\n"
      "---\n"
      "- x\n"
      "- y\n";
  ExpectSameNodesByDump(input);
}

TEST_F(LoadAllStringWrapperTest_582, LeadingAndTrailingWhitespaceMatchesStream_582) {
  const std::string input =
      "\n\n  a: 1  \n"
      "  b: 2\n\n";
  ExpectSameNodesByDump(input);
}

TEST_F(LoadAllStringWrapperTest_582, WindowsLineEndingsMatchesStream_582) {
  const std::string input = "a: 1\r\nb: 2\r\n";
  ExpectSameNodesByDump(input);
}

TEST_F(LoadAllStringWrapperTest_582, EmptyInputMatchesStream_582) {
  const std::string input = "";
  ExpectSameNodesByDump(input);
}

TEST_F(LoadAllStringWrapperTest_582, OnlyWhitespaceInputMatchesStream_582) {
  const std::string input = " \n\t\r\n  \n";
  ExpectSameNodesByDump(input);
}

TEST_F(LoadAllStringWrapperTest_582, LargeScalarContentMatchesStream_582) {
  std::string big(10000, 'x');
  const std::string input = "key: " + big + "\n";
  ExpectSameNodesByDump(input);
}

TEST_F(LoadAllStringWrapperTest_582, UnicodeContentMatchesStream_582) {
  const std::string input =
      "greeting: \"안녕하세요\"\n"
      "emoji: \"😀\"\n";
  ExpectSameNodesByDump(input);
}

TEST_F(LoadAllStringWrapperTest_582, InvalidYamlThrowsYamlExceptionLikeStream_582) {
  // Missing closing bracket.
  const std::string input = "a: [1, 2\n";
  ExpectBothThrowYamlException(input);
}

TEST_F(LoadAllStringWrapperTest_582, ClearlyInvalidSyntaxThrowsYamlExceptionLikeStream_582) {
  // Bad indentation / structure.
  const std::string input =
      "a:\n"
      "  - 1\n"
      "   - 2\n";
  ExpectBothThrowYamlException(input);
}