// InternalKey_DecodeFrom_test.cc
#include "db/dbformat.h"
#include "leveldb/slice.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>

namespace {

using leveldb::InternalKey;
using leveldb::Slice;

class InternalKeyDecodeFromTest_50 : public ::testing::Test {
protected:
  InternalKey key_;
};

TEST_F(InternalKeyDecodeFromTest_50, EmptySliceReturnsFalse_50) {
  Slice empty;  // default-constructed empty slice
  EXPECT_FALSE(key_.DecodeFrom(empty));
}

TEST_F(InternalKeyDecodeFromTest_50, NonEmptyAsciiReturnsTrue_50) {
  std::string payload = "hello";
  Slice s(payload);
  EXPECT_TRUE(key_.DecodeFrom(s));
}

TEST_F(InternalKeyDecodeFromTest_50, BinaryDataWithNullBytesReturnsTrue_50) {
  const char data_with_nulls[] = {'a', '\0', 'b', '\0', 'c'};
  Slice s(data_with_nulls, sizeof(data_with_nulls));
  EXPECT_TRUE(key_.DecodeFrom(s));
}

TEST_F(InternalKeyDecodeFromTest_50, LargeInputReturnsTrue_50) {
  // Create a large buffer (1 MB) filled with non-zero bytes.
  const size_t kSize = 1 << 20; // 1,048,576 bytes
  std::vector<char> big(kSize, 'X');
  Slice s(big.data(), big.size());
  EXPECT_TRUE(key_.DecodeFrom(s));
}

TEST_F(InternalKeyDecodeFromTest_50, MultipleCallsReflectCurrentInput_50) {
  // First call with non-empty -> true
  std::string first = "data";
  EXPECT_TRUE(key_.DecodeFrom(Slice(first)));

  // Second call with empty -> false (observable result depends only on current input)
  Slice empty;
  EXPECT_FALSE(key_.DecodeFrom(empty));

  // Third call with non-empty again -> true
  const char buf[] = {1,2,3};
  EXPECT_TRUE(key_.DecodeFrom(Slice(buf, sizeof(buf))));
}

}  // namespace
