// ASCII85Encoder_tests_215.cpp
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Poppler
#include "poppler/Stream.h"

namespace {

template <typename T, typename = void>
struct has_initNull : std::false_type {};
template <typename T>
struct has_initNull<T, std::void_t<decltype(std::declval<T &>().initNull())>> : std::true_type {};

template <typename T, typename = void>
struct has_rewind : std::false_type {};
template <typename T>
struct has_rewind<T, std::void_t<decltype(std::declval<T &>().rewind())>> : std::true_type {};

template <typename T, typename = void>
struct has_reset : std::false_type {};
template <typename T>
struct has_reset<T, std::void_t<decltype(std::declval<T &>().reset())>> : std::true_type {};

template <typename T, typename = void>
struct has_close : std::false_type {};
template <typename T>
struct has_close<T, std::void_t<decltype(std::declval<T &>().close())>> : std::true_type {};

template <typename T, typename = void>
struct has_getPSFilter_string : std::false_type {};
template <typename T>
struct has_getPSFilter_string<
    T, std::void_t<decltype(std::declval<T &>().getPSFilter(2, static_cast<const char *>(nullptr)))>>
    : std::true_type {};

static Object MakeNullObject()
{
    Object obj;
    if constexpr (has_initNull<Object>::value) {
        obj.initNull();
    }
    return obj;
}

template <typename StreamT>
static void RewindOrReset(StreamT &s)
{
    if constexpr (has_rewind<StreamT>::value) {
        (void)s.rewind();
    } else if constexpr (has_reset<StreamT>::value) {
        s.reset();
    }
}

template <typename StreamT>
static void CloseIfPossible(StreamT &s)
{
    if constexpr (has_close<StreamT>::value) {
        s.close();
    }
}

// Create a MemStream across multiple Poppler/Xpdf API variants.
// (We keep input bytes alive by storing them in a shared vector.)
struct MemStreamHolder {
    std::shared_ptr<std::vector<unsigned char>> bytes;
    std::unique_ptr<Stream> stream;
};

static MemStreamHolder MakeMemStreamFromBytes(const std::vector<unsigned char> &input)
{
    MemStreamHolder h;
    h.bytes = std::make_shared<std::vector<unsigned char>>(input);

    // Try common constructor shapes (varies by Poppler version).
    // We intentionally avoid guessing internal behavior; only adapt to signatures.
    if constexpr (std::is_constructible_v<MemStream, const unsigned char *, size_t, Object>) {
        h.stream = std::make_unique<MemStream>(h.bytes->data(), h.bytes->size(), MakeNullObject());
    } else if constexpr (std::is_constructible_v<MemStream, const unsigned char *, int, Object>) {
        h.stream = std::make_unique<MemStream>(h.bytes->data(),
                                               static_cast<int>(h.bytes->size()),
                                               MakeNullObject());
    } else if constexpr (std::is_constructible_v<MemStream, unsigned char *, int, Object *>) {
        // Older xpdf-style API.
        auto *dict = new Object(MakeNullObject());
        h.stream = std::make_unique<MemStream>(h.bytes->data(),
                                               static_cast<int>(h.bytes->size()),
                                               dict);
        // MemStream/Stream ownership rules vary; tests avoid deleting dict explicitly.
    } else if constexpr (std::is_constructible_v<MemStream, unsigned char *, int, Object>) {
        h.stream = std::make_unique<MemStream>(h.bytes->data(),
                                               static_cast<int>(h.bytes->size()),
                                               MakeNullObject());
    } else if constexpr (std::is_constructible_v<MemStream, const char *, int, Object>) {
        h.stream = std::make_unique<MemStream>(reinterpret_cast<const char *>(h.bytes->data()),
                                               static_cast<int>(h.bytes->size()),
                                               MakeNullObject());
    } else {
        // If Poppler's MemStream signature is different in this codebase, these tests will
        // need to be adjusted to use whatever concrete in-memory Stream is available.
        ADD_FAILURE() << "Unsupported MemStream constructor signature in this Poppler version.";
        h.stream.reset();
    }

    if (h.stream) {
        RewindOrReset(*h.stream);
    }
    return h;
}

static std::string ReadAll(Stream &s)
{
    std::string out;
    for (;;) {
        const int c = s.getChar();
        if (c == EOF) break;
        out.push_back(static_cast<char>(c));
    }
    return out;
}

static std::unique_ptr<ASCII85Encoder> MakeASCII85Encoder(Stream *base)
{
    auto enc = std::make_unique<ASCII85Encoder>(base);
    // Ensure encoder is at start (API differs: rewind/reset).
    RewindOrReset(*enc);
    return enc;
}

} // namespace

// ---------------------------
// TESTS (TEST_ID = 215)
// ---------------------------

class ASCII85EncoderTest_215 : public ::testing::Test {};

TEST_F(ASCII85EncoderTest_215, EmptyInputEmitsTerminatorThenEOF_215)
{
    auto holder = MakeMemStreamFromBytes({});
    ASSERT_NE(holder.stream, nullptr);

    auto enc = MakeASCII85Encoder(holder.stream.release());
    ASSERT_NE(enc, nullptr);

    const std::string out = ReadAll(*enc);

    // Observable behavior: ASCII85Encoder should finish with "~>" for empty input.
    ASSERT_GE(out.size(), 2u);
    EXPECT_EQ(out.substr(out.size() - 2), "~>");

    // Subsequent reads stay at EOF.
    EXPECT_EQ(enc->getChar(), EOF);
    EXPECT_EQ(enc->lookChar(), EOF);

    CloseIfPossible(*enc);
}

TEST_F(ASCII85EncoderTest_215, FourZeroBytesUseZAbbreviationAndTerminator_215)
{
    const std::vector<unsigned char> in = {0x00, 0x00, 0x00, 0x00};
    auto holder = MakeMemStreamFromBytes(in);
    ASSERT_NE(holder.stream, nullptr);

    auto enc = MakeASCII85Encoder(holder.stream.release());
    ASSERT_NE(enc, nullptr);

    const std::string out = ReadAll(*enc);

    // Common, externally-specified ASCII85 behavior: 4 zero bytes => 'z'.
    // And encoder terminates with "~>".
    EXPECT_NE(out.find('z'), std::string::npos);
    ASSERT_GE(out.size(), 2u);
    EXPECT_EQ(out.substr(out.size() - 2), "~>");

    CloseIfPossible(*enc);
}

TEST_F(ASCII85EncoderTest_215, PartialBlockStillTerminates_215)
{
    // Boundary: 1 byte input (partial 4-byte block).
    const std::vector<unsigned char> in = {0x00};
    auto holder = MakeMemStreamFromBytes(in);
    ASSERT_NE(holder.stream, nullptr);

    auto enc = MakeASCII85Encoder(holder.stream.release());
    ASSERT_NE(enc, nullptr);

    const std::string out = ReadAll(*enc);

    // Must always terminate with "~>".
    ASSERT_GE(out.size(), 2u);
    EXPECT_EQ(out.substr(out.size() - 2), "~>");

    // Output should be ASCII (encoder), and not empty beyond terminator.
    EXPECT_GT(out.size(), 2u);
    for (char ch : out) {
        // '\n' may appear for long lines; allow it.
        if (ch == '\n') continue;
        EXPECT_GE(static_cast<unsigned char>(ch), 0x20u);
    }

    CloseIfPossible(*enc);
}

TEST_F(ASCII85EncoderTest_215, LookCharDoesNotConsumeAndMatchesGetChar_215)
{
    const std::vector<unsigned char> in = {0x01, 0x02, 0x03, 0x04};
    auto holder = MakeMemStreamFromBytes(in);
    ASSERT_NE(holder.stream, nullptr);

    auto enc = MakeASCII85Encoder(holder.stream.release());
    ASSERT_NE(enc, nullptr);

    const int a = enc->lookChar();
    ASSERT_NE(a, EOF);

    const int b = enc->lookChar();
    ASSERT_NE(b, EOF);
    EXPECT_EQ(a, b) << "Repeated lookChar() should not consume output.";

    const int c = enc->getChar();
    ASSERT_NE(c, EOF);
    EXPECT_EQ(a, c) << "getChar() should return the same byte previously observed by lookChar().";

    CloseIfPossible(*enc);
}

TEST_F(ASCII85EncoderTest_215, RewindResetsEncodedOutput_215)
{
    const std::vector<unsigned char> in = {0xde, 0xad, 0xbe, 0xef, 0x00};
    auto holder = MakeMemStreamFromBytes(in);
    ASSERT_NE(holder.stream, nullptr);

    auto enc = MakeASCII85Encoder(holder.stream.release());
    ASSERT_NE(enc, nullptr);

    const std::string out1 = ReadAll(*enc);
    ASSERT_FALSE(out1.empty());

    // Reset/rewind and read again; should reproduce identical output.
    RewindOrReset(*enc);
    const std::string out2 = ReadAll(*enc);

    EXPECT_EQ(out1, out2);

    CloseIfPossible(*enc);
}

TEST_F(ASCII85EncoderTest_215, ReportsEncoderAndNonBinaryOutput_215)
{
    const std::vector<unsigned char> in = {0x10, 0x20, 0x30, 0x40};
    auto holder = MakeMemStreamFromBytes(in);
    ASSERT_NE(holder.stream, nullptr);

    auto enc = MakeASCII85Encoder(holder.stream.release());
    ASSERT_NE(enc, nullptr);

    EXPECT_TRUE(enc->isEncoder());

    // For an ASCII encoder, the produced stream is expected to be non-binary.
    // (If this Poppler build defines isBinary differently, this still exercises the API.)
    EXPECT_FALSE(enc->isBinary(true));

    CloseIfPossible(*enc);
}

TEST_F(ASCII85EncoderTest_215, PSFilterMentionsASCII85WhenAvailable_215)
{
    const std::vector<unsigned char> in = {0x01, 0x02, 0x03, 0x04};
    auto holder = MakeMemStreamFromBytes(in);
    ASSERT_NE(holder.stream, nullptr);

    auto enc = MakeASCII85Encoder(holder.stream.release());
    ASSERT_NE(enc, nullptr);

    if constexpr (has_getPSFilter_string<ASCII85Encoder>::value) {
        const auto ps = enc->getPSFilter(/*psLevel=*/2, /*indent=*/"");
        ASSERT_TRUE(ps.has_value());
        EXPECT_NE(ps->find("ASCII85"), std::string::npos);
    } else {
        // Older Poppler may return GooString* instead; still call to ensure it doesn't crash.
        (void)enc->getPSFilter(/*psLevel=*/2, /*indent=*/"");
        SUCCEED();
    }

    CloseIfPossible(*enc);
}

TEST_F(ASCII85EncoderTest_215, LongOutputMayInsertNewlines_215)
{
    // Create enough non-zero data to likely exceed line-length limits in ASCII85 encoder.
    std::vector<unsigned char> in;
    in.reserve(4 * 80);
    for (int i = 0; i < 4 * 80; ++i) {
        in.push_back(static_cast<unsigned char>((i % 251) + 1)); // avoid all-zero blocks
    }

    auto holder = MakeMemStreamFromBytes(in);
    ASSERT_NE(holder.stream, nullptr);

    auto enc = MakeASCII85Encoder(holder.stream.release());
    ASSERT_NE(enc, nullptr);

    const std::string out = ReadAll(*enc);

    // Must terminate.
    ASSERT_GE(out.size(), 2u);
    EXPECT_EQ(out.substr(out.size() - 2), "~>");

    // Boundary/formatting: many implementations insert '\n' periodically.
    // We only assert that output is plausible: either contains '\n' or is a long single line.
    EXPECT_TRUE(out.find('\n') != std::string::npos || out.size() > 100u);

    CloseIfPossible(*enc);
}