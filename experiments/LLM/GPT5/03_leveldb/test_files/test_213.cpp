// File: db/c_comparator_test_213.cc

#include <gtest/gtest.h>
#include <string>
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

// The partial/known struct interface (public members as shown in the prompt).
// If it's already visible via an included header in your build, remove this.
struct leveldb_comparator_t : public leveldb::Comparator {
  void* state_;
  void (*destructor_)(void*);
  int (*compare_)(void*, const char*, size_t, const char*, size_t);
  const char* (*name_)(void*);
  ~leveldb_comparator_t() override;
  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override;
  const char* Name() const override;
  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override;
  void FindShortSuccessor(std::string* key) const override;
};

// ----------------- Test Fixture -----------------

class ComparatorCWrapperTest_213 : public ::testing::Test {
 protected:
  struct State {
    // For destructor
    int dtor_calls = 0;

    // For name
    std::string name_to_return;

    // For compare capture
    std::string last_a;
    std::string last_b;
    int return_value = 0;
  };

  static void DestructorCb(void* s) {
    auto* st = static_cast<State*>(s);
    st->dtor_calls++;
  }

  static const char* NameCb(void* s) {
    auto* st = static_cast<State*>(s);
    return st->name_to_return.c_str();
  }

  static int CompareCb(void* s,
                       const char* a, size_t a_len,
                       const char* b, size_t b_len) {
    auto* st = static_cast<State*>(s);
    st->last_a.assign(a, a_len);
    st->last_b.assign(b, b_len);
    return st->return_value;
  }

  // Helper to build a comparator object configured with our callbacks/state.
  static leveldb_comparator_t MakeComparator(State* state) {
    leveldb_comparator_t c;
    c.state_ = state;
    c.destructor_ = &DestructorCb;
    c.compare_ = &CompareCb;
    c.name_ = &NameCb;
    return c;
  }
};

// ----------------- Tests -----------------

TEST_F(ComparatorCWrapperTest_213, Name_ForwardsToCallback_213) {
  State st;
  st.name_to_return = "my.comparator/213";
  auto cmp = MakeComparator(&st);

  EXPECT_STREQ("my.comparator/213", cmp.Name());
}

TEST_F(ComparatorCWrapperTest_213, Compare_ForwardsArgsAndReturnValue_213) {
  State st;
  st.return_value = -7;
  auto cmp = MakeComparator(&st);

  leveldb::Slice a("alpha");
  leveldb::Slice b("beta");

  // Compare should return exactly what callback returns.
  EXPECT_EQ(-7, cmp.Compare(a, b));

  // Callback should receive the exact bytes and lengths.
  EXPECT_EQ("alpha", st.last_a);
  EXPECT_EQ("beta", st.last_b);
}

TEST_F(ComparatorCWrapperTest_213, Compare_HandlesEmptyAndBinaryData_213) {
  State st;
  st.return_value = 42;
  auto cmp = MakeComparator(&st);

  // Empty slices
  {
    leveldb::Slice a_empty;
    leveldb::Slice b_empty;
    EXPECT_EQ(42, cmp.Compare(a_empty, b_empty));
    EXPECT_TRUE(st.last_a.empty());
    EXPECT_TRUE(st.last_b.empty());
  }

  // Binary data with embedded NULs
  {
    const char a_raw[] = {'A', '\0', 'B', '\0', 'C'};
    const char b_raw[] = {'X', 'Y', '\0'};
    leveldb::Slice a(a_raw, sizeof(a_raw));
    leveldb::Slice b(b_raw, sizeof(b_raw));

    st.return_value = 3;  // change to ensure pass-through still holds
    EXPECT_EQ(3, cmp.Compare(a, b));

    ASSERT_EQ(sizeof(a_raw), st.last_a.size());
    ASSERT_EQ(sizeof(b_raw), st.last_b.size());
    EXPECT_EQ(std::string(a_raw, sizeof(a_raw)), st.last_a);
    EXPECT_EQ(std::string(b_raw, sizeof(b_raw)), st.last_b);
  }
}

TEST_F(ComparatorCWrapperTest_213, Destructor_InvokesCallback_Once_213) {
  State st;
  {
    auto cmp = MakeComparator(&st);
    // Explicitly call the destructor by deleting a heap-allocated copy to
    // ensure the virtual dtor path is exercised in typical ownership mode.
    auto* heap_cmp = new leveldb_comparator_t(cmp);
    EXPECT_EQ(0, st.dtor_calls);
    delete heap_cmp;  // should call destructor_
    EXPECT_EQ(1, st.dtor_calls);
  }
  // Destroying the stack 'cmp' here is an additional destructor call only if
  // its destructor is hooked to the same callback; we don't rely on it.
  // We only assert the guaranteed single call above.
}

TEST_F(ComparatorCWrapperTest_213, FindShortestSeparator_IsCallable_NoThrow_213) {
  State st;
  auto cmp = MakeComparator(&st);

  std::string start = "abc";
  leveldb::Slice limit("abd");
  EXPECT_NO_THROW(cmp.FindShortestSeparator(&start, limit));
  // We do not assert internal transformation; we only verify it’s callable.
}

TEST_F(ComparatorCWrapperTest_213, FindShortSuccessor_IsCallable_NoThrow_213) {
  State st;
  auto cmp = MakeComparator(&st);

  std::string key = "zzz";
  EXPECT_NO_THROW(cmp.FindShortSuccessor(&key));
  // As above, we avoid asserting internal transformations.
}
