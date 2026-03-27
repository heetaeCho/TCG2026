// TEST_ID: 171
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <string>

#include "tinyxml2.h"

namespace {

class XMLUtilToStrUint64Test_171 : public ::testing::Test {
protected:
    static std::string ExpectedString(uint64_t v) {
        // Match the public contract implied by the interface: decimal representation.
        // Use the same cast type as the implementation’s signature suggests is supported.
        return std::to_string(static_cast<unsigned long long>(v));
    }

    static void CallToStr(uint64_t v, char* buffer, int bufferSize) {
        // Call through the public interface only.
        tinyxml2::XMLUtil::ToStr(v, buffer, bufferSize);
    }
};

TEST_F(XMLUtilToStrUint64Test_171, ZeroFormatsAsDecimal_171) {
    char buf[32] = {};
    CallToStr(0u, buf, static_cast<int>(sizeof(buf)));
    EXPECT_STREQ("0", buf);
}

TEST_F(XMLUtilToStrUint64Test_171, SmallValueFormatsAsDecimal_171) {
    char buf[32] = {};
    CallToStr(42u, buf, static_cast<int>(sizeof(buf)));
    EXPECT_STREQ("42", buf);
}

TEST_F(XMLUtilToStrUint64Test_171, MaxUint64FormatsAsDecimal_171) {
    const uint64_t v = (std::numeric_limits<uint64_t>::max)();
    const std::string expected = ExpectedString(v);

    // Big enough buffer for any uint64 decimal + null terminator.
    char buf[64] = {};
    CallToStr(v, buf, static_cast<int>(sizeof(buf)));

    EXPECT_STREQ(expected.c_str(), buf);
}

TEST_F(XMLUtilToStrUint64Test_171, ExactFitBufferWritesFullString_171) {
    const uint64_t v = 18446744073709551615ull; // max uint64_t on typical platforms
    const std::string expected = ExpectedString(v);

    // Allocate exactly expected length + 1 for null.
    std::string storage(expected.size() + 1, '\0');
    char* buf = storage.data();

    CallToStr(v, buf, static_cast<int>(storage.size()));
    EXPECT_STREQ(expected.c_str(), buf);
}

TEST_F(XMLUtilToStrUint64Test_171, BufferTooSmallTruncatesAndNullTerminates_171) {
    const uint64_t v = (std::numeric_limits<uint64_t>::max)();
    const std::string expected = ExpectedString(v);

    // Force truncation: allow only 6 bytes total (5 chars + '\0').
    constexpr int kBufSize = 6;
    char buf[kBufSize];
    std::fill_n(buf, kBufSize, 'X');

    CallToStr(v, buf, kBufSize);

    // Must be null-terminated within provided size (if bufferSize > 0).
    EXPECT_EQ('\0', buf[kBufSize - 1]);

    // Should match the prefix of the expected decimal string up to kBufSize-1 chars.
    std::string got(buf);
    ASSERT_EQ(static_cast<size_t>(kBufSize - 1), got.size());
    EXPECT_EQ(expected.substr(0, kBufSize - 1), got);
}

TEST_F(XMLUtilToStrUint64Test_171, BufferSizeOneProducesEmptyString_171) {
    char buf[4] = {'A', 'B', 'C', 'D'};

    // Only room for '\0'
    CallToStr(123u, buf, 1);

    EXPECT_EQ('\0', buf[0]);
    // Ensure we didn't clobber beyond the declared size (observable memory safety property).
    EXPECT_EQ('B', buf[1]);
    EXPECT_EQ('C', buf[2]);
    EXPECT_EQ('D', buf[3]);
}

TEST_F(XMLUtilToStrUint64Test_171, DoesNotWriteBeyondProvidedBufferSize_171) {
    const uint64_t v = 1234567890123456789ull;
    const std::string expected = ExpectedString(v);

    // Larger actual array, but we pretend the buffer is smaller.
    char buf[32];
    std::fill_n(buf, sizeof(buf), static_cast<char>(0x7F));

    const int providedSize = 10; // includes null terminator capacity
    CallToStr(v, buf, providedSize);

    // Must be terminated within the provided size (since providedSize > 0).
    EXPECT_EQ('\0', buf[providedSize - 1]);

    // Written content should be prefix of the expected string up to providedSize-1.
    const std::string got(buf);
    EXPECT_EQ(expected.substr(0, providedSize - 1), got);

    // Bytes after providedSize should remain unchanged (no overflow).
    for (size_t i = static_cast<size_t>(providedSize); i < sizeof(buf); ++i) {
        EXPECT_EQ(static_cast<char>(0x7F), buf[i]) << "index=" << i;
    }
}

TEST_F(XMLUtilToStrUint64Test_171, DifferentValuesProduceDifferentStrings_171) {
    char buf1[32] = {};
    char buf2[32] = {};

    CallToStr(100u, buf1, static_cast<int>(sizeof(buf1)));
    CallToStr(101u, buf2, static_cast<int>(sizeof(buf2)));

    EXPECT_STRNE(buf1, buf2);
    EXPECT_STREQ("100", buf1);
    EXPECT_STREQ("101", buf2);
}

} // namespace
