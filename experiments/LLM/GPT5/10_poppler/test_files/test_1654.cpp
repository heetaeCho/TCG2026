// FlateEncoder_test_1654.cpp
#include <gtest/gtest.h>

#include "FlateEncoder.h"
#include "Stream.h"

#include <type_traits>
#include <utility>

namespace {

// A minimal Stream implementation suitable for constructing FilterStream-derived
// objects in unit tests without relying on any internal behavior.
class DummyStream final : public Stream {
public:
  DummyStream() = default;
  ~DummyStream() override = default;

  StreamKind getKind() const override { return strWeird; }

  void reset() override {}

  int getChar() override { return EOF; }
  int lookChar() override { return EOF; }

  int getUnfilteredChar() override { return EOF; }
  void unfilteredReset() override {}

  Goffset getPos() override { return 0; }
  void setPos(Goffset /*pos*/, int /*dir*/ = 0) override {}

  GooString *getPSFilter(int /*psLevel*/, const char * /*indent*/) override { return nullptr; }

  bool isBinary(bool /*last*/ = true) override { return true; }

  BaseStream *getBaseStream() override { return nullptr; }
  Stream *getUndecodedStream() override { return this; }

  Dict *getDict() override { return nullptr; }
  Object *getDictObject() override { return nullptr; }

  Stream *getNextStream() const override { return nullptr; }
};

// Handle Poppler API variations where isEncoder() may be const or non-const.
template <typename T>
bool CallIsEncoder(T &obj) {
  if constexpr (std::is_invocable_r_v<bool, decltype(&T::isEncoder), const T *>) {
    return std::as_const(obj).isEncoder();
  } else {
    return obj.isEncoder();
  }
}

class FlateEncoderTest_1654 : public ::testing::Test {
protected:
  DummyStream dummy_;
};

} // namespace

TEST_F(FlateEncoderTest_1654, IsEncoderReturnsTrue_1654) {
  FlateEncoder enc(&dummy_);
  EXPECT_TRUE(CallIsEncoder(enc));
}

TEST_F(FlateEncoderTest_1654, IsEncoderStableAcrossRepeatedCalls_1654) {
  FlateEncoder enc(&dummy_);
  const bool v1 = CallIsEncoder(enc);
  const bool v2 = CallIsEncoder(enc);
  const bool v3 = CallIsEncoder(enc);
  EXPECT_TRUE(v1);
  EXPECT_TRUE(v2);
  EXPECT_TRUE(v3);
}

TEST_F(FlateEncoderTest_1654, IsEncoderAccessibleViaReference_1654) {
  FlateEncoder enc(&dummy_);
  FlateEncoder &ref = enc;
  EXPECT_TRUE(CallIsEncoder(ref));
}

TEST_F(FlateEncoderTest_1654, IsEncoderDoesNotDependOnOtherCalls_1654) {
  FlateEncoder enc(&dummy_);

  // Boundary-ish usage: call unrelated inherited Stream API on the encoder object
  // (via its public interface) and ensure isEncoder() is still true.
  // This does not assume any internal processing; it only checks the exposed result.
  (void)enc.getPos();
  (void)enc.lookChar();

  EXPECT_TRUE(CallIsEncoder(enc));
}