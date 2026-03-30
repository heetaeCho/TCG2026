// File: session_cli_tests_455.cpp
#include <gtest/gtest.h>
#include <sstream>

// Headers under test
#include "catch2/catch_session.hpp"
#include "catch2/internal/catch_clara.hpp"

using Catch::Session;
using Catch::Clara::Parser;

namespace {

// Helper: safely render a Parser to string using only public API.
std::string RenderParser(const Parser& p) {
    std::ostringstream os;
    p.writeToStream(os); // public, const-qualified per header
    return os.str();
}

} // namespace

// TEST_ID = 455

// Verifies that calling Session::cli(newParser) results in Session::cli()
// reflecting the same observable state as `newParser`, as seen via writeToStream.
TEST(SessionCliTest_455, StoresProvidedParser_455) {
    Session s;

    Parser provided; // default-construct; treat as black box
    // We cannot rely on internal details; we only compare publicly rendered output.
    const std::string expected = RenderParser(provided);

    s.cli(provided); // set

    const Parser& got = s.cli(); // observe
    const std::string observed = RenderParser(got);

    EXPECT_EQ(observed, expected);
}

// Verifies that setting the CLI parser again overwrites the previous value,
// as observed through writeToStream. We avoid assuming how to mutate Parser;
// we only ensure that after the second set, Session::cli() matches that parser’s output.
TEST(SessionCliTest_455, OverwritesPreviousParser_455) {
    Session s;

    Parser first;
    s.cli(first);
    const std::string first_out = RenderParser(s.cli());

    Parser second;
    // Even if `first` and `second` render the same (black box),
    // we still verify that after setting `second`, Session::cli() matches `second`.
    s.cli(second);
    const std::string after_second_set_out = RenderParser(s.cli());
    const std::string second_out = RenderParser(second);

    // Must match the most recently set parser
    EXPECT_EQ(after_second_set_out, second_out);

    // Optional sanity: If the underlying library gives different outputs for distinct parsers,
    // this assertion provides additional coverage without depending on it to pass.
    if (first_out != second_out) {
        EXPECT_NE(after_second_set_out, first_out);
    }
}

// Verifies that the reference returned by Session::cli() remains valid & stable
// across reassignments (we can take its address before and after).
// Note: The address of the *member* object is expected to be stable.
TEST(SessionCliTest_455, ReferenceStabilityAcrossAssignments_455) {
    Session s;

    const Parser* addr_before_set = &s.cli(); // take address of the returned const reference

    Parser p1;
    s.cli(p1);
    const Parser* addr_after_first_set = &s.cli();

    Parser p2;
    s.cli(p2);
    const Parser* addr_after_second_set = &s.cli();

    // The address of the internal Parser instance should remain stable
    // (member object’s address does not change just because it is assigned to).
    EXPECT_EQ(addr_before_set, addr_after_first_set);
    EXPECT_EQ(addr_after_first_set, addr_after_second_set);

    // Still behaves normally after multiple sets (no-throw usage check)
    (void)RenderParser(s.cli());
}
