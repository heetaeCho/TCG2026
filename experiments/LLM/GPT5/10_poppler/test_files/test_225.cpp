// RunLengthEncoder_tests_225.cpp
#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/Stream.h"

#include <cstddef>
#include <string>

// A minimal concrete Stream implementation to satisfy RunLengthEncoder's dependency.
// This is an external collaborator (input Stream), not an attempt to reimplement RunLengthEncoder.
class MinimalInputStream final : public Stream {
public:
  explicit MinimalInputStream(std::string data = {}) : data_(std::move(data)) {}

  StreamKind getKind() override { return strWeird; }

  void reset() override { pos_ = 0; }

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

  int getUnfilteredChar() override { return getChar(); }

  void unfilteredReset() override { reset(); }

  int getPos() override { return static_cast<int>(pos_); }

  void setPos(Guint pos, int dir = 0) override {
    // Best-effort, bounds-safe positioning for a test double.
    // dir < 0 means from end; otherwise from start (per Stream.h contract).
    size_t newPos = 0;
    if (dir < 0) {
      const size_t end = data_.size();
      newPos = (pos > end) ? 0 : (end - static_cast<size_t>(pos));
    } else {
      newPos = static_cast<size_t>(pos);
    }
    pos_ = (newPos > data_.size()) ? data_.size() : newPos;
  }

  GBool isBinary(GBool /*last*/ = gTrue) override { return gFalse; }

  BaseStream *getBaseStream() override { return nullptr; }

  Stream *getUndecodedStream() override { return this; }

  Dict *getDict() override { return nullptr; }

private:
  std::string data_;
  size_t pos_ = 0;
};

class RunLengthEncoderTest_225 : public ::testing::Test {};

TEST_F(RunLengthEncoderTest_225, IsEncoderReturnsTrue_225) {
  auto *input = new MinimalInputStream("abc");
  RunLengthEncoder enc(input);

  EXPECT_TRUE(enc.isEncoder());

  // RunLengthEncoder should not delete a non-encoder underlying Stream.
  delete input;
}

TEST_F(RunLengthEncoderTest_225, IsEncoderCallableOnConstReference_225) {
  auto *input = new MinimalInputStream("xyz");
  RunLengthEncoder enc(input);

  const RunLengthEncoder &cenc = enc;
  EXPECT_TRUE(cenc.isEncoder());

  delete input;
}

TEST_F(RunLengthEncoderTest_225, IsEncoderRemainsTrueAfterReset_225) {
  auto *input = new MinimalInputStream("data");
  RunLengthEncoder enc(input);

  enc.reset();
  EXPECT_TRUE(enc.isEncoder());

  delete input;
}

// Verifies observable external interaction: destructor ownership rule for the wrapped Stream.
// If wrapped Stream reports isEncoder() == false, RunLengthEncoder must not delete it.
TEST_F(RunLengthEncoderTest_225, DestructorDoesNotDeleteWrappedNonEncoderStream_225) {
  bool destroyed = false;

  class ProbeNonEncoderStream final : public MinimalInputStream {
  public:
    explicit ProbeNonEncoderStream(bool *flag) : flag_(flag) {}
    ~ProbeNonEncoderStream() override {
      if (flag_) *flag_ = true;
    }
  private:
    bool *flag_;
  };

  auto *probe = new ProbeNonEncoderStream(&destroyed);
  EXPECT_FALSE(destroyed);

  {
    RunLengthEncoder enc(probe);
    EXPECT_TRUE(enc.isEncoder());
  }

  // The wrapped stream should still be alive here (not deleted by RunLengthEncoder).
  EXPECT_FALSE(destroyed);

  delete probe;
  EXPECT_TRUE(destroyed);
}

// If wrapped Stream reports isEncoder() == true, RunLengthEncoder is expected to delete it.
TEST_F(RunLengthEncoderTest_225, DestructorDeletesWrappedEncoderStream_225) {
  bool destroyed = false;

  class ProbeEncoderStream final : public MinimalInputStream {
  public:
    explicit ProbeEncoderStream(bool *flag) : flag_(flag) {}
    ~ProbeEncoderStream() override {
      if (flag_) *flag_ = true;
    }
    GBool isEncoder() override { return gTrue; }
  private:
    bool *flag_;
  };

  auto *probe = new ProbeEncoderStream(&destroyed);
  EXPECT_FALSE(destroyed);

  {
    RunLengthEncoder enc(probe);
    EXPECT_TRUE(enc.isEncoder());
  }

  // The wrapped stream should have been deleted by RunLengthEncoder's destructor.
  EXPECT_TRUE(destroyed);
}