// File: pcre_extract_test_195.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/util/pcre.h"  // Adjust include path if needed

namespace re2 {

class PCRE_ExtractTest_195 : public ::testing::Test {};

TEST_F(PCRE_ExtractTest_195, NoMatch_DoesNotClearOutput_195) {
  // Arrange: pattern that does not occur in the text
  PCRE pattern("XYZ");
  const std::string text = "abc def";
  const std::string rewrite = "\\1";  // any rewrite (won't be used)
  std::string out = "keep-me";

  // Act
  bool ok = pattern.Extract(text, pattern, rewrite, &out);

  // Assert
  EXPECT_FALSE(ok) << "Extract should return false when there is no match";
  EXPECT_EQ(out, "keep-me") << "Output must remain unchanged when no match";
}

TEST_F(PCRE_ExtractTest_195, Match_ClearsAndRewrites_195) {
  // Arrange: simple capturing pattern
  PCRE pattern("(\\w+)-(\\d+)");
  const std::string text = "name-123";
  const std::string rewrite = "\\2:\\1";  // swap captures
  std::string out = "garbage";

  // Act
  bool ok = pattern.Extract(text, pattern, rewrite, &out);

  // Assert
  EXPECT_TRUE(ok) << "Extract should return true on successful rewrite";
  EXPECT_EQ(out, "123:name") << "Output should contain the rewritten text";
}

TEST_F(PCRE_ExtractTest_195, Match_InvalidRewrite_ReturnsFalseAndClearsOutput_195) {
  // Arrange: only two groups exist; rewrite references a non-existent group
  PCRE pattern("(\\w+)-(\\d+)");
  const std::string text = "foo-42";
  const std::string rewrite = "\\3";  // invalid capture index
  std::string out = "should-be-cleared";

  // Act
  bool ok = pattern.Extract(text, pattern, rewrite, &out);

  // Assert
  EXPECT_FALSE(ok) << "Extract should propagate failure from Rewrite()";
  // Extract clears 'out' before calling Rewrite(); on Rewrite failure it should stay cleared.
  EXPECT_EQ(out, "") << "Output must be cleared when rewrite fails after a match";
}

TEST_F(PCRE_ExtractTest_195, Unanchored_FirstMatchUsedWithBackref0_195) {
  // Arrange: UNANCHORED TryMatch should find the first occurrence
  PCRE pattern("(\\d+)");
  const std::string text = "a1b22c333";
  const std::string rewrite = "\\0";  // full match of the chosen span
  std::string out = "x";

  // Act
  bool ok = pattern.Extract(text, pattern, rewrite, &out);

  // Assert
  EXPECT_TRUE(ok);
  // Expect the first number match ("1") to be used.
  EXPECT_EQ(out, "1");
}

}  // namespace re2
