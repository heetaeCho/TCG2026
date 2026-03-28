#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_compact.hpp"

#include "catch_stringref.hpp"



using namespace Catch;



class MockStream : public IStream {

public:

    MOCK_METHOD1(write, void(const std::string&));

};



class CompactReporterTest_813 : public ::testing::Test {

protected:

    std::ostringstream realStream;

    testing::StrictMock<MockStream> mockStream;

    Detail::unique_ptr<IStream> streamPtr{ &mockStream };

    ReporterConfig config{ std::move(streamPtr), ColourMode::None, {} };

    CompactReporter reporter{ std::move(config) };



    void SetUp() override {

        EXPECT_CALL(mockStream, write(_)).WillRepeatedly(testing::Invoke([&](const std::string& str) {

            realStream << str;

        }));

    }

};



TEST_F(CompactReporterTest_813, NoMatchingTestCases_EmptyString_813) {

    StringRef emptySpec = "";

    reporter.noMatchingTestCases(emptySpec);

    EXPECT_EQ(realStream.str(), "No test cases matched ''\n");

}



TEST_F(CompactReporterTest_813, NoMatchingTestCases_NonEmptyString_813) {

    StringRef spec("example_spec");

    reporter.noMatchingTestCases(spec);

    EXPECT_EQ(realStream.str(), "No test cases matched 'example_spec'\n");

}



TEST_F(CompactReporterTest_813, NoMatchingTestCases_LongString_813) {

    std::string longSpec(1024, 'a'); // 1KB string

    StringRef spec(longSpec.c_str(), longSpec.size());

    reporter.noMatchingTestCases(spec);

    EXPECT_EQ(realStream.str(), "No test cases matched '" + longSpec + "'\n");

}
