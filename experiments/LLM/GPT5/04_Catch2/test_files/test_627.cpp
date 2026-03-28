// TextFlow_Columns_OperatorPlus_627_Test.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the provided public headers
#include "catch_textflow.hpp"

using namespace Catch::TextFlow;

namespace {

// Small helpers to observe behavior only via the public ostream operators.
std::string ToString(const Columns& cols) {
    std::ostringstream os;
    os << cols;
    return os.str();
}

std::string ToString(const Column& col) {
    std::ostringstream os;
    os << col;
    return os.str();
}

class TextFlowColumnsOpPlusTest_627 : public ::testing::Test {};
} // namespace

// Verifies that operator+(Columns, Column) does not modify the left-hand side.
// We compare the serialized form of LHS before and after invoking operator+.
TEST_F(TextFlowColumnsOpPlusTest_627, Plus_DoesNotModifyLhs_627) {
    Column a{"A"};
    Column b{"B"};
    Column r{"R"};

    // Build a Columns value for LHS using public Column+Column
    Columns lhs = a + b;

    // Snapshot of LHS (observable via operator<<)
    const std::string before = ToString(lhs);

    // Apply operator+(Columns, Column) under test
    Columns result = lhs + r;

    // LHS should remain unchanged
    EXPECT_EQ(ToString(lhs), before) << "LHS changed after operator+(Columns, Column)";
    // Result should be different from the original LHS in general (not strictly required),
    // but we avoid assuming internal formatting. The key assertion is LHS immutability.
    (void)result;
}

// Verifies that operator+(Columns, Column) produces the same observable result
// as making a copy and applying operator+=(Columns&, Column) once.
TEST_F(TextFlowColumnsOpPlusTest_627, Plus_EquivalentToCopyThenPlusEquals_627) {
    Column a{"Left"};
    Column b{"Mid"};
    Column r{"Right"};

    Columns lhs = a + b;

    // Path 1: operator+(Columns, Column) — subject under test
    Columns viaPlus = lhs + r;

    // Path 2: explicit copy then operator+=(Columns&, Column) — reference behavior
    Columns viaPlusEq = lhs;          // copy via public copy-constructible interface
    operator+=(viaPlusEq, r);         // use the public += (do not assume member vs non-member)

    EXPECT_EQ(ToString(viaPlus), ToString(viaPlusEq))
        << "operator+ result must match copy-then-operator+= observable output";
}

// Verifies chaining: (lhs + r1) + r2 matches applying operator+= twice on a copy.
// This exercises associativity with respect to the observable output, without
// assuming any internal representation.
TEST_F(TextFlowColumnsOpPlusTest_627, Plus_ChainsLikeRepeatedPlusEquals_627) {
    Column a{"X"};
    Column b{"Y"};
    Column r1{"R1"};
    Column r2{"R2"};

    Columns lhs = a + b;

    // Chain with operator+ (under test)
    Columns chained = (lhs + r1) + r2;

    // Reference: copy then two += applications
    Columns staged = lhs;
    operator+=(staged, r1);
    operator+=(staged, r2);

    EXPECT_EQ(ToString(chained), ToString(staged))
        << "Chained operator+ should match two successive operator+= applications";
}

// Boundary case: combining an empty Column should match += with the same empty Column.
// We make no assumptions about whether an empty Column changes the output — only that
// operator+ mirrors the observable behavior of operator+=.
TEST_F(TextFlowColumnsOpPlusTest_627, Plus_WithEmptyColumn_MirrorsPlusEquals_627) {
    Column a{"Alpha"};
    Column b{"Beta"};
    Column empty{""};

    Columns lhs = a + b;

    Columns viaPlus = lhs + empty;

    Columns viaPlusEq = lhs;
    operator+=(viaPlusEq, empty);

    EXPECT_EQ(ToString(viaPlus), ToString(viaPlusEq))
        << "operator+ with empty Column must match operator+=";
}
