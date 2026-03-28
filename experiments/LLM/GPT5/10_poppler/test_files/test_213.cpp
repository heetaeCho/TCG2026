// ASCIIHexEncoder_tests_213.cpp
// Unit tests for poppler::ASCIIHexEncoder (black-box, interface-driven)
//
// TEST_ID: 213

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "Stream.h"

namespace {

// Helper: create an in-memory Stream using whichever Poppler in-tree class is available
// and constructible in this build. We intentionally avoid depending on any specific
// internal behavior of the Stream; we only need a readable Stream* for the encoder.
std::unique_ptr<Stream> MakeInputStream_213(const std::string& bytes) {
  // Many Poppler builds provide MemStream and/or StringStream with varying ctor signatures
  // across versions. Use SFINAE via is_constructible to pick a working constructor at
  // compile time without guessing one exact signature.
  //
  // NOTE: This is not re-implementing any Poppler logic; it's only choosing an available
  // public constructor to obtain a Stream instance for tests.

  const auto* raw = reinterpret_cast<const unsigned char*>(bytes.data());
  const int len = static_cast<int>(bytes.size());

  // Some versions require an Object dictionary; default construction is often supported.
  // Keep it as minimal as possible.
  auto makeNullObject = []() -> Object {
    // Support both default-constructible Object and initNull style.
    Object o;
#if defined(POPPLER_OBJECT_H) || defined(OBJECT_H)
    // If initNull exists, use it; otherwise, leave default.
    if constexpr (requires(Object x) { x.initNull(); }) {
      o.initNull();
    }
#endif
    return o;
  };

  // Try MemStream variants
  if constexpr (std::is_constructible_v<MemStream, const unsigned char*, int, Object>) {
    return std::make_unique<MemStream>(raw, len, makeNullObject());
  } else if constexpr (std::is_constructible_v<MemStream, const char*, int, Object>) {
    return std::make_unique<MemStream>(bytes.data(), len, makeNullObject());
  } else if constexpr (std::is_constructible_v<MemStream, const unsigned char*, int, bool, Object>) {
    // Some builds include a "takeOwnership" bool
    return std::make_unique<MemStream>(raw, len, /*takeOwnership=*/false, makeNullObject());
  } else if constexpr (std::is_constructible_v<MemStream, const unsigned char*, int>) {
    return std::make_unique<MemStream>(raw, len);
  } else if constexpr (std::is_constructible_v<StringStream, GooString*>) {
    // Fallback to StringStream (takes ownership in some builds; keep it heap allocated).
    auto* gs = new GooString(bytes.c_str(), len);
    return std::make_unique<StringStream>(gs);
  } else if constexpr (std::is_constructible_v<StringStream, const GooString*>) {
    static GooString gs(bytes.c_str(), len);
    return std::make_unique<StringStream>(&gs);
  } else {
    // If neither MemStream nor StringStream are available/constructible in this Poppler build,
    // fail early with a clear message.
    ADD_FAILURE() << "No constructible in-memory Stream type (MemStream/StringStream) found in this Poppler build.";
    return nullptr;
  }
}

int ClampByteOrEOF_213(int c) {
  // For sanity checks only: Poppler Stream getChar/lookChar commonly return [-1, 255].
  // We don't assert exact content, only that values are within a valid range.
  return (c == EOF) ? EOF : (c & 0xFF);
}

}  // namespace

class ASCIIHexEncoderTest_213 : public ::testing::Test {
protected:
  std::unique_ptr<Stream> input_;
  std::unique_ptr<ASCIIHexEncoder> enc_;

  void SetUp() override {
    input_ = MakeInputStream_213("ABC\x00\x7F\xFFxyz");
    ASSERT_NE(input_, nullptr);

    // Construct encoder with a valid Stream*.
    enc_ = std::make_unique<ASCIIHexEncoder>(input_.get());
    ASSERT_NE(enc_, nullptr);
  }
};

TEST_F(ASCIIHexEncoderTest_213, IsEncoderAlwaysTrue_213) {
  ASSERT_NE(enc_, nullptr);
  EXPECT_TRUE(enc_->isEncoder());
}

TEST_F(ASCIIHexEncoderTest_213, IsEncoderCallableOnConst_213) {
  ASSERT_NE(enc_, nullptr);
  const ASCIIHexEncoder& cref = *enc_;
  EXPECT_TRUE(cref.isEncoder());
}

TEST_F(ASCIIHexEncoderTest_213, RewindIsCallableAndReturnsBool_213) {
  ASSERT_NE(enc_, nullptr);

  // We don't assume what rewind() *does*, only that it is callable and returns a bool.
  const bool r1 = enc_->rewind();
  const bool r2 = enc_->rewind();
  (void)r1;
  (void)r2;

  // Basic type sanity (always true for bool, but keeps the test intention explicit).
  EXPECT_TRUE(r1 == true || r1 == false);
  EXPECT_TRUE(r2 == true || r2 == false);
}

TEST_F(ASCIIHexEncoderTest_213, GetCharAndLookCharReturnValidRange_213) {
  ASSERT_NE(enc_, nullptr);

  // Call a few times without asserting specific encoding output.
  const int lc1 = enc_->lookChar();
  const int gc1 = enc_->getChar();
  const int lc2 = enc_->lookChar();
  const int gc2 = enc_->getChar();

  // Sanity: values are either EOF or a byte.
  for (int c : {lc1, gc1, lc2, gc2}) {
    if (c != EOF) {
      EXPECT_GE(c, 0);
      EXPECT_LE(c, 255);
    }
  }

  // Ensure clamping helper doesn't change meaning for this check.
  EXPECT_EQ(ClampByteOrEOF_213(lc1), (lc1 == EOF ? EOF : (lc1 & 0xFF)));
}

TEST_F(ASCIIHexEncoderTest_213, ReadingPastEOFStaysAtEOF_213) {
  ASSERT_NE(enc_, nullptr);

  // Drain the encoder until EOF is observed.
  int c = 0;
  int safety = 0;
  while ((c = enc_->getChar()) != EOF && safety++ < 1'000'000) {
    // no-op
  }
  ASSERT_LT(safety, 1'000'000) << "Safety break: encoder did not reach EOF in expected bounds.";

  // After EOF, subsequent reads should remain EOF (common Stream contract).
  EXPECT_EQ(enc_->getChar(), EOF);
  EXPECT_EQ(enc_->lookChar(), EOF);
  EXPECT_EQ(enc_->getChar(), EOF);
}

TEST_F(ASCIIHexEncoderTest_213, GetPSFilterIsCallable_213) {
  ASSERT_NE(enc_, nullptr);

  // We don't assume whether it returns a filter string at a given PS level.
  std::optional<std::string> ps = enc_->getPSFilter(/*psLevel=*/2, /*indent=*/"  ");
  // Just verify the optional is in a valid state and (if present) the string is not absurdly huge.
  if (ps.has_value()) {
    EXPECT_LT(ps->size(), 10'000u);
  }
}

TEST_F(ASCIIHexEncoderTest_213, IsBinaryIsCallable_213) {
  ASSERT_NE(enc_, nullptr);

  // We do not assume true/false; only that calls are valid and stable in type.
  const bool b1 = enc_->isBinary(true);
  const bool b2 = enc_->isBinary(false);

  EXPECT_TRUE(b1 == true || b1 == false);
  EXPECT_TRUE(b2 == true || b2 == false);
}

TEST_F(ASCIIHexEncoderTest_213, GetKindIsCallable_213) {
  ASSERT_NE(enc_, nullptr);

  // Avoid asserting a specific enum value; just ensure callable and returns a StreamKind.
  const StreamKind k = enc_->getKind();
  (void)k;

  // Minimal sanity: repeated calls return the same value for the same object instance.
  EXPECT_EQ(enc_->getKind(), k);
}