#include "catch2/internal/catch_test_case_registry_impl.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_test_case_info_hasher.hpp"
#include "catch2/interfaces/catch_interfaces_testcase.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>

// Mock ITestInvoker
class MockTestInvoker : public Catch::ITestInvoker {
public:
    void invoke() const override {}
};

// Mock IConfig for getAllTestsSorted
class MockConfig : public Catch::IConfig {
public:
    bool allowThrows() const override { return true; }
    std::ostream& stream() const override { static std::ostream s(nullptr); return s; }
    Catch::StringRef name() const override { return "mock"_catch_sr; }
    bool includeSuccessfulResults() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    int abortAfter() const override { return 0; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::Never; }
    double minDuration() const override { return 0.0; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::None; }
    unsigned int rngSeed() const override { return 0; }
    bool shouldDebugBreak() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    unsigned int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    std::vector<std::string> const& getSectionsToRun() const override { static std::vector<std::string> v; return v; }
    Catch::TestSpec const& testSpec() const override { static Catch::TestSpec ts; return ts; }
    std::vector<Catch::ReporterSpec> const& getReporterSpecs() const override { static std::vector<Catch::ReporterSpec> v; return v; }
    std::vector<Catch::ProcessedReporterSpec> const& getProcessedReporterSpecs() const override { static std::vector<Catch::ProcessedReporterSpec> v; return v; }
    Catch::IStream const* getReporterOutputStream(std::size_t) const override { return nullptr; }
};

static Catch::Detail::unique_ptr<Catch::TestCaseInfo> makeTestInfo(const std::string& name, const std::string& className = "") {
    Catch::SourceLineInfo lineInfo("test_file.cpp", 1);
    std::vector<Catch::Tag> tags;
    return Catch::Detail::make_unique<Catch::TestCaseInfo>(
        std::string(className),
        Catch::NameAndTags{name.c_str(), ""}, 
        lineInfo
    );
}

static Catch::Detail::unique_ptr<Catch::ITestInvoker> makeInvoker() {
    return Catch::Detail::make_unique<MockTestInvoker>();
}

class TestRegistryTest_1018 : public ::testing::Test {
protected:
    Catch::TestRegistry registry;
};

TEST_F(TestRegistryTest_1018, InitiallyEmpty_1018) {
    auto const& tests = registry.getAllTests();
    EXPECT_TRUE(tests.empty());
}

TEST_F(TestRegistryTest_1018, InitiallyEmptyInfos_1018) {
    auto const& infos = registry.getAllInfos();
    EXPECT_TRUE(infos.empty());
}

TEST_F(TestRegistryTest_1018, RegisterSingleTest_1018) {
    registry.registerTest(makeTestInfo("TestOne"), makeInvoker());
    
    auto const& tests = registry.getAllTests();
    EXPECT_EQ(tests.size(), 1u);
}

TEST_F(TestRegistryTest_1018, RegisterSingleTestInfoAvailable_1018) {
    registry.registerTest(makeTestInfo("TestOne"), makeInvoker());
    
    auto const& infos = registry.getAllInfos();
    EXPECT_EQ(infos.size(), 1u);
    EXPECT_EQ(infos[0]->name, "TestOne");
}

TEST_F(TestRegistryTest_1018, RegisterMultipleTests_1018) {
    registry.registerTest(makeTestInfo("TestOne"), makeInvoker());
    registry.registerTest(makeTestInfo("TestTwo"), makeInvoker());
    registry.registerTest(makeTestInfo("TestThree"), makeInvoker());
    
    auto const& tests = registry.getAllTests();
    EXPECT_EQ(tests.size(), 3u);
}

TEST_F(TestRegistryTest_1018, RegisterMultipleTestsInfosMatch_1018) {
    registry.registerTest(makeTestInfo("TestOne"), makeInvoker());
    registry.registerTest(makeTestInfo("TestTwo"), makeInvoker());
    
    auto const& infos = registry.getAllInfos();
    EXPECT_EQ(infos.size(), 2u);
    EXPECT_EQ(infos[0]->name, "TestOne");
    EXPECT_EQ(infos[1]->name, "TestTwo");
}

TEST_F(TestRegistryTest_1018, GetAllTestsAndInfosSameCount_1018) {
    registry.registerTest(makeTestInfo("TestA"), makeInvoker());
    registry.registerTest(makeTestInfo("TestB"), makeInvoker());
    
    EXPECT_EQ(registry.getAllTests().size(), registry.getAllInfos().size());
}

TEST_F(TestRegistryTest_1018, GetAllTestsSortedDeclaredOrder_1018) {
    registry.registerTest(makeTestInfo("Zebra"), makeInvoker());
    registry.registerTest(makeTestInfo("Apple"), makeInvoker());
    registry.registerTest(makeTestInfo("Mango"), makeInvoker());
    
    MockConfig config;
    auto const& sorted = registry.getAllTestsSorted(config);
    EXPECT_EQ(sorted.size(), 3u);
}

TEST_F(TestRegistryTest_1018, GetAllTestsSortedReturnsNonEmpty_1018) {
    registry.registerTest(makeTestInfo("TestX"), makeInvoker());
    
    MockConfig config;
    auto const& sorted = registry.getAllTestsSorted(config);
    EXPECT_EQ(sorted.size(), 1u);
}

TEST_F(TestRegistryTest_1018, GetAllTestsSortedEmptyRegistry_1018) {
    MockConfig config;
    auto const& sorted = registry.getAllTestsSorted(config);
    EXPECT_TRUE(sorted.empty());
}

TEST_F(TestRegistryTest_1018, TestHandleHasCorrectInfo_1018) {
    registry.registerTest(makeTestInfo("SpecificTest"), makeInvoker());
    
    auto const& tests = registry.getAllTests();
    ASSERT_EQ(tests.size(), 1u);
    EXPECT_EQ(tests[0].getTestCaseInfo().name, "SpecificTest");
}

TEST_F(TestRegistryTest_1018, RegisterManyTests_1018) {
    for (int i = 0; i < 100; ++i) {
        registry.registerTest(makeTestInfo("Test" + std::to_string(i)), makeInvoker());
    }
    
    EXPECT_EQ(registry.getAllTests().size(), 100u);
    EXPECT_EQ(registry.getAllInfos().size(), 100u);
}

TEST_F(TestRegistryTest_1018, GetAllTestsReturnsSameReference_1018) {
    registry.registerTest(makeTestInfo("Test1"), makeInvoker());
    
    auto const& ref1 = registry.getAllTests();
    auto const& ref2 = registry.getAllTests();
    EXPECT_EQ(&ref1, &ref2);
}

TEST_F(TestRegistryTest_1018, GetAllInfosReturnsSameReference_1018) {
    registry.registerTest(makeTestInfo("Test1"), makeInvoker());
    
    auto const& ref1 = registry.getAllInfos();
    auto const& ref2 = registry.getAllInfos();
    EXPECT_EQ(&ref1, &ref2);
}

TEST_F(TestRegistryTest_1018, RegisteredTestInfoPreserved_1018) {
    registry.registerTest(makeTestInfo("PreservedName"), makeInvoker());
    
    auto const& infos = registry.getAllInfos();
    ASSERT_FALSE(infos.empty());
    EXPECT_NE(infos[0], nullptr);
    EXPECT_EQ(infos[0]->name, "PreservedName");
}

TEST_F(TestRegistryTest_1018, OrderOfRegistrationPreserved_1018) {
    registry.registerTest(makeTestInfo("First"), makeInvoker());
    registry.registerTest(makeTestInfo("Second"), makeInvoker());
    registry.registerTest(makeTestInfo("Third"), makeInvoker());
    
    auto const& infos = registry.getAllInfos();
    ASSERT_EQ(infos.size(), 3u);
    EXPECT_EQ(infos[0]->name, "First");
    EXPECT_EQ(infos[1]->name, "Second");
    EXPECT_EQ(infos[2]->name, "Third");
}

TEST_F(TestRegistryTest_1018, HandleAndInfoCorrespond_1018) {
    registry.registerTest(makeTestInfo("CorrespondTest"), makeInvoker());
    
    auto const& tests = registry.getAllTests();
    auto const& infos = registry.getAllInfos();
    
    ASSERT_EQ(tests.size(), 1u);
    ASSERT_EQ(infos.size(), 1u);
    EXPECT_EQ(&tests[0].getTestCaseInfo(), infos[0]);
}
