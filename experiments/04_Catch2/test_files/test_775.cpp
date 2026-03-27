#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_automake.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class AutomakeReporterTest : public ::testing::Test {

protected:

    class MockStream : public IStream {

    public:

        MOCK_METHOD(void, write, (std::string const& text), (override));

        MOCK_METHOD(void, flush, (), (override));

    };



    AutomakeReporterTest() : m_config(ReporterConfig{Detail::unique_ptr<IStream>(new MockStream)}),

                             m_reporter(std::move(m_config)) {

        m_stream = static_cast<MockStream*>(m_reporter.m_wrapped_stream.get());

    }



protected:

    ReporterConfig m_config;

    AutomakeReporter m_reporter;

    MockStream* m_stream;

};



TEST_F(AutomakeReporterTest, TestCaseEnded_Skipped_775) {

    TestCaseStats stats = TestCaseStats{TestCaseInfo{"ClassName", {"TestName", ""}, SourceLineInfo{"file.cpp", 1}},

                                        Totals{{0, 0, 0, 1}, {1, 0, 0, 1}}, "", "", false};

    EXPECT_CALL(*m_stream, write(":test-result: SKIP TestName\n")).Times(1);

    m_reporter.testCaseEnded(stats);

}



TEST_F(AutomakeReporterTest, TestCaseEnded_AllPassed_775) {

    TestCaseStats stats = TestCaseStats{TestCaseInfo{"ClassName", {"TestName", ""}, SourceLineInfo{"file.cpp", 1}},

                                        Totals{{0, 1, 0, 0}, {1, 0, 0, 0}}, "", "", false};

    EXPECT_CALL(*m_stream, write(":test-result: PASS TestName\n")).Times(1);

    m_reporter.testCaseEnded(stats);

}



TEST_F(AutomakeReporterTest, TestCaseEnded_AllOk_775) {

    TestCaseStats stats = TestCaseStats{TestCaseInfo{"ClassName", {"TestName", ""}, SourceLineInfo{"file.cpp", 1}},

                                        Totals{{0, 0, 1, 0}, {1, 0, 0, 0}}, "", "", false};

    EXPECT_CALL(*m_stream, write(":test-result: XFAIL TestName\n")).Times(1);

    m_reporter.testCaseEnded(stats);

}



TEST_F(AutomakeReporterTest, TestCaseEnded_Failed_775) {

    TestCaseStats stats = TestCaseStats{TestCaseInfo{"ClassName", {"TestName", ""}, SourceLineInfo{"file.cpp", 1}},

                                        Totals{{0, 0, 0, 0}, {1, 0, 0, 0}}, "", "", false};

    EXPECT_CALL(*m_stream, write(":test-result: FAIL TestName\n")).Times(1);

    m_reporter.testCaseEnded(stats);

}



TEST_F(AutomakeReporterTest, SkipTest_775) {

    TestCaseInfo info = TestCaseInfo{"ClassName", {"TestName", ""}, SourceLineInfo{"file.cpp", 1}};

    EXPECT_CALL(*m_stream, write(":test-result: SKIP TestName\n")).Times(1);

    m_reporter.skipTest(info);

}
