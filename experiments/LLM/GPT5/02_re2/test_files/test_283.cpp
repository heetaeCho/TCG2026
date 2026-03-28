// File: tests/re2_hook_test_283.cc
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>

// Bring in the provided implementation so we can instantiate the type.
// If your build already compiles this TU separately, switch this include
// to the corresponding header instead (e.g., "re2/re2.h").
#include "re2/re2.cc"

using namespace std::chrono_literals;

namespace {

struct Dummy {
  int v{0};
};

}  // namespace

// Verifies: Storing a pointer and then loading returns the exact same pointer.
TEST(HookTest_283, StoreAndLoadSamePointer_283) {
  re2::hooks::Hook<Dummy> hook;
  Dummy a{1};

  hook.Store(&a);
  EXPECT_EQ(hook.Load(), &a);
}

// Verifies: Multiple stores — the most recent store is what we observe via Load.
TEST(HookTest_283, MultipleStoresReturnMostRecent_283) {
  re2::hooks::Hook<Dummy> hook;
  Dummy a{1}, b{2};

  hook.Store(&a);
  EXPECT_EQ(hook.Load(), &a);

  hook.Store(&b);
  EXPECT_EQ(hook.Load(), &b);
}

// Verifies: Storing nullptr is observable via Load (explicitly setting "no callback").
TEST(HookTest_283, StoreNullClearsPointer_283) {
  re2::hooks::Hook<Dummy> hook;
  Dummy a{42};

  hook.Store(&a);
  ASSERT_EQ(hook.Load(), &a);

  hook.Store(nullptr);
  EXPECT_EQ(hook.Load(), nullptr);
}

// Verifies: Load can be called on a const reference (API const-correctness).
TEST(HookTest_283, LoadWorksOnConstInstance_283) {
  re2::hooks::Hook<Dummy> hook;
  Dummy a{7};

  hook.Store(&a);
  const re2::hooks::Hook<Dummy>& cref = hook;
  EXPECT_EQ(cref.Load(), &a);
}

// Verifies (concurrency): If we perform a clearly-last Store after other threads
// finish, then Load observes that last stored pointer.
TEST(HookTest_283, ConcurrentStores_LastWriteWins_283) {
  re2::hooks::Hook<Dummy> hook;
  Dummy a{1}, b{2}, c{3}, last{999};

  std::thread t1([&] { hook.Store(&a); });
  std::thread t2([&] { hook.Store(&b); });
  std::thread t3([&] { hook.Store(&c); });

  t1.join();
  t2.join();
  t3.join();

  // Definitively the last write.
  hook.Store(&last);

  // Expect the last written pointer to be visible after threads join.
  EXPECT_EQ(hook.Load(), &last);
}

// Verifies (cross-thread visibility): A store in another thread eventually
// becomes visible via Load in this thread (without assuming any specific memory order).
TEST(HookTest_283, CrossThreadVisibility_283) {
  re2::hooks::Hook<Dummy> hook;
  Dummy x{123};

  std::atomic<bool> started{false};

  std::thread writer([&] {
    started.store(true, std::memory_order_release);
    // Small delay to increase likelihood Load spins before Store.
    std::this_thread::sleep_for(1ms);
    hook.Store(&x);
  });

  // Wait for writer to start.
  while (!started.load(std::memory_order_acquire)) {
    std::this_thread::yield();
  }

  // Try for a bounded period to observe the stored pointer.
  bool seen = false;
  for (int i = 0; i < 500; ++i) {
    if (hook.Load() == &x) {
      seen = true;
      break;
    }
    // Yield/sleep briefly to avoid busy-waiting.
    std::this_thread::yield();
    std::this_thread::sleep_for(1ms);
  }

  writer.join();
  EXPECT_TRUE(seen) << "Load did not observe the pointer stored by another thread within the time bound";
}

// Verifies: Template works with different T; using a primitive to ensure genericity.
// (We only check pointer identity via public API.)
TEST(HookTest_283, WorksWithDifferentTypes_283) {
  re2::hooks::Hook<int> hook;
  int a = 10, b = 20;

  hook.Store(&a);
  EXPECT_EQ(hook.Load(), &a);

  hook.Store(&b);
  EXPECT_EQ(hook.Load(), &b);
}
