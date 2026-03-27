// File: prefilter_info_to_string_test.cc
#include <gtest/gtest.h>
#include "re2/prefilter.h"

using re2::Prefilter;

namespace {

TEST(PrefilterInfoToString_543, DefaultConstructed_ReturnsEmpty_543) {
  // Default-constructed Info has no exact set and no match.
  Prefilter::Info info;
  EXPECT_EQ(info.ToString(), "");
}

TEST(PrefilterInfoToString_543, MatchString_EqualsUnderlyingPrefilterDebugString_543) {
  // Obtain an Info that represents a match via a public factory.
  // We do not assume what the string is; we only verify forwarding behavior.
  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::AnyMatch());
  ASSERT_NE(info, nullptr);

  const std::string to_string = info->ToString();

  // Take the underlying Prefilter* and compare DebugString() with ToString().
  std::unique_ptr<Prefilter> pf(info->TakeMatch());
  ASSERT_NE(pf, nullptr);

  EXPECT_EQ(to_string, pf->DebugString());
}

TEST(PrefilterInfoToString_543, AfterTakeMatch_ToStringBecomesEmpty_543) {
  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::AnyMatch());
  ASSERT_NE(info, nullptr);

  // Consume the underlying match.
  std::unique_ptr<Prefilter> pf(info->TakeMatch());
  ASSERT_NE(pf, nullptr);

  // With no exact_ and match_ consumed, ToString() should now be empty.
  EXPECT_EQ(info->ToString(), "");
}

TEST(PrefilterInfoToString_543, ExactSingleElement_NoComma_543) {
  // Use a factory that yields an "exact" flavor; treat as a black box.
  // EmptyString() is a safe, public entry point; then we only mutate via exact().
  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::EmptyString());
  ASSERT_NE(info, nullptr);
  ASSERT_TRUE(info->is_exact());

  // Add a single element and expect the same string back (no commas).
  info->exact().insert(std::string("one"));
  EXPECT_EQ(info->ToString(), "one");
}

TEST(PrefilterInfoToString_543, ExactMultipleElements_CommaSeparated_ContainsAll_543) {
  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::EmptyString());
  ASSERT_NE(info, nullptr);
  ASSERT_TRUE(info->is_exact());

  // Insert multiple strings via the public exact() accessor.
  auto& set = info->exact();
  set.insert(std::string("alpha"));
  set.insert(std::string("beta"));

  const std::string s = info->ToString();

  // We do not assume ordering; verify exactly one comma and the two tokens.
  size_t comma_pos = s.find(',');
  ASSERT_NE(comma_pos, std::string::npos) << "Expected a single comma in: " << s;
  EXPECT_EQ(s.find(',', comma_pos + 1), std::string::npos) << "Only one comma expected in: " << s;

  const std::string left = s.substr(0, comma_pos);
  const std::string right = s.substr(comma_pos + 1);

  // Order-agnostic containment check
  const bool is_alpha_beta = (left == "alpha" && right == "beta");
  const bool is_beta_alpha = (left == "beta" && right == "alpha");
  EXPECT_TRUE(is_alpha_beta || is_beta_alpha) << "Unexpected tokens: [" << left << "] and [" << right << "]";
}

TEST(PrefilterInfoToString_543, ExactEmptySet_ProducesEmptyString_543) {
  std::unique_ptr<Prefilter::Info> info(Prefilter::Info::EmptyString());
  ASSERT_NE(info, nullptr);
  ASSERT_TRUE(info->is_exact());

  // No entries inserted; join of empty set should yield empty string.
  EXPECT_EQ(info->ToString(), "");
}

}  // namespace
