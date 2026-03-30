// SPDX-License-Identifier: GPL-2.0-or-later
// TestProjects/poppler/poppler/Stream_FilterStream_getPos_139_test.cpp

#include <gtest/gtest.h>

#include "Stream.h"

namespace {

// A simple external collaborator (underlying Stream) that lets us observe calls to getPos()
// without relying on any private/internal state of FilterStream.
class CountingPosStream final : public Stream {
public:
  explicit CountingPosStream(Goffset pos) : pos_(pos) {}

  Goffset getPos() override {
    ++getPosCalls_;
    return pos_;
  }

  void setPosValue(Goffset pos) { pos_ = pos; }
  int getPosCalls() const { return getPosCalls_; }

private:
  Goffset pos_{0};
  int getPosCalls_{0};
};

class FilterStreamTest_139 : public ::testing::Test {};

} // namespace

TEST_F(FilterStreamTest_139, GetPosDelegatesAndReturnsSameValue_139) {
  auto *base = new CountingPosStream(static_cast<Goffset>(123));
  FilterStream filter(base);

  const Goffset p = filter.getPos();

  EXPECT_EQ(p, static_cast<Goffset>(123));
  EXPECT_EQ(base->getPosCalls(), 1);
}

TEST_F(FilterStreamTest_139, GetPosCalledMultipleTimesDelegatesEachTime_139) {
  auto *base = new CountingPosStream(static_cast<Goffset>(7));
  FilterStream filter(base);

  EXPECT_EQ(filter.getPos(), static_cast<Goffset>(7));
  EXPECT_EQ(filter.getPos(), static_cast<Goffset>(7));
  EXPECT_EQ(filter.getPos(), static_cast<Goffset>(7));

  EXPECT_EQ(base->getPosCalls(), 3);
}

TEST_F(FilterStreamTest_139, GetPosBoundaryZero_139) {
  auto *base = new CountingPosStream(static_cast<Goffset>(0));
  FilterStream filter(base);

  EXPECT_EQ(filter.getPos(), static_cast<Goffset>(0));
  EXPECT_EQ(base->getPosCalls(), 1);
}

TEST_F(FilterStreamTest_139, GetPosBoundaryNegativeAndLargeValues_139) {
  auto *base = new CountingPosStream(static_cast<Goffset>(-1));
  FilterStream filter(base);

  EXPECT_EQ(filter.getPos(), static_cast<Goffset>(-1));
  EXPECT_EQ(base->getPosCalls(), 1);

  // Also check a large positive value (boundary-ish, without assuming Goffset width).
  const Goffset large = static_cast<Goffset>(1) << 30;
  base->setPosValue(large);

  EXPECT_EQ(filter.getPos(), large);
  EXPECT_EQ(base->getPosCalls(), 2);
}