// reporter_registry_create_tests_574.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/interfaces/catch_interfaces_reporter_factory.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::ByMove;

namespace {

// Minimal mock for the factory collaborator
class MockReporterFactory : public Catch::IReporterFactory {
public:
    // create should return whatever IEventListenerPtr is in the real interface
    MOCK_METHOD(Catch::IEventListenerPtr, create,
                (Catch::ReporterConfig&&), (override));
    MOCK_METHOD(std::string, getDescription, (), (override));
};

// Helper: build a ReporterConfig with controllable, observable inputs.
// We only use public ctor + public accessors inside the mock.
inline Catch::ReporterConfig MakeConfig(
    const Catch::IConfig* cfg = nullptr,
    int colourModeOrdinal = 0,
    std::map<std::string, std::string> options = {}) {

    return Catch::ReporterConfig(
        cfg,
        Catch::Detail::unique_ptr<Catch::IStream>(nullptr), // stream not needed for these tests
        static_cast<Catch::ColourMode>(colourModeOrdinal),
        std::move(options)
    );
}

} // namespace

// Fixture kept simple for clarity/consistency
class ReporterRegistryCreateTest_574 : public ::testing::Test {
protected:
    Catch::ReporterRegistry registry_;
};

// [Normal] Unknown name -> returns nullptr, and no collaborator is invoked
TEST_F(ReporterRegistryCreateTest_574, ReturnsNullptrWhenNameNotRegistered_574) {
    auto result = registry_.create("does-not-exist", MakeConfig());
    EXPECT_EQ(result, nullptr);
}

// [Normal] Registered name -> factory::create is called once
TEST_F(ReporterRegistryCreateTest_574, CallsFactoryCreateWhenNameRegistered_574) {
    auto* raw = new MockReporterFactory();
    Catch::Detail::unique_ptr<Catch::IReporterFactory> ptr(raw);

    // Expect single invocation; the return value can be nullptr — this test
    // verifies the *interaction* (observable via mock), not internal logic.
    EXPECT_CALL(*raw, create(_))
        .Times(1)
        .WillOnce(Invoke([](Catch::ReporterConfig&&) {
            return Catch::IEventListenerPtr{}; // return whatever the factory decides (nullptr ok)
        }));

    registry_.registerReporter("demo", std::move(ptr));

    // Exercise
    auto out = registry_.create("demo", MakeConfig());
    // We do not assert on non-null here; the factory controls that.
    // The key observable is that create was called exactly once.
}

// [Boundary/Behavior] Lookup should be case-insensitive (map uses CaseInsensitiveLess)
// Register under mixed case, create using different case -> must call factory once
TEST_F(ReporterRegistryCreateTest_574, LookupIsCaseInsensitive_574) {
    auto* raw = new MockReporterFactory();
    Catch::Detail::unique_ptr<Catch::IReporterFactory> ptr(raw);

    EXPECT_CALL(*raw, create(_))
        .Times(1)
        .WillOnce(Invoke([](Catch::ReporterConfig&&) {
            return Catch::IEventListenerPtr{};
        }));

    registry_.registerReporter("MiXeD-NaMe", std::move(ptr));

    // Different casing on purpose
    (void)registry_.create("mixed-name", MakeConfig());
}

// [Behavior] Multiple factories present -> the one matching the requested name is used
TEST_F(ReporterRegistryCreateTest_574, SelectsMatchingFactoryAmongMultiple_574) {
    // Factory A
    auto* rawA = new MockReporterFactory();
    Catch::Detail::unique_ptr<Catch::IReporterFactory> ptrA(rawA);
    EXPECT_CALL(*rawA, create(_)).Times(0); // should NOT be called

    // Factory B
    auto* rawB = new MockReporterFactory();
    Catch::Detail::unique_ptr<Catch::IReporterFactory> ptrB(rawB);
    EXPECT_CALL(*rawB, create(_))
        .Times(1)
        .WillOnce(Invoke([](Catch::ReporterConfig&&) {
            return Catch::IEventListenerPtr{};
        }));

    registry_.registerReporter("A", std::move(ptrA));
    registry_.registerReporter("B", std::move(ptrB));

    (void)registry_.create("B", MakeConfig());
}

// [Interaction Verification] Config is forwarded to factory::create (observable via getters)
TEST_F(ReporterRegistryCreateTest_574, ForwardsReporterConfigToFactory_574) {
    auto* raw = new MockReporterFactory();
    Catch::Detail::unique_ptr<Catch::IReporterFactory> ptr(raw);

    const Catch::IConfig* cfgPtr = nullptr; // still observable (nullptr == nullptr)
    std::map<std::string, std::string> opts = {{"key", "value"}};
    const int colourOrdinal = 42;

    EXPECT_CALL(*raw, create(_))
        .Times(1)
        .WillOnce(Invoke([&](Catch::ReporterConfig&& rc) {
            // Verify public, observable parts only
            EXPECT_EQ(rc.fullConfig(), cfgPtr);
            EXPECT_EQ(rc.colourMode(), static_cast<Catch::ColourMode>(colourOrdinal));
            const auto& got = rc.customOptions();
            auto it = got.find("key");
            ASSERT_NE(it, got.end());
            EXPECT_EQ(it->second, "value");
            return Catch::IEventListenerPtr{};
        }));

    registry_.registerReporter("check-config", std::move(ptr));
    (void)registry_.create("check-config", MakeConfig(cfgPtr, colourOrdinal, opts));
}
