// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tiffencoder_encodebinaryarray_1680.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "exif.hpp"

namespace {

using Exiv2::Exifdatum;
using Exiv2::Internal::TiffBinaryArray;
using Exiv2::Internal::TiffEncoder;

class TiffEncoderEncodeBinaryArrayTest_1680 : public ::testing::Test {};

TEST_F(TiffEncoderEncodeBinaryArrayTest_1680, HasExpectedSignature_1680) {
  // Black-box: only verify the public interface shape is as expected.
  using MethodPtr = void (TiffEncoder::*)(TiffBinaryArray*, const Exifdatum*);
  static_assert(std::is_same_v<decltype(&TiffEncoder::encodeBinaryArray), MethodPtr>,
                "encodeBinaryArray signature mismatch");
  SUCCEED();
}

TEST_F(TiffEncoderEncodeBinaryArrayTest_1680, NullArguments_NoThrowIfDefaultConstructible_1680) {
  if constexpr (std::is_default_constructible_v<TiffEncoder>) {
    TiffEncoder encoder;
    EXPECT_NO_THROW(encoder.encodeBinaryArray(nullptr, nullptr));
  } else {
    GTEST_SKIP() << "TiffEncoder is not default-constructible in this build; "
                    "cannot exercise runtime call without constructing required dependencies.";
  }
}

TEST_F(TiffEncoderEncodeBinaryArrayTest_1680, NullObject_NoThrowIfDefaultConstructible_1680) {
  if constexpr (std::is_default_constructible_v<TiffEncoder>) {
    TiffEncoder encoder;
    const Exifdatum* datum = nullptr;
    EXPECT_NO_THROW(encoder.encodeBinaryArray(nullptr, datum));
  } else {
    GTEST_SKIP();
  }
}

TEST_F(TiffEncoderEncodeBinaryArrayTest_1680, NullDatum_NoThrowIfDefaultConstructible_1680) {
  if constexpr (std::is_default_constructible_v<TiffEncoder>) {
    TiffEncoder encoder;
    TiffBinaryArray* object = nullptr;
    EXPECT_NO_THROW(encoder.encodeBinaryArray(object, nullptr));
  } else {
    GTEST_SKIP();
  }
}

TEST_F(TiffEncoderEncodeBinaryArrayTest_1680, MultipleCalls_WithNulls_NoThrowIfDefaultConstructible_1680) {
  if constexpr (std::is_default_constructible_v<TiffEncoder>) {
    TiffEncoder encoder;
    EXPECT_NO_THROW(encoder.encodeBinaryArray(nullptr, nullptr));
    EXPECT_NO_THROW(encoder.encodeBinaryArray(nullptr, nullptr));
    EXPECT_NO_THROW(encoder.encodeBinaryArray(nullptr, nullptr));
  } else {
    GTEST_SKIP();
  }
}

}  // namespace