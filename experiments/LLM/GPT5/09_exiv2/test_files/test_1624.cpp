// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_sonyTagCipher_1624.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "types.hpp"               // Exiv2::byte, Exiv2::DataBuf
#include "tiffcomposite_int.hpp"   // Exiv2::Internal::TiffComponent

// Include the implementation file to access the internal-linkage function.
// This keeps the production code as a black box while still allowing tests
// to exercise the real implementation.
#include "sonymn_int.cpp"

namespace {

class SonyTagCipherTest_1624 : public ::testing::Test {
protected:
  static std::vector<Exiv2::byte> ToVector(const Exiv2::DataBuf& b) {
    std::vector<Exiv2::byte> out;
    out.reserve(b.size_);
    for (size_t i = 0; i < b.size_; ++i) out.push_back(b.pData_[i]);
    return out;
  }
};

TEST_F(SonyTagCipherTest_1624, SizeZeroAcceptsNullBytesPointer_1624) {
  const Exiv2::byte* bytes = nullptr;
  const size_t size = 0;

  Exiv2::DataBuf outEnc = Exiv2::Internal::sonyTagCipher(0, bytes, size, nullptr, false);
  Exiv2::DataBuf outDec = Exiv2::Internal::sonyTagCipher(0, bytes, size, nullptr, true);

  EXPECT_EQ(outEnc.size_, 0u);
  EXPECT_EQ(outDec.size_, 0u);
}

TEST_F(SonyTagCipherTest_1624, ReturnsBufferWithSameSizeAndDoesNotModifyInput_1624) {
  std::array<Exiv2::byte, 8> input{{0, 1, 2, 3, 4, 5, 250, 255}};
  const auto original = input;  // snapshot

  Exiv2::DataBuf out = Exiv2::Internal::sonyTagCipher(0, input.data(), input.size(), nullptr, false);

  EXPECT_EQ(out.size_, input.size());
  EXPECT_EQ(input, original);  // input should not be mutated
}

TEST_F(SonyTagCipherTest_1624, OutputIsACopyNotAliasedToInput_1624) {
  std::array<Exiv2::byte, 4> input{{10, 20, 30, 40}};

  Exiv2::DataBuf out = Exiv2::Internal::sonyTagCipher(0, input.data(), input.size(), nullptr, false);
  ASSERT_EQ(out.size_, input.size());

  // Mutate the input after the call; output should remain unchanged if it is a copy.
  auto before = ToVector(out);
  input[0] = 99;
  input[1] = 88;
  input[2] = 77;
  input[3] = 66;

  auto after = ToVector(out);
  EXPECT_EQ(after, before);
}

TEST_F(SonyTagCipherTest_1624, EncryptThenDecryptRestoresOriginal_ForAllByteValues_1624) {
  std::array<Exiv2::byte, 256> input{};
  for (size_t i = 0; i < input.size(); ++i) input[i] = static_cast<Exiv2::byte>(i);

  Exiv2::DataBuf enc = Exiv2::Internal::sonyTagCipher(0, input.data(), input.size(), nullptr, false);
  ASSERT_EQ(enc.size_, input.size());

  Exiv2::DataBuf dec = Exiv2::Internal::sonyTagCipher(0, enc.pData_, enc.size_, nullptr, true);
  ASSERT_EQ(dec.size_, input.size());

  for (size_t i = 0; i < input.size(); ++i) {
    EXPECT_EQ(dec.pData_[i], input[i]) << "Mismatch at byte index " << i;
  }
}

TEST_F(SonyTagCipherTest_1624, DecryptThenEncryptRestoresOriginal_ForTypicalPayload_1624) {
  const std::vector<Exiv2::byte> payload = {
      0, 7, 13, 42, 64, 128, 200, 248, 249, 250, 251, 252, 253, 254, 255,
  };

  Exiv2::DataBuf dec = Exiv2::Internal::sonyTagCipher(0, payload.data(), payload.size(), nullptr, true);
  ASSERT_EQ(dec.size_, payload.size());

  Exiv2::DataBuf enc = Exiv2::Internal::sonyTagCipher(0, dec.pData_, dec.size_, nullptr, false);
  ASSERT_EQ(enc.size_, payload.size());

  for (size_t i = 0; i < payload.size(); ++i) {
    EXPECT_EQ(enc.pData_[i], payload[i]) << "Mismatch at payload index " << i;
  }
}

}  // namespace