// iterator_wrapper_seek_test_384.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"
#include "leveldb/slice.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

// Minimal mock for the external collaborator (Iterator).
class MockIterator : public Iterator {
 public:
  // Only mock methods that are observably interacted with for Seek/Update.
  MOCK_METHOD(void, Seek, (const Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));

  // Iterator state/read-outs used by IteratorWrapper::Update().
  MOCK_METHOD(const bool, Valid, (), (override));
  MOCK_METHOD(const Slice, key, (), (override));
  MOCK_METHOD(const Slice, value, (), (override));

  // Keep dtor virtual as in base.
  ~MockIterator() override = default;
};

// ---------- Test Fixture ----------
class IteratorWrapperTest_384 : public ::testing::Test {
 protected:
  StrictMock<MockIterator> mock_;
  IteratorWrapper wrapper_;
  void SetUp() override {
    // Ensure wrapper has a valid collaborator via the public interface.
    wrapper_.Set(&mock_);
  }
};

// Normal operation: Seek forwards target to underlying Iterator and updates state.
TEST_F(IteratorWrapperTest_384, Seek_ForwardsAndUpdatesState_384) {
  const std::string k = "abc";
  const std::string v = "val";

  // Provide stable Slices that reference persistent storage.
  const Slice key_slice(k);
  const Slice val_slice(v);

  // Expect forwarding call.
  EXPECT_CALL(mock_, Seek(::testing::Truly([&](const Slice& s) {
    return s.size() == k.size() && std::string(s.data(), s.size()) == k;
  }))).Times(1);

  // Update() behavior (observable through public accessors):
  // Valid() queried; if true, key()/value() may be consulted.
  EXPECT_CALL(mock_, Valid()).Times(AtLeast(1)).WillRepeatedly(Return(true));
  EXPECT_CALL(mock_, key()).Times(AtLeast(1)).WillRepeatedly(Return(key_slice));
  EXPECT_CALL(mock_, value()).Times(AtLeast(1)).WillRepeatedly(Return(val_slice));

  wrapper_.Seek(Slice(k));

  // Verify externally visible state matches collaborator after Seek.
  EXPECT_TRUE(wrapper_.Valid());
  EXPECT_EQ(k, wrapper_.key().ToString());
  EXPECT_EQ(v, wrapper_.value().ToString());
}

// Boundary: Seek with empty Slice should still be forwarded and state updated.
TEST_F(IteratorWrapperTest_384, Seek_WithEmptySlice_UpdatesState_384) {
  const std::string v = "v";
  const Slice empty_key;     // default-constructed -> empty
  const Slice value_slice(v);

  EXPECT_CALL(mock_, Seek(::testing::Truly([&](const Slice& s) {
    return s.size() == 0; // forwarded exactly as empty
  }))).Times(1);

  EXPECT_CALL(mock_, Valid()).Times(AtLeast(1)).WillRepeatedly(Return(true));
  // If valid, Update() may consult key()/value().
  EXPECT_CALL(mock_, key()).Times(AtLeast(1)).WillRepeatedly(Return(empty_key));
  EXPECT_CALL(mock_, value()).Times(AtLeast(1)).WillRepeatedly(Return(value_slice));

  wrapper_.Seek(Slice());  // empty

  EXPECT_TRUE(wrapper_.Valid());
  EXPECT_EQ("", wrapper_.key().ToString());
  EXPECT_EQ(v, wrapper_.value().ToString());
}

// Exceptional/edge (observable): If underlying iterator reports invalid after Seek,
// wrapper should reflect invalid state. We avoid calling key()/value() when invalid.
TEST_F(IteratorWrapperTest_384, Seek_WhenUnderlyingInvalid_MarksWrapperInvalid_384) {
  const std::string k = "zzz";

  EXPECT_CALL(mock_, Seek(::testing::Truly([&](const Slice& s) {
    return s.size() == k.size() && std::string(s.data(), s.size()) == k;
  }))).Times(1);

  // Update() sees invalid; it should not need key()/value() (observable intent).
  EXPECT_CALL(mock_, Valid()).Times(AtLeast(1)).WillRepeatedly(Return(false));
  EXPECT_CALL(mock_, key()).Times(0);
  EXPECT_CALL(mock_, value()).Times(0);

  wrapper_.Seek(Slice(k));

  EXPECT_FALSE(wrapper_.Valid());
}

// Defensive check from the interface: Seek asserts when no iterator is set.
#if GTEST_HAS_DEATH_TEST
TEST(IteratorWrapperDeathTest_384, Seek_WithoutIterator_TriggersAssert_384) {
  IteratorWrapper wrapper_no_iter;  // default-constructed; no Set() called.

  // Death test: calling Seek should hit assert(iter_).
  EXPECT_DEATH(
      {
        const Slice any("x");
        wrapper_no_iter.Seek(any);
      },
      ".*");  // Match any assert message.
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace leveldb
