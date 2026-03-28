// File: dfa_rwlocker_test_604.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>

using ::testing::InSequence;
using ::testing::StrictMock;
using ::testing::Times;

namespace re2 {

// ---- Test-side declarations to match the public interface ----

// External collaborator we are allowed to mock.
class CacheMutex {
public:
  virtual ~CacheMutex() = default;
  virtual void ReaderLock() {}
  virtual void ReaderUnlock() {}
  virtual void WriterLock() {}
  virtual void WriterUnlock() {}
};

// Class under test: only declare the public surface we need.
class DFA {
public:
  class RWLocker {
  public:
    explicit RWLocker(CacheMutex* mu);
    ~RWLocker();
    void LockForWriting();
    RWLocker(const RWLocker&) = delete;
    RWLocker& operator=(const RWLocker&) = delete;
  };
};

}  // namespace re2

// ---- Mock for the external collaborator ----
class MockCacheMutex : public re2::CacheMutex {
public:
  MOCK_METHOD(void, ReaderLock, (), (override));
  MOCK_METHOD(void, ReaderUnlock, (), (override));
  MOCK_METHOD(void, WriterLock, (), (override));
  MOCK_METHOD(void, WriterUnlock, (), (override));
};

// -----------------------------------------------------------------------------

TEST(DFA_RWLockerTest_604, ConstructorCallsReaderLock_604) {
  StrictMock<MockCacheMutex> mu;

  EXPECT_CALL(mu, ReaderLock()).Times(1);
  re2::DFA::RWLocker locker(&mu);

  // No further expectations: just verify construction side-effect.
}

TEST(DFA_RWLockerTest_604, DestructorWithoutUpgrade_CallsReaderUnlock_604) {
  StrictMock<MockCacheMutex> mu;

  {
    InSequence seq;  // Enforce sensible ordering of observable calls.
    EXPECT_CALL(mu, ReaderLock()).Times(1);
    EXPECT_CALL(mu, ReaderUnlock()).Times(1);
  }
  {
    re2::DFA::RWLocker locker(&mu);
    // Scope end triggers destructor; expectation above verifies the unlock.
  }
}

TEST(DFA_RWLockerTest_604, Upgrade_CallsReaderUnlockThenWriterLock_604) {
  StrictMock<MockCacheMutex> mu;

  {
    InSequence seq;
    EXPECT_CALL(mu, ReaderLock()).Times(1);
    EXPECT_CALL(mu, ReaderUnlock()).Times(1);
    EXPECT_CALL(mu, WriterLock()).Times(1);
    // No destructor expectation here; this test focuses on the upgrade call itself.
  }

  re2::DFA::RWLocker locker(&mu);
  locker.LockForWriting();
}

TEST(DFA_RWLockerTest_604, DestructorAfterUpgrade_ReleasesWriter_604) {
  StrictMock<MockCacheMutex> mu;

  {
    InSequence seq;
    EXPECT_CALL(mu, ReaderLock()).Times(1);
    EXPECT_CALL(mu, ReaderUnlock()).Times(1);
    EXPECT_CALL(mu, WriterLock()).Times(1);
    EXPECT_CALL(mu, WriterUnlock()).Times(1);  // Should release writer on destruction.
  }

  {
    re2::DFA::RWLocker locker(&mu);
    locker.LockForWriting();
    // Destructor at scope end; verifies WriterUnlock().
  }
}

TEST(DFA_RWLockerTest_604, LockForWriting_IsIdempotent_604) {
  StrictMock<MockCacheMutex> mu;

  {
    InSequence seq;
    EXPECT_CALL(mu, ReaderLock()).Times(1);
    EXPECT_CALL(mu, ReaderUnlock()).Times(1);
    EXPECT_CALL(mu, WriterLock()).Times(1);
    EXPECT_CALL(mu, WriterUnlock()).Times(1);
  }

  {
    re2::DFA::RWLocker locker(&mu);
    locker.LockForWriting();   // First upgrade triggers the transition.
    locker.LockForWriting();   // Subsequent call should not cause extra transitions.
  }
}

TEST(DFA_RWLockerTest_604, NotCopyableOrAssignable_604) {
  // Compile-time surface checks only; no internal logic assumed.
  static_assert(!std::is_copy_constructible<re2::DFA::RWLocker>::value,
                "RWLocker should not be copy-constructible");
  static_assert(!std::is_copy_assignable<re2::DFA::RWLocker>::value,
                "RWLocker should not be copy-assignable");
  SUCCEED();
}
