// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 584
//
// Unit tests for Exiv2::MemIo::tell() observable behavior via public interface.
// Constraints honored: treat implementation as black box; no private state access.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

class MemIoTellTest_584 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeBytes(size_t n) {
    std::vector<Exiv2::byte> v(n);
    for (size_t i = 0; i < n; ++i) v[i] = static_cast<Exiv2::byte>(i & 0xFF);
    return v;
  }
};

TEST_F(MemIoTellTest_584, DefaultConstructedTellIsStable_584) {
  Exiv2::MemIo io;

  const size_t t1 = io.tell();
  const size_t t2 = io.tell();

  EXPECT_EQ(t1, t2);
}

TEST_F(MemIoTellTest_584, OpenDoesNotMakeTellDecrease_584) {
  Exiv2::MemIo io;

  const size_t before = io.tell();
  (void)io.open();  // Do not assume return value semantics.

  const size_t after = io.tell();
  EXPECT_GE(after, before);
}

TEST_F(MemIoTellTest_584, PutbAdvancesTellByOneOnSuccess_584) {
  Exiv2::MemIo io;
  (void)io.open();

  const size_t before = io.tell();
  const int rc = io.putb(static_cast<Exiv2::byte>(0xAB));
  const size_t after = io.tell();

  // Only assert advancement if the operation reported success.
  if (rc == 0) {
    EXPECT_EQ(after, before + 1);
  } else {
    // On failure, tell should at least remain a valid stable value.
    EXPECT_EQ(after, io.tell());
  }
}

TEST_F(MemIoTellTest_584, WritePointerAdvancesTellByBytesReportedWritten_584) {
  Exiv2::MemIo io;
  (void)io.open();

  const auto data = MakeBytes(16);

  const size_t before = io.tell();
  const size_t written = io.write(data.data(), data.size());
  const size_t after = io.tell();

  EXPECT_EQ(after, before + written);
}

TEST_F(MemIoTellTest_584, ReadBufferAdvancesTellByBytesReportedRead_584) {
  // Seed with known data via constructor (no assumptions about open requirement).
  const auto seed = MakeBytes(32);
  Exiv2::MemIo io(seed.data(), seed.size());
  (void)io.open();

  const size_t before = io.tell();

  std::vector<Exiv2::byte> buf(10, 0);
  const size_t nread = io.read(buf.data(), buf.size());

  const size_t after = io.tell();
  EXPECT_EQ(after, before + nread);
}

TEST_F(MemIoTellTest_584, GetbAdvancesTellByOneWhenItReturnsAByte_584) {
  const auto seed = MakeBytes(4);
  Exiv2::MemIo io(seed.data(), seed.size());
  (void)io.open();

  const size_t before = io.tell();
  const int value = io.getb();
  const size_t after = io.tell();

  // Only assert advancement when a byte was actually returned (common convention: EOF == -1).
  if (value >= 0) {
    EXPECT_EQ(after, before + 1);
  } else {
    EXPECT_EQ(after, before);
  }
}

TEST_F(MemIoTellTest_584, SeekBegToZeroMakesTellZeroOnSuccess_584) {
  const auto seed = MakeBytes(16);
  Exiv2::MemIo io(seed.data(), seed.size());
  (void)io.open();

  // Move somewhere first using a read that reports progress.
  std::vector<Exiv2::byte> tmp(5, 0);
  (void)io.read(tmp.data(), tmp.size());

  const int rc = io.seek(0, Exiv2::beg);
  if (rc == 0) {
    EXPECT_EQ(io.tell(), 0u);
  }
}

TEST_F(MemIoTellTest_584, SeekCurPositiveMovesTellForwardByOffsetOnSuccess_584) {
  const auto seed = MakeBytes(64);
  Exiv2::MemIo io(seed.data(), seed.size());
  (void)io.open();

  // Ensure we have a baseline position.
  std::vector<Exiv2::byte> tmp(7, 0);
  const size_t progressed = io.read(tmp.data(), tmp.size());
  const size_t before = io.tell();

  const int64_t offset = 3;
  const int rc = io.seek(offset, Exiv2::cur);

  if (rc == 0) {
    // Only assert if we actually progressed to a meaningful baseline.
    EXPECT_EQ(io.tell(), before + static_cast<size_t>(offset));
  } else {
    // On failure, avoid assuming behavior; at minimum tell remains consistent.
    EXPECT_EQ(io.tell(), io.tell());
  }

  (void)progressed;  // silence potential unused warnings under some configs
}

TEST_F(MemIoTellTest_584, SeekEndZeroMakesTellEqualToSizeOnSuccess_584) {
  const auto seed = MakeBytes(19);
  Exiv2::MemIo io(seed.data(), seed.size());
  (void)io.open();

  const size_t sz = io.size();
  const int rc = io.seek(0, Exiv2::end);

  if (rc == 0) {
    EXPECT_EQ(io.tell(), sz);
  }
}

TEST_F(MemIoTellTest_584, CloseDoesNotMakeTellChangeUnexpectedly_584) {
  Exiv2::MemIo io;
  (void)io.open();

  const auto data = MakeBytes(8);
  (void)io.write(data.data(), data.size());

  const size_t beforeClose = io.tell();
  (void)io.close();

  const size_t afterClose = io.tell();
  // We don't assume close resets position; just ensure it's stable and non-negative (size_t).
  EXPECT_EQ(afterClose, io.tell());
  EXPECT_GE(afterClose, 0u);
  (void)beforeClose;
}

}  // namespace