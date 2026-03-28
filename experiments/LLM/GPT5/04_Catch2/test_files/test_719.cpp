// File: tests/config_getProcessedReporterSpecs_719_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include "catch2/catch_config.hpp"  // Adjust include path as needed

// Compile-time verification that the function returns a const reference
// to std::vector<ProcessedReporterSpec>.
namespace {
template <typename T>
struct AlwaysFalse : std::false_type {};

static_assert(std::is_same<
                  decltype(std::declval<const Catch::Config>().getProcessedReporterSpecs()),
                  const std::vector<Catch::ProcessedReporterSpec>&>::value,
              "getProcessedReporterSpecs() must return const std::vector<ProcessedReporterSpec>&");
} // namespace

class Config_GetProcessedReporterSpecs_Test_719 : public ::testing::Test {
protected:
    // Use default-constructed Config to rely only on the public interface.
    Catch::Config cfg_;
};

// [Normal operation] Default-constructed Config should expose a valid (usually empty) vector.
// We only check observable state: size and that the reference is usable.
TEST_F(Config_GetProcessedReporterSpecs_Test_719, DefaultConstructed_IsUsable_719) {
    const auto& specs = cfg_.getProcessedReporterSpecs();
    // Observable behavior: calling size() is valid. Typical default is empty.
    // We do not assert specific contents beyond emptiness since the implementation is a black box.
    EXPECT_GE(specs.size(), 0u);
    // Access does not crash and provides a valid container interface.
    (void)specs.begin();
    (void)specs.end();
}

// [Interface contract] Multiple calls should return the same underlying reference for the same object.
TEST_F(Config_GetProcessedReporterSpecs_Test_719, ReturnsSameReferenceOnRepeatedCalls_719) {
    const auto* first_addr  = &cfg_.getProcessedReporterSpecs();
    const auto* second_addr = &cfg_.getProcessedReporterSpecs();
    EXPECT_EQ(first_addr, second_addr);
}

// [Boundary: object copy] Copying the Config should yield a different object whose reference
// is distinct, while observable contents should be equal at copy time (black-box check via size).
TEST_F(Config_GetProcessedReporterSpecs_Test_719, CopyHasIndependentObjectReference_AndEqualObservableSize_719) {
    const auto& original_vec = cfg_.getProcessedReporterSpecs();

    // Copy-construct a new Config from the original
    Catch::Config cfg_copy = cfg_;
    const auto& copy_vec = cfg_copy.getProcessedReporterSpecs();

    // Different objects -> references should not be the same address
    EXPECT_NE(&original_vec, &copy_vec);

    // Observable equivalence we can assert without peeking internals: sizes match at copy time
    EXPECT_EQ(original_vec.size(), copy_vec.size());
}

// [Const-correctness] Access through a const-qualified Config should still return a const reference.
TEST_F(Config_GetProcessedReporterSpecs_Test_719, ConstAccess_ReturnsConstReference_719) {
    const Catch::Config& const_cfg = cfg_;
    const auto& vec_ref = const_cfg.getProcessedReporterSpecs();

    // The following line should fail to compile if modification were possible.
    // vec_ref.clear(); // intentionally not compiled; we rely on the static_assert above.

    // We still perform a runtime check that we can read size() safely.
    EXPECT_GE(vec_ref.size(), 0u);
}

// [Reference lifetime while object is alive] A captured reference remains valid as long as the
// owning Config instance is alive. We can only check address stability + safe access.
TEST_F(Config_GetProcessedReporterSpecs_Test_719, ReferenceRemainsValidWhileConfigAlive_719) {
    const auto& ref_before = cfg_.getProcessedReporterSpecs();
    const auto* addr_before = &ref_before;

    // Interleave with other calls; we don't rely on or assert any internal mutation.
    (void)cfg_.getProcessedReporterSpecs();
    (void)cfg_.getProcessedReporterSpecs();

    const auto& ref_after = cfg_.getProcessedReporterSpecs();
    const auto* addr_after = &ref_after;

    EXPECT_EQ(addr_before, addr_after);
    EXPECT_GE(ref_after.size(), 0u);
}
