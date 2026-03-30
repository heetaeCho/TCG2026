// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 126
//
// Unit tests for BaseStream::getBaseStream()
// File: ./TestProjects/poppler/poppler/Stream.h

#include <gtest/gtest.h>

#include "poppler/Stream.h"

namespace {

// A minimal concrete BaseStream to allow instantiation in tests.
// This is NOT re-implementing BaseStream logic; it only satisfies abstract
// interface requirements so we can exercise getBaseStream() as a black box.
class TestBaseStream_126 final : public BaseStream {
public:
  explicit TestBaseStream_126(Object &&dictA = Object(), Goffset lengthA = 0)
      : BaseStream(std::move(dictA), lengthA) {}

  // Stream interface (minimal no-op / EOF behavior)
  void reset() override {}
  void close() override {}
  int getChar() override { return EOF; }
  int lookChar() override { return EOF; }
  int getPos() override { return 0; }
  void setPos(Goffset pos, int dir) override {
    // delegate to BaseStream override (exercising its public interface)
    BaseStream::setPos(pos, dir);
  }

  // Some Poppler builds may require additional overrides (e.g., getStart/length),
  // but BaseStream already provides these as virtual non-pure in Stream.h.
};

class BaseStreamGetBaseStreamTest_126 : public ::testing::Test {};

} // namespace

TEST_F(BaseStreamGetBaseStreamTest_126, ReturnsThisPointer_126) {
  TestBaseStream_126 s;
  BaseStream *bs = s.getBaseStream();
  EXPECT_EQ(bs, &s);
}

TEST_F(BaseStreamGetBaseStreamTest_126, WorksViaStreamBasePointer_126) {
  TestBaseStream_126 s;
  Stream *asStream = &s;

  BaseStream *bs = asStream->getBaseStream();
  EXPECT_EQ(bs, &s);
}

TEST_F(BaseStreamGetBaseStreamTest_126, IdempotentAcrossCalls_126) {
  TestBaseStream_126 s;

  BaseStream *first = s.getBaseStream();
  BaseStream *second = s.getBaseStream();
  EXPECT_EQ(first, second);
  EXPECT_EQ(first, &s);
}

TEST_F(BaseStreamGetBaseStreamTest_126, DifferentInstancesReturnDifferentPointers_126) {
  TestBaseStream_126 a;
  TestBaseStream_126 b;

  EXPECT_EQ(a.getBaseStream(), &a);
  EXPECT_EQ(b.getBaseStream(), &b);
  EXPECT_NE(a.getBaseStream(), b.getBaseStream());
}