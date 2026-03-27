// RunLengthEncoder_tests.cpp
// TEST_ID: 221

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Stream.h"  // from ./TestProjects/poppler/poppler/Stream.h

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

using ::testing::AtLeast;

namespace {

// A simple in-memory Stream implementation used only as an external dependency
// for RunLengthEncoder. This does NOT assume anything about RunLengthEncoder's
// internal logic; it only provides deterministic input bytes.
class BufferStream final : public Stream {
public:
  explicit BufferStream(std::vector<unsigned char> data)
      : data_(std::move(data)), pos_(0) {}

  ~BufferStream() override = default;

  StreamKind getKind() const override {
    // Avoid assuming any specific StreamKind enumerator exists.
    return static_cast<StreamKind>(0);
  }

  bool rewind() override {
    pos_ = 0;
    return true;
  }

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

  bool isBinary(bool /*last*/ = true) const override { return true; }

  bool isEncoder() const override { return false; }

private:
  std::vector<unsigned char> data_;
  std::size_t pos_;
};

class MockStream : public Stream {
public:
  ~MockStream() override = default;

  MOCK_METHOD(StreamKind, getKind, (), (const, override));
  MOCK_METHOD(bool, rewind, (), (override));
  MOCK_METHOD(int, getChar, (), (override));
  MOCK_METHOD(int, lookChar, (), (override));
  MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char *), (override));
  MOCK_METHOD(bool, isBinary, (bool), (const, override));
  MOCK_METHOD(bool, isEncoder, (), (const, override));
};

static std::vector<int> ReadAllCharsWithLimit(Stream &s, std::size_t maxSteps) {
  std::vector<int> out;
  out.reserve(256);
  for (std::size_t i = 0; i < maxSteps; ++i) {
    const int c = s.getChar();
    out.push_back(c);
    if (c == EOF) {
      break;
    }
  }
  return out;
}

}  // namespace

class RunLengthEncoderTest_221 : public ::testing::Test {};

TEST_F(RunLengthEncoderTest_221, GetCharEventuallyReturnsEOF_221) {
  auto src = std::make_unique<BufferStream>(
      std::vector<unsigned char>{'a', 'b', 'c', 'd', 'e', 0x00, 0xff, 'z'});

  RunLengthEncoder enc(src.get());

  // Black-box: we only require that reading terminates (EOF appears)
  // within a reasonable bound, and non-EOF bytes are in [0,255].
  const auto bytes = ReadAllCharsWithLimit(enc, /*maxSteps=*/10000);

  ASSERT_FALSE(bytes.empty());
  EXPECT_EQ(bytes.back(), EOF) << "Encoder did not reach EOF within bound";

  for (int v : bytes) {
    if (v == EOF) continue;
    EXPECT_GE(v, 0);
    EXPECT_LE(v, 255);
  }
}

TEST_F(RunLengthEncoderTest_221, LookCharDoesNotConsumeNextByte_221) {
  auto src = std::make_unique<BufferStream>(
      std::vector<unsigned char>{0x10, 0x20, 0x30, 0x40});

  RunLengthEncoder enc(src.get());

  const int c1 = enc.lookChar();
  const int c2 = enc.lookChar();
  EXPECT_EQ(c1, c2) << "lookChar() should be stable when no consuming call happens";

  const int c3 = enc.getChar();
  EXPECT_EQ(c1, c3) << "getChar() should return the byte previously observed by lookChar()";
}

TEST_F(RunLengthEncoderTest_221, RewindRestartsObservableOutputSequence_221) {
  auto src = std::make_unique<BufferStream>(
      std::vector<unsigned char>{'x', 'x', 'x', 'y', 'z', 'z', 'w', 'w', 'w', 'w'});

  RunLengthEncoder enc(src.get());

  // Read a prefix of output.
  std::vector<int> first;
  for (int i = 0; i < 64; ++i) {
    const int c = enc.getChar();
    first.push_back(c);
    if (c == EOF) break;
  }
  ASSERT_FALSE(first.empty());

  // Rewind encoder; we don't assume true/false semantics beyond "callable".
  (void)enc.rewind();

  // Read again and compare a prefix (up to the min length we captured).
  std::vector<int> second;
  for (int i = 0; i < 64; ++i) {
    const int c = enc.getChar();
    second.push_back(c);
    if (c == EOF) break;
  }
  ASSERT_FALSE(second.empty());

  const std::size_t n = std::min(first.size(), second.size());
  for (std::size_t i = 0; i < n; ++i) {
    EXPECT_EQ(first[i], second[i]) << "Mismatch at output index " << i << " after rewind()";
  }
}

TEST_F(RunLengthEncoderTest_221, DeterministicForSameInputAcrossInstances_221) {
  const std::vector<unsigned char> input = {
      0x01, 0x02, 0x02, 0x02, 0x03, 0x04, 0x04, 0x05, 0x06, 0x06, 0x06, 0x06};

  auto src1 = std::make_unique<BufferStream>(input);
  auto src2 = std::make_unique<BufferStream>(input);

  RunLengthEncoder enc1(src1.get());
  RunLengthEncoder enc2(src2.get());

  const auto out1 = ReadAllCharsWithLimit(enc1, /*maxSteps=*/10000);
  const auto out2 = ReadAllCharsWithLimit(enc2, /*maxSteps=*/10000);

  // Black-box deterministic property: same input stream -> same encoded byte stream.
  EXPECT_EQ(out1, out2);
  ASSERT_FALSE(out1.empty());
  EXPECT_EQ(out1.back(), EOF);
}

TEST_F(RunLengthEncoderTest_221, EmptyInputReachesEOFQuickly_221) {
  auto src = std::make_unique<BufferStream>(std::vector<unsigned char>{});
  RunLengthEncoder enc(src.get());

  const auto out = ReadAllCharsWithLimit(enc, /*maxSteps=*/1024);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.back(), EOF) << "Empty input should reach EOF within a small bound";
  for (int v : out) {
    if (v == EOF) continue;
    EXPECT_GE(v, 0);
    EXPECT_LE(v, 255);
  }
}

TEST_F(RunLengthEncoderTest_221, GetCharTriggersUnderlyingGetCharCalls_221) {
  // External interaction verification (mock dependency).
  auto mock = std::make_unique<MockStream>();

  EXPECT_CALL(*mock, isEncoder()).Times(AtLeast(0));
  EXPECT_CALL(*mock, getKind()).Times(AtLeast(0));
  EXPECT_CALL(*mock, getPSFilter(testing::_, testing::_)).Times(AtLeast(0));
  EXPECT_CALL(*mock, isBinary(testing::_)).Times(AtLeast(0));
  EXPECT_CALL(*mock, rewind()).Times(AtLeast(0));

  // We don't assume how many bytes RunLengthEncoder will read internally,
  // only that producing output requires reading from the underlying stream.
  EXPECT_CALL(*mock, getChar()).Times(AtLeast(1))
      .WillRepeatedly(::testing::Return(EOF));
  EXPECT_CALL(*mock, lookChar()).Times(AtLeast(0));

  RunLengthEncoder enc(mock.get());
  (void)enc.getChar();  // should consult underlying stream at least once
}

TEST_F(RunLengthEncoderTest_221, BasicPropertyMethodsAreCallable_221) {
  auto src = std::make_unique<BufferStream>(std::vector<unsigned char>{'a', 'b', 'c'});
  RunLengthEncoder enc(src.get());

  // We do not assert exact values (black-box); just that they are callable and stable.
  const StreamKind k1 = enc.getKind();
  const StreamKind k2 = enc.getKind();
  (void)k1;
  (void)k2;

  const bool b1 = enc.isBinary(true);
  const bool b2 = enc.isBinary(false);
  (void)b1;
  (void)b2;

  EXPECT_TRUE(enc.isEncoder());
}