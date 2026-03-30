// File: onepass_satisfy_test_565.cc
#include <cstdint>
#include <string>
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// --- Minimal declarations to satisfy onepass.cc dependencies ---
namespace re2 {
enum EmptyOp {
  kEmptyBeginLine        = 1,
  kEmptyEndLine          = 2,
  kEmptyBeginText        = 4,
  kEmptyEndText          = 8,
  kEmptyWordBoundary     = 16,
  kEmptyNonWordBoundary  = 32,
  kEmptyAllFlags         = 63
};

class Prog {
 public:
  static uint32_t EmptyFlags(absl::string_view context, const char* p);
};
}  // namespace re2

// ---- Controllable stub for Prog::EmptyFlags (external collaborator) ----
namespace {
static uint32_t g_stub_flags = 0;
static std::string g_last_context;
static const char* g_last_p = nullptr;
}

uint32_t re2::Prog::EmptyFlags(absl::string_view context, const char* p) {
  g_last_context = std::string(context);
  g_last_p = p;
  return g_stub_flags;
}

// --- Include the implementation under test so we can access the internal-linkage function ---
#include "TestProjects/re2/re2/onepass.cc"  // defines namespace re2 { static bool Satisfy(...) }

// ------------------------- Test Fixture -------------------------
class SatisfyTest_565 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_stub_flags = 0;
    g_last_context.clear();
    g_last_p = nullptr;
  }
};

// --------------------------- Test Cases ---------------------------

TEST_F(SatisfyTest_565, CondZeroAlwaysTrue_565) {
  using namespace re2;
  g_stub_flags = 0;  // doesn't matter
  char c = 'x';
  EXPECT_TRUE(Satisfy(/*cond=*/0u, /*context=*/"ignored", /*p=*/&c));
  g_stub_flags = kEmptyAllFlags;
  EXPECT_TRUE(Satisfy(/*cond=*/0u, /*context=*/"ignored", /*p=*/&c));
}

TEST_F(SatisfyTest_565, ReturnsTrueWhenAllRequiredSatisfied_565) {
  using namespace re2;
  g_stub_flags = kEmptyBeginLine | kEmptyEndText;
  char c = 'y';
  EXPECT_TRUE(Satisfy(/*cond=*/kEmptyBeginLine, /*context=*/"ctx", /*p=*/&c));
  EXPECT_TRUE(Satisfy(/*cond=*/kEmptyBeginLine | kEmptyEndText, /*context=*/"ctx", /*p=*/&c));
}

TEST_F(SatisfyTest_565, ReturnsFalseWhenAnyRequiredMissing_565) {
  using namespace re2;
  g_stub_flags = kEmptyBeginLine;  // missing kEmptyEndLine
  char c = 'z';
  EXPECT_FALSE(Satisfy(/*cond=*/kEmptyBeginLine | kEmptyEndLine, /*context=*/"ctx", /*p=*/&c));
}

TEST_F(SatisfyTest_565, IgnoresNonEmptyFlagsBits_565) {
  using namespace re2;
  g_stub_flags = 0;  // no empty flags satisfied
  constexpr uint32_t kNonEmptyBit = 0x80000000u;  // outside kEmptyAllFlags mask
  char c = 'a';
  // Since kNonEmptyBit is not in kEmptyAllFlags, it should be ignored -> true.
  EXPECT_TRUE(Satisfy(/*cond=*/kNonEmptyBit, /*context=*/"ctx", /*p=*/&c));
}

TEST_F(SatisfyTest_565, AllFlagsSatisfied_565) {
  using namespace re2;
  g_stub_flags = kEmptyAllFlags;
  char c = 'b';
  EXPECT_TRUE(Satisfy(/*cond=*/kEmptyAllFlags, /*context=*/"ctx", /*p=*/&c));
}

TEST_F(SatisfyTest_565, ForwardsArgsToEmptyFlags_565) {
  using namespace re2;
  g_stub_flags = kEmptyBeginText;  // arbitrary, not essential for arg-forwarding
  char c = 'c';
  const char* p = &c;
  absl::string_view ctx("forward-me");
  (void)Satisfy(/*cond=*/0u, ctx, p);  // always true; we care about the side-effect in the stub
  EXPECT_EQ(g_last_context, "forward-me");
  EXPECT_EQ(g_last_p, p);
}
