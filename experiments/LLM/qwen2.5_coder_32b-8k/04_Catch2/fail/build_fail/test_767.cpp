#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_console.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"

#include "catch2/internal/catch_console_colour.hpp"

#include "catch2/reporters/catch_reporter_common_base.hpp"

#include "catch2/reporters/catch_reporter_streaming_base.hpp"



using namespace Catch;



class MockStream : public IStream {

public:

    MOCK_METHOD1(write, void(std::string const&));

};



class MockTablePrinter : public TablePrinter {

public:

    using TablePrinter::TablePrinter;

    MOCK_METHOD0(open, void());

    MOCK_METHOD0(close, void());

};



class MockColourImpl : public ColourImpl {

public:

    MockColourImpl(IStream* stream) : ColourImpl(stream) {}

    MOCK_METHOD1(guardColour, ColourGuard(Colour::Code));

};



class ConsoleReporterTest : public ::testing::Test {

protected:

    std::shared_ptr<MockStream> mock_stream;

    std::shared_ptr<MockTablePrinter> mock_table_printer;

    std::shared_ptr<MockColourImpl> mock_colour_impl;



    ReporterConfig config;

    ConsoleReporter reporter;



    void SetUp() override {

        mock_stream = std::make_shared<MockStream>();

        mock_table_printer = std::make_shared<MockTablePrinter>(*mock_stream, std::vector<ColumnInfo>());

        mock_colour_impl = std::make_shared<MockColourImpl>(mock_stream.get());



        config.fullConfig(new IConfig());

        config.takeStream(std::move(mock_stream));

        reporter = ConsoleReporter(std::move(config));



        reporter.m_tablePrinter = Detail::unique_ptr<TablePrinter>(mock_table_printer.release());

        reporter.m_colour = Detail::unique_ptr<ColourImpl>(mock_colour_impl.release());

    }

};



TEST_F(ConsoleReporterTest_767, SectionEnded_NoAssertionsInSection_767) {

    SectionInfo section_info(SourceLineInfo("file.cpp", 10), "section_name");

    SectionStats stats(std::move(section_info), Counts(), 1.5, true);



    EXPECT_CALL(*mock_table_printer, close());

    EXPECT_CALL(*mock_stream, write("\nNo assertions in section 'section_name'\n\n"));

    EXPECT_CALL(*mock_colour_impl, guardColour(Colour::ResultError));



    reporter.sectionEnded(stats);

}



TEST_F(ConsoleReporterTest_767, SectionEnded_NoAssertionsInTestCase_767) {

    SectionInfo section_info(SourceLineInfo("file.cpp", 10), "test_case_name");

    SectionStats stats(std::move(section_info), Counts(), 1.5, true);



    reporter.m_sectionStack.clear();



    EXPECT_CALL(*mock_table_printer, close());

    EXPECT_CALL(*mock_stream, write("\nNo assertions in test case 'test_case_name'\n\n"));

    EXPECT_CALL(*mock_colour_impl, guardColour(Colour::ResultError));



    reporter.sectionEnded(stats);

}



TEST_F(ConsoleReporterTest_767, SectionEnded_WithAssertions_767) {

    SectionInfo section_info(SourceLineInfo("file.cpp", 10), "section_name");

    SectionStats stats(std::move(section_info), Counts(1, 0, 0, 1, 0, 0), 1.5, false);



    EXPECT_CALL(*mock_table_printer, close());

    EXPECT_CALL(*mock_stream, write).Times(0);

    EXPECT_CALL(*mock_colour_impl, guardColour).Times(0);



    reporter.sectionEnded(stats);

}



TEST_F(ConsoleReporterTest_767, SectionEnded_DurationShown_767) {

    SectionInfo section_info(SourceLineInfo("file.cpp", 10), "section_name");

    SectionStats stats(std::move(section_info), Counts(), 1.5, false);



    EXPECT_CALL(*mock_table_printer, close());

    EXPECT_CALL(*mock_stream, write("1.5 s: section_name\n"));



    reporter.sectionEnded(stats);

}



TEST_F(ConsoleReporterTest_767, SectionEnded_HeaderReset_767) {

    SectionInfo section_info(SourceLineInfo("file.cpp", 10), "section_name");

    SectionStats stats(std::move(section_info), Counts(), 1.5, true);



    reporter.m_headerPrinted = true;



    EXPECT_CALL(*mock_table_printer, close());

    EXPECT_CALL(*mock_stream, write("\nNo assertions in section 'section_name'\n\n"));

    EXPECT_CALL(*mock_colour_impl, guardColour(Colour::ResultError));



    reporter.sectionEnded(stats);

    ASSERT_FALSE(reporter.m_headerPrinted);

}
