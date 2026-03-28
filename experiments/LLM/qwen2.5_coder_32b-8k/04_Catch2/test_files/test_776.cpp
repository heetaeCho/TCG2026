#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_automake.hpp"

#include "catch_test_case_info.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::StrEq;



class AutomakeReporterTest : public ::testing::Test {

protected:

    class MockStream : public IStream {

    public:

        MOCK_METHOD(void, write, (std::string const&), (override));

    };



    MockStream mockStream;

    ReporterConfig config{Detail::unique_ptr<IStream>(&mockStream)};

    AutomakeReporter reporter{CATCH_MOVE(config)};



    TestCaseInfo createTestCaseInfo(const std::string& name) {

        NameAndTags nameAndTags{name, ""};

        SourceLineInfo lineInfo{"file.cpp", 10};

        return TestCaseInfo{"className", nameAndTags, lineInfo};

    }

};



TEST_F(AutomakeReporterTest_776, SkipTestWritesSkipMessage_776) {

    const std::string test_name = "SampleTest";

    TestCaseInfo testInfo = createTestCaseInfo(test_name);

    EXPECT_CALL(mockStream, write(StrEq(":test-result: SKIP SampleTest\n")));

    reporter.skipTest(testInfo);

}



TEST_F(AutomakeReporterTest_776, SkipTestHandlesEmptyName_776) {

    TestCaseInfo testInfo = createTestCaseInfo("");

    EXPECT_CALL(mockStream, write(StrEq(":test-result: SKIP \n")));

    reporter.skipTest(testInfo);

}
