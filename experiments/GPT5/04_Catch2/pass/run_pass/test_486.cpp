// tests/generate_random_seed_tests_486.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include <ctime>
#include <type_traits>

// The public interface we test against (no internal details).
namespace Catch {
    enum class GenerateFrom { Time = 0, RandomDevice = 1, Default = 2 };
    std::uint32_t generateRandomSeed(GenerateFrom from);
}

class GenerateRandomSeedTest_486 : public ::testing::Test {};

// Ensures the function's return type remains std::uint32_t
TEST_F(GenerateRandomSeedTest_486, ReturnTypeIsUint32_486) {
    static_assert(std::is_same<decltype(Catch::generateRandomSeed(Catch::GenerateFrom::Time)), std::uint32_t>::value,
                  "generateRandomSeed must return std::uint32_t");
    SUCCEED(); // Compile-time check above; keep the test counted at runtime.
}

// Time-based generation should return a value equal to the current UNIX time
// captured during the call window (inclusive bounds).
TEST_F(GenerateRandomSeedTest_486, TimeBasedSeedWithinCallWindow_486) {
    std::time_t before = std::time(nullptr);
    const std::uint32_t seed = Catch::generateRandomSeed(Catch::GenerateFrom::Time);
    std::time_t after = std::time(nullptr);

    // The seed should be representable as time_t within our call window
    // (use inclusive bounds to avoid flakiness at second boundaries).
    ASSERT_LE(static_cast<std::time_t>(seed), after);
    ASSERT_GE(static_cast<std::time_t>(seed), before);
}

// RandomDevice-based generation should succeed without throwing and produce some value.
TEST_F(GenerateRandomSeedTest_486, RandomDeviceReturnsValue_NoThrow_486) {
    // Primary observable behavior: it returns a value and does not throw.
    EXPECT_NO_THROW({
        (void)Catch::generateRandomSeed(Catch::GenerateFrom::RandomDevice);
    });
}

// Default generation should also succeed without throwing and return a value.
TEST_F(GenerateRandomSeedTest_486, DefaultReturnsValue_NoThrow_486) {
    EXPECT_NO_THROW({
        (void)Catch::generateRandomSeed(Catch::GenerateFrom::Default);
    });
}

// Passing an invalid enum should trigger an observable error (exception).
// We do not assert on the exception type to avoid coupling to internals.
TEST_F(GenerateRandomSeedTest_486, InvalidEnumTriggersError_486) {
    // Use a clearly out-of-range value.
    auto invalid = static_cast<Catch::GenerateFrom>(999);
    ASSERT_ANY_THROW({
        (void)Catch::generateRandomSeed(invalid);
    });
}
