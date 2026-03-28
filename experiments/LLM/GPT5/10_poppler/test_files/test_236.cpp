// TEST_ID: 236
//
// Unit tests for RGBGrayEncoder (poppler/Stream.h)
// Constraints honored:
//  - Treat implementation as black box (no private state access, no logic re-implementation).
//  - Test only via public interface and observable behavior.
//  - Verify external interactions via a simple underlying Stream test double.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "poppler/Stream.h"
#include "poppler/Object.h"

// A simple in-memory Stream used as the underlying source for FilterStream-based encoders.
// This is an external collaborator test double (not simulating RGBGrayEncoder internals).
class VectorMemStream final : public Stream {
public:
  explicit VectorMemStream(std::vector<unsigned char> bytes)
      : data_(std::move(bytes)) {
    // Make sure dictObj_ is a valid Object instance.
    dictObj_.setToNull();
  }

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

  int getUnfilteredChar() override { return getChar(); }

  [[nodiscard]] bool unfilteredRewind() override { return rewind(); }

  Goffset getPos() override { return static_cast<Goffset>(pos_); }

  void setPos(Goffset pos, int dir = 0) override {
    // Minimal, predictable behavior for tests.
    // dir == 0: from start; dir < 0: from end; dir > 0: from current.
    long long newPos = 0;
    if (dir < 0) {
      newPos = static_cast<long long>(data_.size()) + static_cast<long long>(pos);
    } else if (dir > 0) {
      newPos = static_cast<long long>(pos_) + static_cast<long long>(pos);
    } else {
      newPos = static_cast<long long>(pos);
    }

    if (newPos < 0) {
      newPos = 0;
    }
    const auto maxPos = static_cast<long long>(data_.size());
    if (newPos > maxPos) {
      newPos = maxPos;
    }
    pos_ = static_cast<std::size_t>(newPos);
  }

  bool isBinary(bool /*last=*/true) const override { return true; }

  BaseStream *getBaseStream() override { return nullptr; }
  Stream *getUndecodedStream() override { return this; }
  Dict *getDict() override { return nullptr; }
  Object *getDictObject() override { return &dictObj_; }

private:
  std::vector<unsigned char> data_;
  std::size_t pos_{0};
  Object dictObj_;
};

class RGBGrayEncoderTest_236 : public ::testing::Test {
protected:
  static std::vector<int> DrainToEof(Stream &s, std::size_t maxIters = 1'000'000) {
    std::vector<int> out;
    out.reserve(1024);
    for (std::size_t i = 0; i < maxIters; ++i) {
      const int c = s.getChar();
      if (c == EOF) {
        return out;
      }
      out.push_back(c);
    }
    // If we hit this, something is wrong (non-terminating stream).
    ADD_FAILURE() << "Stream did not reach EOF within maxIters=" << maxIters;
    return out;
  }
};

TEST_F(RGBGrayEncoderTest_236, KindIsWeird_236) {
  auto base = std::make_unique<VectorMemStream>(std::vector<unsigned char>{0x00, 0x7f, 0xff});
  RGBGrayEncoder enc(base.get());

  EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(RGBGrayEncoderTest_236, ReportsEncoderAndNotBinaryAndNoPSFilter_236) {
  auto base = std::make_unique<VectorMemStream>(std::vector<unsigned char>{0x01, 0x02, 0x03});
  RGBGrayEncoder enc(base.get());

  EXPECT_TRUE(enc.isEncoder());
  EXPECT_FALSE(enc.isBinary(/*last=*/true));
  EXPECT_FALSE(enc.getPSFilter(/*psLevel=*/2, /*indent=*/"  ").has_value());
}

TEST_F(RGBGrayEncoderTest_236, EmptyInputYieldsEof_236) {
  auto base = std::make_unique<VectorMemStream>(std::vector<unsigned char>{});
  RGBGrayEncoder enc(base.get());

  EXPECT_EQ(enc.lookChar(), EOF);
  EXPECT_EQ(enc.getChar(), EOF);
  EXPECT_EQ(enc.lookChar(), EOF);
}

TEST_F(RGBGrayEncoderTest_236, RewindRestoresDeterministicOutput_236) {
  // Use a modest payload; we do not assume any particular encoding math.
  std::vector<unsigned char> payload;
  for (int i = 0; i < 64; ++i) {
    payload.push_back(static_cast<unsigned char>(i));
  }

  auto base = std::make_unique<VectorMemStream>(payload);
  RGBGrayEncoder enc(base.get());

  ASSERT_TRUE(enc.rewind());
  const auto first = DrainToEof(enc, /*maxIters=*/100000);

  ASSERT_TRUE(enc.rewind());
  const auto second = DrainToEof(enc, /*maxIters=*/100000);

  EXPECT_EQ(first, second);
}

TEST_F(RGBGrayEncoderTest_236, LookCharIsStableAcrossRepeatedCalls_236) {
  auto base = std::make_unique<VectorMemStream>(std::vector<unsigned char>{10, 20, 30, 40, 50, 60});
  RGBGrayEncoder enc(base.get());

  ASSERT_TRUE(enc.rewind());

  const int a = enc.lookChar();
  const int b = enc.lookChar();
  // We don't assume what value is produced, only that repeated peeks are stable.
  EXPECT_EQ(a, b);

  // After consuming one char, the next lookChar should still be stable.
  (void)enc.getChar();
  const int c = enc.lookChar();
  const int d = enc.lookChar();
  EXPECT_EQ(c, d);
}

TEST_F(RGBGrayEncoderTest_236, HandlesNonMultipleOfThreeInputLengthsWithoutHanging_236) {
  // Boundary-ish lengths for an RGB->Gray type encoder: 1,2,3,4,5 bytes.
  for (int len = 1; len <= 5; ++len) {
    std::vector<unsigned char> payload;
    payload.reserve(len);
    for (int i = 0; i < len; ++i) {
      payload.push_back(static_cast<unsigned char>(0xA0 + i));
    }

    auto base = std::make_unique<VectorMemStream>(payload);
    RGBGrayEncoder enc(base.get());

    ASSERT_TRUE(enc.rewind());

    // Must terminate; output content is not asserted.
    const auto out = DrainToEof(enc, /*maxIters=*/10000);
    // Basic sanity: produced chars (if any) must be in byte range.
    for (int v : out) {
      EXPECT_GE(v, 0);
      EXPECT_LE(v, 255);
    }
  }
}

TEST_F(RGBGrayEncoderTest_236, SetPosDelegatesToUnderlyingAndDoesNotCrash_236) {
  auto base = std::make_unique<VectorMemStream>(std::vector<unsigned char>{1, 2, 3, 4, 5, 6, 7, 8, 9});
  RGBGrayEncoder enc(base.get());

  // FilterStream::setPos delegates; we only verify it can be called and subsequent reads terminate.
  enc.setPos(0);
  ASSERT_TRUE(enc.rewind()); // rewind should be safe after setPos usage
  (void)DrainToEof(enc, /*maxIters=*/10000);

  enc.setPos(3);
  (void)DrainToEof(enc, /*maxIters=*/10000);

  enc.setPos(-2, /*dir=*/-1); // near end
  (void)DrainToEof(enc, /*maxIters=*/10000);

  SUCCEED();
}