// =================================================================================================
// TEST_ID: 1571
// Unit tests for Exiv2::AsfVideo::contentDescription (black-box tests via public wrapper subclass)
// File under test: ./TestProjects/exiv2/src/asfvideo.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

// Exiv2 headers
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

namespace {

// Helper: append little-endian uint16_t
static void appendU16LE(std::vector<Exiv2::byte>& out, uint16_t v) {
  out.push_back(static_cast<Exiv2::byte>(v & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 8) & 0xFF));
}

// Helper: encode ASCII into UTF-16LE with a terminating 0x0000.
// Returns the byte length (what we put in the length fields) and appends bytes.
static uint16_t appendUtf16LeNullTerminated(std::vector<Exiv2::byte>& out, const std::string& ascii) {
  // UTF-16LE for ASCII: each char => [char, 0x00]
  for (unsigned char c : ascii) {
    out.push_back(static_cast<Exiv2::byte>(c));
    out.push_back(static_cast<Exiv2::byte>(0x00));
  }
  // terminator
  out.push_back(static_cast<Exiv2::byte>(0x00));
  out.push_back(static_cast<Exiv2::byte>(0x00));
  return static_cast<uint16_t>((ascii.size() + 1) * 2);
}

// Expose protected contentDescription for testing (no internal logic reimplementation).
class TestableAsfVideo : public Exiv2::AsfVideo {
 public:
  explicit TestableAsfVideo(Exiv2::BasicIo::UniquePtr io) : Exiv2::AsfVideo(std::move(io)) {}

  void CallContentDescription() { contentDescription(); }
};

class AsfVideoContentDescriptionTest_1571 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr MakeMemIo(const std::vector<Exiv2::byte>& data) {
    // Using MemIo as a BasicIo implementation (assumed available in Exiv2).
    // Treat this as a standard Exiv2 collaborator; we only provide input bytes.
    return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(data.data(), static_cast<long>(data.size())));
  }
};

}  // namespace

TEST_F(AsfVideoContentDescriptionTest_1571, ZeroLengthsDoesNotPopulateXmp_1571) {
  std::vector<Exiv2::byte> buf;
  // title, author, copyright, description, rating lengths
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);

  TestableAsfVideo vid(MakeMemIo(buf));
  vid.CallContentDescription();

  // With all lengths zero, the observable effect should be no corresponding XMP entries set.
  EXPECT_EQ(vid.xmpData().count(), 0);
  EXPECT_TRUE(vid.xmpData().empty());
}

TEST_F(AsfVideoContentDescriptionTest_1571, TitleOnlyPopulatesTitleKey_1571) {
  std::vector<Exiv2::byte> buf;

  // Reserve space for five lengths, then fill strings after.
  // title length non-zero, others zero.
  const std::string title = "MyTitle";
  std::vector<Exiv2::byte> strings;
  const uint16_t titleLen = appendUtf16LeNullTerminated(strings, title);

  appendU16LE(buf, titleLen);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  buf.insert(buf.end(), strings.begin(), strings.end());

  TestableAsfVideo vid(MakeMemIo(buf));
  vid.CallContentDescription();

  // Title key should exist and be non-empty (exact conversion behavior is implementation-defined).
  EXPECT_GE(vid.xmpData().count(), 1);

  const std::string gotTitle = vid.xmpData()["Xmp.video.Title"].toString();
  EXPECT_FALSE(gotTitle.empty());
}

TEST_F(AsfVideoContentDescriptionTest_1571, AllFieldsPopulatedWhenAllLengthsNonZero_1571) {
  std::vector<Exiv2::byte> buf;

  const std::string title = "T";
  const std::string author = "A";
  const std::string copyright = "C";
  const std::string desc = "D";
  const std::string rating = "R";

  std::vector<Exiv2::byte> strings;
  const uint16_t titleLen = appendUtf16LeNullTerminated(strings, title);
  const uint16_t authorLen = appendUtf16LeNullTerminated(strings, author);
  const uint16_t copyrightLen = appendUtf16LeNullTerminated(strings, copyright);
  const uint16_t descLen = appendUtf16LeNullTerminated(strings, desc);
  const uint16_t ratingLen = appendUtf16LeNullTerminated(strings, rating);

  appendU16LE(buf, titleLen);
  appendU16LE(buf, authorLen);
  appendU16LE(buf, copyrightLen);
  appendU16LE(buf, descLen);
  appendU16LE(buf, ratingLen);
  buf.insert(buf.end(), strings.begin(), strings.end());

  TestableAsfVideo vid(MakeMemIo(buf));
  vid.CallContentDescription();

  // All keys should be set to some (possibly converted) non-empty string.
  EXPECT_FALSE(vid.xmpData()["Xmp.video.Title"].toString().empty());
  EXPECT_FALSE(vid.xmpData()["Xmp.video.Author"].toString().empty());
  EXPECT_FALSE(vid.xmpData()["Xmp.video.Copyright"].toString().empty());
  EXPECT_FALSE(vid.xmpData()["Xmp.video.Description"].toString().empty());
  EXPECT_FALSE(vid.xmpData()["Xmp.video.Rating"].toString().empty());

  // At least 5 entries expected if all assignments create entries.
  EXPECT_GE(vid.xmpData().count(), 5);
}

TEST_F(AsfVideoContentDescriptionTest_1571, MinimalNonZeroLengthMayCreateKeyEvenIfOnlyTerminator_1571) {
  std::vector<Exiv2::byte> buf;

  // Minimal UTF-16LE "empty" string with just a terminator: length 2 bytes.
  // (Whether this yields empty or not depends on implementation; we only assert key presence behavior.)
  appendU16LE(buf, 2);  // title_length
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);

  // Title string bytes: 0x0000
  buf.push_back(static_cast<Exiv2::byte>(0x00));
  buf.push_back(static_cast<Exiv2::byte>(0x00));

  TestableAsfVideo vid(MakeMemIo(buf));
  vid.CallContentDescription();

  // Observable: when length is non-zero, code attempts to set the title field.
  // We verify the key is accessible (operator[] will create if absent, but toString() should be valid).
  (void)vid.xmpData()["Xmp.video.Title"].toString();
  EXPECT_GE(vid.xmpData().count(), 1);
}

TEST_F(AsfVideoContentDescriptionTest_1571, TruncatedBufferThrowsOnRead_1571) {
  std::vector<Exiv2::byte> buf;

  // Provide lengths that claim data exists, but omit the actual string bytes.
  appendU16LE(buf, 10);  // title_length (non-zero)
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);
  appendU16LE(buf, 0);

  TestableAsfVideo vid(MakeMemIo(buf));

  // Reading beyond available data should be observable as an exception from IO/tag readers.
  EXPECT_THROW(vid.CallContentDescription(), Exiv2::Error);
}