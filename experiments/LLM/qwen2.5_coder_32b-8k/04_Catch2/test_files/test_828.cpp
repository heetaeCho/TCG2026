#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_sonarqube.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_xmlwriter.hpp"



using namespace Catch;



class MockXmlWriter : public XmlWriter {

public:

    MockXmlWriter(std::ostream &os) : XmlWriter(os) {}



    MOCK_METHOD1(startElement, XmlWriter&(const std::string& name, XmlFormatting fmt));

    MOCK_METHOD1(endElement, XmlWriter&(XmlFormatting fmt));

    MOCK_METHOD2(writeAttribute, XmlWriter&(StringRef name, StringRef attribute));

};



class SonarQubeReporterTest_828 : public ::testing::Test {

protected:

    void SetUp() override {

        os.str("");

        xmlWriter = std::make_unique<MockXmlWriter>(os);

        reporter = std::make_unique<SonarQubeReporter>(std::move(config));

        reporter->xml = *xmlWriter;

    }



    ReporterConfig config;

    std::ostringstream os;

    std::unique_ptr<MockXmlWriter> xmlWriter;

    std::unique_ptr<SonarQubeReporter> reporter;

};



TEST_F(SonarQubeReporterTest_828, WriteTestFile_StartsAndEndsFileElement_828) {

    StringRef filename("test_file.cpp");

    std::vector<TestCaseNode const*> testCaseNodes;



    EXPECT_CALL(*xmlWriter, startElement("file", XmlFormatting::None)).Times(1);

    EXPECT_CALL(*xmlWriter, writeAttribute("path"_sr, "test_file.cpp")).Times(1);

    EXPECT_CALL(*xmlWriter, endElement(XmlFormatting::NewlineAll)).Times(1);



    reporter->writeTestFile(filename, testCaseNodes);

}



TEST_F(SonarQubeReporterTest_828, WriteTestFile_WritesFilenameAttribute_828) {

    StringRef filename("test_file.cpp");

    std::vector<TestCaseNode const*> testCaseNodes;



    EXPECT_CALL(*xmlWriter, writeAttribute("path"_sr, "test_file.cpp")).Times(1);



    reporter->writeTestFile(filename, testCaseNodes);

}



TEST_F(SonarQubeReporterTest_828, WriteTestFile_HandlesEmptyFilename_828) {

    StringRef filename("");

    std::vector<TestCaseNode const*> testCaseNodes;



    EXPECT_CALL(*xmlWriter, writeAttribute("path"_sr, "")).Times(1);



    reporter->writeTestFile(filename, testCaseNodes);

}



TEST_F(SonarQubeReporterTest_828, WriteTestFile_CallsWriteTestCaseForEachTestCaseNode_828) {

    StringRef filename("test_file.cpp");

    TestCaseNode testCaseNode;

    std::vector<TestCaseNode const*> testCaseNodes = {&testCaseNode};



    EXPECT_CALL(*xmlWriter, writeAttribute("path"_sr, "test_file.cpp")).Times(1);

    EXPECT_CALL(*reporter, writeTestCase(testCaseNode)).Times(1);



    reporter->writeTestFile(filename, testCaseNodes);

}



TEST_F(SonarQubeReporterTest_828, WriteTestFile_HandlesEmptyTestCaseNodesVector_828) {

    StringRef filename("test_file.cpp");

    std::vector<TestCaseNode const*> testCaseNodes;



    EXPECT_CALL(*xmlWriter, writeAttribute("path"_sr, "test_file.cpp")).Times(1);

    EXPECT_CALL(*reporter, writeTestCase(::testing::_)).Times(0);



    reporter->writeTestFile(filename, testCaseNodes);

}
