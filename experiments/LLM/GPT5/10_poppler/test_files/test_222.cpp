// TEST_ID = 222
//
// Unit tests for RunLengthEncoder::lookChar (and related observable behaviors)
//
// File under test:
//   ./TestProjects/poppler/poppler/Stream.h

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Poppler header
#include "poppler/Stream.h"

// -----------------------------------------------------------------------------
// A tiny in-memory Stream implementation to act as an external collaborator.
// This is NOT re-implementing RunLengthEncoder logic; it only provides bytes.
// -----------------------------------------------------------------------------
class ByteArrayStream final : public Stream {
public:
  explicit ByteArrayStream(std::vector<unsigned char> data)
      : data_(std::move(data)), pos_(0) {}

  ~ByteArrayStream() override = default;

  // --- Stream interface (minimal set expected/used by RunLengthEncoder) ---
  bool rewind() override {
    pos_ = 0;
    return true;
  }

  StreamKind getKind() const override { return strWeird; } // arbitrary concrete kind

  int getChar() override {
    if (pos_ >= data_.size()) {
      return EOF;
    }
    return static_cast<int>(data_[pos_++]) & 0xff;
  }

  int lookChar() override {
    if (pos_ >= data_.size()) {
      return EOF;
    }
    return static_cast<int>(data_[pos_]) & 0xff;
  }

  std::optional<std::string> getPSFilter(int /*psLevel*/, const char * /*indent*/) override {
    return std::nullopt;
  }

  bool isBinary(bool /*last = true*/) const override { return true; }

  bool isEncoder() const override { return false; }

private:
  std::vector<unsigned char> data_;
  std::size_t pos_;
};

// -----------------------------------------------------------------------------
// Test fixture
// -----------------------------------------------------------------------------
class RunLengthEncoderTest_222 : public ::testing::Test {
protected:
  static std::unique_ptr<RunLengthEncoder> MakeEncoderFromBytes(const std::vector<unsigned char> &bytes,
                                                                std::unique_ptr<Stream> *ownedSrcOut) {
    auto src = std::make_unique<ByteArrayStream>(bytes);
    Stream *srcRaw = src.get();
    if (ownedSrcOut) {
      *ownedSrcOut = std::move(src);
    }
    return std::make_unique<RunLengthEncoder>(srcRaw);
  }

  static std::vector<unsigned char> ToBytes(const std::string &s) {
    return std::vector<unsigned char>(s.begin(), s.end());
  }
};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

TEST_F(RunLengthEncoderTest_222, LookCharOnEmptyStreamReturnsEOF_222) {
  std::unique_ptr<Stream> ownedSrc;
  auto enc = MakeEncoderFromBytes({}, &ownedSrc);

  ASSERT_TRUE(enc->rewind()); // observable return type is bool in the provided interface
  EXPECT_EQ(enc->lookChar(), EOF);
  EXPECT_EQ(enc->getChar(), EOF);
  EXPECT_EQ(enc->lookChar(), EOF);
}

TEST_F(RunLengthEncoderTest_222, LookCharDoesNotConsumeNextByte_222) {
  std::unique_ptr<Stream> ownedSrc;
  auto enc = MakeEncoderFromBytes(ToBytes("ABC"), &ownedSrc);

  ASSERT_TRUE(enc->rewind());

  const int c1 = enc->lookChar();
  ASSERT_NE(c1, EOF);

  // If lookChar is a peek, getChar should return the same byte next.
  const int g1 = enc->getChar();
  EXPECT_EQ(g1, c1);

  // And the stream should advance afterward.
  const int c2 = enc->lookChar();
  // We can’t assume encoding details; just ensure calls are consistent and not crashing.
  // It’s still valid to check EOF boundary at the end.
  (void)c2;
}

TEST_F(RunLengthEncoderTest_222, RepeatedLookCharIsStableUntilGetChar_222) {
  std::unique_ptr<Stream> ownedSrc;
  auto enc = MakeEncoderFromBytes(ToBytes("Hello"), &ownedSrc);

  ASSERT_TRUE(enc->rewind());

  const int a = enc->lookChar();
  const int b = enc->lookChar();
  EXPECT_EQ(a, b);

  const int g = enc->getChar();
  EXPECT_EQ(g, a);
}

TEST_F(RunLengthEncoderTest_222, LookCharAfterConsumingAllReturnsEOF_222) {
  std::unique_ptr<Stream> ownedSrc;
  auto enc = MakeEncoderFromBytes(ToBytes("X"), &ownedSrc);

  ASSERT_TRUE(enc->rewind());

  // Consume whatever the encoder produces until EOF (black-box).
  while (enc->getChar() != EOF) {
  }

  EXPECT_EQ(enc->lookChar(), EOF);
  EXPECT_EQ(enc->getChar(), EOF);
}

TEST_F(RunLengthEncoderTest_222, LookCharWorksAcrossMultipleCallsWithLargerInput_222) {
  // Large enough to likely exercise internal buffering without assuming sizes.
  std::vector<unsigned char> bytes;
  bytes.reserve(2048);
  for (int i = 0; i < 2048; ++i) {
    bytes.push_back(static_cast<unsigned char>(i & 0xff));
  }

  std::unique_ptr<Stream> ownedSrc;
  auto enc = MakeEncoderFromBytes(bytes, &ownedSrc);

  ASSERT_TRUE(enc->rewind());

  // Exercise lookChar/getChar interplay repeatedly.
  for (int i = 0; i < 128; ++i) {
    const int p = enc->lookChar();
    if (p == EOF) {
      break;
    }
    const int g = enc->getChar();
    EXPECT_EQ(g, p);
  }

  // Eventually, consuming all output reaches EOF.
  while (enc->getChar() != EOF) {
  }
  EXPECT_EQ(enc->lookChar(), EOF);
}

TEST_F(RunLengthEncoderTest_222, IsEncoderReportsTrue_222) {
  std::unique_ptr<Stream> ownedSrc;
  auto enc = MakeEncoderFromBytes(ToBytes("data"), &ownedSrc);

  // This is directly observable via the public interface.
  EXPECT_TRUE(enc->isEncoder());
}