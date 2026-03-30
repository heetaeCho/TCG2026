// File: util/mutexlock_test.cc

#include <type_traits>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

// Provide empty definitions for the thread-safety annotation macros if not already defined.
#ifndef EXCLUSIVE_LOCK_FUNCTION
#define EXCLUSIVE_LOCK_FUNCTION(...)
#endif
#ifndef UNLOCK_FUNCTION
#define UNLOCK_FUNCTION(...)
#endif
#ifndef ASSERT_EXCLUSIVE_LOCK
#define ASSERT_EXCLUSIVE_LOCK(...)
#endif

// ---- Test double for the external collaborator (allowed by Constraints #3) ----
// We declare a minimal port::Mutex interface that matches what MutexLock uses.
// We make methods virtual so gMock can observe calls.
namespace leveldb {
namespace port {

class Mutex {
 public:
  virtual ~Mutex() = default;
  virtual void Lock() EXCLUSIVE_LOCK_FUNCTION() {}
  virtual void Unlock() UNLOCK_FUNCTION() {}
  virtual void AssertHeld() ASSERT_EXCLUSIVE_LOCK() {}
};

}  // namespace port
}  // namespace leveldb

// Now include the class under test. It references leveldb::port::Mutex.
#include "util/mutexlock.h"

namespace leveldb {
namespace {

using ::testing::Exactly;
using ::testing::Expectation;
using ::testing::InSequence;

class MockMutex : public port::Mutex {
 public:
  MOCK_METHOD(void, Lock, (), (override));
  MOCK_METHOD(void, Unlock, (), (override));
  MOCK_METHOD(void, AssertHeld, (), (override));
};

// Test fixture (empty; here for consistency & future extension).
class MutexLockTest_296 : public ::testing::Test {};

// Verifies that ~MutexLock calls Unlock() exactly once on the provided mutex.
TEST_F(MutexLockTest_296, DestructorCallsUnlockOnce_296) {
  MockMutex mu;

  // Expect exactly one Unlock call when the guard is destroyed.
  EXPECT_CALL(mu, Unlock()).Times(Exactly(1));

  {
    // Construct the guard with the mocked collaborator.
    // We assert only on the destructor behavior (observable via mock).
    MutexLock guard(&mu);
    // No further expectations here: constructor behavior is out of scope for this test.
  }  // guard goes out of scope here -> destructor should invoke mu.Unlock()
}

// Verifies the type is not copyable/assignable (observable at compile time via the interface).
TEST_F(MutexLockTest_296, NotCopyableOrAssignable_296) {
  static_assert(!std::is_copy_constructible<MutexLock>::value,
                "MutexLock must not be copy-constructible");
  static_assert(!std::is_copy_assignable<MutexLock>::value,
                "MutexLock must not be copy-assignable");
  // (Optionally) also check move semantics if desired; with the given interface, moves should be disabled.
  static_assert(!std::is_move_constructible<MutexLock>::value,
                "MutexLock must not be move-constructible");
  static_assert(!std::is_move_assignable<MutexLock>::value,
                "MutexLock must not be move-assignable");
}

// Verifies that explicitly invoking the destructor triggers exactly one Unlock()
// (timing-focused variant to ensure the call happens upon destruction).
TEST_F(MutexLockTest_296, ExplicitDestructorInvokesUnlock_296) {
  MockMutex mu;

  {
    InSequence seq;  // enforce ordering within this scope if extended later
    EXPECT_CALL(mu, Unlock()).Times(Exactly(1));
  }

  // Manually control the destructor timing.
  // Placement in its own scope to avoid double-destruction risks.
  {
    // Allocate on stack, then call destructor explicitly.
    // NOLINTNEXTLINE(clang-analyzer-optin.cplusplus.UninitializedObject)
    MutexLock* guard_ptr = new MutexLock(&mu);
    guard_ptr->~MutexLock();  // should call mu.Unlock() exactly once
    // Prevent a second destructor call by avoiding `delete` (the object is already destroyed).
    // We intentionally leak here for test isolation; if you prefer, allocate with `std::aligned_storage`
    // and avoid operator new. The important part is: destructor timing is under test.
  }
}

}  // namespace
}  // namespace leveldb
