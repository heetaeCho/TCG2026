// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 1492
//
// File: test_samsung_mn_header_1492.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>

// Internal headers (part of the codebase under test)
#include "iowrapper.hpp"
#include "makernote_int.hpp"

namespace {

class SamsungMnHeaderTest_1492 : public ::testing::Test {
 protected:
  Exiv2::MemIo memIo_;
  Exiv2::Internal::IoWrapper ioWrapper_{memIo_};
};

TEST_F(SamsungMnHeaderTest_1492, WriteWithLittleEndianReturnsZero_1492) {
  const Exiv2::Internal::SamsungMnHeader hdr;

  const size_t written = hdr.write(ioWrapper_, Exiv2::littleEndian);

  EXPECT_EQ(0u, written);
}

TEST_F(SamsungMnHeaderTest_1492, WriteWithBigEndianReturnsZero_1492) {
  const Exiv2::Internal::SamsungMnHeader hdr;

  const size_t written = hdr.write(ioWrapper_, Exiv2::bigEndian);

  EXPECT_EQ(0u, written);
}

TEST_F(SamsungMnHeaderTest_1492, WriteCanBeCalledRepeatedlyAndStaysZero_1492) {
  const Exiv2::Internal::SamsungMnHeader hdr;

  EXPECT_EQ(0u, hdr.write(ioWrapper_, Exiv2::littleEndian));
  EXPECT_EQ(0u, hdr.write(ioWrapper_, Exiv2::littleEndian));
  EXPECT_EQ(0u, hdr.write(ioWrapper_, Exiv2::bigEndian));
}

}  // namespace