// iterator_wrapper_seek_to_last_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"

// Forward declarations for types referenced by Iterator's interface.
// We don't construct or depend on their internals in these tests.
namespace leveldb {
class Slice;
class Status;
}  // namespace leveldb

using ::testing::AtLeast;
using ::testing::Return;

namespace leveldb {

// Minimal mock of the external collaborator (Iterator).
// We override only what is observably used by IteratorWrapper::SeekToLast + Update path.
class MockIterator : public Iterator {
 public:
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(bool, Valid, (), (const, override));

  // Provide virtual destructor override to satisfy polymorphic deletion.
  ~MockIterator() override = default;
};

// Test fixture (no shared state required for now).
class IteratorWrapperTest_386 : public ::testing::Test {
 protected:
  IteratorWrapper wrapper_;
};

TEST_F(IteratorWrapperTest_386, SeekToLast_ForwardsCallToUnderlying_386) {
  // Arrange: a mock iterator that reports "not valid" so Update() (internal)
  // doesn't need to consult key()/value(). We only verify observable interactions.
  MockIterator iter;
  EXPECT_CALL(iter, SeekToLast()).Times(1);
  EXPECT_CALL(iter, Valid())
      .Times(AtLeast(1))
      .WillRepeatedly(Return(false));

  wrapper_.Set(&iter);

  // Act: exercise the method under test.
  wrapper_.SeekToLast();

  // Assert: additionally, Valid() should reflect the underlying observable state.
  // This is an observable behavior via the public interface.
  EXPECT_FALSE(wrapper_.Valid());
}

TEST_F(IteratorWrapperTest_386, SeekToLast_WithoutIterator_TriggersContract_386) {
  // Boundary/exceptional case: calling SeekToLast when no iterator is set.
  // The provided implementation asserts(iter_). Use a death test to capture that.
  // Note: This check is meaningful in debug builds where assert is active.
#if !defined(NDEBUG)
  EXPECT_DEATH(wrapper_.SeekToLast(), ".*");
#else
  GTEST_SKIP() << "Death test skipped in release builds where assert() is disabled.";
#endif
}

TEST_F(IteratorWrapperTest_386, SeekToLast_AfterSetThenResetNull_ContractHolds_386) {
  // Boundary: If the environment allows resetting to nullptr (via Set(nullptr)),
  // the same assert contract should apply on subsequent SeekToLast calls.
  // If Set(nullptr) is not permitted by the interface, this test still validates
  // that invoking SeekToLast with a null underlying iterator is guarded.
#if !defined(NDEBUG)
  MockIterator iter;
  // Expect normal call once to ensure Set works before nulling.
  EXPECT_CALL(iter, SeekToLast()).Times(1);
  EXPECT_CALL(iter, Valid()).Times(AtLeast(1)).WillRepeatedly(Return(false));

  wrapper_.Set(&iter);
  wrapper_.SeekToLast();

  // Now reset to nullptr and verify the contract via death test.
  wrapper_.Set(nullptr);
  EXPECT_DEATH(wrapper_.SeekToLast(), ".*");
#else
  GTEST_SKIP() << "Death test skipped in release builds where assert() is disabled.";
#endif
}

}  // namespace leveldb
