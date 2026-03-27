// File: test_pngimage_textToDataBuf_970.cpp
//
// Unit tests for Exiv2::tEXtToDataBuf (internal-linkage helper in pngimage.cpp)
//
// NOTE:
// - tEXtToDataBuf is declared "static" inside pngimage.cpp, so it has internal linkage.
// - To test it via its provided signature/observable effects, we include the .cpp directly,
//   making the function visible within this test translation unit.
//
// These tests treat the function as a black box: they verify observable outcomes via the
// DataBuf public interface (size(), c_data()) and the return value.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <SeeTwoStrings>

// Exiv2 core types (DataBuf, byte, etc.)
#include "exiv2/types.hpp"

// Include the implementation unit to access the internal-linkage function.
#include "pngimage.cpp"

namespace {

// Helper: build a byte buffer from std::string (no embedded NUL assumptions beyond string length)
static inline const Exiv2::byte* asBytes(const std::string& s) {
  return reinterpret_cast<const Exiv2::byte*>(s.data());
}

static inline bool call_tEXtToDataBuf(const std::string& s, Exiv2::DataBuf& out) {
  return Exiv2::tEXtToDataBuf(asBytes(s), s.size(), out);
}

class PngImage_tEXtToDataBufTest_970 : public ::testing::Test {
 protected:
  Exiv2::DataBuf buf_;
};

TEST_F(PngImage_tEXtToDataBufTest_970, EmptyInputProducesEmptyBuffer_970) {
  const std::string in;
  const bool ok = call_tEXtToDataBuf(in, buf_);

  EXPECT_TRUE(ok);
  EXPECT_EQ(buf_.size(), 0u);
}

TEST_F(PngImage_tEXtToDataBufTest_970, NoHexCharactersProducesEmptyBuffer_970) {
  const std::string in = "this has no hex digits: gGxX!? \r\t";
  const bool ok = call_tEXtToDataBuf(in, buf_);

  EXPECT_TRUE(ok);
  EXPECT_EQ(buf_.size(), 0u);
}

TEST_F(PngImage_tEXtToDataBufTest_970, PacksPairsOfHexDigitsIntoBytes_970) {
  // Observable behavior: hex digits are converted into bytes in pairs.
  const std::string in = "0A1f";
  const bool ok = call_tEXtToDataBuf(in, buf_);

  ASSERT_TRUE(ok);
  ASSERT_EQ(buf_.size(), 2u);

  const Exiv2::byte* p = buf_.c_data(0);
  EXPECT_EQ(p[0], static_cast<Exiv2::byte>(0x0A));
  EXPECT_EQ(p[1], static_cast<Exiv2::byte>(0x1F));
}

TEST_F(PngImage_tEXtToDataBufTest_970, AcceptsMixedCaseHexDigits_970) {
  const std::string in = "aBcD";
  const bool ok = call_tEXtToDataBuf(in, buf_);

  ASSERT_TRUE(ok);
  ASSERT_EQ(buf_.size(), 2u);

  const Exiv2::byte* p = buf_.c_data(0);
  EXPECT_EQ(p[0], static_cast<Exiv2::byte>(0xAB));
  EXPECT_EQ(p[1], static_cast<Exiv2::byte>(0xCD));
}

TEST_F(PngImage_tEXtToDataBufTest_970, IgnoresNonHexSeparatorsBetweenDigits_970) {
  // Observable behavior: non-hex characters are ignored; only hex digits are packed.
  const std::string in = "A B\tC\nD-1_2";
  // Hex digits (in order): A B C D 1 2  => bytes: AB CD 12
  const bool ok = call_tEXtToDataBuf(in, buf_);

  ASSERT_TRUE(ok);
  ASSERT_EQ(buf_.size(), 3u);

  const Exiv2::byte* p = buf_.c_data(0);
  EXPECT_EQ(p[0], static_cast<Exiv2::byte>(0xAB));
  EXPECT_EQ(p[1], static_cast<Exiv2::byte>(0xCD));
  EXPECT_EQ(p[2], static_cast<Exiv2::byte>(0x12));
}

TEST_F(PngImage_tEXtToDataBufTest_970, SkipsUpToThreeNewlinesBeforeProcessingPayload_970) {
  // Construct input with hex digits before and after the 3rd newline.
  // After the third '\n', the remaining digits are "34" -> one byte 0x34.
  const std::string in = "0\n1\n2\n34";
  const bool ok = call_tEXtToDataBuf(in, buf_);

  ASSERT_TRUE(ok);
  ASSERT_EQ(buf_.size(), 1u);

  const Exiv2::byte* p = buf_.c_data(0);
  EXPECT_EQ(p[0], static_cast<Exiv2::byte>(0x34));
}

TEST_F(PngImage_tEXtToDataBufTest_970, FewerThanThreeNewlinesMayConsumeAllInput_970) {
  // Only newlines and no hex digits -> should still succeed and produce empty buffer.
  const std::string in = "\n\n";
  const bool ok = call_tEXtToDataBuf(in, buf_);

  EXPECT_TRUE(ok);
  EXPECT_EQ(buf_.size(), 0u);
}

TEST_F(PngImage_tEXtToDataBufTest_970, OddNumberOfHexDigitsAllocatesCeilingHalfBytes_970) {
  // With 3 hex digits total, the output buffer size should be 2 bytes (ceil(3/2)).
  // We only assert the fully formed first byte, and do not assume anything about the
  // trailing (incomplete) last byte's content besides buffer sizing and no crash.
  const std::string in = "ABC";
  const bool ok = call_tEXtToDataBuf(in, buf_);

  ASSERT_TRUE(ok);
  ASSERT_EQ(buf_.size(), 2u);

  const Exiv2::byte* p = buf_.c_data(0);
  EXPECT_EQ(p[0], static_cast<Exiv2::byte>(0xAB));
}

TEST_F(PngImage_tEXtToDataBufTest_970, ReuseDataBufOverwritesSizeForNewInput_970) {
  // First call produces non-empty buffer
  {
    const std::string in1 = "0011";
    const bool ok1 = call_tEXtToDataBuf(in1, buf_);
    ASSERT_TRUE(ok1);
    ASSERT_EQ(buf_.size(), 2u);
    const Exiv2::byte* p1 = buf_.c_data(0);
    EXPECT_EQ(p1[0], static_cast<Exiv2::byte>(0x00));
    EXPECT_EQ(p1[1], static_cast<Exiv2::byte>(0x11));
  }

  // Second call produces empty buffer, verify observable size change
  {
    const std::string in2 = "no hex here";
    const bool ok2 = call_tEXtToDataBuf(in2, buf_);
    ASSERT_TRUE(ok2);
    EXPECT_EQ(buf_.size(), 0u);
  }
}

TEST_F(PngImage_tEXtToDataBufTest_970, HandlesEmbeddedNulBytesInInputLengthBasedProcessing_970) {
  // Input includes '\0' inside; processing should be length-based (not C-string terminated).
  // Hex digits present: 'A' 'B' 'C' 'D' => 0xAB 0xCD
  std::string in;
  in.push_back('A');
  in.push_back('B');
  in.push_back('\0');
  in.push_back('C');
  in.push_back('D');

  const bool ok = call_tEXtToDataBuf(in, buf_);

  ASSERT_TRUE(ok);
  ASSERT_EQ(buf_.size(), 2u);
  const Exiv2::byte* p = buf_.c_data(0);
  EXPECT_EQ(p[0], static_cast<Exiv2::byte>(0xAB));
  EXPECT_EQ(p[1], static_cast<Exiv2::byte>(0xCD));
}

}  // namespace