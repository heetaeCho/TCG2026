// RGBGrayEncoder_getChar_237_test.cc
#include <gtest/gtest.h>

#include <poppler/Object.h>
#include <poppler/Stream.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace {

// Reads until EOF or until maxBytes is reached (safety guard against infinite output).
static std::vector<int> ReadAllBytes(Stream &s, size_t maxBytes)
{
    std::vector<int> out;
    out.reserve(256);

    for (size_t i = 0; i < maxBytes; ++i) {
        const int c = s.getChar();
        if (c == EOF) {
            break;
        }
        out.push_back(c);
    }
    return out;
}

// Creates an RGBGrayEncoder with a MemStream backing store.
// NOTE: We allocate the MemStream on the heap and do not manually delete it,
// to avoid double-free risk if FilterStream/RGBGrayEncoder takes ownership.
static std::unique_ptr<RGBGrayEncoder> MakeEncoderFromBytes(const std::vector<unsigned char> &bytes)
{
    const char *buf = reinterpret_cast<const char *>(bytes.data());
    const Goffset start = 0;
    const Goffset length = static_cast<Goffset>(bytes.size());

    // Empty dict is fine for MemStream construction.
    Object dict;

    auto *mem = new MemStream(buf, start, length, std::move(dict));
    return std::make_unique<RGBGrayEncoder>(mem);
}

class RGBGrayEncoderTest_237 : public ::testing::Test
{
};

} // namespace

TEST_F(RGBGrayEncoderTest_237, EmptyInput_ReturnsEOF_237)
{
    const std::vector<unsigned char> in; // empty
    auto enc = MakeEncoderFromBytes(in);

    enc->reset();
    EXPECT_EQ(enc->lookChar(), EOF);
    EXPECT_EQ(enc->getChar(), EOF);
    EXPECT_EQ(enc->lookChar(), EOF);
}

TEST_F(RGBGrayEncoderTest_237, LookChar_DoesNotConsumeNextByte_237)
{
    const std::vector<unsigned char> in = { 0x00, 0x7F, 0xFF, 0x10, 0x20 };
    auto enc = MakeEncoderFromBytes(in);

    enc->reset();

    const int a = enc->lookChar();
    ASSERT_NE(a, EOF);

    // Repeated lookChar should keep returning the same next byte until getChar consumes it.
    EXPECT_EQ(enc->lookChar(), a);
    EXPECT_EQ(enc->lookChar(), a);

    const int b = enc->getChar();
    EXPECT_EQ(b, a);

    const int c = enc->lookChar();
    // If not EOF, it should now be the next byte (not necessarily equal to a).
    if (c != EOF) {
        EXPECT_NE(c, a);
    }
}

TEST_F(RGBGrayEncoderTest_237, GetChar_AlwaysReturnsByteOrEOF_237)
{
    // Include a non-multiple-of-3 length to exercise boundary behavior.
    const std::vector<unsigned char> in = {
        0x00, 0x01, 0x02, // 3
        0x10, 0x20,       // +2 (boundary)
    };
    auto enc = MakeEncoderFromBytes(in);

    enc->reset();

    // Read a bounded number of bytes; verify each is within unsigned-byte range.
    for (int i = 0; i < 256; ++i) {
        const int c = enc->getChar();
        if (c == EOF) {
            SUCCEED();
            return;
        }
        EXPECT_GE(c, 0);
        EXPECT_LE(c, 255);
    }

    // If we get here, the stream did not end within a reasonable bound for tiny input.
    FAIL() << "RGBGrayEncoder did not reach EOF within expected bounds.";
}

TEST_F(RGBGrayEncoderTest_237, Reset_ReplaysSameOutputSequence_237)
{
    const std::vector<unsigned char> in = {
        0x11, 0x22, 0x33,
        0x44, 0x55, 0x66,
        0x77, 0x88, 0x99,
        0xAA, 0xBB, 0xCC,
        0xDD // boundary tail
    };
    auto enc = MakeEncoderFromBytes(in);

    enc->reset();
    const auto first = ReadAllBytes(*enc, /*maxBytes=*/4096);

    // After EOF, further reads should stay at EOF.
    EXPECT_EQ(enc->getChar(), EOF);
    EXPECT_EQ(enc->lookChar(), EOF);

    enc->reset();
    const auto second = ReadAllBytes(*enc, /*maxBytes=*/4096);

    EXPECT_EQ(first, second);
}

TEST_F(RGBGrayEncoderTest_237, EventuallyReachesEOF_ForSmallInputs_237)
{
    // A few small inputs, including sizes around typical RGB component boundaries.
    const std::vector<std::vector<unsigned char>> cases = {
        { 0x01 },                   // 1 byte
        { 0x01, 0x02 },             // 2 bytes
        { 0x01, 0x02, 0x03 },       // 3 bytes
        { 0x01, 0x02, 0x03, 0x04 }, // 4 bytes
        { 0xFF, 0x00, 0xAA, 0x55, 0x10, 0x20, 0x30 }, // 7 bytes
    };

    for (const auto &in : cases) {
        auto enc = MakeEncoderFromBytes(in);
        enc->reset();

        // Safety bound: output should not be unbounded for finite input.
        const auto out = ReadAllBytes(*enc, /*maxBytes=*/8192);

        // Must reach EOF within the bound (otherwise ReadAllBytes would stop at maxBytes).
        ASSERT_LT(out.size(), static_cast<size_t>(8192))
            << "Did not reach EOF within bound for input size " << in.size();

        // Also check post-EOF behavior is stable.
        EXPECT_EQ(enc->getChar(), EOF);
        EXPECT_EQ(enc->lookChar(), EOF);
    }
}