// File: write_batch_iterate_test_200.cc
#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "db/dbformat.h"
#include "leveldb/status.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::InSequence;
using ::testing::StrictMock;
using ::testing::Truly;

namespace leveldb {

class MockHandler : public WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));
  MOCK_METHOD(void, Delete, (const Slice& key), (override));
};

static auto SliceEq(const std::string& want) {
  return Truly([want](const Slice& s) { return s.ToString() == want; });
}

// ---------- Normal operation ----------

TEST(WriteBatchIterateTest_200, EmptyBatch_OkAndNoHandlerCalls_200) {
  WriteBatch b;  // fresh, empty batch
  StrictMock<MockHandler> h;

  // Expect: Iterate returns OK and nothing is called on handler
  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

TEST(WriteBatchIterateTest_200, PutAndDelete_InvokeHandlerInOrder_200) {
  WriteBatch b;
  b.Put(Slice("k1"), Slice("v1"));
  b.Delete(Slice("k2"));

  StrictMock<MockHandler> h;
  {
    InSequence seq;  // enforce call order
    EXPECT_CALL(h, Put(SliceEq("k1"), SliceEq("v1")));
    EXPECT_CALL(h, Delete(SliceEq("k2")));
  }

  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

// ---------- Boundary / error cases ----------

TEST(WriteBatchIterateTest_200, TooSmallBuffer_IsCorruption_200) {
  WriteBatch b;

  // Manually set contents smaller than header to trigger size check
  std::string tiny = "abc";  // < kHeader
  WriteBatchInternal::SetContents(&b, Slice(tiny));

  StrictMock<MockHandler> h;
  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.IsCorruption());
}

TEST(WriteBatchIterateTest_200, UnknownTag_IsCorruption_200) {
  // Start from a valid empty header
  WriteBatch base;
  std::string contents = WriteBatchInternal::Contents(&base).ToString();

  // Append an unknown tag byte (neither kTypeValue nor kTypeDeletion)
  contents.push_back(static_cast<char>(0xFF));

  WriteBatch b;
  WriteBatchInternal::SetContents(&b, Slice(contents));
  // Count says there is 1 record (so we don't fail on wrong-count first)
  WriteBatchInternal::SetCount(&b, 1);

  StrictMock<MockHandler> h;
  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.IsCorruption());
}

TEST(WriteBatchIterateTest_200, BadPutEncoding_IsCorruption_200) {
  // Valid empty header, followed by a Value tag without length-prefixed key/value
  WriteBatch base;
  std::string contents = WriteBatchInternal::Contents(&base).ToString();
  contents.push_back(static_cast<char>(kTypeValue));  // missing key/value bytes

  WriteBatch b;
  WriteBatchInternal::SetContents(&b, Slice(contents));
  WriteBatchInternal::SetCount(&b, 1);

  StrictMock<MockHandler> h;
  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.IsCorruption());
}

TEST(WriteBatchIterateTest_200, BadDeleteEncoding_IsCorruption_200) {
  // Valid empty header, followed by a Deletion tag without length-prefixed key
  WriteBatch base;
  std::string contents = WriteBatchInternal::Contents(&base).ToString();
  contents.push_back(static_cast<char>(kTypeDeletion));  // missing key bytes

  WriteBatch b;
  WriteBatchInternal::SetContents(&b, Slice(contents));
  WriteBatchInternal::SetCount(&b, 1);

  StrictMock<MockHandler> h;
  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.IsCorruption());
}

TEST(WriteBatchIterateTest_200, WrongCount_IsCorruption_200) {
  // Build a valid batch via public API so encoding is correct
  WriteBatch b;
  b.Put(Slice("k"), Slice("v"));

  // Now force an incorrect count (found will be 1; set count to 2)
  WriteBatchInternal::SetCount(&b, 2);

  StrictMock<MockHandler> h;
  // We can't assume whether handler is called before count check; we only check status.
  Status s = b.Iterate(&h);
  EXPECT_TRUE(s.IsCorruption());
}

}  // namespace leveldb
