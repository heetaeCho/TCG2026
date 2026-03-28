// TEST_ID: 171
// File: BaseMemStream_setPos_171_test.cpp

#include <gtest/gtest.h>

#include <vector>
#include <utility>

// Poppler headers
#include "poppler/Stream.h"
#include "poppler/Object.h"

namespace {

class BaseMemStreamTest_171 : public ::testing::Test {
protected:
  using Byte = unsigned char;

  // Helper to create a stream backed by a buffer large enough to address [0..start+length]
  std::unique_ptr<BaseMemStream<Byte>> makeStream(Goffset start, Goffset length) {
    // Ensure buffer is large enough for indices up to (start + length) and a bit extra.
    const auto totalSize = static_cast<size_t>(start + length + 8);
    buf_.resize(totalSize);

    // Fill with a recognizable pattern.
    for (size_t i = 0; i < buf_.size(); ++i) {
      buf_[i] = static_cast<Byte>(i & 0xFF);
    }

    Object dict; // Default-constructed dict is acceptable as an rvalue for BaseStream.
    auto s = std::make_unique<BaseMemStream<Byte>>(buf_.data(), start, length, std::move(dict));

    // Put the stream in a known position if rewind is supported.
    // (We don't assume constructor behavior; rewind() is part of the public interface.)
    s->rewind();
    return s;
  }

  std::vector<Byte> buf_;
};

TEST_F(BaseMemStreamTest_171, SetPos_DirNonNegative_SetsExactPositionWithinRange_171) {
  const Goffset start = 2;
  const Goffset length = 5;
  auto s = makeStream(start, length);

  const Goffset target = start + 3; // within [start, start+length]
  s->setPos(target, /*dir=*/0);

  EXPECT_EQ(s->getPos(), target);

  // Observable effect: lookChar/getChar should reflect the new position.
  const int looked = s->lookChar();
  ASSERT_NE(looked, EOF);
  EXPECT_EQ(looked, static_cast<int>(buf_[static_cast<size_t>(target)]));

  const int got = s->getChar();
  ASSERT_NE(got, EOF);
  EXPECT_EQ(got, static_cast<int>(buf_[static_cast<size_t>(target)]));

  // After consuming one char, position should advance by 1 (observable via getPos()).
  EXPECT_EQ(s->getPos(), target + 1);
}

TEST_F(BaseMemStreamTest_171, SetPos_DirNonNegative_ClampsBelowStartToStart_171) {
  const Goffset start = 4;
  const Goffset length = 6;
  auto s = makeStream(start, length);

  s->setPos(start - 100, /*dir=*/0);

  EXPECT_EQ(s->getPos(), start);

  const int got = s->getChar();
  ASSERT_NE(got, EOF);
  EXPECT_EQ(got, static_cast<int>(buf_[static_cast<size_t>(start)]));
}

TEST_F(BaseMemStreamTest_171, SetPos_DirNonNegative_ClampsAboveEndToEnd_171) {
  const Goffset start = 3;
  const Goffset length = 4;
  auto s = makeStream(start, length);

  const Goffset end = start + length;
  s->setPos(end + 100, /*dir=*/0);

  EXPECT_EQ(s->getPos(), end);

  // At end position, the stream should be at EOF when reading/peeking.
  EXPECT_EQ(s->lookChar(), EOF);
  EXPECT_EQ(s->getChar(), EOF);

  // We avoid asserting getPos() after EOF reads (implementation-dependent).
}

TEST_F(BaseMemStreamTest_171, SetPos_DirNegative_Pos0MovesToEnd_171) {
  const Goffset start = 1;
  const Goffset length = 7;
  auto s = makeStream(start, length);

  const Goffset end = start + length;
  s->setPos(/*pos=*/0, /*dir=*/-1);

  EXPECT_EQ(s->getPos(), end);
  EXPECT_EQ(s->lookChar(), EOF);
  EXPECT_EQ(s->getChar(), EOF);
}

TEST_F(BaseMemStreamTest_171, SetPos_DirNegative_Pos1MovesToLastByte_171) {
  const Goffset start = 2;
  const Goffset length = 6;
  auto s = makeStream(start, length);

  // With dir < 0, setPos(1) should land on the last valid byte (one before end).
  const Goffset expected = start + length - 1;
  s->setPos(/*pos=*/1, /*dir=*/-1);

  EXPECT_EQ(s->getPos(), expected);

  const int looked = s->lookChar();
  ASSERT_NE(looked, EOF);
  EXPECT_EQ(looked, static_cast<int>(buf_[static_cast<size_t>(expected)]));

  const int got = s->getChar();
  ASSERT_NE(got, EOF);
  EXPECT_EQ(got, static_cast<int>(buf_[static_cast<size_t>(expected)]));
}

TEST_F(BaseMemStreamTest_171, SetPos_DirNegative_ClampsPastStartAndPastEnd_171) {
  const Goffset start = 5;
  const Goffset length = 3;
  auto s = makeStream(start, length);

  // Case 1: a very large pos with dir < 0 yields i far below start -> should clamp to start.
  s->setPos(/*pos=*/1000, /*dir=*/-1);
  EXPECT_EQ(s->getPos(), start);

  // Case 2: negative pos with dir < 0 yields i far above end -> should clamp to end.
  const Goffset end = start + length;
  s->setPos(/*pos=*/-100, /*dir=*/-1);
  EXPECT_EQ(s->getPos(), end);
  EXPECT_EQ(s->lookChar(), EOF);
}

} // namespace