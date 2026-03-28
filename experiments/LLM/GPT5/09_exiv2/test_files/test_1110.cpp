// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1110
//
// Unit tests for Exiv2::ImageFactory::create(ImageType type)
// File under test: ./TestProjects/exiv2/src/image.cpp

#include <gtest/gtest.h>

#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <cstdint>
#include <limits>
#include <memory>
#include <type_traits>

namespace {

// ---- Optional, non-invasive helpers to observe Exiv2::Error details if available ----

template <typename T, typename = void>
struct has_code_method : std::false_type {};
template <typename T>
struct has_code_method<T, std::void_t<decltype(std::declval<const T&>().code())>> : std::true_type {};

template <typename T, typename = void>
struct has_error_code_method : std::false_type {};
template <typename T>
struct has_error_code_method<T,
                             std::void_t<decltype(std::declval<const T&>().errorCode())>> : std::true_type {};

// Extract an ErrorCode if the Error type exposes something usable; otherwise, return std::nullopt.
static std::optional<Exiv2::ErrorCode> tryGetErrorCode(const Exiv2::Error& e) {
  if constexpr (has_code_method<Exiv2::Error>::value) {
    // Many Exiv2 Error implementations expose code() returning int or ErrorCode.
    auto c = e.code();
    if constexpr (std::is_same_v<decltype(c), Exiv2::ErrorCode>) {
      return c;
    } else if constexpr (std::is_integral_v<decltype(c)>) {
      return static_cast<Exiv2::ErrorCode>(c);
    }
  }
  if constexpr (has_error_code_method<Exiv2::Error>::value) {
    auto c = e.errorCode();
    if constexpr (std::is_same_v<decltype(c), Exiv2::ErrorCode>) {
      return c;
    } else if constexpr (std::is_integral_v<decltype(c)>) {
      return static_cast<Exiv2::ErrorCode>(c);
    }
  }
  return std::nullopt;
}

class ImageFactoryCreateTest_1110 : public ::testing::Test {
protected:
  Exiv2::ImageFactory factory_;
};

}  // namespace

TEST_F(ImageFactoryCreateTest_1110, CreateWithVeryLargeTypeThrowsError_1110) {
  // Boundary/exceptional case: use an out-of-range enum value.
  const auto type = static_cast<Exiv2::ImageType>(std::numeric_limits<int>::max());

  try {
    (void)factory_.create(type);
    FAIL() << "Expected Exiv2::Error to be thrown for an unsupported ImageType.";
  } catch (const Exiv2::Error& e) {
    // Observable behavior: an Exiv2::Error is thrown when create(type, MemIo) yields null.
    // If ErrorCode is observable through the interface, validate it's kerUnsupportedImageType.
    if (auto code = tryGetErrorCode(e); code.has_value()) {
      EXPECT_EQ(*code, Exiv2::ErrorCode::kerUnsupportedImageType);
    }
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type.";
  }
}

TEST_F(ImageFactoryCreateTest_1110, CreateWithNegativeTypeThrowsError_1110) {
  // Boundary/exceptional case: negative underlying value (if ImageType is enum).
  const auto type = static_cast<Exiv2::ImageType>(-1);

  try {
    (void)factory_.create(type);
    FAIL() << "Expected Exiv2::Error to be thrown for an unsupported ImageType.";
  } catch (const Exiv2::Error& e) {
    if (auto code = tryGetErrorCode(e); code.has_value()) {
      EXPECT_EQ(*code, Exiv2::ErrorCode::kerUnsupportedImageType);
    }
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but caught a different exception type.";
  }
}

TEST_F(ImageFactoryCreateTest_1110, CreateDoesNotReturnNullWhenItSucceeds_1110) {
  // Normal operation (best-effort, black-box):
  // Probe a small range of ImageType values and assert that if create succeeds, it returns non-null.
  // Also assert we can find at least one supported type in a typical build.
  bool foundSupported = false;

  for (int i = 0; i <= 200; ++i) {
    const auto type = static_cast<Exiv2::ImageType>(i);

    try {
      auto img = factory_.create(type);
      ASSERT_NE(img.get(), nullptr) << "create(type) succeeded but returned nullptr (i=" << i << ")";
      foundSupported = true;

      // Basic ownership sanity: moving unique_ptr transfers ownership.
      auto moved = std::move(img);
      EXPECT_EQ(img.get(), nullptr);
      EXPECT_NE(moved.get(), nullptr);

      break;  // one success is enough for this test
    } catch (const Exiv2::Error&) {
      // Unsupported types are expected in the probed range; continue searching.
    }
  }

  ASSERT_TRUE(foundSupported)
      << "Did not find any supported ImageType in the probed range [0..200]. "
         "If this build intentionally disables all image types, adjust the test environment.";
}

TEST_F(ImageFactoryCreateTest_1110, CreateHandlesZeroValueTypeWithoutCrashing_1110) {
  // Boundary: lowest common underlying value.
  const auto type = static_cast<Exiv2::ImageType>(0);

  // Black-box expectation: either it succeeds with non-null, or throws Exiv2::Error.
  try {
    auto img = factory_.create(type);
    ASSERT_NE(img.get(), nullptr);
  } catch (const Exiv2::Error& e) {
    if (auto code = tryGetErrorCode(e); code.has_value()) {
      EXPECT_EQ(*code, Exiv2::ErrorCode::kerUnsupportedImageType);
    }
  } catch (...) {
    FAIL() << "Expected success or Exiv2::Error; caught a different exception type.";
  }
}