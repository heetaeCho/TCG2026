// File: lookup_group_test_521.cc

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// Include the interface types.
#include "re2/unicode_groups.h"

// Include the implementation so we can test the (file-static) function.
#include "re2/parse.cc"

namespace {

using re2::UGroup;

// Small helper to build UGroup values without relying on internal details.
static UGroup MakeGroup(const char* name, int sign = 1) {
  UGroup g;
  g.name = name;
  g.sign = sign;
  g.r16 = nullptr;
  g.nr16 = 0;
  g.r32 = nullptr;
  g.nr32 = 0;
  return g;
}

// Normal operation: finds an exact match and returns its address.
TEST(LookupGroupTest_521, FindsExactMatch_521) {
  UGroup groups[] = {
      MakeGroup("Latin"),
      MakeGroup("Greek"),
      MakeGroup("ASCII"),
  };

  const UGroup* found = re2::LookupGroup("Greek", groups, 3);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, &groups[1]);  // observable address of the matched element
}

// Boundary: no groups -> returns nullptr (safe even if pointer is nullptr).
TEST(LookupGroupTest_521, ReturnsNullWhenNoGroups_521) {
  const UGroup* found = re2::LookupGroup("Anything", /*groups=*/nullptr, /*ngroups=*/0);
  EXPECT_EQ(found, nullptr);
}

// Not found: name not present -> returns nullptr.
TEST(LookupGroupTest_521, ReturnsNullWhenNotFound_521) {
  UGroup groups[] = {MakeGroup("Latin"), MakeGroup("Greek")};
  const UGroup* found = re2::LookupGroup("Cyrillic", groups, 2);
  EXPECT_EQ(found, nullptr);
}

// Case sensitivity: comparison is exact, so different case should not match.
TEST(LookupGroupTest_521, CaseSensitiveComparison_521) {
  UGroup groups[] = {MakeGroup("Greek")};
  const UGroup* found = re2::LookupGroup("greek", groups, 1);
  EXPECT_EQ(found, nullptr);
}

// Duplicate names: verifies the first matching element is returned.
TEST(LookupGroupTest_521, ReturnsFirstOfDuplicates_521) {
  UGroup groups[] = {
      MakeGroup("Kana"),      // index 0
      MakeGroup("Hangul"),    // index 1
      MakeGroup("Kana"),      // index 2 (duplicate)
  };

  const UGroup* found = re2::LookupGroup("Kana", groups, 3);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, &groups[0]);  // first occurrence
}

// Empty name handling: exact match with empty string if present; otherwise nullptr.
TEST(LookupGroupTest_521, EmptyNameLookup_521) {
  UGroup groups[] = {MakeGroup(""), MakeGroup("Greek")};

  const UGroup* found_present = re2::LookupGroup("", groups, 2);
  ASSERT_NE(found_present, nullptr);
  EXPECT_EQ(found_present, &groups[0]);

  const UGroup* found_absent = re2::LookupGroup("", &groups[1], 1);  // only "Greek"
  EXPECT_EQ(found_absent, nullptr);
}

}  // namespace
