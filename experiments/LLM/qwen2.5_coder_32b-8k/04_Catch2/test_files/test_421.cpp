#include <gtest/gtest.h>

#include "catch2/internal/catch_reporter_spec_parser.hpp"



using namespace Catch;



class ReporterSpecTest_421 : public ::testing::Test {

protected:

    Optional<ColourMode> m_colourMode;

    ReporterSpec spec;



    void SetUp() override {

        m_colourMode = ColourMode{Colour::Auto};

        spec = ReporterSpec{"default", {}, m_colourMode, {}};

    }

};



TEST_F(ReporterSpecTest_421, ConstructorInitializesCorrectly_421) {

    EXPECT_EQ(spec.name(), "default");

    EXPECT_TRUE(!spec.outputFile().has_value());

    EXPECT_EQ(*spec.colourMode(), Colour::Auto);

}



TEST_F(ReporterSpecTest_421, ConstructorWithOutputFileName_421) {

    Optional<std::string> outputFileName = "output.txt";

    ReporterSpec specWithOutput{"default", outputFileName, m_colourMode, {}};

    EXPECT_EQ(*specWithOutput.outputFile(), "output.txt");

}



TEST_F(ReporterSpecTest_421, ConstructorWithoutColourMode_421) {

    Optional<ColourMode> noColourMode;

    ReporterSpec specWithoutColour{"default", {}, noColourMode, {}};

    EXPECT_FALSE(specWithoutColour.colourMode().has_value());

}



TEST_F(ReporterSpecTest_421, CustomOptionsConstructor_421) {

    std::map<std::string, std::string> customOptions = {{"option1", "value1"}, {"option2", "value2"}};

    ReporterSpec specWithCustomOptions{"default", {}, m_colourMode, customOptions};

    EXPECT_EQ(specWithCustomOptions.customOptions(), customOptions);

}



TEST_F(ReporterSpecTest_421, EqualityOperatorSameObject_421) {

    ReporterSpec anotherSpec = spec;

    EXPECT_TRUE(anotherSpec == spec);

}



TEST_F(ReporterSpecTest_421, EqualityOperatorDifferentName_421) {

    ReporterSpec differentSpec{"different", {}, m_colourMode, {}};

    EXPECT_FALSE(differentSpec == spec);

}



TEST_F(ReporterSpecTest_421, EqualityOperatorDifferentColourMode_421) {

    Optional<ColourMode> differentColour = ColourMode{Colour::None};

    ReporterSpec differentSpec{"default", {}, differentColour, {}};

    EXPECT_FALSE(differentSpec == spec);

}



TEST_F(ReporterSpecTest_421, EqualityOperatorDifferentCustomOptions_421) {

    std::map<std::string, std::string> customOptions = {{"option1", "value1"}};

    ReporterSpec differentSpec{"default", {}, m_colourMode, customOptions};

    EXPECT_FALSE(differentSpec == spec);

}
