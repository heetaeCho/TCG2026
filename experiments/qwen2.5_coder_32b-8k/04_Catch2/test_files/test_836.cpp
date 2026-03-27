#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_interfaces_config.hpp"

#include "catch_test_run_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



// Mock IConfig for testing XmlReporter

class MockIConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(name, StringRef());

    MOCK_CONST_METHOD0(rngSeed, uint32_t());

    MOCK_CONST_METHOD0(testSpec, const TestSpec&());

};



TEST_F(XmlReporterTest_836, TestRunStarting_WritesCorrectAttributes_836) {

    std::ostringstream oss;

    XmlWriter xmlWriter(oss);

    NiceMock<MockIConfig> configMock;



    EXPECT_CALL(configMock, name()).WillOnce(::testing::Return("SampleName"_sr));

    EXPECT_CALL(configMock, rngSeed()).WillOnce(::testing::Return(12345u));



    TestSpec testSpec;

    ON_CALL(configMock, testSpec()).WillByDefault(::testing::ReturnRef(testSpec));



    XmlReporter reporter({&configMock});

    reporter.m_xml = xmlWriter;



    TestRunInfo testRunInfo("SampleTest"_sr);

    reporter.testRunStarting(testRunInfo);



    std::string expectedOutput = R"(<Catch2TestRun name="SampleName" rng-seed="12345" xml-format-version="3" catch2-version=")";

    expectedOutput += libraryVersion();

    expectedOutput += "\"></Catch2TestRun>";

    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(expectedOutput));

}



TEST_F(XmlReporterTest_836, TestRunStarting_WritesStylesheetRefIfPresent_836) {

    std::ostringstream oss;

    XmlWriter xmlWriter(oss);

    NiceMock<MockIConfig> configMock;



    EXPECT_CALL(configMock, name()).WillOnce(::testing::Return("SampleName"_sr));

    EXPECT_CALL(configMock, rngSeed()).WillOnce(::testing::Return(12345u));



    TestSpec testSpec;

    ON_CALL(configMock, testSpec()).WillByDefault(::testing::ReturnRef(testSpec));



    XmlReporter reporter({&configMock});

    reporter.m_xml = xmlWriter;



    reporter.getStylesheetRef = []() { return "http://example.com/stylesheet.xsl"; };



    TestRunInfo testRunInfo("SampleTest"_sr);

    reporter.testRunStarting(testRunInfo);



    std::string expectedOutput = R"(<?xml-stylesheet type="text/xsl" href="http://example.com/stylesheet.xsl"?><Catch2TestRun name="SampleName" rng-seed="12345" xml-format-version="3" catch2-version=")";

    expectedOutput += libraryVersion();

    expectedOutput += "\"></Catch2TestRun>";

    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(expectedOutput));

}



TEST_F(XmlReporterTest_836, TestRunStarting_IncludesFiltersIfPresent_836) {

    std::ostringstream oss;

    XmlWriter xmlWriter(oss);

    NiceMock<MockIConfig> configMock;



    EXPECT_CALL(configMock, name()).WillOnce(::testing::Return("SampleName"_sr));

    EXPECT_CALL(configMock, rngSeed()).WillOnce(::testing::Return(12345u));



    TestSpec testSpec;

    ON_CALL(testSpec, hasFilters()).WillByDefault(::testing::Return(true));

    ON_CALL(testSpec, serializeTo(_)).WillByDefault([](std::ostream & out) { out << "some_filter"; });

    ON_CALL(configMock, testSpec()).WillByDefault(::testing::ReturnRef(testSpec));



    XmlReporter reporter({&configMock});

    reporter.m_xml = xmlWriter;



    TestRunInfo testRunInfo("SampleTest"_sr);

    reporter.testRunStarting(testRunInfo);



    std::string expectedOutput = R"(<Catch2TestRun name="SampleName" rng-seed="12345" xml-format-version="3" catch2-version=")";

    expectedOutput += libraryVersion();

    expectedOutput += R"(" filters="some_filter"></Catch2TestRun>)";

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(XmlReporterTest_836, TestRunStarting_NoFiltersIfNotPresent_836) {

    std::ostringstream oss;

    XmlWriter xmlWriter(oss);

    NiceMock<MockIConfig> configMock;



    EXPECT_CALL(configMock, name()).WillOnce(::testing::Return("SampleName"_sr));

    EXPECT_CALL(configMock, rngSeed()).WillOnce(::testing::Return(12345u));



    TestSpec testSpec;

    ON_CALL(testSpec, hasFilters()).WillByDefault(::testing::Return(false));

    ON_CALL(configMock, testSpec()).WillByDefault(::testing::ReturnRef(testSpec));



    XmlReporter reporter({&configMock});

    reporter.m_xml = xmlWriter;



    TestRunInfo testRunInfo("SampleTest"_sr);

    reporter.testRunStarting(testRunInfo);



    std::string expectedOutput = R"(<Catch2TestRun name="SampleName" rng-seed="12345" xml-format-version="3" catch2-version=")";

    expectedOutput += libraryVersion();

    expectedOutput += "\"></Catch2TestRun>";

    EXPECT_EQ(oss.str(), expectedOutput);

}
