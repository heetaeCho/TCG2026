// File: db/c_writebatch_delete_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/write_batch.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

// We include the C shim implementation so we can call the exact wrapper under test
// and access the concrete leveldb_writebatch_t defined there.
#include "db/c.cc"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::Property;
using ::testing::StrictMock;

namespace {

// Minimal mock of WriteBatch::Handler to observe calls made via Iterate.
class MockHandler : public leveldb::WriteBatch::Handler {
public:
  MOCK_METHOD(void, Put, (const leveldb::Slice& key, const leveldb::Slice& value), (override));
  MOCK_METHOD(void, Delete, (const leveldb::Slice& key), (override));
};

// A simple fixture with a fresh writebatch wrapper each test.
class WriteBatchDeleteTest_248 : public ::testing::Test {
protected:
  leveldb_writebatch_t wb_;  // Contains `leveldb::WriteBatch rep;`
};

}  // namespace

// [Normal] Deleting a single key is surfaced as one Delete() during Iterate.
TEST_F(WriteBatchDeleteTest_248, Delete_SingleKey_248) {
  StrictMock<MockHandler> handler;
  const char* k = "alpha";
  const size_t klen = 5;

  EXPECT_CALL(handler, Put(_, _)).Times(0);
  EXPECT_CALL(handler, Delete(Property(&leveldb::Slice::ToString, Eq(std::string("alpha"))))).Times(1);

  leveldb_writebatch_delete(&wb_, k, klen);
  leveldb::Status s = wb_.rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// [Boundary] Empty key (klen == 0) must be passed through exactly as empty Slice.
TEST_F(WriteBatchDeleteTest_248, Delete_EmptyKey_248) {
  StrictMock<MockHandler> handler;

  // Match a Slice whose size() == 0.
  auto EmptySlice = Property(&leveldb::Slice::size, Eq(static_cast<size_t>(0)));

  EXPECT_CALL(handler, Put(_, _)).Times(0);
  EXPECT_CALL(handler, Delete(EmptySlice)).Times(1);

  leveldb_writebatch_delete(&wb_, "ignored", 0);
  leveldb::Status s = wb_.rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// [Boundary] Key with embedded '\0' bytes: length must be honored literally.
TEST_F(WriteBatchDeleteTest_248, Delete_KeyWithEmbeddedNull_248) {
  StrictMock<MockHandler> handler;

  const char raw[] = {'a','\0','b','\0','c'};  // length 5, not a C-string
  const size_t klen = sizeof(raw);

  // We check both size() and that the bytes up to klen form the expected std::string.
  EXPECT_CALL(handler, Put(_, _)).Times(0);
  EXPECT_CALL(handler, Delete(AllOf(
      Property(&leveldb::Slice::size, Eq(klen)),
      Property(&leveldb::Slice::ToString, Eq(std::string(raw, klen)))
  ))).Times(1);

  leveldb_writebatch_delete(&wb_, raw, klen);
  leveldb::Status s = wb_.rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// [Normal + Order] Multiple deletes appear in Iterate in the same order.
TEST_F(WriteBatchDeleteTest_248, Delete_MultipleKeys_OrderPreserved_248) {
  StrictMock<MockHandler> handler;
  InSequence seq;  // enforce call order

  EXPECT_CALL(handler, Put(_, _)).Times(0);
  EXPECT_CALL(handler, Delete(Property(&leveldb::Slice::ToString, Eq(std::string("k1")))));
  EXPECT_CALL(handler, Delete(Property(&leveldb::Slice::ToString, Eq(std::string("k2")))));
  EXPECT_CALL(handler, Delete(Property(&leveldb::Slice::ToString, Eq(std::string("k3")))));

  leveldb_writebatch_delete(&wb_, "k1", 2);
  leveldb_writebatch_delete(&wb_, "k2", 2);
  leveldb_writebatch_delete(&wb_, "k3", 2);

  leveldb::Status s = wb_.rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}

// [Boundary] Provided length is respected even if the input pointer points to a longer C-string.
TEST_F(WriteBatchDeleteTest_248, Delete_UsesProvidedLengthNotCStr_248) {
  StrictMock<MockHandler> handler;
  const char* k = "abcdef"; // strlen = 6, but we pass klen = 3 -> expect "abc"

  EXPECT_CALL(handler, Put(_, _)).Times(0);
  EXPECT_CALL(handler, Delete(AllOf(
      Property(&leveldb::Slice::size, Eq(static_cast<size_t>(3))),
      Property(&leveldb::Slice::ToString, Eq(std::string("abc")))
  ))).Times(1);

  leveldb_writebatch_delete(&wb_, k, 3);
  leveldb::Status s = wb_.rep.Iterate(&handler);
  EXPECT_TRUE(s.ok());
}
