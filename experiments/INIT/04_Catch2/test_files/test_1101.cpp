// File: tests/TagAliasAutoregistrarTests_1101.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_tag_alias_autoregistrar.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Eq;
using ::testing::Field;
using ::testing::Property;
using ::testing::StrEq;
using ::testing::Invoke;

namespace Catch {

// --- Test shim to intercept global access to the registry hub ----

// We’ll route the global accessor to a test-controlled pointer.
static IMutableRegistryHub* g_mockHubForTests = nullptr;

// Provide a strong definition that the AUT (class under test) will call.
// In test builds, this overrides the real one at link time.
IMutableRegistryHub& getMutableRegistryHub() {
    // Precondition for tests: this must be set by each test.
    assert(g_mockHubForTests && "Test hub not set");
    return *g_mockHubForTests;
}

} // namespace Catch

// ---------------------- GMock for the hub ------------------------
// We only care about the two interactions exercised by the AUT:
//   - registerTagAlias
//   - registerStartupException
// Other pure virtuals get no-op bodies; tests never touch them.

namespace Catch {

// Forward declarations for types used in IMutableRegistryHub's signature
namespace Detail {
template <typename T> class unique_ptr;
class EventListenerFactory;
class TestCaseInfo;
class ITestInvoker;
class IExceptionTranslator;
} // namespace Detail

class DummyEnumValuesRegistry : public IMutableEnumValuesRegistry {};

// Concrete mock
class MockMutableRegistryHub : public IMutableRegistryHub {
public:
    // We verify these two
    MOCK_METHOD(void, registerTagAlias,
                (const std::string& alias,
                 const std::string& tag,
                 const SourceLineInfo& lineInfo),
                (override));

    MOCK_METHOD(void, registerStartupException, (), (override));

    // ---- Unused pure-virtuals (no-ops to satisfy interface) ----
    void registerReporter(const std::string&, IReporterFactoryPtr) override {}
    void registerListener(Detail::unique_ptr<EventListenerFactory>) override {}
    void registerTest(Detail::unique_ptr<TestCaseInfo>&&,
                      Detail::unique_ptr<ITestInvoker>&&) override {}
    void registerTranslator(Detail::unique_ptr<IExceptionTranslator>&&) override {}
    IMutableEnumValuesRegistry& getMutableEnumValuesRegistry() override {
        static DummyEnumValuesRegistry dummy;
        return dummy;
    }

    // Virtual dtor already declared in interface; use default
    ~MockMutableRegistryHub() override = default;
};

} // namespace Catch

// ---------------------------- Tests ------------------------------

class TagAliasAutoregistrarTest_1101 : public ::testing::Test {
protected:
    void SetUp() override {
        hub_ = std::make_unique<Catch::MockMutableRegistryHub>();
        Catch::g_mockHubForTests = hub_.get();
    }
    void TearDown() override {
        Catch::g_mockHubForTests = nullptr;
    }

    std::unique_ptr<Catch::MockMutableRegistryHub> hub_;
};

// Normal operation: the constructor should call registerTagAlias once
// with the provided alias, tag, and SourceLineInfo — and NOT call
// registerStartupException.
TEST_F(TagAliasAutoregistrarTest_1101, RegistersAliasOnConstruction_1101) {
    const char* kAlias = "myAlias";
    const char* kTag   = "[fast][unit]";
    Catch::SourceLineInfo sli{"tag_alias_tests.cpp", 321};

    EXPECT_CALL(*hub_,
        registerTagAlias(StrEq(kAlias), StrEq(kTag),
            AllOf(
                Field(&Catch::SourceLineInfo::file, StrEq(sli.file)),
                Field(&Catch::SourceLineInfo::line, Eq(sli.line))
            )))
        .Times(1);

    EXPECT_CALL(*hub_, registerStartupException()).Times(0);

    // Act: constructing the registrar performs the registration
    Catch::RegistrarForTagAliases registrar{kAlias, kTag, sli};
}

// Exceptional path: if registerTagAlias throws, the registrar must
// catch it and notify via registerStartupException(); no exception
// should escape the constructor.
TEST_F(TagAliasAutoregistrarTest_1101, RegistersStartupExceptionOnFailure_1101) {
    const char* kAlias = "broken";
    const char* kTag   = "[oops]";
    Catch::SourceLineInfo sli{"tag_alias_tests.cpp", 999};

    EXPECT_CALL(*hub_, registerTagAlias(_, _, _))
        .WillOnce(Invoke([](const std::string&, const std::string&, const Catch::SourceLineInfo&) {
            throw std::runtime_error("simulated failure");
        }));

    EXPECT_CALL(*hub_, registerStartupException()).Times(1);

    // Act & Assert: constructor should NOT rethrow
    EXPECT_NO_THROW({
        Catch::RegistrarForTagAliases registrar{kAlias, kTag, sli};
    });
}
