#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_console.hpp"

#include "catch2/catch_section_info.hpp"



using namespace Catch;

using ::testing::Mock;



class MockTablePrinter : public TablePrinter {

public:

    MOCK_METHOD(void, open, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



class ConsoleReporterTest : public ::testing::Test {

protected:

    void SetUp() override {

        auto mockTablePrinterPtr = std::make_unique<MockTablePrinter>();

        m_mockTablePrinter = mockTablePrinterPtr.get();

        m_consoleReporter = new ConsoleReporter({nullptr});

        m_consoleReporter->m_tablePrinter.reset(mockTablePrinterPtr.release());

    }



    void TearDown() override {

        delete m_consoleReporter;

    }



    MockTablePrinter* m_mockTablePrinter;

    ConsoleReporter* m_consoleReporter;

};



TEST_F(ConsoleReporterTest_766, SectionStarting_ClosesTablePrinter_766) {

    SectionInfo sectionInfo(SourceLineInfo("file", 1), "section");

    EXPECT_CALL(*m_mockTablePrinter, close()).Times(1);

    m_consoleReporter->sectionStarting(sectionInfo);

}



TEST_F(ConsoleReporterTest_766, SectionStarting_ResetsHeaderPrintedFlag_766) {

    SectionInfo sectionInfo(SourceLineInfo("file", 1), "section");

    m_consoleReporter->m_headerPrinted = true;

    m_consoleReporter->sectionStarting(sectionInfo);

    EXPECT_FALSE(m_consoleReporter->m_headerPrinted);

}



TEST_F(ConsoleReporterTest_766, SectionStarting_CallsBaseClassMethod_766) {

    SectionInfo sectionInfo(SourceLineInfo("file", 1), "section");

    EXPECT_CALL(*static_cast<StreamingReporterBase*>(m_consoleReporter), sectionStarting(sectionInfo)).Times(1);

    m_consoleReporter->sectionStarting(sectionInfo);

}
