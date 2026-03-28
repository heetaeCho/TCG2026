// =================================================================================================
// Unit tests for FromUTF16Native
// File: ./TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp
// TEST_ID: 2059
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// Pull in UTF16Unit / UTF8Unit typedefs and error codes (kXMPErr_*).
// These are part of the XMP SDK headers used by Exiv2's xmpsdk subtree.
#include "XMP_Const.h"

// The function under test is implemented in UnicodeConversions.cpp (already linked in the codebase).
extern void FromUTF16Native(const UTF16Unit* utf16In, size_t utf16Len, std::string* utf8Str);

namespace {

class FromUTF16NativeTest_2059 : public ::testing::Test {};

static std::vector<UTF16Unit> MakeUTF16UnitsFromASCII(const std::string& ascii) {
  std::vector<UTF16Unit> out;
  out.reserve(ascii.size());
  for (unsigned char c : ascii) out.push_back(static_cast<UTF16Unit>(c));
  return out;
}

TEST_F(FromUTF16NativeTest_2059, EmptyInputClearsOutput_2059) {
  std::string out = "not empty";

  // Boundary: utf16Len == 0; input pointer should not be dereferenced.
  FromUTF16Native(reinterpret_cast<const UTF16Unit*>(""), 0, &out);

  EXPECT_TRUE(out.empty());
}

TEST_F(FromUTF16NativeTest_2059, ConvertsASCIIHello_2059) {
  const auto in = MakeUTF16UnitsFromASCII("Hello");
  std::string out;

  FromUTF16Native(in.data(), in.size(), &out);

  EXPECT_EQ(out, "Hello");
}

TEST_F(FromUTF16NativeTest_2059, ConvertsNonASCII_BMP_EuroSign_2059) {
  // U+20AC EURO SIGN is a single UTF-16 code unit in the BMP.
  const UTF16Unit in[] = { static_cast<UTF16Unit>(0x20AC) };
  std::string out;

  FromUTF16Native(in, 1, &out);

  // UTF-8 encoding for U+20AC is: E2 82 AC
  const std::string expected("\xE2\x82\xAC", 3);
  EXPECT_EQ(out.size(), expected.size());
  EXPECT_EQ(out, expected);
}

TEST_F(FromUTF16NativeTest_2059, PreservesEmbeddedNulls_2059) {
  // UTF-16: 'A', NUL, 'B'
  const UTF16Unit in[] = {
      static_cast<UTF16Unit>('A'),
      static_cast<UTF16Unit>(0x0000),
      static_cast<UTF16Unit>('B'),
  };
  std::string out = "seed";

  FromUTF16Native(in, 3, &out);

  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], 'A');
  EXPECT_EQ(out[1], '\0');
  EXPECT_EQ(out[2], 'B');
}

TEST_F(FromUTF16NativeTest_2059, OverwritesExistingOutput_2059) {
  const auto in = MakeUTF16UnitsFromASCII("XMP");
  std::string out = "this should be replaced";

  FromUTF16Native(in.data(), in.size(), &out);

  EXPECT_EQ(out, "XMP");
}

TEST_F(FromUTF16NativeTest_2059, LargeInputConvertsAllCharacters_2059) {
  // Boundary/robustness: large input likely forces multiple internal iterations.
  const size_t kCount = 20000;  // > 16k, to exercise chunking if present.
  std::vector<UTF16Unit> in(kCount, static_cast<UTF16Unit>('A'));
  std::string out;

  FromUTF16Native(in.data(), in.size(), &out);

  EXPECT_EQ(out.size(), kCount);
  EXPECT_EQ(out, std::string(kCount, 'A'));
}

TEST_F(FromUTF16NativeTest_2059, IncompleteSurrogateAtEndThrows_2059) {
  // Error case: a lone high surrogate (0xD800) is incomplete and should be rejected.
  const UTF16Unit in[] = { static_cast<UTF16Unit>(0xD800) };
  std::string out;

  EXPECT_ANY_THROW(FromUTF16Native(in, 1, &out));
}

}  // namespace