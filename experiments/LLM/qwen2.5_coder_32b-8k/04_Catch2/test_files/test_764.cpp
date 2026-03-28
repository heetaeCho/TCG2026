#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_console.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using ::testing::HasSubstr;



class ConsoleReporterTest_764 : public ::testing::Test {

protected:

    class MockStream {

    public:

        MOCK_METHOD(std::ostream&, stream, (), (const));

    };



    class ReporterConfigMock : public ReporterConfig {

    public:

        ReporterConfigMock() : ReporterConfig(ReporterConfigData{}) {

            m_stream = std::make_unique<MockStream>();

        }

        std::unique_ptr<IStream>& takeStream() override { return m_stream; }



        std::unique_ptr<MockStream> m_stream;

    };



    ConsoleReporterTest_764() : configMock(), reporter(std::move(configMock)) {}



    ReporterConfigMock configMock;

    ConsoleReporter reporter;

};



TEST_F(ConsoleReporterTest_764, ReportInvalidTestSpec_NormalOperation_764) {

    StringRef arg("test_spec");

    EXPECT_CALL(*configMock.m_stream, stream())

        .WillOnce(::testing::ReturnRef(std::cout));

    

    testing::internal::CaptureStdout();

    reporter.reportInvalidTestSpec(arg);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_THAT(output, HasSubstr("Invalid Filter: test_spec\n"));

}



TEST_F(ConsoleReporterTest_764, ReportInvalidTestSpec_EmptyString_764) {

    StringRef arg("");

    EXPECT_CALL(*configMock.m_stream, stream())

        .WillOnce(::testing::ReturnRef(std::cout));



    testing::internal::CaptureStdout();

    reporter.reportInvalidTestSpec(arg);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_THAT(output, HasSubstr("Invalid Filter: \n"));

}



TEST_F(ConsoleReporterTest_764, ReportInvalidTestSpec_SpecialCharacters_764) {

    StringRef arg("!@#$%^&*()");

    EXPECT_CALL(*configMock.m_stream, stream())

        .WillOnce(::testing::ReturnRef(std::cout));



    testing::internal::CaptureStdout();

    reporter.reportInvalidTestSpec(arg);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_THAT(output, HasSubstr("Invalid Filter: !@#$%^&*()\n"));

}
