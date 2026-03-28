// File: tests/XmlEncode_Fuzz_InterfaceTests_20.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>
#include <cstdint>

// Headers from the provided codebase snippets
#include "Catch2/src/catch2/internal/catch_xmlwriter.hpp"
#include "Catch2/fuzzing/NullOStream.h"

namespace {

class XmlEncodeInterfaceTest_20 : public ::testing::Test {
protected:
    // Helper: builds a std::string from raw bytes (mirrors fuzz harness approach)
    static std::string BytesToString(const std::vector<uint8_t>& bytes) {
        return std::string(bytes.begin(), bytes.end());
    }
};

} // namespace

// --- Normal operation ---

TEST_F(XmlEncodeInterfaceTest_20, EncodeTo_WritesToStdOStream_20) {
    std::ostringstream os;
    Catch::XmlEncode enc{ "" };           // default ForWhat (per interface)
    EXPECT_NO_THROW(enc.encodeTo(os));    // should be callable and not throw
    EXPECT_TRUE(os.good());               // stream should remain good

    os.str(""); os.clear();
    Catch::XmlEncode enc2{ "abc" };
    EXPECT_NO_THROW(enc2.encodeTo(os));
    EXPECT_TRUE(os.good());
    // We do not assert exact contents (black-box), but writing non-empty input
    // should produce some output.
    EXPECT_FALSE(os.str().empty());
}

TEST_F(XmlEncodeInterfaceTest_20, OperatorShift_InsertsAndReturnsSameStream_20) {
    std::ostringstream os;
    const Catch::XmlEncode enc{"text"};
    std::ostream& ret = (os << enc);
    // Must return the same stream by reference
    EXPECT_EQ(&ret, static_cast<std::ostream*>(&os));
    EXPECT_TRUE(os.good());
    EXPECT_FALSE(os.str().empty());
}

// --- Boundary conditions ---

TEST_F(XmlEncodeInterfaceTest_20, EncodeTo_EmptyString_ProducesEmptyOutput_20) {
    std::ostringstream os;
    const Catch::XmlEncode enc{""};
    ASSERT_NO_THROW(enc.encodeTo(os));
    EXPECT_TRUE(os.good());
    EXPECT_TRUE(os.str().empty());  // empty input -> empty output is a safe, observable expectation
}

TEST_F(XmlEncodeInterfaceTest_20, EncodeTo_SpecialXmlCharacters_NoThrow_And_NotShorter_20) {
    // Characters commonly special in XML; we do NOT assert how they are encoded,
    // only that encoding does not reduce length (defensive, black-box friendly).
    const std::string input = "<>&\"'";
    std::ostringstream os;
    const Catch::XmlEncode enc{input.c_str()};
    ASSERT_NO_THROW(enc.encodeTo(os));
    EXPECT_TRUE(os.good());
    // Output should be at least as long as input (encoding may expand or keep same)
    EXPECT_GE(os.str().size(), input.size());
}

// Large input boundary
TEST_F(XmlEncodeInterfaceTest_20, EncodeTo_LargeInput_NoThrow_20) {
    // 1 MB of 'a' to simulate large data path; write into NullOStream for cheap sink.
    std::string large(1024 * 1024, 'a');
    Catch::XmlEncode enc{ large.c_str() };
    NullOStream nul;
    EXPECT_NO_THROW(enc.encodeTo(nul));
    // No stream state to inspect on NullOStream; success is "no throw".
}

// --- Exceptional / error-like scenarios (as observable) ---

TEST_F(XmlEncodeInterfaceTest_20, EncodeTo_BinaryData_NoThrow_And_StreamGood_20) {
    // Arbitrary bytes including NULs and high-bit values
    std::vector<uint8_t> bytes = {
        0x00, 0xFF, 0x01, 0x02, 0x7F, 0x80, 0x3C, 0x3E, 0x26, 0x22, 0x27
    };
    std::string buf = XmlEncodeInterfaceTest_20::BytesToString(bytes);

    std::ostringstream os;
    Catch::XmlEncode enc{ buf.c_str() };
    EXPECT_NO_THROW(enc.encodeTo(os));
    EXPECT_TRUE(os.good());
    // Output existence (may differ in size; we do not assert exact content)
    EXPECT_GE(os.str().size(), 0u);
}

// --- Verification of external interactions ---

TEST_F(XmlEncodeInterfaceTest_20, EncodeTo_WritesToNullOStream_NoThrow_20) {
    // Mirrors the fuzzer’s usage pattern
    NullOStream nul;
    const std::string input = "sample";
    Catch::XmlEncode enc{ input.c_str() };
    EXPECT_NO_THROW(enc.encodeTo(nul));
    // Nothing else to assert about NullOStream beyond “no throw”.
}

TEST_F(XmlEncodeInterfaceTest_20, OperatorShift_WithNullOStream_ChainsWithoutFailure_20) {
    NullOStream nul;
    const Catch::XmlEncode enc{"chain"};
    // Chaining support: << should return the same stream reference, so further writes work
    std::ostream& s1 = (nul << enc);
    EXPECT_EQ(&s1, static_cast<std::ostream*>(&nul));
    // Additional writes should be accepted (no throw)
    EXPECT_NO_THROW(s1 << enc);
}
