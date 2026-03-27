// File: poppler_password_to_latin1_test_2138.cc
//
// Unit tests for: poppler_password_to_latin1(const gchar*)
// NOTE: This function has internal linkage (static). To test it as a black box
// without re-implementing, we include the implementation TU here.
//
// If your build system dislikes including a .cc directly, you can alternatively
// compile this test in the same TU or expose a test-only wrapper in the project.

#include <gtest/gtest.h>

#include <cstring>
#include <optional>
#include <string>
#include <vector>

#include <glib.h>

#include "goo/GooString.h"

// Include the production implementation to access the static function.
// Adjust include path as needed for your build.
#include "poppler-document.cc"

namespace {

class PopplerPasswordToLatin1Test_2138 : public ::testing::Test {};

TEST_F(PopplerPasswordToLatin1Test_2138, NullPasswordReturnsEmptyOptional_2138) {
  std::optional<GooString> out = poppler_password_to_latin1(nullptr);
  EXPECT_FALSE(out.has_value());
}

TEST_F(PopplerPasswordToLatin1Test_2138, EmptyStringReturnsPresentOptionalWithEmptyString_2138) {
  std::optional<GooString> out = poppler_password_to_latin1("");
  ASSERT_TRUE(out.has_value());
  EXPECT_STREQ(out->c_str(), "");
  EXPECT_EQ(out->getLength(), 0);
}

TEST_F(PopplerPasswordToLatin1Test_2138, AsciiPasswordConvertsAndMatchesExactly_2138) {
  const char* in = "simple-ASCII-Password_123";
  std::optional<GooString> out = poppler_password_to_latin1(in);

  ASSERT_TRUE(out.has_value());
  EXPECT_STREQ(out->c_str(), in);
  EXPECT_EQ(out->getLength(), static_cast<int>(std::strlen(in)));
}

TEST_F(PopplerPasswordToLatin1Test_2138, Latin1RepresentableUnicodePreservesLatin1Bytes_2138) {
  // "Ångström" in UTF-8 input should convert to ISO-8859-1 bytes:
  // Å = 0xC5, ö = 0xF6.
  const char* utf8_in = u8"Ångström";

  std::optional<GooString> out = poppler_password_to_latin1(utf8_in);
  ASSERT_TRUE(out.has_value());

  const std::string expected_latin1 = std::string("\xC5") + "ngstr" + std::string("\xF6") + "m";
  EXPECT_EQ(out->getLength(), static_cast<int>(expected_latin1.size()));
  EXPECT_EQ(std::string(out->c_str(), out->getLength()), expected_latin1);
}

TEST_F(PopplerPasswordToLatin1Test_2138, LongAsciiPasswordConvertsAndPreservesLength_2138) {
  std::string in(4096, 'A');
  std::optional<GooString> out = poppler_password_to_latin1(in.c_str());

  ASSERT_TRUE(out.has_value());
  EXPECT_EQ(out->getLength(), static_cast<int>(in.size()));
  EXPECT_EQ(std::string(out->c_str(), out->getLength()), in);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerPasswordToLatin1Test_2138, UnrepresentableUnicodeMayFailFast_2138) {
  // A CJK character (漢) is not representable in ISO-8859-1.
  // The interface provides no error channel; if conversion fails and the
  // implementation does not handle it, this can lead to a crash.
  //
  // This test documents and verifies that the function does not silently succeed
  // for unrepresentable input (observed failure is acceptable via death test).
  const char* utf8_in = u8"漢";

  EXPECT_DEATH(
      {
        auto out = poppler_password_to_latin1(utf8_in);
        (void)out;
      },
      "");
}
#endif

}  // namespace