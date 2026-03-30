// File: db/c_iter_next_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Minimal interface stubs from the provided headers (no internal logic).
namespace leveldb {
class Iterator {
 public:
  Iterator() = default;
  Iterator(const Iterator&) = delete;
  Iterator& operator=(const Iterator&) = delete;
  virtual ~Iterator() = default;

  // Signatures as given in the prompt (we only need Next() for these tests).
  virtual void Next();
};
}  // namespace leveldb

// C wrapper struct from db/c.cc (provided).
struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

// Function under test (provided in db/c.cc).
extern "C" void leveldb_iter_next(leveldb_iterator_t* iter);

// ---- Mock & Fixture ---------------------------------------------------------

class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(void, Next, (), (override));
};

class IterNextTest_239 : public ::testing::Test {
 protected:
  leveldb_iterator_t c_iter_{};
  MockIterator mock_{};

  void SetUp() override {
    c_iter_.rep = &mock_;
  }
};

// ---- Tests ------------------------------------------------------------------

// [Normal] Calls Next() exactly once on the underlying Iterator.
TEST_F(IterNextTest_239, CallsNextOnRep_239) {
  EXPECT_CALL(mock_, Next()).Times(1);

  leveldb_iter_next(&c_iter_);
}

// [Normal] Multiple calls to the wrapper result in the same number of Next() calls.
TEST_F(IterNextTest_239, MultipleCallsInvokeNextMultipleTimes_239) {
  EXPECT_CALL(mock_, Next()).Times(3);

  leveldb_iter_next(&c_iter_);
  leveldb_iter_next(&c_iter_);
  leveldb_iter_next(&c_iter_);
}

// [Boundary/Error-Observable] Passing a nullptr iter should cause a hard failure (death).
// This validates that the wrapper does not perform null checks and will crash on misuse.
// Use death test to capture the observable failure behavior.
TEST(IterNextDeathTest_239, NullIteratorPointerCausesDeath_239) {
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH(
      {
        leveldb_iter_next(nullptr);
      },
      ".*");
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

// [Boundary/Error-Observable] Passing a struct with null rep should cause a hard failure (death).
TEST(IterNextDeathTest_239, NullRepPointerCausesDeath_239) {
#if GTEST_HAS_DEATH_TEST
  leveldb_iterator_t bad_iter{};
  bad_iter.rep = nullptr;

  EXPECT_DEATH(
      {
        leveldb_iter_next(&bad_iter);
      },
      ".*");
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}
