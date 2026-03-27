// File: prog_destructor_and_accessors_test_398.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "re2/prog.h"

using ::testing::NotNull;
using ::testing::IsNull;

namespace re2 {

class ProgTest_398 : public ::testing::Test {
protected:
  // Helper to exercise destruction path explicitly
  static void ConstructAndDelete() {
    auto* p = new Prog();
    delete p;  // Should be safe and not crash
  }
};

// ----------------------------------------------------------------------------
// Defaults & simple accessors
// ----------------------------------------------------------------------------

TEST_F(ProgTest_398, Defaults_AreSane_398) {
  Prog p;

  // Verify observable defaults via public API.
  // Only assert on fields with public getters.
  EXPECT_EQ(p.start(), 0);
  EXPECT_EQ(p.start_unanchored(), 0);

  EXPECT_FALSE(p.reversed());
  EXPECT_FALSE(p.anchor_start());
  EXPECT_FALSE(p.anchor_end());

  // dfa_mem() is observable via getter
  EXPECT_EQ(p.dfa_mem(), 0);

  // These may exist per the provided interface; validate they return non-negative/zero-ish values.
  EXPECT_GE(p.bytemap_range(), 0);
  EXPECT_GE(p.list_count(), 0);
  EXPECT_GE(static_cast<int>(p.bit_state_text_max_size()), 0);
}

TEST_F(ProgTest_398, Setters_RoundTrip_398) {
  Prog p;

  p.set_start(5);
  EXPECT_EQ(p.start(), 5);

  p.set_start_unanchored(7);
  EXPECT_EQ(p.start_unanchored(), 7);

  p.set_reversed(true);
  EXPECT_TRUE(p.reversed());
  p.set_reversed(false);
  EXPECT_FALSE(p.reversed());

  p.set_anchor_start(true);
  EXPECT_TRUE(p.anchor_start());
  p.set_anchor_start(false);
  EXPECT_FALSE(p.anchor_start());

  p.set_anchor_end(true);
  EXPECT_TRUE(p.anchor_end());
  p.set_anchor_end(false);
  EXPECT_FALSE(p.anchor_end());

  p.set_dfa_mem(123456789);
  EXPECT_EQ(p.dfa_mem(), 123456789);
}

// ----------------------------------------------------------------------------
// Destructor safety
// ----------------------------------------------------------------------------

TEST_F(ProgTest_398, Destructor_DefaultConstructed_DoesNotCrash_398) {
  EXPECT_NO_FATAL_FAILURE(ProgTest_398::ConstructAndDelete());
}

TEST_F(ProgTest_398, Destructor_AfterConfigurePrefixAccel_NoFoldcase_DoesNotCrash_398) {
  auto* p = new Prog();

  // Configure prefix accel with a simple prefix and foldcase = false.
  p->ConfigurePrefixAccel(std::string("abc"), /*prefix_foldcase=*/false);

  // Call one of the prefix-accel entry points with a small data buffer to
  // exercise any internal state that might be tied to cleanup.
  const char data[] = "zzzabcxxx";
  (void)p->PrefixAccel_ShiftDFA(data, sizeof(data) - 1);

  // Destruction should be safe (no leaks/crash is an execution-time property;
  // the test asserts no fatal failure/crash).
  EXPECT_NO_FATAL_FAILURE(delete p);
}

TEST_F(ProgTest_398, Destructor_AfterConfigurePrefixAccel_Foldcase_DoesNotCrash_398) {
  auto* p = new Prog();

  // Configure with foldcase = true (which, per interface, may allocate
  // fold-case specific resources internally).
  p->ConfigurePrefixAccel(std::string("AbC"), /*prefix_foldcase=*/true);

  // Exercise the other prefix-accel entry point as an observable call.
  const char data[] = "xxAbcYY";
  (void)p->PrefixAccel_FrontAndBack(data, sizeof(data) - 1);

  // Ensure destruction is safe.
  EXPECT_NO_FATAL_FAILURE(delete p);
}

// ----------------------------------------------------------------------------
// PrefixAccel edge inputs (observable calls only; no internal assumptions)
// ----------------------------------------------------------------------------

TEST_F(ProgTest_398, PrefixAccel_AllowsEmptyInputWithoutCrash_398) {
  Prog p;
  p.ConfigurePrefixAccel(std::string("a"), /*prefix_foldcase=*/true);

  // size==0 should be handled gracefully by the public API.
  const void* out = p.PrefixAccel(nullptr, 0);
  // We don't assert semantics beyond "call is safe"; result may be nullptr or
  // some sentinel per implementation—treat as black box.
  (void)out;
  SUCCEED();
}

}  // namespace re2
