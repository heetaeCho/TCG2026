#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include "leveldb/comparator.h"

// We need to replicate the struct definition since it's defined in c.cc
// This mirrors the struct from db/c.cc
namespace leveldb {
class Slice;
}

using leveldb::Slice;
using leveldb::Comparator;

struct leveldb_comparator_t : public Comparator {
  void* state_;
  void (*destructor_)(void*);
  int (*compare_)(void*, const char*, size_t, const char*, size_t);
  const char* (*name_)(void*);

  ~leveldb_comparator_t() override {
    if (destructor_) {
      (*destructor_)(state_);
    }
  }

  int Compare(const Slice& a, const Slice& b) const override {
    return (*compare_)(state_, a.data(), a.size(), b.data(), b.size());
  }

  const char* Name() const override { return (*name_)(state_); }

  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string* key) const override {}
};

// --- Test helper functions ---

static int TestCompareFunction(void* state, const char* a, size_t alen,
                               const char* b, size_t blen) {
  Slice sa(a, alen);
  Slice sb(b, blen);
  if (sa.ToString() < sb.ToString()) return -1;
  if (sa.ToString() > sb.ToString()) return 1;
  return 0;
}

static const char* TestNameFunction(void* state) {
  return "test_comparator";
}

static bool destructor_called = false;

static void TestDestructorFunction(void* state) {
  destructor_called = true;
}

static int call_count = 0;

static int CountingCompareFunction(void* state, const char* a, size_t alen,
                                   const char* b, size_t blen) {
  call_count++;
  return TestCompareFunction(state, a, alen, b, blen);
}

// Custom compare that uses state
static int StateBasedCompare(void* state, const char* a, size_t alen,
                             const char* b, size_t blen) {
  int* multiplier = static_cast<int*>(state);
  int result = TestCompareFunction(nullptr, a, alen, b, blen);
  return result * (*multiplier);
}

// --- Test fixture ---

class LevelDBComparatorTest_212 : public ::testing::Test {
 protected:
  void SetUp() override {
    destructor_called = false;
    call_count = 0;
  }

  leveldb_comparator_t* CreateDefaultComparator() {
    auto* cmp = new leveldb_comparator_t();
    cmp->state_ = nullptr;
    cmp->destructor_ = nullptr;
    cmp->compare_ = TestCompareFunction;
    cmp->name_ = TestNameFunction;
    return cmp;
  }
};

// Test that Compare returns 0 for equal slices
TEST_F(LevelDBComparatorTest_212, CompareEqualSlices_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("hello");
  Slice b("hello");
  EXPECT_EQ(0, cmp->Compare(a, b));
  delete cmp;
}

// Test that Compare returns negative when a < b
TEST_F(LevelDBComparatorTest_212, CompareLessThan_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("abc");
  Slice b("def");
  EXPECT_LT(cmp->Compare(a, b), 0);
  delete cmp;
}

// Test that Compare returns positive when a > b
TEST_F(LevelDBComparatorTest_212, CompareGreaterThan_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("xyz");
  Slice b("abc");
  EXPECT_GT(cmp->Compare(a, b), 0);
  delete cmp;
}

// Test Compare with empty slices
TEST_F(LevelDBComparatorTest_212, CompareEmptySlices_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("", 0);
  Slice b("", 0);
  EXPECT_EQ(0, cmp->Compare(a, b));
  delete cmp;
}

// Test Compare with one empty and one non-empty slice
TEST_F(LevelDBComparatorTest_212, CompareEmptyVsNonEmpty_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("", 0);
  Slice b("hello");
  EXPECT_LT(cmp->Compare(a, b), 0);
  EXPECT_GT(cmp->Compare(b, a), 0);
  delete cmp;
}

// Test that Name() returns the correct name
TEST_F(LevelDBComparatorTest_212, NameReturnsCorrectName_212) {
  auto* cmp = CreateDefaultComparator();
  EXPECT_STREQ("test_comparator", cmp->Name());
  delete cmp;
}

// Test that destructor calls the destructor function
TEST_F(LevelDBComparatorTest_212, DestructorCallsCallback_212) {
  auto* cmp = new leveldb_comparator_t();
  cmp->state_ = nullptr;
  cmp->destructor_ = TestDestructorFunction;
  cmp->compare_ = TestCompareFunction;
  cmp->name_ = TestNameFunction;

  EXPECT_FALSE(destructor_called);
  delete cmp;
  EXPECT_TRUE(destructor_called);
}

// Test that destructor does not crash when destructor_ is nullptr
TEST_F(LevelDBComparatorTest_212, DestructorWithNullCallback_212) {
  auto* cmp = new leveldb_comparator_t();
  cmp->state_ = nullptr;
  cmp->destructor_ = nullptr;
  cmp->compare_ = TestCompareFunction;
  cmp->name_ = TestNameFunction;

  // Should not crash
  delete cmp;
}

// Test that compare function is called with correct data and size
TEST_F(LevelDBComparatorTest_212, ComparePassesCorrectDataAndSize_212) {
  auto* cmp = new leveldb_comparator_t();
  cmp->state_ = nullptr;
  cmp->destructor_ = nullptr;
  cmp->name_ = TestNameFunction;
  cmp->compare_ = CountingCompareFunction;

  Slice a("test1");
  Slice b("test2");
  cmp->Compare(a, b);
  EXPECT_EQ(1, call_count);

  cmp->Compare(b, a);
  EXPECT_EQ(2, call_count);

  delete cmp;
}

// Test Compare with binary data (containing null bytes)
TEST_F(LevelDBComparatorTest_212, CompareWithBinaryData_212) {
  auto* cmp = CreateDefaultComparator();
  
  const char data_a[] = {'a', '\0', 'b'};
  const char data_b[] = {'a', '\0', 'c'};
  Slice a(data_a, 3);
  Slice b(data_b, 3);
  
  EXPECT_LT(cmp->Compare(a, b), 0);
  EXPECT_GT(cmp->Compare(b, a), 0);
  delete cmp;
}

// Test that state is passed correctly to the compare function
TEST_F(LevelDBComparatorTest_212, StatePassedToCompare_212) {
  auto* cmp = new leveldb_comparator_t();
  int multiplier = -1;  // Reverse the comparison
  cmp->state_ = &multiplier;
  cmp->destructor_ = nullptr;
  cmp->compare_ = StateBasedCompare;
  cmp->name_ = TestNameFunction;

  Slice a("abc");
  Slice b("def");

  // Normal would be -1 (a < b), but multiplier reverses it
  EXPECT_GT(cmp->Compare(a, b), 0);
  EXPECT_LT(cmp->Compare(b, a), 0);
  
  delete cmp;
}

// Test Compare with single character slices
TEST_F(LevelDBComparatorTest_212, CompareSingleCharSlices_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("a");
  Slice b("b");
  EXPECT_LT(cmp->Compare(a, b), 0);
  EXPECT_GT(cmp->Compare(b, a), 0);
  
  Slice c("a");
  EXPECT_EQ(0, cmp->Compare(a, c));
  delete cmp;
}

// Test Compare with prefix strings
TEST_F(LevelDBComparatorTest_212, ComparePrefixStrings_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("hello");
  Slice b("helloworld");
  EXPECT_LT(cmp->Compare(a, b), 0);
  EXPECT_GT(cmp->Compare(b, a), 0);
  delete cmp;
}

// Test Name with state-dependent name function
TEST_F(LevelDBComparatorTest_212, NameUsesState_212) {
  static const char* custom_name = "custom_name";
  auto name_fn = [](void* state) -> const char* {
    return static_cast<const char*>(state);
  };
  
  auto* cmp = new leveldb_comparator_t();
  cmp->state_ = const_cast<char*>(custom_name);
  cmp->destructor_ = nullptr;
  cmp->compare_ = TestCompareFunction;
  cmp->name_ = name_fn;
  
  EXPECT_STREQ("custom_name", cmp->Name());
  delete cmp;
}

// Test that the comparator works as a Comparator pointer (polymorphism)
TEST_F(LevelDBComparatorTest_212, WorksAsComparatorPointer_212) {
  auto* cmp = CreateDefaultComparator();
  const Comparator* base_ptr = cmp;

  Slice a("abc");
  Slice b("def");
  EXPECT_LT(base_ptr->Compare(a, b), 0);
  EXPECT_STREQ("test_comparator", base_ptr->Name());

  delete cmp;
}

// Test Compare symmetry: if Compare(a, b) < 0, then Compare(b, a) > 0
TEST_F(LevelDBComparatorTest_212, CompareSymmetry_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("apple");
  Slice b("banana");

  int result_ab = cmp->Compare(a, b);
  int result_ba = cmp->Compare(b, a);

  EXPECT_LT(result_ab, 0);
  EXPECT_GT(result_ba, 0);
  delete cmp;
}

// Test that FindShortestSeparator does not crash (it's a no-op)
TEST_F(LevelDBComparatorTest_212, FindShortestSeparatorNoOp_212) {
  auto* cmp = CreateDefaultComparator();
  std::string key = "hello";
  Slice limit("world");
  
  // Should not crash or modify key in a meaningful way (implementation is empty)
  cmp->FindShortestSeparator(&key, limit);
  delete cmp;
}

// Test that FindShortSuccessor does not crash (it's a no-op)
TEST_F(LevelDBComparatorTest_212, FindShortSuccessorNoOp_212) {
  auto* cmp = CreateDefaultComparator();
  std::string key = "hello";
  
  // Should not crash
  cmp->FindShortSuccessor(&key);
  delete cmp;
}

// Test Compare with very long strings
TEST_F(LevelDBComparatorTest_212, CompareVeryLongStrings_212) {
  auto* cmp = CreateDefaultComparator();
  std::string long_a(10000, 'a');
  std::string long_b(10000, 'b');
  Slice a(long_a);
  Slice b(long_b);
  
  EXPECT_LT(cmp->Compare(a, b), 0);
  EXPECT_GT(cmp->Compare(b, a), 0);
  
  std::string long_a2(10000, 'a');
  Slice a2(long_a2);
  EXPECT_EQ(0, cmp->Compare(a, a2));
  
  delete cmp;
}

// Test Compare with slices of different lengths but same prefix
TEST_F(LevelDBComparatorTest_212, CompareDifferentLengthsSamePrefix_212) {
  auto* cmp = CreateDefaultComparator();
  Slice a("abc");
  Slice b("abcd");
  
  EXPECT_LT(cmp->Compare(a, b), 0);
  EXPECT_GT(cmp->Compare(b, a), 0);
  delete cmp;
}
