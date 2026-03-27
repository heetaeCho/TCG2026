// File: test_sonymn_int_sonyTagDecipher_1625.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>
#include <vector>

#include <exiv2/types.hpp>

// Forward declarations (treat implementation as black-box; avoid re-implementing logic).
namespace Exiv2 {
namespace Internal {
DataBuf sonyTagDecipher(uint16_t tag, const byte* bytes, size_t size, TiffComponent* object);
DataBuf sonyTagCipher(uint16_t tag, const byte* bytes, size_t size, TiffComponent* object, bool decode);
}  // namespace Internal
}  // namespace Exiv2

namespace {

// --- Minimal, robust accessors for Exiv2::DataBuf across potential API variants ---
template <typename T>
auto DataBufSizeImpl(const T& b, int) -> decltype(b.size(), size_t{}) {
  return static_cast<size_t>(b.size());
}
template <typename T>
auto DataBufSizeImpl(const T& b, long) -> decltype(b.size_, size_t{}) {
  return static_cast<size_t>(b.size_);
}
inline size_t DataBufSize(const Exiv2::DataBuf& b) {
  return DataBufSizeImpl(b, 0);
}

template <typename T>
auto DataBufDataImpl(const T& b, int) -> decltype(b.data(), (const Exiv2::byte*)nullptr) {
  return reinterpret_cast<const Exiv2::byte*>(b.data());
}
template <typename T>
auto DataBufDataImpl(const T& b, long) -> decltype(b.pData_, (const Exiv2::byte*)nullptr) {
  return reinterpret_cast<const Exiv2::byte*>(b.pData_);
}
inline const Exiv2::byte* DataBufData(const Exiv2::DataBuf& b) {
  return DataBufDataImpl(b, 0);
}

// Compares sonyTagDecipher(...) against sonyTagCipher(..., /*decode=*/true) for:
// - same "throws vs not" behavior
// - if both succeed: same output size and content bytes (when accessible)
static void ExpectSameAsCipherDecodeTrue(uint16_t tag,
                                        const Exiv2::byte* bytes,
                                        size_t size,
                                        Exiv2::Internal::TiffComponent* object) {
  bool decipher_threw = false;
  bool cipher_threw = false;

  Exiv2::DataBuf out_decipher;
  Exiv2::DataBuf out_cipher;

  try {
    out_decipher = Exiv2::Internal::sonyTagDecipher(tag, bytes, size, object);
  } catch (...) {
    decipher_threw = true;
  }

  try {
    out_cipher = Exiv2::Internal::sonyTagCipher(tag, bytes, size, object, true);
  } catch (...) {
    cipher_threw = true;
  }

  ASSERT_EQ(decipher_threw, cipher_threw) << "Decipher and Cipher(decode=true) differed in throw behavior";

  if (decipher_threw) {
    // Both threw: consistent behavior is all we can observe safely.
    return;
  }

  const size_t sz_d = DataBufSize(out_decipher);
  const size_t sz_c = DataBufSize(out_cipher);
  ASSERT_EQ(sz_d, sz_c) << "Output sizes differ";

  if (sz_d == 0) return;

  const Exiv2::byte* p_d = DataBufData(out_decipher);
  const Exiv2::byte* p_c = DataBufData(out_cipher);

  // If pointers are not accessible (unexpected), at least validate size equality already done.
  ASSERT_NE(p_d, nullptr);
  ASSERT_NE(p_c, nullptr);

  EXPECT_EQ(0, std::memcmp(p_d, p_c, sz_d)) << "Output contents differ";
}

class SonyTagDecipherTest_1625 : public ::testing::Test {};

}  // namespace

TEST_F(SonyTagDecipherTest_1625, MatchesCipherForEmptyInput_1625) {
  const uint16_t tag = 0;
  const Exiv2::byte* bytes = nullptr;
  const size_t size = 0;

  ExpectSameAsCipherDecodeTrue(tag, bytes, size, nullptr);
}

TEST_F(SonyTagDecipherTest_1625, MatchesCipherForSmallInputVariousTags_1625) {
  const std::vector<Exiv2::byte> buf = {0x00, 0x01, 0x7f, 0x80, 0xff};

  for (uint16_t tag : {static_cast<uint16_t>(0x0000),
                       static_cast<uint16_t>(0x0001),
                       static_cast<uint16_t>(0x00ff),
                       static_cast<uint16_t>(0x1234),
                       static_cast<uint16_t>(0xffff)}) {
    ExpectSameAsCipherDecodeTrue(tag, buf.data(), buf.size(), nullptr);
  }
}

TEST_F(SonyTagDecipherTest_1625, MatchesCipherForLargerBuffer_1625) {
  std::vector<Exiv2::byte> buf(1024);
  for (size_t i = 0; i < buf.size(); ++i) {
    buf[i] = static_cast<Exiv2::byte>(i & 0xff);
  }

  ExpectSameAsCipherDecodeTrue(static_cast<uint16_t>(0x00a1), buf.data(), buf.size(), nullptr);
}

TEST_F(SonyTagDecipherTest_1625, DoesNotModifyInputBuffer_1625) {
  std::vector<Exiv2::byte> buf = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60};
  const std::vector<Exiv2::byte> original = buf;

  // Call both (black-box). We only assert the input buffer remains unchanged.
  // (If either throws, input should still not be modified.)
  try {
    (void)Exiv2::Internal::sonyTagDecipher(static_cast<uint16_t>(0x0002), buf.data(), buf.size(), nullptr);
  } catch (...) {
  }
  EXPECT_EQ(buf, original);

  try {
    (void)Exiv2::Internal::sonyTagCipher(static_cast<uint16_t>(0x0002), buf.data(), buf.size(), nullptr, true);
  } catch (...) {
  }
  EXPECT_EQ(buf, original);
}

TEST_F(SonyTagDecipherTest_1625, HandlesNullptrBytesWithZeroSize_1625) {
  // Boundary: nullptr bytes is typically only safe with size==0.
  ExpectSameAsCipherDecodeTrue(static_cast<uint16_t>(0x00ff), nullptr, 0, nullptr);
}

TEST_F(SonyTagDecipherTest_1625, BehaviorConsistencyWhenBytesNullAndSizeNonZero_1625) {
  // Potential error case: nullptr bytes with non-zero size.
  // We do NOT assume throw vs no-throw; we assert consistency between the wrapper and the underlying call.
  ExpectSameAsCipherDecodeTrue(static_cast<uint16_t>(0x00ff), nullptr, 1, nullptr);
}