// File: tests/processed_reporter_spec_eq_711_tests.cpp

#include <gtest/gtest.h>
#include <map>
#include <string>

// Include the real header from your tree:
// #include "Catch2/src/catch2/catch_config.hpp"

namespace Catch {
    // Forward declarations for compilation in isolation of these tests.
    // Remove this block if you include the real header above.
    enum class ColourMode { PlatformDefault, ANSI, None };

    struct ProcessedReporterSpec {
        // Public fields (as exposed by the interface).
        std::string name;              // Present in the operator== implementation.
        std::string outputFilename;
        ColourMode colourMode;
        std::map<std::string, std::string> customOptions;
    };

    // The real operator== exists in the implementation TU.
    // Here we only declare it to let the tests compile & link against the real code.
    bool operator==(ProcessedReporterSpec const& lhs, ProcessedReporterSpec const& rhs);
    inline bool operator!=(ProcessedReporterSpec const& lhs, ProcessedReporterSpec const& rhs) {
        return !(lhs == rhs);
    }
}

using Catch::ProcessedReporterSpec;
using Catch::ColourMode;

class ProcessedReporterSpecTest_711 : public ::testing::Test {
protected:
    static ProcessedReporterSpec MakeSpec(
        const std::string& name,
        const std::string& out,
        ColourMode mode,
        std::map<std::string, std::string> opts = {}
    ) {
        ProcessedReporterSpec s;
        s.name = name;
        s.outputFilename = out;
        s.colourMode = mode;
        s.customOptions = std::move(opts);
        return s;
    }
};

// Normal operation: all observable fields equal -> equality true
TEST_F(ProcessedReporterSpecTest_711, Equal_AllFieldsEqual_711) {
    auto a = MakeSpec("console", "results.xml", ColourMode::ANSI,
                      {{"key1","val1"}, {"key2","val2"}});
    auto b = MakeSpec("console", "results.xml", ColourMode::ANSI,
                      {{"key1","val1"}, {"key2","val2"}});
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

// Boundary: empty strings and empty options map considered equal if other fields match
TEST_F(ProcessedReporterSpecTest_711, Boundary_EmptyStringsAndEmptyOptions_711) {
    auto a = MakeSpec("", "", ColourMode::PlatformDefault, {});
    auto b = MakeSpec("", "", ColourMode::PlatformDefault, {});
    EXPECT_TRUE(a == b);
}

// Map insertion order should not affect equality (observable: still equal)
TEST_F(ProcessedReporterSpecTest_711, Equality_IgnoresMapOrder_711) {
    auto a = MakeSpec("xml", "out.txt", ColourMode::None,
                      {{"a","1"}, {"b","2"}, {"c","3"}});
    // Insert in different order
    auto b = MakeSpec("xml", "out.txt", ColourMode::None,
                      {{"c","3"}, {"a","1"}, {"b","2"}});
    EXPECT_TRUE(a == b);
}

// Exceptional/negative: differing name -> not equal
TEST_F(ProcessedReporterSpecTest_711, NotEqual_DifferentName_711) {
    auto a = MakeSpec("console", "file", ColourMode::ANSI, {{"x","y"}});
    auto b = MakeSpec("junit",   "file", ColourMode::ANSI, {{"x","y"}});
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

// Exceptional/negative: differing output filename -> not equal
TEST_F(ProcessedReporterSpecTest_711, NotEqual_DifferentOutputFilename_711) {
    auto a = MakeSpec("console", "a.txt", ColourMode::ANSI, {});
    auto b = MakeSpec("console", "b.txt", ColourMode::ANSI, {});
    EXPECT_FALSE(a == b);
}

// Exceptional/negative: differing colour mode -> not equal
TEST_F(ProcessedReporterSpecTest_711, NotEqual_DifferentColourMode_711) {
    auto a = MakeSpec("console", "out", ColourMode::ANSI, {});
    auto b = MakeSpec("console", "out", ColourMode::None, {});
    EXPECT_FALSE(a == b);
}

// Exceptional/negative: same keys but one value differs -> not equal
TEST_F(ProcessedReporterSpecTest_711, NotEqual_DifferentCustomOptionsValue_711) {
    auto a = MakeSpec("console", "out", ColourMode::ANSI, {{"k","v1"}});
    auto b = MakeSpec("console", "out", ColourMode::ANSI, {{"k","v2"}});
    EXPECT_FALSE(a == b);
}

// Exceptional/negative: one has extra key -> not equal
TEST_F(ProcessedReporterSpecTest_711, NotEqual_ExtraCustomOptionKey_711) {
    auto a = MakeSpec("console", "out", ColourMode::ANSI, {{"k1","v1"}});
    auto b = MakeSpec("console", "out", ColourMode::ANSI, {{"k1","v1"}, {"k2","v2"}});
    EXPECT_FALSE(a == b);
}

// General properties: reflexivity and symmetry (observable through ==/!=)
TEST_F(ProcessedReporterSpecTest_711, Properties_ReflexiveAndSymmetric_711) {
    auto a = MakeSpec("console", "out", ColourMode::PlatformDefault, {{"a","b"}});
    auto b = MakeSpec("console", "out", ColourMode::PlatformDefault, {{"a","b"}});
    // Reflexive
    EXPECT_TRUE(a == a);
    // Symmetric
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(b != a);
}
