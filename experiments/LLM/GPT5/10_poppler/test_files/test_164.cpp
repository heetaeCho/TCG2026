// TEST_ID 164
#include <gtest/gtest.h>

#include <memory>
#include <typeinfo>

#include "poppler/Object.h"
#include "poppler/Stream.h"

namespace {

using UCharMemStream = BaseMemStream<unsigned char>;

class BaseMemStreamTest_164 : public ::testing::Test {
protected:
  static Object MakeNullDict_164() { return Object::null(); }
};

TEST_F(BaseMemStreamTest_164, CopyReturnsNonNullAndSameDynamicType_164) {
  unsigned char data[] = {'A', 'B', 'C'};
  auto s = std::make_unique<UCharMemStream>(data, /*startA=*/0, /*lengthA=*/3, MakeNullDict_164());

  std::unique_ptr<BaseStream> c = s->copy();
  ASSERT_NE(c, nullptr);

  // Observable: copy() should return a usable BaseStream; for BaseMemStream it should be the same concrete type.
  auto *typed = dynamic_cast<UCharMemStream *>(c.get());
  EXPECT_NE(typed, nullptr);
}

TEST_F(BaseMemStreamTest_164, CopyPreservesStartLengthAndKind_164) {
  unsigned char data[] = {'A', 'B', 'C', 'D'};
  auto s = std::make_unique<UCharMemStream>(data, /*startA=*/1, /*lengthA=*/2, MakeNullDict_164());

  const auto origStart = s->getStart();
  const auto origLen = s->getLength();
  const auto origKind = s->getKind();

  std::unique_ptr<BaseStream> c = s->copy();
  ASSERT_NE(c, nullptr);

  EXPECT_EQ(c->getStart(), origStart);
  EXPECT_EQ(c->getLength(), origLen);
  EXPECT_EQ(c->getKind(), origKind);
}

TEST_F(BaseMemStreamTest_164, CopyHasIndependentReadPosition_164) {
  unsigned char data[] = {'A', 'B', 'C'};
  auto s = std::make_unique<UCharMemStream>(data, /*startA=*/0, /*lengthA=*/3, MakeNullDict_164());

  // Prime: verify initial observable state.
  const int origLook0 = s->lookChar();
  const Goffset origPos0 = s->getPos();

  std::unique_ptr<BaseStream> c = s->copy();
  ASSERT_NE(c, nullptr);

  // Before consuming, copy should observe the same next char and position as original had at copy time.
  EXPECT_EQ(c->lookChar(), origLook0);
  EXPECT_EQ(c->getPos(), origPos0);

  // Consume one char from original.
  const int origCh1 = s->getChar();
  const Goffset origPos1 = s->getPos();

  // Copy should still be at its own initial position and see its own next char unchanged.
  EXPECT_EQ(c->getPos(), origPos0);
  EXPECT_EQ(c->lookChar(), origLook0);

  // Original position should have advanced (if any advancement is observable through getPos()).
  EXPECT_NE(origPos1, origPos0);
  (void)origCh1; // value itself is not asserted here (implementation-defined EOF conventions), only independence.
}

TEST_F(BaseMemStreamTest_164, CopyReadsSameSequenceFromSameStart_164) {
  unsigned char data[] = {'X', 'Y', 'Z'};
  auto s = std::make_unique<UCharMemStream>(data, /*startA=*/0, /*lengthA=*/3, MakeNullDict_164());

  std::unique_ptr<BaseStream> c = s->copy();
  ASSERT_NE(c, nullptr);

  // Read a small sequence from both streams; they should match when starting from the same state.
  const int s0 = s->getChar();
  const int c0 = c->getChar();
  EXPECT_EQ(c0, s0);

  const int s1 = s->getChar();
  const int c1 = c->getChar();
  EXPECT_EQ(c1, s1);

  const int s2 = s->getChar();
  const int c2 = c->getChar();
  EXPECT_EQ(c2, s2);
}

TEST_F(BaseMemStreamTest_164, CopyRespectsNonZeroStart_164) {
  unsigned char data[] = {'A', 'B', 'C', 'D'};
  auto s = std::make_unique<UCharMemStream>(data, /*startA=*/2, /*lengthA=*/2, MakeNullDict_164());

  // At this start, first char should match between original and its copy.
  const int origFirst = s->lookChar();

  std::unique_ptr<BaseStream> c = s->copy();
  ASSERT_NE(c, nullptr);

  EXPECT_EQ(c->lookChar(), origFirst);

  // And consuming from both should match.
  EXPECT_EQ(c->getChar(), s->getChar());
  EXPECT_EQ(c->getChar(), s->getChar());
}

TEST_F(BaseMemStreamTest_164, CopyOnEmptyLengthIsUsableAndConsistent_164) {
  // Boundary: length 0. Use a null buffer to avoid assuming dereference behavior.
  unsigned char *nullBuf = nullptr;
  auto s = std::make_unique<UCharMemStream>(nullBuf, /*startA=*/0, /*lengthA=*/0, MakeNullDict_164());

  std::unique_ptr<BaseStream> c = s->copy();
  ASSERT_NE(c, nullptr);

  // Observable consistency: look/get should behave the same on both streams for empty content.
  EXPECT_EQ(c->lookChar(), s->lookChar());
  EXPECT_EQ(c->getChar(), s->getChar());
}

TEST_F(BaseMemStreamTest_164, MultipleCopiesAreIndependentFromEachOther_164) {
  unsigned char data[] = {'Q', 'W', 'E'};
  auto s = std::make_unique<UCharMemStream>(data, /*startA=*/0, /*lengthA=*/3, MakeNullDict_164());

  std::unique_ptr<BaseStream> c1 = s->copy();
  std::unique_ptr<BaseStream> c2 = s->copy();
  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);

  // Advance c1 only.
  const int c1_first = c1->getChar();

  // c2 should still be at the beginning and see the initial char.
  EXPECT_EQ(c2->lookChar(), c1_first);

  // Original should still be independent as well.
  EXPECT_EQ(s->lookChar(), c1_first);
}

} // namespace