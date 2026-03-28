// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymnheader_1501.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "makernote_int.hpp"  // Exiv2::Internal::SonyMnHeader
#include "types.hpp"          // Exiv2::byte, Exiv2::ByteOrder (and endian constants)

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;
using Exiv2::Internal::SonyMnHeader;

// ---- Detection helpers (avoid depending on non-provided interface) ----
template <typename T, typename = void>
struct HasStaticSizeOfSignature : std::false_type {};
template <typename T>
struct HasStaticSizeOfSignature<T, std::void_t<decltype(T::sizeOfSignature())>> : std::true_type {};

template <typename T, typename = void>
struct HasStaticSignature : std::false_type {};
template <typename T>
struct HasStaticSignature<T, std::void_t<decltype(T::signature())>> : std::true_type {};

template <typename T>
constexpr bool kHasSigApi = HasStaticSizeOfSignature<T>::value && HasStaticSignature<T>::value;

// Attempts to materialize the signature bytes if SonyMnHeader exposes them via public static API.
// Expected patterns handled:
//  - signature() returns pointer-like (const byte* / const unsigned char*) to N bytes
//  - signature() returns std::array<byte, N> / similar container with data()
template <typename T>
std::vector<byte> GetSignatureBytes() {
  std::vector<byte> sig;

  if constexpr (!kHasSigApi<T>) {
    return sig;
  } else {
    const size_t n = static_cast<size_t>(T::sizeOfSignature());
    sig.resize(n);

    auto s = T::signature();
    if constexpr (std::is_pointer_v<decltype(s)>) {
      const auto* p = reinterpret_cast<const byte*>(s);
      for (size_t i = 0; i < n; ++i) sig[i] = p[i];
    } else if constexpr (requires { s.data(); }) {
      const auto* p = reinterpret_cast<const byte*>(s.data());
      for (size_t i = 0; i < n; ++i) sig[i] = p[i];
    } else {
      // Unknown signature() shape
      sig.clear();
    }
    return sig;
  }
}

ByteOrder SomeByteOrder() {
#ifdef EXV_HAVE_BYTEORDER_ENUM
  // If ByteOrder is strongly typed and Exiv2 provides endian constants, prefer them.
#endif
  // In Exiv2, typical values are Exiv2::littleEndian / Exiv2::bigEndian.
  // Use littleEndian if present, otherwise fall back to a default-constructed ByteOrder.
#if defined(littleEndian)
  return Exiv2::littleEndian;
#elif defined(bigEndian)
  return Exiv2::bigEndian;
#else
  return ByteOrder{};
#endif
}

class SonyMnHeaderTest_1501 : public ::testing::Test {
 protected:
  SonyMnHeader hdr_;
};

}  // namespace

TEST_F(SonyMnHeaderTest_1501, ReadNullDataReturnsFalse_1501) {
  EXPECT_FALSE(hdr_.read(nullptr, 0U, SomeByteOrder()));
  EXPECT_FALSE(hdr_.read(nullptr, 10U, SomeByteOrder()));
}

TEST_F(SonyMnHeaderTest_1501, ReadWithZeroSizeReturnsFalse_1501) {
  const byte b = 0x00;
  EXPECT_FALSE(hdr_.read(&b, 0U, SomeByteOrder()));
}

TEST_F(SonyMnHeaderTest_1501, ReadWithSizeLessThanSignatureReturnsFalse_1501) {
  if constexpr (!HasStaticSizeOfSignature<SonyMnHeader>::value) {
    GTEST_SKIP() << "SonyMnHeader::sizeOfSignature() is not available via the public interface.";
  } else {
    const size_t sigSize = static_cast<size_t>(SonyMnHeader::sizeOfSignature());
    if (sigSize == 0) {
      GTEST_SKIP() << "Signature size reported as 0; boundary test not applicable.";
    }

    const size_t tooSmall = sigSize - 1;
    std::vector<byte> data(sigSize, 0xAA);

    EXPECT_FALSE(hdr_.read(data.data(), tooSmall, SomeByteOrder()));
  }
}

TEST_F(SonyMnHeaderTest_1501, ReadWithMismatchedSignatureReturnsFalse_1501) {
  if constexpr (!kHasSigApi<SonyMnHeader>) {
    GTEST_SKIP() << "Signature bytes are not available via the public interface; "
                    "cannot guarantee a deterministic mismatch buffer.";
  } else {
    const auto sig = GetSignatureBytes<SonyMnHeader>();
    ASSERT_FALSE(sig.empty());

    std::vector<byte> data = sig;
    // Flip first byte to guarantee mismatch while keeping size == signature size.
    data[0] = static_cast<byte>(data[0] ^ 0xFF);

    EXPECT_FALSE(hdr_.read(data.data(), data.size(), SomeByteOrder()));
  }
}

TEST_F(SonyMnHeaderTest_1501, ReadWithMatchingSignatureReturnsTrue_1501) {
  if constexpr (!kHasSigApi<SonyMnHeader>) {
    GTEST_SKIP() << "SonyMnHeader does not expose signature/size via the public interface; "
                    "cannot construct a guaranteed-valid header.";
  } else {
    const auto sig = GetSignatureBytes<SonyMnHeader>();
    ASSERT_FALSE(sig.empty());

    // Provide extra bytes beyond the signature; interface says it only checks prefix + size.
    std::vector<byte> data = sig;
    data.push_back(static_cast<byte>(0x11));
    data.push_back(static_cast<byte>(0x22));

    EXPECT_TRUE(hdr_.read(data.data(), data.size(), SomeByteOrder()));
  }
}

TEST_F(SonyMnHeaderTest_1501, ReadIsNotAffectedByPreviousFailures_1501) {
  // A previous failure should not make a nullptr call succeed, regardless of internal state.
  std::vector<byte> data(8, 0x00);
  (void)hdr_.read(data.data(), data.size(), SomeByteOrder());  // may be false; that's fine
  EXPECT_FALSE(hdr_.read(nullptr, 8U, SomeByteOrder()));
}

TEST_F(SonyMnHeaderTest_1501, ReadAfterSuccessThenNullStillReturnsFalse_1501) {
  if constexpr (!kHasSigApi<SonyMnHeader>) {
    GTEST_SKIP() << "SonyMnHeader does not expose signature/size via the public interface; "
                    "cannot force a successful read.";
  } else {
    const auto sig = GetSignatureBytes<SonyMnHeader>();
    ASSERT_FALSE(sig.empty());

    std::vector<byte> data = sig;
    data.push_back(static_cast<byte>(0x33));

    ASSERT_TRUE(hdr_.read(data.data(), data.size(), SomeByteOrder()));
    EXPECT_FALSE(hdr_.read(nullptr, data.size(), SomeByteOrder()));
  }
}