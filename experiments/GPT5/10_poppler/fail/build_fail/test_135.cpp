// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
//
// Unit tests for BaseSeekInputStream::getPos (TEST_ID=135)
//
// File: Stream_getPos_tests_135.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "poppler/Stream.h"
#include "poppler/Object.h"

namespace {

class MemorySeekInputStream final : public BaseSeekInputStream {
public:
  MemorySeekInputStream(Goffset startA, bool limitedA, Goffset lengthA, Object &&dictA,
                        std::vector<unsigned char> dataA)
      : BaseSeekInputStream(startA, limitedA, lengthA, std::move(dictA)),
        data(std::move(dataA)),
        pos(0) {}

private:
  const Goffset currentPos() override { return pos; }

  void setCurrentPos(Goffset offset) override {
    // Clamp to [0, data.size()] for a stable, safe backing store.
    // (This is backing-stream behavior, not BaseSeekInputStream logic.)
    if (offset < 0) {
      pos = 0;
    } else {
      const auto maxPos = static_cast<Goffset>(data.size());
      pos = std::min(offset, maxPos);
    }
  }

  Goffset read(char *outBuf, Goffset size) override {
    if (size <= 0) {
      return 0;
    }
    const auto maxPos = static_cast<Goffset>(data.size());
    if (pos >= maxPos) {
      return 0;
    }

    const Goffset avail = maxPos - pos;
    const Goffset n = std::min(size, avail);

    std::copy_n(reinterpret_cast<const char *>(&data[static_cast<size_t>(pos)]),
                static_cast<size_t>(n), outBuf);
    pos += n;
    return n;
  }

  std::vector<unsigned char> data;
  Goffset pos;
};

static Object MakeNullDictObject() {
  Object o;
  // In Poppler, Object supports initNull(); keep it minimal.
  o.initNull();
  return o;
}

class BaseSeekInputStreamTest_135 : public ::testing::Test {
protected:
  static std::vector<unsigned char> MakeData(size_t n) {
    std::vector<unsigned char> v(n);
    for (size_t i = 0; i < n; ++i) {
      v[i] = static_cast<unsigned char>(i & 0xFF);
    }
    return v;
  }
};

} // namespace

TEST_F(BaseSeekInputStreamTest_135, InitialPosEqualsStart_135) {
  auto dict = MakeNullDictObject();
  const Goffset start = 0;
  const auto data = MakeData(16);

  MemorySeekInputStream s(start, /*limitedA=*/true, /*lengthA=*/static_cast<Goffset>(data.size()),
                          std::move(dict), data);

  EXPECT_EQ(s.getPos(), s.getStart());
}

TEST_F(BaseSeekInputStreamTest_135, GetPosAdvancesAfterGetChar_135) {
  auto dict = MakeNullDictObject();
  const auto data = MakeData(8);

  MemorySeekInputStream s(/*startA=*/0, /*limitedA=*/true,
                          /*lengthA=*/static_cast<Goffset>(data.size()), std::move(dict), data);

  const Goffset p0 = s.getPos();
  const int c = s.getChar();

  ASSERT_NE(c, EOF);
  EXPECT_EQ(s.getPos(), p0 + 1);
}

TEST_F(BaseSeekInputStreamTest_135, LookCharDoesNotAdvancePosition_135) {
  auto dict = MakeNullDictObject();
  const auto data = MakeData(8);

  MemorySeekInputStream s(/*startA=*/0, /*limitedA=*/true,
                          /*lengthA=*/static_cast<Goffset>(data.size()), std::move(dict), data);

  const Goffset p0 = s.getPos();
  const int c = s.lookChar();

  ASSERT_NE(c, EOF);
  EXPECT_EQ(s.getPos(), p0);

  // Consistency check: consuming afterwards should advance by 1.
  const int c2 = s.getChar();
  ASSERT_NE(c2, EOF);
  EXPECT_EQ(s.getPos(), p0 + 1);
  EXPECT_EQ(c2, c);
}

TEST_F(BaseSeekInputStreamTest_135, RewindRestoresStartPosition_135) {
  auto dict = MakeNullDictObject();
  const auto data = MakeData(10);

  MemorySeekInputStream s(/*startA=*/0, /*limitedA=*/true,
                          /*lengthA=*/static_cast<Goffset>(data.size()), std::move(dict), data);

  // Move forward a bit.
  ASSERT_NE(s.getChar(), EOF);
  ASSERT_NE(s.getChar(), EOF);
  ASSERT_NE(s.getChar(), EOF);
  EXPECT_EQ(s.getPos(), s.getStart() + 3);

  // Rewind should be observable via position.
  EXPECT_TRUE(s.rewind());
  EXPECT_EQ(s.getPos(), s.getStart());

  // And reading again should advance from start.
  ASSERT_NE(s.getChar(), EOF);
  EXPECT_EQ(s.getPos(), s.getStart() + 1);
}

TEST_F(BaseSeekInputStreamTest_135, SetPosToStartRestoresPosition_135) {
  auto dict = MakeNullDictObject();
  const auto data = MakeData(12);

  MemorySeekInputStream s(/*startA=*/0, /*limitedA=*/true,
                          /*lengthA=*/static_cast<Goffset>(data.size()), std::move(dict), data);

  ASSERT_NE(s.getChar(), EOF);
  ASSERT_NE(s.getChar(), EOF);
  EXPECT_EQ(s.getPos(), s.getStart() + 2);

  // Regardless of internal buffering, setting position to 0 from beginning
  // should make getPos observable as start.
  s.setPos(/*pos=*/0, /*dir=*/0);
  EXPECT_EQ(s.getPos(), s.getStart());

  // Next read advances from start again.
  ASSERT_NE(s.getChar(), EOF);
  EXPECT_EQ(s.getPos(), s.getStart() + 1);
}

TEST_F(BaseSeekInputStreamTest_135, GetPosDoesNotChangeAfterEOF_135) {
  auto dict = MakeNullDictObject();
  const auto data = MakeData(5);

  MemorySeekInputStream s(/*startA=*/0, /*limitedA=*/true,
                          /*lengthA=*/static_cast<Goffset>(data.size()), std::move(dict), data);

  // Consume all bytes.
  Goffset lastPos = s.getPos();
  for (size_t i = 0; i < data.size(); ++i) {
    const int c = s.getChar();
    ASSERT_NE(c, EOF);
    const Goffset now = s.getPos();
    EXPECT_EQ(now, lastPos + 1);
    lastPos = now;
  }

  // Now at end. First EOF:
  const Goffset beforeEof = s.getPos();
  EXPECT_EQ(s.getChar(), EOF);
  EXPECT_EQ(s.getPos(), beforeEof);

  // Repeated EOF should not move position either.
  EXPECT_EQ(s.getChar(), EOF);
  EXPECT_EQ(s.getPos(), beforeEof);
}

TEST_F(BaseSeekInputStreamTest_135, SetPosBeyondEndDoesNotCrashAndEOFs_135) {
  auto dict = MakeNullDictObject();
  const auto data = MakeData(6);

  MemorySeekInputStream s(/*startA=*/0, /*limitedA=*/true,
                          /*lengthA=*/static_cast<Goffset>(data.size()), std::move(dict), data);

  // Boundary: request a position well beyond stream length. We don't assume clamping
  // semantics for getPos; we only verify observable safe behavior: reading returns EOF.
  s.setPos(/*pos=*/static_cast<Goffset>(data.size() + 1000), /*dir=*/0);

  EXPECT_EQ(s.getChar(), EOF);
  EXPECT_EQ(s.lookChar(), EOF);
}