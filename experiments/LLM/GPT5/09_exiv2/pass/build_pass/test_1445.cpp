// TEST_ID 1445
// File: test_olympus2mnheader_read_1445.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#if __has_include("makernote_int.hpp")
#include "makernote_int.hpp"
#elif __has_include("exiv2/makernote_int.hpp")
#include "exiv2/makernote_int.hpp"
#else
#include <exiv2/makernote_int.hpp>
#endif

#if __has_include("types.hpp")
#include "types.hpp"
#elif __has_include("exiv2/types.hpp")
#include "exiv2/types.hpp"
#else
#include <exiv2/types.hpp>
#endif

namespace {

using Exiv2::ByteOrder;
using Exiv2::byte;

class Olympus2MnHeaderTest_1445 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeBufferOfSize(std::size_t n, byte fill = static_cast<byte>(0x00)) {
    return std::vector<byte>(n, fill);
  }

  // Common Olympus II maker-note header signature used by Exiv2 for the
  // "Olympus2" header check (first 10 bytes are compared in the implementation).
  static constexpr std::array<byte, 10> kExpectedSignature10 = {
      static_cast<byte>('O'), static_cast<byte>('L'), static_cast<byte>('Y'), static_cast<byte>('M'),
      static_cast<byte>('P'), static_cast<byte>('U'), static_cast<byte>('S'), static_cast<byte>(0x00),
      static_cast<byte>('I'), static_cast<byte>('I'),
  };

  static void WriteExpectedSignature10(std::vector<byte>& buf) {
    ASSERT_GE(buf.size(), kExpectedSignature10.size());
    std::copy(kExpectedSignature10.begin(), kExpectedSignature10.end(), buf.begin());
  }

  static ByteOrder AnyByteOrder() {
    // The provided implementation does not depend on byte order for the observable return value,
    // but we pass a valid enumerator.
    return Exiv2::littleEndian;
  }
};

TEST_F(Olympus2MnHeaderTest_1445, ReadReturnsFalseWhenDataIsNull_1445) {
  Exiv2::Internal::Olympus2MnHeader header;

  const bool ok = header.read(nullptr, /*size=*/100, AnyByteOrder());
  EXPECT_FALSE(ok);
}

TEST_F(Olympus2MnHeaderTest_1445, ReadReturnsFalseWhenSizeIsZeroEvenIfPointerNonNull_1445) {
  Exiv2::Internal::Olympus2MnHeader header;

  byte oneByte = static_cast<byte>(0xAB);
  const bool ok = header.read(&oneByte, /*size=*/0, AnyByteOrder());
  EXPECT_FALSE(ok);
}

TEST_F(Olympus2MnHeaderTest_1445, ReadReturnsFalseWhenSizeSmallerThanSignatureSize_1445) {
  Exiv2::Internal::Olympus2MnHeader header;

  const std::size_t sigSize = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();
  ASSERT_GT(sigSize, 0u);

  std::vector<byte> buf = MakeBufferOfSize(sigSize, static_cast<byte>(0x00));
  // Provide one less than required.
  const bool ok = header.read(buf.data(), sigSize - 1, AnyByteOrder());
  EXPECT_FALSE(ok);
}

TEST_F(Olympus2MnHeaderTest_1445, ReadReturnsFalseWhenSignatureDoesNotMatch_1445) {
  Exiv2::Internal::Olympus2MnHeader header;

  const std::size_t sigSize = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();
  ASSERT_GT(sigSize, 0u);

  std::vector<byte> buf = MakeBufferOfSize(sigSize, static_cast<byte>(0xFF));  // very likely mismatch
  const bool ok = header.read(buf.data(), buf.size(), AnyByteOrder());
  EXPECT_FALSE(ok);
}

TEST_F(Olympus2MnHeaderTest_1445, ReadReturnsTrueWhenSignatureMatchesAtStart_1445) {
  Exiv2::Internal::Olympus2MnHeader header;

  const std::size_t sigSize = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();
  ASSERT_GE(sigSize, kExpectedSignature10.size());

  std::vector<byte> buf = MakeBufferOfSize(sigSize, static_cast<byte>(0x00));
  WriteExpectedSignature10(buf);

  const bool ok = header.read(buf.data(), buf.size(), AnyByteOrder());
  EXPECT_TRUE(ok);
}

TEST_F(Olympus2MnHeaderTest_1445, ReadReturnsTrueWhenSignatureMatchesAndInputHasExtraTrailingBytes_1445) {
  Exiv2::Internal::Olympus2MnHeader header;

  const std::size_t sigSize = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();
  ASSERT_GE(sigSize, kExpectedSignature10.size());

  std::vector<byte> buf = MakeBufferOfSize(sigSize + 8, static_cast<byte>(0x7E));
  WriteExpectedSignature10(buf);

  const bool ok = header.read(buf.data(), buf.size(), AnyByteOrder());
  EXPECT_TRUE(ok);
}

TEST_F(Olympus2MnHeaderTest_1445, ReadReturnsFalseWhenOneByteInSignatureIsModified_1445) {
  Exiv2::Internal::Olympus2MnHeader header;

  const std::size_t sigSize = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature();
  ASSERT_GE(sigSize, kExpectedSignature10.size());

  std::vector<byte> buf = MakeBufferOfSize(sigSize, static_cast<byte>(0x00));
  WriteExpectedSignature10(buf);

  // Flip one byte within the compared prefix (first 10 bytes).
  buf[2] = static_cast<byte>(buf[2] ^ static_cast<byte>(0x01));

  const bool ok = header.read(buf.data(), buf.size(), AnyByteOrder());
  EXPECT_FALSE(ok);
}

}  // namespace