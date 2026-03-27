// File: test_newsigmamn_1528.cpp
// Tests for: Exiv2::Internal::newSigmaMn (makernote_int.cpp)

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <vector>

// Exiv2 internals
#include "makernote_int.hpp"
#include "sigmamn_int.hpp"   // for SigmaMnHeader::sizeOfSignature()
#include "types.hpp"         // for Exiv2::byte, ByteOrder, IfdId

namespace {

class NewSigmaMnTest_1528 : public ::testing::Test {
 protected:
  static size_t MinSize() {
    return Exiv2::Internal::SigmaMnHeader::sizeOfSignature() + 18u;
  }

  static Exiv2::IfdId AnyIfdId() {
    // Avoid relying on specific enumerators; just pass a valid value in-range for compilation.
    return static_cast<Exiv2::IfdId>(0);
  }
};

}  // namespace

TEST_F(NewSigmaMnTest_1528, ReturnsNullptrWhenSizeIsZero_1528) {
  const uint16_t tag = 0;
  const Exiv2::IfdId group = AnyIfdId();
  const Exiv2::IfdId mnGroup = AnyIfdId();

  auto mn = Exiv2::Internal::newSigmaMn(tag, group, mnGroup,
                                        /*data*/ nullptr,
                                        /*size*/ 0,
                                        /*byteOrder*/ Exiv2::littleEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewSigmaMnTest_1528, ReturnsNullptrWhenSizeBelowMinimum_1528) {
  const size_t minSize = MinSize();
  ASSERT_GT(minSize, 0u);

  const size_t size = minSize - 1u;
  std::vector<Exiv2::byte> buf(size, 0);

  auto mn = Exiv2::Internal::newSigmaMn(/*tag*/ 0, AnyIfdId(), AnyIfdId(),
                                        buf.data(), buf.size(), Exiv2::littleEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewSigmaMnTest_1528, ReturnsNonNullptrWhenSizeEqualsMinimum_1528) {
  const size_t size = MinSize();
  std::vector<Exiv2::byte> buf(size, 0);

  auto mn = Exiv2::Internal::newSigmaMn(/*tag*/ 0, AnyIfdId(), AnyIfdId(),
                                        buf.data(), buf.size(), Exiv2::littleEndian);
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewSigmaMnTest_1528, ReturnsNonNullptrWhenSizeAboveMinimum_1528) {
  const size_t size = MinSize() + 64u;
  std::vector<Exiv2::byte> buf(size, 0);

  auto mn = Exiv2::Internal::newSigmaMn(/*tag*/ 0, AnyIfdId(), AnyIfdId(),
                                        buf.data(), buf.size(), Exiv2::littleEndian);
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewSigmaMnTest_1528, BelowMinimumReturnsNullptrRegardlessOfParameters_1528) {
  const size_t minSize = MinSize();
  ASSERT_GT(minSize, 0u);

  const size_t size = minSize - 1u;
  std::vector<Exiv2::byte> buf(size, 0);

  auto mn1 = Exiv2::Internal::newSigmaMn(/*tag*/ 0, AnyIfdId(), AnyIfdId(),
                                         buf.data(), buf.size(), Exiv2::littleEndian);
  auto mn2 = Exiv2::Internal::newSigmaMn(/*tag*/ 0xFFFFu,
                                         static_cast<Exiv2::IfdId>(1),
                                         static_cast<Exiv2::IfdId>(2),
                                         buf.data(), buf.size(), Exiv2::bigEndian);

  EXPECT_EQ(mn1, nullptr);
  EXPECT_EQ(mn2, nullptr);
}