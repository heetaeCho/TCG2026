// File: bitstate_search_tests_580.cc

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

// Under test:
#include "re2/bitstate.cc"   // Uses the provided partial implementation
#include "re2/prog.h"

// ---- Minimal collaborator stubs for Prog ----
// We provide *only* the methods that BitState::Search can consult before
// it would dive into internal search (TrySearch). This keeps us within
// the constraint of not simulating the class-under-test internals.

namespace re2 {
namespace {
// Controllable globals to drive Prog's observable behavior for tests.
static bool g_anchor_start = false;
static bool g_anchor_end   = false;
static bool g_can_prefix   = false;
static int  g_list_count   = 1;
static int  g_start_state  = 0;
static const void* g_prefix_accel_return = nullptr;
}  // namespace

// Define just the Prog members that BitState::Search may call.
// (No internal search behavior is emulated.)
bool Prog::anchor_start() { return g_anchor_start; }
bool Prog::anchor_end()   { return g_anchor_end; }
bool Prog::can_prefix_accel() { return g_can_prefix; }
const void* Prog::PrefixAccel(const void* /*data*/, size_t /*size*/) {
  return g_prefix_accel_return;
}
int Prog::start()       { return g_start_state; }
int Prog::list_count()  { return g_list_count; }

// Provide empty ctor/dtor if the test build needs them linked.
Prog::Prog() {}
Prog::~Prog() {}
}  // namespace re2

namespace {

class BitStateSearchTest_580 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset controllable collaborator behavior before each test.
    re2::g_anchor_start = false;
    re2::g_anchor_end   = false;
    re2::g_can_prefix   = false;
    re2::g_list_count   = 1;
    re2::g_start_state  = 0;
    re2::g_prefix_accel_return = nullptr;
  }
};

}  // namespace

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

// Verifies: If prog_->anchor_start() is true and the begin pointer of
// context != begin pointer of text, Search() must return false immediately.
// (Early-return path; does not depend on TrySearch.)
TEST_F(BitStateSearchTest_580, AnchorStartMismatch_ReturnsFalse_580) {
  using namespace re2;

  g_anchor_start = true;  // Force start anchoring

  Prog prog;
  BitState bs(&prog);

  // Different underlying buffers => different begin pointers.
  std::string text = "abc";
  std::string ctx  = "zabc";  // distinct storage and different begin

  absl::string_view submatches[1];  // not used on early-return path
  const bool anchored = false;
  const bool longest  = false;

  bool ok = bs.Search(text, absl::string_view(ctx), anchored, longest,
                      submatches, /*nsubmatch=*/1);

  EXPECT_FALSE(ok);
}

// Verifies: If prog_->anchor_end() is true and the end pointer of
// context != end pointer of text, Search() must return false immediately.
// (Early-return path; does not depend on TrySearch.)
TEST_F(BitStateSearchTest_580, AnchorEndMismatch_ReturnsFalse_580) {
  using namespace re2;

  g_anchor_end = true;  // Force end anchoring

  Prog prog;
  BitState bs(&prog);

  // Different end pointers via different sizes/storage.
  std::string text = "abc";
  std::string ctx  = "abcx";  // longer => different end pointer

  absl::string_view submatches[1];
  const bool anchored = false;
  const bool longest  = false;

  bool ok = bs.Search(text, absl::string_view(ctx), anchored, longest,
                      submatches, /*nsubmatch=*/1);

  EXPECT_FALSE(ok);
}

