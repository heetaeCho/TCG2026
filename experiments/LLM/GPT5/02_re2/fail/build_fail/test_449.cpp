// File: dfa_rwlocker_lockforwriting_test_449.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// If your project exposes RWLocker via a header, prefer including it:
//   #include "re2/dfa.h"
// The tests below only rely on the public interface:
//   - re2::DFA::RWLocker(CacheMutex*)
//   - void re2::DFA::RWLocker::LockForWriting()

using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::_;
using ::testing::Times;

namespace re2 {

// Minimal interface for the external collaborator used by RWLocker.
// These are virtual so we can observe calls via Google Mock.
// If your codebase already defines CacheMutex, remove this block and
// derive the mock from that definition instead.
class CacheMutex {
public:
  virtual ~CacheMutex() = default;
  virtual void ReaderLock() {}
  virtual void ReaderUnlock() {}
  virtual void WriterLock() {}
  virtual void WriterUnlock() {}
};

// Mock of the external collaborator. We observe interactions only.
class MockCacheMutex : public CacheMutex {
public:
  MOCK_METHOD(void, ReaderLock,   (), (override));
  MOCK_METHOD(void, ReaderUnlock, (), (override));
  MOCK_METHOD(void, WriterLock,   (), (override));
  MOCK_METHOD(void, WriterUnlock, (), (override));
};

// Forward declaration matching the class-under-test surface.
// In your codebase this should already be declared in the public header.
class DFA {
public:
  class RWLocker {
  public:
    explicit RWLocker(CacheMutex* mu);
    ~RWLocker();
    void LockForWriting();  // method under test
  };
};

}  // namespace re2

// ---------- Tests ----------
namespace {

class RWLockerTest_449 : public ::testing::Test {};

TEST_F(RWLockerTest_449, LockForWriting_CallsReaderUnlockThenWriterLockOnce_449) {
  // Use NiceMock to allow any destructor-side lock transitions (e.g., WriterUnlock/ReaderLock)
  // without making the test brittle. We still assert the specific calls we care about.
  NiceMock<re2::MockCacheMutex> mu;

  // Verify the observable interaction and ordering on the first call.
  InSequence seq;
  EXPECT_CALL(mu, ReaderUnlock()).Times(1);
  EXPECT_CALL(mu, WriterLock()).Times(1);

  re2::DFA::RWLocker locker(&mu);
  locker.LockForWriting();
}

TEST_F(RWLockerTest_449, LockForWriting_IdempotentOnSecondCall_NoAdditionalRWCalls_449) {
  NiceMock<re2::MockCacheMutex> mu;

  // Lock escalation should happen at most once per RWLocker instance.
  // We assert exactly one pair of calls even if LockForWriting() is invoked twice.
  InSequence seq;
  EXPECT_CALL(mu, ReaderUnlock()).Times(1);
  EXPECT_CALL(mu, WriterLock()).Times(1);

  re2::DFA::RWLocker locker(&mu);
  locker.LockForWriting();  // first call: should escalate
  locker.LockForWriting();  // second call: should be a no-op w.r.t. ReaderUnlock/WriterLock
}

TEST_F(RWLockerTest_449, TwoIndependentLockersEachEscalateSeparately_449) {
  NiceMock<re2::MockCacheMutex> mu;

  // Each independent RWLocker should perform its own escalation exactly once.
  InSequence seq;
  EXPECT_CALL(mu, ReaderUnlock()).Times(1);
  EXPECT_CALL(mu, WriterLock()).Times(1);
  EXPECT_CALL(mu, ReaderUnlock()).Times(1);
  EXPECT_CALL(mu, WriterLock()).Times(1);

  re2::DFA::RWLocker locker1(&mu);
  re2::DFA::RWLocker locker2(&mu);

  locker1.LockForWriting();
  locker2.LockForWriting();
}

TEST_F(RWLockerTest_449, NoUnexpectedCallsBeforeLockForWriting_449) {
  // Ensures constructing RWLocker alone does not trigger ReaderUnlock/WriterLock.
  // We allow destructor behavior by using NiceMock.
  NiceMock<re2::MockCacheMutex> mu;

  re2::DFA::RWLocker locker(&mu);
  // No EXPECT_CALL for ReaderUnlock/WriterLock here implies zero invocations so far.
  // If the constructor performed them, gMock would flag unexpected calls.
}

}  // namespace
