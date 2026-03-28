// TEST_ID: 818
// File: test_commentvalue_charsetinfo_818.cpp

#include <gtest/gtest.h>

#include <string>

#include <exiv2/value.hpp>

namespace {

class CommentValueCharsetInfoTest_818 : public ::testing::Test {
 protected:
  using CharsetId = Exiv2::CommentValue::CharsetId;
  using CharsetInfo = Exiv2::CommentValue::CharsetInfo;
};

TEST_F(CommentValueCharsetInfoTest_818, CharsetIdByCode_RoundTripsKnownCodes_818) {
  const CharsetId ids[] = {
      CharsetId::ascii,
      CharsetId::jis,
      CharsetId::unicode,
      CharsetId::undefined,
  };

  for (const auto id : ids) {
    const char* code = CharsetInfo::code(id);
    ASSERT_NE(code, nullptr) << "code() must provide a non-null code for known CharsetId";

    const CharsetId got = CharsetInfo::charsetIdByCode(std::string(code));
    EXPECT_EQ(got, id) << "charsetIdByCode(code(id)) should round-trip for known CharsetId";
  }
}

TEST_F(CommentValueCharsetInfoTest_818, CharsetIdByCode_UnknownCodeReturnsInvalid_818) {
  // An 8-character string that is extremely unlikely to be a valid charset code.
  const std::string unknown8 = "ZZZZZZZZ";
  EXPECT_EQ(CharsetInfo::charsetIdByCode(unknown8), CharsetId::invalidCharsetId);

  // Also verify empty string is treated as unknown.
  EXPECT_EQ(CharsetInfo::charsetIdByCode(std::string()), CharsetId::invalidCharsetId);
}

TEST_F(CommentValueCharsetInfoTest_818, CharsetIdByCode_LengthMismatchDoesNotMatch_818) {
  // Take a known code and ensure that changing its length prevents a match.
  const char* asciiCode = CharsetInfo::code(CharsetId::ascii);
  ASSERT_NE(asciiCode, nullptr);

  const std::string base(asciiCode);

  // If base is empty for some reason, we can't meaningfully run the mismatch checks.
  ASSERT_FALSE(base.empty());

  EXPECT_EQ(CharsetInfo::charsetIdByCode(base + "X"), CharsetId::invalidCharsetId)
      << "Appending a character should prevent a match";

  // If base has at least 2 chars, try a shortened variant too.
  if (base.size() >= 2) {
    EXPECT_EQ(CharsetInfo::charsetIdByCode(base.substr(0, base.size() - 1)), CharsetId::invalidCharsetId)
        << "Removing a character should prevent a match";
  }
}

TEST_F(CommentValueCharsetInfoTest_818, CharsetIdByCode_CaseChangedDoesNotMatch_818) {
  // Use a known code and flip case of ASCII letters where possible; expect it not to match.
  const char* jisCode = CharsetInfo::code(CharsetId::jis);
  ASSERT_NE(jisCode, nullptr);

  std::string altered(jisCode);
  bool changed = false;
  for (char& c : altered) {
    if (c >= 'a' && c <= 'z') {
      c = static_cast<char>(c - ('a' - 'A'));
      changed = true;
      break;
    }
    if (c >= 'A' && c <= 'Z') {
      c = static_cast<char>(c + ('a' - 'A'));
      changed = true;
      break;
    }
  }

  if (changed) {
    EXPECT_EQ(CharsetInfo::charsetIdByCode(altered), CharsetId::invalidCharsetId)
        << "Case-altered code should not match (exact string match expected)";
  } else {
    // If there were no alphabetic characters to flip, at least verify the original still round-trips.
    EXPECT_EQ(CharsetInfo::charsetIdByCode(std::string(jisCode)), CharsetId::jis);
  }
}

TEST_F(CommentValueCharsetInfoTest_818, CharsetIdByCode_GarbageBinaryLikeStringReturnsInvalid_818) {
  // Boundary-ish: include NUL within the std::string; should be treated as unknown unless
  // the implementation explicitly supports such codes (observable outcome: invalid expected here).
  std::string withNul;
  withNul.push_back('\0');
  withNul.append("ABCDEF");  // total length 7
  EXPECT_EQ(CharsetInfo::charsetIdByCode(withNul), CharsetId::invalidCharsetId);

  // Make it 8 length with mixed bytes.
  withNul.push_back('\x7F');  // now length 8
  EXPECT_EQ(CharsetInfo::charsetIdByCode(withNul), CharsetId::invalidCharsetId);
}

}  // namespace