#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_console.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;



class MockTablePrinter : public TablePrinter {

public:

    MOCK_METHOD(void, open, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



class ConsoleReporterTest_772 : public ::testing::Test {

protected:

    ReporterConfig config;

    std::unique_ptr<MockTablePrinter> mockTablePrinter = std::make_unique<MockTablePrinter>();

    NiceMock<MockTablePrinter>* mockTablePrinterRawPtr = mockTablePrinter.get();

    ConsoleReporter reporter{std::move(config)};



    void SetUp() override {

        reporter.m_tablePrinter.reset(mockTablePrinter.release());

    }



    TestCaseStats createTestCaseStats() const {

        TestCaseInfo testInfo("test_case_name", "filename.cpp", 10);

        Totals totals{};

        std::string stdOut = "";

        std::string stdErr = "";

        bool aborting = false;

        return TestCaseStats{testInfo, totals, std::move(stdOut), std::move(stdErr), aborting};

    }

};



TEST_F(ConsoleReporterTest_772, testCaseEnded_ClosesTablePrinter_772) {

    TestCaseStats testCaseStats = createTestCaseStats();

    EXPECT_CALL(*mockTablePrinterRawPtr, close());

    reporter.testCaseEnded(testCaseStats);

}



TEST_F(ConsoleReporterTest_772, testCaseEnded_ResetsHeaderPrintedFlag_772) {

    TestCaseStats testCaseStats = createTestCaseStats();

    reporter.m_headerPrinted = true;

    reporter.testCaseEnded(testCaseStats);

    EXPECT_FALSE(reporter.m_headerPrinted);

}
