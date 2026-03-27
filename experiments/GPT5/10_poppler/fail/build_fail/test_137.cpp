// © 2026
// Unit tests for BaseSeekInputStream::getUnfilteredChar
// File: base_seek_input_stream_get_unfiltered_char_137_test.cc

#include <gtest/gtest.h>

#include "poppler/Stream.h"
#include "poppler/Object.h"

namespace {

class TestSeekInputStream_137 final : public BaseSeekInputStream {
public:
  TestSeekInputStream_137()
      : BaseSeekInputStream(/*startA=*/0,
                            /*limitedA=*/false,
                            /*lengthA=*/0,
                            /*dictA=*/Object()) {}

  void setNextChar(int c) { nextChar_ = c; }
  int getCharCallCount() const { return getCharCallCount_; }

  int getChar() override {
    ++getCharCallCount_;
    return nextChar_;
  }

private:
  int nextChar_ = -1;
  int getCharCallCount_ = 0;
};

class BaseSeekInputStreamTest_137 : public ::testing::Test {
protected:
  TestSeekInputStream_137 s_;
};

} // namespace

TEST_F(BaseSeekInputStreamTest_137, GetUnfilteredCharReturnsGetCharValue_137) {
  s_.setNextChar('A');

  const int c = s_.getUnfilteredChar();

  EXPECT_EQ(c, 'A');
  EXPECT_EQ(s_.getCharCallCount(), 1);
}

TEST_F(BaseSeekInputStreamTest_137, GetUnfilteredCharPropagatesEof_137) {
  // Many Poppler stream APIs use -1 as EOF; regardless, this verifies propagation.
  s_.setNextChar(-1);

  const int c = s_.getUnfilteredChar();

  EXPECT_EQ(c, -1);
  EXPECT_EQ(s_.getCharCallCount(), 1);
}

TEST_F(BaseSeekInputStreamTest_137, GetUnfilteredCharCallsGetCharEachTime_137) {
  s_.setNextChar(0);
  EXPECT_EQ(s_.getUnfilteredChar(), 0);

  s_.setNextChar(255);
  EXPECT_EQ(s_.getUnfilteredChar(), 255);

  EXPECT_EQ(s_.getCharCallCount(), 2);
}