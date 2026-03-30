// File: ./TestProjects/yaml-cpp/test/emitterutils_writetag_test_636.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

// Forward declaration (treat implementation as black box; no internal headers required)
namespace YAML {
namespace Utils {
bool WriteTag(ostream_wrapper& out, const std::string& str, bool verbatim);
}  // namespace Utils
}  // namespace YAML

namespace {

class WriteTagTest_636 : public ::testing::Test {
 protected:
  static std::string RunWriteTagAndGetOutput(const std::string& tag, bool verbatim, bool* ok_out = nullptr) {
    std::stringstream ss;
    YAML::ostream_wrapper out(ss);

    const bool ok = YAML::Utils::WriteTag(out, tag, verbatim);
    if (ok_out) *ok_out = ok;

    return ss.str();
  }
};

TEST_F(WriteTagTest_636, NonVerbatimValidSimpleTag_WritesBangPlusTag_636) {
  bool ok = false;
  const std::string out = RunWriteTagAndGetOutput("tag", /*verbatim=*/false, &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "!tag");
}

TEST_F(WriteTagTest_636, VerbatimValidUriLike_WritesBangAngleBracketsPlusTag_636) {
  bool ok = false;
  const std::string input = "http://example.com";
  const std::string out = RunWriteTagAndGetOutput(input, /*verbatim=*/true, &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "!<" + input + ">");
}

TEST_F(WriteTagTest_636, NonVerbatimEmptyString_WritesOnlyBangAndReturnsTrue_636) {
  bool ok = false;
  const std::string out = RunWriteTagAndGetOutput("", /*verbatim=*/false, &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "!");
}

TEST_F(WriteTagTest_636, VerbatimEmptyString_WritesBangAngleAndCloseAndReturnsTrue_636) {
  bool ok = false;
  const std::string out = RunWriteTagAndGetOutput("", /*verbatim=*/true, &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "!<>");
}

TEST_F(WriteTagTest_636, NonVerbatimInvalidCharacters_ReturnsFalseAndWritesPrefix_636) {
  bool ok = true;
  const std::string input = std::string("bad") + '\n' + "tag";  // newline is commonly invalid in tags
  const std::string out = RunWriteTagAndGetOutput(input, /*verbatim=*/false, &ok);

  EXPECT_FALSE(ok);

  // Observable behavior: function writes the non-verbatim prefix before validating.
  ASSERT_GE(out.size(), 1u);
  EXPECT_EQ(out[0], '!');

  // Should not have produced the full "!<input>" for a failing validation.
  EXPECT_NE(out, "!" + input);
}

TEST_F(WriteTagTest_636, VerbatimInvalidCharacters_ReturnsFalseAndDoesNotAppendClosingBracket_636) {
  bool ok = true;
  const std::string input = std::string("http://example.com/") + '\n';  // newline is commonly invalid in URIs
  const std::string out = RunWriteTagAndGetOutput(input, /*verbatim=*/true, &ok);

  EXPECT_FALSE(ok);

  // Observable behavior: verbatim mode writes "!<" prefix first.
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.substr(0, 2), "!<");

  // If validation fails, it should not have written the verbatim suffix ">".
  // (At minimum, output should not end with '>' when returning false.)
  EXPECT_NE(out.back(), '>');
}

}  // namespace