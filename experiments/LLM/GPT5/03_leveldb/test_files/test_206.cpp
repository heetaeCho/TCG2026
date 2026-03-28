// write_batch_delete_test_206.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/write_batch.h"
#include "db/write_batch_internal.h"
#include "leveldb/slice.h"
#include "db/dbformat.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::StrictMock;

namespace leveldb {

// A mock handler to verify Iterate() interactions.
// This treats Handler as an external collaborator.
class MockHandler : public WriteBatch::Handler {
 public:
  MOCK_METHOD(void, Put, (const Slice& key, const Slice& value), (override));
  MOCK_METHOD(void, Delete, (const Slice& key), (override));
};

class WriteBatchTest_206 : public ::testing::Test {
 protected:
  WriteBatch batch_;
};

// [Normal] Delete increments the batch count by 1.
TEST_F(WriteBatchTest_206, DeleteIncreasesCount_206) {
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));

  const Slice key("abc");
  batch_.Delete(key);

  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));
}

// [Boundary] Delete called with an empty key should still be recorded
// and visible via Count() and Iterate().
TEST_F(WriteBatchTest_206, DeleteWithEmptyKey_206) {
  ASSERT_EQ(0, WriteBatchInternal::Count(&batch_));

  const Slice empty_key("");
  batch_.Delete(empty_key);

  EXPECT_EQ(1, WriteBatchInternal::Count(&batch_));

  StrictMock<MockHandler> h;
  // Expect a single Delete with an empty key; no Put calls.
  EXPECT_CALL(h, Delete(_)).Times(1);
  EXPECT_CALL(h, Put(_, _)).Times(0);

  // Iterate should succeed and invoke the Delete callback once.
  Status s = batch_.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

// [Interaction] Iterate must invoke Handler::Delete once with the same key.
TEST_F(WriteBatchTest_206, IterateInvokesDeleteOnceWithKey_206) {
  const std::string key_str = "to_remove";
  batch_.Delete(Slice(key_str));

  StrictMock<MockHandler> h;
  // Verify the Delete is called with a Slice that matches our key bytes/size.
  EXPECT_CALL(h, Delete(::testing::Truly([&](const Slice& k) {
                return k.size() == key_str.size() &&
                       std::string(k.data(), k.size()) == key_str;
              }))).Times(1);
  EXPECT_CALL(h, Put(_, _)).Times(0);

  Status s = batch_.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

// [Size effect] ApproximateSize / ByteSize increase after a Delete.
TEST_F(WriteBatchTest_206, ApproxSizeAndByteSizeIncreaseAfterDelete_206) {
  const size_t approx_before =
#if defined(__cpp_constexpr) // guard in case ApproximateSize is const in your tree
      batch_.ApproximateSize();
#else
      batch_.ApproximateSize();
#endif
  const size_t bytes_before = WriteBatchInternal::ByteSize(&batch_);

  batch_.Delete(Slice("k"));

  const size_t approx_after = batch_.ApproximateSize();
  const size_t bytes_after  = WriteBatchInternal::ByteSize(&batch_);

  // We do not assert any specific encoding; only that sizes increase.
  EXPECT_GT(approx_after, approx_before);
  EXPECT_GT(bytes_after, bytes_before);
}

// [Multiple ops] Two Deletes: Count==2 and Iterate calls Delete twice in order.
TEST_F(WriteBatchTest_206, MultipleDeletesAreCountedAndIteratedInOrder_206) {
  const std::string k1 = "a";
  const std::string k2 = "bbbb";

  batch_.Delete(Slice(k1));
  batch_.Delete(Slice(k2));

  EXPECT_EQ(2, WriteBatchInternal::Count(&batch_));

  StrictMock<MockHandler> h;
  {
    InSequence seq;  // enforce call order
    EXPECT_CALL(h, Delete(::testing::Truly([&](const Slice& k) {
                  return std::string(k.data(), k.size()) == k1;
                })));
    EXPECT_CALL(h, Delete(::testing::Truly([&](const Slice& k) {
                  return std::string(k.data(), k.size()) == k2;
                })));
  }
  EXPECT_CALL(h, Put(_, _)).Times(0);

  Status s = batch_.Iterate(&h);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
