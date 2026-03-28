// File: util/get_varint32_test.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <string>

#include "leveldb/slice.h"   // Slice interface
#include "util/coding.h"     // Declares GetVarint32

using leveldb::Slice;
using leveldb::GetVarint32;

class GetVarint32Test_447 : public ::testing::Test {
protected:
  // Builds a std::string from raw bytes.
  static std::string Bytes(std::initializer_list<unsigned char> bytes) {
    return std::string(reinterpret_cast<const char*>(bytes.begin()), bytes.size());
  }
};

// Normal operation: single-byte value 0
TEST_F(GetVarint32Test_447, ParsesZeroSingleByte_447) {
  const std::string buf = GetVarint32Test_447::Bytes({0x00});
  Slice input(buf.data(), buf.size());
  uint32_t value = 12345; // will be overwritten

  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(value, 0u);

  // Slice advanced to end (no remaining bytes)
  EXPECT_EQ(input.size(), 0u);
}

// Normal operation: single-byte value 127 (0x7F)
TEST_F(GetVarint32Test_447, Parses127SingleByte_447) {
  const std::string buf = GetVarint32Test_447::Bytes({0x7F});
  Slice input(buf.data(), buf.size());
  uint32_t value = 0;

  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(value, 127u);
  EXPECT_EQ(input.size(), 0u);
}

// Normal operation: multi-byte value 128 (encoded as 0x80 0x01)
TEST_F(GetVarint32Test_447, Parses128MultiByte_447) {
  const std::string buf = GetVarint32Test_447::Bytes({0x80, 0x01});
  Slice input(buf.data(), buf.size());
  uint32_t value = 0;

  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(value, 128u);
  EXPECT_EQ(input.size(), 0u);
}

// Normal operation + remainder verification:
// parse first value and ensure Slice now points at the remaining bytes.
TEST_F(GetVarint32Test_447, AdvancesInputAndLeavesRemainder_447) {
  // 300 encodes as 0xAC 0x02; then raw tail bytes 0xDE 0xAD remain
  const std::string buf = GetVarint32Test_447::Bytes({0xAC, 0x02, 0xDE, 0xAD});
  Slice input(buf.data(), buf.size());
  const char* original_data = input.data();
  uint32_t value = 0;

  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(value, 300u);

  // After consuming 2 bytes, 2 bytes should remain.
  EXPECT_EQ(input.size(), 2u);
  ASSERT_EQ(static_cast<size_t>(input.data() - original_data), 2u);
  // Remaining content matches the tail
  EXPECT_EQ(std::string(input.data(), input.size()),
            std::string("\xDE\xAD", 2));
}

// Boundary condition: maximum uint32_t (4294967295)
// Encoded as five bytes: 0xFF 0xFF 0xFF 0xFF 0x0F
TEST_F(GetVarint32Test_447, ParsesMaxUint32_447) {
  const std::string buf =
      GetVarint32Test_447::Bytes({0xFF, 0xFF, 0xFF, 0xFF, 0x0F});
  Slice input(buf.data(), buf.size());
  uint32_t value = 0;

  ASSERT_TRUE(GetVarint32(&input, &value));
  EXPECT_EQ(value, 0xFFFFFFFFu);
  EXPECT_EQ(input.size(), 0u);
}

// Error case: empty input should fail and not advance the Slice
TEST_F(GetVarint32Test_447, EmptyInputReturnsFalseAndDoesNotAdvance_447) {
  const std::string buf;  // empty
  Slice input(buf.data(), buf.size());
  const char* before_data = input.data();
  const size_t before_size = input.size();
  uint32_t value = 0;

  EXPECT_FALSE(GetVarint32(&input, &value));
  EXPECT_EQ(input.data(), before_data);
  EXPECT_EQ(input.size(), before_size);
}

// Error case: truncated varint (continuation bit set, no following byte)
// Should return false and leave Slice unchanged.
TEST_F(GetVarint32Test_447, TruncatedVarintReturnsFalseAndDoesNotAdvance_447) {
  const std::string buf = GetVarint32Test_447::Bytes({0x80}); // incomplete
  Slice input(buf.data(), buf.size());
  const char* before_data = input.data();
  const size_t before_size = input.size();
  uint32_t value = 0;

  EXPECT_FALSE(GetVarint32(&input, &value));
  EXPECT_EQ(input.data(), before_data);
  EXPECT_EQ(input.size(), before_size);
}
