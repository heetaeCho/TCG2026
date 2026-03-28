// File: test_xmlutil_convertutf32toutf8_163.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

#include "tinyxml2.h"

namespace {

using tinyxml2::XMLUtil;

class XMLUtilConvertUTF32ToUTF8Test_163 : public ::testing::Test {
protected:
    static void Fill(std::array<unsigned char, 16>& buf, unsigned char v) {
        buf.fill(v);
    }
};

static void ExpectBytesEq_163(const unsigned char* actual,
                              const std::initializer_list<unsigned char>& expected) {
    size_t i = 0;
    for (auto b : expected) {
        EXPECT_EQ(actual[i], b) << "Mismatch at byte " << i;
        ++i;
    }
}

}  // namespace

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, AsciiOneByte_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x41UL /* 'A' */, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 1);
    EXPECT_EQ(out[0], 0x41);
    // Ensure no extra bytes were touched beyond the produced length.
    EXPECT_EQ(out[1], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, TwoByteSequence_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x00A2UL /* U+00A2: ¢ */, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 2);
    ExpectBytesEq_163(out.data(), {0xC2, 0xA2});
    EXPECT_EQ(out[2], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, ThreeByteSequence_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x20ACUL /* U+20AC: € */, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 3);
    ExpectBytesEq_163(out.data(), {0xE2, 0x82, 0xAC});
    EXPECT_EQ(out[3], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, FourByteSequence_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x1F600UL /* U+1F600: 😀 */, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 4);
    ExpectBytesEq_163(out.data(), {0xF0, 0x9F, 0x98, 0x80});
    EXPECT_EQ(out[4], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, Boundary_LastOneByte_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x7FUL, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 1);
    EXPECT_EQ(out[0], 0x7F);
    EXPECT_EQ(out[1], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, Boundary_FirstTwoBytes_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x80UL, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 2);
    ExpectBytesEq_163(out.data(), {0xC2, 0x80});
    EXPECT_EQ(out[2], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, Boundary_LastTwoBytes_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x7FFUL, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 2);
    ExpectBytesEq_163(out.data(), {0xDF, 0xBF});
    EXPECT_EQ(out[2], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, Boundary_FirstThreeBytes_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x800UL, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 3);
    ExpectBytesEq_163(out.data(), {0xE0, 0xA0, 0x80});
    EXPECT_EQ(out[3], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, Boundary_LastThreeBytes_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0xFFFFUL, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 3);
    ExpectBytesEq_163(out.data(), {0xEF, 0xBF, 0xBF});
    EXPECT_EQ(out[3], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, Boundary_FirstFourBytes_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x10000UL, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 4);
    ExpectBytesEq_163(out.data(), {0xF0, 0x90, 0x80, 0x80});
    EXPECT_EQ(out[4], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, Boundary_LastFourBytesWithinSupportedRange_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x1FFFFFUL, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 4);
    ExpectBytesEq_163(out.data(), {0xF7, 0xBF, 0xBF, 0xBF});
    EXPECT_EQ(out[4], 0xCC);
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, OutOfRangeSetsLengthZeroAndDoesNotModifyOutput_163) {
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    int len = -1;
    XMLUtil::ConvertUTF32ToUTF8(0x200000UL, reinterpret_cast<char*>(out.data()), &len);

    EXPECT_EQ(len, 0);
    // Observable behavior: should not write any bytes when length is 0.
    for (size_t i = 0; i < out.size(); ++i) {
        EXPECT_EQ(out[i], 0xCC) << "Output modified at index " << i;
    }
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, NullLengthPointerDeath_163) {
#if GTEST_HAS_DEATH_TEST
    std::array<unsigned char, 16> out{};
    Fill(out, 0xCC);

    // Passing a null length pointer is invalid usage; observable behavior is a crash/assert in many builds.
    EXPECT_DEATH(
        { XMLUtil::ConvertUTF32ToUTF8(0x41UL, reinterpret_cast<char*>(out.data()), nullptr); },
        "");
#else
    GTEST_SKIP() << "Death tests are not supported in this build configuration.";
#endif
}

TEST_F(XMLUtilConvertUTF32ToUTF8Test_163, NullOutputPointerDeath_163) {
#if GTEST_HAS_DEATH_TEST
    int len = -1;

    // Passing a null output pointer is invalid usage; observable behavior is a crash/assert in many builds.
    EXPECT_DEATH(
        { XMLUtil::ConvertUTF32ToUTF8(0x41UL, nullptr, &len); },
        "");
#else
    GTEST_SKIP() << "Death tests are not supported in this build configuration.";
#endif
}
