// =====================================================================================
// TEST_ID: 1626
// Unit tests for Exiv2::Internal::sonyTagEncipher
// File under test: ./TestProjects/exiv2/src/sonymn_int.cpp
// =====================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#if __has_include("sonymn_int.hpp")
#include "sonymn_int.hpp"
#elif __has_include("sonymn_int.h")
#include "sonymn_int.h"
#elif __has_include("sonymn_int.hpp")
#include "sonymn_int.hpp"
#elif __has_include(<exiv2/sonymn_int.hpp>)
#include <exiv2/sonymn_int.hpp>
#endif

#if __has_include("tiffcomposite_int.hpp")
#include "tiffcomposite_int.hpp"
#elif __has_include(<exiv2/tiffcomposite_int.hpp>)
#include <exiv2/tiffcomposite_int.hpp>
#endif

namespace {

// Helpers that work with typical Exiv2::DataBuf (often has public .pData_/.size_).
template <typename DataBufT>
size_t DataBufSize(const DataBufT& b) {
  if constexpr (requires { b.size_; }) {
    return static_cast<size_t>(b.size_);
  } else if constexpr (requires { b.size(); }) {
    return static_cast<size_t>(b.size());
  } else {
    // If neither is available, compilation will fail here, which is fine for CI discovery.
    return 0;
  }
}

template <typename DataBufT>
const unsigned char* DataBufData(const DataBufT& b) {
  if constexpr (requires { b.pData_; }) {
    return reinterpret_cast<const unsigned char*>(b.pData_);
  } else if constexpr (requires { b.data(); }) {
    return reinterpret_cast<const unsigned char*>(b.data());
  } else {
    return nullptr;
  }
}

template <typename DataBufT>
void ExpectSameDataBuf(const DataBufT& a, const DataBufT& b) {
  const size_t asz = DataBufSize(a);
  const size_t bsz = DataBufSize(b);
  ASSERT_EQ(asz, bsz);

  const auto* ap = DataBufData(a);
  const auto* bp = DataBufData(b);

  if (asz == 0) {
    // For empty buffers, content pointers may be null or non-null; only size matters.
    return;
  }

  ASSERT_NE(ap, nullptr);
  ASSERT_NE(bp, nullptr);
  EXPECT_EQ(0, std::memcmp(ap, bp, asz));
}

// Minimal concrete TiffComponent to supply a pointer through the public constructor.
// (No assumptions about internal behavior.)
class DummyTiffComponent_1626 : public Exiv2::Internal::TiffComponent {
 public:
  DummyTiffComponent_1626(uint16_t tag, Exiv2::Internal::IfdId group)
      : Exiv2::Internal::TiffComponent(tag, group) {}
};

}  // namespace

class SonyTagEncipherTest_1626 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeBytes(size_t n) {
    std::vector<Exiv2::byte> v(n);
    for (size_t i = 0; i < n; ++i) v[i] = static_cast<Exiv2::byte>((i * 131u + 7u) & 0xFFu);
    return v;
  }
};

// Normal operation: wrapper should match the observable output of sonyTagCipher(..., false).
TEST_F(SonyTagEncipherTest_1626, MatchesSonyTagCipherForTypicalInput_1626) {
  DummyTiffComponent_1626 obj(/*tag*/ 0x1234, static_cast<Exiv2::Internal::IfdId>(0));
  const auto bytes = MakeBytes(64);

  const uint16_t tag = 0x2001;

  const auto out_enc =
      Exiv2::Internal::sonyTagEncipher(tag, bytes.data(), bytes.size(), &obj);
  const auto out_cipher =
      Exiv2::Internal::sonyTagCipher(tag, bytes.data(), bytes.size(), &obj, /*decipher*/ false);

  ExpectSameDataBuf(out_enc, out_cipher);
}

// Determinism (observable): repeated calls with same inputs should produce identical outputs.
TEST_F(SonyTagEncipherTest_1626, DeterministicForSameInputs_1626) {
  DummyTiffComponent_1626 obj(/*tag*/ 0x7777, static_cast<Exiv2::Internal::IfdId>(0));
  const auto bytes = MakeBytes(128);
  const uint16_t tag = 0x00A5;

  const auto out1 =
      Exiv2::Internal::sonyTagEncipher(tag, bytes.data(), bytes.size(), &obj);
  const auto out2 =
      Exiv2::Internal::sonyTagEncipher(tag, bytes.data(), bytes.size(), &obj);

  ExpectSameDataBuf(out1, out2);
}

// Boundary: size==0 with nullptr input buffer (common C API convention). Compare to cipher behavior.
TEST_F(SonyTagEncipherTest_1626, ZeroSizeWithNullBytesMatchesCipher_1626) {
  DummyTiffComponent_1626 obj(/*tag*/ 0x0102, static_cast<Exiv2::Internal::IfdId>(0));
  const uint16_t tag = 0x0001;

  const Exiv2::byte* bytes = nullptr;
  const size_t size = 0;

  const auto out_enc = Exiv2::Internal::sonyTagEncipher(tag, bytes, size, &obj);
  const auto out_cipher =
      Exiv2::Internal::sonyTagCipher(tag, bytes, size, &obj, /*decipher*/ false);

  ExpectSameDataBuf(out_enc, out_cipher);
}

// Boundary: tag at minimum value.
TEST_F(SonyTagEncipherTest_1626, TagMinValueMatchesCipher_1626) {
  DummyTiffComponent_1626 obj(/*tag*/ 0x0000, static_cast<Exiv2::Internal::IfdId>(0));
  const auto bytes = MakeBytes(16);

  const uint16_t tag = 0x0000;

  const auto out_enc =
      Exiv2::Internal::sonyTagEncipher(tag, bytes.data(), bytes.size(), &obj);
  const auto out_cipher =
      Exiv2::Internal::sonyTagCipher(tag, bytes.data(), bytes.size(), &obj, /*decipher*/ false);

  ExpectSameDataBuf(out_enc, out_cipher);
}

// Boundary: tag at maximum value.
TEST_F(SonyTagEncipherTest_1626, TagMaxValueMatchesCipher_1626) {
  DummyTiffComponent_1626 obj(/*tag*/ 0xFFFF, static_cast<Exiv2::Internal::IfdId>(0));
  const auto bytes = MakeBytes(33);

  const uint16_t tag = 0xFFFF;

  const auto out_enc =
      Exiv2::Internal::sonyTagEncipher(tag, bytes.data(), bytes.size(), &obj);
  const auto out_cipher =
      Exiv2::Internal::sonyTagCipher(tag, bytes.data(), bytes.size(), &obj, /*decipher*/ false);

  ExpectSameDataBuf(out_enc, out_cipher);
}

// Error/exceptional (if observable): null object pointer.
// We don't assume it must succeed; we only require sonyTagEncipher to behave identically
// to sonyTagCipher(..., false) for the same inputs (including nullptr).
TEST_F(SonyTagEncipherTest_1626, NullObjectPointerMatchesCipher_1626) {
  const auto bytes = MakeBytes(24);
  const uint16_t tag = 0x0BEE;

  Exiv2::Internal::TiffComponent* obj = nullptr;

  const auto out_enc =
      Exiv2::Internal::sonyTagEncipher(tag, bytes.data(), bytes.size(), obj);
  const auto out_cipher =
      Exiv2::Internal::sonyTagCipher(tag, bytes.data(), bytes.size(), obj, /*decipher*/ false);

  ExpectSameDataBuf(out_enc, out_cipher);
}

// Boundary: very small payload (size==1).
TEST_F(SonyTagEncipherTest_1626, SingleBytePayloadMatchesCipher_1626) {
  DummyTiffComponent_1626 obj(/*tag*/ 0x2222, static_cast<Exiv2::Internal::IfdId>(0));
  const auto bytes = MakeBytes(1);
  const uint16_t tag = 0x0100;

  const auto out_enc =
      Exiv2::Internal::sonyTagEncipher(tag, bytes.data(), bytes.size(), &obj);
  const auto out_cipher =
      Exiv2::Internal::sonyTagCipher(tag, bytes.data(), bytes.size(), &obj, /*decipher*/ false);

  ExpectSameDataBuf(out_enc, out_cipher);
}