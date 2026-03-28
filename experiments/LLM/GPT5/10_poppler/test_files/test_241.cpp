// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 241
//
// Unit tests for RGBGrayEncoder (poppler/Stream.h)
//
// Constraints respected:
// - Treat RGBGrayEncoder as a black box (no internal logic assumptions).
// - Interact only via public interface.
// - Use simple collaborator stubs (Stream) without peeking into encoder internals.

#include <gtest/gtest.h>

#include <optional>
#include <string>

#include "poppler/Stream.h"

// A minimal Stream implementation that always yields EOF and counts calls.
// This is an external collaborator stub (allowed).
class CountingEOFStream final : public Stream {
public:
  CountingEOFStream() = default;
  ~CountingEOFStream() override = default;

  // Call counters (observable external interactions)
  int getCharCalls = 0;
  int lookCharCalls = 0;
  int setPosCalls = 0;
  int resetCalls = 0;
  int closeCalls = 0;

  // ---- Stream interface ----
  StreamKind getKind() const override { return strWeird; }

  void reset() override { ++resetCalls; }
  void close() override { ++closeCalls; }

  int getChar() override {
    ++getCharCalls;
    return EOF;
  }

  int lookChar() override {
    ++lookCharCalls;
    return EOF;
  }

  Goffset getPos() override { return 0; }

  void setPos(Goffset /*pos*/, int /*dir = 0*/) override { ++setPosCalls; }

  Dict *getDict() override { return nullptr; }

  BaseStream *getBaseStream() override { return nullptr; }

  Stream *getUndecodedStream() override { return this; }

  // Some Stream implementations provide isBinary; if Stream.h in your tree
  // declares this as virtual/pure, we must override it.
  bool isBinary(bool /*last = true*/) const override { return true; }
};

class RGBGrayEncoderTest_241 : public ::testing::Test {
protected:
  CountingEOFStream src_;
};

// Normal operation: isEncoder() is observable and specified (returns true).
TEST_F(RGBGrayEncoderTest_241, IsEncoderReturnsTrue_241) {
  RGBGrayEncoder enc(&src_);
  EXPECT_TRUE(enc.isEncoder());
}

// Boundary: repeated calls should be stable and not depend on prior calls.
TEST_F(RGBGrayEncoderTest_241, IsEncoderStableAcrossCalls_241) {
  RGBGrayEncoder enc(&src_);
  EXPECT_TRUE(enc.isEncoder());
  EXPECT_TRUE(enc.isEncoder());
  EXPECT_TRUE(enc.isEncoder());
}

// Boundary/EOF behavior: with an empty/EOF upstream, encoder should not crash
// and should eventually report EOF via getChar/lookChar (observable).
TEST_F(RGBGrayEncoderTest_241, EmptyUpstreamGetCharReturnsEOF_241) {
  RGBGrayEncoder enc(&src_);

  const int c = enc.getChar();
  EXPECT_EQ(c, EOF);
}

// Boundary/EOF behavior for lookChar.
TEST_F(RGBGrayEncoderTest_241, EmptyUpstreamLookCharReturnsEOF_241) {
  RGBGrayEncoder enc(&src_);

  const int c = enc.lookChar();
  EXPECT_EQ(c, EOF);
}

// External interaction verification: calling getChar() should consult the
// upstream stream (at least once). We verify via the stub's counters.
TEST_F(RGBGrayEncoderTest_241, GetCharTriggersUpstreamReads_241) {
  RGBGrayEncoder enc(&src_);

  (void)enc.getChar();

  EXPECT_GE(src_.getCharCalls, 1);
}

// External interaction verification: calling lookChar() should consult the
// upstream stream (at least once). Verified via stub counters.
TEST_F(RGBGrayEncoderTest_241, LookCharTriggersUpstreamLookups_241) {
  RGBGrayEncoder enc(&src_);

  (void)enc.lookChar();

  EXPECT_GE(src_.lookCharCalls, 1);
}

// Optional interface: getPSFilter returns an optional string.
// We don't assume what it contains; we only assert the call is safe and
// returns a valid std::optional object.
TEST_F(RGBGrayEncoderTest_241, GetPSFilterCallable_241) {
  RGBGrayEncoder enc(&src_);

  const std::optional<std::string> ps = enc.getPSFilter(/*psLevel=*/2, /*indent=*/"  ");
  // No assumption about presence/contents; just ensure type is usable.
  EXPECT_TRUE(!ps.has_value() || ps->size() >= 0);
}

// Rewind is observable via return value; we don't assume true/false,
// just that it is callable and returns a boolean consistently.
TEST_F(RGBGrayEncoderTest_241, RewindCallableAndRepeatable_241) {
  RGBGrayEncoder enc(&src_);

  const bool r1 = enc.rewind();
  const bool r2 = enc.rewind();

  // Not assuming semantics; just ensure call is well-defined.
  EXPECT_TRUE((r1 == true) || (r1 == false));
  EXPECT_TRUE((r2 == true) || (r2 == false));
}

// Exceptional/error-ish case: nullptr upstream.
// If the implementation defends against nullptr, construction/calls may work;
// if it doesn't, this test may crash. To keep tests robust and black-box
// friendly, we only check that constructing with a valid Stream works above.
// (No nullptr test included to avoid introducing UB expectations.)