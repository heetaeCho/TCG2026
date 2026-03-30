// BaseMemStream_getUnfilteredChar_174_test.cpp
// The TEST_ID is 174

#include <gtest/gtest.h>

#include "Stream.h"   // poppler/Stream.h in this project
#include "Object.h"   // for Object / objNull

namespace {

// A small controllable subclass so we can observe the *external* interaction:
// BaseMemStream::getUnfilteredChar() should call virtual getChar() and return its result.
class TestMemStream_174 final : public BaseMemStream<unsigned char> {
public:
  TestMemStream_174(unsigned char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
      : BaseMemStream<unsigned char>(bufA, startA, lengthA, std::move(dictA)) {}

  int getChar() override {
    ++getCharCalls;
    return nextReturn;
  }

  int getCharCalls = 0;
  int nextReturn = 0;
};

class BaseMemStreamGetUnfilteredCharTest_174 : public ::testing::Test {
protected:
  static Object makeNullDict() {
    // Typical Poppler pattern: Object constructed as null.
    return Object(objNull);
  }

  unsigned char buf[4] = {0x01, 0x02, 0x03, 0x04};
};

} // namespace

TEST_F(BaseMemStreamGetUnfilteredCharTest_174, ReturnsExactlyWhatGetCharReturns_174) {
  TestMemStream_174 s(buf, /*startA=*/0, /*lengthA=*/4, makeNullDict());
  s.nextReturn = 42;

  const int ch = s.getUnfilteredChar();

  EXPECT_EQ(ch, 42);
  EXPECT_EQ(s.getCharCalls, 1);
}

TEST_F(BaseMemStreamGetUnfilteredCharTest_174, MultipleCallsDelegateEachTime_174) {
  TestMemStream_174 s(buf, /*startA=*/0, /*lengthA=*/4, makeNullDict());

  s.nextReturn = 'A';
  EXPECT_EQ(s.getUnfilteredChar(), 'A');
  EXPECT_EQ(s.getCharCalls, 1);

  s.nextReturn = 'B';
  EXPECT_EQ(s.getUnfilteredChar(), 'B');
  EXPECT_EQ(s.getCharCalls, 2);
}

TEST_F(BaseMemStreamGetUnfilteredCharTest_174, PropagatesEofOrErrorCodeFromGetChar_174) {
  TestMemStream_174 s(buf, /*startA=*/0, /*lengthA=*/4, makeNullDict());

  // Many Poppler stream APIs use EOF == -1 for end-of-stream.
  s.nextReturn = -1;

  EXPECT_EQ(s.getUnfilteredChar(), -1);
  EXPECT_EQ(s.getCharCalls, 1);
}