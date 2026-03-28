#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>

#include "catch2/reporters/catch_reporter_tap.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_stream.hpp"
#include "catch2/catch_reporter_config.hpp"
#include "catch2/internal/catch_istream.hpp"

using namespace Catch;

namespace {

// A helper IStream implementation that wraps a stringstream for testing
class StringIStream : public Catch::IStream {
    std::ostringstream m_oss;
public:
    std::ostream& stream() override { return m_oss; }
    std::string str() const { return m_oss.str(); }
};

// Helper to create a TAPReporter with a captured output stream
struct TAPReporterTestFixture {
    StringIStream* rawStreamPtr = nullptr;
    std::unique_ptr<TAPReporter> reporter;

    TAPReporterTestFixture() {
        // We need to build a ReporterConfig. This requires creating the necessary
        // Catch2 infrastructure objects.
    }
};

} // anonymous namespace

class TAPReporterTest_746 : public ::testing::Test {
protected:
    std::ostringstream oss;
    
    // We'll try to create a TAPReporter through the Catch2 config mechanism
    // Since construction is complex, we use Catch2's own helpers where possible.
    
    struct TestStream : public Catch::IStream {
        std::ostringstream oss;
        std::ostream& stream() override { return oss; }
    };
    
    std::unique_ptr<TAPReporter> createReporter() {
        auto testStream = Catch::Detail::make_unique<TestStream>();
        streamPtr = testStream.get();
        
        // Create a minimal config
        const char* argv[] = {"test"};
        Catch::ConfigData configData;
        auto config = std::make_shared<Catch::Config>(configData);
        
        auto reporterConfig = Catch::ReporterConfig(
            config.get(),
            std::move(testStream),
            Catch::ColourMode::None,
            std::map<std::string, std::string>{}
        );
        
        savedConfig = config;
        return std::make_unique<TAPReporter>(std::move(reporterConfig));
    }
    
    TestStream* streamPtr = nullptr;
    std::shared_ptr<Catch::Config> savedConfig;
};

TEST_F(TAPReporterTest_746, NoMatchingTestCases_OutputsCorrectFormat_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("SomeTestSpec");
    
    std::string output = streamPtr->oss.str();
    EXPECT_NE(output.find("No test cases matched"), std::string::npos);
    EXPECT_NE(output.find("SomeTestSpec"), std::string::npos);
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_ContainsSpecName_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("MySpecialTest");
    
    std::string output = streamPtr->oss.str();
    EXPECT_NE(output.find("MySpecialTest"), std::string::npos);
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_StartsWithHash_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("AnySpec");
    
    std::string output = streamPtr->oss.str();
    // TAP comments start with #
    EXPECT_EQ(output.substr(0, 1), "#");
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_EmptySpec_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("");
    
    std::string output = streamPtr->oss.str();
    EXPECT_NE(output.find("No test cases matched"), std::string::npos);
    EXPECT_NE(output.find("''"), std::string::npos);
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_SpecWithSpecialCharacters_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("[tag1][tag2]");
    
    std::string output = streamPtr->oss.str();
    EXPECT_NE(output.find("[tag1][tag2]"), std::string::npos);
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_EndsWithNewline_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("test");
    
    std::string output = streamPtr->oss.str();
    ASSERT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_MultipleCallsAccumulate_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("Spec1");
    reporter->noMatchingTestCases("Spec2");
    
    std::string output = streamPtr->oss.str();
    EXPECT_NE(output.find("Spec1"), std::string::npos);
    EXPECT_NE(output.find("Spec2"), std::string::npos);
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_ExactFormat_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("foo");
    
    std::string output = streamPtr->oss.str();
    EXPECT_EQ(output, "# No test cases matched 'foo'\n");
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_LongSpecName_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    std::string longSpec(1000, 'x');
    reporter->noMatchingTestCases(StringRef(longSpec));
    
    std::string output = streamPtr->oss.str();
    EXPECT_NE(output.find(longSpec), std::string::npos);
}

TEST_F(TAPReporterTest_746, NoMatchingTestCases_SpecWithSpaces_746) {
    auto reporter = createReporter();
    ASSERT_NE(reporter, nullptr);
    
    reporter->noMatchingTestCases("test with spaces");
    
    std::string output = streamPtr->oss.str();
    EXPECT_EQ(output, "# No test cases matched 'test with spaces'\n");
}

TEST_F(TAPReporterTest_746, GetDescription_ReturnsNonEmpty_746) {
    std::string desc = TAPReporter::getDescription();
    EXPECT_FALSE(desc.empty());
}
