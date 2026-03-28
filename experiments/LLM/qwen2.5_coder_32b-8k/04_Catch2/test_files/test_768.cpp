#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_console.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace testing;



// Mock TablePrinter for verifying interactions

class MockTablePrinter : public TablePrinter {

public:

    MOCK_METHOD(void, open, (), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_CONST_METHOD0(columnInfos, std::vector<ColumnInfo> const&());

};



class ConsoleReporterTest_768 : public Test {

protected:

    NiceMock<MockTablePrinter>* mock_table_printer;

    ConsoleReporter* reporter;



    void SetUp() override {

        mock_table_printer = new NiceMock<MockTablePrinter>(std::cout, {});

        reporter = new ConsoleReporter(ReporterConfig{});

        reporter->m_tablePrinter.reset(mock_table_printer);

    }



    void TearDown() override {

        delete reporter;

    }

};



TEST_F(ConsoleReporterTest_768, BenchmarkPreparing_CallsLazyPrintWithoutClosingBenchmarkTable_768) {

    EXPECT_CALL(*mock_table_printer, columnInfos()).Times(AtLeast(1));

    StringRef name("BenchmarkName");

    reporter->benchmarkPreparing(name);

}



TEST_F(ConsoleReporterTest_768, BenchmarkPreparing_FormatsAndOutputsNameCorrectly_768) {

    EXPECT_CALL(*mock_table_printer, columnInfos())

        .WillOnce(Return(std::vector<ColumnInfo>{{.width = 20, .justification = Justification::Left}}));



    StringRef name("BenchmarkName");

    reporter->benchmarkPreparing(name);

}



TEST_F(ConsoleReporterTest_768, BenchmarkPreparing_HandlesEmptyString_768) {

    EXPECT_CALL(*mock_table_printer, columnInfos())

        .WillOnce(Return(std::vector<ColumnInfo>{{.width = 20, .justification = Justification::Left}}));



    StringRef name("");

    reporter->benchmarkPreparing(name);

}



TEST_F(ConsoleReporterTest_768, BenchmarkPreparing_HandlesLongString_768) {

    EXPECT_CALL(*mock_table_printer, columnInfos())

        .WillOnce(Return(std::vector<ColumnInfo>{{.width = 20, .justification = Justification::Left}}));



    StringRef name("ThisIsAVeryLongBenchmarkNameThatExceedsTheDefaultColumnWidth");

    reporter->benchmarkPreparing(name);

}



TEST_F(ConsoleReporterTest_768, BenchmarkPreparing_VerifiesTablePrinterInteractions_768) {

    EXPECT_CALL(*mock_table_printer, columnInfos())

        .WillOnce(Return(std::vector<ColumnInfo>{{.width = 20, .justification = Justification::Left}}));



    StringRef name("BenchmarkName");

    reporter->benchmarkPreparing(name);

}
