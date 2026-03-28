#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

// A concrete iterator implementation for testing purposes
class TestIterator : public Iterator {
 public:
  TestIterator() : valid_(false) {}
  ~TestIterator() override {}

  bool Valid() const override { return valid_; }
  void SeekToFirst() override { valid_ = true; }
  void SeekToLast() override { valid_ = true; }
  void Seek(const Slice& target) override { valid_ = true; }
  void Next() override {}
  void Prev() override {}
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
static std::vector<std::pair<void*, void*>> g_cleanup_calls;

static void TestCleanupFunction(void* arg1, void* arg2) {
  g_cleanup_call_count++;
  g_last_arg1 = arg1;
  g_last_arg2 = arg2;
  g_cleanup_calls.push_back({arg1, arg2});
}

static void IncrementIntCleanup(void* arg1, void* arg2) {
  int* counter = reinterpret_cast<int*>(arg1);
  (*counter)++;
}

static void DeleteIntCleanup(void* arg1, void* arg2) {
  int* p = reinterpret_cast<int*>(arg1);
  delete p;
}

class IteratorTest_402 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_cleanup_call_count = 0;
    g_last_arg1 = nullptr;
    g_last_arg2 = nullptr;
    g_cleanup_calls.clear();
  }
};

// Test that registering a single cleanup function works and is called on destruction
TEST_F(IteratorTest_402, SingleCleanupCalledOnDestruction_402) {
  {
    TestIterator* iter = new TestIterator();
    int marker = 0;
    iter->RegisterCleanup(IncrementIntCleanup, &marker, nullptr);
    EXPECT_EQ(marker, 0);
    delete iter;
    EXPECT_EQ(marker, 1);
  }
}

// Test that multiple cleanup functions are all called on destruction
TEST_F(IteratorTest_402, MultipleCleanupsCalled_402) {
  {
    TestIterator* iter = new TestIterator();
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    iter->RegisterCleanup(IncrementIntCleanup, &counter1, nullptr);
    iter->RegisterCleanup(IncrementIntCleanup, &counter2, nullptr);
    iter->RegisterCleanup(IncrementIntCleanup, &counter3, nullptr);
    EXPECT_EQ(counter1, 0);
    EXPECT_EQ(counter2, 0);
    EXPECT_EQ(counter3, 0);
    delete iter;
    EXPECT_EQ(counter1, 1);
    EXPECT_EQ(counter2, 1);
    EXPECT_EQ(counter3, 1);
  }
}

// Test that cleanup receives the correct arg1 and arg2
TEST_F(IteratorTest_402, CleanupReceivesCorrectArgs_402) {
  {
    TestIterator* iter = new TestIterator();
    int val1 = 42;
    int val2 = 84;
    iter->RegisterCleanup(TestCleanupFunction, &val1, &val2);
    delete iter;
    EXPECT_EQ(g_cleanup_call_count, 1);
    EXPECT_EQ(g_last_arg1, &val1);
    EXPECT_EQ(g_last_arg2, &val2);
  }
}

// Test cleanup with nullptr arguments (arg1 and arg2 can be nullptr)
TEST_F(IteratorTest_402, CleanupWithNullArgs_402) {
  {
    TestIterator* iter = new TestIterator();
    iter->RegisterCleanup(TestCleanupFunction, nullptr, nullptr);
    delete iter;
    EXPECT_EQ(g_cleanup_call_count, 1);
    EXPECT_EQ(g_last_arg1, nullptr);
    EXPECT_EQ(g_last_arg2, nullptr);
  }
}

// Test that no cleanup is called if none is registered
TEST_F(IteratorTest_402, NoCleanupRegistered_402) {
  {
    TestIterator* iter = new TestIterator();
    delete iter;
    // No crash, no cleanup calls
    EXPECT_EQ(g_cleanup_call_count, 0);
  }
}

// Test that cleanup functions are executed (memory is freed properly)
TEST_F(IteratorTest_402, CleanupDeletesMemory_402) {
  {
    TestIterator* iter = new TestIterator();
    int* heap_int = new int(100);
    iter->RegisterCleanup(DeleteIntCleanup, heap_int, nullptr);
    delete iter;
    // If this doesn't leak, the cleanup was called. No way to check directly
    // without sanitizers, but the test verifies no crash.
  }
}

// Test registering many cleanup functions (boundary/stress test)
TEST_F(IteratorTest_402, ManyCleanups_402) {
  const int kNumCleanups = 100;
  int counters[kNumCleanups];
  for (int i = 0; i < kNumCleanups; i++) {
    counters[i] = 0;
  }

  {
    TestIterator* iter = new TestIterator();
    for (int i = 0; i < kNumCleanups; i++) {
      iter->RegisterCleanup(IncrementIntCleanup, &counters[i], nullptr);
    }
    delete iter;
  }

  for (int i = 0; i < kNumCleanups; i++) {
    EXPECT_EQ(counters[i], 1) << "Cleanup " << i << " was not called exactly once";
  }
}

// Test that multiple cleanups with different args are all called with correct args
TEST_F(IteratorTest_402, MultipleCleanupsCorrectArgs_402) {
  {
    TestIterator* iter = new TestIterator();
    int a1 = 1, a2 = 2, a3 = 3, a4 = 4;
    iter->RegisterCleanup(TestCleanupFunction, &a1, &a2);
    iter->RegisterCleanup(TestCleanupFunction, &a3, &a4);
    delete iter;
    EXPECT_EQ(g_cleanup_call_count, 2);
    // Verify both pairs of args were received
    bool found_pair1 = false, found_pair2 = false;
    for (auto& call : g_cleanup_calls) {
      if (call.first == &a1 && call.second == &a2) found_pair1 = true;
      if (call.first == &a3 && call.second == &a4) found_pair2 = true;
    }
    EXPECT_TRUE(found_pair1);
    EXPECT_TRUE(found_pair2);
  }
}

// Test that the iterator's basic virtual methods work as expected on TestIterator
TEST_F(IteratorTest_402, BasicIteratorInterface_402) {
  TestIterator iter;
  EXPECT_FALSE(iter.Valid());
  iter.SeekToFirst();
  EXPECT_TRUE(iter.Valid());
  EXPECT_EQ(iter.key().ToString(), "key");
  EXPECT_EQ(iter.value().ToString(), "value");
  EXPECT_TRUE(iter.status().ok());
}

// Test that iterator is not copyable (compile-time constraint - just verify basic use)
TEST_F(IteratorTest_402, IteratorNotCopyable_402) {
  // This test verifies that the deleted copy constructor/assignment
  // doesn't interfere with normal usage. We can't test a compile error
  // at runtime, but we verify the iterator works normally.
  TestIterator* iter = new TestIterator();
  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());
  delete iter;
}

// Test that registering cleanup with arg2 being non-null but arg1 null works
TEST_F(IteratorTest_402, CleanupNullArg1NonNullArg2_402) {
  {
    TestIterator* iter = new TestIterator();
    int val = 99;
    iter->RegisterCleanup(TestCleanupFunction, nullptr, &val);
    delete iter;
    EXPECT_EQ(g_cleanup_call_count, 1);
    EXPECT_EQ(g_last_arg1, nullptr);
    EXPECT_EQ(g_last_arg2, &val);
  }
}

}  // namespace leveldb
