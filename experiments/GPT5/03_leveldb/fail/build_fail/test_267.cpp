// File: db/c_comparator_create_test.cc

#include <gtest/gtest.h>
#include <string>
#include <cstring>

#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "leveldb/c.h"   // for leveldb_comparator_create

using leveldb::Comparator;
using leveldb::Slice;

// ---- Test helpers (act as external collaborators) ----
namespace {

struct CallbackCapture {
  void* last_state = nullptr;
  std::string last_a;
  std::string last_b;
  size_t last_alen = 0;
  size_t last_blen = 0;
  int compare_return = 0;

  bool destructor_called = false;
  void* destructor_state = nullptr;

  const char* name_return = "MockCmp";
  bool name_called = false;
  void* name_state = nullptr;

  void Reset() { *this = CallbackCapture(); }
};

static CallbackCapture g_cap;

// C-style callbacks with the required signatures:
extern "C" {

static void MockDestructor(void* state) {
  g_cap.destructor_called = true;
  g_cap.destructor_state = state;
}

static int MockCompare(void* state,
                       const char* a, size_t alen,
                       const char* b, size_t blen) {
  g_cap.last_state = state;
  g_cap.last_a.assign(a, a + alen);
  g_cap.last_b.assign(b, b + blen);
  g_cap.last_alen = alen;
  g_cap.last_blen = blen;
  return g_cap.compare_return;  // test controls this
}

static const char* MockName(void* state) {
  g_cap.name_called = true;
  g_cap.name_state = state;
  return g_cap.name_return;
}

}  // extern "C"

}  // namespace

// ---- Fixture ----
class ComparatorCreateTest_267 : public ::testing::Test {
protected:
  leveldb_comparator_t* cmp_ = nullptr;
  int state_holder_ = 1234;  // arbitrary state we pass through

  void SetUp() override {
    g_cap.Reset();
    cmp_ = leveldb_comparator_create(
        &state_holder_, &MockDestructor, &MockCompare, &MockName);
    ASSERT_NE(cmp_, nullptr);  // sanity for subsequent tests
  }

  void TearDown() override {
    // Intentionally delete to trigger ~leveldb_comparator_t and callback.
    // This relies on the publicly-declared destructor in the provided snippet.
    delete cmp_;
    cmp_ = nullptr;
  }

  // Convenience cast to the C++ Comparator interface (observable API surface).
  const Comparator* AsComparator() const {
    return static_cast<const Comparator*>(cmp_);
  }
};

// ---- Tests ----

// Verifies that creation yields a non-null comparator object.
TEST_F(ComparatorCreateTest_267, CreateReturnsNonNull_267) {
  // SetUp already ASSERTed non-null; repeat here as an explicit test.
  EXPECT_NE(cmp_, nullptr);
}

// Verifies Name() delegates to the provided name callback and passes state.
TEST_F(ComparatorCreateTest_267, NameDelegatesAndPassesState_267) {
  const char* name = AsComparator()->Name();
  EXPECT_TRUE(g_cap.name_called);
  EXPECT_EQ(g_cap.name_state, &state_holder_);
  EXPECT_STREQ(name, g_cap.name_return);
}

// Verifies Compare() delegates to the provided compare callback with correct
// pointers, lengths, and state; and that the return value is propagated.
TEST_F(ComparatorCreateTest_267, CompareDelegatesAndPropagatesReturn_267) {
  // Control the compare return value from our mock.
  g_cap.compare_return = -1;

  // Use slices that include embedded nulls to ensure lengths are honored.
  const char a_buf[] = {'A', '\0', 'X'};
  const char b_buf[] = {'A', 'B', '\0', 'Y'};

  Slice a(a_buf, sizeof(a_buf));  // len = 3
  Slice b(b_buf, sizeof(b_buf));  // len = 4

  int rv = AsComparator()->Compare(a, b);
  EXPECT_EQ(rv, -1);

  // Check that the callback saw exactly what Comparator->Compare sent.
  EXPECT_EQ(g_cap.last_state, &state_holder_);
  EXPECT_EQ(g_cap.last_alen, a.size());
  EXPECT_EQ(g_cap.last_blen, b.size());
  ASSERT_EQ(g_cap.last_a.size(), a.size());
  ASSERT_EQ(g_cap.last_b.size(), b.size());
  EXPECT_EQ(0, std::memcmp(g_cap.last_a.data(), a.data(), a.size()));
  EXPECT_EQ(0, std::memcmp(g_cap.last_b.data(), b.data(), b.size()));
}

// Verifies that destroying the comparator triggers the provided destructor
// callback with the original state (observable external interaction).
TEST_F(ComparatorCreateTest_267, DestructorCallbackInvokedOnDelete_267) {
  // Manually delete early to assert, then prevent TearDown from double-delete.
  delete cmp_;
  cmp_ = nullptr;

  EXPECT_TRUE(g_cap.destructor_called);
  EXPECT_EQ(g_cap.destructor_state, &state_holder_);
}

// Smoke test: calling the separator/successor hooks should be safe to invoke
// from the public interface. We don't assert any internal behavior—only that
// the calls are accepted (black-box, observable: no crash).
TEST_F(ComparatorCreateTest_267, SeparatorAndSuccessorAreCallable_267) {
  std::string key = "foo";
  AsComparator()->FindShortestSeparator(&key, Slice("bar"));
  AsComparator()->FindShortSuccessor(&key);
  SUCCEED();  // Reaching here implies the calls were accepted without error.
}
