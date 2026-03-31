#include "catch2/internal/catch_reporter_spec_parser.hpp"
#include <gtest/gtest.h>
#include <string>
#include <map>

using namespace Catch;

class ReporterSpecTest_418 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and accessor methods
TEST_F(ReporterSpecTest_418, ConstructorAndNameAccessor_418) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_EQ(spec.name(), "console");
}

TEST_F(ReporterSpecTest_418, ConstructorWithOutputFile_418) {
    Optional<std::string> outputFile("output.txt");
    ReporterSpec spec("xml", outputFile, {}, {});
    EXPECT_EQ(spec.name(), "xml");
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "output.txt");
}

TEST_F(ReporterSpecTest_418, ConstructorWithNoOutputFile_418) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_FALSE(spec.outputFile().has_value());
}

TEST_F(ReporterSpecTest_418, ConstructorWithColourMode_418) {
    Optional<ColourMode> colour(ColourMode::ANSI);
    ReporterSpec spec("console", {}, colour, {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::ANSI);
}

TEST_F(ReporterSpecTest_418, ConstructorWithNoColourMode_418) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_FALSE(spec.colourMode().has_value());
}

TEST_F(ReporterSpecTest_418, ConstructorWithCustomOptions_418) {
    std::map<std::string, std::string> options;
    options["key1"] = "value1";
    options["key2"] = "value2";
    ReporterSpec spec("console", {}, {}, options);
    EXPECT_EQ(spec.customOptions().size(), 2u);
    EXPECT_EQ(spec.customOptions().at("key1"), "value1");
    EXPECT_EQ(spec.customOptions().at("key2"), "value2");
}

TEST_F(ReporterSpecTest_418, ConstructorWithEmptyCustomOptions_418) {
    ReporterSpec spec("console", {}, {}, {});
    EXPECT_TRUE(spec.customOptions().empty());
}

TEST_F(ReporterSpecTest_418, ConstructorWithAllParameters_418) {
    Optional<std::string> outputFile("result.xml");
    Optional<ColourMode> colour(ColourMode::None);
    std::map<std::string, std::string> options;
    options["verbose"] = "true";

    ReporterSpec spec("junit", outputFile, colour, options);

    EXPECT_EQ(spec.name(), "junit");
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "result.xml");
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::None);
    EXPECT_EQ(spec.customOptions().size(), 1u);
    EXPECT_EQ(spec.customOptions().at("verbose"), "true");
}

// Equality tests
TEST_F(ReporterSpecTest_418, EqualityWithIdenticalSpecs_418) {
    ReporterSpec spec1("console", {}, {}, {});
    ReporterSpec spec2("console", {}, {}, {});
    EXPECT_TRUE(spec1 == spec2);
    EXPECT_FALSE(spec1 != spec2);
}

TEST_F(ReporterSpecTest_418, InequalityWithDifferentNames_418) {
    ReporterSpec spec1("console", {}, {}, {});
    ReporterSpec spec2("xml", {}, {}, {});
    EXPECT_FALSE(spec1 == spec2);
    EXPECT_TRUE(spec1 != spec2);
}

TEST_F(ReporterSpecTest_418, InequalityWithDifferentOutputFiles_418) {
    Optional<std::string> file1("file1.txt");
    Optional<std::string> file2("file2.txt");
    ReporterSpec spec1("console", file1, {}, {});
    ReporterSpec spec2("console", file2, {}, {});
    EXPECT_FALSE(spec1 == spec2);
    EXPECT_TRUE(spec1 != spec2);
}

TEST_F(ReporterSpecTest_418, InequalityOneWithOutputFileOneWithout_418) {
    Optional<std::string> file("file.txt");
    ReporterSpec spec1("console", file, {}, {});
    ReporterSpec spec2("console", {}, {}, {});
    EXPECT_FALSE(spec1 == spec2);
    EXPECT_TRUE(spec1 != spec2);
}

TEST_F(ReporterSpecTest_418, InequalityWithDifferentColourModes_418) {
    Optional<ColourMode> colour1(ColourMode::ANSI);
    Optional<ColourMode> colour2(ColourMode::None);
    ReporterSpec spec1("console", {}, colour1, {});
    ReporterSpec spec2("console", {}, colour2, {});
    EXPECT_FALSE(spec1 == spec2);
    EXPECT_TRUE(spec1 != spec2);
}

TEST_F(ReporterSpecTest_418, InequalityWithDifferentCustomOptions_418) {
    std::map<std::string, std::string> opts1{{"key", "val1"}};
    std::map<std::string, std::string> opts2{{"key", "val2"}};
    ReporterSpec spec1("console", {}, {}, opts1);
    ReporterSpec spec2("console", {}, {}, opts2);
    EXPECT_FALSE(spec1 == spec2);
    EXPECT_TRUE(spec1 != spec2);
}

TEST_F(ReporterSpecTest_418, EqualityWithAllFieldsPopulated_418) {
    Optional<std::string> file("out.xml");
    Optional<ColourMode> colour(ColourMode::ANSI);
    std::map<std::string, std::string> opts{{"k", "v"}};

    ReporterSpec spec1("junit", file, colour, opts);
    ReporterSpec spec2("junit", file, colour, opts);
    EXPECT_TRUE(spec1 == spec2);
    EXPECT_FALSE(spec1 != spec2);
}

// Boundary: empty name
TEST_F(ReporterSpecTest_418, EmptyName_418) {
    ReporterSpec spec("", {}, {}, {});
    EXPECT_EQ(spec.name(), "");
}

// Boundary: empty output file string
TEST_F(ReporterSpecTest_418, EmptyOutputFileName_418) {
    Optional<std::string> emptyFile(std::string(""));
    ReporterSpec spec("console", emptyFile, {}, {});
    ASSERT_TRUE(spec.outputFile().has_value());
    EXPECT_EQ(*spec.outputFile(), "");
}

// Boundary: large custom options map
TEST_F(ReporterSpecTest_418, LargeCustomOptionsMap_418) {
    std::map<std::string, std::string> opts;
    for (int i = 0; i < 100; ++i) {
        opts["key" + std::to_string(i)] = "value" + std::to_string(i);
    }
    ReporterSpec spec("console", {}, {}, opts);
    EXPECT_EQ(spec.customOptions().size(), 100u);
    EXPECT_EQ(spec.customOptions().at("key50"), "value50");
}

// Test that two specs with different number of custom options are not equal
TEST_F(ReporterSpecTest_418, InequalityDifferentNumberOfCustomOptions_418) {
    std::map<std::string, std::string> opts1{{"a", "1"}};
    std::map<std::string, std::string> opts2{{"a", "1"}, {"b", "2"}};
    ReporterSpec spec1("console", {}, {}, opts1);
    ReporterSpec spec2("console", {}, {}, opts2);
    EXPECT_FALSE(spec1 == spec2);
    EXPECT_TRUE(spec1 != spec2);
}

// Reflexivity of equality
TEST_F(ReporterSpecTest_418, EqualityReflexive_418) {
    Optional<std::string> file("test.xml");
    Optional<ColourMode> colour(ColourMode::ANSI);
    std::map<std::string, std::string> opts{{"x", "y"}};
    ReporterSpec spec("name", file, colour, opts);
    EXPECT_TRUE(spec == spec);
    EXPECT_FALSE(spec != spec);
}

// ColourMode::Win32 if available (platform dependent, but testing with None as safe)
TEST_F(ReporterSpecTest_418, ColourModeNone_418) {
    Optional<ColourMode> colour(ColourMode::None);
    ReporterSpec spec("console", {}, colour, {});
    ASSERT_TRUE(spec.colourMode().has_value());
    EXPECT_EQ(*spec.colourMode(), ColourMode::None);
}

// Verify const correctness - accessors return const references
TEST_F(ReporterSpecTest_418, AccessorsReturnConstReferences_418) {
    std::map<std::string, std::string> opts{{"key", "val"}};
    Optional<std::string> file("file.txt");
    Optional<ColourMode> colour(ColourMode::ANSI);
    
    const ReporterSpec spec("reporter", file, colour, opts);
    
    const std::string& nameRef = spec.name();
    EXPECT_EQ(nameRef, "reporter");
    
    const Optional<std::string>& fileRef = spec.outputFile();
    ASSERT_TRUE(fileRef.has_value());
    EXPECT_EQ(*fileRef, "file.txt");
    
    const Optional<ColourMode>& colourRef = spec.colourMode();
    ASSERT_TRUE(colourRef.has_value());
    EXPECT_EQ(*colourRef, ColourMode::ANSI);
    
    const std::map<std::string, std::string>& optsRef = spec.customOptions();
    EXPECT_EQ(optsRef.size(), 1u);
}
