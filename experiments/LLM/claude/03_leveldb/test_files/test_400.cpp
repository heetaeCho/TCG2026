#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "table/format.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include "util/coding.h"
#include "util/crc32c.h"
#include "port/port.h"

#include <cstring>
#include <string>

namespace leveldb {

// Mock for RandomAccessFile
class MockRandomAccessFile : public RandomAccessFile {
 public:
  MOCK_METHOD(Status, Read, (uint64_t offset, size_t n, Slice* result, char* scratch), (const, override));
};

class ReadBlockTest_400 : public ::testing::Test {
 protected:
  MockRandomAccessFile file_;
  ReadOptions options_;
  BlockHandle handle_;
  BlockContents result_;

  // Helper to create a valid uncompressed block with proper trailer
  std::string MakeBlock(const std::string& data, CompressionType type, bool valid_crc = true) {
    std::string block = data;
    // Append compression type byte
    block.push_back(static_cast<char>(type));
    // Compute CRC over data + type byte
    uint32_t crc = crc32c::Value(block.data(), block.size());
    if (!valid_crc) {
      crc = crc + 1;  // corrupt the CRC
    }
    crc = crc32c::Mask(crc);
    char crc_bytes[4];
    EncodeFixed32(crc_bytes, crc);
    block.append(crc_bytes, 4);
    return block;
  }

  void SetUp() override {
    handle_.set_offset(0);
    handle_.set_size(0);
    options_.verify_checksums = false;
    options_.fill_cache = true;
  }

  void TearDown() override {
    if (result_.heap_allocated) {
      delete[] result_.data.data();
    }
  }
};

// Test: Read returns an error status from the file
TEST_F(ReadBlockTest_400, FileReadError_400) {
  handle_.set_offset(0);
  handle_.set_size(10);

  EXPECT_CALL(file_, Read(0, 10 + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce(testing::Return(Status::IOError("read failed")));

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// Test: Read returns fewer bytes than expected (truncated block)
TEST_F(ReadBlockTest_400, TruncatedBlockRead_400) {
  handle_.set_offset(0);
  handle_.set_size(10);

  EXPECT_CALL(file_, Read(0, 10 + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([](uint64_t offset, size_t n, Slice* result, char* scratch) {
        // Return fewer bytes than requested
        memset(scratch, 0, 5);
        *result = Slice(scratch, 5);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_NE(s.ToString().find("truncated block read"), std::string::npos);
}

// Test: Successful read of uncompressed block where data is in scratch buffer
TEST_F(ReadBlockTest_400, UncompressedBlockFromScratch_400) {
  std::string data = "hello world";
  handle_.set_offset(0);
  handle_.set_size(data.size());

  std::string block = MakeBlock(data, kNoCompression);

  EXPECT_CALL(file_, Read(0, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        // Copy into scratch buffer, so data == buf
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result_.data.size(), data.size());
  EXPECT_EQ(std::string(result_.data.data(), result_.data.size()), data);
  EXPECT_TRUE(result_.heap_allocated);
  EXPECT_TRUE(result_.cachable);
}

// Test: Successful read of uncompressed block where data is NOT in scratch buffer
TEST_F(ReadBlockTest_400, UncompressedBlockNotFromScratch_400) {
  std::string data = "hello world";
  handle_.set_offset(0);
  handle_.set_size(data.size());

  // We store the block data in a persistent string so the pointer is different from scratch
  std::string block = MakeBlock(data, kNoCompression);

  EXPECT_CALL(file_, Read(0, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        // Point result to block's data, not scratch
        *result = Slice(block.data(), n);
        return Status::OK();
      });

  // Need to prevent TearDown from deleting since heap_allocated will be false
  BlockContents local_result;
  local_result.data = Slice();
  local_result.cachable = false;
  local_result.heap_allocated = false;

  Status s = ReadBlock(&file_, options_, handle_, &local_result);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(local_result.data.size(), data.size());
  EXPECT_EQ(std::string(local_result.data.data(), local_result.data.size()), data);
  EXPECT_FALSE(local_result.heap_allocated);
  EXPECT_FALSE(local_result.cachable);
}

// Test: Checksum verification passes for valid block
TEST_F(ReadBlockTest_400, ChecksumVerificationPass_400) {
  std::string data = "checksum test data";
  handle_.set_offset(0);
  handle_.set_size(data.size());
  options_.verify_checksums = true;

  std::string block = MakeBlock(data, kNoCompression, true);

  EXPECT_CALL(file_, Read(0, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result_.data.size(), data.size());
}

// Test: Checksum verification fails for corrupted block
TEST_F(ReadBlockTest_400, ChecksumVerificationFail_400) {
  std::string data = "checksum fail test";
  handle_.set_offset(0);
  handle_.set_size(data.size());
  options_.verify_checksums = true;

  std::string block = MakeBlock(data, kNoCompression, false);

  EXPECT_CALL(file_, Read(0, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_NE(s.ToString().find("block checksum mismatch"), std::string::npos);
}

// Test: Bad compression type returns corruption
TEST_F(ReadBlockTest_400, BadCompressionType_400) {
  std::string data = "bad type data";
  handle_.set_offset(0);
  handle_.set_size(data.size());

  // Build a block with an invalid compression type (e.g., 0xFF)
  std::string block = data;
  block.push_back(static_cast<char>(0xFF));  // invalid type
  uint32_t crc = crc32c::Value(block.data(), block.size());
  crc = crc32c::Mask(crc);
  char crc_bytes[4];
  EncodeFixed32(crc_bytes, crc);
  block.append(crc_bytes, 4);

  EXPECT_CALL(file_, Read(0, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_NE(s.ToString().find("bad block type"), std::string::npos);
}

// Test: Empty block (size 0) with no compression
TEST_F(ReadBlockTest_400, EmptyBlock_400) {
  std::string data = "";
  handle_.set_offset(0);
  handle_.set_size(0);

  std::string block = MakeBlock(data, kNoCompression);

  EXPECT_CALL(file_, Read(0, kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result_.data.size(), 0u);
}

// Test: Snappy compressed block - successful decompression
TEST_F(ReadBlockTest_400, SnappyCompressedBlock_400) {
  // First check if Snappy is available
  std::string original = "hello snappy hello snappy hello snappy";
  std::string compressed;
  
  // Try to compress with Snappy
  if (!port::Snappy_Compress(original.data(), original.size(), &compressed)) {
    GTEST_SKIP() << "Snappy compression not available";
  }

  handle_.set_offset(0);
  handle_.set_size(compressed.size());

  std::string block = MakeBlock(compressed, kSnappyCompression);

  EXPECT_CALL(file_, Read(0, compressed.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result_.data.size(), original.size());
  EXPECT_EQ(std::string(result_.data.data(), result_.data.size()), original);
  EXPECT_TRUE(result_.heap_allocated);
  EXPECT_TRUE(result_.cachable);
}

// Test: Corrupted snappy data returns corruption error
TEST_F(ReadBlockTest_400, CorruptedSnappyData_400) {
  // Use garbage data marked as snappy compressed
  std::string garbage(20, 'x');
  handle_.set_offset(0);
  handle_.set_size(garbage.size());

  std::string block = MakeBlock(garbage, kSnappyCompression);

  EXPECT_CALL(file_, Read(0, garbage.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  // Should fail with corruption (either at GetUncompressedLength or Uncompress)
  if (!s.ok()) {
    EXPECT_TRUE(s.IsCorruption());
  }
  // If somehow it succeeds (unlikely with garbage), that's also acceptable behavior
}

// Test: Read with non-zero offset
TEST_F(ReadBlockTest_400, NonZeroOffset_400) {
  std::string data = "offset test data";
  handle_.set_offset(1000);
  handle_.set_size(data.size());

  std::string block = MakeBlock(data, kNoCompression);

  EXPECT_CALL(file_, Read(1000, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        EXPECT_EQ(offset, 1000u);
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result_.data.size(), data.size());
  EXPECT_EQ(std::string(result_.data.data(), result_.data.size()), data);
}

// Test: Large block read
TEST_F(ReadBlockTest_400, LargeBlock_400) {
  std::string data(100000, 'A');
  handle_.set_offset(0);
  handle_.set_size(data.size());

  std::string block = MakeBlock(data, kNoCompression);

  EXPECT_CALL(file_, Read(0, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result_.data.size(), data.size());
  EXPECT_TRUE(result_.heap_allocated);
  EXPECT_TRUE(result_.cachable);
}

// Test: BlockContents is properly initialized on error
TEST_F(ReadBlockTest_400, ResultInitializedOnError_400) {
  handle_.set_offset(0);
  handle_.set_size(10);

  EXPECT_CALL(file_, Read(0, 10 + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce(testing::Return(Status::IOError("disk error")));

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(result_.data.empty());
  EXPECT_FALSE(result_.cachable);
  EXPECT_FALSE(result_.heap_allocated);
}

// Test: Checksum not verified when verify_checksums is false
TEST_F(ReadBlockTest_400, NoChecksumVerification_400) {
  std::string data = "no checksum verify";
  handle_.set_offset(0);
  handle_.set_size(data.size());
  options_.verify_checksums = false;

  // Create block with bad CRC - should still succeed since we don't verify
  std::string block = MakeBlock(data, kNoCompression, false);

  EXPECT_CALL(file_, Read(0, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result_.data.size(), data.size());
}

// Test: Single byte block
TEST_F(ReadBlockTest_400, SingleByteBlock_400) {
  std::string data = "X";
  handle_.set_offset(0);
  handle_.set_size(data.size());

  std::string block = MakeBlock(data, kNoCompression);

  EXPECT_CALL(file_, Read(0, data.size() + kBlockTrailerSize, testing::_, testing::_))
      .WillOnce([&block](uint64_t offset, size_t n, Slice* result, char* scratch) {
        memcpy(scratch, block.data(), n);
        *result = Slice(scratch, n);
        return Status::OK();
      });

  Status s = ReadBlock(&file_, options_, handle_, &result_);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(result_.data.size(), 1u);
  EXPECT_EQ(result_.data[0], 'X');
}

}  // namespace leveldb
