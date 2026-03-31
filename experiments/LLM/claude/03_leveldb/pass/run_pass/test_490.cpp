#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

// A concrete implementation of Iterator for testing purposes
// Since Iterator is abstract, we need a minimal concrete subclass
class TestIterator : public Iterator {
 public:
  TestIterator() : valid_(false) {}

  bool Valid() const override { return valid_; }
  void SeekToFirst() override { valid_ = true; pos_ = 0; }
  void SeekToLast() override { valid_ = true; pos_ = 100; }
  void Seek(const Slice& target) override { valid_ = true; }
  void Next() override {
    pos_++;
    if (pos_ > 100) valid_ = false;
  }
  void Prev() override {
    pos_--;
    if (pos_ < 0) valid_ = false;
  }
  Slice key() const override { return Slice("key"); }
  Slice value() const override { return Slice("value"); }
  Status status() const override { return Status::OK(); }

  void SetValid(bool v) { valid_ = v; }

 private:
  bool valid_;
  int pos_ = 0;
};

// Cleanup function used in tests
static void CleanupFunc(void* arg1, void* arg2) {
  int* counter = reinterpret_cast<int*>(arg1);
  (*counter)++;
}

static void CleanupFuncWithArg2(void* arg1, void* arg2) {
  int* counter = reinterpret_cast<int*>(arg1);
  int* increment = reinterpret_cast<int*>(arg2);
  (*counter) += (*increment);
}

// Test fixture
class IteratorTest_490 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a newly created iterator can be destroyed without issues
// (no cleanup functions registered)
TEST_F(IteratorTest_490, DefaultConstructorAndDestructor_490) {
  TestIterator* iter = new TestIterator();
  // Should be safe to delete with no registered cleanups
  delete iter;
}

// Test Valid() returns false for a fresh iterator
TEST_F(IteratorTest_490, InitiallyInvalid_490) {
  TestIterator iter;
  EXPECT_FALSE(iter.Valid());
}

// Test SeekToFirst makes iterator valid
TEST_F(IteratorTest_490, SeekToFirstMakesValid_490) {
  TestIterator iter;
  iter.SeekToFirst();
  EXPECT_TRUE(iter.Valid());
}

// Test SeekToLast makes iterator valid
TEST_F(IteratorTest_490, SeekToLastMakesValid_490) {
  TestIterator iter;
  iter.SeekToLast();
  EXPECT_TRUE(iter.Valid());
}

// Test Seek makes iterator valid
TEST_F(IteratorTest_490, SeekMakesValid_490) {
  TestIterator iter;
  iter.Seek(Slice("target"));
  EXPECT_TRUE(iter.Valid());
}

// Test key() and value() return expected values
TEST_F(IteratorTest_490, KeyAndValue_490) {
  TestIterator iter;
  iter.SeekToFirst();
  EXPECT_EQ(iter.key().ToString(), "key");
  EXPECT_EQ(iter.value().ToString(), "value");
}

// Test status() returns OK
TEST_F(IteratorTest_490, StatusIsOK_490) {
  TestIterator iter;
  EXPECT_TRUE(iter.status().ok());
}

// Test RegisterCleanup: single cleanup function is called on destruction
TEST_F(IteratorTest_490, RegisterSingleCleanup_490) {
  int counter = 0;
  {
    TestIterator iter;
    iter.RegisterCleanup(&CleanupFunc, &counter, nullptr);
  }
  EXPECT_EQ(counter, 1);
}

// Test RegisterCleanup: multiple cleanup functions are all called on destruction
TEST_F(IteratorTest_490, RegisterMultipleCleanups_490) {
  int counter = 0;
  {
    TestIterator iter;
    iter.RegisterCleanup(&CleanupFunc, &counter, nullptr);
    iter.RegisterCleanup(&CleanupFunc, &counter, nullptr);
    iter.RegisterCleanup(&CleanupFunc, &counter, nullptr);
  }
  EXPECT_EQ(counter, 3);
}

// Test RegisterCleanup: cleanup function receives correct arg2
TEST_F(IteratorTest_490, RegisterCleanupWithArg2_490) {
  int counter = 0;
  int increment = 5;
  {
    TestIterator iter;
    iter.RegisterCleanup(&CleanupFuncWithArg2, &counter, &increment);
  }
  EXPECT_EQ(counter, 5);
}

// Test RegisterCleanup: mixed cleanup functions
TEST_F(IteratorTest_490, RegisterMixedCleanups_490) {
  int counter1 = 0;
  int counter2 = 0;
  int increment = 10;
  {
    TestIterator iter;
    iter.RegisterCleanup(&CleanupFunc, &counter1, nullptr);
    iter.RegisterCleanup(&CleanupFuncWithArg2, &counter2, &increment);
    iter.RegisterCleanup(&CleanupFunc, &counter1, nullptr);
  }
  EXPECT_EQ(counter1, 2);
  EXPECT_EQ(counter2, 10);
}

// Test that no cleanup is called if none registered (no crash)
TEST_F(IteratorTest_490, NoCleanupRegistered_490) {
  TestIterator* iter = new TestIterator();
  // Deleting without any registered cleanups should not crash
  EXPECT_NO_FATAL_FAILURE(delete iter);
}

// Test Next() operation
TEST_F(IteratorTest_490, NextOperation_490) {
  TestIterator iter;
  iter.SeekToFirst();
  EXPECT_TRUE(iter.Valid());
  iter.Next();
  EXPECT_TRUE(iter.Valid());
}

// Test Prev() operation
TEST_F(IteratorTest_490, PrevOperation_490) {
  TestIterator iter;
  iter.SeekToLast();
  EXPECT_TRUE(iter.Valid());
  iter.Prev();
  EXPECT_TRUE(iter.Valid());
}

// Test that registering a large number of cleanup functions works correctly
TEST_F(IteratorTest_490, RegisterManyCleanups_490) {
  int counter = 0;
  {
    TestIterator iter;
    for (int i = 0; i < 100; i++) {
      iter.RegisterCleanup(&CleanupFunc, &counter, nullptr);
    }
  }
  EXPECT_EQ(counter, 100);
}

// Test that cleanup with nullptr function pointer is handled
// (RegisterCleanup should assert/require non-null, but we test the valid case)
TEST_F(IteratorTest_490, CleanupWithValidFunction_490) {
  int counter = 0;
  {
    TestIterator iter;
    iter.RegisterCleanup(&CleanupFunc, &counter, nullptr);
  }
  EXPECT_EQ(counter, 1);
}

// Test that dynamically allocated iterator with cleanup works
TEST_F(IteratorTest_490, DynamicAllocationWithCleanup_490) {
  int counter = 0;
  TestIterator* iter = new TestIterator();
  iter->RegisterCleanup(&CleanupFunc, &counter, nullptr);
  iter->RegisterCleanup(&CleanupFunc, &counter, nullptr);
  delete iter;
  EXPECT_EQ(counter, 2);
}

}  // namespace leveldb
