// File: write_batch_append_test_207.cc
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "leveldb/status.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"

using ::testing::InSequence;
using ::testing::StrictMock;
using ::testing::_;
using ::testing::Times;

namespace leveldb {

namespace {

struct MockHandler : public WriteBatch::Handler {
  MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));
  MOCK_METHOD(void, Delete, (const Slice& key), (override));
};

class WriteBatchAppendTest_207 : public ::testing::Test {
 protected:
  static Slice S(const char* s) { return Slice(s); }
};

}  // namespace

// Empty + Empty -> no callbacks on Iterate
TEST_F(WriteBatchAppendTest_207, Append_EmptyToEmpty_NoOps_207) {
  WriteBatch dst;
  WriteBatch src;

  dst.Append(src);

  StrictMock<MockHandler> h;
  EXPECT_CALL(h, Put(_, _)).Times(0);
  EXPECT_CALL(h, Delete(_)).Times(0);

  Status st = dst.Iterate(&h);
  EXPECT_TRUE(st.ok());
}

// Non-empty src + Empty dst -> callbacks match src, in order
TEST_F(WriteBatchAppendTest_207, Append_NonEmptySourceToEmptyDest_207) {
  WriteBatch dst;
  WriteBatch src;

  src.Put(S("a"), S("1"));
  src.Delete(S("b"));

  dst.Append(src);

  StrictMock<MockHandler> h;
  {
    InSequence seq;
    EXPECT_CALL(h, Put(S("a"), S("1")));
    EXPECT_CALL(h, Delete(S("b")));
  }

  Status st = dst.Iterate(&h);
  EXPECT_TRUE(st.ok());
}

// Empty src + Non-empty dst -> dst unchanged
TEST_F(WriteBatchAppendTest_207, Append_EmptySourceToNonEmptyDest_207) {
  WriteBatch dst;
  dst.Put(S("x"), S("0"));

  WriteBatch src;  // empty
  dst.Append(src);

  StrictMock<MockHandler> h;
  EXPECT_CALL(h, Put(S("x"), S("0")));

  Status st = dst.Iterate(&h);
  EXPECT_TRUE(st.ok());
}

// Verify order: existing dst entries come before appended src entries
TEST_F(WriteBatchAppendTest_207, Append_Order_DestThenSource_207) {
  WriteBatch dst;
  dst.Put(S("d"), S("1"));
  dst.Delete(S("e"));

  WriteBatch src;
  src.Put(S("s"), S("2"));
  src.Delete(S("t"));

  dst.Append(src);

  StrictMock<MockHandler> h;
  {
    InSequence seq;
    EXPECT_CALL(h, Put(S("d"), S("1")));
    EXPECT_CALL(h, Delete(S("e")));
    EXPECT_CALL(h, Put(S("s"), S("2")));
    EXPECT_CALL(h, Delete(S("t")));
  }

  Status st = dst.Iterate(&h);
  EXPECT_TRUE(st.ok());
}

// Source batch must be unchanged after Append (idempotent w.r.t. src)
TEST_F(WriteBatchAppendTest_207, Append_SourceUnmodified_207) {
  WriteBatch dst;
  dst.Put(S("d"), S("0"));

  WriteBatch src;
  src.Put(S("k"), S("v"));
  src.Delete(S("z"));

  dst.Append(src);

  // Verify src still iterates its original operations
  StrictMock<MockHandler> h_src;
  {
    InSequence seq;
    EXPECT_CALL(h_src, Put(S("k"), S("v")));
    EXPECT_CALL(h_src, Delete(S("z")));
  }
  Status st_src = src.Iterate(&h_src);
  EXPECT_TRUE(st_src.ok());
}

// Multiple appends accumulate in sequence
TEST_F(WriteBatchAppendTest_207, Append_MultipleAppends_Cumulative_207) {
  WriteBatch dst;
  dst.Put(S("d1"), S("v1"));

  WriteBatch s1;
  s1.Delete(S("x"));

  WriteBatch s2;
  s2.Put(S("d2"), S("v2"));

  dst.Append(s1);
  dst.Append(s2);

  StrictMock<MockHandler> h;
  {
    InSequence seq;
    EXPECT_CALL(h, Put(S("d1"), S("v1")));  // from dst
    EXPECT_CALL(h, Delete(S("x")));         // from s1
    EXPECT_CALL(h, Put(S("d2"), S("v2")));  // from s2
  }

  Status st = dst.Iterate(&h);
  EXPECT_TRUE(st.ok());
}

}  // namespace leveldb
