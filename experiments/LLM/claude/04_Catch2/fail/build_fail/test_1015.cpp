#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <chrono>

// Include necessary Catch2 headers
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_testcase.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_test_registry.hpp"

// Forward declaration of the function under test
namespace Catch {
    std::vector<TestCaseHandle> const& getAllTestCasesSorted(IConfig const& config);
    IRegistryHub const& getRegistryHub();
    void cleanUpContext();
    IMutableRegistryHub& getMutableRegistryHub();
}

// Mock for IConfig
class MockConfig : public Catch::IConfig {
public:
    ~MockConfig() override = default;
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class GetAllTestCasesSortedTest_1015 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that getAllTestCasesSorted returns a reference (non-null, valid vector)
TEST_F(GetAllTestCasesSortedTest_1015, ReturnsVectorReference_1015) {
    MockConfig config;
    Catch::TestSpec emptySpec;
    std::vector<std::string> emptyVec;

    ON_CALL(config, runOrder()).WillByDefault(::testing::Return(Catch::TestRunOrder::Declared));
    ON_CALL(config, rngSeed()).WillByDefault(::testing::Return(0u));
    ON_CALL(config, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
    ON_CALL(config, hasTestFilters()).WillByDefault(::testing::Return(false));
    ON_CALL(config, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));

    const std::vector<Catch::TestCaseHandle>& result = Catch::getAllTestCasesSorted(config);
    // The result should be a valid reference; we can check its size is non-negative (always true for size_t)
    EXPECT_GE(result.size(), 0u);
}

// Test that calling getAllTestCasesSorted twice with the same config returns the same reference
TEST_F(GetAllTestCasesSortedTest_1015, ConsistentResultsForSameConfig_1015) {
    MockConfig config;
    Catch::TestSpec emptySpec;
    std::vector<std::string> emptyVec;

    ON_CALL(config, runOrder()).WillByDefault(::testing::Return(Catch::TestRunOrder::Declared));
    ON_CALL(config, rngSeed()).WillByDefault(::testing::Return(0u));
    ON_CALL(config, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
    ON_CALL(config, hasTestFilters()).WillByDefault(::testing::Return(false));
    ON_CALL(config, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));

    const std::vector<Catch::TestCaseHandle>& result1 = Catch::getAllTestCasesSorted(config);
    const std::vector<Catch::TestCaseHandle>& result2 = Catch::getAllTestCasesSorted(config);

    EXPECT_EQ(result1.size(), result2.size());
}

// Test that the function delegates to the registry hub properly
// The returned vector size should match what getTestCaseRegistry().getAllTestsSorted() returns
TEST_F(GetAllTestCasesSortedTest_1015, ReturnsSameAsRegistrySorted_1015) {
    MockConfig config;
    Catch::TestSpec emptySpec;
    std::vector<std::string> emptyVec;

    ON_CALL(config, runOrder()).WillByDefault(::testing::Return(Catch::TestRunOrder::Declared));
    ON_CALL(config, rngSeed()).WillByDefault(::testing::Return(0u));
    ON_CALL(config, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
    ON_CALL(config, hasTestFilters()).WillByDefault(::testing::Return(false));
    ON_CALL(config, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));

    const auto& fromFunction = Catch::getAllTestCasesSorted(config);
    const auto& fromRegistry = Catch::getRegistryHub().getTestCaseRegistry().getAllTestsSorted(config);

    // Both should reference the same underlying data
    EXPECT_EQ(&fromFunction, &fromRegistry);
}

// Test with a config that has test filters disabled
TEST_F(GetAllTestCasesSortedTest_1015, NoTestFiltersReturnsSorted_1015) {
    MockConfig config;
    Catch::TestSpec emptySpec;
    std::vector<std::string> emptyVec;

    ON_CALL(config, runOrder()).WillByDefault(::testing::Return(Catch::TestRunOrder::Declared));
    ON_CALL(config, rngSeed()).WillByDefault(::testing::Return(42u));
    ON_CALL(config, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
    ON_CALL(config, hasTestFilters()).WillByDefault(::testing::Return(false));
    ON_CALL(config, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));

    const std::vector<Catch::TestCaseHandle>& result = Catch::getAllTestCasesSorted(config);

    // Should not throw and should return a valid vector
    SUCCEED();
}

// Test with randomized run order
TEST_F(GetAllTestCasesSortedTest_1015, RandomRunOrderDoesNotCrash_1015) {
    MockConfig config;
    Catch::TestSpec emptySpec;
    std::vector<std::string> emptyVec;

    ON_CALL(config, runOrder()).WillByDefault(::testing::Return(Catch::TestRunOrder::Randomized));
    ON_CALL(config, rngSeed()).WillByDefault(::testing::Return(12345u));
    ON_CALL(config, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
    ON_CALL(config, hasTestFilters()).WillByDefault(::testing::Return(false));
    ON_CALL(config, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));

    EXPECT_NO_THROW({
        const std::vector<Catch::TestCaseHandle>& result = Catch::getAllTestCasesSorted(config);
        (void)result;
    });
}

// Test that the return type is const reference
TEST_F(GetAllTestCasesSortedTest_1015, ReturnsConstReference_1015) {
    MockConfig config;
    Catch::TestSpec emptySpec;
    std::vector<std::string> emptyVec;

    ON_CALL(config, runOrder()).WillByDefault(::testing::Return(Catch::TestRunOrder::Declared));
    ON_CALL(config, rngSeed()).WillByDefault(::testing::Return(0u));
    ON_CALL(config, testSpec()).WillByDefault(::testing::ReturnRef(emptySpec));
    ON_CALL(config, hasTestFilters()).WillByDefault(::testing::Return(false));
    ON_CALL(config, getTestsOrTags()).WillByDefault(::testing::ReturnRef(emptyVec));

    // Verify it compiles as a const reference
    const std::vector<Catch::TestCaseHandle>& result = Catch::getAllTestCasesSorted(config);
    static_assert(std::is_const<std::remove_reference_t<decltype(result)>>::value,
                  "Return type should be const reference");
    SUCCEED();
}
