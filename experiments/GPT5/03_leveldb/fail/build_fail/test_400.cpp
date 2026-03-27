// File: table/format_readblock_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "table/format.h"   // BlockHandle, BlockContents, kBlockTrailerSize, CompressionType
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include "leveldb/env.h"    // RandomAccessFile
#include "table/format.h"   // for BlockHandle
#include "table/format.cc"  // to get ReadBlock declaration if not in header (or include proper header exposing it)

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;

namespace leveldb {

// ---- Test doubles ----
class MockRandomAccessFile : public RandomAccessFile {
 public:
  MOCK_METHOD(Status, Read,
              (uint64_t offset, size_t n, Slice* result, char* scratch),
              (override));
  ~MockRandomAccessFile() override = default;
};

// ---- Small helpers (test-only) ----
static inline void PutFixed32LE(std::string& dst, uint32_t v) {
  // Not re-implementing any LevelDB internals—just creating test input bytes.
  char buf[4];
  buf[0] = static_cast<char>(v & 0xff);
  buf[1] = static_cast<char>((v >> 8) & 0xff);
  buf[2] = static_cast<char>((v >> 16) & 0xff);
  buf[3] = static_cast<char>((v >> 24) & 0xff);
  dst.append(buf, 4);
}

static std::string MakeRawBlock(const std::string& payload,
                                uint8_t compression_type,
                                uint32_t masked_crc /* arbitrary when checksums not verified */) {
  std::string s = payload;
  s.push_back(static_cast<char>(compression_type));
  PutFixed32LE(s, masked_crc);
  return s;
}

// ---- Tests ----

// Normal operation: kNoCompression, file returns data aliasing 'scratch'.
// Expect: OK, result contains the first 'n' bytes, heap_allocated=true, cachable=true.
TEST(ReadBlockTest_400, NoCompression_UsesScratchBuffer_400) {
  MockRandomAccessFile file;

  const std::string payload = "hello_world";  // n = 11
  const uint64_t n = payload.size();
  const std::string whole = MakeRawBlock(payload, kNoCompression, /*masked_crc*/0);

  // BlockHandle points to offset 100 (arbitrary) and 'n' bytes of data.
  BlockHandle handle;
  handle.set_offset(100);
  handle.set_size(n);

  EXPECT_CALL(file, Read(handle.offset(), n + kBlockTrailerSize, _, _))
      .WillOnce(Invoke([&](uint64_t /*offset*/, size_t /*read_n*/, Slice* result, char* scratch) {
        // Simulate the environment filling the provided scratch and pointing result at it.
        std::memcpy(scratch, whole.data(), whole.size());
        *result = Slice(scratch, whole.size());
        return Status::OK();
      }));

  ReadOptions ro;  // verify_checksums = false by default
  BlockContents out;
  Status s = ReadBlock(&file, ro, handle, &out);

  ASSERT_TRUE(s.ok());
  EXPECT_EQ(out.data.size(), n);
  EXPECT_EQ(std::string(out.data.data(), out.data.size()), payload);
  EXPECT_TRUE(out.heap_allocated);  // data == buf path
  EXPECT_TRUE(out.cachable);
}

// Normal operation: kNoCompression, file returns data NOT aliasing 'scratch'.
// Expect: OK, result contains the first 'n' bytes, heap_allocated=false, cachable=false.
TEST(ReadBlockTest_400, NoCompression_UsesExternalMapping_400) {
  MockRandomAccessFile file;

  const std::string payload = "ABCDE";  // n = 5
  const uint64_t n = payload.size();
  const std::string whole = MakeRawBlock(payload, kNoCompression, /*masked_crc*/0);

  // Backing store that outlives the Read call; result.data() will point here.
  static std::string mapped_storage = whole;

  BlockHandle handle;
  handle.set_offset(777);
  handle.set_size(n);

  EXPECT_CALL(file, Read(handle.offset(), n + kBlockTrailerSize, _, _))
      .WillOnce(Invoke([&](uint64_t /*offset*/, size_t /*read_n*/, Slice* result, char* /*scratch*/) {
        *result = Slice(mapped_storage.data(), mapped_storage.size());
        return Status::OK();
      }));

  ReadOptions ro;
  BlockContents out;
  Status s = ReadBlock(&file, ro, handle, &out);

  ASSERT_TRUE(s.ok());
  EXPECT_EQ(out.data.size(), n);
  EXPECT_EQ(std::string(out.data.data(), out.data.size()), payload);
  EXPECT_FALSE(out.heap_allocated);  // data != buf path
  EXPECT_FALSE(out.cachable);        // Do not double-cache in this branch
}

// Error: underlying file->Read returns non-OK status. Expect that exact status to be returned.
TEST(ReadBlockTest_400, PropagatesReadError_400) {
  MockRandomAccessFile file;

  const uint64_t n = 8;
  BlockHandle handle;
  handle.set_offset(0x1234);
  handle.set_size(n);

  EXPECT_CALL(file, Read(handle.offset(), n + kBlockTrailerSize, _, _))
      .WillOnce(Return(Status::IOError("boom")));

  ReadOptions ro;
  BlockContents out;
  Status s = ReadBlock(&file, ro, handle, &out);

  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// Error: truncated read (contents.size() != n + kBlockTrailerSize). Expect Corruption("truncated block read").
TEST(ReadBlockTest_400, TruncatedBlockReadIsCorruption_400) {
  MockRandomAccessFile file;

  const std::string payload = "123456"; // n = 6
  const uint64_t n = payload.size();
  const std::string whole = MakeRawBlock(payload, kNoCompression, /*masked_crc*/0);

  BlockHandle handle;
  handle.set_offset(55);
  handle.set_size(n);

  // Return one byte short
  const size_t short_size = whole.size() - 1;

  EXPECT_CALL(file, Read(handle.offset(), n + kBlockTrailerSize, _, _))
      .WillOnce(Invoke([&](uint64_t /*offset*/, size_t /*read_n*/, Slice* result, char* scratch) {
        std::memcpy(scratch, whole.data(), short_size);
        *result = Slice(scratch, short_size);
        return Status::OK();
      }));

  ReadOptions ro;
  BlockContents out;
  Status s = ReadBlock(&file, ro, handle, &out);

  EXPECT_TRUE(s.IsCorruption());
  // Optional string check (depends on Status::ToString formatting):
  // EXPECT_NE(s.ToString().find("truncated block read"), std::string::npos);
}

// Error: bad block type (unknown compression). Expect Corruption("bad block type").
TEST(ReadBlockTest_400, BadBlockTypeIsCorruption_400) {
  MockRandomAccessFile file;

  const std::string payload = "xyz";
  const uint64_t n = payload.size();
  const uint8_t bad_type = 0xff;  // not in {0,1,2}
  const std::string whole = MakeRawBlock(payload, bad_type, /*masked_crc*/0);

  BlockHandle handle;
  handle.set_offset(9);
  handle.set_size(n);

  EXPECT_CALL(file, Read(handle.offset(), n + kBlockTrailerSize, _, _))
      .WillOnce(Invoke([&](uint64_t /*offset*/, size_t /*read_n*/, Slice* result, char* scratch) {
        std::memcpy(scratch, whole.data(), whole.size());
        *result = Slice(scratch, whole.size());
        return Status::OK();
      }));

  ReadOptions ro;
  BlockContents out;
  Status s = ReadBlock(&file, ro, handle, &out);

  EXPECT_TRUE(s.IsCorruption());
  // Optional: check message contains "bad block type"
  // EXPECT_NE(s.ToString().find("bad block type"), std::string::npos);
}

// Error: checksum mismatch when verify_checksums = true. Expect Corruption("block checksum mismatch").
TEST(ReadBlockTest_400, ChecksumMismatchWhenVerifiedIsCorruption_400) {
  MockRandomAccessFile file;

  const std::string payload = "checkme";
  const uint64_t n = payload.size();
  // Store a bogus masked CRC (zero), which will mismatch unless the actual also decodes to zero.
  const std::string whole = MakeRawBlock(payload, kNoCompression, /*masked_crc*/0);

  BlockHandle handle;
  handle.set_offset(42);
  handle.set_size(n);

  EXPECT_CALL(file, Read(handle.offset(), n + kBlockTrailerSize, _, _))
      .WillOnce(Invoke([&](uint64_t /*offset*/, size_t /*read_n*/, Slice* result, char* scratch) {
        std::memcpy(scratch, whole.data(), whole.size());
        *result = Slice(scratch, whole.size());
        return Status::OK();
      }));

  ReadOptions ro;
  ro.verify_checksums = true;  // trigger checksum verification

  BlockContents out;
  Status s = ReadBlock(&file, ro, handle, &out);

  EXPECT_TRUE(s.IsCorruption());
  // Optional: message check
  // EXPECT_NE(s.ToString().find("block checksum mismatch"), std::string::npos);
}

}  // namespace leveldb
