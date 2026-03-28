// File: dfa_rwlocker_test_450.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>

using ::testing::AtLeast;
using ::testing::NiceMock;

// ---- Minimal interface shims (interface-only; no reimplementation) ----
namespace re2 {

// Interface of the external collaborator used by RWLocker.
// Methods are virtual so we can mock externally observable interactions.
class CacheMutex {
 public:
  virtual ~CacheMutex() = default;
  virtual void ReaderLock() {}
  virtual void ReaderUnlock() {}
  virtual void WriterLock() {}
  virtual void WriterUnlock() {}
};

// Forward declaration of the class under test, matching the public interface.
class DFA {
 public:
  class RWLocker {
   public:
    explicit RWLocker(CacheMutex* mu);
    ~RWLocker();
    void LockForWriting();

    // Copy operations are deleted per provided interface snippet.
    RWLocker(const RWLocker&) = delete;
    RWLocker& operator=(const RWLocker&) = delete;
  };
};

}  // namespace re2

// ---- Mock of the external collaborator ----
class MockCacheMutex : public re2::CacheMutex {
 public:
  MOCK_METHOD(void, ReaderLock, (), (override));
  MOCK_METHOD(void, ReaderUnlock, (), (override));
  MOCK_METHOD(void, WriterLock, (), (override));
  MOCK_METHOD(void, WriterUnlock, (), (override));
};

// ---- Trait checks on copy-ability (interface-level) ----
static_assert(!std::is_copy_constructible<re2::DFA::RWLocker>::value,
              "RWLocker should not be copy constructible");
static_assert(!std::is_copy_assignable<re2::DFA::RWLocker>::value,
              "RWLocker should not be copy assignable");

// ---- Tests ----

// By default (no upgrade), destruction should release via ReaderUnlock.
// We also ensure WriterUnlock is NOT called in this path.
TEST(RWLockerTest_450, DestructorCallsReaderUnlockByDefault_450) {
  NiceMock<MockCacheMutex> mu;

  {
    re2::DFA::RWLocker lock(&mu);

    // Expect exactly one ReaderUnlock at destruction.
    EXPECT_CALL(mu, ReaderUnlock()).Times(1);
    // And no WriterUnlock in this code path.
    EXPECT_CALL(mu, WriterUnlock()).Times(0);
  }  // lock goes out of scope; expectations verified here
}

// After LockForWriting(), destruction should release via WriterUnlock.
// We also verify that LockForWriting() acquires the write lock at least once.
TEST(RWLockerTest_450, LockForWritingLeadsToWriterUnlock_450) {
  NiceMock<MockCacheMutex> mu;

  {
    re2::DFA::RWLocker lock(&mu);

    // LockForWriting should take a write lock (observable interaction).
    EXPECT_CALL(mu, WriterLock()).Times(AtLeast(1));
    lock.LockForWriting();

    // After upgrading, the destructor should unlock the writer lock.
    EXPECT_CALL(mu, WriterUnlock()).Times(1);
  }  // verify expectations on scope exit
}

// Calling LockForWriting() multiple times should not cause multiple unlocks.
// We only assert one WriterUnlock at destruction; WriterLock may happen at least once.
TEST(RWLockerTest_450, MultipleLockForWritingCalls_DoNotDoubleUnlock_450) {
  NiceMock<MockCacheMutex> mu;

  {
    re2::DFA::RWLocker lock(&mu);

    EXPECT_CALL(mu, WriterLock()).Times(AtLeast(1));
    lock.LockForWriting();
    // Call again to exercise boundary behavior (idempotency from the interface perspective).
    lock.LockForWriting();

    EXPECT_CALL(mu, WriterUnlock()).Times(1);
  }  // verify expectations when destroyed
}

