// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_makernote_int_nikon3mnheader_write_1471.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>

// Internal headers from the codebase under test
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::DataBuf;

using Exiv2::Internal::IoWrapper;
using Exiv2::Internal::Nikon3MnHeader;
using Exiv2::Internal::TiffHeader;

class Nikon3MnHeaderTest_1471 : public ::testing::Test {
 protected:
  Nikon3MnHeader header_{};

  static IoWrapper MakeWrapper(Exiv2::BasicIo& io) {
    // The header pointer/size and OffsetWriter are not needed for these tests;
    // we only observe bytes written through BasicIo.
    return IoWrapper(io, /*pHeader=*/nullptr, /*size=*/0, /*pow=*/nullptr);
  }

  static size_t CurrentSize(Exiv2::BasicIo& io) {
    // BasicIo::size() exists on Exiv2 BasicIo implementations (e.g., MemIo).
    return static_cast<size_t>(io.size());
  }
};

TEST_F(Nikon3MnHeaderTest_1471, WriteLittleEndian_WritesExpectedByteCount_1471) {
  Exiv2::MemIo mem;
  auto wrapper = MakeWrapper(mem);

  const ByteOrder bo = Exiv2::littleEndian;

  // Expected size is observable via the TiffHeader public interface (no internal inference).
  TiffHeader th(bo);
  const DataBuf tiffBuf = th.write();
  const size_t expected = 10u + tiffBuf.size();

  const size_t before = CurrentSize(mem);
  const size_t written = header_.write(wrapper, bo);
  const size_t after = CurrentSize(mem);

  EXPECT_EQ(written, expected);
  EXPECT_EQ(after - before, written);
  EXPECT_GT(written, 0u);
}

TEST_F(Nikon3MnHeaderTest_1471, WriteBigEndian_WritesExpectedByteCount_1471) {
  Exiv2::MemIo mem;
  auto wrapper = MakeWrapper(mem);

  const ByteOrder bo = Exiv2::bigEndian;

  TiffHeader th(bo);
  const DataBuf tiffBuf = th.write();
  const size_t expected = 10u + tiffBuf.size();

  const size_t before = CurrentSize(mem);
  const size_t written = header_.write(wrapper, bo);
  const size_t after = CurrentSize(mem);

  EXPECT_EQ(written, expected);
  EXPECT_EQ(after - before, written);
  EXPECT_GT(written, 0u);
}

TEST_F(Nikon3MnHeaderTest_1471, WriteTwice_AppendsBytesAndReturnsConsistentSizes_1471) {
  Exiv2::MemIo mem;
  auto wrapper = MakeWrapper(mem);

  const ByteOrder bo = Exiv2::littleEndian;

  TiffHeader th(bo);
  const DataBuf tiffBuf = th.write();
  const size_t expectedSingle = 10u + tiffBuf.size();

  const size_t before = CurrentSize(mem);

  const size_t written1 = header_.write(wrapper, bo);
  const size_t mid = CurrentSize(mem);

  const size_t written2 = header_.write(wrapper, bo);
  const size_t after = CurrentSize(mem);

  EXPECT_EQ(written1, expectedSingle);
  EXPECT_EQ(written2, expectedSingle);

  EXPECT_EQ(mid - before, written1);
  EXPECT_EQ(after - mid, written2);
  EXPECT_EQ(after - before, written1 + written2);
}

}  // namespace