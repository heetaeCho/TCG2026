// File: test_parser_pipe_operator_398.cpp

#include <gtest/gtest.h>
#include <sstream>

// Header under test (path as given in the prompt)
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::Parser;
using Catch::Clara::ExeName;

// Small helper to capture observable state via the public interface.
static std::string CaptureStream(const Parser& p) {
    std::ostringstream os;
    p.writeToStream(os);
    return os.str();
}

// Verifies that (p | rhs) produces the same observable result as
// taking a copy of p and applying (copy |= rhs).
TEST(ParserPipeOperator_398, PipeWithExeName_EqualsCopyPlusOrEquals_398) {
    Parser p; // start from a default parser (no assumptions about its internals)

    // Build using operator|
    Parser piped = p | ExeName{"prog398"};

    // Build the specification-equivalent using copy + |=
    Parser expected(p);
    expected |= ExeName{"prog398"};

    // Compare observable behavior via the public stream output
    EXPECT_EQ(CaptureStream(piped), CaptureStream(expected));
}

// Verifies that operator| does not mutate the left-hand side parser.
// We check this only through public, observable output.
TEST(ParserPipeOperator_398, PipeDoesNotMutateLhs_398) {
    Parser p;

    // Capture original observable state
    const std::string before = CaptureStream(p);

    // Perform piping; by contract this should act on a copy
    Parser piped = p | ExeName{"left-not-mutated"};

    // LHS should remain observably identical
    const std::string after = CaptureStream(p);
    EXPECT_EQ(before, after);

    // Sanity: the result should be *some* parser; we do not assert details,
    // only that it is not required to match `p` (black-box friendly).
    (void)piped;
}

// Verifies that piping with another Parser behaves as copy + |= other.
TEST(ParserPipeOperator_398, PipeWithParser_EqualsCopyPlusOrEquals_398) {
    Parser base;
    Parser other;
    // Modify `other` using only public operators
    other |= ExeName{"other-prog398"};

    // Using operator|
    Parser combined = base | other;

    // Using copy + |=
    Parser expected(base);
    expected |= other;

    EXPECT_EQ(CaptureStream(combined), CaptureStream(expected));
}

// Verifies that chaining with operator| composes like repeated copy + |=.
TEST(ParserPipeOperator_398, PipeChaining_ComposesLikeSequentialOrEquals_398) {
    Parser p;

    // Chain with operator|
    Parser chained = (p | ExeName{"A398"}) | ExeName{"B398"};

    // Sequential copy + |= steps that mirror chaining
    Parser step1(p);
    step1 |= ExeName{"A398"};
    Parser expected(step1);
    expected |= ExeName{"B398"};

    EXPECT_EQ(CaptureStream(chained), CaptureStream(expected));
}
