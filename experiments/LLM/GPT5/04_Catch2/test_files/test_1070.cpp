// File: tests/session_constructor_tests_1070.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_session.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/internal/catch_startup_exception_registry.hpp"
#include "catch2/internal/catch_clara.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

using ::testing::_;
using ::testing::Exactly;
using ::testing::NiceMock;

namespace Catch {

// ===== Test Doubles injected for constructor collaborators =====

// 1) Mutable registry hub mock — we only assert on registerStartupException()
class MockMutableRegistryHub : public IMutableRegistryHub {
public:
    MOCK_METHOD(void, registerReporter,
                (const std::string& name, IReporterFactoryPtr factory), (override));
    MOCK_METHOD(void, registerListener,
                (Detail::unique_ptr<EventListenerFactory> factory), (override));
    MOCK_METHOD(void, registerTest,
                (Detail::unique_ptr<TestCaseInfo>&& testInfo,
                 Detail::unique_ptr<ITestInvoker>&& invoker), (override));
    MOCK_METHOD(void, registerTranslator,
                (Detail::unique_ptr<IExceptionTranslator>&& translator), (override));
    MOCK_METHOD(void, registerTagAlias,
                (const std::string& alias, const std::string& tag,
                 const SourceLineInfo& lineInfo), (override));
    MOCK_METHOD(void, registerStartupException, (), (override));
    MOCK_METHOD(IMutableEnumValuesRegistry&, getMutableEnumValuesRegistry, (), (override));
};

// 2) Const registry hub mock — only used to supply an empty StartupExceptionRegistry
class MockRegistryHub : public IRegistryHub {
public:
    MockRegistryHub() = default;

    // Provide accessors needed by Session() — only startup exceptions are used here
    const ReporterRegistry& getReporterRegistry() override {
        // Not used in these tests; provide a dummy to satisfy interface.
        static ReporterRegistry* dummy = reinterpret_cast<ReporterRegistry*>(0x1);
        return *dummy;
    }
    const ITestCaseRegistry& getTestCaseRegistry() override {
        static ITestCaseRegistry* dummy = reinterpret_cast<ITestCaseRegistry*>(0x1);
        return *dummy;
    }
    const ITagAliasRegistry& getTagAliasRegistry() override {
        static ITagAliasRegistry* dummy = reinterpret_cast<ITagAliasRegistry*>(0x1);
        return *dummy;
    }
    const IExceptionTranslatorRegistry& getExceptionTranslatorRegistry() override {
        static IExceptionTranslatorRegistry* dummy =
            reinterpret_cast<IExceptionTranslatorRegistry*>(0x1);
        return *dummy;
    }
    const StartupExceptionRegistry& getStartupExceptionRegistry() override {
        // Keep it empty so Session() does not enter the printing/colour path
        return m_emptyStartup;
    }

private:
    StartupExceptionRegistry m_emptyStartup; // starts empty
};

// Global pointers the injected free functions will use
static MockMutableRegistryHub* g_mockMutableHub = nullptr;
static MockRegistryHub*       g_mockConstHub    = nullptr;

// 3) Injected global accessors used by Session() constructor
IMutableRegistryHub& getMutableRegistryHub() {
    // Provided for the constructor's catch-all path on double-instantiation
    return *g_mockMutableHub;
}
IRegistryHub const& getRegistryHub() {
    // Provided for reading startup exceptions (empty in these tests)
    return *g_mockConstHub;
}

// 4) Injected CLI factory used by Session() constructor
//    We just return a default-constructed parser; we do NOT simulate internal behavior.
Clara::Parser makeCommandLineParser(ConfigData&) {
    return Clara::Parser{};
}

} // namespace Catch

// ===== Test fixture =====
class SessionTest_1070 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create NiceMocks so unexpected calls are ignored (we’ll assert only what we care about)
        m_mutable.reset(new NiceMock<Catch::MockMutableRegistryHub>());
        m_const.reset(new NiceMock<Catch::MockRegistryHub>());
        Catch::g_mockMutableHub = m_mutable.get();
        Catch::g_mockConstHub   = m_const.get();

        // getMutableEnumValuesRegistry is pure virtual; return a reference to a dummy object
        ON_CALL(*m_mutable, getMutableEnumValuesRegistry())
            .WillByDefault(::testing::ReturnRef(m_dummyEnumRegistry));
    }

    void TearDown() override {
        Catch::g_mockMutableHub = nullptr;
        Catch::g_mockConstHub   = nullptr;
    }

private:
    // Minimal dummy to satisfy pure-virtual return by reference
    class DummyEnumValuesRegistry : public Catch::IMutableEnumValuesRegistry {
    public:
        void registerEnumValue( std::string const&, std::string const&,
                                Catch::SourceLineInfo const& ) override {}
    } m_dummyEnumRegistry;

protected:
    std::unique_ptr<NiceMock<Catch::MockMutableRegistryHub>> m_mutable;
    std::unique_ptr<NiceMock<Catch::MockRegistryHub>>        m_const;
};


// ========== TESTS ==========

// First construction should not report a startup exception
TEST_F(SessionTest_1070, FirstConstruction_DoesNotRegisterStartupException_1070) {
    // Expect no startup exception registration on the first instance
    EXPECT_CALL(*m_mutable, registerStartupException()).Times(0);

    // Act: first instance
    Catch::Session s1;
}

// Subsequent constructions should register a startup exception each time
TEST_F(SessionTest_1070, SecondConstruction_RegistersStartupExceptionOnce_1070) {
    // Arrange: first instance created
    Catch::Session s1;

    // Expect exactly one registration from the second construction
    EXPECT_CALL(*m_mutable, registerStartupException()).Times(Exactly(1));

    // Act: second instance (should trigger the catch-all path that reports a startup exception)
    Catch::Session s2;
}

// Multiple extra instances should each report a startup exception
TEST_F(SessionTest_1070, MultipleExtraConstructions_RegisterStartupExceptionPerInstance_1070) {
    // Arrange: first instance created
    Catch::Session s1;

    // Two more instances -> expect 2 registrations
    EXPECT_CALL(*m_mutable, registerStartupException()).Times(Exactly(2));

    Catch::Session s2;
    Catch::Session s3;
}
