// TEST_ID: 210
// Unit tests for ASCIIHexEncoder (poppler/Stream.h)

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#if __has_include("poppler/Stream.h")
#include "poppler/Stream.h"
#elif __has_include("Stream.h")
#include "Stream.h"
#else
#error "Cannot find poppler Stream.h"
#endif

#if __has_include("poppler/Object.h")
#include "poppler/Object.h"
#elif __has_include("Object.h")
#include "Object.h"
#endif

namespace {

// Create a "null" Object in a way that compiles across multiple poppler variants.
// If Object exists but doesn't have these helpers, we fall back to default construction.
static Object MakeNullObjectIfPossible() {
#if defined(Object)
  Object obj;
  // Try common null initializers guarded by SFINAE-like tricks (C++17 friendly).
  // We can't use requires() here, so we use overload resolution with pointers.
  struct Helper {
    static void InitNull(Object* o, int) {
      // Most older poppler: initNull()
      o->initNull();
    }
    static void InitNull(Object* /*o*/, long) {
      // Fallback: do nothing (default constructed object might already be null)
    }
  };
  // If initNull() exists, the first overload is viable; otherwise second is chosen.
  // We simulate this by taking the address of the member if it exists.
  // Note: This is intentionally conservative; if initNull doesn't exist we just skip.
  // (Some poppler versions use setToNull(), setToNull(), or constructors.)
  // Try initNull:
  (void)sizeof(&Object::initNull);  // may fail if initNull doesn't exist
  Helper::InitNull(&obj, 0);
  return obj;
#else
  return Object{};
#endif
}

// A helper that builds a MemStream in a version-tolerant way.
// We try a few known constructor shapes using std::is_constructible.
static std::unique_ptr<Stream> MakeMemStreamFromBytes(std::vector<unsigned char>& storage) {
  // Ensure stable backing storage.
  if (storage.empty()) {
    // Still provide a non-null pointer and length=0 where possible.
  }

  // Some poppler versions use Guint; use size_t and cast where needed.
  const auto len = static_cast<std::size_t>(storage.size());

  // Prepare dict argument in multiple forms.
#if defined(Object)
  Object dictObj = MakeNullObjectIfPossible();
#endif

  // Candidate 1: MemStream(char *bufA, Guint startA, Guint lengthA, Object *dictA)
#if defined(Object)
  if constexpr (std::is_constructible_v<MemStream, char*, Guint, Guint, Object*>) {
    return std::unique_ptr<Stream>(
        new MemStream(reinterpret_cast<char*>(storage.data()),
                      static_cast<Guint>(0),
                      static_cast<Guint>(len),
                      &dictObj));
  }
#endif

  // Candidate 2: MemStream(const char *bufA, Guint startA, Guint lengthA, Object *dictA)
#if defined(Object)
  if constexpr (std::is_constructible_v<MemStream, const char*, Guint, Guint, Object*>) {
    return std::unique_ptr<Stream>(
        new MemStream(reinterpret_cast<const char*>(storage.data()),
                      static_cast<Guint>(0),
                      static_cast<Guint>(len),
                      &dictObj));
  }
#endif

  // Candidate 3: MemStream(char *bufA, size_t startA, size_t lengthA, Object *dictA)
#if defined(Object)
  if constexpr (std::is_constructible_v<MemStream, char*, std::size_t, std::size_t, Object*>) {
    return std::unique_ptr<Stream>(
        new MemStream(reinterpret_cast<char*>(storage.data()), 0u, len, &dictObj));
  }
#endif

  // Candidate 4: MemStream(const char *bufA, size_t startA, size_t lengthA, Object *dictA)
#if defined(Object)
  if constexpr (std::is_constructible_v<MemStream, const char*, std::size_t, std::size_t, Object*>) {
    return std::unique_ptr<Stream>(
        new MemStream(reinterpret_cast<const char*>(storage.data()), 0u, len, &dictObj));
  }
#endif

  // Candidate 5: Some newer poppler variants take an Object by value/rvalue.
#if defined(Object)
  if constexpr (std::is_constructible_v<MemStream, const unsigned char*, std::size_t, Object&&>) {
    return std::unique_ptr<Stream>(
        new MemStream(storage.data(), len, std::move(dictObj)));
  }
  if constexpr (std::is_constructible_v<MemStream, const char*, std::size_t, Object&&>) {
    return std::unique_ptr<Stream>(
        new MemStream(reinterpret_cast<const char*>(storage.data()), len, std::move(dictObj)));
  }
#endif

  // Candidate 6: MemStream(const unsigned char*, size_t) or similar (no dict)
  if constexpr (std::is_constructible_v<MemStream, const unsigned char*, std::size_t>) {
    return std::unique_ptr<Stream>(new MemStream(storage.data(), len));
  }
  if constexpr (std::is_constructible_v<MemStream, const char*, std::size_t>) {
    return std::unique_ptr<Stream>(new MemStream(reinterpret_cast<const char*>(storage.data()), len));
  }

  return nullptr;
}

static std::string ReadAllChars(Stream& s) {
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

class ASCIIHexEncoderTest_210 : public ::testing::Test {};

TEST_F(ASCIIHexEncoderTest_210, EmptyInputProducesOnlyTerminator_210) {
  std::vector<unsigned char> bytes;  // empty
  auto base = MakeMemStreamFromBytes(bytes);
  ASSERT_NE(base, nullptr);

  ASCIIHexEncoder enc(base.get());

  const std::string out = ReadAllChars(enc);
  // Observable behavior: encoder must produce some output and then EOF.
  // For ASCIIHex encoding, empty input should terminate immediately.
  EXPECT_EQ(out, std::string(">"));
  EXPECT_EQ(enc.getChar(), EOF);
  EXPECT_EQ(enc.lookChar(), EOF);
}

TEST_F(ASCIIHexEncoderTest_210, LookCharDoesNotConsumeAndMatchesGetChar_210) {
  std::vector<unsigned char> bytes = {0xAB};  // should encode to "ab" then ">"
  auto base = MakeMemStreamFromBytes(bytes);
  ASSERT_NE(base, nullptr);

  ASCIIHexEncoder enc(base.get());

  const int c1 = enc.lookChar();
  ASSERT_NE(c1, EOF);

  const int c2 = enc.lookChar();
  EXPECT_EQ(c2, c1) << "lookChar() should not consume";

  const int g1 = enc.getChar();
  EXPECT_EQ(g1, c1) << "getChar() should return the same next character as lookChar()";

  // After consuming one char, next char should differ for this input (most likely),
  // but we only assert the stream progresses.
  const int next = enc.lookChar();
  EXPECT_NE(next, EOF);
}

TEST_F(ASCIIHexEncoderTest_210, EncodesSingleByteToLowercaseHexAndTerminates_210) {
  std::vector<unsigned char> bytes = {0xAB};
  auto base = MakeMemStreamFromBytes(bytes);
  ASSERT_NE(base, nullptr);

  ASCIIHexEncoder enc(base.get());

  const std::string out = ReadAllChars(enc);
  // For a single byte 0xAB, ASCII hex encoding is "ab", then '>' terminator.
  EXPECT_EQ(out, std::string("ab>"));
}

TEST_F(ASCIIHexEncoderTest_210, InsertsNewlineAfter64EncodedChars_210) {
  // 33 bytes of 0x00 => 66 hex chars "00..." plus terminator.
  // Typical ASCIIHexEncoder inserts '\n' when line length reaches 64 before writing next pair.
  std::vector<unsigned char> bytes(33, 0x00);
  auto base = MakeMemStreamFromBytes(bytes);
  ASSERT_NE(base, nullptr);

  ASCIIHexEncoder enc(base.get());
  const std::string out = ReadAllChars(enc);

  // Expected: 32 bytes => 64 chars of "00" repeated, then '\n', then one more "00", then '>'.
  const std::string first64(64, '0');  // WRONG if we used '0' only; build explicitly.
  std::string expected;
  expected.reserve(64 + 1 + 2 + 1);
  for (int i = 0; i < 32; ++i) expected += "00";
  expected += "\n";
  expected += "00";
  expected += ">";

  EXPECT_EQ(out, expected);
}

TEST_F(ASCIIHexEncoderTest_210, RewindResetsOutputToBeginning_210) {
  std::vector<unsigned char> bytes = {0x01, 0x23};
  auto base = MakeMemStreamFromBytes(bytes);
  ASSERT_NE(base, nullptr);

  ASCIIHexEncoder enc(base.get());

  // Consume a few characters.
  const int a = enc.getChar();
  const int b = enc.getChar();
  ASSERT_NE(a, EOF);
  ASSERT_NE(b, EOF);

  // Rewind and ensure we see the same prefix again.
  const bool ok = enc.rewind();
  EXPECT_TRUE(ok);

  const int a2 = enc.getChar();
  const int b2 = enc.getChar();
  EXPECT_EQ(a2, a);
  EXPECT_EQ(b2, b);

  // And the rest is still readable to EOF.
  const std::string tail = ReadAllChars(enc);
  EXPECT_FALSE(tail.empty());
}

TEST_F(ASCIIHexEncoderTest_210, IsEncoderReturnsTrue_210) {
  std::vector<unsigned char> bytes = {0x00};
  auto base = MakeMemStreamFromBytes(bytes);
  ASSERT_NE(base, nullptr);

  ASCIIHexEncoder enc(base.get());
  EXPECT_TRUE(enc.isEncoder());
}

}  // namespace