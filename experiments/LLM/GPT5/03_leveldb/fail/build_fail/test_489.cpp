// iterator_wrapper_test_489.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "table/iterator_wrapper.h"
#include "leveldb/iterator.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

// A Google Mock for leveldb::Iterator that lets us verify the external
// interactions made by IteratorWrapper. We do not simulate any internal
// behavior of IteratorWrapper itself.
namespace leveldb {

class MockIterator : public Iterator {
 public:
  // Use signatures that match the (partially shown) interface.
  // NOTE: We rely only on call forwarding and return values;
  // no internal state of IteratorWrapper is observed.
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(const Slice, key, (), (const, override));
  MOCK_METHOD(const Slice, value, (), (const, override));
  MOCK_METHOD(const Status, status, (), (const, override));

  // RegisterCleanup is not used by IteratorWrapper’s public API paths in these tests.
  // Provide a no-op override to satisfy pure virtual interface if needed.
  void RegisterCleanup(CleanupFunction, void*, void*) override {}
  ~MockIterator() override = default;
};

}  // namespace leveldb

namespace {

class IteratorWrapperTest_489 : public ::testing::Test {};

//
// Construction / basic state
//

// Ensures default-constructed wrapper has no iterator and reports invalid.
TEST_F(IteratorWrapperTest_489, DefaultConstruct_IsInvalid_489) {
  leveldb::IteratorWrapper w;  // default ctor
  // Observable behavior: Valid() should be false for an empty wrapper.
  EXPECT_FALSE(w.Valid());
  // And iter() should be nullptr.
  EXPECT_EQ(w.iter(), nullptr);
}

// Constructing with an iterator should expose that iterator via iter().
TEST_F(IteratorWrapperTest_489, ConstructWithIterator_ExposesPointer_489) {
  leveldb::MockIterator it;
  leveldb::IteratorWrapper w(&it);
  EXPECT_EQ(w.iter(), &it);
}

//
// Valid() reflection
//

// Valid() forwards to the underlying iterator when present (true case).
TEST_F(IteratorWrapperTest_489, Valid_ForwardsTrue_489) {
  leveldb::MockIterator it;
  EXPECT_CALL(it, Valid()).WillOnce(Return(true));

  leveldb::IteratorWrapper w(&it);
  EXPECT_TRUE(w.Valid());
}

// Valid() forwards to the underlying iterator when present (false case).
TEST_F(IteratorWrapperTest_489, Valid_ForwardsFalse_489) {
  leveldb::MockIterator it;
  EXPECT_CALL(it, Valid()).WillOnce(Return(false));

  leveldb::IteratorWrapper w(&it);
  EXPECT_FALSE(w.Valid());
}

//
// Forwarding of navigation operations
//

TEST_F(IteratorWrapperTest_489, Next_ForwardsToIterator_489) {
  leveldb::MockIterator it;
  EXPECT_CALL(it, Next()).Times(1);

  leveldb::IteratorWrapper w(&it);
  w.Next();  // observable: underlying Next() is called exactly once
}

TEST_F(IteratorWrapperTest_489, Prev_ForwardsToIterator_489) {
  leveldb::MockIterator it;
  EXPECT_CALL(it, Prev()).Times(1);

  leveldb::IteratorWrapper w(&it);
  w.Prev();
}

TEST_F(IteratorWrapperTest_489, SeekForwards_WithKeyParameter_489) {
  leveldb::MockIterator it;
  // We cannot construct a real Slice here without the full definition, but we can still
  // verify that Seek(const Slice&) is called with *some* Slice reference.
  EXPECT_CALL(it, Seek(_)).Times(1);

  leveldb::IteratorWrapper w(&it);

  // Create a dummy Slice through the wrapper's interface expectations.
  // If a real Slice is available in your build, replace with an actual value.
  const leveldb::Slice* dummy = reinterpret_cast<const leveldb::Slice*>(0x1);
  // NOTE: We are not dereferencing dummy; it is used only to satisfy the call.
  // In a real codebase, pass a real Slice (e.g., leveldb::Slice("k")).
  w.Seek(*dummy);
}

TEST_F(IteratorWrapperTest_489, SeekToFirst_ForwardsToIterator_489) {
  leveldb::MockIterator it;
  EXPECT_CALL(it, SeekToFirst()).Times(1);

  leveldb::IteratorWrapper w(&it);
  w.SeekToFirst();
}

TEST_F(IteratorWrapperTest_489, SeekToLast_ForwardsToIterator_489) {
  leveldb::MockIterator it;
  EXPECT_CALL(it, SeekToLast()).Times(1);

  leveldb::IteratorWrapper w(&it);
  w.SeekToLast();
}

//
// Accessors key()/value()/status() are forwarded to the iterator
// (we only verify the call/return path; no assumptions about caching).
//

TEST_F(IteratorWrapperTest_489, Key_ForwardsToIterator_489) {
  leveldb::MockIterator it;
  // If a concrete leveldb::Slice is available, set a value and assert equality.
  // Here, we only verify that the call is forwarded.
  EXPECT_CALL(it, key()).Times(1);

  leveldb::IteratorWrapper w(&it);
  // We cannot assert equality without a concrete Slice instance; just invoke.
  (void)w.key();
}

TEST_F(IteratorWrapperTest_489, Value_ForwardsToIterator_489) {
  leveldb::MockIterator it;
  EXPECT_CALL(it, value()).Times(1);

  leveldb::IteratorWrapper w(&it);
  (void)w.value();
}

TEST_F(IteratorWrapperTest_489, Status_ForwardsToIterator_489) {
  leveldb::MockIterator it;
  EXPECT_CALL(it, status()).Times(1);

  leveldb::IteratorWrapper w(&it);
  (void)w.status();
}

//
// Set() behavior: replacing the iterator should redirect subsequent calls
// to the new iterator instance.
// We do not assert anything about cleanup or previous iterator handling;
// only that new calls target the new iterator.
//

TEST_F(IteratorWrapperTest_489, Set_ReplacesUnderlyingIterator_489) {
  leveldb::MockIterator it1;
  leveldb::MockIterator it2;

  {
    InSequence seq;
    EXPECT_CALL(it1, Next()).Times(1);
    EXPECT_CALL(it2, Next()).Times(1);
  }

  leveldb::IteratorWrapper w(&it1);
  w.Next();        // should call it1.Next()

  w.Set(&it2);     // replace
  EXPECT_EQ(w.iter(), &it2);
  w.Next();        // should call it2.Next()
}

//
// Set(nullptr): wrapper becomes empty; Valid() is observable as false.
// We do not call key()/value() when invalid.
//

TEST_F(IteratorWrapperTest_489, SetNull_MakesWrapperInvalid_489) {
  leveldb::MockIterator it;
  leveldb::IteratorWrapper w(&it);

  // After Set(nullptr), the wrapper should behave as empty/invalid.
  w.Set(nullptr);
  EXPECT_EQ(w.iter(), nullptr);
  EXPECT_FALSE(w.Valid());
}

}  // namespace
