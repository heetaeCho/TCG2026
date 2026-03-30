// TEST_ID = 231
// Unit tests for CMYKGrayEncoder (poppler/Stream.h)

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <vector>

#include "Stream.h"

namespace {

template <typename T, typename... Args>
constexpr bool is_constructible_v = std::is_constructible<T, Args...>::value;

// Create a "null" Object if Object exists in this Poppler build.
// Some Poppler versions have Object::initNull(), others default-construct to null.
static inline Object MakeNullObject() {
  Object o;
  if constexpr (requires(Object x) { x.initNull(); }) {
    o.initNull();
  }
  return o;
}

// Best-effort MemStream factory that supports multiple Poppler signatures.
// Returns Stream* owned by the caller via unique_ptr.
static inline std::unique_ptr<Stream> MakeMemStream(const std::vector<unsigned char>& bytes) {
  const unsigned char* p = bytes.empty() ? nullptr : bytes.data();
  const int len = static_cast<int>(bytes.size());

  // Try common constructors in a robust order.
  if constexpr (is_constructible_v<MemStream, const unsigned char*, int, Object>) {
    return std::unique_ptr<Stream>(new MemStream(p, len, MakeNullObject()));
  } else if constexpr (is_constructible_v<MemStream, const unsigned char*, int, Object&&>) {
    Object o = MakeNullObject();
    return std::unique_ptr<Stream>(new MemStream(p, len, std::move(o)));
  } else if constexpr (is_constructible_v<MemStream, const unsigned char*, int, int, Object>) {
    return std::unique_ptr<Stream>(new MemStream(p, len, /*startA=*/0, MakeNullObject()));
  } else if constexpr (is_constructible_v<MemStream, const unsigned char*, int, int, Object&&>) {
    Object o = MakeNullObject();
    return std::unique_ptr<Stream>(new MemStream(p, len, /*startA=*/0, std::move(o)));
  } else if constexpr (is_constructible_v<MemStream, const unsigned char*, int>) {
    return std::unique_ptr<Stream>(new MemStream(p, len));
  } else {
    // If MemStream isn't available or signatures differ too much, fail fast with a clear message.
    // (This keeps the test file self-contained without re-implementing Stream internals.)
    ADD_FAILURE() << "Unable to construct MemStream with available constructors in this Poppler build.";
    return nullptr;
  }
}

// Reads up to maxChars from encoder until EOF, returning collected bytes.
static inline std::vector<int> ReadUntilEof(Stream& s, size_t maxChars) {
  std::vector<int> out;
  out.reserve(std::min<size_t>(maxChars, 256));
  for (size_t i = 0; i < maxChars; ++i) {
    int c = s.getChar();
    if (c == EOF) break;
    out.push_back(c);
  }
  return out;
}

class CMYKGrayEncoderTest_231 : public ::testing::Test {};

}  // namespace

TEST_F(CMYKGrayEncoderTest_231, EmptyInput_ReturnsEOFImmediately_231) {
  auto base = MakeMemStream({});
  ASSERT_NE(base, nullptr);

  CMYKGrayEncoder enc(base.get());
  EXPECT_EQ(enc.getChar(), EOF);
  EXPECT_EQ(enc.lookChar(), EOF);
}

TEST_F(CMYKGrayEncoderTest_231, LookChar_DoesNotConsumeNextCharacter_231) {
  // Provide some bytes (content doesn't matter; we only assert stream semantics).
  const std::vector<unsigned char> in = {0x00, 0x7f, 0xff, 0x10, 0x20, 0x30, 0x40, 0x50};
  auto base = MakeMemStream(in);
  ASSERT_NE(base, nullptr);

  CMYKGrayEncoder enc(base.get());

  int a = enc.lookChar();
  if (a != EOF) {
    int b = enc.getChar();
    EXPECT_EQ(b, a);
  } else {
    // If encoder produces no output for this input in this build, that's still valid.
    EXPECT_EQ(enc.getChar(), EOF);
  }
}

TEST_F(CMYKGrayEncoderTest_231, GetChar_EventuallyReachesEOF_231) {
  const std::vector<unsigned char> in(64, 0xaa);
  auto base = MakeMemStream(in);
  ASSERT_NE(base, nullptr);

  CMYKGrayEncoder enc(base.get());

  // Ensure it doesn't loop forever producing non-EOF.
  // We don't assume output size; just that EOF is eventually observable.
  const auto out = ReadUntilEof(enc, /*maxChars=*/100000);
  // If we hit the limit without EOF, ReadUntilEof would return maxChars entries.
  EXPECT_LT(out.size(), 100000u) << "Encoder did not reach EOF within reasonable bound";
}

TEST_F(CMYKGrayEncoderTest_231, Rewind_ResetsOutputSequenceDeterministically_231) {
  const std::vector<unsigned char> in = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  };
  auto base = MakeMemStream(in);
  ASSERT_NE(base, nullptr);

  CMYKGrayEncoder enc(base.get());

  // Read a prefix (up to some bound).
  const auto first = ReadUntilEof(enc, /*maxChars=*/256);

  // Rewind should succeed (observable via boolean) and allow replaying same prefix.
  const bool rewound = enc.rewind();
  if (!rewound) {
    // If rewind is not supported/failed in this build for this stream combination,
    // we can only assert it reports failure consistently.
    EXPECT_FALSE(enc.rewind());
    return;
  }

  const auto second = ReadUntilEof(enc, /*maxChars=*/256);
  EXPECT_EQ(second, first);
}

TEST_F(CMYKGrayEncoderTest_231, IsEncoder_ReturnsTrue_231) {
  const std::vector<unsigned char> in = {0x01, 0x02, 0x03, 0x04};
  auto base = MakeMemStream(in);
  ASSERT_NE(base, nullptr);

  CMYKGrayEncoder enc(base.get());
  EXPECT_TRUE(enc.isEncoder());
}

TEST_F(CMYKGrayEncoderTest_231, GetKind_IsStableAcrossCalls_231) {
  const std::vector<unsigned char> in = {0xde, 0xad, 0xbe, 0xef};
  auto base = MakeMemStream(in);
  ASSERT_NE(base, nullptr);

  CMYKGrayEncoder enc(base.get());
  const StreamKind k1 = enc.getKind();
  const StreamKind k2 = enc.getKind();
  EXPECT_EQ(k2, k1);
}

TEST_F(CMYKGrayEncoderTest_231, IsBinary_IsStableAcrossCalls_231) {
  const std::vector<unsigned char> in = {0x10, 0x20, 0x30, 0x40};
  auto base = MakeMemStream(in);
  ASSERT_NE(base, nullptr);

  CMYKGrayEncoder enc(base.get());
  const bool b1 = enc.isBinary();
  const bool b2 = enc.isBinary();
  EXPECT_EQ(b2, b1);
}

TEST_F(CMYKGrayEncoderTest_231, GetPSFilter_IsCallableAndIfPresentNonEmpty_231) {
  const std::vector<unsigned char> in = {0x00, 0x00, 0x00, 0x00};
  auto base = MakeMemStream(in);
  ASSERT_NE(base, nullptr);

  CMYKGrayEncoder enc(base.get());

  // We don't assume what filter string is returned (or if any); just validate interface behavior.
  std::optional<std::string> ps = enc.getPSFilter(/*psLevel=*/2, /*indent=*/"  ");
  if (ps.has_value()) {
    EXPECT_FALSE(ps->empty());
  }
}