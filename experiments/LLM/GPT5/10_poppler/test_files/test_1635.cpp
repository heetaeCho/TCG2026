// Decrypt_sha256_test_1635.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// Include the implementation file to access the TU-local static function.
// This does not re-implement logic; it allows black-box verification via observable outputs.
#include "./TestProjects/poppler/poppler/Decrypt.cc"

namespace {

using Digest32 = std::array<uint8_t, 32>;

static Digest32 Sha256Of(const void *data, int len)
{
  Digest32 out{};
  sha256(reinterpret_cast<unsigned char *>(const_cast<void *>(data)), len,
         reinterpret_cast<unsigned char *>(out.data()));
  return out;
}

static Digest32 Sha256OfString(const std::string &s)
{
  return Sha256Of(s.data(), static_cast<int>(s.size()));
}

static std::string ToHex(const Digest32 &d)
{
  static const char kHex[] = "0123456789abcdef";
  std::string s;
  s.reserve(64);
  for (uint8_t b : d) {
    s.push_back(kHex[(b >> 4) & 0xF]);
    s.push_back(kHex[b & 0xF]);
  }
  return s;
}

static Digest32 FromHex64(const char *hex64)
{
  auto nibble = [](char c) -> uint8_t {
    if (c >= '0' && c <= '9') return static_cast<uint8_t>(c - '0');
    if (c >= 'a' && c <= 'f') return static_cast<uint8_t>(c - 'a' + 10);
    if (c >= 'A' && c <= 'F') return static_cast<uint8_t>(c - 'A' + 10);
    return 0;
  };
  Digest32 d{};
  for (int i = 0; i < 32; ++i) {
    d[i] = static_cast<uint8_t>((nibble(hex64[i * 2]) << 4) | nibble(hex64[i * 2 + 1]));
  }
  return d;
}

class Sha256Test_1635 : public ::testing::Test
{
};

} // namespace

TEST_F(Sha256Test_1635, EmptyString_KnownVector_1635)
{
  // SHA-256("") =
  // e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
  const auto got = Sha256Of(nullptr, 0);
  const auto expected = FromHex64("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
  EXPECT_EQ(got, expected);
}

TEST_F(Sha256Test_1635, ABC_KnownVector_1635)
{
  // SHA-256("abc") =
  // ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
  const auto got = Sha256OfString("abc");
  const auto expected = FromHex64("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
  EXPECT_EQ(got, expected);
}

TEST_F(Sha256Test_1635, QuickBrownFox_KnownVector_1635)
{
  // SHA-256("The quick brown fox jumps over the lazy dog") =
  // d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592
  const auto got = Sha256OfString("The quick brown fox jumps over the lazy dog");
  const auto expected = FromHex64("d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592");
  EXPECT_EQ(got, expected);
}

TEST_F(Sha256Test_1635, OneByteBoundary_DeterministicAndKnown_1635)
{
  // SHA-256("a") =
  // ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb
  const auto got = Sha256OfString("a");
  const auto expected = FromHex64("ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb");
  EXPECT_EQ(got, expected);
}

TEST_F(Sha256Test_1635, PaddingBoundary_55Bytes_1635)
{
  // 55 bytes is the last length that fits padding+length in a single final block.
  std::string msg(55, 'a');
  const auto got1 = Sha256OfString(msg);
  const auto got2 = Sha256OfString(msg);
  EXPECT_EQ(got1, got2);
  EXPECT_EQ(ToHex(got1).size(), 64u);
}

TEST_F(Sha256Test_1635, PaddingBoundary_56Bytes_UsesExtraBlock_Deterministic_1635)
{
  // 56 bytes triggers the "blkLen > 56" path (extra block). We validate determinism & output shape.
  std::string msg(56, 'a');
  const auto got1 = Sha256OfString(msg);
  const auto got2 = Sha256OfString(msg);
  EXPECT_EQ(got1, got2);
  EXPECT_EQ(ToHex(got1).size(), 64u);
  // Sanity: different input length should yield different digest (observable property).
  EXPECT_NE(got1, Sha256OfString(std::string(55, 'a')));
}

TEST_F(Sha256Test_1635, MultiBlockBoundary_64And65Bytes_Deterministic_1635)
{
  std::string msg64(64, 'b'); // exactly one full block
  std::string msg65(65, 'b'); // one full block + 1 byte

  const auto d64 = Sha256OfString(msg64);
  const auto d65 = Sha256OfString(msg65);

  EXPECT_EQ(d64, Sha256OfString(msg64));
  EXPECT_EQ(d65, Sha256OfString(msg65));
  EXPECT_NE(d64, d65);
  EXPECT_EQ(ToHex(d64).size(), 64u);
  EXPECT_EQ(ToHex(d65).size(), 64u);
}

TEST_F(Sha256Test_1635, WritesExactly32BytesIntoHashBuffer_1635)
{
  // Observable effect: function writes the digest to the provided buffer.
  // We surround the buffer with sentinels and ensure only the digest region changes.
  std::array<uint8_t, 32 + 8> buf{};
  for (size_t i = 0; i < buf.size(); ++i) buf[i] = 0xA5;

  unsigned char *hash = reinterpret_cast<unsigned char *>(buf.data() + 4); // 4-byte prefix sentinel
  const std::string msg = "abc";
  sha256(reinterpret_cast<unsigned char *>(const_cast<char *>(msg.data())),
         static_cast<int>(msg.size()), hash);

  // Prefix sentinel intact
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(buf[i], 0xA5) << "prefix sentinel modified at " << i;
  }
  // Suffix sentinel intact
  for (int i = 36; i < 40; ++i) {
    EXPECT_EQ(buf[i], 0xA5) << "suffix sentinel modified at " << i;
  }

  // Digest matches expected for "abc"
  Digest32 got{};
  std::memcpy(got.data(), buf.data() + 4, 32);
  const auto expected = FromHex64("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
  EXPECT_EQ(got, expected);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(Sha256Test_1635, NullMsgWithPositiveLength_Death_1635)
{
  // If the implementation dereferences msg when msgLen > 0, this is an observable error case.
  // (Death tests are isolated; they do not assume specific internal logic beyond a crash on invalid input.)
  std::array<uint8_t, 32> out{};
  ASSERT_DEATH(
      sha256(nullptr, 1, reinterpret_cast<unsigned char *>(out.data())),
      "");
}
#endif