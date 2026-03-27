#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include "catch2/catch_section_info.hpp"



using namespace Catch;



class JsonReporterTest_870 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming ReporterConfig is default constructible for test purposes

        reporter = std::make_unique<JsonReporter>(ReporterConfig{});

    }



    std::unique_ptr<JsonReporter> reporter;

    SectionInfo sectionInfo { SourceLineInfo{"file.cpp", 123}, "TestSection" };

};



TEST_F(JsonReporterTest_870, SectionStarting_WritesCorrectKind_870) {

    // Arrange

    std::stringstream ss;

    JsonValueWriter writer{ss};

    reporter->m_objectWriters.push(writer.writeObject());



    // Act

    reporter->sectionStarting(sectionInfo);



    // Assert

    EXPECT_TRUE(ss.str().find("\"kind\":\"section\"") != std::string::npos);

}



TEST_F(JsonReporterTest_870, SectionStarting_WritesCorrectName_870) {

    // Arrange

    std::stringstream ss;

    JsonValueWriter writer{ss};

    reporter->m_objectWriters.push(writer.writeObject());



    // Act

    reporter->sectionStarting(sectionInfo);



    // Assert

    EXPECT_TRUE(ss.str().find("\"name\":\"TestSection\"") != std::string::npos);

}



TEST_F(JsonReporterTest_870, SectionStarting_WritesSourceInfo_870) {

    // Arrange

    std::stringstream ss;

    JsonValueWriter writer{ss};

    reporter->m_objectWriters.push(writer.writeObject());



    // Act

    reporter->sectionStarting(sectionInfo);



    // Assert

    EXPECT_TRUE(ss.str().find("\"line\":123") != std::string::npos);

}



TEST_F(JsonReporterTest_870, SectionStarting_StartsPathArray_870) {

    // Arrange

    std::stringstream ss;

    JsonValueWriter writer{ss};

    reporter->m_objectWriters.push(writer.writeObject());



    // Act

    reporter->sectionStarting(sectionInfo);



    // Assert

    EXPECT_TRUE(ss.str().find("\"path\":") != std::string::npos);

}



TEST_F(JsonReporterTest_870, SectionStarting_AssertionOnWrongWriterState_870) {

    // Arrange & Act & Assert

    EXPECT_DEATH(reporter->sectionStarting(sectionInfo), "Section should always start inside an object");

}
