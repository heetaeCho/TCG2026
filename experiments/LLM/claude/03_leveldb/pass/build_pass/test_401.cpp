#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

// A concrete implementation of Iterator for testing purposes
class TestIterator : public Iterator {
 public:
  TestIterator() : valid_(false) {}

  bool Valid() const override { return valid_; }
  void SeekToFirst() override { valid_ = true; }
  void SeekToLast() override { valid_ = true; }
  void Seek(const Slice& target) override { valid_ = true; }
  void Next() override { valid_ = false; }
  void Prev() override { valid_ = false; }
  Slice key() const override { return Slice("key"); }
  Slice value() const override { return Slice("value"); }
  Status status() const override { return Status::OK(); }

 private:
  bool valid_;
};

// Global tracking variables for cleanup function calls
static int g_cleanup_call_count = 0;
static void* g_last_arg1 = nullptr;
static void* g_last_arg2 = nullptr;

static void CleanupFunc(void* arg1, void* arg2) {
  g_cleanup_call_count++;
  g_last_arg1 = arg1;
  g_last_arg2 = arg2;
}

static int g_cleanup_order_index = 0;
static int g_cleanup_order[10];

static void CleanupFuncOrdered1(void* arg1, void* arg2) {
  g_cleanup_order[g_cleanup_order_index++] = 1;
}

static void CleanupFuncOrdered2(void* arg1, void* arg2) {
  g_cleanup_order[g_cleanup_order_index++] = 2;
}

static void CleanupFuncOrdered3(void* arg1, void* arg2) {
  g_cleanup_order[g_cleanup_order_index++] = 3;
}

class IteratorTest_401 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_cleanup_call_count = 0;
    g_last_arg1 = nullptr;
    g_last_arg2 = nullptr;
    g_cleanup_order_index = 0;
    for (int i = 0; i < 10; i++) {
      g_cleanup_order[i] = 0;
    }
  }
};

// Test that an iterator can be created and destroyed without cleanup functions
TEST_F(IteratorTest_401, CreateAndDestroyWithoutCleanup_401) {
  TestIterator* iter = new TestIterator();
  // Should not crash on destruction with no registered cleanups
  delete iter;
}

// Test that a single cleanup function is called on destruction
TEST_F(IteratorTest_401, SingleCleanupCalledOnDestruction_401) {
  TestIterator* iter = new TestIterator();
  int dummy1 = 42;
  int dummy2 = 84;
  iter->RegisterCleanup(CleanupFunc, &dummy1, &dummy2);
  delete iter;
  EXPECT_EQ(g_cleanup_call_count, 1);
  EXPECT_EQ(g_last_arg1, &dummy1);
  EXPECT_EQ(g_last_arg2, &dummy2);
}

// Test that multiple cleanup functions are all called on destruction
TEST_F(IteratorTest_401, MultipleCleanupsCalled_401) {
  TestIterator* iter = new TestIterator();
  iter->RegisterCleanup(CleanupFunc, nullptr, nullptr);
  iter->RegisterCleanup(CleanupFunc, nullptr, nullptr);
  iter->RegisterCleanup(CleanupFunc, nullptr, nullptr);
  delete iter;
  EXPECT_EQ(g_cleanup_call_count, 3);
}

// Test cleanup functions receive correct arguments
TEST_F(IteratorTest_401, CleanupReceivesCorrectArguments_401) {
  TestIterator* iter = new TestIterator();
  int val1 = 100;
  int val2 = 200;
  iter->RegisterCleanup(CleanupFunc, &val1, &val2);
  delete iter;
  EXPECT_EQ(g_last_arg1, &val1);
  EXPECT_EQ(g_last_arg2, &val2);
}

// Test cleanup functions with null arguments
TEST_F(IteratorTest_401, CleanupWithNullArguments_401) {
  TestIterator* iter = new TestIterator();
  iter->RegisterCleanup(CleanupFunc, nullptr, nullptr);
  delete iter;
  EXPECT_EQ(g_cleanup_call_count, 1);
  EXPECT_EQ(g_last_arg1, nullptr);
  EXPECT_EQ(g_last_arg2, nullptr);
}

// Test ordering of cleanup calls (all cleanups run in registered order)
TEST_F(IteratorTest_401, CleanupOrderIsPreserved_401) {
  TestIterator* iter = new TestIterator();
  iter->RegisterCleanup(CleanupFuncOrdered1, nullptr, nullptr);
  iter->RegisterCleanup(CleanupFuncOrdered2, nullptr, nullptr);
  iter->RegisterCleanup(CleanupFuncOrdered3, nullptr, nullptr);
  delete iter;
  EXPECT_EQ(g_cleanup_order_index, 3);
  // The head cleanup runs first, then the linked list
  EXPECT_EQ(g_cleanup_order[0], 1);
  EXPECT_EQ(g_cleanup_order[1], 2);
  EXPECT_EQ(g_cleanup_order[2], 3);
}

// Test basic iterator interface methods
TEST_F(IteratorTest_401, ValidReturnsFalseInitially_401) {
  TestIterator iter;
  EXPECT_FALSE(iter.Valid());
}

TEST_F(IteratorTest_401, SeekToFirstMakesValid_401) {
  TestIterator iter;
  iter.SeekToFirst();
  EXPECT_TRUE(iter.Valid());
}

TEST_F(IteratorTest_401, SeekToLastMakesValid_401) {
  TestIterator iter;
  iter.SeekToLast();
  EXPECT_TRUE(iter.Valid());
}

TEST_F(IteratorTest_401, SeekMakesValid_401) {
  TestIterator iter;
  iter.Seek("target");
  EXPECT_TRUE(iter.Valid());
}

TEST_F(IteratorTest_401, NextInvalidatesIterator_401) {
  TestIterator iter;
  iter.SeekToFirst();
  EXPECT_TRUE(iter.Valid());
  iter.Next();
  EXPECT_FALSE(iter.Valid());
}

TEST_F(IteratorTest_401, PrevInvalidatesIterator_401) {
  TestIterator iter;
  iter.SeekToFirst();
  EXPECT_TRUE(iter.Valid());
  iter.Prev();
  EXPECT_FALSE(iter.Valid());
}

TEST_F(IteratorTest_401, KeyReturnsSlice_401) {
  TestIterator iter;
  iter.SeekToFirst();
  Slice k = iter.key();
  EXPECT_EQ(k.ToString(), "key");
}

TEST_F(IteratorTest_401, ValueReturnsSlice_401) {
  TestIterator iter;
  iter.SeekToFirst();
  Slice v = iter.value();
  EXPECT_EQ(v.ToString(), "value");
}

TEST_F(IteratorTest_401, StatusReturnsOK_401) {
  TestIterator iter;
  EXPECT_TRUE(iter.status().ok());
}

// Test that cleanup with a dynamically allocated argument properly receives it
TEST_F(IteratorTest_401, CleanupWithDynamicArgs_401) {
  TestIterator* iter = new TestIterator();
  int* heap_val1 = new int(999);
  int* heap_val2 = new int(888);
  
  // Register a cleanup that will verify and delete the heap values
  static int* s_heap1 = nullptr;
  static int* s_heap2 = nullptr;
  s_heap1 = heap_val1;
  s_heap2 = heap_val2;
  
  iter->RegisterCleanup(CleanupFunc, heap_val1, heap_val2);
  delete iter;
  
  EXPECT_EQ(g_last_arg1, heap_val1);
  EXPECT_EQ(g_last_arg2, heap_val2);
  
  // Clean up our heap allocations
  delete heap_val1;
  delete heap_val2;
}

// Test many cleanup registrations
TEST_F(IteratorTest_401, ManyCleanupRegistrations_401) {
  TestIterator* iter = new TestIterator();
  const int kNumCleanups = 100;
  for (int i = 0; i < kNumCleanups; i++) {
    iter->RegisterCleanup(CleanupFunc, nullptr, nullptr);
  }
  delete iter;
  EXPECT_EQ(g_cleanup_call_count, kNumCleanups);
}

}  // namespace leveldb
