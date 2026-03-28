// TEST_ID: 238
// Unit tests for RGBGrayEncoder::lookChar (black-box)
//
// File: ./TestProjects/poppler/poppler/Stream.h

#include <gtest/gtest.h>

#include <climits>
#include <cstring>
#include <memory>
#include <vector>

#include "poppler/Stream.h"

namespace {

class RGBGrayEncoderTest_238 : public ::testing::Test {
protected:
  // Helper to build a MemStream-backed Stream*.
  // NOTE: We intentionally do not assume anything about RGBGrayEncoder's internal
  // transformation logic; we only validate observable "peek" behavior of lookChar().
  static std::unique_ptr<Stream> MakeMemStream(const std::vector<unsigned char>& bytes) {
    // Poppler's MemStream historically takes a mutable char* buffer; allocate our own copy.
    char* buf = static_cast<char*>(gmalloc(bytes.size() > 0 ? bytes.size() : 1));
    if (!bytes.empty()) {
      std::memcpy(buf, bytes.data(), bytes.size());
    }

    Object dict;
    dict.initNull();

    // MemStream takes ownership only if configured; to avoid guessing, we simply leak-proof the
    // buffer by always allocating with gmalloc and allowing MemStream to decide. The MemStream
    // destructor typically frees only if it "owns" the buffer; if it doesn't, we still need to
    // free it. To keep the test robust without relying on internals, we wrap the Stream in a
    // custom deleter that frees the buffer after deleting the stream.
    //
    // However, we cannot safely access MemStream internals to check ownership. So we use a
    // small adapter: create a substream that points to the same buffer and then free the buffer
    // after deleting both in the correct order would still be relying on internals.
    //
    // Practical approach used in many Poppler unit tests: allocate buffer and let MemStream
    // manage it (needFree is typically false for external buffers). We therefore free the buffer
    // ourselves after deleting the stream by keeping it in a shared_ptr captured by deleter.
    struct Holder {
      char* p;
      explicit Holder(char* p_) : p(p_) {}
      ~Holder() { gfree(p); }
    };
    auto holder = std::make_shared<Holder>(buf);

    Stream* raw = new MemStream(buf, /*startA=*/0, /*lengthA=*/static_cast<Guint>(bytes.size()), &dict);

    // Ensure dict is not freed before MemStream copies/uses it (BaseStream copies Object).
    // dict will free on scope exit; that's fine.

    return std::unique_ptr<Stream>(raw, [holder](Stream* s) {
      delete s;
      // holder frees buf
    });
  }
};

TEST_F(RGBGrayEncoderTest_238, LookCharReturnsEOFOnEmptyInput_238) {
  auto base = MakeMemStream({});
  RGBGrayEncoder enc(base.get());

  // If rewind is meaningful/required, it should be safe and report success/failure.
  // We don't assert on the boolean unless it is observable/consistent across builds.
  (void)enc.rewind();

  EXPECT_EQ(enc.lookChar(), EOF);
  // Repeated peek at EOF should remain EOF.
  EXPECT_EQ(enc.lookChar(), EOF);
}

TEST_F(RGBGrayEncoderTest_238, LookCharDoesNotConsumeAndMatchesNextGetChar_238) {
  std::vector<unsigned char> bytes = {0x00, 0x7f, 0x80, 0xff};
  auto base = MakeMemStream(bytes);
  RGBGrayEncoder enc(base.get());
  (void)enc.rewind();

  // Peek twice: should be stable (no consumption).
  const int p0 = enc.lookChar();
  const int p0_again = enc.lookChar();
  EXPECT_EQ(p0, p0_again);

  // getChar should yield the same value as the peeked value.
  const int c0 = enc.getChar();
  EXPECT_EQ(p0, c0);

  // Peek next and consume next.
  const int p1 = enc.lookChar();
  const int c1 = enc.getChar();
  EXPECT_EQ(p1, c1);
}

TEST_F(RGBGrayEncoderTest_238, LookCharBehavesAcrossManyReadsAndAtEnd_238) {
  // Use a payload large enough to plausibly cross internal buffer boundaries without assuming
  // the actual buffer size.
  std::vector<unsigned char> bytes;
  bytes.reserve(5000);
  for (int i = 0; i < 5000; ++i) {
    bytes.push_back(static_cast<unsigned char>(i & 0xff));
  }

  auto base = MakeMemStream(bytes);
  RGBGrayEncoder enc(base.get());
  (void)enc.rewind();

  // Sample peek/consume agreement at various positions.
  const int sample_positions[] = {0, 1, 2, 100, 1023, 1024, 1500, 2047, 2048, 4095, 4999};

  int next_pos_to_check = 0;

  for (int i = 0; i < static_cast<int>(bytes.size()); ++i) {
    if (next_pos_to_check < static_cast<int>(sizeof(sample_positions) / sizeof(sample_positions[0])) &&
        i == sample_positions[next_pos_to_check]) {
      const int peeked = enc.lookChar();
      const int consumed = enc.getChar();
      EXPECT_EQ(peeked, consumed) << "Mismatch at position " << i;
      ++next_pos_to_check;
    } else {
      // Consume without asserting on exact value (encoder may transform).
      (void)enc.getChar();
    }
  }

  // After consuming all bytes, lookChar should report EOF and remain EOF.
  EXPECT_EQ(enc.lookChar(), EOF);
  EXPECT_EQ(enc.lookChar(), EOF);
}

TEST_F(RGBGrayEncoderTest_238, LookCharAfterFullConsumptionStaysEOF_238) {
  std::vector<unsigned char> bytes = {0x12};
  auto base = MakeMemStream(bytes);
  RGBGrayEncoder enc(base.get());
  (void)enc.rewind();

  // Consume the only byte.
  (void)enc.getChar();

  EXPECT_EQ(enc.lookChar(), EOF);
  EXPECT_EQ(enc.lookChar(), EOF);

  // getChar at end should also be EOF (observable error case).
  EXPECT_EQ(enc.getChar(), EOF);
}

}  // namespace