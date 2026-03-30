// File: test_nikon2_mn_header_1463.cpp
// Unit tests for Exiv2::Internal::Nikon2MnHeader::read
//
// Constraints respected:
// - Treat implementation as black box: only observe bool return value
// - No access to private state (buf_, start_, signature_, sizeOfSignature())
// - Boundary + error cases + normal operation covered

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "makernote_int.hpp"  // Exiv2::Internal::Nikon2MnHeader
#include "types.hpp"          // Exiv2::byte, Exiv2::ByteOrder (path may vary in your tree)

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;

constexpr std::array<byte, 6> kNikonSignature6 = {
    static_cast<byte>('N'),
    static_cast<byte>('i'),
    static_cast<byte>('k'),
    static_cast<byte>('o'),
    static_cast<byte>('n'),
    static_cast<byte>(0x00),
};

std::vector<byte> MakeBufferWithGoodPrefix(std::size_t n) {
  std::vector<byte> buf(n, static_cast<byte>(0xAB));
  if (buf.size() >= kNikonSignature6.size()) {
    for (std::size_t i = 0; i < kNikonSignature6.size(); ++i) buf[i] = kNikonSignature6[i];
  }
  return buf;
}

std::vector<byte> MakeBufferWithBadPrefix(std::size_t n) {
  auto buf = MakeBufferWithGoodPrefix(n);
  if (!buf.empty()) buf[0] = static_cast<byte>('X');  // break signature
  return buf;
}

}  // namespace

namespace Exiv2::Internal {

class Nikon2MnHeaderTest_1463 : public ::testing::Test {
 protected:
  Nikon2MnHeader header_;
};

TEST_F(Nikon2MnHeaderTest_1463, ReadReturnsFalseWhenDataIsNull_1463) {
  EXPECT_FALSE(header_.read(nullptr, 0u, ByteOrder::littleEndian));
  EXPECT_FALSE(header_.read(nullptr, 100u, ByteOrder::bigEndian));
}

TEST_F(Nikon2MnHeaderTest_1463, ReadReturnsFalseWhenSignatureDoesNotMatch_1463) {
  // Use a sufficiently large size to avoid depending on the internal sizeOfSignature().
  const auto buf = MakeBufferWithBadPrefix(64);
  EXPECT_FALSE(header_.read(buf.data(), buf.size(), ByteOrder::littleEndian));
  EXPECT_FALSE(header_.read(buf.data(), buf.size(), ByteOrder::bigEndian));
}

TEST_F(Nikon2MnHeaderTest_1463, ReadFindsMinimumAcceptableSizeAndRejectsSmallerSizes_1463) {
  // Black-box boundary probing: find the smallest size that returns true for a buffer
  // with the expected 6-byte signature prefix, then assert all smaller sizes fail.
  const auto full = MakeBufferWithGoodPrefix(128);

  std::size_t first_success = 0;
  bool found = false;

  for (std::size_t sz = 0; sz <= full.size(); ++sz) {
    Nikon2MnHeader h;
    if (h.read(full.data(), sz, ByteOrder::littleEndian)) {
      first_success = sz;
      found = true;
      break;
    }
  }

  ASSERT_TRUE(found) << "Could not find any size where read() succeeds; "
                        "the expected signature prefix may differ.";

  for (std::size_t sz = 0; sz < first_success; ++sz) {
    Nikon2MnHeader h;
    EXPECT_FALSE(h.read(full.data(), sz, ByteOrder::littleEndian)) << "size=" << sz;
  }

  // And the boundary itself should succeed (sanity check).
  {
    Nikon2MnHeader h;
    EXPECT_TRUE(h.read(full.data(), first_success, ByteOrder::littleEndian));
  }
}

TEST_F(Nikon2MnHeaderTest_1463, ReadSucceedsForLargeEnoughBufferWithGoodSignature_1463) {
  const auto buf = MakeBufferWithGoodPrefix(256);
  EXPECT_TRUE(header_.read(buf.data(), buf.size(), ByteOrder::littleEndian));
}

TEST_F(Nikon2MnHeaderTest_1463, ReadSuccessDoesNotDependOnByteOrderParameter_1463) {
  const auto buf = MakeBufferWithGoodPrefix(256);

  Nikon2MnHeader h1;
  Nikon2MnHeader h2;

  EXPECT_TRUE(h1.read(buf.data(), buf.size(), ByteOrder::littleEndian));
  EXPECT_TRUE(h2.read(buf.data(), buf.size(), ByteOrder::bigEndian));
}

}  // namespace Exiv2::Internal