// SPDX-License-Identifier: GPL-2.0-or-later
// File: BaseSeekInputStream_lookChar_tests.cpp
//
// Unit tests for BaseSeekInputStream::lookChar()
// TEST_ID: 134

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <utility>
#include <vector>

#include "Stream.h"

// A simple in-memory seekable input stream.
// We only override the documented virtual hooks (read/currentPos/setCurrentPos)
// to provide an external data source for BaseSeekInputStream's buffering logic.
class MemSeekInputStream final : public BaseSeekInputStream {
public:
  MemSeekInputStream(std::vector<unsigned char> data, bool limited, Goffset length)
      : BaseSeekInputStream(/*startA=*/0, /*limitedA=*/limited, /*lengthA=*/length, std::move(makeDictObject())),
        data_(std::move(data)) {}

  int readCalls() const { return readCalls_; }

private:
  static Object makeDictObject() {
    // BaseSeekInputStream takes an Object rvalue "dictA".
    // We keep this minimal: default-constructed Object is sufficient for these tests.
    Object obj;
    return obj;
  }

  Goffset currentPos() override { return pos_; }
  void setCurrentPos(Goffset offset) override { pos_ = offset; }

  Goffset read(char *buf, Goffset size) override {
    ++readCalls_;
    if (size <= 0) {
      return 0;
    }
    if (pos_ < 0) {
      return 0;
    }
    const std::size_t upos = static_cast<std::size_t>(pos_);
    if (upos >= data_.size()) {
      return 0;
    }

    const std::size_t remaining = data_.size() - upos;
    const std::size_t want = static_cast<std::size_t>(size);
    const std::size_t n = std::min(remaining, want);

    if (n > 0) {
      std::memcpy(buf, data_.data() + upos, n);
      pos_ += static_cast<Goffset>(n);
    }
    return static_cast<Goffset>(n);
  }

  std::vector<unsigned char> data_;
  Goffset pos_{0};
  int readCalls_{0};
};

class BaseSeekInputStreamLookCharTest_134 : public ::testing::Test {};

TEST_F(BaseSeekInputStreamLookCharTest_134, ReturnsEofOnEmptyStream_134) {
  MemSeekInputStream s(/*data=*/{}, /*limited=*/false, /*length=*/0);

  EXPECT_EQ(s.lookChar(), EOF);
  EXPECT_EQ(s.getChar(), EOF);
}

TEST_F(BaseSeekInputStreamLookCharTest_134, ReturnsFirstByteWithoutConsuming_134) {
  MemSeekInputStream s(/*data=*/{'A', 'B', 'C'}, /*limited=*/false, /*length=*/0);

  const Goffset p0 = s.getPos();

  EXPECT_EQ(s.lookChar(), static_cast<int>('A'));
  EXPECT_EQ(s.lookChar(), static_cast<int>('A')) << "lookChar() should not consume input";
  EXPECT_EQ(s.getPos(), p0) << "Position should not change after lookChar()";

  EXPECT_EQ(s.getChar(), static_cast<int>('A'));
  EXPECT_NE(s.getPos(), p0) << "Position should advance after getChar()";

  EXPECT_EQ(s.lookChar(), static_cast<int>('B'));
  EXPECT_EQ(s.getChar(), static_cast<int>('B'));
  EXPECT_EQ(s.lookChar(), static_cast<int>('C'));
  EXPECT_EQ(s.getChar(), static_cast<int>('C'));
  EXPECT_EQ(s.lookChar(), EOF);
}

TEST_F(BaseSeekInputStreamLookCharTest_134, ReturnsUnsignedByteValuesIncluding0x00And0xFF_134) {
  MemSeekInputStream s(/*data=*/{0xFFu, 0x00u, 0x7Fu}, /*limited=*/false, /*length=*/0);

  EXPECT_EQ(s.lookChar(), 0xFF) << "lookChar() should return (*bufPtr & 0xff) and not treat 0xFF as EOF";
  EXPECT_EQ(s.getChar(), 0xFF);

  EXPECT_EQ(s.lookChar(), 0x00);
  EXPECT_EQ(s.getChar(), 0x00);

  EXPECT_EQ(s.lookChar(), 0x7F);
  EXPECT_EQ(s.getChar(), 0x7F);

  EXPECT_EQ(s.lookChar(), EOF);
}

TEST_F(BaseSeekInputStreamLookCharTest_134, LookCharTriggersUnderlyingReadWhenBufferIsEmpty_134) {
  MemSeekInputStream s(/*data=*/{'Z'}, /*limited=*/false, /*length=*/0);

  // Before any operation, no reads should have occurred.
  EXPECT_EQ(s.readCalls(), 0);

  // First lookChar() should force a buffer fill from the underlying read().
  const int c = s.lookChar();
  EXPECT_EQ(c, static_cast<int>('Z'));
  EXPECT_GE(s.readCalls(), 1);

  // Repeated lookChar() should keep returning the same byte (no consumption).
  EXPECT_EQ(s.lookChar(), static_cast<int>('Z'));
}

TEST_F(BaseSeekInputStreamLookCharTest_134, LimitedZeroLengthAlwaysEof_134) {
  // Boundary: limited stream with length 0 should have no readable content.
  MemSeekInputStream s(/*data=*/{'X', 'Y'}, /*limited=*/true, /*length=*/0);

  EXPECT_EQ(s.lookChar(), EOF);
  EXPECT_EQ(s.getChar(), EOF);
}