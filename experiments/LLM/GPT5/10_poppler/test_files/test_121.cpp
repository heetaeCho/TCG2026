// File: stream_fillgoostring_tests_121.cpp
//
// Unit tests for Stream::fillGooString(GooString*)
// Constraints respected:
// - Treat Stream implementation as a black box.
// - Test only observable behavior via public interface.
// - No access to private/internal state of Stream.
// - Provide normal + boundary cases.
// - Each test name includes TEST_ID (121).

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "poppler/Stream.h"
#include "goo/GooString.h"

// A small deterministic Stream for testing.
// This is a collaborator used to supply known bytes through the virtual interface.
class MemoryStreamForTest_121 : public Stream {
public:
  explicit MemoryStreamForTest_121(std::string data) : data_(std::move(data)), pos_(0) {}
  ~MemoryStreamForTest_121() override = default;

  bool rewind() override {
    pos_ = 0;
    return true;
  }

  int getChar() override {
    if (pos_ >= data_.size()) {
      return EOF;
    }
    return static_cast<unsigned char>(data_[pos_++]);
  }

  int lookChar() override {
    if (pos_ >= data_.size()) {
      return EOF;
    }
    return static_cast<unsigned char>(data_[pos_]);
  }

  Goffset getPos() override { return static_cast<Goffset>(pos_); }

  void setPos(Goffset pos, int /*dir*/) override {
    if (pos < 0) {
      pos_ = 0;
      return;
    }
    const auto upos = static_cast<size_t>(pos);
    pos_ = (upos > data_.size()) ? data_.size() : upos;
  }

  void close() override {}

private:
  std::string data_;
  size_t pos_;
};

class StreamFillGooStringTest_121 : public ::testing::Test {};

TEST_F(StreamFillGooStringTest_121, FillGooStringMatchesFillStringFromSameInitial_121) {
  const std::string payload = "Hello, Stream!\nSecond line.\n";

  MemoryStreamForTest_121 s1(payload);
  MemoryStreamForTest_121 s2(payload);

  GooString gs("prefix:");
  std::string ss("prefix:");

  // Act
  s1.fillGooString(&gs);
  s2.fillString(ss);

  // Assert: fillGooString should behave consistently with fillString when given equivalent storage.
  EXPECT_EQ(gs.toStr(), ss);
}

TEST_F(StreamFillGooStringTest_121, FillGooStringWorksWithEmptyInitialString_121) {
  const std::string payload = "ABC";

  MemoryStreamForTest_121 s1(payload);
  MemoryStreamForTest_121 s2(payload);

  GooString gs;          // empty
  std::string ss;        // empty

  s1.fillGooString(&gs);
  s2.fillString(ss);

  EXPECT_EQ(gs.toStr(), ss);
}

TEST_F(StreamFillGooStringTest_121, FillGooStringHandlesLargePayloadBoundary_121) {
  // Boundary: payload larger than typical small buffers.
  std::string payload;
  payload.reserve(20000);
  for (int i = 0; i < 20000; ++i) {
    payload.push_back(static_cast<char>('a' + (i % 26)));
  }

  MemoryStreamForTest_121 s1(payload);
  MemoryStreamForTest_121 s2(payload);

  GooString gs("start-");
  std::string ss("start-");

  s1.fillGooString(&gs);
  s2.fillString(ss);

  EXPECT_EQ(gs.toStr(), ss);
  EXPECT_GE(gs.toStr().size(), std::string("start-").size());
}

TEST_F(StreamFillGooStringTest_121, FillGooStringPreservesEmbeddedNullBytes_121) {
  // Boundary: payload includes '\0' bytes.
  std::string payload;
  payload.push_back('A');
  payload.push_back('\0');
  payload.push_back('B');
  payload.push_back('\0');
  payload.push_back('C');

  MemoryStreamForTest_121 s1(payload);
  MemoryStreamForTest_121 s2(payload);

  GooString gs("P");
  std::string ss("P");

  s1.fillGooString(&gs);
  s2.fillString(ss);

  EXPECT_EQ(gs.toStr().size(), ss.size());
  EXPECT_EQ(gs.toStr(), ss);

  // Spot-check that nulls are present in the same positions relative to the prefix.
  ASSERT_GE(gs.toStr().size(), 1u + payload.size());
  EXPECT_EQ(gs.toStr()[1 + 1], '\0'); // after prefix 'P' + 'A'
  EXPECT_EQ(gs.toStr()[1 + 3], '\0'); // after prefix 'P' + "A\0B"
}

TEST_F(StreamFillGooStringTest_121, FillGooStringReadsUntilEofConsistentlyWithFillString_121) {
  const std::string payload = "end";

  MemoryStreamForTest_121 s1(payload);
  MemoryStreamForTest_121 s2(payload);

  GooString gs("X");
  std::string ss("X");

  // Ensure we start at a non-zero position, then rewind (exercise observable interaction via public API).
  (void)s1.getChar();
  (void)s2.getChar();
  ASSERT_TRUE(s1.rewind());
  ASSERT_TRUE(s2.rewind());

  s1.fillGooString(&gs);
  s2.fillString(ss);

  EXPECT_EQ(gs.toStr(), ss);
}