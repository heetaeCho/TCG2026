// Sha384Test_1645.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// NOTE:
// sha384() is declared static in Decrypt.cc (internal linkage).
// To test it via its interface, we include the implementation file here so the
// function is available in this translation unit.
#include "./TestProjects/poppler/poppler/Decrypt.cc"

namespace {

std::string ToHex_1645(const unsigned char *buf, size_t len)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < len; ++i) {
        oss << std::setw(2) << static_cast<unsigned int>(buf[i]);
    }
    return oss.str();
}

std::vector<unsigned char> BytesFromString_1645(const std::string &s)
{
    return std::vector<unsigned char>(s.begin(), s.end());
}

class Sha384Test_1645 : public ::testing::Test
{
};

TEST_F(Sha384Test_1645, HashOfEmptyStringMatchesKnownVector_1645)
{
    const std::string msgStr;
    auto msg = BytesFromString_1645(msgStr);

    unsigned char out[48];
    std::memset(out, 0, sizeof(out));
    sha384(msg.data(), static_cast<int>(msg.size()), out);

    const std::string expected =
        "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da"
        "274edebfe76f65fbd51ad2f14898b95b";
    EXPECT_EQ(ToHex_1645(out, sizeof(out)), expected);
}

TEST_F(Sha384Test_1645, HashOfAbcMatchesKnownVector_1645)
{
    const std::string msgStr = "abc";
    auto msg = BytesFromString_1645(msgStr);

    unsigned char out[48];
    std::memset(out, 0, sizeof(out));
    sha384(msg.data(), static_cast<int>(msg.size()), out);

    const std::string expected =
        "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed"
        "8086072ba1e7cc2358baeca134c825a7";
    EXPECT_EQ(ToHex_1645(out, sizeof(out)), expected);
}

TEST_F(Sha384Test_1645, HashOfQuickBrownFoxMatchesKnownVector_1645)
{
    const std::string msgStr = "The quick brown fox jumps over the lazy dog";
    auto msg = BytesFromString_1645(msgStr);

    unsigned char out[48];
    std::memset(out, 0, sizeof(out));
    sha384(msg.data(), static_cast<int>(msg.size()), out);

    const std::string expected =
        "ca737f1014a48f4c0b6dd43cb177b0afd9e5169367544c494011e3317dbf9a50"
        "9cb1e5dc1e85a941bbee3d7f2afbc9b1";
    EXPECT_EQ(ToHex_1645(out, sizeof(out)), expected);
}

TEST_F(Sha384Test_1645, HashOfQuickBrownFoxWithPeriodMatchesKnownVector_1645)
{
    const std::string msgStr = "The quick brown fox jumps over the lazy dog.";
    auto msg = BytesFromString_1645(msgStr);

    unsigned char out[48];
    std::memset(out, 0, sizeof(out));
    sha384(msg.data(), static_cast<int>(msg.size()), out);

    const std::string expected =
        "ed892481d8272ca6df370bf706e4d7bc1b573fa2177aae6c50e946678718fc67"
        "a7af2819a021c2fc34e91bdb63409d";
    EXPECT_EQ(ToHex_1645(out, sizeof(out)), expected);
}

TEST_F(Sha384Test_1645, HashOfLongKnownVectorMatches_1645)
{
    const std::string msgStr =
        "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno"
        "ijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
    auto msg = BytesFromString_1645(msgStr);

    unsigned char out[48];
    std::memset(out, 0, sizeof(out));
    sha384(msg.data(), static_cast<int>(msg.size()), out);

    const std::string expected =
        "09330c33f71147e83d192fc782cd1b4753111b173b3b05d22fa08086e3b0f712"
        "fcc7c71a557e2db966c3e9fa91746039";
    EXPECT_EQ(ToHex_1645(out, sizeof(out)), expected);
}

TEST_F(Sha384Test_1645, DeterministicForSameInput_1645)
{
    std::vector<unsigned char> msg(256);
    for (size_t i = 0; i < msg.size(); ++i) {
        msg[i] = static_cast<unsigned char>(i & 0xFF);
    }

    unsigned char out1[48];
    unsigned char out2[48];
    std::memset(out1, 0, sizeof(out1));
    std::memset(out2, 0, sizeof(out2));

    sha384(msg.data(), static_cast<int>(msg.size()), out1);
    sha384(msg.data(), static_cast<int>(msg.size()), out2);

    EXPECT_EQ(0, std::memcmp(out1, out2, sizeof(out1)));
}

TEST_F(Sha384Test_1645, DifferentInputsProduceDifferentHashesInPractice_1645)
{
    // Observable behavior: changing the input should (practically) change output.
    // This is not asserting internal details; it verifies the function responds to input changes.
    std::vector<unsigned char> msg1(64, static_cast<unsigned char>('A'));
    std::vector<unsigned char> msg2 = msg1;
    msg2[0] = static_cast<unsigned char>('B');

    unsigned char out1[48];
    unsigned char out2[48];
    std::memset(out1, 0, sizeof(out1));
    std::memset(out2, 0, sizeof(out2));

    sha384(msg1.data(), static_cast<int>(msg1.size()), out1);
    sha384(msg2.data(), static_cast<int>(msg2.size()), out2);

    EXPECT_NE(0, std::memcmp(out1, out2, sizeof(out1)));
}

TEST_F(Sha384Test_1645, HandlesBoundaryLengthsAroundPaddingThreshold_1645)
{
    // Boundary conditions: lengths around 112 bytes (SHA-512-family padding threshold for final block)
    // We only verify observable properties (no crash, deterministic outputs, and sensitivity to length).
    const std::vector<int> lens = {111, 112, 113};
    std::vector<std::string> hexes;

    for (int len : lens) {
        std::vector<unsigned char> msg(static_cast<size_t>(len), static_cast<unsigned char>('x'));

        unsigned char outA[48];
        unsigned char outB[48];
        std::memset(outA, 0, sizeof(outA));
        std::memset(outB, 0, sizeof(outB));

        sha384(msg.data(), len, outA);
        sha384(msg.data(), len, outB);

        // Deterministic for the same input/length.
        EXPECT_EQ(0, std::memcmp(outA, outB, sizeof(outA)));

        hexes.push_back(ToHex_1645(outA, sizeof(outA)));
    }

    // Different lengths (even if same fill byte) should typically yield different digests.
    EXPECT_NE(hexes[0], hexes[1]);
    EXPECT_NE(hexes[1], hexes[2]);
}

TEST_F(Sha384Test_1645, HandlesBlockBoundaryLengths_1645)
{
    // Boundary conditions: exact 128-byte block and nearby.
    const std::vector<int> lens = {127, 128, 129};
    std::vector<std::string> hexes;

    for (int len : lens) {
        std::vector<unsigned char> msg(static_cast<size_t>(len), static_cast<unsigned char>('A'));

        unsigned char out[48];
        std::memset(out, 0, sizeof(out));
        sha384(msg.data(), len, out);

        // Basic observable sanity: output isn't all zeros for typical inputs.
        const bool allZero = std::all_of(std::begin(out), std::end(out),
                                         [](unsigned char b) { return b == 0; });
        EXPECT_FALSE(allZero);

        hexes.push_back(ToHex_1645(out, sizeof(out)));
    }

    EXPECT_NE(hexes[0], hexes[1]);
    EXPECT_NE(hexes[1], hexes[2]);
}

} // namespace