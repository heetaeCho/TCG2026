// base_seek_input_stream_getstart_tests_136.cpp
// Unit tests for BaseSeekInputStream::getStart()
// TEST_ID = 136

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "Stream.h"

// A tiny backend stream that provides data via the BaseSeekInputStream's virtual I/O hooks.
// This is a test collaborator (not a reimplementation of BaseSeekInputStream internals).
class TestSeekInputStreamBackend final : public BaseSeekInputStream {
public:
  TestSeekInputStreamBackend(Goffset startA, bool limitedA, Goffset lengthA, Object&& dictA,
                             std::string bytes)
      : BaseSeekInputStream(startA, limitedA, lengthA, std::move(dictA)),
        data_(bytes.begin(), bytes.end()),
        curPos_(0) {}

private:
  // Provide a simple backing store for reads; BaseSeekInputStream uses these via virtual dispatch.
  const Goffset currentPos() override { return curPos_; }

  void setCurrentPos(Goffset offset) override { curPos_ = offset; }

  Goffset read(char* buf, Goffset size) override {
    if (size <= 0) {
      return 0;
    }
    if (curPos_ < 0) {
      return 0;
    }
    const auto pos = static_cast<std::size_t>(curPos_);
    if (pos >= data_.size()) {
      return 0;
    }
    const std::size_t avail = data_.size() - pos;
    const std::size_t want = static_cast<std::size_t>(size);
    const std::size_t n = std::min(avail, want);
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos, n);
      curPos_ += static_cast<Goffset>(n);
    }
    return static_cast<Goffset>(n);
  }

  std::vector<char> data_;
  Goffset curPos_;
};

class BaseSeekInputStreamGetStartTest_136 : public ::testing::Test {
protected:
  static Object MakeDictObject() {
    // Keep this intentionally minimal: we only need an Object instance to satisfy the ctor.
    // The concrete Object implementation is provided by the codebase.
    Object o;
    return o;
  }
};

TEST_F(BaseSeekInputStreamGetStartTest_136, GetStartReturnsConstructorStart_136) {
  const Goffset start = 123;
  Object dict = MakeDictObject();
  TestSeekInputStreamBackend s(start, /*limitedA=*/false, /*lengthA=*/0, std::move(dict), "");

  EXPECT_EQ(s.getStart(), start);
}

TEST_F(BaseSeekInputStreamGetStartTest_136, GetStartWorksForZeroStart_136) {
  const Goffset start = 0;
  Object dict = MakeDictObject();
  TestSeekInputStreamBackend s(start, /*limitedA=*/false, /*lengthA=*/0, std::move(dict), "abc");

  EXPECT_EQ(s.getStart(), start);
}

TEST_F(BaseSeekInputStreamGetStartTest_136, GetStartWorksForLargeStart_136) {
  const Goffset start = static_cast<Goffset>(1) << 40;  // large but reasonable for Goffset
  Object dict = MakeDictObject();
  TestSeekInputStreamBackend s(start, /*limitedA=*/false, /*lengthA=*/0, std::move(dict), "x");

  EXPECT_EQ(s.getStart(), start);
}

TEST_F(BaseSeekInputStreamGetStartTest_136, GetStartIsStableAcrossReads_136) {
  const Goffset start = 77;
  Object dict = MakeDictObject();
  TestSeekInputStreamBackend s(start, /*limitedA=*/false, /*lengthA=*/0, std::move(dict), "hi");

  const Goffset before = s.getStart();

  // Exercise observable public API; regardless of read outcome, getStart should remain consistent.
  (void)s.lookChar();
  (void)s.getChar();
  (void)s.getChar();      // possibly EOF
  (void)s.lookChar();     // possibly EOF
  (void)s.getUnfilteredChar();
  (void)s.getUnfilteredChar();

  EXPECT_EQ(s.getStart(), before);
}

TEST_F(BaseSeekInputStreamGetStartTest_136, MoveStartByZeroDoesNotChangeStart_136) {
  const Goffset start = 10;
  Object dict = MakeDictObject();
  TestSeekInputStreamBackend s(start, /*limitedA=*/false, /*lengthA=*/0, std::move(dict), "data");

  const Goffset before = s.getStart();
  s.moveStart(0);
  EXPECT_EQ(s.getStart(), before);
}