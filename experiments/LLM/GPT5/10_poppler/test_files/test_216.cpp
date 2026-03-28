// ASCII85Encoder_216_test.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "Object.h"
#include "Stream.h"

namespace {

class ASCII85EncoderTest_216 : public ::testing::Test {
 protected:
  // Creates a MemStream whose backing storage stays alive for the duration
  // of the test (MemStream typically does not copy the buffer).
  std::unique_ptr<Stream> MakeMemStream(const std::string& bytes) {
    backing_.assign(bytes.begin(), bytes.end());
    // MemStream in poppler/xpdf-style APIs expects a mutable char*.
    // start=0, length=bytes.size()
    dict_.initNull();
    return std::unique_ptr<Stream>(
        new MemStream(backing_.data(), /*startA=*/0u,
                      /*lengthA=*/static_cast<Guint>(backing_.size()),
                      /*dictA=*/&dict_));
  }

  // Helper to create encoder + rewind it into a known state.
  std::unique_ptr<ASCII85Encoder> MakeEncoderAndRewind(const std::string& bytes) {
    input_ = MakeMemStream(bytes);
    auto enc = std::unique_ptr<ASCII85Encoder>(new ASCII85Encoder(input_.get()));
    // Interface in prompt: rewind()
    EXPECT_TRUE(enc->rewind());
    return enc;
  }

  // Reads the remaining encoded output until EOF.
  static std::string ReadAll(Stream& s) {
    std::string out;
    for (;;) {
      const int c = s.getChar();
      if (c == EOF) break;
      out.push_back(static_cast<char>(c));
      // Safety: prevent runaway if something is wrong.
      if (out.size() > 1'000'000) break;
    }
    return out;
  }

  static bool IsReasonableEncodedByte(int c) {
    if (c == EOF) return true;
    // ASCII85 encoder output is generally printable ASCII + newlines.
    return c == '\n' || (c >= 0x20 && c <= 0x7e);
  }

  std::vector<char> backing_;
  Object dict_;
  std::unique_ptr<Stream> input_;
};

TEST_F(ASCII85EncoderTest_216, LookCharDoesNotConsume_216) {
  auto enc = MakeEncoderAndRewind("Hello");

  const int a = enc->lookChar();
  const int b = enc->lookChar();
  EXPECT_EQ(a, b);

  const int g = enc->getChar();
  EXPECT_EQ(a, g);

  const int nextPeek = enc->lookChar();
  const int nextGet = enc->getChar();
  EXPECT_EQ(nextPeek, nextGet);

  EXPECT_TRUE(IsReasonableEncodedByte(a));
  EXPECT_TRUE(IsReasonableEncodedByte(nextPeek));
}

TEST_F(ASCII85EncoderTest_216, LookCharReturnsEOFAtEndAndStaysEOF_216) {
  auto enc = MakeEncoderAndRewind("A");

  // Drain everything.
  (void)ReadAll(*enc);

  EXPECT_EQ(EOF, enc->lookChar());
  EXPECT_EQ(EOF, enc->lookChar());
  EXPECT_EQ(EOF, enc->getChar());
  EXPECT_EQ(EOF, enc->lookChar());
}

TEST_F(ASCII85EncoderTest_216, RewindRestartsOutput_216) {
  auto enc = MakeEncoderAndRewind("Hello");

  const int first = enc->lookChar();
  ASSERT_NE(EOF, first);

  // Consume a bit.
  (void)enc->getChar();
  (void)enc->getChar();

  // Rewind and ensure the first output byte matches again.
  EXPECT_TRUE(enc->rewind());
  const int firstAfter = enc->lookChar();
  EXPECT_EQ(first, firstAfter);
}

TEST_F(ASCII85EncoderTest_216, EmptyInputProducesFiniteOutputAndEOF_216) {
  auto enc = MakeEncoderAndRewind("");

  std::string out = ReadAll(*enc);
  // Don’t assume exact encoding markers; just ensure it terminates and is reasonable.
  EXPECT_LT(out.size(), 1024u);
  for (unsigned char ch : out) {
    EXPECT_TRUE(IsReasonableEncodedByte(static_cast<int>(ch)));
  }

  EXPECT_EQ(EOF, enc->lookChar());
  EXPECT_EQ(EOF, enc->getChar());
}

TEST_F(ASCII85EncoderTest_216, ReportsEncoderAndKindIsStable_216) {
  auto enc = MakeEncoderAndRewind("Hi");

  EXPECT_TRUE(enc->isEncoder());

  // getKind should be callable and stable across calls.
  const StreamKind k1 = enc->getKind();
  const StreamKind k2 = enc->getKind();
  EXPECT_EQ(k1, k2);

  // getPSFilter should be callable; value may be empty depending on build/options.
  auto ps = enc->getPSFilter(/*psLevel=*/0, /*indent=*/"");
  (void)ps;

  // isBinary should be callable and stable for the same argument.
  const bool b1 = enc->isBinary(true);
  const bool b2 = enc->isBinary(true);
  EXPECT_EQ(b1, b2);
}

}  // namespace