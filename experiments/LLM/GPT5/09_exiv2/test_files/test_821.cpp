// =================================================================================================
//  Unit tests for Exiv2::CommentValue::copy
//  File: ./TestProjects/exiv2/src/value.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <vector>

#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

namespace {

class CommentValueTest_821 : public ::testing::Test {
 protected:
  static std::string MakeAsciiComment(const std::string& text) {
    // 8-byte charset id prefix used by Exiv2 comments (ASCII\0\0\0)
    return std::string("ASCII\0\0\0", 8) + text;
  }

  static std::vector<Exiv2::byte> MakeUnicodeCommentPrefixOnly() {
    const char prefix[8] = {'U', 'N', 'I', 'C', 'O', 'D', 'E', '\0'};
    return std::vector<Exiv2::byte>(reinterpret_cast<const Exiv2::byte*>(prefix),
                                    reinterpret_cast<const Exiv2::byte*>(prefix) + 8);
  }

  static std::vector<Exiv2::byte> MakeUnicodeCommentUcs2LePayload(std::initializer_list<Exiv2::byte> ucs2_le) {
    std::vector<Exiv2::byte> v = MakeUnicodeCommentPrefixOnly();
    v.insert(v.end(), ucs2_le.begin(), ucs2_le.end());
    return v;
  }
};

TEST_F(CommentValueTest_821, CopyReturnsZeroWhenEmpty_821) {
  Exiv2::CommentValue cv;

  std::vector<Exiv2::byte> out(16, static_cast<Exiv2::byte>(0xAA));
  const size_t n = cv.copy(out.data(), Exiv2::littleEndian);

  EXPECT_EQ(0u, n);
}

TEST_F(CommentValueTest_821, CopyCopiesAsciiBytesAndIgnoresByteOrder_821) {
  Exiv2::CommentValue cv;
  const std::string comment = MakeAsciiComment("Hello");

  ASSERT_EQ(0, cv.read(comment));

  std::vector<Exiv2::byte> out_le(comment.size() + 8, 0);
  std::vector<Exiv2::byte> out_be(comment.size() + 8, 0);

  const size_t n_le = cv.copy(out_le.data(), Exiv2::littleEndian);
  const size_t n_be = cv.copy(out_be.data(), Exiv2::bigEndian);

  ASSERT_EQ(comment.size(), n_le);
  ASSERT_EQ(comment.size(), n_be);

  EXPECT_EQ(0, std::memcmp(out_le.data(), comment.data(), comment.size()));
  EXPECT_EQ(0, std::memcmp(out_be.data(), comment.data(), comment.size()));
}

TEST_F(CommentValueTest_821, CopyConvertsUnicodePayloadWhenByteOrderDiffers_821) {
  // Build a UNICODE comment with UCS-2LE payload "Hi" -> 0x48 0x00 0x69 0x00
  const std::vector<Exiv2::byte> in = MakeUnicodeCommentUcs2LePayload({0x48, 0x00, 0x69, 0x00});

  Exiv2::CommentValue cv;
  ASSERT_EQ(0, cv.read(in.data(), in.size(), Exiv2::littleEndian));

  std::vector<Exiv2::byte> out_be(in.size() + 8, 0);
  const size_t n_be = cv.copy(out_be.data(), Exiv2::bigEndian);

  ASSERT_EQ(in.size(), n_be);

  // Prefix should be preserved verbatim
  EXPECT_EQ(0, std::memcmp(out_be.data(), in.data(), 8));

  // Payload should be swapped to UCS-2BE: 0x00 0x48 0x00 0x69
  const Exiv2::byte expected_payload_be[] = {0x00, 0x48, 0x00, 0x69};
  EXPECT_EQ(0, std::memcmp(out_be.data() + 8, expected_payload_be, sizeof(expected_payload_be)));
}

TEST_F(CommentValueTest_821, CopyPreservesUnicodePayloadWhenByteOrderMatches_821) {
  // UNICODE comment with UCS-2LE payload "A" -> 0x41 0x00
  const std::vector<Exiv2::byte> in = MakeUnicodeCommentUcs2LePayload({0x41, 0x00});

  Exiv2::CommentValue cv;
  ASSERT_EQ(0, cv.read(in.data(), in.size(), Exiv2::littleEndian));

  std::vector<Exiv2::byte> out_le(in.size() + 8, 0);
  const size_t n_le = cv.copy(out_le.data(), Exiv2::littleEndian);

  ASSERT_EQ(in.size(), n_le);
  EXPECT_EQ(0, std::memcmp(out_le.data(), in.data(), in.size()));
}

TEST_F(CommentValueTest_821, CopyReturnsPrefixSizeForUnicodeWithEmptyPayload_821) {
  const std::vector<Exiv2::byte> in = MakeUnicodeCommentPrefixOnly();

  Exiv2::CommentValue cv;
  ASSERT_EQ(0, cv.read(in.data(), in.size(), Exiv2::littleEndian));

  std::vector<Exiv2::byte> out(in.size() + 8, 0);
  const size_t n = cv.copy(out.data(), Exiv2::bigEndian);

  ASSERT_EQ(8u, n);
  EXPECT_EQ(0, std::memcmp(out.data(), in.data(), 8));
}

}  // namespace