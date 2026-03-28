// File: prog_prefix_accel_test_131.cc

#include "re2/prog.h"
#include <gtest/gtest.h>
#include <cstring>
#include <string>

using re2::Prog;

class ProgPrefixAccelTest_131 : public ::testing::Test {
protected:
    // Helper to make a byte buffer from a std::string (stable pointer).
    static const void* BufPtr(const std::string& s) { return static_cast<const void*>(s.data()); }
};

// Normal + boundary: single-char, no fold -> memchr path.
TEST_F(ProgPrefixAccelTest_131, RoutesToMemchrWhenSingleCharNoFold_131) {
    Prog p;
    p.ConfigurePrefixAccel("X", /*prefix_foldcase=*/false);
    ASSERT_TRUE(p.can_prefix_accel());  // Observable state via public API.

    const std::string data = "abcXdefX";
    const void* base = BufPtr(data);

    // Should return pointer to the first 'X' (memchr semantics).
    const void* got = p.PrefixAccel(base, data.size());
    ASSERT_NE(got, nullptr);
    EXPECT_EQ(static_cast<const char*>(got) - static_cast<const char*>(base), 3);

    // When character is absent -> nullptr.
    const std::string data_absent = "abcdef";
    EXPECT_EQ(p.PrefixAccel(BufPtr(data_absent), data_absent.size()), nullptr);

    // Boundary: size=0 -> nullptr (memchr with zero count).
    EXPECT_EQ(p.PrefixAccel(BufPtr(data), 0), nullptr);

    // Boundary: character at position 0.
    const std::string data0 = "Xzzz";
    const void* got0 = p.PrefixAccel(BufPtr(data0), data0.size());
    ASSERT_NE(got0, nullptr);
    EXPECT_EQ(static_cast<const char*>(got0) - static_cast<const char*>(BufPtr(data0)), 0);
}

// Delegation check: multi-char, no fold -> FrontAndBack path.
// We validate by comparing PrefixAccel's return to the public collaborator
// PrefixAccel_FrontAndBack under identical inputs (black-box equivalence).
TEST_F(ProgPrefixAccelTest_131, RoutesToFrontAndBackWhenMultiCharNoFold_131) {
    Prog p;
    p.ConfigurePrefixAccel("AB", /*prefix_foldcase=*/false);
    ASSERT_TRUE(p.can_prefix_accel());

    const std::string data1 = "xxAByy";
    const std::string data2 = "nope";

    // Normal case: compare outputs exactly.
    const void* expected1 = p.PrefixAccel_FrontAndBack(BufPtr(data1), data1.size());
    const void* got1      = p.PrefixAccel(BufPtr(data1), data1.size());
    EXPECT_EQ(got1, expected1);

    // Not found.
    const void* expected2 = p.PrefixAccel_FrontAndBack(BufPtr(data2), data2.size());
    const void* got2      = p.PrefixAccel(BufPtr(data2), data2.size());
    EXPECT_EQ(got2, expected2);

    // Boundary: buffer smaller than prefix length.
    const std::string small = "A";
    const void* expected_small = p.PrefixAccel_FrontAndBack(BufPtr(small), small.size());
    const void* got_small      = p.PrefixAccel(BufPtr(small), small.size());
    EXPECT_EQ(got_small, expected_small);

    // Boundary: size = 0.
    const std::string any = "AB";
    const void* expected0 = p.PrefixAccel_FrontAndBack(BufPtr(any), 0);
    const void* got0      = p.PrefixAccel(BufPtr(any), 0);
    EXPECT_EQ(got0, expected0);
}

// Delegation check: foldcase=true -> ShiftDFA path.
// Validate by comparing to public PrefixAccel_ShiftDFA (black-box equivalence).
TEST_F(ProgPrefixAccelTest_131, RoutesToShiftDFAWhenFoldcase_131) {
    Prog p;
    p.ConfigurePrefixAccel("aB", /*prefix_foldcase=*/true);
    ASSERT_TRUE(p.can_prefix_accel());

    const std::string data1 = "xxAbyy";  // Potential foldcase match depending on implementation.
    const std::string data2 = "no match here";

    const void* expected1 = p.PrefixAccel_ShiftDFA(BufPtr(data1), data1.size());
    const void* got1      = p.PrefixAccel(BufPtr(data1), data1.size());
    EXPECT_EQ(got1, expected1);

    const void* expected2 = p.PrefixAccel_ShiftDFA(BufPtr(data2), data2.size());
    const void* got2      = p.PrefixAccel(BufPtr(data2), data2.size());
    EXPECT_EQ(got2, expected2);

    // Boundary: size = 0.
    const void* expected0 = p.PrefixAccel_ShiftDFA(BufPtr(data1), 0);
    const void* got0      = p.PrefixAccel(BufPtr(data1), 0);
    EXPECT_EQ(got0, expected0);
}
