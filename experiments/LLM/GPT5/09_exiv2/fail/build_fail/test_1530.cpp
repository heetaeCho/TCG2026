// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_newsonymn_1530.cpp
//
// Unit tests for Exiv2::Internal::newSonyMn (makernote_int.cpp)
// Constraints honored: black-box tests via observable return value (nullptr/non-null) and safe-call behavior.

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>

#if __has_include("makernote_int.hpp")
#include "makernote_int.hpp"
#elif __has_include("makernote_int.h")
#include "makernote_int.h"
#elif __has_include(<exiv2/makernote_int.hpp>)
#include <exiv2/makernote_int.hpp>
#else
// If your build uses a different include path, adjust accordingly.
#include "makernote_int.hpp"
#endif

namespace {

using Exiv2::byte;

constexpr std::array<byte, 12> kSonyDscSignature = {
    static_cast<byte>('S'), static_cast<byte>('O'), static_cast<byte>('N'),
    static_cast<byte>('Y'), static_cast<byte>(' '), static_cast<byte>('D'),
    static_cast<byte>('S'), static_cast<byte>('C'), static_cast<byte>(' '),
    static_cast<byte>('\0'), static_cast<byte>('\0'), static_cast<byte>('\0'),
};

static Exiv2::ByteOrder AnyByteOrder() {
#if defined(EXV_HAVE_BYTEORDER_ENUM) // (unlikely) placeholder if your build defines such a macro
    return Exiv2::ByteOrder::littleEndian;
#else
    // Use a commonly present enumerator if available; otherwise fall back to zero-init cast.
    // Most Exiv2 builds provide ByteOrder::{littleEndian,bigEndian,invalidByteOrder}.
    // If compilation fails here, replace with a known enumerator for your tree.
    return static_cast<Exiv2::ByteOrder>(0);
#endif
}

static Exiv2::IfdId AnyIfdGroup() {
    // If your tree has a well-known "exifId/ifd0Id" enumerator, feel free to swap it in.
    return static_cast<Exiv2::IfdId>(0);
}

} // namespace

class NewSonyMnTest_1530 : public ::testing::Test {
protected:
    const uint16_t tag_ = 0x1234;
    const Exiv2::IfdId group_ = AnyIfdGroup();
    const Exiv2::IfdId ignored_ifd_ = AnyIfdGroup();
    const Exiv2::ByteOrder bo_ = AnyByteOrder();
};

TEST_F(NewSonyMnTest_1530, ReturnsNullWhenSizeIsZeroWithNullDataPtr_1530) {
    // size < 12 triggers early return path; must not dereference pData.
    const byte* pData = nullptr;
    auto mn = Exiv2::Internal::newSonyMn(tag_, group_, ignored_ifd_, pData, /*size=*/0, bo_);
    EXPECT_EQ(mn, nullptr);
}

TEST_F(NewSonyMnTest_1530, ReturnsNullWhenSizeIsElevenWithNullDataPtr_1530) {
    // Boundary: size just below 12; should still be safe with nullptr pData.
    const byte* pData = nullptr;
    auto mn = Exiv2::Internal::newSonyMn(tag_, group_, ignored_ifd_, pData, /*size=*/11, bo_);
    EXPECT_EQ(mn, nullptr);
}

TEST_F(NewSonyMnTest_1530, ReturnsNullWhenSizeIsTwelveButSignatureDoesNotMatch_1530) {
    // size == 12 means signature comparison is evaluated; mismatch keeps us in the first branch,
    // and since size < 18 it must return nullptr.
    std::array<byte, 12> data = kSonyDscSignature;
    data[0] = static_cast<byte>('X'); // force mismatch

    auto mn = Exiv2::Internal::newSonyMn(tag_, group_, ignored_ifd_, data.data(), data.size(), bo_);
    EXPECT_EQ(mn, nullptr);
}

TEST_F(NewSonyMnTest_1530, ReturnsNullWhenSizeIsSeventeenAndSignatureDoesNotMatch_1530) {
    // Boundary: size just below 18 in mismatch path => must return nullptr.
    std::array<byte, 17> data{};
    data[0] = static_cast<byte>('N'); // arbitrary non-matching content

    auto mn = Exiv2::Internal::newSonyMn(tag_, group_, ignored_ifd_, data.data(), data.size(), bo_);
    EXPECT_EQ(mn, nullptr);
}

TEST_F(NewSonyMnTest_1530, ReturnsNullWhenSignatureMatchesButSizeIsOnlyTwelve_1530) {
    // Signature matches, but then it checks:
    //   size < SonyMnHeader::sizeOfSignature() + 14  => nullptr
    // With size==12, this must be true for any non-negative signature size.
    std::array<byte, 12> data = kSonyDscSignature;

    auto mn = Exiv2::Internal::newSonyMn(tag_, group_, ignored_ifd_, data.data(), data.size(), bo_);
    EXPECT_EQ(mn, nullptr);
}

TEST_F(NewSonyMnTest_1530, ReturnsNullWhenSignatureMatchesButSizeIsOneLessThanHeaderPlus14_1530) {
    // Directly exercises the documented threshold, without relying on any downstream parsing.
    const size_t need = Exiv2::Internal::SonyMnHeader::sizeOfSignature() + 14;
    ASSERT_GT(need, 0u);

    const size_t size = need - 1;
    // Fill buffer; first 12 bytes must match signature.
    std::vector<byte> data(size, static_cast<byte>(0));
    ASSERT_GE(data.size(), kSonyDscSignature.size());
    std::copy(kSonyDscSignature.begin(), kSonyDscSignature.end(), data.begin());

    auto mn = Exiv2::Internal::newSonyMn(tag_, group_, ignored_ifd_, data.data(), data.size(), bo_);
    EXPECT_EQ(mn, nullptr);
}

TEST_F(NewSonyMnTest_1530, ReturnsNullWhenSignatureMatchesButSizeIsSmallerThanHeaderPlus14_ByOneAtMinimumSize_1530) {
    // Extra boundary check: when header signature size is large, ensure we still handle tiny buffers correctly.
    // We compute the minimum size that still provides the 12-byte SONY signature, but stays < need.
    const size_t need = Exiv2::Internal::SonyMnHeader::sizeOfSignature() + 14;
    ASSERT_GT(need, 0u);

    const size_t size = (need > 12) ? 12 : (need - 1); // always < need, and <= 12
    std::vector<byte> data(size, static_cast<byte>(0));
    if (data.size() >= kSonyDscSignature.size()) {
        std::copy(kSonyDscSignature.begin(), kSonyDscSignature.end(), data.begin());
    } else {
        // If size < 12, we must not dereference for signature comparison path anyway.
        // But we keep pData valid to avoid nullptr surprises.
    }

    auto mn = Exiv2::Internal::newSonyMn(tag_, group_, ignored_ifd_, data.data(), data.size(), bo_);
    EXPECT_EQ(mn, nullptr);
}