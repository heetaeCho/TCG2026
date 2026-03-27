// TEST_ID: 232
// Unit tests for CMYKGrayEncoder::lookChar (black-box)
// File: CMYKGrayEncoder_lookChar_test_232.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "poppler/Stream.h"

// A minimal in-memory Stream implementation to act as the upstream source for CMYKGrayEncoder.
// This is an external collaborator of the encoder, not an implementation detail of CMYKGrayEncoder.
class VectorStream final : public Stream {
public:
  explicit VectorStream(std::vector<unsigned char> data)
      : data_(std::move(data)), pos_(0) {}

  StreamKind getKind() const override { return strWeird; }

  [[nodiscard]] bool rewind() override {
    pos_ = 0;
    return true;
  }

  int getChar() override {
    if (pos_ >= data_.size()) {
      return EOF;
    }
    return static_cast<int>(data_[pos_++]);
  }

  int lookChar() override {
    if (pos_ >= data_.size()) {
      return EOF;
    }
    return static_cast<int>(data_[pos_]);
  }

  int getUnfilteredChar() override {
    // No filtering in this simple stream.
    return getChar();
  }

  [[nodiscard]] bool unfilteredRewind() override { return rewind(); }

  bool isBinary(bool /*last*/ = true) const override { return true; }

  BaseStream *getBaseStream() override { return nullptr; }

  Stream *getUndecodedStream() override { return this; }

  Dict *getDict() override { return nullptr; }

  Object *getDictObject() override { return nullptr; }

  Goffset getPos() override { return static_cast<Goffset>(pos_); }

  void setPos(Goffset pos, int dir = 0) override {
    // Behaves like a normal seek: from start (dir==0) or from end (dir<0).
    // Clamp into [0, size].
    long long base = 0;
    if (dir < 0) {
      base = static_cast<long long>(data_.size());
    }
    long long target = base + static_cast<long long>(pos);
    if (target < 0) {
      target = 0;
    }
    if (static_cast<size_t>(target) > data_.size()) {
      target = static_cast<long long>(data_.size());
    }
    pos_ = static_cast<size_t>(target);
  }

private:
  std::vector<unsigned char> data_;
  size_t pos_;
};

class CMYKGrayEncoderTest_232 : public ::testing::Test {
protected:
  static std::vector<unsigned char> MakeBytes(size_t n) {
    std::vector<unsigned char> v;
    v.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      v.push_back(static_cast<unsigned char>((i * 37u + 11u) & 0xffu));
    }
    return v;
  }
};

TEST_F(CMYKGrayEncoderTest_232, EmptyInput_LookCharReturnsEOF_232) {
  auto src = std::make_unique<VectorStream>(std::vector<unsigned char>{});
  CMYKGrayEncoder enc(src.get());

  ASSERT_TRUE(enc.rewind());
  EXPECT_EQ(EOF, enc.lookChar());
  EXPECT_EQ(EOF, enc.getChar());
  EXPECT_EQ(EOF, enc.lookChar());
}

TEST_F(CMYKGrayEncoderTest_232, LookCharDoesNotConsume_FirstByteMatchesNextGetChar_232) {
  // Provide some data; we do not assume anything about encoding output values,
  // only that lookChar peeks the next output char without consuming it.
  auto src = std::make_unique<VectorStream>(MakeBytes(64));
  CMYKGrayEncoder enc(src.get());

  ASSERT_TRUE(enc.rewind());

  const int peek = enc.lookChar();
  if (peek == EOF) {
    // If the encoder produces no output for this input, at least ensure consistency.
    EXPECT_EQ(EOF, enc.getChar());
    EXPECT_EQ(EOF, enc.lookChar());
    return;
  }

  const int got = enc.getChar();
  EXPECT_EQ(peek, got);

  // After consuming one char, lookChar should now reflect the next output char (or EOF).
  // We cannot assert what it is, only that it is consistent with getChar.
  const int peek2 = enc.lookChar();
  const int got2 = enc.getChar();
  EXPECT_EQ(peek2, got2);
}

TEST_F(CMYKGrayEncoderTest_232, MultipleLookCharCallsAreIdempotentUntilConsumed_232) {
  auto src = std::make_unique<VectorStream>(MakeBytes(128));
  CMYKGrayEncoder enc(src.get());

  ASSERT_TRUE(enc.rewind());

  const int a = enc.lookChar();
  const int b = enc.lookChar();
  const int c = enc.lookChar();
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);

  const int consumed = enc.getChar();
  EXPECT_EQ(a, consumed);

  // Now peeking again should be stable again (even if EOF).
  const int d = enc.lookChar();
  const int e = enc.lookChar();
  EXPECT_EQ(d, e);
}

TEST_F(CMYKGrayEncoderTest_232, LookCharEventuallyReturnsEOFAfterReadingAllOutput_232) {
  auto src = std::make_unique<VectorStream>(MakeBytes(512));
  CMYKGrayEncoder enc(src.get());

  ASSERT_TRUE(enc.rewind());

  // Black-box read loop: validate peek/get consistency for every produced byte,
  // and ensure it terminates (EOF reached).
  constexpr int kMaxOutputBytes = 100000; // safety cap to prevent infinite loops
  int count = 0;

  for (; count < kMaxOutputBytes; ++count) {
    const int peek = enc.lookChar();
    if (peek == EOF) {
      // Once lookChar is EOF, getChar should also be EOF (no further output).
      EXPECT_EQ(EOF, enc.getChar());
      EXPECT_EQ(EOF, enc.lookChar());
      break;
    }
    const int got = enc.getChar();
    EXPECT_EQ(peek, got);
  }

  ASSERT_LT(count, kMaxOutputBytes) << "Encoder did not reach EOF within safety limit";
}

TEST_F(CMYKGrayEncoderTest_232, RewindResetsPeekGetSequence_232) {
  auto src = std::make_unique<VectorStream>(MakeBytes(256));
  CMYKGrayEncoder enc(src.get());

  ASSERT_TRUE(enc.rewind());

  // Capture the first (peek, get) pair from the first run.
  const int p1 = enc.lookChar();
  const int g1 = enc.getChar();
  EXPECT_EQ(p1, g1);

  // Consume a few more bytes (if any).
  for (int i = 0; i < 10; ++i) {
    const int p = enc.lookChar();
    if (p == EOF) {
      break;
    }
    EXPECT_EQ(p, enc.getChar());
  }

  // Rewind and ensure the first output byte sequence restarts consistently.
  ASSERT_TRUE(enc.rewind());
  const int p2 = enc.lookChar();
  const int g2 = enc.getChar();
  EXPECT_EQ(p2, g2);

  // If the stream produces output, the first byte after rewind should match the original first byte.
  if (p1 != EOF && p2 != EOF) {
    EXPECT_EQ(p1, p2);
  }
}