// TEST_ID: 175
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"

namespace {

class StreamGetTest_175 : public ::testing::Test {
 protected:
  struct Holder {
    explicit Holder(const std::string& s) : input(s), stream(input) {}
    std::istringstream input;
    YAML::Stream stream;
  };
};

TEST_F(StreamGetTest_175, GetReturnsPeekedCharAndAdvances_175) {
  Holder h("x");

  const char p = h.stream.peek();
  const char g = h.stream.get();

  EXPECT_EQ(g, p);
  EXPECT_EQ(g, 'x');

  // After consuming the only character, peek/get should produce eof().
  EXPECT_EQ(h.stream.peek(), YAML::Stream::eof());
  EXPECT_EQ(h.stream.get(), YAML::Stream::eof());
}

TEST_F(StreamGetTest_175, NormalCharsAdvancePosAndColumn_175) {
  Holder h("abc");

  EXPECT_EQ(h.stream.pos(), 0);
  EXPECT_EQ(h.stream.line(), 0);
  EXPECT_EQ(h.stream.column(), 0);

  EXPECT_EQ(h.stream.get(), 'a');
  EXPECT_EQ(h.stream.pos(), 1);
  EXPECT_EQ(h.stream.line(), 0);
  EXPECT_EQ(h.stream.column(), 1);

  EXPECT_EQ(h.stream.get(), 'b');
  EXPECT_EQ(h.stream.pos(), 2);
  EXPECT_EQ(h.stream.line(), 0);
  EXPECT_EQ(h.stream.column(), 2);

  EXPECT_EQ(h.stream.get(), 'c');
  EXPECT_EQ(h.stream.pos(), 3);
  EXPECT_EQ(h.stream.line(), 0);
  EXPECT_EQ(h.stream.column(), 3);

  EXPECT_EQ(h.stream.peek(), YAML::Stream::eof());
}

TEST_F(StreamGetTest_175, UnixNewlineIncrementsLineAndResetsColumn_175) {
  Holder h("a\nb");

  EXPECT_EQ(h.stream.get(), 'a');
  EXPECT_EQ(h.stream.line(), 0);
  EXPECT_EQ(h.stream.column(), 1);

  EXPECT_EQ(h.stream.get(), '\n');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 0);

  EXPECT_EQ(h.stream.get(), 'b');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 1);
}

TEST_F(StreamGetTest_175, WindowsCRLFCountsLineEndingOnLF_175) {
  Holder h("a\r\nb");

  EXPECT_EQ(h.stream.get(), 'a');
  EXPECT_EQ(h.stream.line(), 0);
  EXPECT_EQ(h.stream.column(), 1);

  // For CRLF, line/column should not be reset on '\r' itself.
  EXPECT_EQ(h.stream.get(), '\r');
  EXPECT_EQ(h.stream.line(), 0);
  EXPECT_EQ(h.stream.column(), 2);

  // The following '\n' is treated as the line-ending character.
  EXPECT_EQ(h.stream.get(), '\n');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 0);

  EXPECT_EQ(h.stream.get(), 'b');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 1);
}

TEST_F(StreamGetTest_175, ClassicMacCRCountsLineEndingOnCR_175) {
  Holder h("a\rb");

  EXPECT_EQ(h.stream.get(), 'a');
  EXPECT_EQ(h.stream.line(), 0);
  EXPECT_EQ(h.stream.column(), 1);

  // For CR-only endings, line/column should reset on '\r'.
  EXPECT_EQ(h.stream.get(), '\r');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 0);

  EXPECT_EQ(h.stream.get(), 'b');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 1);
}

TEST_F(StreamGetTest_175, FirstDetectedLineEndingSymbolIsUsedThereafter_175) {
  // First line ending is '\n'; later '\r' should not be treated as a line ending.
  Holder h("a\nb\rc");

  EXPECT_EQ(h.stream.get(), 'a');
  EXPECT_EQ(h.stream.get(), '\n');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 0);

  EXPECT_EQ(h.stream.get(), 'b');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 1);

  // '\r' should not increment the line or reset the column when '\n' was chosen.
  EXPECT_EQ(h.stream.get(), '\r');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 2);

  EXPECT_EQ(h.stream.get(), 'c');
  EXPECT_EQ(h.stream.line(), 1);
  EXPECT_EQ(h.stream.column(), 3);
}

TEST_F(StreamGetTest_175, EmptyStreamGetReturnsEof_175) {
  Holder h("");

  EXPECT_EQ(h.stream.peek(), YAML::Stream::eof());
  EXPECT_EQ(h.stream.get(), YAML::Stream::eof());
  EXPECT_EQ(h.stream.get(), YAML::Stream::eof());
}

TEST_F(StreamGetTest_175, BoolBecomesFalseAfterConsumingAllInput_175) {
  Holder h("z");

  // Expect the stream to be usable before consuming and not usable after.
  EXPECT_TRUE(static_cast<bool>(h.stream));
  EXPECT_FALSE(!h.stream);

  EXPECT_EQ(h.stream.get(), 'z');

  EXPECT_FALSE(static_cast<bool>(h.stream));
  EXPECT_TRUE(!h.stream);
}

}  // namespace