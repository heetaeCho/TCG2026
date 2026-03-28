// TEST_ID 805
// Unit tests for Exiv2::StringValueBase::copy (black-box via public/derived public interfaces)

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// Exiv2 public headers
#include <exiv2/value.hpp>

namespace {

// Helper to create a byte buffer filled with a sentinel value.
static std::vector<Exiv2::byte> MakeBuf(std::size_t n, Exiv2::byte fill) {
  return std::vector<Exiv2::byte>(n, fill);
}

class StringValueBaseTest_805 : public ::testing::Test {};

TEST_F(StringValueBaseTest_805, EmptyValueReturnsZeroAndDoesNotModifyBuffer_805) {
  // Use a concrete string-based value type (inherits StringValueBase).
  Exiv2::StringValue v;  // expected to be empty by default

  auto buf = MakeBuf(16, static_cast<Exiv2::byte>(0xAA));
  const auto before = buf;

  const std::size_t copied = v.copy(buf.data(), Exiv2::littleEndian);

  EXPECT_EQ(copied, 0u);
  EXPECT_EQ(buf, before) << "Buffer should remain unchanged when value is empty";
}

TEST_F(StringValueBaseTest_805, NonEmptyValueCopiesAllBytesAndReturnsSize_805) {
  const std::string s = "abc";
  Exiv2::StringValue v(s);

  auto buf = MakeBuf(10, static_cast<Exiv2::byte>(0xCC));
  const std::size_t copied = v.copy(buf.data(), Exiv2::bigEndian);

  ASSERT_EQ(copied, s.size());

  EXPECT_EQ(buf[0], static_cast<Exiv2::byte>('a'));
  EXPECT_EQ(buf[1], static_cast<Exiv2::byte>('b'));
  EXPECT_EQ(buf[2], static_cast<Exiv2::byte>('c'));

  // Ensure bytes beyond the copied range are not altered.
  for (std::size_t i = s.size(); i < buf.size(); ++i) {
    EXPECT_EQ(buf[i], static_cast<Exiv2::byte>(0xCC)) << "Index " << i;
  }
}

TEST_F(StringValueBaseTest_805, CopyDoesNotWriteNullTerminator_805) {
  const std::string s = "hi";
  Exiv2::StringValue v(s);

  // Buffer is larger than string; last byte should remain sentinel, not '\0'.
  auto buf = MakeBuf(3, static_cast<Exiv2::byte>('X'));

  const std::size_t copied = v.copy(buf.data(), Exiv2::littleEndian);

  ASSERT_EQ(copied, s.size());
  EXPECT_EQ(buf[0], static_cast<Exiv2::byte>('h'));
  EXPECT_EQ(buf[1], static_cast<Exiv2::byte>('i'));
  EXPECT_EQ(buf[2], static_cast<Exiv2::byte>('X')) << "No null-terminator should be appended";
}

TEST_F(StringValueBaseTest_805, ByteOrderParameterDoesNotAffectCopiedBytes_805) {
  const std::string s = "Hello, Exiv2!";
  Exiv2::StringValue v(s);

  auto buf_le = MakeBuf(s.size() + 5, static_cast<Exiv2::byte>(0x11));
  auto buf_be = MakeBuf(s.size() + 5, static_cast<Exiv2::byte>(0x22));

  const std::size_t copied_le = v.copy(buf_le.data(), Exiv2::littleEndian);
  const std::size_t copied_be = v.copy(buf_be.data(), Exiv2::bigEndian);

  ASSERT_EQ(copied_le, s.size());
  ASSERT_EQ(copied_be, s.size());

  // Compare the copied ranges are identical (independent of byte order).
  for (std::size_t i = 0; i < s.size(); ++i) {
    EXPECT_EQ(buf_le[i], buf_be[i]) << "Index " << i;
    EXPECT_EQ(buf_le[i], static_cast<Exiv2::byte>(s[i])) << "Index " << i;
  }

  // And ensure trailing sentinel bytes remain untouched.
  for (std::size_t i = s.size(); i < buf_le.size(); ++i) {
    EXPECT_EQ(buf_le[i], static_cast<Exiv2::byte>(0x11)) << "Index " << i;
    EXPECT_EQ(buf_be[i], static_cast<Exiv2::byte>(0x22)) << "Index " << i;
  }
}

}  // namespace