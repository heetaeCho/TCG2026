// iterator_wrapper_prev_test_383.cc
#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::_;
using ::testing::Return;

namespace leveldb {

// A mock for the external collaborator: leveldb::Iterator.
// We only verify observable interactions (that IteratorWrapper delegates to it).
class MockIterator : public Iterator {
 public:
  // Core navigation methods
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice& target), (override));

  // Accessors that Update() may call internally; we allow them without asserting logic.
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(Slice, key, (), (const, override));
  MOCK_METHOD(Slice, value, (), (const, override));
  MOCK_METHOD(Status, status, (), (const, override));

  ~MockIterator() override = default;
};

class IteratorWrapperTest_383 : public ::testing::Test {
 protected:
  // Helper to set safe defaults so Update() can query without failing test expectations.
  void SetSafeDefaults(NiceMock<MockIterator>& it) {
    ON_CALL(it, Valid()).WillByDefault(Return(false));
    // key() / value() / status() may be queried by Update(); provide benign defaults.
    // Slice and Status are real types in LevelDB; default-constructed returns are fine.
    // (We don't assert their values here—only that Prev() is delegated.)
    ON_CALL(it, key()).WillByDefault(testing::Return(Slice()));
    ON_CALL(it, value()).WillByDefault(testing::Return(Slice()));
    ON_CALL(it, status()).WillByDefault(testing::Return(Status()));
  }
};

// Normal operation: Prev delegates to underlying iterator.
// We also permit any internal Update() queries (e.g., Valid()/key()/value()).
TEST_F(IteratorWrapperTest_383, PrevDelegatesToUnderlying_383) {
  NiceMock<MockIterator> mock;
  SetSafeDefaults(mock);

  EXPECT_CALL(mock, Prev()).Times(1);

  IteratorWrapper w;
  w.Set(&mock);
  w.Prev();  // Should call mock.Prev() and then Update() safely.
}

// Boundary/exceptional: calling Prev() with no iterator should assert/abort.
// Uses a death test to verify the contract "assert(iter_)"
TEST_F(IteratorWrapperTest_383, PrevWithoutIteratorAborts_383) {
#if GTEST_HAS_DEATH_TEST
  IteratorWrapper w;  // not set -> iter_ is null
  ASSERT_DEATH({ w.Prev(); }, "");  // any assertion/abort message
#else
  GTEST_SKIP() << "Death tests are not supported on this platform.";
#endif
}

// Boundary: Wrapper after Set(nullptr) then Set(valid) should work and delegate Prev().
TEST_F(IteratorWrapperTest_383, PrevAfterResetAndSetDelegates_383) {
  NiceMock<MockIterator> mock;
  SetSafeDefaults(mock);

  IteratorWrapper w;
  // First, explicitly set to nullptr (if supported by interface) to simulate reset path.
  // Even if Set(nullptr) is a no-op, the next Set(&mock) must succeed.
  w.Set(nullptr);
  w.Set(&mock);

  EXPECT_CALL(mock, Prev()).Times(1);
  w.Prev();
}

// Sanity: iter() reflects the pointer provided via Set(), and Prev() still delegates.
TEST_F(IteratorWrapperTest_383, IterGetterAndPrevDelegation_383) {
  NiceMock<MockIterator> mock;
  SetSafeDefaults(mock);

  IteratorWrapper w;
  w.Set(&mock);
  ASSERT_EQ(w.iter(), &mock);  // Observable via public API

  EXPECT_CALL(mock, Prev()).Times(1);
  w.Prev();
}

}  // namespace leveldb
