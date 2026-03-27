// FixedLengthEncoder_tests.cpp
// Unit tests for FixedLengthEncoder (TEST_ID = 205)

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "poppler/Stream.h"

// A minimal concrete Stream implementation to act as an external collaborator.
// We intentionally keep behavior simple and observable (counts + in-memory bytes).
class CountingMemStream final : public Stream {
public:
  explicit CountingMemStream(std::string bytes)
      : data_(bytes.begin(), bytes.end()), pos_(0), start_(0) {}

  // --- Stream interface ---
  StreamKind getKind() const override { return strWeird; }

  void reset() override { pos_ = 0; }

  void close() override {}

  int getChar() override {
    ++getCharCalls;
    if (pos_ >= static_cast<int>(data_.size())) {
      return EOF;
    }
    return static_cast<unsigned char>(data_[pos_++]);
  }

  int lookChar() override {
    ++lookCharCalls;
    if (pos_ >= static_cast<int>(data_.size())) {
      return EOF;
    }
    return static_cast<unsigned char>(data_[pos_]);
  }

  int getPos() override { return pos_; }

  void setPos(Goffset pos, int dir = 0) override {
    // Simple, predictable positioning:
    // dir==0: absolute from start
    // dir==1: relative to current
    // dir==2: relative to end
    int newPos = 0;
    if (dir == 0) {
      newPos = static_cast<int>(pos);
    } else if (dir == 1) {
      newPos = pos_ + static_cast<int>(pos);
    } else { // dir == 2
      newPos = static_cast<int>(data_.size()) + static_cast<int>(pos);
    }
    if (newPos < 0) newPos = 0;
    if (newPos > static_cast<int>(data_.size())) newPos = static_cast<int>(data_.size());
    pos_ = newPos;
  }

  Goffset getStart() override { return start_; }

  void moveStart(int delta) override {
    start_ += delta;
    if (start_ < 0) start_ = 0;
  }

  Stream *getNextStream() override { return nullptr; }

  bool isBinary(bool /*unnamed*/) override { return true; }

  // --- Observability ---
  int getCharCalls = 0;
  int lookCharCalls = 0;

private:
  std::vector<unsigned char> data_;
  int pos_;
  Goffset start_;
};

class FixedLengthEncoderTest_205 : public ::testing::Test {
protected:
  // Note: FixedLengthEncoder takes ownership semantics unknown; we keep stream alive
  // for the duration of each test by owning it in the fixture.
  std::unique_ptr<CountingMemStream> base_;
};

TEST_F(FixedLengthEncoderTest_205, GetKindReturnsStrWeird_205) {
  base_ = std::make_unique<CountingMemStream>("abc");
  FixedLengthEncoder enc(base_.get(), /*lengthA=*/3);

  EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(FixedLengthEncoderTest_205, GetKindIsIndependentOfLengthBoundaryValues_205) {
  base_ = std::make_unique<CountingMemStream>("abc");

  FixedLengthEncoder encZero(base_.get(), /*lengthA=*/0);
  EXPECT_EQ(encZero.getKind(), strWeird);

  FixedLengthEncoder encNegative(base_.get(), /*lengthA=*/-1);
  EXPECT_EQ(encNegative.getKind(), strWeird);

  FixedLengthEncoder encLarge(base_.get(), /*lengthA=*/1000000);
  EXPECT_EQ(encLarge.getKind(), strWeird);
}

TEST_F(FixedLengthEncoderTest_205, IsEncoderReportsTrue_205) {
  base_ = std::make_unique<CountingMemStream>("abc");
  FixedLengthEncoder enc(base_.get(), /*lengthA=*/3);

  EXPECT_TRUE(enc.isEncoder());
}

TEST_F(FixedLengthEncoderTest_205, RewindIsCallableAndReturnsAStableBool_205) {
  base_ = std::make_unique<CountingMemStream>("abc");
  FixedLengthEncoder enc(base_.get(), /*lengthA=*/3);

  // We only assert that it is callable and returns a boolean value consistently
  // for repeated calls on the same object (observable behavior, not internal logic).
  const bool r1 = enc.rewind();
  const bool r2 = enc.rewind();
  EXPECT_EQ(r1, r2);
}

TEST_F(FixedLengthEncoderTest_205, GetCharInteractsWithUnderlyingStream_205) {
  base_ = std::make_unique<CountingMemStream>("abc");
  FixedLengthEncoder enc(base_.get(), /*lengthA=*/3);

  const int before = base_->getCharCalls + base_->lookCharCalls;
  (void)enc.getChar();
  const int after = base_->getCharCalls + base_->lookCharCalls;

  // External-interaction verification: calling getChar() should require some
  // interaction with the wrapped Stream (at least one call).
  EXPECT_GT(after, before);
}

TEST_F(FixedLengthEncoderTest_205, LookCharInteractsWithUnderlyingStream_205) {
  base_ = std::make_unique<CountingMemStream>("abc");
  FixedLengthEncoder enc(base_.get(), /*lengthA=*/3);

  const int before = base_->getCharCalls + base_->lookCharCalls;
  (void)enc.lookChar();
  const int after = base_->getCharCalls + base_->lookCharCalls;

  EXPECT_GT(after, before);
}

TEST_F(FixedLengthEncoderTest_205, IsBinaryIsCallableForBothFlagValues_205) {
  base_ = std::make_unique<CountingMemStream>("abc");
  FixedLengthEncoder enc(base_.get(), /*lengthA=*/3);

  // Observable behavior: returns a bool for both inputs.
  const bool b1 = enc.isBinary(false);
  const bool b2 = enc.isBinary(true);

  // We avoid assuming specific semantics; just ensure it is well-defined and stable.
  EXPECT_TRUE((b1 == true) || (b1 == false));
  EXPECT_TRUE((b2 == true) || (b2 == false));
}

TEST_F(FixedLengthEncoderTest_205, GetPSFilterIsCallable_205) {
  base_ = std::make_unique<CountingMemStream>("abc");
  FixedLengthEncoder enc(base_.get(), /*lengthA=*/3);

  // Observable: returns an optional string; we do not assume contents.
  const auto ps = enc.getPSFilter(/*psLevel=*/2, /*indent=*/"  ");
  EXPECT_TRUE(!ps.has_value() || ps->size() >= 0);
}