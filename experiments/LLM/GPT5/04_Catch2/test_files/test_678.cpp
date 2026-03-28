// File: tests/TagAliasRegistryGet_678_Test.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using ::testing::ReturnRef;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Times;

namespace Catch {

// --- Minimal interface shims matching the public surface we need ---
// NOTE: We only declare what's necessary to compile & verify behavior.
//       We do NOT reproduce any internal logic.

struct TagAlias { std::string alias; std::string expansion; };

class ITagAliasRegistry {
public:
    virtual ~ITagAliasRegistry() = default;
    // Only declare methods we might reference in mocks; we won't call them here.
    virtual TagAlias const* find(const std::string& alias) = 0;
    virtual std::string expandAliases(const std::string& unexpandedTestSpec) = 0;

    // The function under test:
    static ITagAliasRegistry const& get();
};

class IRegistryHub {
public:
    virtual ~IRegistryHub() = default;
    virtual ITagAliasRegistry const& getTagAliasRegistry() const = 0;
};

// The production code calls this global accessor.
// In tests, we provide a definition that returns our injected test double.
IRegistryHub& getRegistryHub();

} // namespace Catch

// ---------------- Test doubles ----------------
namespace Catch {

class MockTagAliasRegistry : public ITagAliasRegistry {
public:
    MOCK_METHOD(TagAlias const*, find, (const std::string&), (override));
    MOCK_METHOD(std::string, expandAliases, (const std::string&), (override));
};

class MockRegistryHub : public IRegistryHub {
public:
    MOCK_METHOD(const ITagAliasRegistry&, getTagAliasRegistry, (), (const, override));
};

// Test-scoped registry hub injection point.
static IRegistryHub* g_testHub = nullptr;

// Provide the symbol used by ITagAliasRegistry::get() implementation.
// Our definition delegates to the test-controlled pointer.
IRegistryHub& getRegistryHub() {
    // In normal production, this would return the real hub singleton.
    // For tests we require it to be set explicitly.
    assert(g_testHub && "Test hub must be set before calling getRegistryHub()");
    return *g_testHub;
}

} // namespace Catch

// ---------------- Test fixture ----------------
class TagAliasRegistryGet_678 : public ::testing::Test {
protected:
    NiceMock<Catch::MockTagAliasRegistry> aliasRegistry_;
    StrictMock<Catch::MockRegistryHub> hub_;

    void SetUp() override {
        Catch::g_testHub = &hub_;
    }
    void TearDown() override {
        Catch::g_testHub = nullptr;
    }
};

// ---------------- Tests ----------------

// Verifies that ITagAliasRegistry::get() delegates to the registry hub and
// returns the exact reference provided by IRegistryHub::getTagAliasRegistry().
TEST_F(TagAliasRegistryGet_678, DelegatesToRegistryHub_678) {
    // Arrange: hub will return our alias registry reference.
    EXPECT_CALL(hub_, getTagAliasRegistry())
        .Times(1)
        .WillOnce(ReturnRef(aliasRegistry_));

    // Act
    const Catch::ITagAliasRegistry& got = Catch::ITagAliasRegistry::get();

    // Assert: address equality confirms the returned reference is exactly the hub's.
    EXPECT_EQ(&got, &aliasRegistry_);
}

// Verifies that multiple calls to ITagAliasRegistry::get() query the hub each time,
// i.e., no hidden caching is relied upon by the test (observable interaction only).
TEST_F(TagAliasRegistryGet_678, MultipleCallsQueryHubEachTime_678) {
    // Arrange: both calls return the same registry reference (could be different in theory,
    // but we only verify calls and returned reference identity per call).
    EXPECT_CALL(hub_, getTagAliasRegistry())
        .Times(2)
        .WillRepeatedly(ReturnRef(aliasRegistry_));

    // Act
    auto& first  = Catch::ITagAliasRegistry::get();
    auto& second = Catch::ITagAliasRegistry::get();

    // Assert
    EXPECT_EQ(&first, &aliasRegistry_);
    EXPECT_EQ(&second, &aliasRegistry_);
}

// Defensive/edge scenario: if the hub returned a different alias registry object,
// get() should forward that reference transparently (we verify by identity).
TEST_F(TagAliasRegistryGet_678, ForwardsWhateverHubReturns_678) {
    NiceMock<Catch::MockTagAliasRegistry> anotherRegistry;

    {
        ::testing::InSequence s;
        EXPECT_CALL(hub_, getTagAliasRegistry())
            .WillOnce(ReturnRef(aliasRegistry_));
        EXPECT_CALL(hub_, getTagAliasRegistry())
            .WillOnce(ReturnRef(anotherRegistry));
    }

    auto& first  = Catch::ITagAliasRegistry::get();
    auto& second = Catch::ITagAliasRegistry::get();

    EXPECT_EQ(&first,  &aliasRegistry_);
    EXPECT_EQ(&second, &anotherRegistry);
}

