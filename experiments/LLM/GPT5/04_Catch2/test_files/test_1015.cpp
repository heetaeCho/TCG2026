// File: tests/getAllTestCasesSorted_tests_1015.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

// Catch2 forward declarations / interfaces
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/interfaces/catch_interfaces_testcase.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
// For TestCaseHandle definition
#include "catch2/internal/catch_test_case_info.hpp"

using ::testing::Ref;
using ::testing::ReturnRef;
using ::testing::Throw;
using ::testing::InSequence;

namespace Catch {
// Forward-declare the function under test (it is implemented in the real source)
const std::vector<TestCaseHandle>& getAllTestCasesSorted(IConfig const& config);

// ---- Test seam for the global accessor used by the SUT ----
class MockTestCaseRegistry : public ITestCaseRegistry {
public:
    MOCK_METHOD(const std::vector<TestCaseInfo*>&, getAllInfos, (), (const, override));
    MOCK_METHOD(const std::vector<TestCaseHandle>&, getAllTests, (), (const, override));
    MOCK_METHOD(const std::vector<TestCaseHandle>&, getAllTestsSorted, (const IConfig&), (const, override));
    ~MockTestCaseRegistry() override = default;
};

class MockRegistryHub : public IRegistryHub {
public:
    // Only the method used by the SUT is mocked; others can be left unimplemented or defaulted
    MOCK_METHOD(const ITestCaseRegistry&, getTestCaseRegistry, (), (const, override));

    // Unused in these tests; provide dummies to satisfy interface linkage if needed.
    MOCK_METHOD(const ReporterRegistry&, getReporterRegistry, (), (const, override));
    MOCK_METHOD(const ITagAliasRegistry&, getTagAliasRegistry, (), (const, override));
    MOCK_METHOD(const IExceptionTranslatorRegistry&, getExceptionTranslatorRegistry, (), (const, override));
    MOCK_METHOD(const StartupExceptionRegistry&, getStartupExceptionRegistry, (), (const, override));

    ~MockRegistryHub() override = default;
};

class MockConfig : public IConfig {
public:
    // We don't rely on any config behavior, only identity/reference. No methods need expectations.
    ~MockConfig() override = default;
};

// Global pointer used by the seam below
static IRegistryHub* gHubForTests = nullptr;

// Provide a test replacement for the global accessor used by the SUT.
// The SUT calls this function, and our tests control what it returns.
IRegistryHub& getRegistryHub() {
    assert(gHubForTests && "Test hub must be set before calling SUT");
    return *gHubForTests;
}
} // namespace Catch

// ---------------------- Test Fixture ----------------------

class GetAllTestCasesSorted_1015 : public ::testing::Test {
protected:
    Catch::MockRegistryHub hub_;
    Catch::MockTestCaseRegistry registry_;
    Catch::MockConfig config_; // used only for identity

    // storage vectors to return by reference from mocks
    std::vector<Catch::TestCaseHandle> empty_;
    std::vector<Catch::TestCaseHandle> second_;

    void SetUp() override {
        // Install the hub into the seam
        Catch::gHubForTests = &hub_;
    }

    void TearDown() override {
        Catch::gHubForTests = nullptr;
    }
};

// ------------------------- Tests --------------------------

// Verifies: the SUT forwards to IRegistryHub::getTestCaseRegistry()
// then to ITestCaseRegistry::getAllTestsSorted(config), and returns
// exactly the reference provided by the registry.
TEST_F(GetAllTestCasesSorted_1015, ForwardsCallAndReturnsReference_1015) {
    EXPECT_CALL(hub_, getTestCaseRegistry())
        .WillOnce(ReturnRef(static_cast<const Catch::ITestCaseRegistry&>(registry_)));

    EXPECT_CALL(registry_, getAllTestsSorted(Ref(config_)))
        .WillOnce(ReturnRef(empty_));

    const auto& result = Catch::getAllTestCasesSorted(config_);
    EXPECT_EQ(&result, &empty_) << "SUT must return the exact reference from registry";
}

// Verifies: the exact IConfig reference is propagated to the registry (no copies).
TEST_F(GetAllTestCasesSorted_1015, PropagatesExactConfigReference_1015) {
    Catch::MockConfig anotherConfig; // to ensure Ref(config_) is checked precisely

    EXPECT_CALL(hub_, getTestCaseRegistry())
        .WillOnce(ReturnRef(static_cast<const Catch::ITestCaseRegistry&>(registry_)));
    EXPECT_CALL(registry_, getAllTestsSorted(Ref(config_)))  // must be the same object
        .WillOnce(ReturnRef(empty_));

    const auto& r1 = Catch::getAllTestCasesSorted(config_);
    (void)r1;

    // Also ensure calling with a different instance requires a new call with that instance.
    ::testing::Mock::VerifyAndClearExpectations(&hub_);
    ::testing::Mock::VerifyAndClearExpectations(&registry_);

    EXPECT_CALL(hub_, getTestCaseRegistry())
        .WillOnce(ReturnRef(static_cast<const Catch::ITestCaseRegistry&>(registry_)));
    EXPECT_CALL(registry_, getAllTestsSorted(Ref(anotherConfig)))
        .WillOnce(ReturnRef(empty_));

    const auto& r2 = Catch::getAllTestCasesSorted(anotherConfig);
    (void)r2;
}

// Verifies: multiple SUT invocations do not cache the registry result;
// they call through each time and can return different references.
TEST_F(GetAllTestCasesSorted_1015, MultipleCallsDoNotCacheAndMayReturnDifferentReferences_1015) {
    // Prepare a second distinct container to distinguish results
    second_ = {}; // remains distinct by address from empty_

    {
        InSequence seq;
        EXPECT_CALL(hub_, getTestCaseRegistry())
            .WillOnce(ReturnRef(static_cast<const Catch::ITestCaseRegistry&>(registry_)));
        EXPECT_CALL(registry_, getAllTestsSorted(Ref(config_)))
            .WillOnce(ReturnRef(empty_));
        EXPECT_CALL(hub_, getTestCaseRegistry())
            .WillOnce(ReturnRef(static_cast<const Catch::ITestCaseRegistry&>(registry_)));
        EXPECT_CALL(registry_, getAllTestsSorted(Ref(config_)))
            .WillOnce(ReturnRef(second_));
    }

    const auto& first = Catch::getAllTestCasesSorted(config_);
    const auto& second = Catch::getAllTestCasesSorted(config_);
    EXPECT_EQ(&first, &empty_);
    EXPECT_EQ(&second, &second_);
    EXPECT_NE(&first, &second);
}

// Verifies: exceptions from the registry propagate unchanged.
TEST_F(GetAllTestCasesSorted_1015, PropagatesExceptionsFromRegistry_1015) {
    EXPECT_CALL(hub_, getTestCaseRegistry())
        .WillOnce(ReturnRef(static_cast<const Catch::ITestCaseRegistry&>(registry_)));
    EXPECT_CALL(registry_, getAllTestsSorted(Ref(config_)))
        .WillOnce(Throw(std::runtime_error{"boom"}));

    EXPECT_THROW(
        (void)Catch::getAllTestCasesSorted(config_),
        std::runtime_error
    );
}
