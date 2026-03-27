// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sigma_mn_header_1494.cpp
//
// Unit tests for Exiv2::Internal::SigmaMnHeader (makernote_int.cpp / makernote_int.hpp)
//
// Constraints note:
// - Treat implementation as a black box.
// - Only test observable behavior via the public interface.
// - Avoid relying on any private/internal state.

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::SigmaMnHeader;
using Exiv2::Internal::MnHeader;

class SigmaMnHeaderTest_1494 : public ::testing::Test {};

TEST_F(SigmaMnHeaderTest_1494, SizeEqualsStaticSignatureSize_1494) {
  SigmaMnHeader header;
  const size_t expected = SigmaMnHeader::sizeOfSignature();

  // Observable behavior: size() should match the signature size.
  EXPECT_EQ(header.size(), expected);
}

TEST_F(SigmaMnHeaderTest_1494, ConstSizeEqualsStaticSignatureSize_1494) {
  const SigmaMnHeader header;
  const size_t expected = SigmaMnHeader::sizeOfSignature();

  // Observable behavior: const size() should match the signature size.
  EXPECT_EQ(header.size(), expected);
}

TEST_F(SigmaMnHeaderTest_1494, VirtualDispatchSizeViaBasePointer_1494) {
  SigmaMnHeader header;
  MnHeader* base = &header;

  const size_t expected = SigmaMnHeader::sizeOfSignature();

  // Observable behavior through the base interface (virtual dispatch).
  EXPECT_EQ(base->size(), expected);
}

TEST_F(SigmaMnHeaderTest_1494, SizeIsStableAcrossRepeatedCalls_1494) {
  SigmaMnHeader header;

  const size_t first = header.size();
  const size_t second = header.size();
  const size_t third = header.size();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_EQ(third, SigmaMnHeader::sizeOfSignature());
}

TEST_F(SigmaMnHeaderTest_1494, SizePreservedAfterCopyConstruction_1494) {
  SigmaMnHeader original;
  SigmaMnHeader copied(original);

  EXPECT_EQ(original.size(), copied.size());
  EXPECT_EQ(copied.size(), SigmaMnHeader::sizeOfSignature());
}

TEST_F(SigmaMnHeaderTest_1494, SizePreservedAfterMoveConstruction_1494) {
  SigmaMnHeader original;
  const size_t expected = original.size();

  SigmaMnHeader moved(std::move(original));

  EXPECT_EQ(moved.size(), expected);
  EXPECT_EQ(moved.size(), SigmaMnHeader::sizeOfSignature());
}

}  // namespace