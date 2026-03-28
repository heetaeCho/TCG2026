// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon3mnheader_2189.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"
#include "basicio.hpp"

namespace {

// NOTE: Keep fixture name and every test name suffixed with TEST_ID = 2189.
class Nikon3MnHeaderTest_2189 : public ::testing::Test {
 protected:
  Exiv2::Internal::Nikon3MnHeader hdr_;
};

TEST_F(Nikon3MnHeaderTest_2189, ConstructsAndBasicQueriesAreStable_2189) {
  // Constructor should be safe; query methods should be callable and stable.
  const auto sigSize1 = Exiv2::Internal::Nikon3MnHeader::sizeOfSignature();
  const auto sigSize2 = Exiv2::Internal::Nikon3MnHeader::sizeOfSignature();
  EXPECT_EQ(sigSize1, sigSize2);

  const auto size1 = hdr_.size();
  const auto size2 = hdr_.size();
  EXPECT_EQ(size1, size2);

  const auto ifd1 = hdr_.ifdOffset();
  const auto ifd2 = hdr_.ifdOffset();
  EXPECT_EQ(ifd1, ifd2);

  // Basic sanity: sizes/offsets are non-negative by type, but ensure no weirdness.
  EXPECT_LE(ifd1, size1);
}

TEST_F(Nikon3MnHeaderTest_2189, SetByteOrderIsObservableViaByteOrder_2189) {
  hdr_.setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(hdr_.byteOrder(), Exiv2::littleEndian);

  hdr_.setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(hdr_.byteOrder(), Exiv2::bigEndian);
}

TEST_F(Nikon3MnHeaderTest_2189, BaseOffsetIsCallableAndStableForSameInput_2189) {
  const size_t mnOffset = 0;
  const auto b1 = hdr_.baseOffset(mnOffset);
  const auto b2 = hdr_.baseOffset(mnOffset);
  EXPECT_EQ(b1, b2);

  const size_t mnOffsetLarge = 1024u;
  const auto b3 = hdr_.baseOffset(mnOffsetLarge);
  const auto b4 = hdr_.baseOffset(mnOffsetLarge);
  EXPECT_EQ(b3, b4);
}

TEST_F(Nikon3MnHeaderTest_2189, ReadHandlesNullAndEmptyInputGracefully_2189) {
  // Boundary: nullptr with size 0 should not crash; return value is observable.
  EXPECT_FALSE(hdr_.read(nullptr, 0, Exiv2::littleEndian));

  // Boundary: non-null pointer but size 0 should also be handled.
  const Exiv2::byte dummy = 0;
  EXPECT_FALSE(hdr_.read(&dummy, 0, Exiv2::littleEndian));
}

TEST_F(Nikon3MnHeaderTest_2189, WriteReturnsCountConsistentWithIoGrowth_2189) {
  // Use in-memory IO as a real collaborator (no mocking of internal behavior).
  Exiv2::MemIo memIo;
  Exiv2::Internal::IoWrapper ioWrapper(memIo);

  const auto before = memIo.size();
  const auto written = hdr_.write(ioWrapper, Exiv2::littleEndian);
  const auto after = memIo.size();

  // Observable consistency check: reported written bytes match IO size delta.
  ASSERT_GE(after, before);
  EXPECT_EQ(written, static_cast<size_t>(after - before));
}

}  // namespace