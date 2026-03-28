// iterator_wrapper_status_test_381.cc
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/status.h"
#include "leveldb/slice.h"
#include "leveldb/iterator.h"
#include "table/iterator_wrapper.h"

using ::testing::NiceMock;
using ::testing::Return;

namespace leveldb {
namespace {

// A strict interface-faithful mock of leveldb::Iterator.
// We only care about status(), but we mock the full interface so the type is concrete.
class MockIterator : public Iterator {
 public:
  // Destructor
  ~MockIterator() override = default;

  // Core iterator interface
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(Slice, key, (), (const, override));
  MOCK_METHOD(Slice, value, (), (const, override));
  MOCK_METHOD(Status, status, (), (const, override));
};

//
// Tests
//

// 1) Calling status() without setting an underlying iterator should fail via assert.
//    This is an observable crash (death test).
TEST(IteratorWrapperStatusTest_381, StatusDiesWhenNoIterator_381) {
  IteratorWrapper w;  // default-constructed; no underlying iterator set
#ifdef NDEBUG
  // In release builds, assert may be compiled out. We only check death when asserts are enabled.
  GTEST_SKIP() << "Assertions disabled (NDEBUG defined); skipping assert death check.";
#else
  ASSERT_DEATH({ (void)w.status(); }, ".*");
#endif
}

// 2) status() forwards to the underlying iterator and returns its Status (non-OK case).
TEST(IteratorWrapperStatusTest_381, ForwardsUnderlyingStatus_NotOK_381) {
  NiceMock<MockIterator> it;
  EXPECT_CALL(it, status()).WillOnce(Return(Status::NotFound("missing")));

  IteratorWrapper w;
  w.Set(&it);

  Status s = w.status();
  EXPECT_FALSE(s.ok());
}

// 3) status() forwards to the underlying iterator and returns its Status (OK case).
TEST(IteratorWrapperStatusTest_381, ForwardsUnderlyingStatus_OK_381) {
  NiceMock<MockIterator> it;
  EXPECT_CALL(it, status()).WillOnce(Return(Status::OK()));

  IteratorWrapper w;
  w.Set(&it);

  Status s = w.status();
  EXPECT_TRUE(s.ok());
}

// 4) After swapping the underlying iterator via Set(), status() reflects the new iterator.
TEST(IteratorWrapperStatusTest_381, StatusReflectsIteratorAfterSetSwap_381) {
  NiceMock<MockIterator> it1;
  NiceMock<MockIterator> it2;

  EXPECT_CALL(it1, status()).WillOnce(Return(Status::NotFound("first")));
  EXPECT_CALL(it2, status()).WillOnce(Return(Status::OK()));

  IteratorWrapper w;
  w.Set(&it1);
  Status s1 = w.status();
  EXPECT_FALSE(s1.ok());

  w.Set(&it2);
  Status s2 = w.status();
  EXPECT_TRUE(s2.ok());
}

// 5) If the client explicitly clears the iterator by Set(nullptr), status() should assert.
TEST(IteratorWrapperStatusTest_381, StatusDiesAfterClearingIterator_381) {
  IteratorWrapper w;

  NiceMock<MockIterator> it;
  EXPECT_CALL(it, status()).WillOnce(Return(Status::OK()));

  w.Set(&it);
  EXPECT_TRUE(w.status().ok());  // sanity check with valid iterator

#ifdef NDEBUG
  GTEST_SKIP() << "Assertions disabled (NDEBUG defined); skipping assert death check.";
#else
  w.Set(nullptr);
  ASSERT_DEATH({ (void)w.status(); }, ".*");
#endif
}

}  // namespace
}  // namespace leveldb
