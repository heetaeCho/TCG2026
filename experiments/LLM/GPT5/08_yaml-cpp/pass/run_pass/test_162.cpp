// TEST_ID: 162
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "TestProjects/yaml-cpp/src/stream.h"
#include "yaml-cpp/exceptions.h"
#include "TestProjects/yaml-cpp/src/exp.h"  // Keys::VerbatimTagEnd

// Forward declaration for the unit under test (implemented in src/scantag.cpp).
namespace YAML {
const std::string ScanVerbatimTag(Stream& INPUT);
}  // namespace YAML

namespace {

class ScanVerbatimTagTest_162 : public ::testing::Test {
 protected:
  // Keep the stringstream alive for the lifetime of Stream.
  std::stringstream ss_;
};

TEST_F(ScanVerbatimTagTest_162, ReturnsTagAndConsumesEnd_162) {
  ss_.str("<foo>xyz");
  YAML::Stream in(ss_);

  const std::string tag = YAML::ScanVerbatimTag(in);
  EXPECT_EQ(tag, "foo");

  // The function should have consumed the terminating '>' and stop right after it.
  EXPECT_TRUE(in);
  EXPECT_EQ(in.peek(), 'x');
}

TEST_F(ScanVerbatimTagTest_162, EmptyTagReturnsEmptyString_162) {
  ss_.str("<>x");
  YAML::Stream in(ss_);

  const std::string tag = YAML::ScanVerbatimTag(in);
  EXPECT_TRUE(tag.empty());

  EXPECT_TRUE(in);
  EXPECT_EQ(in.peek(), 'x');
}

TEST_F(ScanVerbatimTagTest_162, MissingEndDelimiterThrowsParserException_162) {
  ss_.str("<foo");  // no '>'
  YAML::Stream in(ss_);

  try {
    (void)YAML::ScanVerbatimTag(in);
    FAIL() << "Expected YAML::ParserException";
  } catch (const YAML::ParserException& e) {
    // Message is a stable externally-visible string.
    EXPECT_NE(std::string(e.what()).find(YAML::ErrorMsg::END_OF_VERBATIM_TAG),
              std::string::npos);
  }
}

TEST_F(ScanVerbatimTagTest_162, InvalidCharacterBeforeEndThrowsParserException_162) {
  // Space is not expected to be part of a URI; scanning should fail before seeing '>'.
  ss_.str("<foo bar>");
  YAML::Stream in(ss_);

  try {
    (void)YAML::ScanVerbatimTag(in);
    FAIL() << "Expected YAML::ParserException";
  } catch (const YAML::ParserException& e) {
    EXPECT_NE(std::string(e.what()).find(YAML::ErrorMsg::END_OF_VERBATIM_TAG),
              std::string::npos);
  }
}

TEST_F(ScanVerbatimTagTest_162, StopsAtFirstEndDelimiterLeavingFollowingCharacters_162) {
  ss_.str("<foo>>");
  YAML::Stream in(ss_);

  const std::string tag = YAML::ScanVerbatimTag(in);
  EXPECT_EQ(tag, "foo");

  // Only the first '>' should be consumed; the second should remain.
  EXPECT_TRUE(in);
  EXPECT_EQ(in.peek(), YAML::Keys::VerbatimTagEnd);
}

}  // namespace