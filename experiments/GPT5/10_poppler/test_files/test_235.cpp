// TEST_ID = 235
// Unit tests for CMYKGrayEncoder (poppler/Stream.h)

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Stream.h"

using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class DummyStream_235 final : public Stream {
public:
  explicit DummyStream_235(std::vector<unsigned char> data) : data_(std::move(data)) {}

  StreamKind getKind() const override { return strWeird; }

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

  int getUnfilteredChar() override { return getChar(); }

  bool unfilteredRewind() override { return rewind(); }

  Goffset getPos() override { return static_cast<Goffset>(pos_); }

  void setPos(Goffset pos, int dir = 0) override {
    // Minimal, predictable seek behavior for tests.
    long long base = 0;
    if (dir < 0) {
      base = static_cast<long long>(data_.size());
    } else {
      base = 0;
    }
    long long target = base + static_cast<long long>(pos);
    if (target < 0) {
      target = 0;
    }
    if (target > static_cast<long long>(data_.size())) {
      target = static_cast<long long>(data_.size());
    }
    pos_ = static_cast<size_t>(target);
  }

  bool isBinary(bool /*last*/ = true) const override { return false; }

  BaseStream *getBaseStream() override { return nullptr; }
  Stream *getUndecodedStream() override { return this; }
  Dict *getDict() override { return nullptr; }
  Object *getDictObject() override { return nullptr; }

private:
  std::vector<unsigned char> data_;
  size_t pos_ = 0;
};

class MockStream_235 : public Stream {
public:
  MOCK_METHOD(StreamKind, getKind, (), (const, override));
  MOCK_METHOD(bool, rewind, (), (override));
  MOCK_METHOD(int, getChar, (), (override));
  MOCK_METHOD(int, lookChar, (), (override));
  MOCK_METHOD(int, getUnfilteredChar, (), (override));
  MOCK_METHOD(bool, unfilteredRewind, (), (override));
  MOCK_METHOD(Goffset, getPos, (), (override));
  MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
  MOCK_METHOD(bool, isBinary, (bool last), (const, override));
  MOCK_METHOD(BaseStream *, getBaseStream, (), (override));
  MOCK_METHOD(Stream *, getUndecodedStream, (), (override));
  MOCK_METHOD(Dict *, getDict, (), (override));
  MOCK_METHOD(Object *, getDictObject, (), (override));
};

class CMYKGrayEncoderTest_235 : public ::testing::Test {};

TEST_F(CMYKGrayEncoderTest_235, IsEncoderReturnsTrue_235) {
  DummyStream_235 src({'a', 'b', 'c', 'd'});
  CMYKGrayEncoder enc(&src);

  EXPECT_TRUE(enc.isEncoder());
  const CMYKGrayEncoder &cenc = enc;
  EXPECT_TRUE(cenc.isEncoder());
}

TEST_F(CMYKGrayEncoderTest_235, IsEncoderTrueViaBasePointer_235) {
  DummyStream_235 src({'x'});
  CMYKGrayEncoder enc(&src);

  Stream *asStream = &enc;
  EXPECT_TRUE(asStream->isEncoder());
}

TEST_F(CMYKGrayEncoderTest_235, IsEncoderRemainsTrueAfterUseAndEof_235) {
  DummyStream_235 src({}); // empty input (boundary)
  CMYKGrayEncoder enc(&src);

  EXPECT_TRUE(enc.isEncoder());

  // Boundary behavior: getting from empty stream should be EOF; encoder property should remain true.
  EXPECT_EQ(enc.lookChar(), EOF);
  EXPECT_EQ(enc.getChar(), EOF);
  EXPECT_TRUE(enc.isEncoder());

  // Rewind should be callable; encoder property should remain true.
  (void)enc.rewind();
  EXPECT_TRUE(enc.isEncoder());
}

TEST_F(CMYKGrayEncoderTest_235, RewindCallsUnderlyingStream_235) {
  NiceMock<MockStream_235> src;

  // Provide safe defaults for required pure-virtuals.
  ON_CALL(src, getKind()).WillByDefault(Return(strWeird));
  ON_CALL(src, rewind()).WillByDefault(Return(true));
  ON_CALL(src, unfilteredRewind()).WillByDefault(Return(true));
  ON_CALL(src, getChar()).WillByDefault(Return(EOF));
  ON_CALL(src, lookChar()).WillByDefault(Return(EOF));
  ON_CALL(src, getUnfilteredChar()).WillByDefault(Return(EOF));
  ON_CALL(src, getPos()).WillByDefault(Return(0));
  ON_CALL(src, setPos(testing::_, testing::_)).WillByDefault(testing::Return());
  ON_CALL(src, isBinary(testing::_)).WillByDefault(Return(false));
  ON_CALL(src, getBaseStream()).WillByDefault(Return(nullptr));
  ON_CALL(src, getUndecodedStream()).WillByDefault(Return(&src));
  ON_CALL(src, getDict()).WillByDefault(Return(nullptr));
  ON_CALL(src, getDictObject()).WillByDefault(Return(nullptr));

  CMYKGrayEncoder enc(&src);

  // Observable external interaction: encoder rewind should (at least) ask the underlying stream to rewind.
  EXPECT_CALL(src, rewind()).Times(AtLeast(1));
  EXPECT_TRUE(enc.rewind());
  EXPECT_TRUE(enc.isEncoder());
}

} // namespace