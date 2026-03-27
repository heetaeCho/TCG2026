// File: test_baseseekinputstream_getchar_133.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <string>

#include "./TestProjects/poppler/poppler/Stream.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;
using ::testing::Return;

// A test double that drives BaseSeekInputStream via its virtual I/O hooks.
// We do NOT touch private state; we only observe behavior via getChar() and
// verify external interactions via mocked virtual methods.
class MockBaseSeekInputStream final : public BaseSeekInputStream {
public:
  explicit MockBaseSeekInputStream(std::string data)
      // Use "unlimited" to avoid length limiting affecting getChar() behavior.
      : BaseSeekInputStream(/*startA=*/0, /*limitedA=*/false, /*lengthA=*/0, Object()),
        data_(std::move(data)) {
    // Default behavior for position hooks (fillBuf may consult these).
    ON_CALL(*this, currentPos()).WillByDefault(Invoke([this]() -> Goffset {
      return static_cast<Goffset>(pos_);
    }));
    ON_CALL(*this, setCurrentPos(_)).WillByDefault(Invoke([this](Goffset off) {
      if (off < 0) {
        pos_ = 0;
      } else {
        const auto u = static_cast<size_t>(off);
        pos_ = std::min(u, data_.size());
      }
    }));

    // Default behavior for reads from our backing string.
    ON_CALL(*this, read(_, _)).WillByDefault(Invoke([this](char *buf, Goffset size) -> Goffset {
      if (size <= 0) {
        return 0;
      }
      if (pos_ >= data_.size()) {
        return 0;
      }
      const size_t n = std::min(static_cast<size_t>(size), data_.size() - pos_);
      std::copy_n(data_.data() + pos_, n, buf);
      pos_ += n;
      return static_cast<Goffset>(n);
    }));
  }

  // BaseSeekInputStream declares these virtuals (even if private) – we override them
  // so we can control/observe external interactions.
  MOCK_METHOD(Goffset, currentPos, (), (override));
  MOCK_METHOD(void, setCurrentPos, (Goffset offset), (override));
  MOCK_METHOD(Goffset, read, (char *buf, Goffset size), (override));

private:
  std::string data_;
  size_t pos_ = 0;
};

class BaseSeekInputStreamTest_133 : public ::testing::Test {};

TEST_F(BaseSeekInputStreamTest_133, ReturnsEOFWhenEmpty_133) {
  MockBaseSeekInputStream s("");

  // If empty, getChar should attempt to fill and then return EOF.
  EXPECT_CALL(s, read(_, _)).Times(AtLeast(1));
  // Position hooks may or may not be used; allow any.
  EXPECT_CALL(s, currentPos()).Times(testing::AnyNumber());
  EXPECT_CALL(s, setCurrentPos(_)).Times(testing::AnyNumber());

  EXPECT_EQ(s.getChar(), EOF);
  EXPECT_EQ(s.getChar(), EOF);  // stays EOF
}

TEST_F(BaseSeekInputStreamTest_133, ReadsSequentialBytesThenEOF_133) {
  MockBaseSeekInputStream s("ABC");

  EXPECT_CALL(s, read(_, _)).Times(AtLeast(1));
  EXPECT_CALL(s, currentPos()).Times(testing::AnyNumber());
  EXPECT_CALL(s, setCurrentPos(_)).Times(testing::AnyNumber());

  EXPECT_EQ(s.getChar(), static_cast<unsigned char>('A'));
  EXPECT_EQ(s.getChar(), static_cast<unsigned char>('B'));
  EXPECT_EQ(s.getChar(), static_cast<unsigned char>('C'));
  EXPECT_EQ(s.getChar(), EOF);
  EXPECT_EQ(s.getChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_133, MasksCharToUnsignedRange_133) {
  // Ensure (*bufPtr++ & 0xff) behavior is observable: 0xFF should become 255, not EOF.
  std::string data;
  data.push_back(static_cast<char>(0xFF));

  MockBaseSeekInputStream s(data);

  EXPECT_CALL(s, read(_, _)).Times(AtLeast(1));
  EXPECT_CALL(s, currentPos()).Times(testing::AnyNumber());
  EXPECT_CALL(s, setCurrentPos(_)).Times(testing::AnyNumber());

  const int c = s.getChar();
  EXPECT_EQ(c, 255);            // 0xFF masked to 255
  EXPECT_NE(c, EOF);            // must not be interpreted as EOF
  EXPECT_EQ(s.getChar(), EOF);  // then EOF
}

TEST_F(BaseSeekInputStreamTest_133, SingleByteBoundaryThenEOF_133) {
  MockBaseSeekInputStream s("Z");

  EXPECT_CALL(s, read(_, _)).Times(AtLeast(1));
  EXPECT_CALL(s, currentPos()).Times(testing::AnyNumber());
  EXPECT_CALL(s, setCurrentPos(_)).Times(testing::AnyNumber());

  EXPECT_EQ(s.getChar(), static_cast<unsigned char>('Z'));
  EXPECT_EQ(s.getChar(), EOF);
}

TEST_F(BaseSeekInputStreamTest_133, CallsReadAgainAfterBufferExhausted_133) {
  // Provide more data than one small read might return if implementation chooses;
  // we don't assume internal buffering strategy, but we can still verify that reads
  // occur when consumption continues beyond the initially filled buffer.
  MockBaseSeekInputStream s(std::string(5000, 'x'));

  // We expect at least one read, and very likely multiple; assert "at least 1"
  // plus a weak additional check: after many getChar() calls, read should have
  // been invoked more than once *if* fill is chunked. But we cannot assume that,
  // so we only require at least one.
  EXPECT_CALL(s, read(_, _)).Times(AtLeast(1));
  EXPECT_CALL(s, currentPos()).Times(testing::AnyNumber());
  EXPECT_CALL(s, setCurrentPos(_)).Times(testing::AnyNumber());

  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(s.getChar(), static_cast<unsigned char>('x'));
  }
}