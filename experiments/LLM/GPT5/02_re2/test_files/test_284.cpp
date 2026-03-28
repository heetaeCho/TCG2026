// File: hook_test_284.cc
#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>

// If there's no public header for Hook<T>, include the provided implementation.
// Adjust the include path to match your project layout.
#include "re2/re2/re2.cc"

using re2::hooks::Hook;

namespace {

struct Payload {
  int a{0};
  int b{0};
};

// ---------- Normal operation ----------

TEST(HookTest_284, StoreThenLoadSamePointer_284) {
  Hook<Payload> hook;
  auto* p = new Payload();
  p->a = 10; p->b = 20;

  hook.Store(p);
  EXPECT_EQ(hook.Load(), p);

  delete p;
}

TEST(HookTest_284, OverwriteReturnsLatestPointer_284) {
  Hook<Payload> hook;

  auto* p1 = new Payload();
  p1->a = 1; p1->b = 2;

  auto* p2 = new Payload();
  p2->a = 3; p2->b = 4;

  hook.Store(p1);
  EXPECT_EQ(hook.Load(), p1);

  hook.Store(p2);
  EXPECT_EQ(hook.Load(), p2);

  delete p1;
  delete p2;
}

// ---------- Boundary conditions ----------

TEST(HookTest_284, StoreNullThenLoadNull_284) {
  Hook<Payload> hook;

  hook.Store(nullptr);
  EXPECT_EQ(hook.Load(), nullptr);
}

TEST(HookTest_284, ConstLoadIsUsable_284) {
  Hook<Payload> hook;

  auto* p = new Payload();
  hook.Store(p);

  const Hook<Payload>& chook = hook;  // Ensure Load() is const-correct
  EXPECT_EQ(chook.Load(), p);

  delete p;
}

// ---------- Concurrency / observable synchronization behavior ----------

TEST(HookTest_284, AcquireReleasePublishesPayload_284) {
  Hook<Payload> hook;
  // Ensure a known initial observable state via the public API.
  hook.Store(nullptr);

  auto* published = new Payload();

  std::thread producer([&]{
    // Initialize the object fully before publication.
    published->a = 123;
    published->b = 456;

    // Publish pointer through Hook; consumer will observe via Load().
    hook.Store(published);
  });

  std::thread consumer([&]{
    Payload* seen = nullptr;
    // Spin until a non-null is observed via the public API.
    while ((seen = hook.Load()) == nullptr) {
      // Optional small pause to reduce busy-spin in test environments.
      std::this_thread::yield();
    }
    // After Load() observes the pointer, the payload's fields should also be visible.
    EXPECT_EQ(seen->a, 123);
    EXPECT_EQ(seen->b, 456);
  });

  producer.join();
  consumer.join();

  delete published;
}

// This stress-like test only checks that the final pointer is one that
// was previously stored (no assumptions about "which" thread wins).
TEST(HookTest_284, FinalValueIsFromSomePublisher_284) {
  Hook<Payload> hook;
  hook.Store(nullptr);

  constexpr int kThreads = 8;
  std::vector<Payload*> pool;
  pool.reserve(kThreads);
  std::vector<std::thread> threads;

  for (int i = 0; i < kThreads; ++i) {
    auto* p = new Payload();
    p->a = i;
    p->b = i * 10;
    pool.push_back(p);
  }

  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([&, i]{
      // Each publisher publishes a distinct pointer.
      hook.Store(pool[i]);
      // Slight variability to alter interleaving (still black-box).
      std::this_thread::yield();
    });
  }

  for (auto& t : threads) t.join();

  Payload* final_ptr = hook.Load();
  // The final observed pointer must be one that was published.
  bool found = std::find(pool.begin(), pool.end(), final_ptr) != pool.end();
  EXPECT_TRUE(found);

  for (auto* p : pool) delete p;
}

}  // namespace
