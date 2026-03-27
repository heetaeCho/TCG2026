// TEST_ID 1544
// File: test_cr2header_int_1544.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <vector>

#include "cr2header_int.hpp"  // Exiv2::Internal::Cr2Header
#include "exiv2/types.hpp"

namespace {

// ---- DataBuf access helpers (works across common Exiv2 DataBuf variants) ----
template <typename T, typename = void>
struct HasSizeMethod : std::false_type {};
template <typename T>
struct HasSizeMethod<T, std::void_t<decltype(std::declval<const T&>().size())>> : std::true_type {};

template <typename T, typename = void>
struct HasSizeMember : std::false_type {};
template <typename T>
struct HasSizeMember<T, std::void_t<decltype(std::declval<const T&>().size_)>> : std::true_type {};

template <typename T, typename = void>
struct HasDataMethod : std::false_type {};
template <typename T>
struct HasDataMethod<T, std::void_t<decltype(std::declval<const T&>().data())>> : std::true_type {};

template <typename T, typename = void>
struct HasDataMember : std::false_type {};
template <typename T>
struct HasDataMember<T, std::void_t<decltype(std::declval<const T&>().pData_)>> : std::true_type {};

template <typename DataBufT>
static size_t DataBufSize(const DataBufT& b) {
  if constexpr (HasSizeMethod<DataBufT>::value) {
    return static_cast<size_t>(b.size());
  } else if constexpr (HasSizeMember<DataBufT>::value) {
    return static_cast<size_t>(b.size_);
  } else {
    // If neither exists, compilation should fail here, signaling an unexpected DataBuf API.
    return 0;
  }
}

template <typename DataBufT>
static const Exiv2::byte* DataBufData(const DataBufT& b) {
  if constexpr (HasDataMethod<DataBufT>::value) {
    return reinterpret_cast<const Exiv2::byte*>(b.data());
  } else if constexpr (HasDataMember<DataBufT>::value) {
    return reinterpret_cast<const Exiv2::byte*>(b.pData_);
  } else {
    return nullptr;
  }
}

static std::vector<Exiv2::byte> MakeValidCr2HeaderBytes(Exiv2::ByteOrder bo) {
  Exiv2::Internal::Cr2Header hdr(bo);
  const auto db = hdr.write();
  const auto* p = DataBufData(db);
  const size_t n = DataBufSize(db);
  EXPECT_NE(p, nullptr);
  EXPECT_GE(n, 16u);
  return std::vector<Exiv2::byte>(p, p + n);
}

class Cr2HeaderTest_1544 : public ::testing::Test {};

}  // namespace

TEST_F(Cr2HeaderTest_1544, ReadSucceedsOnValidHeaderWrittenByWrite_LittleEndian_1544) {
  auto bytes = MakeValidCr2HeaderBytes(Exiv2::littleEndian);

  Exiv2::Internal::Cr2Header hdr(Exiv2::littleEndian);
  EXPECT_TRUE(hdr.read(bytes.data(), bytes.size()));
}

TEST_F(Cr2HeaderTest_1544, ReadSucceedsOnValidHeaderWrittenByWrite_BigEndian_1544) {
  auto bytes = MakeValidCr2HeaderBytes(Exiv2::bigEndian);

  Exiv2::Internal::Cr2Header hdr(Exiv2::bigEndian);
  EXPECT_TRUE(hdr.read(bytes.data(), bytes.size()));
}

TEST_F(Cr2HeaderTest_1544, ReadFailsOnNullData_1544) {
  Exiv2::Internal::Cr2Header hdr(Exiv2::littleEndian);
  EXPECT_FALSE(hdr.read(nullptr, 16));
}

TEST_F(Cr2HeaderTest_1544, ReadFailsWhenSizeIsLessThanMinimumHeader_1544) {
  auto bytes = MakeValidCr2HeaderBytes(Exiv2::littleEndian);
  ASSERT_GE(bytes.size(), 16u);

  Exiv2::Internal::Cr2Header hdr(Exiv2::littleEndian);
  EXPECT_FALSE(hdr.read(bytes.data(), 15));  // boundary: just below 16
}

TEST_F(Cr2HeaderTest_1544, ReadFailsOnInvalidByteOrderMarker_1544) {
  auto bytes = MakeValidCr2HeaderBytes(Exiv2::littleEndian);
  ASSERT_GE(bytes.size(), 16u);

  // Corrupt the byte-order marker (first two bytes) to something not "II" or "MM".
  bytes[0] = static_cast<Exiv2::byte>('I');
  bytes[1] = static_cast<Exiv2::byte>('M');

  Exiv2::Internal::Cr2Header hdr(Exiv2::littleEndian);
  EXPECT_FALSE(hdr.read(bytes.data(), bytes.size()));
}

TEST_F(Cr2HeaderTest_1544, ReadFailsWhenTagDoesNotMatch_1544) {
  auto bytes = MakeValidCr2HeaderBytes(Exiv2::littleEndian);
  ASSERT_GE(bytes.size(), 16u);

  // The tag is stored at bytes[2..3] in the header; flip a bit to force mismatch.
  bytes[2] ^= static_cast<Exiv2::byte>(0x01);

  Exiv2::Internal::Cr2Header hdr(Exiv2::littleEndian);
  EXPECT_FALSE(hdr.read(bytes.data(), bytes.size()));
}

TEST_F(Cr2HeaderTest_1544, ReadFailsWhenSignatureDoesNotMatch_1544) {
  auto bytes = MakeValidCr2HeaderBytes(Exiv2::littleEndian);
  ASSERT_GE(bytes.size(), 16u);

  // Signature is compared against 4 bytes at offset 8..11; corrupt one byte.
  bytes[8] ^= static_cast<Exiv2::byte>(0xFF);

  Exiv2::Internal::Cr2Header hdr(Exiv2::littleEndian);
  EXPECT_FALSE(hdr.read(bytes.data(), bytes.size()));
}

TEST_F(Cr2HeaderTest_1544, ReadFailsIfByteOrderMarkerChangedWithoutReencodingFields_1544) {
  auto bytes = MakeValidCr2HeaderBytes(Exiv2::littleEndian);
  ASSERT_GE(bytes.size(), 16u);

  // Change "II" to "MM" but do not swap tag/offset fields; this should typically break parsing.
  bytes[0] = static_cast<Exiv2::byte>('M');
  bytes[1] = static_cast<Exiv2::byte>('M');

  Exiv2::Internal::Cr2Header hdr(Exiv2::bigEndian);
  EXPECT_FALSE(hdr.read(bytes.data(), bytes.size()));
}