// getFileName_test_2719.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <vector>

// Rename main() if pdfdetach.cc defines it (common for Poppler utils).
#define main pdfdetach_main_unused_2719
// Include the implementation file so we can test the TU-local static getFileName().
#include "./TestProjects/poppler/utils/pdfdetach.cc"
#undef main

namespace {

// --- Recording helpers for verifying external interactions (mapUnicode calls) ---
static std::vector<uint32_t> g_seen_unicodes;
static std::vector<int> g_seen_buf_sizes;

// NOTE: In Poppler, Unicode is typically a 32-bit integral type.
// We record as uint32_t to avoid depending on exact typedef.
static int RecordingUnicodeMapFunc(Unicode u, char *buf, int bufSize)
{
    g_seen_unicodes.push_back(static_cast<uint32_t>(u));
    g_seen_buf_sizes.push_back(bufSize);

    // Deterministic output: emit the low 8 bits as a single byte.
    if (bufSize <= 0) {
        return 0;
    }
    buf[0] = static_cast<char>(static_cast<uint32_t>(u) & 0xFFu);
    return 1;
}

static int ZeroLenUnicodeMapFunc(Unicode u, char * /*buf*/, int bufSize)
{
    g_seen_unicodes.push_back(static_cast<uint32_t>(u));
    g_seen_buf_sizes.push_back(bufSize);
    (void)bufSize;
    return 0; // simulate "no output produced" for every character
}

static void ResetRecorder()
{
    g_seen_unicodes.clear();
    g_seen_buf_sizes.clear();
}

class GetFileNameTest_2719 : public ::testing::Test {
protected:
    void SetUp() override { ResetRecorder(); }
    void TearDown() override { ResetRecorder(); }
};

TEST_F(GetFileNameTest_2719, EmptyStringReturnsEmpty_2719)
{
    // Arrange
    const GooString s("", 0);

    // Use a UnicodeMap backed by our recording function.
    UnicodeMap uMap("recording", /*unicodeOutA=*/false, RecordingUnicodeMapFunc);

    // Act
    const std::string out = getFileName(s, uMap);

    // Assert
    EXPECT_TRUE(out.empty());
    EXPECT_TRUE(g_seen_unicodes.empty());
    EXPECT_TRUE(g_seen_buf_sizes.empty());
}

TEST_F(GetFileNameTest_2719, UnicodeBOMOnlyProducesEmptyAndNoMapCalls_2719)
{
    // Arrange: BOM (FE FF) and nothing else; length is even so it should be treated as Unicode.
    const char bytes[] = { static_cast<char>(0xFE), static_cast<char>(0xFF) };
    const GooString s(bytes, sizeof(bytes));

    UnicodeMap uMap("recording", /*unicodeOutA=*/false, RecordingUnicodeMapFunc);

    // Act
    const std::string out = getFileName(s, uMap);

    // Assert
    EXPECT_TRUE(out.empty());
    EXPECT_TRUE(g_seen_unicodes.empty());
    EXPECT_TRUE(g_seen_buf_sizes.empty());
}

TEST_F(GetFileNameTest_2719, NonUnicodeAsciiUsesPdfDocEncodingPathAndMapsEachByte_2719)
{
    // Arrange: no BOM -> non-unicode path.
    const char bytes[] = { 'A', 'B', 'C' };
    const GooString s(bytes, sizeof(bytes));

    UnicodeMap uMap("recording", /*unicodeOutA=*/false, RecordingUnicodeMapFunc);

    // Act
    const std::string out = getFileName(s, uMap);

    // Assert (observable behavior): output bytes are low 8 bits of the Unicode values passed to mapUnicode.
    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(out[0], 'A');
    EXPECT_EQ(out[1], 'B');
    EXPECT_EQ(out[2], 'C');

    // External interaction: mapUnicode called once per input byte.
    ASSERT_EQ(g_seen_unicodes.size(), 3u);
    ASSERT_EQ(g_seen_buf_sizes.size(), 3u);
    EXPECT_EQ(g_seen_buf_sizes[0], 8);
    EXPECT_EQ(g_seen_buf_sizes[1], 8);
    EXPECT_EQ(g_seen_buf_sizes[2], 8);

    // We avoid asserting exact pdfDocEncoding mapping for all bytes; for ASCII we can at least
    // verify the low byte matches the character (a minimal observable check).
    EXPECT_EQ(static_cast<char>(g_seen_unicodes[0] & 0xFFu), 'A');
    EXPECT_EQ(static_cast<char>(g_seen_unicodes[1] & 0xFFu), 'B');
    EXPECT_EQ(static_cast<char>(g_seen_unicodes[2] & 0xFFu), 'C');
}

TEST_F(GetFileNameTest_2719, UnicodeBigEndianBOMDecodesPairsAndSkipsBOM_2719)
{
    // Arrange: BOM (FE FF), then U+0041 ('A'), U+0042 ('B') in big-endian.
    const char bytes[] = {
        static_cast<char>(0xFE), static_cast<char>(0xFF),
        static_cast<char>(0x00), static_cast<char>(0x41),
        static_cast<char>(0x00), static_cast<char>(0x42),
    };
    const GooString s(bytes, sizeof(bytes));

    UnicodeMap uMap("recording", /*unicodeOutA=*/false, RecordingUnicodeMapFunc);

    // Act
    const std::string out = getFileName(s, uMap);

    // Assert
    ASSERT_EQ(out.size(), 2u);
    EXPECT_EQ(out[0], 'A');
    EXPECT_EQ(out[1], 'B');

    // External interaction: mapUnicode called once per Unicode code unit (2 bytes), excluding BOM.
    ASSERT_EQ(g_seen_unicodes.size(), 2u);
    ASSERT_EQ(g_seen_buf_sizes.size(), 2u);
    EXPECT_EQ(g_seen_buf_sizes[0], 8);
    EXPECT_EQ(g_seen_buf_sizes[1], 8);

    // Verify Unicode values observed (this is determined by the interface-visible construction in getFileName).
    EXPECT_EQ(g_seen_unicodes[0], 0x0041u);
    EXPECT_EQ(g_seen_unicodes[1], 0x0042u);
}

TEST_F(GetFileNameTest_2719, BOMWithOddLengthIsNotTreatedAsUnicodeAndMapsAllBytes_2719)
{
    // Arrange: Starts with BOM-like bytes but total length is odd, so Unicode BOM path should not be taken.
    const char bytes[] = { static_cast<char>(0xFE), static_cast<char>(0xFF), 'A' };
    const GooString s(bytes, sizeof(bytes));

    UnicodeMap uMap("recording", /*unicodeOutA=*/false, RecordingUnicodeMapFunc);

    // Act
    const std::string out = getFileName(s, uMap);

    // Assert (boundary condition): regardless of encoding, the function must iterate over all bytes
    // (since it won't consume 2-byte units starting at offset 2).
    ASSERT_EQ(g_seen_unicodes.size(), 3u);
    ASSERT_EQ(g_seen_buf_sizes.size(), 3u);
    EXPECT_EQ(g_seen_buf_sizes[0], 8);
    EXPECT_EQ(g_seen_buf_sizes[1], 8);
    EXPECT_EQ(g_seen_buf_sizes[2], 8);

    // Minimal observable check: last input byte is 'A', so output's last byte should be 'A'
    // given our mapping function emits low 8 bits.
    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(out.back(), 'A');
}

TEST_F(GetFileNameTest_2719, MapUnicodeReturningZeroProducesEmptyOutputButStillCallsMapper_2719)
{
    // Arrange
    const char bytes[] = { 'Z' };
    const GooString s(bytes, sizeof(bytes));

    UnicodeMap uMap("zero", /*unicodeOutA=*/false, ZeroLenUnicodeMapFunc);

    // Act
    const std::string out = getFileName(s, uMap);

    // Assert: output empty because mapUnicode returns 0 bytes appended.
    EXPECT_TRUE(out.empty());

    // External interaction still occurs once.
    ASSERT_EQ(g_seen_unicodes.size(), 1u);
    ASSERT_EQ(g_seen_buf_sizes.size(), 1u);
    EXPECT_EQ(g_seen_buf_sizes[0], 8);
}

} // namespace