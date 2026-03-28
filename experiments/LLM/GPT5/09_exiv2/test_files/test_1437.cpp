// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_olympusmnheader_1437.cpp
//
// Unit tests for Exiv2::Internal::OlympusMnHeader (makernote_int.*)
// The TEST_ID is 1437

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

#include "makernote_int.hpp"

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;
using Exiv2::Internal::OlympusMnHeader;

class OlympusMnHeaderTest_1437 : public ::testing::Test {};

TEST_F(OlympusMnHeaderTest_1437, SizeConstAndNonConstAgree_1437) {
  OlympusMnHeader h;

  const OlympusMnHeader& ch = h;
  const size_t s1 = h.size();   // non-const overload (override)
  const size_t s2 = ch.size();  // const overload

  EXPECT_EQ(s1, s2);
}

TEST_F(OlympusMnHeaderTest_1437, SizeOfSignatureIsNonZeroAndStable_1437) {
  const size_t sig1 = OlympusMnHeader::sizeOfSignature();
  const size_t sig2 = OlympusMnHeader::sizeOfSignature();

  EXPECT_GT(sig1, 0u);
  EXPECT_EQ(sig1, sig2);
}

TEST_F(OlympusMnHeaderTest_1437, ReadWithNullptrAndZeroSizeReturnsFalse_1437) {
  OlympusMnHeader h;

  const bool ok = h.read(nullptr, 0, ByteOrder::littleEndian);

  EXPECT_FALSE(ok);
}

TEST_F(OlympusMnHeaderTest_1437, ReadWithTooSmallBufferReturnsFalse_1437) {
  OlympusMnHeader h;

  const size_t sig = OlympusMnHeader::sizeOfSignature();
  // If signature is 0 (shouldn't be), keep the test safe anyway.
  const size_t small = (sig > 0u) ? (sig - 1u) : 0u;

  std::vector<byte> buf(small, static_cast<byte>(0));

  const bool ok = h.read(buf.empty() ? nullptr : buf.data(), buf.size(), ByteOrder::littleEndian);

  EXPECT_FALSE(ok);
}

TEST_F(OlympusMnHeaderTest_1437, FailedReadDoesNotChangeReportedSize_1437) {
  OlympusMnHeader h;
  const size_t before = h.size();

  const size_t sig = OlympusMnHeader::sizeOfSignature();
  const size_t small = (sig > 0u) ? (sig - 1u) : 0u;
  std::vector<byte> buf(small, static_cast<byte>(0xFF));

  (void)h.read(buf.empty() ? nullptr : buf.data(), buf.size(), ByteOrder::littleEndian);

  const size_t after = h.size();
  EXPECT_EQ(before, after);
}

}  // namespace