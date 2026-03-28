// File: lzwencoder_test_228.cpp
#include <gtest/gtest.h>

#include "Stream.h"

namespace {

// Tries to construct LZWEncoder in a way that is compatible with different
// constructor signatures that may exist in the real codebase.
// If none match, the test will be skipped at runtime.
template <typename T>
struct EncoderFactory {
  static bool CanCreate() {
    if constexpr (std::is_default_constructible_v<T>) {
      return true;
    } else if constexpr (std::is_constructible_v<T, Stream*>) {
      return true;
    } else if constexpr (std::is_constructible_v<T, Stream*, int>) {
      return true;
    } else {
      return false;
    }
  }

  static T Create() {
    if constexpr (std::is_default_constructible_v<T>) {
      return T{};
    } else if constexpr (std::is_constructible_v<T, Stream*>) {
      return T{static_cast<Stream*>(nullptr)};
    } else if constexpr (std::is_constructible_v<T, Stream*, int>) {
      return T{static_cast<Stream*>(nullptr), 0};
    } else {
      // Should never be instantiated when guarded by CanCreate() / if constexpr.
      return T{};
    }
  }
};

class LZWEncoderTest_228 : public ::testing::Test {};

}  // namespace

TEST_F(LZWEncoderTest_228, IsBinaryReturnsTrue_DefaultArg_228) {
  if (!EncoderFactory<LZWEncoder>::CanCreate()) {
    GTEST_SKIP() << "LZWEncoder cannot be constructed with supported signatures in this test.";
  }
  auto enc = EncoderFactory<LZWEncoder>::Create();

  EXPECT_TRUE(enc.isBinary());
}

TEST_F(LZWEncoderTest_228, IsBinaryReturnsTrue_LastFalse_228) {
  if (!EncoderFactory<LZWEncoder>::CanCreate()) {
    GTEST_SKIP() << "LZWEncoder cannot be constructed with supported signatures in this test.";
  }
  auto enc = EncoderFactory<LZWEncoder>::Create();

  EXPECT_TRUE(enc.isBinary(false));
}

TEST_F(LZWEncoderTest_228, IsBinaryReturnsTrue_LastTrue_228) {
  if (!EncoderFactory<LZWEncoder>::CanCreate()) {
    GTEST_SKIP() << "LZWEncoder cannot be constructed with supported signatures in this test.";
  }
  auto enc = EncoderFactory<LZWEncoder>::Create();

  EXPECT_TRUE(enc.isBinary(true));
}