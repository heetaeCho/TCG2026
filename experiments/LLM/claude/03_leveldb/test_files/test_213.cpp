#include "gtest/gtest.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

#include <cstring>
#include <string>

// Replicate the struct definition as provided in the known dependencies
struct leveldb_comparator_t : public leveldb::Comparator {
  void* state_;
  void (*destructor_)(void*);
  int (*compare_)(void*, const char*, size_t, const char*, size_t);
  const char* (*name_)(void*);

  ~leveldb_comparator_t() override { (*destructor_)(state_); }

  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    return (*compare_)(state_, a.data(), a.size(), b.data(), b.size());
  }

  const char* Name() const override { return (*name_)(state_); }

  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}

  void FindShortSuccessor(std::string* key) const override {}
};

// Helper functions for setting up the comparator
namespace {

struct TestState {
  bool destructor_called;
  const char* name;
};

void TestDestructor(void* state) {
  static_cast<TestState*>(state)->destructor_called = true;
}

int TestCompare(void* state, const char* a, size_t alen, const char* b,
                size_t blen) {
  leveldb::Slice sa(a, alen);
  leveldb::Slice sb(b, blen);
  if (sa < sb) return -1;
  if (sa == sb) return 0;
  return 1;
}

const char* TestName(void* state) {
  return static_cast<TestState*>(state)->name;
}

}  // namespace

class LeveldbComparatorTest_213 : public ::testing::Test {
 protected:
  void SetUp() override {
    test_state_.destructor_called = false;
    test_state_.name = "test.comparator";
  }

  void TearDown() override {}

  TestState test_state_;
};

TEST_F(LeveldbComparatorTest_213, NameReturnsCorrectName_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};  // no-op to avoid double cleanup
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  EXPECT_STREQ(cmp.Name(), "test.comparator");
}

TEST_F(LeveldbComparatorTest_213, NameReturnsDifferentName_213) {
  test_state_.name = "another.comparator";

  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  EXPECT_STREQ(cmp.Name(), "another.comparator");
}

TEST_F(LeveldbComparatorTest_213, CompareEqualSlices_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("hello");
  leveldb::Slice b("hello");
  EXPECT_EQ(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, CompareLessThan_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("abc");
  leveldb::Slice b("def");
  EXPECT_LT(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, CompareGreaterThan_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("xyz");
  leveldb::Slice b("abc");
  EXPECT_GT(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, CompareEmptySlices_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("");
  leveldb::Slice b("");
  EXPECT_EQ(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, CompareEmptyVsNonEmpty_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("");
  leveldb::Slice b("a");
  EXPECT_LT(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, CompareNonEmptyVsEmpty_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("a");
  leveldb::Slice b("");
  EXPECT_GT(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, DestructorCallsCallback_213) {
  TestState* heap_state = new TestState;
  heap_state->destructor_called = false;
  heap_state->name = "destructor.test";

  bool destructor_invoked = false;

  {
    leveldb_comparator_t* cmp = new leveldb_comparator_t;
    cmp->state_ = heap_state;
    cmp->destructor_ = [](void* s) {
      static_cast<TestState*>(s)->destructor_called = true;
    };
    cmp->compare_ = TestCompare;
    cmp->name_ = TestName;

    delete cmp;
  }

  EXPECT_TRUE(heap_state->destructor_called);
  delete heap_state;
}

TEST_F(LeveldbComparatorTest_213, ComparePrefixSlices_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("abc");
  leveldb::Slice b("abcd");
  EXPECT_LT(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, CompareLongerVsShorterPrefix_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("abcd");
  leveldb::Slice b("abc");
  EXPECT_GT(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, NameWithEmptyString_213) {
  test_state_.name = "";

  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  EXPECT_STREQ(cmp.Name(), "");
}

TEST_F(LeveldbComparatorTest_213, FindShortestSeparatorDoesNotCrash_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  std::string key = "abc";
  leveldb::Slice limit("xyz");
  // FindShortestSeparator should not crash (it's a no-op)
  cmp.FindShortestSeparator(&key, limit);
}

TEST_F(LeveldbComparatorTest_213, FindShortSuccessorDoesNotCrash_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  std::string key = "abc";
  // FindShortSuccessor should not crash (it's a no-op)
  cmp.FindShortSuccessor(&key);
}

TEST_F(LeveldbComparatorTest_213, CompareWithBinaryData_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  std::string s1("ab\0c", 4);
  std::string s2("ab\0d", 4);
  leveldb::Slice a(s1);
  leveldb::Slice b(s2);
  EXPECT_LT(cmp.Compare(a, b), 0);
}

TEST_F(LeveldbComparatorTest_213, CompareSymmetry_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("foo");
  leveldb::Slice b("bar");

  int result_ab = cmp.Compare(a, b);
  int result_ba = cmp.Compare(b, a);

  // If a > b then b < a
  if (result_ab > 0) {
    EXPECT_LT(result_ba, 0);
  } else if (result_ab < 0) {
    EXPECT_GT(result_ba, 0);
  } else {
    EXPECT_EQ(result_ba, 0);
  }
}

TEST_F(LeveldbComparatorTest_213, StateIsPassedToCallbacks_213) {
  // Verify that the state pointer is correctly forwarded
  bool name_received_correct_state = false;
  bool compare_received_correct_state = false;

  struct CustomState {
    bool* name_flag;
    bool* compare_flag;
  };

  CustomState custom_state;
  custom_state.name_flag = &name_received_correct_state;
  custom_state.compare_flag = &compare_received_correct_state;

  leveldb_comparator_t cmp;
  cmp.state_ = &custom_state;
  cmp.destructor_ = [](void*) {};
  cmp.name_ = [](void* s) -> const char* {
    auto* cs = static_cast<CustomState*>(s);
    *cs->name_flag = true;
    return "custom";
  };
  cmp.compare_ = [](void* s, const char*, size_t, const char*,
                     size_t) -> int {
    auto* cs = static_cast<CustomState*>(s);
    *cs->compare_flag = true;
    return 0;
  };

  cmp.Name();
  EXPECT_TRUE(name_received_correct_state);

  leveldb::Slice a("x");
  leveldb::Slice b("y");
  cmp.Compare(a, b);
  EXPECT_TRUE(compare_received_correct_state);
}

TEST_F(LeveldbComparatorTest_213, CompareSingleCharSlices_213) {
  leveldb_comparator_t cmp;
  cmp.state_ = &test_state_;
  cmp.destructor_ = [](void*) {};
  cmp.compare_ = TestCompare;
  cmp.name_ = TestName;

  leveldb::Slice a("a");
  leveldb::Slice b("b");
  EXPECT_LT(cmp.Compare(a, b), 0);

  leveldb::Slice c("z");
  leveldb::Slice d("a");
  EXPECT_GT(cmp.Compare(c, d), 0);
}
