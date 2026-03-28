// TEST_ID 170
// File: base_mem_stream_getpos_test_170.cc

#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include "poppler/Object.h"
#include "poppler/Stream.h"

namespace {

using UCharMemStream = BaseMemStream<unsigned char>;

class BaseMemStreamTest_170 : public ::testing::Test {
protected:
  static std::unique_ptr<UCharMemStream> MakeStream(std::vector<unsigned char>& backing,
                                                    Goffset start,
                                                    Goffset length) {
    // Use a default Object and move it into the stream as the dict argument.
    Object dict;
    return std::make_unique<UCharMemStream>(backing.data(), start, length, std::move(dict));
  }
};

TEST_F(BaseMemStreamTest_170, RewindMakesGetPosEqualGetStart_170) {
  std::vector<unsigned char> buf(16);
  auto s = MakeStream(buf, /*start=*/3, /*length=*/7);

  // Regardless of initial state, rewind is expected to reset to the stream start.
  ASSERT_TRUE(s->rewind());
  EXPECT_EQ(s->getPos(), s->getStart());
}

TEST_F(BaseMemStreamTest_170, LookCharDoesNotAdvancePosition_170) {
  std::vector<unsigned char> buf = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15};
  auto s = MakeStream(buf, /*start=*/1, /*length=*/4);

  ASSERT_TRUE(s->rewind());
  const Goffset posBefore = s->getPos();

  (void)s->lookChar(); // may return EOF for empty streams; here length > 0
  EXPECT_EQ(s->getPos(), posBefore);
}

TEST_F(BaseMemStreamTest_170, GetCharAdvancesPositionOnSuccessfulRead_170) {
  std::vector<unsigned char> buf = {0x21, 0x22, 0x23, 0x24, 0x25};
  auto s = MakeStream(buf, /*start=*/0, /*length=*/5);

  ASSERT_TRUE(s->rewind());
  const Goffset posBefore = s->getPos();

  const int c = s->getChar();
  ASSERT_NE(c, EOF) << "Expected a successful read for non-empty stream";
  EXPECT_EQ(s->getPos(), posBefore + 1);
}

TEST_F(BaseMemStreamTest_170, ReadingToEndStopsAtStartPlusLength_170) {
  const Goffset start = 2;
  const Goffset length = 5;

  std::vector<unsigned char> buf(16);
  for (size_t i = 0; i < buf.size(); ++i) buf[i] = static_cast<unsigned char>(i);

  auto s = MakeStream(buf, start, length);
  ASSERT_TRUE(s->rewind());

  // Consume exactly 'length' bytes successfully.
  for (Goffset i = 0; i < length; ++i) {
    const Goffset before = s->getPos();
    const int c = s->getChar();
    ASSERT_NE(c, EOF) << "Expected EOF only after reading 'length' bytes";
    EXPECT_EQ(s->getPos(), before + 1);
  }

  // Now at end: position should not move after EOF.
  const Goffset endPos = s->getPos();
  EXPECT_EQ(endPos, s->getStart() + length);

  const int c2 = s->getChar();
  EXPECT_EQ(c2, EOF);

  EXPECT_EQ(s->getPos(), endPos);
}

TEST_F(BaseMemStreamTest_170, SetPosMovesGetPosAndSubsequentReadReflectsNewPosition_170) {
  // Use distinct values so we can sanity-check that seeking changes what is read,
  // without depending on any private/internal state.
  std::vector<unsigned char> buf = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7};
  const Goffset start = 1;
  const Goffset length = 6; // valid region: indices [1..6] inclusive as bytes, end at pos start+length

  auto s = MakeStream(buf, start, length);
  ASSERT_TRUE(s->rewind());

  const Goffset target = start + 3;
  s->setPos(target, /*dir=*/0);

  EXPECT_EQ(s->getPos(), target);

  const int c = s->getChar();
  // We only assert it's not EOF and that position advanced from the new location.
  ASSERT_NE(c, EOF);
  EXPECT_EQ(s->getPos(), target + 1);
}

TEST_F(BaseMemStreamTest_170, SetPosOutOfRangeDoesNotMoveGetPosOutsideStartAndEnd_170) {
  std::vector<unsigned char> buf(10, 0x7F);
  const Goffset start = 2;
  const Goffset length = 5;
  auto s = MakeStream(buf, start, length);

  ASSERT_TRUE(s->rewind());

  // Try a clearly out-of-range position.
  s->setPos(start + length + 100, /*dir=*/0);

  // Observable safety property: position should remain within [start, start+length].
  // (We do not assume whether it clamps to end or leaves unchanged, only that it stays valid.)
  EXPECT_GE(s->getPos(), s->getStart());
  EXPECT_LE(s->getPos(), s->getStart() + length);

  // Also try a negative seek (if supported by Goffset being signed).
  s->setPos(static_cast<Goffset>(-1), /*dir=*/0);
  EXPECT_GE(s->getPos(), s->getStart());
  EXPECT_LE(s->getPos(), s->getStart() + length);
}

} // namespace