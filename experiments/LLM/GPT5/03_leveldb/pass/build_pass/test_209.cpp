// File: write_batch_setcontents_test_209.cc

#include "db/write_batch_internal.h"
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"

#include <gtest/gtest.h>
#include <string>

using namespace leveldb;

namespace {

// From the prompt's provided global (db/write_batch.cc): kHeader == 12.
constexpr size_t kHeaderValueForTests = 12;

// Helper to build a deterministic byte sequence of given size.
static std::string MakeBytes(size_t n) {
  std::string s;
  s.resize(n);
  for (size_t i = 0; i < n; ++i) {
    s[i] = static_cast<char>(i % 251);  // non-trivial repeating pattern
  }
  return s;
}

class WriteBatchSetContentsTest_209 : public ::testing::Test {};

}  // namespace

// Normal operation: copies provided bytes into the batch (size >= kHeader).
TEST_F(WriteBatchSetContentsTest_209, CopiesBytesIntoBatch_209) {
  WriteBatch b;

  const std::string payload = MakeBytes(kHeaderValueForTests + 20);  // >= header
  const Slice contents(payload.data(), payload.size());

  WriteBatchInternal::SetContents(&b, contents);

  Slice got = WriteBatchInternal::Contents(&b);
  EXPECT_EQ(got.size(), payload.size());
  EXPECT_EQ(std::string(got.data(), got.size()), payload);

  // ByteSize should reflect the content length.
  EXPECT_EQ(WriteBatchInternal::ByteSize(&b), payload.size());
}

// Boundary: exactly kHeader bytes is accepted and preserved.
TEST_F(WriteBatchSetContentsTest_209, AcceptsExactlyHeaderSize_209) {
  WriteBatch b;

  const std::string header_only = MakeBytes(kHeaderValueForTests);  // exactly header
  const Slice contents(header_only.data(), header_only.size());

  WriteBatchInternal::SetContents(&b, contents);

  Slice got = WriteBatchInternal::Contents(&b);
  EXPECT_EQ(got.size(), header_only.size());
  EXPECT_EQ(std::string(got.data(), got.size()), header_only);
  EXPECT_EQ(WriteBatchInternal::ByteSize(&b), header_only.size());
}

// Normal operation: calling SetContents again overwrites previous content.
TEST_F(WriteBatchSetContentsTest_209, OverwritesPreviousContents_209) {
  WriteBatch b;

  const std::string first = MakeBytes(kHeaderValueForTests + 5);
  WriteBatchInternal::SetContents(&b, Slice(first.data(), first.size()));

  const std::string second = MakeBytes(kHeaderValueForTests + 37);  // different size & pattern
  WriteBatchInternal::SetContents(&b, Slice(second.data(), second.size()));

  Slice got = WriteBatchInternal::Contents(&b);
  EXPECT_EQ(got.size(), second.size());
  EXPECT_EQ(std::string(got.data(), got.size()), second);
  EXPECT_EQ(WriteBatchInternal::ByteSize(&b), second.size());
}

// Exceptional/error path (observable via assert): contents smaller than kHeader should fail.
// Note: This is a death test and requires asserts enabled in the test build.
TEST_F(WriteBatchSetContentsTest_209, FailsWhenContentsSmallerThanHeader_209) {
  WriteBatch b;

  const std::string too_small = MakeBytes(kHeaderValueForTests - 1);
  // The exact death regex is not important here; empty matches anything.
  ASSERT_LT(too_small.size(), kHeaderValueForTests);
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-core.CallAndMessage)
        WriteBatchInternal::SetContents(&b, Slice(too_small.data(), too_small.size()));
      },
      "");
}
