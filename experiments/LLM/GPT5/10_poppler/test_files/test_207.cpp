// FixedLengthEncoder_tests_207.cpp
// Unit tests for poppler::FixedLengthEncoder (black-box via public interface)
//
// TEST_ID: 207

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Poppler header under test
#include "Stream.h"

namespace {

// A small concrete Stream implementation for testing wrapper behavior.
// Implements only via the public Stream interface (no access to internals of FixedLengthEncoder).
class VectorStream final : public Stream {
public:
  explicit VectorStream(std::vector<unsigned char> data,
                        bool is_encoder = false,
                        bool binary_answer = false)
      : data_(std::move(data)),
        is_encoder_(is_encoder),
        binary_answer_(binary_answer) {}

  ~VectorStream() override = default;

  StreamKind getKind() const override { return kind_; }
  void setKind(StreamKind k) { kind_ = k; }

  // rewind(): reset to beginning
  bool rewind() override {
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

  // isBinary: record the last argument for verification.
  bool isBinary(bool last) const override {
    last_isBinary_arg_ = last;
    return binary_answer_;
  }

  // getPSFilter: return a fixed value (or empty) - not important for these tests.
  std::optional<std::string> getPSFilter(int /*psLevel*/, const char* /*indent*/) override {
    return std::nullopt;
  }

  bool isEncoder() const override { return is_encoder_; }

  // Minimal position API (commonly present in Stream implementations).
  // If your local Stream interface differs, adjust these methods accordingly.
  Goffset getPos() override { return static_cast<Goffset>(pos_); }

  void setPos(Goffset pos, int dir = 0) override {
    std::size_t base = 0;
    if (dir < 0) {
      base = data_.size();
    }
    std::int64_t target = static_cast<std::int64_t>(base) + static_cast<std::int64_t>(pos);
    if (target < 0) {
      pos_ = 0;
    } else if (static_cast<std::size_t>(target) > data_.size()) {
      pos_ = data_.size();
    } else {
      pos_ = static_cast<std::size_t>(target);
    }
  }

  // Unfiltered hooks (often required by Stream).
  int getUnfilteredChar() override { return getChar(); }
  void unfilteredReset() override { (void)rewind(); }

  Stream* getUndecodedStream() override { return this; }

  // Exposed for assertions
  std::size_t position() const { return pos_; }
  bool lastIsBinaryArg() const { return last_isBinary_arg_.value_or(false); }
  bool hasLastIsBinaryArg() const { return last_isBinary_arg_.has_value(); }

private:
  std::vector<unsigned char> data_;
  std::size_t pos_{0};
  bool is_encoder_{false};
  bool binary_answer_{false};
  StreamKind kind_{strWeird};
  mutable std::optional<bool> last_isBinary_arg_{};
};

// A stream that increments a counter when destroyed (to observe ownership behavior).
class DtorCountingStream final : public VectorStream {
public:
  explicit DtorCountingStream(std::vector<unsigned char> data,
                              bool is_encoder,
                              int* dtor_counter)
      : VectorStream(std::move(data), is_encoder),
        dtor_counter_(dtor_counter) {}

  ~DtorCountingStream() override {
    if (dtor_counter_) {
      ++(*dtor_counter_);
    }
  }

private:
  int* dtor_counter_{nullptr};
};

class FixedLengthEncoderTest_207 : public ::testing::Test {};

}  // namespace

TEST_F(FixedLengthEncoderTest_207, IsEncoderReturnsTrue_207) {
  auto* src = new VectorStream({'a', 'b', 'c'}, /*is_encoder=*/false);
  FixedLengthEncoder enc(src, /*lengthA=*/2);

  EXPECT_TRUE(enc.isEncoder());
}

TEST_F(FixedLengthEncoderTest_207, GetCharStopsAtExactLength_207) {
  auto* src = new VectorStream({'A', 'B', 'C', 'D'}, /*is_encoder=*/false);
  FixedLengthEncoder enc(src, /*lengthA=*/2);

  EXPECT_EQ(enc.getChar(), 'A');
  EXPECT_EQ(enc.getChar(), 'B');
  EXPECT_EQ(enc.getChar(), EOF);

  // Further reads should remain EOF (observable behavior).
  EXPECT_EQ(enc.getChar(), EOF);
}

TEST_F(FixedLengthEncoderTest_207, LengthZeroReturnsEofImmediately_207) {
  auto* src = new VectorStream({'X', 'Y'}, /*is_encoder=*/false);
  FixedLengthEncoder enc(src, /*lengthA=*/0);

  EXPECT_EQ(enc.getChar(), EOF);
  EXPECT_EQ(enc.lookChar(), EOF);
}

TEST_F(FixedLengthEncoderTest_207, NegativeLengthDoesNotPrematurelyStop_207) {
  auto* src = new VectorStream({'1', '2', '3'}, /*is_encoder=*/false);
  FixedLengthEncoder enc(src, /*lengthA=*/-1);

  EXPECT_EQ(enc.getChar(), '1');
  EXPECT_EQ(enc.getChar(), '2');
  EXPECT_EQ(enc.getChar(), '3');
  EXPECT_EQ(enc.getChar(), EOF);
}

TEST_F(FixedLengthEncoderTest_207, RewindAllowsRereadUpToLength_207) {
  auto* src = new VectorStream({'k', 'l', 'm'}, /*is_encoder=*/false);
  FixedLengthEncoder enc(src, /*lengthA=*/2);

  EXPECT_EQ(enc.getChar(), 'k');
  EXPECT_EQ(enc.getChar(), 'l');
  EXPECT_EQ(enc.getChar(), EOF);

  ASSERT_TRUE(enc.rewind());

  EXPECT_EQ(enc.getChar(), 'k');
  EXPECT_EQ(enc.getChar(), 'l');
  EXPECT_EQ(enc.getChar(), EOF);
}

TEST_F(FixedLengthEncoderTest_207, IsBinaryDelegatesToUnderlying_207) {
  auto* src = new VectorStream({'a'}, /*is_encoder=*/false, /*binary_answer=*/true);
  FixedLengthEncoder enc(src, /*lengthA=*/1);

  // Call with either value; we only verify delegation happened and returned underlying answer.
  EXPECT_TRUE(enc.isBinary(false));
  EXPECT_TRUE(src->hasLastIsBinaryArg());
}

TEST_F(FixedLengthEncoderTest_207, DestructorDeletesUnderlyingIfItIsEncoder_207) {
  int dtor_count = 0;
  auto* src = new DtorCountingStream({'a', 'b'}, /*is_encoder=*/true, &dtor_count);

  {
    auto* enc = new FixedLengthEncoder(src, /*lengthA=*/1);
    // deleting encoder should delete underlying stream if underlying reports isEncoder() == true
    delete enc;
  }

  EXPECT_EQ(dtor_count, 1);
}

TEST_F(FixedLengthEncoderTest_207, DestructorDoesNotDeleteUnderlyingIfNotEncoder_207) {
  int dtor_count = 0;
  auto* src = new DtorCountingStream({'a', 'b'}, /*is_encoder=*/false, &dtor_count);

  {
    auto* enc = new FixedLengthEncoder(src, /*lengthA=*/1);
    delete enc;
  }

  // Underlying should still be alive (observable via destructor counter).
  EXPECT_EQ(dtor_count, 0);

  delete src;
  EXPECT_EQ(dtor_count, 1);
}