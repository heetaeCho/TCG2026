// File: db/log_reader_last_record_offset_test_325.cc

#include <gtest/gtest.h>

// ---- Minimal stubs to satisfy the public interface dependencies ----
// We do NOT simulate any internal behavior; these are only to allow construction.
namespace leveldb {

// Forward-declare a trivial Status and Slice that won't be used by these tests.
class Status {};
class Slice {};

class SequentialFile {
  // Intentionally empty: the Reader under test won't call into this in our cases.
};

namespace log {
// kBlockSize is referenced by the Reader constructor; define a sensible constant.
static constexpr size_t kBlockSize = 32768;

struct Reporter {
  virtual ~Reporter() = default;
  // Intentionally omitted methods; not needed for these tests.
};

}  // namespace log
}  // namespace leveldb

// Include the provided interface (treating it as a black box).
#include "db/log_reader.h"

using leveldb::log::Reader;

class ReaderLastRecordOffsetTest_325 : public ::testing::Test {
protected:
  leveldb::SequentialFile dummy_file_;
  leveldb::log::Reporter* reporter_ = nullptr;  // Not used by these tests.
};

// [Normal] After fresh construction with initial_offset = 0, LastRecordOffset() should be 0.
TEST_F(ReaderLastRecordOffsetTest_325, ReturnsZeroInitially_325) {
  Reader reader(/*file=*/&dummy_file_,
                /*reporter=*/reporter_,
                /*checksum=*/false,
                /*initial_offset=*/0);

  uint64_t off = reader.LastRecordOffset();
  EXPECT_EQ(off, 0u) << "Expected last-record offset to be zero immediately after construction.";
}

// [Boundary] Calling LastRecordOffset() multiple times without any reads should be stable (idempotent).
TEST_F(ReaderLastRecordOffsetTest_325, StableWithoutReads_325) {
  Reader reader(/*file=*/&dummy_file_,
                /*reporter=*/reporter_,
                /*checksum=*/false,
                /*initial_offset=*/0);

  uint64_t first = reader.LastRecordOffset();
  uint64_t second = reader.LastRecordOffset();
  EXPECT_EQ(first, second) << "LastRecordOffset() should be stable across repeated calls with no reads.";
}

// [Boundary] A non-zero initial_offset is construction-time configuration; without reads,
// LastRecordOffset() should still reflect “no records observed yet”.
TEST_F(ReaderLastRecordOffsetTest_325, InitialOffsetDoesNotPrepopulateLastRecord_325) {
  const uint64_t kInitialOffset = 1024;  // Arbitrary non-zero.
  Reader reader(/*file=*/&dummy_file_,
                /*reporter=*/reporter_,
                /*checksum=*/true,
                /*initial_offset=*/kInitialOffset);

  // We only assert on the observable: LastRecordOffset() value after construction.
  EXPECT_EQ(reader.LastRecordOffset(), 0u)
      << "Initial offset should not by itself imply any last-record position.";
}
