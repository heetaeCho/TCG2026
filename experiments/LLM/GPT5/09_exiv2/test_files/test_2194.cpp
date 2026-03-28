// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sigma_mn_header_2194.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "makernote_int.hpp"
#include "types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

using Exiv2::Internal::SigmaMnHeader;

class SigmaMnHeaderTest_2194 : public ::testing::Test {};

TEST_F(SigmaMnHeaderTest_2194, DefaultConstructor_DoesNotThrow_2194) {
  EXPECT_NO_THROW({
    SigmaMnHeader header;
    (void)header;
  });
}

TEST_F(SigmaMnHeaderTest_2194, SizeOfSignature_IsDeterministicAndNonZero_2194) {
  const size_t s1 = SigmaMnHeader::sizeOfSignature();
  const size_t s2 = SigmaMnHeader::sizeOfSignature();

  EXPECT_EQ(s1, s2);
  EXPECT_GT(s1, 0u);
}

TEST_F(SigmaMnHeaderTest_2194, Size_IsDeterministicAcrossCalls_2194) {
  SigmaMnHeader header;

  const size_t s1 = header.size();
  const size_t s2 = header.size();

  EXPECT_EQ(s1, s2);
}

TEST_F(SigmaMnHeaderTest_2194, IfdOffset_IsDeterministicAcrossCalls_2194) {
  SigmaMnHeader header;

  const size_t o1 = header.ifdOffset();
  const size_t o2 = header.ifdOffset();

  EXPECT_EQ(o1, o2);
}

TEST_F(SigmaMnHeaderTest_2194, Read_WithNullAndZeroSize_IsDeterministic_2194) {
  SigmaMnHeader header;

  // Boundary input: no data, no size.
  bool r1 = false;
  bool r2 = false;

  EXPECT_NO_THROW({ r1 = header.read(nullptr, 0u, invalidByteOrder); });
  EXPECT_NO_THROW({ r2 = header.read(nullptr, 0u, invalidByteOrder); });

  EXPECT_EQ(r1, r2);
}

TEST_F(SigmaMnHeaderTest_2194, Read_WithBufferSmallerThanSignature_IsDeterministic_2194) {
  SigmaMnHeader header;

  const size_t sig = SigmaMnHeader::sizeOfSignature();
  if (sig == 0u) {
    GTEST_SKIP() << "sizeOfSignature() returned 0; cannot construct smaller-than-signature buffer.";
  }
  if (sig == 1u) {
    // Smallest "smaller" buffer would be size 0; already covered by the null/zero-size test.
    GTEST_SKIP() << "sizeOfSignature() is 1; smaller-than-signature case would be size 0.";
  }

  std::vector<Exiv2::byte> buf(sig - 1u, static_cast<Exiv2::byte>(0));

  bool r1 = false;
  bool r2 = false;

  EXPECT_NO_THROW({ r1 = header.read(buf.data(), buf.size(), invalidByteOrder); });
  EXPECT_NO_THROW({ r2 = header.read(buf.data(), buf.size(), invalidByteOrder); });

  EXPECT_EQ(r1, r2);
}

TEST_F(SigmaMnHeaderTest_2194, Read_WithBufferExactlySignatureSize_DoesNotThrow_2194) {
  SigmaMnHeader header;

  const size_t sig = SigmaMnHeader::sizeOfSignature();
  ASSERT_GT(sig, 0u);

  std::vector<Exiv2::byte> buf(sig, static_cast<Exiv2::byte>(0));

  // Exercise read with a minimally "plausible" buffer length.
  EXPECT_NO_THROW({
    (void)header.read(buf.data(), buf.size(), invalidByteOrder);
  });
}

TEST_F(SigmaMnHeaderTest_2194, SetByteOrder_UpdatesByteOrder_2194) {
  SigmaMnHeader header;

  EXPECT_NO_THROW(header.setByteOrder(littleEndian));
  EXPECT_EQ(header.byteOrder(), littleEndian);

  EXPECT_NO_THROW(header.setByteOrder(bigEndian));
  EXPECT_EQ(header.byteOrder(), bigEndian);

  EXPECT_NO_THROW(header.setByteOrder(invalidByteOrder));
  EXPECT_EQ(header.byteOrder(), invalidByteOrder);
}

TEST_F(SigmaMnHeaderTest_2194, BaseOffset_DoesNotDependOnInputOffset_2194) {
  SigmaMnHeader header;

  // Based on the public MnHeader interface in the prompt: baseOffset(size_t /*mnOffset*/).
  const size_t b0 = header.baseOffset(0u);
  const size_t b1 = header.baseOffset(1u);
  const size_t b2 = header.baseOffset(12345u);

  EXPECT_EQ(b0, b1);
  EXPECT_EQ(b0, b2);
}

}  // namespace