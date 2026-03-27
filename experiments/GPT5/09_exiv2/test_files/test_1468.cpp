// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include "makernote_int.hpp"
#include "basicio.hpp"  // MemIo (if needed by headers); safe include in Exiv2 tests.

#include <cstddef>
#include <vector>

namespace Exiv2::Internal {

class Nikon3MnHeaderTest_1468 : public ::testing::Test {};

TEST_F(Nikon3MnHeaderTest_1468, SetByteOrderIsReflectedByGetter_1468) {
  Nikon3MnHeader h;

  h.setByteOrder(bigEndian);
  EXPECT_EQ(bigEndian, h.byteOrder());

  h.setByteOrder(littleEndian);
  EXPECT_EQ(littleEndian, h.byteOrder());
}

TEST_F(Nikon3MnHeaderTest_1468, SizeOfSignatureIsStableAndNonZero_1468) {
  const size_t s1 = Nikon3MnHeader::sizeOfSignature();
  const size_t s2 = Nikon3MnHeader::sizeOfSignature();

  EXPECT_EQ(s1, s2);
  EXPECT_GT(s1, 0u);
}

TEST_F(Nikon3MnHeaderTest_1468, VirtualDispatchForByteOrderMatchesConcreteGetter_1468) {
  Nikon3MnHeader h;
  MnHeader* base = &h;

  h.setByteOrder(bigEndian);
  EXPECT_EQ(h.byteOrder(), base->byteOrder());

  h.setByteOrder(littleEndian);
  EXPECT_EQ(h.byteOrder(), base->byteOrder());
}

TEST_F(Nikon3MnHeaderTest_1468, VirtualDispatchForSizeIsStableAcrossCalls_1468) {
  Nikon3MnHeader h;
  MnHeader* base = &h;

  const size_t s1 = base->size();
  const size_t s2 = base->size();
  EXPECT_EQ(s1, s2);
}

TEST_F(Nikon3MnHeaderTest_1468, VirtualDispatchForIfdOffsetIsStableAcrossCalls_1468) {
  Nikon3MnHeader h;
  MnHeader* base = &h;

  const size_t o1 = base->ifdOffset();
  const size_t o2 = base->ifdOffset();
  EXPECT_EQ(o1, o2);
}

TEST_F(Nikon3MnHeaderTest_1468, ReadWithNullBufferAndZeroSizeFails_1468) {
  Nikon3MnHeader h;

  // Boundary/invalid input: no data.
  EXPECT_FALSE(h.read(nullptr, 0u, littleEndian));
  EXPECT_FALSE(h.read(nullptr, 0u, bigEndian));
}

TEST_F(Nikon3MnHeaderTest_1468, ReadWithTooSmallBufferFails_1468) {
  Nikon3MnHeader h;

  const size_t sig = Nikon3MnHeader::sizeOfSignature();
  ASSERT_GT(sig, 0u);

  // Size strictly smaller than the signature size is clearly insufficient.
  const size_t small = (sig > 1u) ? (sig - 1u) : 0u;
  std::vector<byte> buf(small, static_cast<byte>(0));

  const byte* p = buf.empty() ? nullptr : buf.data();
  EXPECT_FALSE(h.read(p, buf.size(), littleEndian));
  EXPECT_FALSE(h.read(p, buf.size(), bigEndian));
}

TEST_F(Nikon3MnHeaderTest_1468, ReadWithAllZeroSignatureSizedBufferDoesNotSucceed_1468) {
  Nikon3MnHeader h;

  const size_t sig = Nikon3MnHeader::sizeOfSignature();
  ASSERT_GT(sig, 0u);

  // A buffer of all zeros is not a valid Nikon MakerNote header signature in practice;
  // observable expectation: read should fail.
  std::vector<byte> buf(sig, static_cast<byte>(0));
  EXPECT_FALSE(h.read(buf.data(), buf.size(), littleEndian));
  EXPECT_FALSE(h.read(buf.data(), buf.size(), bigEndian));
}

}  // namespace Exiv2::Internal