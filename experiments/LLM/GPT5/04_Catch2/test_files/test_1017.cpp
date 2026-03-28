// File: test_testregistry_getallinfos_1017.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <vector>

// We rely only on the public interface shown in the prompt.
namespace Catch {
    class TestCaseInfo;
    class TestRegistry {
    public:
        // As specified in the partial code:
        std::vector<TestCaseInfo*> const& getAllInfos() const;
    };
} // namespace Catch

// A small fixture to hold common utilities if needed later.
class TestRegistry_GetAllInfos_1017 : public ::testing::Test {
protected:
    // NOLINTNEXTLINE
    Catch::TestRegistry reg_; // Treat as black box; default-constructed instance.
};

// -------------------- Compile-time interface checks --------------------

// [Behavior] Method signature matches "const-ref returning const-qualified member function".
TEST_F(TestRegistry_GetAllInfos_1017, SignatureIsConstRef_1017) {
    using Returned =
        decltype(std::declval<const Catch::TestRegistry&>().getAllInfos());
    static_assert(std::is_same_v<Returned,
                  const std::vector<Catch::TestCaseInfo*>&>,
                  "getAllInfos() must return const std::vector<TestCaseInfo*>&");

    using PMF = const std::vector<Catch::TestCaseInfo*>& (Catch::TestRegistry::*)() const;
    static_assert(std::is_same_v<PMF, decltype(&Catch::TestRegistry::getAllInfos)>,
                  "getAllInfos() must be const-qualified with the expected return type");
    SUCCEED();
}

// -------------------- Runtime, observable-behavior tests --------------------

// [Behavior] Calling getAllInfos() on a default-constructed registry does not throw
// and returns a valid reference.
TEST_F(TestRegistry_GetAllInfos_1017, DefaultConstructed_NoThrowAndValidRef_1017) {
    EXPECT_NO_THROW({
        auto const& infos = reg_.getAllInfos();
        (void)infos.data(); // Access something benign to prove it's a valid container.
    });
}

// [Behavior] The returned reference is to the same underlying container across calls.
// (Reference identity stability)
TEST_F(TestRegistry_GetAllInfos_1017, ReturnsSameContainerAcrossCalls_1017) {
    auto const* first_addr  = std::addressof(reg_.getAllInfos());
    auto const* second_addr = std::addressof(reg_.getAllInfos());
    EXPECT_EQ(first_addr, second_addr);
}

// [Behavior] The returned reference is to a const container (cannot be mutated through it).
// (This is primarily compile-time verified; here we ensure read-only usage works.)
TEST_F(TestRegistry_GetAllInfos_1017, ReturnedContainerIsConst_ViewOnly_1017) {
    auto const& infos = reg_.getAllInfos();
    // We can observe size() but not mutate via the reference.
    // (Attempting to call infos.push_back(...) would fail to compile.)
    (void)infos.size();
    SUCCEED();
}

// [Behavior] Method is callable on a const-qualified object and returns a valid reference.
TEST_F(TestRegistry_GetAllInfos_1017, CallableOnConstObject_1017) {
    const Catch::TestRegistry& cref = reg_;
    auto const& infos = cref.getAllInfos();
    (void)infos.size();
    SUCCEED();
}

// [Behavior] Multiple reads do not implicitly change the view (idempotent read).
TEST_F(TestRegistry_GetAllInfos_1017, MultipleReadsAreIdempotent_1017) {
    auto const& a = reg_.getAllInfos();
    auto size_a = a.size();

    auto const& b = reg_.getAllInfos();
    auto size_b = b.size();

    EXPECT_EQ(size_a, size_b);
}
