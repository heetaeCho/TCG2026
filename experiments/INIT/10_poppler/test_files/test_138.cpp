// -*- mode: c++; -*-
// TEST_ID 138
//
// Unit tests for BaseSeekInputStream::unfilteredRewind() from poppler/Stream.h
//
// Constraints honored:
// - Treat implementation as black box (only verify observable behavior).
// - Do not access private/internal state of BaseSeekInputStream.
// - Use a derived test double only to observe virtual-call behavior of rewind().

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

// Poppler headers (project-local)
#include "poppler/Stream.h"
#include "poppler/Object.h"

namespace {

// A small test double that lets us observe whether unfilteredRewind()
// dispatches to rewind(), and what value/exception propagates out.
class TestBaseSeekInputStream final : public BaseSeekInputStream {
public:
  TestBaseSeekInputStream(bool rewindReturn, bool throwOnRewind = false)
      : BaseSeekInputStream(/*startA=*/0,
                            /*limitedA=*/false,
                            /*lengthA=*/0,
                            MakeNullDictObject()),
        rewindReturn_(rewindReturn),
        throwOnRewind_(throwOnRewind) {}

  bool rewind() override {
    ++rewindCalls_;
    if (throwOnRewind_) {
      throw std::runtime_error("rewind failed");
    }
    return rewindReturn_;
  }

  int rewindCalls() const { return rewindCalls_; }

  void setRewindReturn(bool v) { rewindReturn_ = v; }
  void setThrowOnRewind(bool v) { throwOnRewind_ = v; }

private:
  static Object MakeNullDictObject() {
    // We avoid assuming details about Object beyond being constructible/movable.
    // A default Object in Poppler is typically a "null" object, which is fine
    // for this test because unfilteredRewind() should only delegate to rewind().
    Object obj;
    return obj;
  }

  bool rewindReturn_ = false;
  bool throwOnRewind_ = false;
  int rewindCalls_ = 0;
};

class BaseSeekInputStreamTest_138 : public ::testing::Test {};

}  // namespace

TEST_F(BaseSeekInputStreamTest_138, UnfilteredRewindReturnsTrueWhenRewindReturnsTrue_138) {
  TestBaseSeekInputStream s(/*rewindReturn=*/true);

  EXPECT_TRUE(s.unfilteredRewind());
  EXPECT_EQ(s.rewindCalls(), 1);
}

TEST_F(BaseSeekInputStreamTest_138, UnfilteredRewindReturnsFalseWhenRewindReturnsFalse_138) {
  TestBaseSeekInputStream s(/*rewindReturn=*/false);

  EXPECT_FALSE(s.unfilteredRewind());
  EXPECT_EQ(s.rewindCalls(), 1);
}

TEST_F(BaseSeekInputStreamTest_138, UnfilteredRewindCallsRewindEachTimeWhenInvokedMultipleTimes_138) {
  TestBaseSeekInputStream s(/*rewindReturn=*/true);

  EXPECT_TRUE(s.unfilteredRewind());
  EXPECT_TRUE(s.unfilteredRewind());
  EXPECT_TRUE(s.unfilteredRewind());

  EXPECT_EQ(s.rewindCalls(), 3);
}

TEST_F(BaseSeekInputStreamTest_138, UnfilteredRewindPropagatesExceptionFromRewind_138) {
  TestBaseSeekInputStream s(/*rewindReturn=*/true, /*throwOnRewind=*/true);

  EXPECT_THROW({ (void)s.unfilteredRewind(); }, std::runtime_error);
  EXPECT_EQ(s.rewindCalls(), 1);
}