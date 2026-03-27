// File: lookup_unicode_group_test_524.cc

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

// Minimal types to satisfy the interface used by parse.cc.
namespace re2 {
struct URange16 { unsigned short lo, hi; };
struct URange32 { unsigned int   lo, hi; };
struct UGroup {
  const char*       name;
  int               sign;
  const URange16*   r16;
  int               nr16;
  const URange32*   r32;
  int               nr32;
};

// Will be defined by including parse.cc below.
extern UGroup anygroup;

// Provide controllable test versions of these globals so we can observe
// what pointers/values are forwarded into LookupGroup.
static const URange16 kDummy16[] = { {0, 0} };
static const URange32 kDummy32[] = { {0, 0} };
const UGroup unicode_groups[] = {
  {"Greek", +1, kDummy16, 1, kDummy32, 1},
  {"Latin", +1, kDummy16, 1, kDummy32, 1},
};
const int num_unicode_groups = static_cast<int>(sizeof(unicode_groups)/sizeof(unicode_groups[0]));

// --- Test seam for LookupGroup (external collaborator) ---
// We don't simulate internal logic; we only capture observable calls & return a preset pointer.
static int        g_lookup_group_call_count = 0;
static std::string g_last_name;
static const UGroup* g_last_groups_ptr = nullptr;
static int        g_last_count = -1;
static const UGroup* g_return_ptr = nullptr;

const UGroup* LookupGroup(absl::string_view name,
                          const UGroup groups[],
                          int count) {
  ++g_lookup_group_call_count;
  g_last_name.assign(name.data(), name.size());
  g_last_groups_ptr = groups;
  g_last_count = count;
  return g_return_ptr;
}
}  // namespace re2

// Include the implementation TU so that the (file-local) static function is visible here.
#include "re2/parse.cc"

namespace {

class LookupUnicodeGroupTest_524 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset seam state before each test.
    re2::g_lookup_group_call_count = 0;
    re2::g_last_name.clear();
    re2::g_last_groups_ptr = nullptr;
    re2::g_last_count = -1;
    re2::g_return_ptr = nullptr;
  }
};

// Normal operation: exact "Any" should return &anygroup and NOT consult LookupGroup.
TEST_F(LookupUnicodeGroupTest_524, NameIsAny_ReturnsAnygroupWithoutDelegation_524) {
  const re2::UGroup* got = re2::LookupUnicodeGroup("Any");
  EXPECT_EQ(got, &re2::anygroup) << "Expected direct pointer to global anygroup";
  EXPECT_EQ(re2::g_lookup_group_call_count, 0) << "Must not delegate for name == \"Any\"";
}

// Normal operation: a typical non-\"Any\" input delegates to LookupGroup and returns its result.
TEST_F(LookupUnicodeGroupTest_524, NonAny_DelegatesAndReturnsLookupGroupResult_524) {
  // Prepare a sentinel to prove the return value is exactly what LookupGroup returns.
  static const re2::UGroup kSentinel = {"Sentinel", +1, nullptr, 0, nullptr, 0};
  re2::g_return_ptr = &kSentinel;

  const re2::UGroup* got = re2::LookupUnicodeGroup("Greek");

  // Returned pointer should be exactly what our seam returned.
  EXPECT_EQ(got, &kSentinel);

  // Verify delegation details (observable via our seam).
  EXPECT_EQ(re2::g_lookup_group_call_count, 1);
  EXPECT_EQ(re2::g_last_name, "Greek");
  EXPECT_EQ(re2::g_last_groups_ptr, re2::unicode_groups);
  EXPECT_EQ(re2::g_last_count, re2::num_unicode_groups);
}

// Boundary: empty name should NOT match \"Any\" and should delegate to LookupGroup.
TEST_F(LookupUnicodeGroupTest_524, EmptyName_DelegatesToLookupGroup_524) {
  static const re2::UGroup kSentinel = {"EmptyRet", +1, nullptr, 0, nullptr, 0};
  re2::g_return_ptr = &kSentinel;

  const re2::UGroup* got = re2::LookupUnicodeGroup("");

  EXPECT_EQ(got, &kSentinel);
  EXPECT_EQ(re2::g_lookup_group_call_count, 1);
  EXPECT_EQ(re2::g_last_name, "");
  EXPECT_EQ(re2::g_last_groups_ptr, re2::unicode_groups);
  EXPECT_EQ(re2::g_last_count, re2::num_unicode_groups);
}

// Boundary: case sensitivity — \"any\" (lowercase) should not be treated as \"Any\" and should delegate.
TEST_F(LookupUnicodeGroupTest_524, CaseSensitivity_LowercaseAnyDelegates_524) {
  static const re2::UGroup kSentinel = {"LowerAny", +1, nullptr, 0, nullptr, 0};
  re2::g_return_ptr = &kSentinel;

  const re2::UGroup* got = re2::LookupUnicodeGroup("any");

  EXPECT_EQ(got, &kSentinel);
  EXPECT_EQ(re2::g_lookup_group_call_count, 1);
  EXPECT_EQ(re2::g_last_name, "any");
  EXPECT_EQ(re2::g_last_groups_ptr, re2::unicode_groups);
  EXPECT_EQ(re2::g_last_count, re2::num_unicode_groups);
}

}  // namespace
