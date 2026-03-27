// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 990
//
// Unit tests for internal helper in: ./TestProjects/exiv2/src/version.cpp
//
// Notes:
// - The function under test is declared `static` in the .cpp, so it is not link-visible.
//   To test it as a black box via its provided signature, we include the implementation
//   translation unit here so the `static` symbol is available in this TU.
// - These tests intentionally do NOT infer any additional internal logic beyond the
//   observable behavior implied by the signature and inputs/outputs.

#include <gtest/gtest.h>

#include <regex>
#include <string>
#include <vector>

// Include the implementation file that contains the `static bool shouldOutput(...)`.
// If your build uses different include roots, adjust this path accordingly.
#include "TestProjects/exiv2/src/version.cpp"

namespace {

class ShouldOutputTest_990 : public ::testing::Test {};

TEST_F(ShouldOutputTest_990, EmptyGrepsPrintsByDefault_990) {
  const std::vector<std::regex> greps;  // empty
  const char* key = "Any.Key";
  const std::string value = "Any value";

  EXPECT_TRUE(shouldOutput(greps, key, value));
}

TEST_F(ShouldOutputTest_990, SingleRegexMatchesKey_ReturnsTrue_990) {
  const std::vector<std::regex> greps{std::regex("Exif\\.")};
  const char* key = "Exif.Image.Make";
  const std::string value = "Canon";

  EXPECT_TRUE(shouldOutput(greps, key, value));
}

TEST_F(ShouldOutputTest_990, SingleRegexMatchesValue_ReturnsTrue_990) {
  const std::vector<std::regex> greps{std::regex("Canon")};
  const char* key = "Exif.Image.Make";
  const std::string value = "Canon";

  EXPECT_TRUE(shouldOutput(greps, key, value));
}

TEST_F(ShouldOutputTest_990, SingleRegexMatchesNeither_ReturnsFalse_990) {
  const std::vector<std::regex> greps{std::regex("Nikon")};
  const char* key = "Exif.Image.Make";
  const std::string value = "Canon";

  EXPECT_FALSE(shouldOutput(greps, key, value));
}

TEST_F(ShouldOutputTest_990, MultipleRegex_AnyMatchKey_ReturnsTrue_990) {
  const std::vector<std::regex> greps{
      std::regex("NoMatchHere"),
      std::regex("Image\\.Make"),
      std::regex("StillNoMatch"),
  };
  const char* key = "Exif.Image.Make";
  const std::string value = "Canon";

  EXPECT_TRUE(shouldOutput(greps, key, value));
}

TEST_F(ShouldOutputTest_990, MultipleRegex_AnyMatchValue_ReturnsTrue_990) {
  const std::vector<std::regex> greps{
      std::regex("NoMatchHere"),
      std::regex("Canon"),
      std::regex("StillNoMatch"),
  };
  const char* key = "Exif.Image.Make";
  const std::string value = "Canon";

  EXPECT_TRUE(shouldOutput(greps, key, value));
}

TEST_F(ShouldOutputTest_990, EmptyKeyAndValue_NoMatch_ReturnsFalse_990) {
  const std::vector<std::regex> greps{std::regex("something")};
  const char* key = "";
  const std::string value;

  EXPECT_FALSE(shouldOutput(greps, key, value));
}

TEST_F(ShouldOutputTest_990, EmptyKeyAndValue_WithMatchAllRegex_ReturnsTrue_990) {
  const std::vector<std::regex> greps{std::regex(".*")};
  const char* key = "";
  const std::string value;

  EXPECT_TRUE(shouldOutput(greps, key, value));
}

TEST_F(ShouldOutputTest_990, SpecialCharactersInKey_RegexEscapingCanMatch_990) {
  const std::vector<std::regex> greps{std::regex("Xmp\\.dc:creator")};
  const char* key = "Xmp.dc:creator";
  const std::string value = "Alice";

  // This test verifies behavior when the key contains characters that often appear in metadata keys.
  EXPECT_TRUE(shouldOutput(greps, key, value));
}

}  // namespace