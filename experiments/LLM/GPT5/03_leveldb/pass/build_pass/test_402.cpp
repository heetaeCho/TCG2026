// File: table/iterator_register_cleanup_test_402.cc

#include "leveldb/iterator.h"   // Use the real interface only
#include <gtest/gtest.h>
#include <memory>
#include <atomic>

namespace {

// A minimal concrete iterator to allow construction/destruction in tests.
// We do NOT rely on or access any internal state. We only need an instance
// to call RegisterCleanup and then observe callbacks upon destruction.
class TestIterator_402 : public leveldb::Iterator {
 public:
  TestIterator_402() = default;
  ~TestIterator_402() override = default;

  // The following overrides are stubs because we're not testing them.
  // We avoid touching internal state or behavior.
  bool Valid() const override { return false; }
  void SeekToFirst() override {}
  void SeekToLast() override {}
  void Seek(const leveldb::Slice&) override {}
  void Next() override {}
  void Prev() override {}
  leveldb::Slice key() const override { static leveldb::Slice dummy; return dummy; }
  leveldb::Slice value() const override { static leveldb::Slice dummy; return dummy; }
  leveldb::Status status() const override { static leveldb::Status ok; return ok; }
};

// Helpers for cleanup callbacks (external interactions we can observe).
struct PairCounter {
  std::atomic<int> a{0};
  std::atomic<int> b{0};
};

// Signature must match leveldb::CleanupFunction: void (*)(void*, void*)
void IncA_Add10ToB_402(void* arg1, void* arg2) {
  auto* pc = static_cast<PairCounter*>(arg1);
  auto* flag = static_cast<std::atomic<bool>*>(arg2);
  pc->a.fetch_add(1);
  pc->b.fetch_add(10);
  if (flag) { flag->store(true); }
}

void Add5ToA_And2ToB_402(void* arg1, void* arg2) {
  auto* pc = static_cast<PairCounter*>(arg1);
  auto* flag = static_cast<std::atomic<bool>*>(arg2);
  pc->a.fetch_add(5);
  pc->b.fetch_add(2);
  if (flag) { flag->store(true); }
}

}  // namespace

// ---- Tests ----

// Verifies the API precondition: passing a null function asserts.
// This is observable via a death test (assert fires).
TEST(IteratorRegisterCleanupTest_402, NullFunctionAsserts_402) {
#if GTEST_HAS_DEATH_TEST
  std::unique_ptr<TestIterator_402> it(new TestIterator_402());
  PairCounter pc;
  std::atomic<bool> flag{false};

  // Expect an assertion failure when function is nullptr.
  ASSERT_DEATH(
      {
        it->RegisterCleanup(nullptr, &pc, &flag);
      },
      "");  // No regex assumption about the message.
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

// Registering a single cleanup results in the callback being invoked
// when the iterator is destroyed (observable effect on passed-in args).
TEST(IteratorRegisterCleanupTest_402, SingleCleanupRunsOnDestruction_402) {
  PairCounter pc;
  std::atomic<bool> ran{false};

  {
    std::unique_ptr<TestIterator_402> it(new TestIterator_402());
    it->RegisterCleanup(&IncA_Add10ToB_402, &pc, &ran);
    // No other interaction; we rely on the observable effect at destruction.
  }  // ~Iterator runs here; callback should have executed.

  EXPECT_EQ(pc.a.load(), 1);
  EXPECT_EQ(pc.b.load(), 10);
  EXPECT_TRUE(ran.load());
}

// Registering multiple cleanups results in all of them being invoked
// on destruction. We do not assert call order (not part of the interface).
TEST(IteratorRegisterCleanupTest_402, MultipleCleanupsAllRun_402) {
  PairCounter pc;
  std::atomic<bool> ran1{false};
  std::atomic<bool> ran2{false};

  {
    std::unique_ptr<TestIterator_402> it(new TestIterator_402());
    it->RegisterCleanup(&IncA_Add10ToB_402, &pc, &ran1);
    it->RegisterCleanup(&Add5ToA_And2ToB_402, &pc, &ran2);
  }  // destruction triggers both cleanups

  // Both effects should be visible.
  // Totals: a = 1 + 5 = 6, b = 10 + 2 = 12.
  EXPECT_EQ(pc.a.load(), 6);
  EXPECT_EQ(pc.b.load(), 12);
  EXPECT_TRUE(ran1.load());
  EXPECT_TRUE(ran2.load());
}

// The same function can be registered more than once with different args;
// each registration must be observed independently when the iterator dies.
TEST(IteratorRegisterCleanupTest_402, DuplicateFunctionRegistrationsAreIndependent_402) {
  PairCounter pc1, pc2;
  std::atomic<bool> ran1{false};
  std::atomic<bool> ran2{false};

  {
    std::unique_ptr<TestIterator_402> it(new TestIterator_402());
    it->RegisterCleanup(&IncA_Add10ToB_402, &pc1, &ran1);
    it->RegisterCleanup(&IncA_Add10ToB_402, &pc2, &ran2);
  }

  EXPECT_EQ(pc1.a.load(), 1);
  EXPECT_EQ(pc1.b.load(), 10);
  EXPECT_TRUE(ran1.load());

  EXPECT_EQ(pc2.a.load(), 1);
  EXPECT_EQ(pc2.b.load(), 10);
  EXPECT_TRUE(ran2.load());
}

// Registering after an initial (possibly empty-head) registration should still work.
// This hits the path where an additional node may be allocated internally,
// but we ONLY assert the externally observable effects.
TEST(IteratorRegisterCleanupTest_402, RegisterAfterFirstAlsoRuns_402) {
  PairCounter pc;
  std::atomic<bool> ranFirst{false};
  std::atomic<bool> ranSecond{false};

  {
    std::unique_ptr<TestIterator_402> it(new TestIterator_402());
    it->RegisterCleanup(&Add5ToA_And2ToB_402, &pc, &ranFirst);
    it->RegisterCleanup(&IncA_Add10ToB_402, &pc, &ranSecond);
  }

  // Totals: a = 5 + 1 = 6, b = 2 + 10 = 12.
  EXPECT_EQ(pc.a.load(), 6);
  EXPECT_EQ(pc.b.load(), 12);
  EXPECT_TRUE(ranFirst.load());
  EXPECT_TRUE(ranSecond.load());
}
