#include <gtest/gtest.h>
#include <atomic>
#include <functional>

// Recreate the Hook interface based on the provided code
namespace re2 {
namespace hooks {

template <typename T>
class Hook {
 public:
  void Store(T* cb) { cb_.store(cb, std::memory_order_release); }
  T* Load() const { return cb_.load(std::memory_order_acquire); }

 private:
  std::atomic<T*> cb_;
};

}  // namespace hooks
}  // namespace re2

// Test fixture
class HookTest_283 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Type used for testing
using CallbackType = void(int);

// Test that Store and Load work for a basic function pointer type
TEST_F(HookTest_283, StoreAndLoadReturnsStoredPointer_283) {
  re2::hooks::Hook<int> hook;
  int value = 42;
  hook.Store(&value);
  EXPECT_EQ(hook.Load(), &value);
}

// Test that storing nullptr works
TEST_F(HookTest_283, StoreNullptrAndLoad_283) {
  re2::hooks::Hook<int> hook;
  hook.Store(nullptr);
  EXPECT_EQ(hook.Load(), nullptr);
}

// Test that storing different pointers overwrites correctly
TEST_F(HookTest_283, StoreOverwritesPreviousValue_283) {
  re2::hooks::Hook<int> hook;
  int value1 = 10;
  int value2 = 20;
  hook.Store(&value1);
  EXPECT_EQ(hook.Load(), &value1);
  hook.Store(&value2);
  EXPECT_EQ(hook.Load(), &value2);
}

// Test with a different type (double)
TEST_F(HookTest_283, StoreAndLoadWithDoubleType_283) {
  re2::hooks::Hook<double> hook;
  double val = 3.14;
  hook.Store(&val);
  EXPECT_EQ(hook.Load(), &val);
}

// Test that Load can be called multiple times and returns the same value
TEST_F(HookTest_283, LoadIsIdempotent_283) {
  re2::hooks::Hook<int> hook;
  int value = 99;
  hook.Store(&value);
  EXPECT_EQ(hook.Load(), hook.Load());
  EXPECT_EQ(hook.Load(), &value);
}

// Test storing nullptr after a valid pointer
TEST_F(HookTest_283, StoreNullAfterValidPointer_283) {
  re2::hooks::Hook<int> hook;
  int value = 55;
  hook.Store(&value);
  EXPECT_EQ(hook.Load(), &value);
  hook.Store(nullptr);
  EXPECT_EQ(hook.Load(), nullptr);
}

// Test with struct type
struct TestStruct {
  int x;
  int y;
};

TEST_F(HookTest_283, StoreAndLoadWithStructType_283) {
  re2::hooks::Hook<TestStruct> hook;
  TestStruct s{1, 2};
  hook.Store(&s);
  EXPECT_EQ(hook.Load(), &s);
  EXPECT_EQ(hook.Load()->x, 1);
  EXPECT_EQ(hook.Load()->y, 2);
}

// Test with function type (using typedef)
TEST_F(HookTest_283, StoreAndLoadWithFunctionType_283) {
  re2::hooks::Hook<CallbackType> hook;
  hook.Store(nullptr);
  EXPECT_EQ(hook.Load(), nullptr);
}

// Test multiple rapid stores
TEST_F(HookTest_283, MultipleRapidStores_283) {
  re2::hooks::Hook<int> hook;
  int values[100];
  for (int i = 0; i < 100; ++i) {
    values[i] = i;
    hook.Store(&values[i]);
  }
  // After all stores, Load should return the last stored pointer
  EXPECT_EQ(hook.Load(), &values[99]);
}

// Test const correctness of Load
TEST_F(HookTest_283, LoadIsConst_283) {
  re2::hooks::Hook<int> hook;
  int value = 77;
  hook.Store(&value);
  const re2::hooks::Hook<int>& const_ref = hook;
  EXPECT_EQ(const_ref.Load(), &value);
}
