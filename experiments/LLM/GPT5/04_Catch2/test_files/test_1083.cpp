// File: tests/ReporterRegistrarTest_1083.cpp
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>
#include <type_traits>

//
// Minimal, test-local doubles that match the provided interface
// and the observable external interaction used by ReporterRegistrar.
//
namespace Catch {

// External collaborator we will intercept: accepts a (polymorphic) factory.
struct ReporterFactoryBase {
    virtual ~ReporterFactoryBase() = default;
};

template <typename T>
struct ReporterFactory : ReporterFactoryBase {};

// Test-local substitute for Detail::make_unique used by the registrar
namespace Detail {
    template <typename U, typename... Args>
    std::unique_ptr<U> make_unique(Args&&... args) {
        return std::unique_ptr<U>(new U(std::forward<Args>(args)...));
    }
}

// === Test spy state for calls to registerReporterImpl ===
static int g_register_calls = 0;
static std::vector<std::string> g_names;
static std::vector<std::unique_ptr<ReporterFactoryBase>> g_factories;

inline void reset_register_spy() {
    g_register_calls = 0;
    g_names.clear();
    g_factories.clear();
}

// This is the external interaction invoked by ReporterRegistrar's ctor.
// We provide a test-local definition to observe the call.
inline void registerReporterImpl(std::string const& name,
                                 std::unique_ptr<ReporterFactoryBase> factory) {
    ++g_register_calls;
    g_names.push_back(name);
    g_factories.push_back(std::move(factory)); // keep ownership so RTTI stays valid
}

// === Class under test (from the provided partial code) ===
template <typename T>
class ReporterRegistrar {
public:
    explicit ReporterRegistrar(std::string const& name) {
        registerReporterImpl(name, Detail::make_unique<ReporterFactory<T>>());
    }
};

} // namespace Catch

// Dummy reporter types for type-distinguishing checks
struct DummyReporterA {};
struct DummyReporterB {};

class ReporterRegistrarTest_1083 : public ::testing::Test {
protected:
    void SetUp() override { Catch::reset_register_spy(); }
};

// --- Tests ---

TEST_F(ReporterRegistrarTest_1083, RegistersWithGivenName_Normal_1083) {
    const std::string name = "dummy-reporter";
    {
        Catch::ReporterRegistrar<DummyReporterA> reg{name};
    }

    ASSERT_EQ(Catch::g_register_calls, 1);
    ASSERT_EQ(Catch::g_names.size(), 1u);
    EXPECT_EQ(Catch::g_names[0], name);

    ASSERT_EQ(Catch::g_factories.size(), 1u);
    // Factory should be for DummyReporterA
    auto* typed =
        dynamic_cast<Catch::ReporterFactory<DummyReporterA>*>(Catch::g_factories[0].get());
    EXPECT_NE(typed, nullptr);
}

TEST_F(ReporterRegistrarTest_1083, AllowsEmptyName_Boundary_1083) {
    const std::string empty_name = "";
    {
        Catch::ReporterRegistrar<DummyReporterA> reg{empty_name};
    }

    ASSERT_EQ(Catch::g_register_calls, 1);
    ASSERT_EQ(Catch::g_names.size(), 1u);
    EXPECT_EQ(Catch::g_names[0], empty_name);

    ASSERT_EQ(Catch::g_factories.size(), 1u);
    auto* typed =
        dynamic_cast<Catch::ReporterFactory<DummyReporterA>*>(Catch::g_factories[0].get());
    EXPECT_NE(typed, nullptr);
}

TEST_F(ReporterRegistrarTest_1083, MultipleRegistrations_CallCountAndTypes_1083) {
    {
        Catch::ReporterRegistrar<DummyReporterA> regA{"rep-A"};
        Catch::ReporterRegistrar<DummyReporterB> regB{"rep-B"};
    }

    ASSERT_EQ(Catch::g_register_calls, 2);
    ASSERT_EQ(Catch::g_names.size(), 2u);
    EXPECT_EQ(Catch::g_names[0], "rep-A");
    EXPECT_EQ(Catch::g_names[1], "rep-B");

    ASSERT_EQ(Catch::g_factories.size(), 2u);

    auto* typedA =
        dynamic_cast<Catch::ReporterFactory<DummyReporterA>*>(Catch::g_factories[0].get());
    auto* typedB =
        dynamic_cast<Catch::ReporterFactory<DummyReporterB>*>(Catch::g_factories[1].get());

    EXPECT_NE(typedA, nullptr);
    EXPECT_NE(typedB, nullptr);
}

