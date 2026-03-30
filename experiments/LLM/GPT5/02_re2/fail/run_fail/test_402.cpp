// File: prog_dump_test_402.cc
#include "gtest/gtest.h"

#include "re2/prog.h"         // Prog interface
#include "re2/sparse_set.h"   // Workq typedef (SparseSet)

#include <string>
#include <utility>

namespace re2 {
// ---- Test doubles for external helpers used by Prog::Dump() ----
// These are observable collaborators, not internal logic.
// They let us observe which path Dump() takes and with what parameters.

namespace {
struct Calls {
  int add_to_queue_calls = 0;
  int prog_to_string_calls = 0;
  int flattened_prog_to_string_calls = 0;

  int last_add_to_queue_start = -1;
  int last_flattened_start = -1;

  // We won't inspect the queue internals; we just observe counts & params.
} g_calls;
}  // namespace

// Signature: std::string FlattenedProgToString(Prog*, int)
std::string FlattenedProgToString(Prog* prog, int start) {
  g_calls.flattened_prog_to_string_calls++;
  g_calls.last_flattened_start = start;
  (void)prog;  // not used in the observable contract
  return std::string("FLATTENED_PATH");
}

// Signature: void AddToQueue(Workq*, int)
void AddToQueue(SparseSet* /*q*/, int start) {
  g_calls.add_to_queue_calls++;
  g_calls.last_add_to_queue_start = start;
}

// Signature: std::string ProgToString(Prog*, Workq*)
std::string ProgToString(Prog* /*prog*/, SparseSet* /*q*/) {
  g_calls.prog_to_string_calls++;
  return std::string("NON_FLATTENED_PATH");
}

}  // namespace re2

// -------------------- Test Fixture --------------------
class ProgDumpTest_402 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset call tracking before each test
    re2::g_calls = re2::Calls{};
  }
};

// -------------------- Tests --------------------

// [Normal] When not flattened (default), Dump uses AddToQueue + ProgToString.
TEST_F(ProgDumpTest_402, Dump_UsesQueueAndProgToString_WhenNotFlattened_402) {
  re2::Prog p;

  // Choose a non-default start value to verify it is forwarded correctly.
  p.set_start(42);

  const std::string out = p.Dump();

  // Observable effects:
  EXPECT_EQ(out, "NON_FLATTENED_PATH");
  EXPECT_EQ(re2::g_calls.add_to_queue_calls, 1);
  EXPECT_EQ(re2::g_calls.prog_to_string_calls, 1);
  EXPECT_EQ(re2::g_calls.flattened_prog_to_string_calls, 0);

  // Start index should be passed to AddToQueue.
  EXPECT_EQ(re2::g_calls.last_add_to_queue_start, 42);
}

// [Boundary] With default start (0), still uses non-flattened path and forwards start=0.
TEST_F(ProgDumpTest_402, Dump_ForwardsDefaultStartZero_402) {
  re2::Prog p;  // default start_ is 0 per constructor

  const std::string out = p.Dump();

  EXPECT_EQ(out, "NON_FLATTENED_PATH");
  EXPECT_EQ(re2::g_calls.add_to_queue_calls, 1);
  EXPECT_EQ(re2::g_calls.prog_to_string_calls, 1);
  EXPECT_EQ(re2::g_calls.flattened_prog_to_string_calls, 0);

  EXPECT_EQ(re2::g_calls.last_add_to_queue_start, 0);
}

// [Behavior switch] After calling Flatten(), Dump uses FlattenedProgToString.
TEST_F(ProgDumpTest_402, Dump_UsesFlattenedProgToString_AfterFlatten_402) {
  re2::Prog p;
  p.set_start(7);

  // Trigger flattened mode via the public API.
  p.Flatten();

  const std::string out = p.Dump();

  // Observable effects:
  EXPECT_EQ(out, "FLATTENED_PATH");
  EXPECT_EQ(re2::g_calls.flattened_prog_to_string_calls, 1);

  // In flattened path, the non-flattened collaborators should not be used.
  EXPECT_EQ(re2::g_calls.add_to_queue_calls, 0);
  EXPECT_EQ(re2::g_calls.prog_to_string_calls, 0);

  // Start index should be forwarded to FlattenedProgToString.
  EXPECT_EQ(re2::g_calls.last_flattened_start, 7);
}

// [Idempotence-ish sanity] Calling Dump() multiple times without Flatten() keeps using non-flattened path.
TEST_F(ProgDumpTest_402, Dump_CalledTwiceWithoutFlatten_StaysNonFlattened_402) {
  re2::Prog p;
  p.set_start(3);

  const std::string first = p.Dump();
  const std::string second = p.Dump();

  EXPECT_EQ(first, "NON_FLATTENED_PATH");
  EXPECT_EQ(second, "NON_FLATTENED_PATH");

  // Each call should enqueue and stringify.
  EXPECT_EQ(re2::g_calls.add_to_queue_calls, 2);
  EXPECT_EQ(re2::g_calls.prog_to_string_calls, 2);
  EXPECT_EQ(re2::g_calls.flattened_prog_to_string_calls, 0);
}

// [Transition] First Dump() non-flattened, then Flatten(), then Dump() flattened.
TEST_F(ProgDumpTest_402, Dump_TransitionFromNonFlattenedToFlattened_402) {
  re2::Prog p;
  p.set_start(11);

  const std::string before = p.Dump();  // non-flattened path
  p.Flatten();
  p.set_start(12);                       // ensure current start is reflected
  const std::string after = p.Dump();    // flattened path

  EXPECT_EQ(before, "NON_FLATTENED_PATH");
  EXPECT_EQ(after, "FLATTENED_PATH");

  EXPECT_EQ(re2::g_calls.add_to_queue_calls, 1);
  EXPECT_EQ(re2::g_calls.prog_to_string_calls, 1);
  EXPECT_EQ(re2::g_calls.flattened_prog_to_string_calls, 1);

  // Check that both paths forwarded the start value they were called with.
  EXPECT_EQ(re2::g_calls.last_add_to_queue_start, 11);
  EXPECT_EQ(re2::g_calls.last_flattened_start, 12);
}
