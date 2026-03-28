// iterator_wrapper_next_test_382.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "table/iterator_wrapper.h"   // Class under test
#include "leveldb/iterator.h"         // Iterator interface

using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Expectation;
using ::testing::InSequence;
using ::testing::_;
using ::testing::AtLeast;

namespace leveldb {

// A GMock for leveldb::Iterator.
// NOTE: We keep signatures minimal and permissive so we don't assume internal logic.
// We also use NiceMock to tolerate extra calls made indirectly by IteratorWrapper::Update().
class MockIterator : public Iterator {
public:
  // The header snippet shows these as virtuals; we mirror them for mocking.
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice&), (override));

  // For potential calls from IteratorWrapper::Update(); allow them but don't assert on them.
  MOCK_METHOD(bool, Valid, (), (override));
  MOCK_METHOD(const Slice, key, (), (override));   // returning by value for simplicity
  MOCK_METHOD(const Slice, value, (), (override)); // returning by value for simplicity
  MOCK_METHOD(Status, status, (), (override));

  ~MockIterator() override = default;
};

// Test fixture (keeps declarations tidy; no shared state required).
class IteratorWrapperTest_382 : public ::testing::Test { };


// [Normal] Next delegates to the underlying iterator's Next()
TEST_F(IteratorWrapperTest_382, Next_DelegatesToUnderlying_382) {
  NiceMock<MockIterator> mock_it;  // NiceMock to allow any Update()-related calls.
  IteratorWrapper wrapper;
  wrapper.Set(&mock_it);

  // We only verify that Iterator::Next() is called at least once.
  EXPECT_CALL(mock_it, Next()).Times(1);

  // Act
  wrapper.Next();
}

// [Interaction correctness] After Set() with a new iterator, Next() uses the most recently set iterator
TEST_F(IteratorWrapperTest_382, Next_UsesMostRecentlySetIterator_382) {
  NiceMock<MockIterator> first;
  NiceMock<MockIterator> second;

  IteratorWrapper wrapper;
  wrapper.Set(&first);
  wrapper.Set(&second);

  // Only 'second' should receive Next().
  EXPECT_CALL(first, Next()).Times(0);
  EXPECT_CALL(second, Next()).Times(1);

  // Act
  wrapper.Next();
}

// [Boundary / Error] Calling Next() with no iterator set should trigger the assert
// Use death test where supported (debug builds, no NDEBUG).
#if GTEST_HAS_DEATH_TEST
TEST_F(IteratorWrapperTest_382, Next_DeathWhenNoIteratorSet_382) {
  IteratorWrapper wrapper; // default-constructed; iter_ is null per interface comments/snippet
  // Expect an assertion failure due to assert(iter_) in Next().
  EXPECT_DEATH({ wrapper.Next(); }, "");
}
#endif

} // namespace leveldb
