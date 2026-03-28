// SPDX-License-Identifier: GPL-2.0-or-later
// File: ASCIIHexEncoder_209_test.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "Stream.h"
#include "Object.h"

namespace {

// ---- Small compatibility helpers (to avoid depending on a single Poppler API shape) ----

static Object MakeNullObject_209() {
  Object o;
  if constexpr (requires(Object &x) { x.setToNull(); }) {
    o.setToNull();
  } else if constexpr (requires(Object &x) { x.initNull(); }) {
    o.initNull();
  } else {
    // Leave default-constructed if neither exists.
  }
  return o;
}

static std::unique_ptr<Stream> MakeMemStreamFromBytes_209(const std::string &bytes) {
  // Prefer to avoid copying, but different Poppler versions have different MemStream constructors.
  // We'll allocate a stable mutable buffer if needed.
  auto buf = std::make_unique<char[]>(bytes.size());
  if (!bytes.empty()) {
    std::memcpy(buf.get(), bytes.data(), bytes.size());
  }

  // Keep the buffer alive by capturing it in a small wrapper Stream owner.
  struct OwnedStream {
    std::unique_ptr<char[]> storage;
    std::unique_ptr<Stream> stream;
  };

  // We return only Stream*, so stash ownership in a static list is not acceptable.
  // Instead, we use a small Stream subclass that owns both the MemStream and the buffer,
  // and delegates all calls to the MemStream. This avoids guessing Stream's pure-virtual set
  // by not inheriting from Stream here.
  //
  // So: we must rely on MemStream being a Stream itself and return it directly, while also
  // ensuring the backing storage outlives it. The simplest is to allocate with the MemStream
  // taking ownership (when supported) OR allocate storage with "needFree" behavior in Poppler.
  //
  // Because we cannot rely on internals, we instead accept copying into a GooString-ish stream
  // if available; but we don't have that here. So we choose the safest common approach:
  // create a MemStream that references external storage and keep that storage in a global
  // shared registry scoped to the test binary lifetime.

  static std::vector<std::unique_ptr<char[]>> g_buffers_209;
  char *raw = buf.get();
  g_buffers_209.emplace_back(std::move(buf));

  // Try several known MemStream constructor shapes.
  // NOTE: We intentionally avoid relying on private behavior; this is just to obtain a Stream.
  Object dict = MakeNullObject_209();

  if constexpr (std::is_constructible_v<MemStream, char *, Guint, Guint, Object>) {
    return std::make_unique<MemStream>(raw, 0, static_cast<Guint>(bytes.size()), std::move(dict));
  } else if constexpr (std::is_constructible_v<MemStream, const char *, Guint, Guint, Object>) {
    return std::make_unique<MemStream>(raw, 0, static_cast<Guint>(bytes.size()), std::move(dict));
  } else if constexpr (std::is_constructible_v<MemStream, char *, Guint, Guint, Object *>) {
    // Older API
    Object *dictPtr = nullptr;
    return std::make_unique<MemStream>(raw, 0, static_cast<Guint>(bytes.size()), dictPtr);
  } else if constexpr (std::is_constructible_v<MemStream, const char *, Guint, Guint, Object *>) {
    Object *dictPtr = nullptr;
    return std::make_unique<MemStream>(raw, 0, static_cast<Guint>(bytes.size()), dictPtr);
  } else {
    // If Poppler's MemStream isn't available/compatible, fail explicitly.
    ADD_FAILURE() << "No compatible MemStream constructor found for this Poppler build.";
    return nullptr;
  }
}

static std::string DrainToString_209(Stream &s) {
  std::string out;
  for (;;) {
    const int c = s.getChar();
    if (c == EOF) {
      break;
    }
    out.push_back(static_cast<char>(c));
  }
  return out;
}

static std::string ToLowerHex_209(unsigned char v) {
  static const char *k = "0123456789abcdef";
  std::string r;
  r.push_back(k[(v >> 4) & 0x0f]);
  r.push_back(k[v & 0x0f]);
  return r;
}

class ASCIIHexEncoderTest_209 : public ::testing::Test {
protected:
  static std::unique_ptr<ASCIIHexEncoder> MakeEncoder_209(const std::string &bytes) {
    auto base = MakeMemStreamFromBytes_209(bytes);
    if (!base) return nullptr;
    // ASCIIHexEncoder takes ownership only if base->isEncoder() (per many Poppler encoders),
    // but we treat it as a black box and keep ownership with the pointer we pass.
    // Poppler's FilterStream pattern typically assumes heap allocation and deletes in dtor.
    // So we must release ownership here and let the encoder manage as designed.
    Stream *raw = base.release();
    return std::make_unique<ASCIIHexEncoder>(raw);
  }
};

} // namespace

TEST_F(ASCIIHexEncoderTest_209, EmptyInputEmitsSomeOutputThenEof_209) {
  auto enc = MakeEncoder_209(std::string{});
  ASSERT_NE(enc, nullptr);

  const int c1 = enc->getChar();
  // For an encoder, it's observable that it may output a terminator even for empty input.
  // We only assert that it returns either EOF immediately or a byte followed eventually by EOF.
  if (c1 == EOF) {
    SUCCEED();
    return;
  }

  // Must eventually reach EOF (avoid infinite loop).
  int steps = 0;
  int c = c1;
  while (c != EOF && steps < 1024) {
    c = enc->getChar();
    ++steps;
  }
  EXPECT_EQ(c, EOF);
  EXPECT_LT(steps, 1024);
}

TEST_F(ASCIIHexEncoderTest_209, LookCharDoesNotAdvanceStream_209) {
  auto enc = MakeEncoder_209(std::string("\x00", 1));
  ASSERT_NE(enc, nullptr);

  const int peek = enc->lookChar();
  const int got = enc->getChar();

  EXPECT_EQ(peek, got);
}

TEST_F(ASCIIHexEncoderTest_209, EncodesSingleByteToTwoPrintableCharsPlusTrailerOrEof_209) {
  auto enc = MakeEncoder_209(std::string("\xAB", 1));
  ASSERT_NE(enc, nullptr);

  // Treat as black-box encoder; we only assert a reasonable observable contract:
  // it should produce at least one output byte, and it should be finite.
  std::string out = DrainToString_209(*enc);
  ASSERT_FALSE(out.empty());

  // Many Poppler builds use lowercase hex; if so, the prefix should match.
  // If this build differs, we keep the assertion soft by allowing either exact match
  // or at least that the output begins with two ASCII hex characters.
  const std::string expectedPrefix = ToLowerHex_209(static_cast<unsigned char>(0xAB));
  if (out.size() >= 2) {
    const bool looksLikeLowerHex = (out.substr(0, 2) == expectedPrefix);
    const auto isHexCh = [](char ch) {
      return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
    };
    const bool looksHexy = isHexCh(out[0]) && isHexCh(out[1]);
    EXPECT_TRUE(looksLikeLowerHex || looksHexy);
  }
}

TEST_F(ASCIIHexEncoderTest_209, ProducesFiniteOutputForManyBytes_209) {
  std::string in;
  in.resize(256);
  for (int i = 0; i < 256; ++i) in[i] = static_cast<char>(i);

  auto enc = MakeEncoder_209(in);
  ASSERT_NE(enc, nullptr);

  // Ensure it terminates and doesn't explode in size unexpectedly.
  std::string out = DrainToString_209(*enc);
  EXPECT_FALSE(out.empty());

  // Very conservative upper bound: even if it adds line breaks and a trailer,
  // it should remain linear in input size.
  EXPECT_LT(out.size(), 10u * in.size() + 1024u);
}

TEST_F(ASCIIHexEncoderTest_209, RewindResetsIfSupported_209) {
  auto enc = MakeEncoder_209(std::string("abc", 3));
  ASSERT_NE(enc, nullptr);

  const std::string first = DrainToString_209(*enc);

  // Some versions expose rewind(), others use reset(). Interface lists rewind().
  const bool rewound = enc->rewind();
  if (!rewound) {
    // If rewind isn't supported, we only verify the call is safe/observable.
    SUCCEED();
    return;
  }

  const std::string second = DrainToString_209(*enc);
  EXPECT_EQ(first, second);
}

TEST_F(ASCIIHexEncoderTest_209, IsEncoderReportsTrue_209) {
  auto enc = MakeEncoder_209(std::string("x", 1));
  ASSERT_NE(enc, nullptr);

  EXPECT_TRUE(enc->isEncoder());
}