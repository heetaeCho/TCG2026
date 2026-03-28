// Decrypt_sha256sigma1_test_1633.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// NOTE:
// sha256sigma1() is a static inline function in Decrypt.cc, so it is not link-visible.
// To test it via its provided interface, we include the implementation file directly.
#include "Decrypt.cc"

class DecryptSha256Sigma1Test_1633 : public ::testing::Test {};

TEST_F(DecryptSha256Sigma1Test_1633, ReturnsExpectedForZero_1633)
{
    EXPECT_EQ(sha256sigma1(0u), 0u);
}

TEST_F(DecryptSha256Sigma1Test_1633, ReturnsExpectedKnownVectors_1633)
{
    struct Vec {
        unsigned int in;
        unsigned int out;
    };

    // Precomputed expected values (golden vectors).
    const std::vector<Vec> vectors = {
        {0u, 0u},
        {1u, 0x0000A000u},
        {0xFFFFFFFFu, 0x003FFFFFu},
        {0x80000000u, 0x00205000u},
        {0x12345678u, 0xA1F78649u},
        {0x9ABCDEF0u, 0xF480F13Eu},
        {0xDEADBEEFu, 0x689DBFECu},
    };

    for (const auto &v : vectors) {
        EXPECT_EQ(sha256sigma1(v.in), v.out) << "input=0x" << std::hex << v.in;
    }
}

TEST_F(DecryptSha256Sigma1Test_1633, HandlesBoundaryAroundBitShift10_1633)
{
    // Boundary around the (x >> 10) term.
    EXPECT_EQ(sha256sigma1(0x000003FFu), 0x01806000u);
    EXPECT_EQ(sha256sigma1(0x00000400u), 0x02800001u);
}

TEST_F(DecryptSha256Sigma1Test_1633, DeterministicForSameInput_1633)
{
    const unsigned int x = 0x12345678u;
    const unsigned int y1 = sha256sigma1(x);
    const unsigned int y2 = sha256sigma1(x);
    const unsigned int y3 = sha256sigma1(x);

    EXPECT_EQ(y1, y2);
    EXPECT_EQ(y2, y3);
}

TEST_F(DecryptSha256Sigma1Test_1633, ProducesDifferentOutputsForDifferentInputsInSampleSet_1633)
{
    // Not asserting global injectivity, just that a small diverse sample does not collide.
    const std::vector<unsigned int> inputs = {
        0u, 1u, 2u, 0x3FFu, 0x400u, 0x80000000u, 0xFFFFFFFFu, 0x12345678u, 0x9ABCDEF0u, 0xDEADBEEFu
    };

    std::vector<unsigned int> outputs;
    outputs.reserve(inputs.size());
    for (auto x : inputs) {
        outputs.push_back(sha256sigma1(x));
    }

    for (size_t i = 0; i < outputs.size(); ++i) {
        for (size_t j = i + 1; j < outputs.size(); ++j) {
            EXPECT_NE(outputs[i], outputs[j])
                << "Unexpected collision for inputs 0x" << std::hex << inputs[i]
                << " and 0x" << std::hex << inputs[j];
        }
    }
}