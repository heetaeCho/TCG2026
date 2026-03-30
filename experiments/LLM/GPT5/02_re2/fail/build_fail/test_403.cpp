// File: prog_dump_unanchored_test.cc

#include <gtest/gtest.h>
#include <string>

// Forward declarations to avoid pulling in heavy headers.
// We only need pointer types for our stubs and to call the method under test.
namespace re2 {
class Prog;
struct SparseSet;  // treat as opaque
}

// ====== Test doubles for external collaborators in re2 namespace ======
namespace re2 {

// Global capture state for assertions in tests.
static int g_add_to_queue_calls = 0;
static int g_prog_to_string_calls = 0;
static int g_flattened_prog_to_string_calls = 0;

static int g_last_add_to_queue_start = -1;
static const SparseSet* g_last_add_to_queue_q = nullptr;

static const SparseSet* g_last_prog_to_string_q = nullptr;
static const Prog* g_last_prog_to_string_prog = nullptr;

static int g_last_flattened_prog_to_string_start = -1;
static const Prog* g_last_flattened_prog_to_string_prog = nullptr;

static std::string g_prog_to_string_return = "UNSET";
static std::string g_flattened_prog_to_string_return = "UNSET";

// Stub: called by DumpUnanchored() when NOT flattened.
void AddToQueue(SparseSet* q, int start) {
  ++g_add_to_queue_calls;
  g_last_add_to_queue_q = q;
  g_last_add_to_queue_start = start;
}

// Stub: called by DumpUnanchored() when NOT flattened after AddToQueue.
std::string ProgToString(Prog* p, SparseSet* q) {
  ++g_prog_to_string_calls;
  g_last_prog_to_string_prog = p;
  g_last_prog_to_string_q = q;
  return g_prog_to_string_return;
}

// Stub: called by DumpUnanchored() when flattened.
std::string FlattenedProgToString(Prog* p, int start) {
  ++g_flattened_prog_to_string_calls;
  g_last_flattened_prog_to_string_prog = p;
  g_last_flattened_prog_to_string_start = start;
  return g_flattened_prog_to_string_return;
}

}  // namespace re2

// Now include the interface under test.
#include "re2/prog.h"

namespace {

using namespace re2;

struct DumpUnanchoredTest : ::testing::Test {
  void SetUp() override {
    // Reset all captured globals before each test.
    g_add_to_queue_calls = 0;
    g_prog_to_string_calls = 0;
    g_flattened_prog_to_string_calls = 0;

    g_last_add_to_queue_start = -1;
    g_last_add_to_queue_q = nullptr;

    g_last_prog_to_string_q = nullptr;
    g_last_prog_to_string_prog = nullptr;

    g_last_flattened_prog_to_string_start = -1;
    g_last_flattened_prog_to_string_prog = nullptr;

    g_prog_to_string_return = "PT_DEFAULT";
    g_flattened_prog_to_string_return = "FT_DEFAULT";
  }
};

// Normal path (not flattened): it should enqueue start_unanchored into q
// and then stringify via ProgToString. Return value should come from ProgToString.
TEST_F(DumpUnanchoredTest, NotFlattened_CallsAddToQueue_And_ProgToString_403) {
  Prog prog;
  prog.set_start_unanchored(123);  // observable input for collaborators

  // Set expected return for ProgToString
  g_prog_to_string_return = "NON_FLAT_STRING";

  const std::string s = prog.DumpUnanchored();

  // Verify collaborator interactions
  EXPECT_EQ(g_add_to_queue_calls, 1);
  EXPECT_EQ(g_prog_to_string_calls, 1);
  EXPECT_EQ(g_flattened_prog_to_string_calls, 0);

  // Ensure the same queue pointer is passed to both calls
  ASSERT_NE(g_last_add_to_queue_q, nullptr);
  ASSERT_NE(g_last_prog_to_string_q, nullptr);
  EXPECT_EQ(g_last_add_to_queue_q, g_last_prog_to_string_q);

  // Ensure the correct start value is forwarded to AddToQueue
  EXPECT_EQ(g_last_add_to_queue_start, 123);

  // Ensure Prog* passed is the same object
  EXPECT_EQ(g_last_prog_to_string_prog, &prog);

  // Ensure return value is exactly what ProgToString produced
  EXPECT_EQ(s, "NON_FLAT_STRING");
}

// Flattened path: after calling Flatten(), DumpUnanchored should bypass
// AddToQueue/ProgToString and call FlattenedProgToString with start_unanchored.
TEST_F(DumpUnanchoredTest, Flattened_UsesFlattenedProgToString_Only_403) {
  Prog prog;
  prog.set_start_unanchored(7);

  // Make it flattened through the public API (no private access).
  prog.Flatten();

  // Set expected return for FlattenedProgToString
  g_flattened_prog_to_string_return = "FLAT_STRING";

  const std::string s = prog.DumpUnanchored();

  // Verify only flattened path collaborator was used
  EXPECT_EQ(g_add_to_queue_calls, 0);
  EXPECT_EQ(g_prog_to_string_calls, 0);
  EXPECT_EQ(g_flattened_prog_to_string_calls, 1);

  // Verify arguments forwarded to FlattenedProgToString
  EXPECT_EQ(g_last_flattened_prog_to_string_prog, &prog);
  EXPECT_EQ(g_last_flattened_prog_to_string_start, 7);

  // Ensure return comes from FlattenedProgToString
  EXPECT_EQ(s, "FLAT_STRING");
}

// Boundary-ish scenario: default start_unanchored (constructor default) should be forwarded.
// Also ensure not-flattened path still works when start_unanchored is 0.
TEST_F(DumpUnanchoredTest, NotFlattened_UsesDefaultStartUnanchored_WhenNotSet_403) {
  Prog prog;  // start_unanchored defaults to 0 in ctor (per header)

  g_prog_to_string_return = "DEFAULT_START";

  const std::string s = prog.DumpUnanchored();

  EXPECT_EQ(g_add_to_queue_calls, 1);
  EXPECT_EQ(g_prog_to_string_calls, 1);
  EXPECT_EQ(g_flattened_prog_to_string_calls, 0);

  EXPECT_EQ(g_last_add_to_queue_start, 0);
  EXPECT_EQ(s, "DEFAULT_START");
}

// Sanity: after Flatten(), changing start_unanchored propagates to FlattenedProgToString.
TEST_F(DumpUnanchoredTest, Flattened_RespectsUpdatedStartUnanchored_403) {
  Prog prog;
  prog.set_start_unanchored(1);
  prog.Flatten();
  prog.set_start_unanchored(42);  // update after flatten

  g_flattened_prog_to_string_return = "UPDATED_START";

  const std::string s = prog.DumpUnanchored();

  EXPECT_EQ(g_add_to_queue_calls, 0);
  EXPECT_EQ(g_prog_to_string_calls, 0);
  EXPECT_EQ(g_flattened_prog_to_string_calls, 1);

  EXPECT_EQ(g_last_flattened_prog_to_string_start, 42);
  EXPECT_EQ(s, "UPDATED_START");
}

}  // namespace
