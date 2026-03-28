// File: tests/reporter_spec_eq_690.cpp
#include <gtest/gtest.h>
#include <map>
#include <string>

// Include the public interface
#include "Catch2/src/catch2/internal/catch_reporter_spec_parser.hpp"

using Catch::ReporterSpec;
using Catch::Optional;
using Catch::ColourMode;

namespace {

// Small helper to construct ReporterSpec instances succinctly.
// This uses only the public constructor (no inspection of internals).
static ReporterSpec MakeSpec(
    const std::string& name,
    Optional<std::string> output,
    Optional<ColourMode> colour,
    const std::map<std::string, std::string>& opts = {}) {
    return ReporterSpec(name, output, colour, opts);
}

} // namespace

// --- Normal operation: identical fields -> equal
TEST(ReporterSpecEqTest_690, AllFieldsIdentical_YieldsEqual_690) {
    auto a = MakeSpec(
        "console",
        Optional<std::string>{std::string("out.txt")},
        Optional<ColourMode>{static_cast<ColourMode>(0)},
        {{"key", "value"}, {"x", "1"}}
    );
    auto b = MakeSpec(
        "console",
        Optional<std::string>{std::string("out.txt")},
        Optional<ColourMode>{static_cast<ColourMode>(0)},
        {{"key", "value"}, {"x", "1"}}
    );

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);            // symmetry
    EXPECT_TRUE(a == a);            // reflexivity
}

// --- Boundary: empty strings and empty optionals should still compare correctly
TEST(ReporterSpecEqTest_690, EmptyNameAndNoOptionals_EqualWhenSame_690) {
    auto a = MakeSpec(
        "",                       // empty name
        Optional<std::string>{},  // no output
        Optional<ColourMode>{},   // no colour
        {}                        // empty options
    );
    auto b = MakeSpec(
        "", Optional<std::string>{}, Optional<ColourMode>{}, {}
    );

    EXPECT_TRUE(a == b);
}

// --- Inequality when names differ
TEST(ReporterSpecEqTest_690, DifferentName_YieldsNotEqual_690) {
    auto a = MakeSpec("console", Optional<std::string>{}, Optional<ColourMode>{}, {});
    auto b = MakeSpec("junit",   Optional<std::string>{}, Optional<ColourMode>{}, {});

    EXPECT_FALSE(a == b);
}

// --- Inequality when output file differs in value
TEST(ReporterSpecEqTest_690, DifferentOutputValue_YieldsNotEqual_690) {
    auto a = MakeSpec("console",
                      Optional<std::string>{std::string("a.txt")},
                      Optional<ColourMode>{}, {});
    auto b = MakeSpec("console",
                      Optional<std::string>{std::string("b.txt")},
                      Optional<ColourMode>{}, {});

    EXPECT_FALSE(a == b);
}

// --- Inequality when one has output file and the other does not
TEST(ReporterSpecEqTest_690, OutputPresentVsAbsent_YieldsNotEqual_690) {
    auto a = MakeSpec("console", Optional<std::string>{}, {});
    auto b = MakeSpec("console", Optional<std::string>{std::string("out.txt")}, {});

    EXPECT_FALSE(a == b);
}

// --- Inequality when colour mode differs in value
TEST(ReporterSpecEqTest_690, DifferentColourValue_YieldsNotEqual_690) {
    auto a = MakeSpec("console",
                      Optional<std::string>{},
                      Optional<ColourMode>{static_cast<ColourMode>(0)},
                      {});
    auto b = MakeSpec("console",
                      Optional<std::string>{},
                      Optional<ColourMode>{static_cast<ColourMode>(1)},
                      {});

    EXPECT_FALSE(a == b);
}

// --- Inequality when one has colour and the other does not
TEST(ReporterSpecEqTest_690, ColourPresentVsAbsent_YieldsNotEqual_690) {
    auto a = MakeSpec("console", Optional<std::string>{}, Optional<ColourMode>{}, {});
    auto b = MakeSpec("console",
                      Optional<std::string>{},
                      Optional<ColourMode>{static_cast<ColourMode>(0)},
                      {});
    EXPECT_FALSE(a == b);
}

// --- Map equality: same key/values in different insertion order -> equal
TEST(ReporterSpecEqTest_690, CustomOptionsSameContentDifferentOrder_Equal_690) {
    std::map<std::string, std::string> opts1{{"a","1"},{"b","2"}};
    std::map<std::string, std::string> opts2{{"b","2"},{"a","1"}}; // different insertion order

    auto a = MakeSpec("console", Optional<std::string>{}, Optional<ColourMode>{}, opts1);
    auto b = MakeSpec("console", Optional<std::string>{}, Optional<ColourMode>{}, opts2);

    EXPECT_TRUE(a == b);
}

// --- Map inequality: differing value for the same key
TEST(ReporterSpecEqTest_690, CustomOptionsDifferentValue_NotEqual_690) {
    auto a = MakeSpec("console", {}, {}, {{"threshold","10"}});
    auto b = MakeSpec("console", {}, {}, {{"threshold","11"}});

    EXPECT_FALSE(a == b);
}

// --- Map inequality: one has extra key
TEST(ReporterSpecEqTest_690, CustomOptionsExtraKey_NotEqual_690) {
    auto a = MakeSpec("console", {}, {}, {{"x","1"}});
    auto b = MakeSpec("console", {}, {}, {{"x","1"},{"y","2"}});

    EXPECT_FALSE(a == b);
}

// --- Transitivity: if a == b and b == c then a == c (sanity for equivalence relation)
TEST(ReporterSpecEqTest_690, EqualityTransitive_690) {
    auto a = MakeSpec("console",
                      Optional<std::string>{std::string("x.log")},
                      Optional<ColourMode>{static_cast<ColourMode>(0)},
                      {{"k","v"}});
    auto b = MakeSpec("console",
                      Optional<std::string>{std::string("x.log")},
                      Optional<ColourMode>{static_cast<ColourMode>(0)},
                      {{"k","v"}});
    auto c = MakeSpec("console",
                      Optional<std::string>{std::string("x.log")},
                      Optional<ColourMode>{static_cast<ColourMode>(0)},
                      {{"k","v"}});

    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == c);
    EXPECT_TRUE(a == c);
}
