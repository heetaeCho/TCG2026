// File: log_writer_init_type_crc_test.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cstring>

// Pull in the constant for kMaxRecordType
#include "db/log_format.h"

// Include the implementation file so the internal-linkage function is visible here.
// IMPORTANT: Do not link the production object of db/log_writer.cc in this test target.
#include "db/log_writer.cc"

namespace {

using leveldb::log::kMaxRecordType;

// A small helper to fill a buffer with a sentinel value (byte-wise).
static void FillWithSentinel(uint32_t* p, size_t n, uint32_t sentinel) {
  for (size_t i = 0; i < n; ++i) p[i] = sentinel;
}

// ---------- Tests ----------

TEST(LogWriterInitTypeCrcTest_344, PopulatesAllEntries_344) {
  const uint32_t kSentinel = 0xAAAAAAAAu;

  // Allocate exactly kMaxRecordType + 1 entries as the writable region.
  std::vector<uint32_t> buf(static_cast<size_t>(kMaxRecordType) + 1u);
  FillWithSentinel(buf.data(), buf.size(), kSentinel);

  // Call the function under test.
  // Observable expectation: it populates all entries in [0, kMaxRecordType].
  leveldb::log::InitTypeCrc(buf.data());

  // Verify: every slot is changed from the sentinel (i.e., populated).
  for (size_t i = 0; i < buf.size(); ++i) {
    EXPECT_NE(buf[i], kSentinel) << "Entry " << i << " was not populated";
  }
}

TEST(LogWriterInitTypeCrcTest_344, DoesNotWriteOutsideBounds_344) {
  const uint32_t kSentinel = 0xDEADBEEFu;
  const uint32_t kCanaryL  = 0x11111111u;
  const uint32_t kCanaryR  = 0x22222222u;

  // Create a buffer with left/right canaries to detect out-of-bounds writes.
  const size_t kPayloadSize = static_cast<size_t>(kMaxRecordType) + 1u;
  std::vector<uint32_t> raw(kPayloadSize + 2u /* left+right canaries */);

  raw.front() = kCanaryL;
  raw.back()  = kCanaryR;

  uint32_t* payload = raw.data() + 1;
  FillWithSentinel(payload, kPayloadSize, kSentinel);

  leveldb::log::InitTypeCrc(payload);

  // Verify: canaries unchanged (no writes outside [0, kMaxRecordType]).
  EXPECT_EQ(raw.front(), kCanaryL) << "Left canary was modified";
  EXPECT_EQ(raw.back(),  kCanaryR) << "Right canary was modified";

  // Also ensure the intended region was actually populated (not left as sentinel).
  for (size_t i = 0; i < kPayloadSize; ++i) {
    EXPECT_NE(payload[i], kSentinel) << "Entry " << i << " was not populated";
  }
}

TEST(LogWriterInitTypeCrcTest_344, DeterministicAcrossIndependentBuffers_344) {
  const size_t kSize = static_cast<size_t>(kMaxRecordType) + 1u;
  std::vector<uint32_t> a(kSize), b(kSize);

  leveldb::log::InitTypeCrc(a.data());
  leveldb::log::InitTypeCrc(b.data());

  ASSERT_EQ(a.size(), b.size());
  for (size_t i = 0; i < a.size(); ++i) {
    EXPECT_EQ(a[i], b[i]) << "Mismatch at index " << i;
  }
}

TEST(LogWriterInitTypeCrcTest_344, IdempotentOnSameBuffer_344) {
  const size_t kSize = static_cast<size_t>(kMaxRecordType) + 1u;
  std::vector<uint32_t> v(kSize);

  leveldb::log::InitTypeCrc(v.data());
  // Take a snapshot after the first call.
  std::vector<uint32_t> snapshot = v;

  // Call again; observable expectation: contents remain the same.
  leveldb::log::InitTypeCrc(v.data());

  ASSERT_EQ(v.size(), snapshot.size());
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], snapshot[i]) << "Value changed at index " << i << " after second call";
  }
}

}  // namespace
