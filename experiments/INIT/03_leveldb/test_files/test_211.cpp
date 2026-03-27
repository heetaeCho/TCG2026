// File: db/c_comparator_test_211.cc

#include <gtest/gtest.h>
#include <string>

#include "leveldb/slice.h"          // For leveldb::Slice
#include "leveldb/comparator.h"     // For leveldb::Comparator
// The struct is defined in db/c.cc per the prompt. If there is a header, include that instead.
// Otherwise, include the cc to get the definition in test TU.
#include "db/c.cc"

using leveldb::Slice;

namespace {

// ---- Test helpers for capturing external interactions ----
static bool g_destructor_called = false;
static void* g_destructor_arg = nullptr;

static int g_last_compare_a_size = -1;
static int g_last_compare_b_size = -1;
static const char* g_last_compare_a_data = nullptr;
static const char* g_last_compare_b_data = nullptr;

// Different compare behaviors to verify return propagation.
extern "C" int AlwaysNeg(void*, const char*, size_t, const char*, size_t) { return -1; }
extern "C" int AlwaysZero(void*, const char*, size_t, const char*, size_t) { return 0; }
extern "C" int AlwaysPos(void*, const char*, size_t, const char*, size_t) { return 1; }

// Capturing compare that records the exact bytes/sizes passed in.
extern "C" int CapturingCompare(void* /*state*/,
                                const char* a, size_t asz,
                                const char* b, size_t bsz) {
  g_last_compare_a_data = a;
  g_last_compare_b_data = b;
  g_last_compare_a_size = static_cast<int>(asz);
  g_last_compare_b_size = static_cast<int>(bsz);
  return 42; // Arbitrary, just to verify propagation
}

// Name providers
extern "C" const char* NameFoo(void*) { return "foo_cmp"; }
extern "C" const char* NameBar(void*) { return "bar_cmp"; }

// Destructor that records the state it received
extern "C" void RecordingDestructor(void* state) {
  g_destructor_called = true;
  g_destructor_arg = state;
}

// Utility to reset capture globals between tests
void ResetCaptures() {
  g_destructor_called = false;
  g_destructor_arg = nullptr;
  g_last_compare_a_size = -1;
  g_last_compare_b_size = -1;
  g_last_compare_a_data = nullptr;
  g_last_compare_b_data = nullptr;
}

struct LeveldbComparatorTest_211 : public ::testing::Test {
  void SetUp() override { ResetCaptures(); }
};

} // namespace

// --- Tests ---

TEST_F(LeveldbComparatorTest_211, Compare_ReturnValueIsPropagated_211) {
  leveldb_comparator_t cmp;
  cmp.state_ = nullptr;
  cmp.destructor_ = RecordingDestructor; // not used in this test
  cmp.name_ = NameFoo;                   // not used in this test

  // Verify propagation of various return codes from compare_
  cmp.compare_ = AlwaysNeg;
  EXPECT_LT(cmp.Compare(Slice("a"), Slice("b")), 0);

  cmp.compare_ = AlwaysZero;
  EXPECT_EQ(cmp.Compare(Slice("a"), Slice("a")), 0);

  cmp.compare_ = AlwaysPos;
  EXPECT_GT(cmp.Compare(Slice("b"), Slice("a")), 0);
}

TEST_F(LeveldbComparatorTest_211, Compare_PassesExactBytesIncludingNulls_211) {
  leveldb_comparator_t cmp;
  cmp.state_ = nullptr;
  cmp.destructor_ = RecordingDestructor; // not used in this test
  cmp.name_ = NameFoo;                   // not used
  cmp.compare_ = CapturingCompare;

  // Slices with embedded NULs and explicit sizes
  const char a_buf[] = {'a', 'b', '\0', 'c'};
  const char b_buf[] = {'x', '\0', 'y'};
  Slice a(a_buf, sizeof(a_buf));
  Slice b(b_buf, sizeof(b_buf));

  int ret = cmp.Compare(a, b);
  EXPECT_EQ(ret, 42); // must propagate return value from CapturingCompare

  ASSERT_NE(g_last_compare_a_data, nullptr);
  ASSERT_NE(g_last_compare_b_data, nullptr);
  EXPECT_EQ(g_last_compare_a_size, static_cast<int>(sizeof(a_buf)));
  EXPECT_EQ(g_last_compare_b_size, static_cast<int>(sizeof(b_buf)));

  // Verify the first and last bytes to increase confidence that exact buffers were passed
  EXPECT_EQ(g_last_compare_a_data[0], 'a');
  EXPECT_EQ(g_last_compare_a_data[1], 'b');
  EXPECT_EQ(g_last_compare_a_data[2], '\0');
  EXPECT_EQ(g_last_compare_a_data[3], 'c');

  EXPECT_EQ(g_last_compare_b_data[0], 'x');
  EXPECT_EQ(g_last_compare_b_data[1], '\0');
  EXPECT_EQ(g_last_compare_b_data[2], 'y');
}

TEST_F(LeveldbComparatorTest_211, Name_ReturnsUnderlyingProviderResult_211) {
  leveldb_comparator_t cmp;
  cmp.state_ = nullptr;
  cmp.destructor_ = RecordingDestructor; // not used here
  cmp.compare_ = AlwaysZero;             // not used here

  cmp.name_ = NameFoo;
  EXPECT_STREQ(cmp.Name(), "foo_cmp");

  cmp.name_ = NameBar;
  EXPECT_STREQ(cmp.Name(), "bar_cmp");
}

TEST_F(LeveldbComparatorTest_211, Destructor_InvokesProvidedDestructorWithState_211) {
  auto* cmp = new leveldb_comparator_t;
  int state_value = 12345;
  cmp->state_ = &state_value;
  cmp->destructor_ = RecordingDestructor;
  cmp->compare_ = AlwaysZero;
  cmp->name_ = NameFoo;

  EXPECT_FALSE(g_destructor_called);
  delete cmp; // should trigger ~leveldb_comparator_t and call provided destructor

  EXPECT_TRUE(g_destructor_called);
  EXPECT_EQ(g_destructor_arg, &state_value);
}

// The following smoke test only verifies that these calls are callable and do not throw,
// without assuming any internal mutation semantics (black-box constraint).
TEST_F(LeveldbComparatorTest_211, ShortestSeparatorAndShortSuccessor_AreCallable_And_NonThrowing_211) {
  leveldb_comparator_t cmp;
  cmp.state_ = nullptr;
  cmp.destructor_ = RecordingDestructor;
  cmp.compare_ = AlwaysZero;
  cmp.name_ = NameFoo;

  std::string start = "start";
  std::string key = "key";
  Slice limit("limit");

  // We do not assert on resulting values to avoid inferring internal logic.
  EXPECT_NO_THROW(cmp.FindShortestSeparator(&start, limit));
  EXPECT_NO_THROW(cmp.FindShortSuccessor(&key));
}

