#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <vector>

// Based on the interface provided, we need the Hook definition
namespace re2 {
namespace hooks {

template <typename T>
class Hook {
 public:
  void Store(T* cb) {
    cb_.store(cb, std::memory_order_release);
  }

  T* Load() const {
    return cb_.load(std::memory_order_acquire);
  }

 private:
  std::atomic<T*> cb_{nullptr};
};

}  // namespace hooks
}  // namespace re2

// Test fixture
class HookTest_284 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Type used for testing
using CallbackType = void(int);
using SimpleCallback = void();
using IntCallback = int(int, int);

// Test that a default-constructed Hook loads as nullptr
TEST_F(HookTest_284, DefaultConstructedLoadReturnsNullptr_284) {
  re2::hooks::Hook<SimpleCallback> hook;
  EXPECT_EQ(hook.Load(), nullptr);
}

// Test that Store followed by Load returns the stored pointer
TEST_F(HookTest_284, StoreAndLoadReturnsStoredPointer_284) {
  re2::hooks::Hook<CallbackType> hook;
  
  auto callback = [](int) {};
  CallbackType* cb_ptr = +callback;  // Convert lambda to function pointer
  
  hook.Store(cb_ptr);
  EXPECT_EQ(hook.Load(), cb_ptr);
}

// Test storing nullptr explicitly
TEST_F(HookTest_284, StoreNullptrAndLoad_284) {
  re2::hooks::Hook<SimpleCallback> hook;
  
  hook.Store(nullptr);
  EXPECT_EQ(hook.Load(), nullptr);
}

// Test overwriting a stored value with a new one
TEST_F(HookTest_284, StoreOverwritesPreviousValue_284) {
  re2::hooks::Hook<SimpleCallback> hook;
  
  auto cb1 = []() {};
  auto cb2 = []() {};
  SimpleCallback* ptr1 = +cb1;
  SimpleCallback* ptr2 = +cb2;
  
  hook.Store(ptr1);
  EXPECT_EQ(hook.Load(), ptr1);
  
  hook.Store(ptr2);
  EXPECT_EQ(hook.Load(), ptr2);
}

// Test overwriting a stored value with nullptr
TEST_F(HookTest_284, StoreNullptrOverwritesPreviousValue_284) {
  re2::hooks::Hook<SimpleCallback> hook;
  
  auto cb = []() {};
  SimpleCallback* ptr = +cb;
  
  hook.Store(ptr);
  EXPECT_NE(hook.Load(), nullptr);
  
  hook.Store(nullptr);
  EXPECT_EQ(hook.Load(), nullptr);
}

// Test multiple loads return the same value
TEST_F(HookTest_284, MultipleLoadsReturnSameValue_284) {
  re2::hooks::Hook<CallbackType> hook;
  
  auto callback = [](int) {};
  CallbackType* cb_ptr = +callback;
  
  hook.Store(cb_ptr);
  EXPECT_EQ(hook.Load(), hook.Load());
  EXPECT_EQ(hook.Load(), cb_ptr);
}

// Test with different template parameter types
TEST_F(HookTest_284, WorksWithDifferentCallbackTypes_284) {
  re2::hooks::Hook<IntCallback> hook;
  
  EXPECT_EQ(hook.Load(), nullptr);
  
  auto cb = [](int a, int b) -> int { return a + b; };
  IntCallback* ptr = +cb;
  
  hook.Store(ptr);
  EXPECT_EQ(hook.Load(), ptr);
}

// Test that the stored function pointer is actually callable
TEST_F(HookTest_284, StoredCallbackIsCallable_284) {
  re2::hooks::Hook<IntCallback> hook;
  
  auto cb = [](int a, int b) -> int { return a + b; };
  IntCallback* ptr = +cb;
  
  hook.Store(ptr);
  
  IntCallback* loaded = hook.Load();
  ASSERT_NE(loaded, nullptr);
  EXPECT_EQ(loaded(3, 4), 7);
}

// Test thread safety: concurrent Store and Load
TEST_F(HookTest_284, ConcurrentStoreAndLoad_284) {
  re2::hooks::Hook<SimpleCallback> hook;
  
  auto cb1 = []() {};
  auto cb2 = []() {};
  SimpleCallback* ptr1 = +cb1;
  SimpleCallback* ptr2 = +cb2;
  
  std::atomic<bool> start{false};
  
  std::thread writer([&]() {
    while (!start.load()) {}
    for (int i = 0; i < 10000; ++i) {
      hook.Store((i % 2 == 0) ? ptr1 : ptr2);
    }
  });
  
  std::thread reader([&]() {
    while (!start.load()) {}
    for (int i = 0; i < 10000; ++i) {
      SimpleCallback* loaded = hook.Load();
      // loaded must be nullptr, ptr1, or ptr2
      EXPECT_TRUE(loaded == nullptr || loaded == ptr1 || loaded == ptr2);
    }
  });
  
  start.store(true);
  writer.join();
  reader.join();
}

// Test repeated store of the same value
TEST_F(HookTest_284, RepeatedStoreOfSameValue_284) {
  re2::hooks::Hook<SimpleCallback> hook;
  
  auto cb = []() {};
  SimpleCallback* ptr = +cb;
  
  for (int i = 0; i < 100; ++i) {
    hook.Store(ptr);
    EXPECT_EQ(hook.Load(), ptr);
  }
}

// Test with a plain struct type (not just function pointers)
TEST_F(HookTest_284, WorksWithStructType_284) {
  struct MyStruct {
    int value;
  };
  
  re2::hooks::Hook<MyStruct> hook;
  EXPECT_EQ(hook.Load(), nullptr);
  
  MyStruct s{42};
  hook.Store(&s);
  EXPECT_EQ(hook.Load(), &s);
  EXPECT_EQ(hook.Load()->value, 42);
}
