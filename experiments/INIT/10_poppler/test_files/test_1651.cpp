// FlateEncoder_lookChar_test_1651.cpp
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "Object.h"
#include "Stream.h"
#include "FlateEncoder.h"

namespace {

std::unique_ptr<Stream> MakeMemStreamFromBytes(const std::vector<unsigned char> &bytes)
{
  // MemStream typically expects a raw buffer with a stable lifetime.
  // Use a static backing store per-call by allocating and intentionally letting MemStream
  // manage it as appropriate for the Poppler build (some variants copy, some reference).
  // For tests, we keep ownership in a shared heap buffer that outlives the stream object.
  auto *buf = new unsigned char[bytes.size() == 0 ? 1 : bytes.size()];
  if (!bytes.empty()) {
    std::memcpy(buf, bytes.data(), bytes.size());
  }

  Object dict(objNull);
  auto *ms = new MemStream(reinterpret_cast<const char *>(buf),
                           /*startA=*/0,
                           /*lengthA=*/static_cast<Guint>(bytes.size()),
                           std::move(dict));
  ms->reset();
  return std::unique_ptr<Stream>(ms);
}

std::vector<unsigned char> DrainAll(Stream &s)
{
  std::vector<unsigned char> out;
  while (true) {
    const int c = s.getChar();
    if (c == EOF) {
      break;
    }
    out.push_back(static_cast<unsigned char>(c));
  }
  return out;
}

class FlateEncoderLookCharTest_1651 : public ::testing::Test {
};

} // namespace

TEST_F(FlateEncoderLookCharTest_1651, LookCharDoesNotConsumeAndMatchesGetChar_1651)
{
  // Non-empty input so we can observe lookChar() before consumption.
  const std::vector<unsigned char> input = {'H', 'e', 'l', 'l', 'o'};
  auto base = MakeMemStreamFromBytes(input);
  ASSERT_NE(base, nullptr);

  FlateEncoder enc(base.get());

  const int c1 = enc.lookChar();
  const int c2 = enc.lookChar();

  // lookChar should be stable when called repeatedly (no consumption).
  EXPECT_EQ(c1, c2);

  const int g1 = enc.getChar();
  // The next consumed character should match what lookChar reported.
  EXPECT_EQ(c1, g1);
}

TEST_F(FlateEncoderLookCharTest_1651, LookCharAfterSomeGetsMatchesNextGet_1651)
{
  const std::vector<unsigned char> input = {'A', 'B', 'C', 'D'};
  auto base = MakeMemStreamFromBytes(input);
  ASSERT_NE(base, nullptr);

  FlateEncoder enc(base.get());

  // Consume a few bytes.
  (void)enc.getChar();
  (void)enc.getChar();

  const int peek = enc.lookChar();
  const int next = enc.getChar();

  EXPECT_EQ(peek, next);
}

TEST_F(FlateEncoderLookCharTest_1651, LookCharReturnsEOFWhenStreamExhausted_1651)
{
  const std::vector<unsigned char> input = {'x'};
  auto base = MakeMemStreamFromBytes(input);
  ASSERT_NE(base, nullptr);

  FlateEncoder enc(base.get());

  // Drain everything via getChar().
  EXPECT_NE(enc.getChar(), EOF);
  EXPECT_EQ(enc.getChar(), EOF);

  // Once exhausted, lookChar should report EOF as well.
  EXPECT_EQ(enc.lookChar(), EOF);
}

TEST_F(FlateEncoderLookCharTest_1651, EmptyInputProducesImmediateEOF_1651)
{
  const std::vector<unsigned char> input = {};
  auto base = MakeMemStreamFromBytes(input);
  ASSERT_NE(base, nullptr);

  FlateEncoder enc(base.get());

  EXPECT_EQ(enc.lookChar(), EOF);
  EXPECT_EQ(enc.getChar(), EOF);
}

TEST_F(FlateEncoderLookCharTest_1651, RewindIfSupportedRestoresLookCharToInitialPosition_1651)
{
  const std::vector<unsigned char> input = {'1', '2', '3'};
  auto base = MakeMemStreamFromBytes(input);
  ASSERT_NE(base, nullptr);

  FlateEncoder enc(base.get());

  const int first_peek = enc.lookChar();
  const int first_get = enc.getChar();
  ASSERT_EQ(first_peek, first_get);

  // Move forward.
  (void)enc.getChar();

  const bool rewound = enc.rewind();
  if (!rewound) {
    // Some builds/streams may not support rewinding cleanly; this is observable via return.
    SUCCEED();
    return;
  }

  // After rewind, lookChar should again match the first byte that would be returned by getChar.
  const int rewind_peek = enc.lookChar();
  const int rewind_get = enc.getChar();
  EXPECT_EQ(rewind_peek, rewind_get);
  EXPECT_EQ(rewind_peek, first_peek);
}