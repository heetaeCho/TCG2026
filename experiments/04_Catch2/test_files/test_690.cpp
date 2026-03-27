#include <gtest/gtest.h>

#include <catch2/internal/catch_reporter_spec_parser.hpp>



using namespace Catch;



TEST_F(ReporterSpecTest_690, EqualitySameValues_690) {

    ReporterSpec spec1("name", Optional<std::string>("file"), Optional<ColourMode>(ColourMode::Auto), {{"key", "value"}});

    ReporterSpec spec2("name", Optional<std::string>("file"), Optional<ColourMode>(ColourMode::Auto), {{"key", "value"}});

    EXPECT_TRUE(spec1 == spec2);

}



TEST_F(ReporterSpecTest_690, EqualityDifferentName_690) {

    ReporterSpec spec1("name1", Optional<std::string>("file"), Optional<ColourMode>(ColourMode::Auto), {{"key", "value"}});

    ReporterSpec spec2("name2", Optional<std::string>("file"), Optional<ColourMode>(ColourMode::Auto), {{"key", "value"}});

    EXPECT_FALSE(spec1 == spec2);

}



TEST_F(ReporterSpecTest_690, EqualityDifferentOutputFile_690) {

    ReporterSpec spec1("name", Optional<std::string>("file1"), Optional<ColourMode>(ColourMode::Auto), {{"key", "value"}});

    ReporterSpec spec2("name", Optional<std::string>("file2"), Optional<ColourMode>(ColourMode::Auto), {{"key", "value"}});

    EXPECT_FALSE(spec1 == spec2);

}



TEST_F(ReporterSpecTest_690, EqualityDifferentColourMode_690) {

    ReporterSpec spec1("name", Optional<std::string>("file"), Optional<ColourMode>(ColourMode::On), {{"key", "value"}});

    ReporterSpec spec2("name", Optional<std::string>("file"), Optional<ColourMode>(ColourMode::Off), {{"key", "value"}});

    EXPECT_FALSE(spec1 == spec2);

}



TEST_F(ReporterSpecTest_690, EqualityDifferentCustomOptions_690) {

    ReporterSpec spec1("name", Optional<std::string>("file"), Optional<ColourMode>(ColourMode::Auto), {{"key1", "value"}});

    ReporterSpec spec2("name", Optional<std::string>("file"), Optional<ColourMode>(ColourMode::Auto), {{"key2", "value"}});

    EXPECT_FALSE(spec1 == spec2);

}



TEST_F(ReporterSpecTest_690, AccessorName_690) {

    ReporterSpec spec("test_name", Optional<std::string>(), Optional<ColourMode>(), {});

    EXPECT_EQ(spec.name(), "test_name");

}



TEST_F(ReporterSpecTest_690, AccessorOutputFilePresent_690) {

    ReporterSpec spec("name", Optional<std::string>("output"), Optional<ColourMode>(), {});

    EXPECT_TRUE(spec.outputFile().has_value());

    EXPECT_EQ(*spec.outputFile(), "output");

}



TEST_F(ReporterSpecTest_690, AccessorOutputFileNotPresent_690) {

    ReporterSpec spec("name", Optional<std::string>(), Optional<ColourMode>(), {});

    EXPECT_FALSE(spec.outputFile().has_value());

}



TEST_F(ReporterSpecTest_690, AccessorColourModePresent_690) {

    ReporterSpec spec("name", Optional<std::string>(), Optional<ColourMode>(ColourMode::On), {});

    EXPECT_TRUE(spec.colourMode().has_value());

    EXPECT_EQ(*spec.colourMode(), ColourMode::On);

}



TEST_F(ReporterSpecTest_690, AccessorColourModeNotPresent_690) {

    ReporterSpec spec("name", Optional<std::string>(), Optional<ColourMode>(), {});

    EXPECT_FALSE(spec.colourMode().has_value());

}



TEST_F(ReporterSpecTest_690, AccessorCustomOptionsNotEmpty_690) {

    std::map<std::string, std::string> options = {{"key1", "value1"}, {"key2", "value2"}};

    ReporterSpec spec("name", Optional<std::string>(), Optional<ColourMode>(), options);

    EXPECT_EQ(spec.customOptions(), options);

}



TEST_F(ReporterSpecTest_690, AccessorCustomOptionsEmpty_690) {

    ReporterSpec spec("name", Optional<std::string>(), Optional<ColourMode>(), {});

    EXPECT_TRUE(spec.customOptions().empty());

}
