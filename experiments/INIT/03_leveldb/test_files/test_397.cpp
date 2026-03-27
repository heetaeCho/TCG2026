// File: block_handle_decodefrom_test_397.cc
#include "table/format.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

#include <gtest/gtest.h>
#include <string>

using leveldb::BlockHandle;
using leveldb::Slice;
using leveldb::Status;

class BlockHandleDecodeFromTest_397 : public ::testing::Test {};

// Normal operation: decoding a handle previously encoded via the public API succeeds.
TEST_F(BlockHandleDecodeFromTest_397, DecodeFrom_SucceedsOnEncodedHandle_397) {
  BlockHandle src;
  src.set_offset(12345u);
  src.set_size(67890u);

  std::string enc;
  src.EncodeTo(&enc);

  Slice in(enc);
  BlockHandle dst;
  Status st = dst.DecodeFrom(&in);

  EXPECT_TRUE(st.ok());
  // Decoding should consume exactly the bytes that represent the handle.
  EXPECT_EQ(in.size(), 0u);
}

// Normal operation + observable side effect: bytes after a valid handle remain in the Slice.
TEST_F(BlockHandleDecodeFromTest_397, DecodeFrom_AdvancesSliceAndLeavesRemainder_397) {
  BlockHandle src;
  src.set_offset(11u);
  src.set_size(22u);

  std::string enc;
  src.EncodeTo(&enc);

  const std::string trailer = "XYZ";
  std::string with_trailer = enc + trailer;

  Slice in(with_trailer);
  BlockHandle dst;
  Status st = dst.DecodeFrom(&in);

  ASSERT_TRUE(st.ok());
  // After consuming the encoded handle, the remainder should be exactly the trailer.
  ASSERT_EQ(in.size(), trailer.size());
  EXPECT_EQ(std::string(in.data(), in.size()), trailer);
}

// Error case: empty input cannot decode a block handle (should report Corruption).
TEST_F(BlockHandleDecodeFromTest_397, DecodeFrom_FailsOnEmptyInput_397) {
  Slice in("");  // no bytes at all
  BlockHandle dst;
  Status st = dst.DecodeFrom(&in);

  EXPECT_FALSE(st.ok());
  EXPECT_TRUE(st.IsCorruption());
}

// Error case: truncated input (missing part of the second varint) should report Corruption.
// We generate a valid encoding via EncodeTo and then drop the last byte to simulate truncation.
TEST_F(BlockHandleDecodeFromTest_397, DecodeFrom_FailsOnTruncatedSecondVarint_397) {
  BlockHandle src;
  // Choose values that are very likely to produce multi-byte varints for the size,
  // so dropping the last byte creates an incomplete second varint.
  src.set_offset(1u);
  src.set_size(300u);  // >=128 typically requires multi-byte varint encoding

  std::string enc;
  src.EncodeTo(&enc);

  ASSERT_GT(enc.size(), 1u) << "Encoded handle should have more than one byte to allow truncation";

  std::string truncated = enc.substr(0, enc.size() - 1);  // drop the final byte
  Slice in(truncated);
  BlockHandle dst;
  Status st = dst.DecodeFrom(&in);

  EXPECT_FALSE(st.ok());
  EXPECT_TRUE(st.IsCorruption());
}
