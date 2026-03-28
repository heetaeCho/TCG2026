#include <gtest/gtest.h>
#include <string>
#include <map>

// Include the header for ProcessedReporterSpec
#include "catch2/catch_config.hpp"

using namespace Catch;

class ProcessedReporterSpecTest_711 : public ::testing::Test {
protected:
    ProcessedReporterSpec createSpec(
        const std::string& name,
        const std::string& outputFilename,
        ColourMode colourMode,
        const std::map<std::string, std::string>& customOptions = {}
    ) {
        ProcessedReporterSpec spec;
        spec.name = name;
        spec.outputFilename = outputFilename;
        spec.colourMode = colourMode;
        spec.customOptions = customOptions;
        return spec;
    }
};

TEST_F(ProcessedReporterSpecTest_711, IdenticalSpecsAreEqual_711) {
    auto spec1 = createSpec("console", "output.txt", ColourMode::PlatformDefault);
    auto spec2 = createSpec("console", "output.txt", ColourMode::PlatformDefault);
    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, DifferentNameNotEqual_711) {
    auto spec1 = createSpec("console", "output.txt", ColourMode::PlatformDefault);
    auto spec2 = createSpec("xml", "output.txt", ColourMode::PlatformDefault);
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, DifferentOutputFilenameNotEqual_711) {
    auto spec1 = createSpec("console", "output1.txt", ColourMode::PlatformDefault);
    auto spec2 = createSpec("console", "output2.txt", ColourMode::PlatformDefault);
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, DifferentColourModeNotEqual_711) {
    auto spec1 = createSpec("console", "output.txt", ColourMode::PlatformDefault);
    auto spec2 = createSpec("console", "output.txt", ColourMode::None);
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, DifferentCustomOptionsNotEqual_711) {
    std::map<std::string, std::string> opts1 = {{"key1", "val1"}};
    std::map<std::string, std::string> opts2 = {{"key2", "val2"}};
    auto spec1 = createSpec("console", "output.txt", ColourMode::PlatformDefault, opts1);
    auto spec2 = createSpec("console", "output.txt", ColourMode::PlatformDefault, opts2);
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, SameCustomOptionsAreEqual_711) {
    std::map<std::string, std::string> opts = {{"key1", "val1"}, {"key2", "val2"}};
    auto spec1 = createSpec("console", "output.txt", ColourMode::PlatformDefault, opts);
    auto spec2 = createSpec("console", "output.txt", ColourMode::PlatformDefault, opts);
    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, EmptySpecsAreEqual_711) {
    auto spec1 = createSpec("", "", ColourMode::PlatformDefault);
    auto spec2 = createSpec("", "", ColourMode::PlatformDefault);
    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, EmptyVsNonEmptyNameNotEqual_711) {
    auto spec1 = createSpec("", "output.txt", ColourMode::PlatformDefault);
    auto spec2 = createSpec("console", "output.txt", ColourMode::PlatformDefault);
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, EmptyVsNonEmptyOutputFilenameNotEqual_711) {
    auto spec1 = createSpec("console", "", ColourMode::PlatformDefault);
    auto spec2 = createSpec("console", "output.txt", ColourMode::PlatformDefault);
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, EmptyCustomOptionsVsNonEmptyNotEqual_711) {
    std::map<std::string, std::string> opts = {{"key", "value"}};
    auto spec1 = createSpec("console", "output.txt", ColourMode::PlatformDefault);
    auto spec2 = createSpec("console", "output.txt", ColourMode::PlatformDefault, opts);
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, CustomOptionsDifferentValuesNotEqual_711) {
    std::map<std::string, std::string> opts1 = {{"key", "val1"}};
    std::map<std::string, std::string> opts2 = {{"key", "val2"}};
    auto spec1 = createSpec("console", "output.txt", ColourMode::PlatformDefault, opts1);
    auto spec2 = createSpec("console", "output.txt", ColourMode::PlatformDefault, opts2);
    EXPECT_FALSE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, SelfEqualityCheck_711) {
    std::map<std::string, std::string> opts = {{"a", "b"}, {"c", "d"}};
    auto spec = createSpec("reporter", "file.xml", ColourMode::PlatformDefault, opts);
    EXPECT_TRUE(spec == spec);
}

TEST_F(ProcessedReporterSpecTest_711, MultipleCustomOptionsOrder_711) {
    std::map<std::string, std::string> opts1 = {{"a", "1"}, {"b", "2"}, {"c", "3"}};
    std::map<std::string, std::string> opts2 = {{"c", "3"}, {"a", "1"}, {"b", "2"}};
    auto spec1 = createSpec("console", "out.txt", ColourMode::PlatformDefault, opts1);
    auto spec2 = createSpec("console", "out.txt", ColourMode::PlatformDefault, opts2);
    // std::map orders by key, so insertion order doesn't matter; they should be equal
    EXPECT_TRUE(spec1 == spec2);
}

TEST_F(ProcessedReporterSpecTest_711, AllFieldsDifferentNotEqual_711) {
    std::map<std::string, std::string> opts1 = {{"x", "y"}};
    std::map<std::string, std::string> opts2 = {{"a", "b"}};
    auto spec1 = createSpec("console", "out1.txt", ColourMode::PlatformDefault, opts1);
    auto spec2 = createSpec("xml", "out2.txt", ColourMode::None, opts2);
    EXPECT_FALSE(spec1 == spec2);
}
