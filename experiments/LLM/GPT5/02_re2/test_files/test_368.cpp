// File: ./TestProjects/re2/re2/tests/regexp_requiredprefix_test.cc

#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

using re2::Regexp;

namespace {

// Small helper to parse a pattern into a Regexp* using the provided flags.
// Treats the class as a black box: construction only via the public Parse API.
static Regexp* ParseOrNull(const std::string& pat,
                           Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0)) {
  return Regexp::Parse(absl::string_view(pat), flags, /*status=*/nullptr);
}

// Ensures we always Decref() anything we acquire, without peeking into internals.
struct RegexpHolder {
  Regexp* ptr = nullptr;
  explicit RegexpHolder(Regexp* p = nullptr) : ptr(p) {}
  ~RegexpHolder() { if (ptr) ptr->Decref(); }
  Regexp* get() const { return ptr; }
  Regexp* release() { Regexp* tmp = ptr; ptr = nullptr; return tmp; }
  Regexp*& ref() { return ptr; }
};

}  // namespace

// ========== Negative/Boundary behavior ==========

TEST(RegexpRequiredPrefixTest_368, ReturnsFalse_WhenOpIsNotConcat_368) {
  RegexpHolder re(ParseOrNull("abc"));  // Likely a single literal-string node.
  ASSERT_NE(re.get(), nullptr);

  std::string prefix;
  bool fold = true;        // Will be reset by the call.
  Regexp* suffix = reinterpret_cast<Regexp*>(0x1); // Will be reset to NULL.

  bool ok = re.get()->RequiredPrefix(&prefix, &fold, &suffix);
  EXPECT_FALSE(ok);
  EXPECT_TRUE(prefix.empty());
  EXPECT_FALSE(fold);
  EXPECT_EQ(suffix, nullptr);
}

TEST(RegexpRequiredPrefixTest_368, ReturnsFalse_WhenNoBeginTextAtStart_368) {
  RegexpHolder re(ParseOrNull("a(b)c"));  // Concat tree but no leading ^ anchor.
  ASSERT_NE(re.get(), nullptr);

  std::string prefix;
  bool fold = true;
  Regexp* suffix = reinterpret_cast<Regexp*>(0x1);

  bool ok = re.get()->RequiredPrefix(&prefix, &fold, &suffix);
  EXPECT_FALSE(ok);
  EXPECT_TRUE(prefix.empty());
  EXPECT_FALSE(fold);
  EXPECT_EQ(suffix, nullptr);
}

TEST(RegexpRequiredPrefixTest_368, ReturnsFalse_WhenBeginTextButNextIsNotLiteral_368) {
  RegexpHolder re(ParseOrNull("^."));  // ^ followed by "any char" (not a literal)
  ASSERT_NE(re.get(), nullptr);

  std::string prefix;
  bool fold = true;
  Regexp* suffix = reinterpret_cast<Regexp*>(0x1);

  bool ok = re.get()->RequiredPrefix(&prefix, &fold, &suffix);
  EXPECT_FALSE(ok);
  EXPECT_TRUE(prefix.empty());
  EXPECT_FALSE(fold);
  EXPECT_EQ(suffix, nullptr);
}

// ========== Positive behavior ==========

TEST(RegexpRequiredPrefixTest_368, ReturnsTrue_SimpleLiteral_NoSuffix_368) {
  RegexpHolder re(ParseOrNull("^a"));
  ASSERT_NE(re.get(), nullptr);

  std::string prefix;
  bool fold = false;
  Regexp* suffix = nullptr;

  bool ok = re.get()->RequiredPrefix(&prefix, &fold, &suffix);
  ASSERT_TRUE(ok);
  EXPECT_EQ(prefix, "a");
  EXPECT_FALSE(fold);
  ASSERT_NE(suffix, nullptr);

  // Validate via public API only.
  EXPECT_EQ(suffix->op(), re2::kRegexpEmptyMatch);

  RegexpHolder suffix_hold(suffix);
}

TEST(RegexpRequiredPrefixTest_368, ReturnsTrue_LiteralString_WithRemainderConcat_368) {
  // Pattern: ^abc.*d  → BeginText, LiteralString("abc"), then two more pieces (.* and 'd')
  // so the suffix should be a concatenation of the remaining parts.
  RegexpHolder re(ParseOrNull("^abc.*d"));
  ASSERT_NE(re.get(), nullptr);

  std::string prefix;
  bool fold = false;
  Regexp* suffix = nullptr;

  bool ok = re.get()->RequiredPrefix(&prefix, &fold, &suffix);
  ASSERT_TRUE(ok);
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(fold);
  ASSERT_NE(suffix, nullptr);

  // Publicly check that we got a Concat remainder.
  // (RequiredPrefix builds the remainder via Regexp::Concat.)
  EXPECT_EQ(suffix->op(), re2::kRegexpConcat);

  RegexpHolder suffix_hold(suffix);
}

TEST(RegexpRequiredPrefixTest_368, SetsFoldCaseTrue_WhenInlineCaseInsensitive_368) {
  // (?i) makes subsequent literals case-insensitive; ensure foldcase==true.
  // Example ensures we still have a literal immediately after ^.
  RegexpHolder re(ParseOrNull("(?i)^a"));
  if (re.get() == nullptr) {
    // Fallback in case the engine scopes (?i) differently: apply it only to 'a'.
    re.ref() = ParseOrNull("^(?i:a)");
  }
  ASSERT_NE(re.get(), nullptr);

  std::string prefix;
  bool fold = false;
  Regexp* suffix = nullptr;

  bool ok = re.get()->RequiredPrefix(&prefix, &fold, &suffix);
  ASSERT_TRUE(ok);
  EXPECT_EQ(prefix, "a");
  EXPECT_TRUE(fold);
  ASSERT_NE(suffix, nullptr);

  RegexpHolder suffix_hold(suffix);
}

TEST(RegexpRequiredPrefixTest_368, UsesLatin1WhenFlagIsSet_368) {
  // With Latin1 flag, a single byte literal \xE9 should be returned as that byte.
  // Build the pattern as "^\xE9".
  std::string pattern = "^";
  pattern.push_back('\xE9');  // single byte 0xE9

  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(Regexp::Latin1);
  RegexpHolder re(ParseOrNull(pattern, flags));
  ASSERT_NE(re.get(), nullptr);

  std::string prefix;
  bool fold = false;
  Regexp* suffix = nullptr;

  bool ok = re.get()->RequiredPrefix(&prefix, &fold, &suffix);
  ASSERT_TRUE(ok);
  ASSERT_EQ(prefix.size(), 1u);
  EXPECT_EQ(static_cast<unsigned char>(prefix[0]), 0xE9);
  EXPECT_FALSE(fold);
  ASSERT_NE(suffix, nullptr);

  RegexpHolder suffix_hold(suffix);
}

