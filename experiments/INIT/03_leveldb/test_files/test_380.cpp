// iterator_wrapper_value_test_380.cc
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

using ::testing::Return;
using ::testing::ByMove;
using ::testing::Times;

namespace leveldb {

// Minimal mock for Iterator focusing only on methods touched
// indirectly by IteratorWrapper during Set()/Update() and value().
class MockIterator : public Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice&), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(Slice, key, (), (override));
  MOCK_METHOD(Slice, value, (), (override));
  MOCK_METHOD(Status, status, (), (override));
};

class IteratorWrapperTest_380 : public ::testing::Test {};

TEST_F(IteratorWrapperTest_380, ValueForwardsAndReturnsUnderlyingSlice_380) {
  MockIterator it;
  IteratorWrapper w;

  // Arrange: when the wrapper is set, many impls Update() by reading Valid() and key().
  // We provide those expectations non-invasively, only to satisfy observable flow.
  Slice key_slice("k");          // any key (not asserted here, just to satisfy Update)
  Slice expected_value("value"); // the value we expect to be returned

  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(key_slice));

  // After being valid, Wrapper::value() should forward to the underlying iterator's value().
  EXPECT_CALL(it, value()).Times(1).WillOnce(Return(expected_value));

  // Act
  w.Set(&it);
  Slice got = w.value();

  // Assert: observable return equality
  // (Compare using Slice's ToString(), which is part of the public Slice surface.)
  EXPECT_EQ(got.ToString(), expected_value.ToString());
}

TEST_F(IteratorWrapperTest_380, ValueCallsUnderlyingExactlyOnceWhenValid_380) {
  MockIterator it;
  IteratorWrapper w;

  Slice key_slice("k");
  Slice val_slice("v");

  EXPECT_CALL(it, Valid()).WillOnce(Return(true));
  EXPECT_CALL(it, key()).WillOnce(Return(key_slice));
  EXPECT_CALL(it, value()).Times(1).WillOnce(Return(val_slice));

  w.Set(&it);
  (void)w.value();  // act

  // No explicit assert needed beyond Times(1); if called more/less, the test fails.
}

TEST_F(IteratorWrapperTest_380, ValueAssertsWhenInvalid_380) {
#ifdef NDEBUG
  GTEST_SKIP() << "Assertions are disabled in release builds (NDEBUG).";
#else
  // Default-constructed wrapper has no iterator set -> not valid.
  IteratorWrapper w;
  EXPECT_DEATH({ (void)w.value(); }, ".*");
#endif
}

}  // namespace leveldb
