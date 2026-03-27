// FlateEncoder_test_1650.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

// Poppler headers
#include "FlateEncoder.h"
#include "Stream.h"
#include "goo/gtypes.h"

// A simple in-memory source Stream to feed FlateEncoder.
// This is an external collaborator (dependency) of FlateEncoder, so providing a
// minimal concrete Stream implementation is acceptable for black-box testing.
class BufferStreamForFlateEncoderTest_1650 : public Stream {
public:
  explicit BufferStreamForFlateEncoderTest_1650(std::vector<unsigned char> data)
      : data_(std::move(data)), pos_(0) {}

  StreamKind getKind() const override { return strWeird; }

  void reset() override { pos_ = 0; }

  void close() override {
    // no-op for in-memory stream
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

  Goffset getPos() override { return static_cast<Goffset>(pos_); }

  void setPos(Goffset pos, int dir = 0) override {
    // dir: 0 = absolute, 1 = relative, 2 = from end (common Poppler convention)
    long long newPos = 0;
    if (dir == 0) {
      newPos = static_cast<long long>(pos);
    } else if (dir == 1) {
      newPos = static_cast<long long>(pos_) + static_cast<long long>(pos);
    } else { // dir == 2
      newPos = static_cast<long long>(data_.size()) + static_cast<long long>(pos);
    }

    if (newPos < 0) newPos = 0;
    if (newPos > static_cast<long long>(data_.size())) newPos = static_cast<long long>(data_.size());
    pos_ = static_cast<std::size_t>(newPos);
  }

private:
  std::vector<unsigned char> data_;
  std::size_t pos_;
};

class FlateEncoderTest_1650 : public ::testing::Test {
protected:
  static std::vector<unsigned char> ToBytes(const std::string &s) {
    return std::vector<unsigned char>(s.begin(), s.end());
  }

  // Read bytes until EOF (with a hard cap to avoid infinite loops).
  static std::vector<unsigned char> ReadAll(FlateEncoder &enc, std::size_t hardCap = 1u << 20) {
    std::vector<unsigned char> out;
    out.reserve(1024);

    for (std::size_t i = 0; i < hardCap; ++i) {
      const int c = enc.getChar();
      if (c == EOF) {
        return out;
      }
      EXPECT_GE(c, 0);
      EXPECT_LE(c, 255);
      out.push_back(static_cast<unsigned char>(c));
    }

    // If we hit here, encoder never produced EOF within cap.
    ADD_FAILURE() << "FlateEncoder did not reach EOF within hardCap=" << hardCap;
    return out;
  }
};

TEST_F(FlateEncoderTest_1650, GetCharReturnsByteValuesAndEventuallyEOF_1650) {
  BufferStreamForFlateEncoderTest_1650 src(ToBytes("hello world"));
  FlateEncoder enc(&src);

  const auto out = ReadAll(enc);

  // Black-box expectation: an encoder should produce a finite output stream.
  // We do not assert exact compressed bytes.
  EXPECT_GE(out.size(), 1u);

  // After EOF is reached, repeated reads should remain EOF (typical Stream behavior).
  EXPECT_EQ(enc.getChar(), EOF);
  EXPECT_EQ(enc.getChar(), EOF);
}

TEST_F(FlateEncoderTest_1650, LookCharDoesNotConsumeNextByte_1650) {
  BufferStreamForFlateEncoderTest_1650 src(ToBytes("peek test"));
  FlateEncoder enc(&src);

  const int firstPeek = enc.lookChar();
  ASSERT_NE(firstPeek, EOF);
  EXPECT_GE(firstPeek, 0);
  EXPECT_LE(firstPeek, 255);

  // Multiple peeks should be stable before consuming.
  const int secondPeek = enc.lookChar();
  EXPECT_EQ(secondPeek, firstPeek);

  // getChar should return the same value as the prior lookChar.
  const int firstGet = enc.getChar();
  EXPECT_EQ(firstGet, firstPeek);

  // And subsequent peek/get should still behave consistently.
  const int nextPeek = enc.lookChar();
  if (nextPeek != EOF) {
    EXPECT_EQ(enc.getChar(), nextPeek);
  } else {
    EXPECT_EQ(enc.getChar(), EOF);
  }
}

TEST_F(FlateEncoderTest_1650, RewindRestartsEncodedStream_1650) {
  BufferStreamForFlateEncoderTest_1650 src(ToBytes("rewind test data"));
  FlateEncoder enc(&src);

  // Read a prefix of the encoded output.
  std::vector<unsigned char> prefix1;
  for (int i = 0; i < 16; ++i) {
    const int c = enc.getChar();
    ASSERT_NE(c, EOF);
    prefix1.push_back(static_cast<unsigned char>(c));
  }

  // Rewind should allow reading from the beginning again.
  EXPECT_TRUE(enc.rewind());

  std::vector<unsigned char> prefix2;
  for (int i = 0; i < 16; ++i) {
    const int c = enc.getChar();
    ASSERT_NE(c, EOF);
    prefix2.push_back(static_cast<unsigned char>(c));
  }

  // On a deterministic encoder, rewinding should reproduce the same initial bytes.
  EXPECT_EQ(prefix2, prefix1);
}

TEST_F(FlateEncoderTest_1650, EmptyInputStillTerminatesWithEOF_1650) {
  BufferStreamForFlateEncoderTest_1650 src(std::vector<unsigned char>{});
  FlateEncoder enc(&src);

  const auto out = ReadAll(enc);

  // Do not assume whether the encoder emits headers/trailers for empty input.
  // Only require that it terminates and subsequent reads stay at EOF.
  EXPECT_EQ(enc.getChar(), EOF);
  EXPECT_EQ(enc.getChar(), EOF);

  // Output should be finite (ReadAll already enforces EOF within cap).
  EXPECT_LE(out.size(), (1u << 20));
}