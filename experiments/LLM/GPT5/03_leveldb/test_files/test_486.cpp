// Writer_test_486.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/log_writer.h"
#include "leveldb/env.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

namespace leveldb {
namespace {

class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

class WriterTest_486 : public ::testing::Test {
 protected:
  MockWritableFile mock_file_;
};

}  // namespace

// Verifies the class is non-copyable as declared by the interface.
TEST(WriterCopyControl_486, DeletedCopyAndAssignment_486) {
  using log::Writer;
  static_assert(!std::is_copy_constructible<Writer>::value,
                "Writer should not be copy-constructible");
  static_assert(!std::is_copy_assignable<Writer>::value,
                "Writer should not be copy-assignable");
}

// Normal operation: AddRecord should attempt to append to the destination and
// return OK when the destination append succeeds.
TEST_F(WriterTest_486, AddRecord_AppendsAndReturnsOK_486) {
  log::Writer writer(&mock_file_);

  // We do not assume how many physical appends happen; only that at least one
  // append is attempted and overall Status is OK when all appends succeed.
  EXPECT_CALL(mock_file_, Append(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(Status::OK()));

  Slice payload("hello world");
  Status s = writer.AddRecord(payload);
  EXPECT_TRUE(s.ok());
}

// Error propagation: if the WritableFile::Append returns an error Status,
// AddRecord should return a (non-ok) Status as an observable effect.
TEST_F(WriterTest_486, AddRecord_PropagatesAppendError_486) {
  log::Writer writer(&mock_file_);

  // First append fails; Writer should surface the failure to the caller.
  Status io_error = Status::IOError("append failed (test)");
  EXPECT_CALL(mock_file_, Append(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(io_error));

  Slice payload("some bytes");
  Status s = writer.AddRecord(payload);
  EXPECT_FALSE(s.ok());
  // We intentionally do not assert exact error type/message beyond non-ok,
  // to avoid depending on internal formatting.
}

// Boundary-ish constructor scenario: constructing with an explicit dest_length
// must still allow adding a record; we only verify observable interaction
// (that an append is attempted) without inferring internal block math.
TEST_F(WriterTest_486, CtorWithDestLength_AddRecordAppends_486) {
  // Choose an arbitrary dest_length; we avoid relying on kBlockSize details.
  const uint64_t dest_length = 12345;
  log::Writer writer(&mock_file_, dest_length);

  EXPECT_CALL(mock_file_, Append(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(Status::OK()));

  Slice payload("record after preexisting bytes");
  Status s = writer.AddRecord(payload);
  EXPECT_TRUE(s.ok());
}

// Sanity: constructing the Writer with a valid destination should not,
// by itself, cause any file operation; only AddRecord triggers appends.
// (We don't assert *no* calls at construction time—just ensure AddRecord leads to calls.)
TEST_F(WriterTest_486, ConstructionPlusAddRecordTriggersAppend_486) {
  log::Writer writer(&mock_file_);

  EXPECT_CALL(mock_file_, Append(_))
      .Times(AtLeast(1))
      .WillRepeatedly(Return(Status::OK()));

  Slice payload("x");
  Status s = writer.AddRecord(payload);
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
