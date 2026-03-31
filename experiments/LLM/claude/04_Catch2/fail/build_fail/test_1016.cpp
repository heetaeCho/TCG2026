#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary Catch2 headers
#include "catch2/internal/catch_test_case_registry_impl.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_test_registry.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// We need to create concrete implementations for testing

namespace {

// A simple mock/stub for ITestInvoker
class StubTestInvoker : public Catch::ITestInvoker {
public:
    void invoke() const override {}
};

// Helper to create a TestCaseInfo for testing
Catch::Detail::unique_ptr<Catch::TestCaseInfo> makeTestCaseInfo(
    const std::string& name,
    const std::string& className = "",
    const Catch::SourceLineInfo& lineInfo = {"test_file.cpp", 1}) {
    
    Catch::TestCaseInfo info(
        className,
        {lineInfo, name, Catch::StringRef()},
        Catch::TestCaseInfo::None
    );
    return Catch::Detail::unique_ptr<Catch::TestCaseInfo>(
        new Catch::TestCaseInfo(info)
    );
}

Catch::Detail::unique_ptr<Catch::ITestInvoker> makeInvoker() {
    return Catch::Detail::unique_ptr<Catch::ITestInvoker>(
        new StubTestInvoker()
    );
}

// Mock IConfig for getAllTestsSorted
class MockConfig : public Catch::IConfig {
public:
    // Provide minimal implementation of IConfig
    bool allowThrows() const override { return true; }
    Catch::StringRef name() const override { return "MockConfig"; }
    int abortAfter() const override { return -1; }
    bool showInvisibles() const override { return false; }
    Catch::ShowDurations showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return -1.0; }
    Catch::TestRunOrder runOrder() const override { return Catch::TestRunOrder::Declared; }
    Catch::ColourMode defaultColourMode() const override { return Catch::ColourMode::PlatformDefault; }
    bool shouldDebugBreak() const override { return false; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 100000; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds(100); }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override { 
        static std::vector<std::string> empty;
        return empty; 
    }
    std::vector<std::string> const& getSectionsToRun() const override {
        static std::vector<std::string> empty;
        return empty;
    }
    Catch::TestSpec const& testSpec() const override {
        static Catch::TestSpec spec;
        return spec;
    }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    unsigned int rngSeed() const override { return 0; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
};

} // anonymous namespace

class TestRegistryTest_1016 : public ::testing::Test {
protected:
    Catch::TestRegistry registry;
};

// Test that a freshly created TestRegistry has no tests
TEST_F(TestRegistryTest_1016, InitiallyEmpty_1016) {
    EXPECT_TRUE(registry.getAllInfos().empty());
    EXPECT_TRUE(registry.getAllTests().empty());
}

// Test that registering a single test increases counts
TEST_F(TestRegistryTest_1016, RegisterSingleTest_1016) {
    auto info = makeTestCaseInfo("Test1");
    auto invoker = makeInvoker();
    
    registry.registerTest(CATCH_MOVE(info), CATCH_MOVE(invoker));
    
    EXPECT_EQ(registry.getAllInfos().size(), 1u);
    EXPECT_EQ(registry.getAllTests().size(), 1u);
}

// Test registering multiple tests
TEST_F(TestRegistryTest_1016, RegisterMultipleTests_1016) {
    for (int i = 0; i < 5; ++i) {
        auto info = makeTestCaseInfo("Test" + std::to_string(i));
        auto invoker = makeInvoker();
        registry.registerTest(CATCH_MOVE(info), CATCH_MOVE(invoker));
    }
    
    EXPECT_EQ(registry.getAllInfos().size(), 5u);
    EXPECT_EQ(registry.getAllTests().size(), 5u);
}

// Test that getAllInfos returns pointers to the registered TestCaseInfo objects
TEST_F(TestRegistryTest_1016, GetAllInfosReturnsCorrectPointers_1016) {
    auto info = makeTestCaseInfo("UniqueTestName");
    Catch::TestCaseInfo* rawPtr = info.get();
    auto invoker = makeInvoker();
    
    registry.registerTest(CATCH_MOVE(info), CATCH_MOVE(invoker));
    
    auto const& infos = registry.getAllInfos();
    ASSERT_EQ(infos.size(), 1u);
    EXPECT_EQ(infos[0], rawPtr);
}

// Test that getAllTests returns handles corresponding to registered tests
TEST_F(TestRegistryTest_1016, GetAllTestsMatchesRegistration_1016) {
    auto info1 = makeTestCaseInfo("TestA");
    auto info2 = makeTestCaseInfo("TestB");
    Catch::TestCaseInfo* rawPtr1 = info1.get();
    Catch::TestCaseInfo* rawPtr2 = info2.get();
    
    registry.registerTest(CATCH_MOVE(info1), makeInvoker());
    registry.registerTest(CATCH_MOVE(info2), makeInvoker());
    
    auto const& tests = registry.getAllTests();
    ASSERT_EQ(tests.size(), 2u);
    EXPECT_EQ(&tests[0].getTestCaseInfo(), rawPtr1);
    EXPECT_EQ(&tests[1].getTestCaseInfo(), rawPtr2);
}

// Test getAllInfos consistency with getAllTests
TEST_F(TestRegistryTest_1016, InfosAndTestsConsistent_1016) {
    for (int i = 0; i < 3; ++i) {
        registry.registerTest(makeTestCaseInfo("Test" + std::to_string(i)), makeInvoker());
    }
    
    EXPECT_EQ(registry.getAllInfos().size(), registry.getAllTests().size());
}

// Test that getAllTestsSorted returns results with declared ordering
TEST_F(TestRegistryTest_1016, GetAllTestsSortedDeclaredOrder_1016) {
    registry.registerTest(makeTestCaseInfo("Alpha"), makeInvoker());
    registry.registerTest(makeTestCaseInfo("Beta"), makeInvoker());
    registry.registerTest(makeTestCaseInfo("Gamma"), makeInvoker());
    
    MockConfig config;
    auto const& sorted = registry.getAllTestsSorted(config);
    
    EXPECT_EQ(sorted.size(), 3u);
}

// Test that getAllTestsSorted with same config returns same size as getAllTests
TEST_F(TestRegistryTest_1016, SortedSizeMatchesTotal_1016) {
    for (int i = 0; i < 10; ++i) {
        registry.registerTest(makeTestCaseInfo("Test" + std::to_string(i)), makeInvoker());
    }
    
    MockConfig config;
    auto const& sorted = registry.getAllTestsSorted(config);
    auto const& all = registry.getAllTests();
    
    EXPECT_EQ(sorted.size(), all.size());
}

// Test empty registry with getAllTestsSorted
TEST_F(TestRegistryTest_1016, GetAllTestsSortedEmpty_1016) {
    MockConfig config;
    auto const& sorted = registry.getAllTestsSorted(config);
    EXPECT_TRUE(sorted.empty());
}

// Test registering a large number of tests (boundary-ish condition)
TEST_F(TestRegistryTest_1016, RegisterManyTests_1016) {
    const size_t count = 100;
    for (size_t i = 0; i < count; ++i) {
        registry.registerTest(
            makeTestCaseInfo("Test" + std::to_string(i)),
            makeInvoker()
        );
    }
    
    EXPECT_EQ(registry.getAllInfos().size(), count);
    EXPECT_EQ(registry.getAllTests().size(), count);
}

// Test that the order of getAllInfos matches registration order
TEST_F(TestRegistryTest_1016, RegistrationOrderPreserved_1016) {
    std::vector<Catch::TestCaseInfo*> rawPtrs;
    
    for (int i = 0; i < 5; ++i) {
        auto info = makeTestCaseInfo("Test" + std::to_string(i));
        rawPtrs.push_back(info.get());
        registry.registerTest(CATCH_MOVE(info), makeInvoker());
    }
    
    auto const& infos = registry.getAllInfos();
    ASSERT_EQ(infos.size(), rawPtrs.size());
    
    for (size_t i = 0; i < rawPtrs.size(); ++i) {
        EXPECT_EQ(infos[i], rawPtrs[i]) << "Mismatch at index " << i;
    }
}

// Test that getAllInfos returns a const reference (stability check)
TEST_F(TestRegistryTest_1016, GetAllInfosReferenceStability_1016) {
    registry.registerTest(makeTestCaseInfo("First"), makeInvoker());
    
    auto const& infos1 = registry.getAllInfos();
    ASSERT_EQ(infos1.size(), 1u);
    Catch::TestCaseInfo* firstPtr = infos1[0];
    
    registry.registerTest(makeTestCaseInfo("Second"), makeInvoker());
    
    auto const& infos2 = registry.getAllInfos();
    ASSERT_EQ(infos2.size(), 2u);
    // First registered test info pointer should remain the same
    EXPECT_EQ(infos2[0], firstPtr);
}
