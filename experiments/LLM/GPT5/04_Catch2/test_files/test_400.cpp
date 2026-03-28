// File: tests/parser_ostream_operator_400_test.cpp

#include <gtest/gtest.h>
#include <sstream>

// Include the header under test.
// Adjust the relative path if your test build layout differs.
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {

using Catch::Clara::Parser;

// A tiny helper to build an ostream that already has failbit set.
struct FailingStream : public std::ostringstream {
    FailingStream() {
        // Pre-set an error condition to ensure operator<< does not implicitly reset it.
        setstate(std::ios::failbit);
    }
};

} // namespace

// Verifies that operator<< returns the same ostream reference (critical for chaining).
TEST(ParserOstreamTest_400, OperatorReturnsSameStream_400) {
    Parser parser; // treat as black box: default-constructed instance
    std::ostringstream os;

    std::ostream& ret = (os << parser);

    // The operator must return the exact same stream reference it received.
    EXPECT_EQ(&ret, static_cast<std::ostream*>(&os));
}

// Verifies that chaining via << works as expected when followed by writing more data.
TEST(ParserOstreamTest_400, OperatorSupportsChaining_400) {
    Parser parser;
    std::ostringstream os;

    // Chain the insertion with additional text.
    (os << parser) << "TAIL";

    // Whatever writeToStream does internally is a black box; we only assert that
    // chaining kept the stream usable and "TAIL" made it into the buffer.
    EXPECT_NE(os.str().find("TAIL"), std::string::npos);
}

// Verifies operator<< does not (on its own) clear a pre-existing fail state.
TEST(ParserOstreamTest_400, OperatorPreservesPreexistingFailbit_400) {
    Parser parser;
    FailingStream fos;

    // If the stream is already in fail state, << should still return the same stream
    // and should NOT clear the error flags.
    std::ostream& ret = (fos << parser);

    EXPECT_EQ(&ret, static_cast<std::ostream*>(&fos));
    EXPECT_TRUE(fos.fail());
    // Also ensure we can still attempt to chain; stream should remain in fail state.
    ret << "X";
    EXPECT_TRUE(fos.fail());
}
