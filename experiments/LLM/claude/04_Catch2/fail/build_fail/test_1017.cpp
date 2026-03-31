#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>

// Include necessary Catch2 headers
#include "catch2/internal/catch_test_case_registry_impl.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_test_case_info_hasher.hpp"
#include "catch2/interfaces/catch_interfaces_testcase.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;

// Mock ITestInvoker for registering tests
class MockTestInvoker : public ITestInvoker {
public:
    void invoke() const override {}
};

// Mock IConfig for getAllTestsSorted
class MockConfig : public IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(ReporterSpec const&, getReporterSpec, (std::size_t), (const, override));
    MOCK_METHOD(std::vector<ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(std::vector<ProcessedReporterSpec> const&, getProcessedReporterSpecs, (), (const, override));
    MOCK_METHOD(TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class TestRegistryTest_1017 : public ::testing::Test {
protected:
    void SetUp() override {
        registry = std::make_unique<TestRegistry>();
    }

    void TearDown() override {
        registry.reset();
    }

    std::unique_ptr<TestRegistry> registry;

    Detail::unique_ptr<TestCaseInfo> makeTestInfo(const std::string& name,
                                                   const std::string& className = "",
                                                   SourceLineInfo lineInfo = {"test_file.cpp", 1}) {
        return Detail::make_unique<TestCaseInfo>(
            name, className, Tag{}, lineInfo);
    }

    Detail::unique_ptr<ITestInvoker> makeInvoker() {
        return Detail::make_unique<MockTestInvoker>();
    }
};

// Test that a freshly constructed TestRegistry has no infos
TEST_F(TestRegistryTest_1017, EmptyRegistryHasNoInfos_1017) {
    auto const& infos = registry->getAllInfos();
    EXPECT_TRUE(infos.empty());
}

// Test that a freshly constructed TestRegistry has no tests
TEST_F(TestRegistryTest_1017, EmptyRegistryHasNoTests_1017) {
    auto const& tests = registry->getAllTests();
    EXPECT_TRUE(tests.empty());
}

// Test registering a single test case and verifying getAllInfos returns it
TEST_F(TestRegistryTest_1017, RegisterSingleTestAppearsInInfos_1017) {
    auto info = makeTestInfo("TestOne");
    auto* rawInfoPtr = info.get();
    registry->registerTest(std::move(info), makeInvoker());

    auto const& infos = registry->getAllInfos();
    ASSERT_EQ(infos.size(), 1u);
    EXPECT_EQ(infos[0], rawInfoPtr);
}

// Test registering a single test case and verifying getAllTests returns it
TEST_F(TestRegistryTest_1017, RegisterSingleTestAppearsInTests_1017) {
    registry->registerTest(makeTestInfo("TestOne"), makeInvoker());

    auto const& tests = registry->getAllTests();
    ASSERT_EQ(tests.size(), 1u);
}

// Test registering multiple test cases
TEST_F(TestRegistryTest_1017, RegisterMultipleTestsAllAppear_1017) {
    registry->registerTest(makeTestInfo("TestOne"), makeInvoker());
    registry->registerTest(makeTestInfo("TestTwo"), makeInvoker());
    registry->registerTest(makeTestInfo("TestThree"), makeInvoker());

    auto const& infos = registry->getAllInfos();
    ASSERT_EQ(infos.size(), 3u);

    auto const& tests = registry->getAllTests();
    ASSERT_EQ(tests.size(), 3u);
}

// Test that getAllInfos returns pointers matching registered test names
TEST_F(TestRegistryTest_1017, RegisteredTestInfoHasCorrectName_1017) {
    registry->registerTest(makeTestInfo("MySpecialTest"), makeInvoker());

    auto const& infos = registry->getAllInfos();
    ASSERT_EQ(infos.size(), 1u);
    EXPECT_EQ(infos[0]->name, "MySpecialTest");
}

// Test that order of registration is preserved in getAllInfos
TEST_F(TestRegistryTest_1017, RegistrationOrderPreservedInInfos_1017) {
    registry->registerTest(makeTestInfo("First"), makeInvoker());
    registry->registerTest(makeTestInfo("Second"), makeInvoker());
    registry->registerTest(makeTestInfo("Third"), makeInvoker());

    auto const& infos = registry->getAllInfos();
    ASSERT_EQ(infos.size(), 3u);
    EXPECT_EQ(infos[0]->name, "First");
    EXPECT_EQ(infos[1]->name, "Second");
    EXPECT_EQ(infos[2]->name, "Third");
}

// Test that order of registration is preserved in getAllTests
TEST_F(TestRegistryTest_1017, RegistrationOrderPreservedInTests_1017) {
    registry->registerTest(makeTestInfo("Alpha"), makeInvoker());
    registry->registerTest(makeTestInfo("Beta"), makeInvoker());

    auto const& tests = registry->getAllTests();
    ASSERT_EQ(tests.size(), 2u);
    EXPECT_EQ(tests[0].getTestCaseInfo().name, "Alpha");
    EXPECT_EQ(tests[1].getTestCaseInfo().name, "Beta");
}

// Test that getAllInfos and getAllTests sizes are consistent
TEST_F(TestRegistryTest_1017, InfosAndTestsSizeConsistent_1017) {
    for (int i = 0; i < 5; ++i) {
        registry->registerTest(makeTestInfo("Test" + std::to_string(i)), makeInvoker());
    }

    EXPECT_EQ(registry->getAllInfos().size(), registry->getAllTests().size());
}

// Test that getAllInfos returns a reference to the same vector (consistency)
TEST_F(TestRegistryTest_1017, GetAllInfosReturnsConsistentReference_1017) {
    registry->registerTest(makeTestInfo("ConsistencyTest"), makeInvoker());

    auto const& infos1 = registry->getAllInfos();
    auto const& infos2 = registry->getAllInfos();

    EXPECT_EQ(&infos1, &infos2);
}

// Test that getAllTests returns a reference to the same vector (consistency)
TEST_F(TestRegistryTest_1017, GetAllTestsReturnsConsistentReference_1017) {
    registry->registerTest(makeTestInfo("ConsistencyTest"), makeInvoker());

    auto const& tests1 = registry->getAllTests();
    auto const& tests2 = registry->getAllTests();

    EXPECT_EQ(&tests1, &tests2);
}

// Test that TestCaseHandle from getAllTests references correct info
TEST_F(TestRegistryTest_1017, TestCaseHandleReferencesCorrectInfo_1017) {
    auto info = makeTestInfo("HandleTest");
    auto* rawPtr = info.get();
    registry->registerTest(std::move(info), makeInvoker());

    auto const& tests = registry->getAllTests();
    ASSERT_EQ(tests.size(), 1u);
    EXPECT_EQ(&tests[0].getTestCaseInfo(), rawPtr);
}

// Test registering many tests (boundary-ish)
TEST_F(TestRegistryTest_1017, RegisterManyTests_1017) {
    const size_t count = 100;
    for (size_t i = 0; i < count; ++i) {
        registry->registerTest(makeTestInfo("Test_" + std::to_string(i)), makeInvoker());
    }

    EXPECT_EQ(registry->getAllInfos().size(), count);
    EXPECT_EQ(registry->getAllTests().size(), count);
}

// Test that the registry can be destroyed without issues (no crash)
TEST_F(TestRegistryTest_1017, DestructorDoesNotCrash_1017) {
    registry->registerTest(makeTestInfo("DestroyMe"), makeInvoker());
    // Explicit destruction
    registry.reset();
    // If we get here, no crash occurred
    SUCCEED();
}

// Test that empty registry destruction works fine
TEST_F(TestRegistryTest_1017, EmptyRegistryDestructorDoesNotCrash_1017) {
    registry.reset();
    SUCCEED();
}

// Test getAllInfos pointer validity after multiple registrations
TEST_F(TestRegistryTest_1017, InfoPointersRemainValidAfterMultipleRegistrations_1017) {
    auto info1 = makeTestInfo("First");
    auto* ptr1 = info1.get();
    registry->registerTest(std::move(info1), makeInvoker());

    auto info2 = makeTestInfo("Second");
    auto* ptr2 = info2.get();
    registry->registerTest(std::move(info2), makeInvoker());

    auto const& infos = registry->getAllInfos();
    ASSERT_EQ(infos.size(), 2u);
    // Pointers should still be valid (ownership is in the registry)
    EXPECT_EQ(infos[0], ptr1);
    EXPECT_EQ(infos[1], ptr2);
    EXPECT_EQ(infos[0]->name, "First");
    EXPECT_EQ(infos[1]->name, "Second");
}
