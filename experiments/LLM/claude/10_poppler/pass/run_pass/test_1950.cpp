#include <gtest/gtest.h>
#include <optional>

// Since hasValidResult is a static template function that calls isValidResult,
// we need to provide types and corresponding isValidResult overloads to test it.

// Define test result types
struct ValidResult {
    int value;
};

struct InvalidResult {
    int value;
};

struct AlwaysValidResult {};
struct AlwaysInvalidResult {};

// Define isValidResult overloads for our test types
static bool isValidResult(const ValidResult &r)
{
    return r.value > 0;
}

static bool isValidResult(const InvalidResult &r)
{
    return false;
}

static bool isValidResult(const AlwaysValidResult &)
{
    return true;
}

static bool isValidResult(const AlwaysInvalidResult &)
{
    return false;
}

// Include the template function under test
// Reproducing the template as given in the prompt since it's a header-level template
template<typename Result>
static bool hasValidResult(const std::optional<Result> &result)
{
    if (!result) {
        return false;
    }
    return isValidResult(result.value());
}

// Test fixture
class HasValidResultTest_1950 : public ::testing::Test {
protected:
};

// Test: nullopt (empty optional) should return false
TEST_F(HasValidResultTest_1950, NulloptReturnsFalse_ValidResult_1950)
{
    std::optional<ValidResult> empty = std::nullopt;
    EXPECT_FALSE(hasValidResult(empty));
}

TEST_F(HasValidResultTest_1950, NulloptReturnsFalse_InvalidResult_1950)
{
    std::optional<InvalidResult> empty = std::nullopt;
    EXPECT_FALSE(hasValidResult(empty));
}

TEST_F(HasValidResultTest_1950, NulloptReturnsFalse_AlwaysValid_1950)
{
    std::optional<AlwaysValidResult> empty = std::nullopt;
    EXPECT_FALSE(hasValidResult(empty));
}

TEST_F(HasValidResultTest_1950, NulloptReturnsFalse_AlwaysInvalid_1950)
{
    std::optional<AlwaysInvalidResult> empty = std::nullopt;
    EXPECT_FALSE(hasValidResult(empty));
}

// Test: optional with value where isValidResult returns true
TEST_F(HasValidResultTest_1950, ValidResultReturnsTrue_1950)
{
    std::optional<ValidResult> opt = ValidResult{42};
    EXPECT_TRUE(hasValidResult(opt));
}

// Test: optional with value where isValidResult returns false
TEST_F(HasValidResultTest_1950, InvalidValueReturnsFalse_1950)
{
    std::optional<ValidResult> opt = ValidResult{-1};
    EXPECT_FALSE(hasValidResult(opt));
}

// Test: optional with value where isValidResult always returns false
TEST_F(HasValidResultTest_1950, AlwaysInvalidReturnsFalse_1950)
{
    std::optional<InvalidResult> opt = InvalidResult{100};
    EXPECT_FALSE(hasValidResult(opt));
}

// Test: AlwaysValidResult with value returns true
TEST_F(HasValidResultTest_1950, AlwaysValidReturnsTrue_1950)
{
    std::optional<AlwaysValidResult> opt = AlwaysValidResult{};
    EXPECT_TRUE(hasValidResult(opt));
}

// Test: AlwaysInvalidResult with value returns false
TEST_F(HasValidResultTest_1950, AlwaysInvalidWithValueReturnsFalse_1950)
{
    std::optional<AlwaysInvalidResult> opt = AlwaysInvalidResult{};
    EXPECT_FALSE(hasValidResult(opt));
}

// Boundary: ValidResult with value == 0 (boundary for our isValidResult: value > 0)
TEST_F(HasValidResultTest_1950, BoundaryZeroValueReturnsFalse_1950)
{
    std::optional<ValidResult> opt = ValidResult{0};
    EXPECT_FALSE(hasValidResult(opt));
}

// Boundary: ValidResult with value == 1 (just above boundary)
TEST_F(HasValidResultTest_1950, BoundaryOneValueReturnsTrue_1950)
{
    std::optional<ValidResult> opt = ValidResult{1};
    EXPECT_TRUE(hasValidResult(opt));
}

// Test: default-constructed optional is empty
TEST_F(HasValidResultTest_1950, DefaultConstructedOptionalReturnsFalse_1950)
{
    std::optional<ValidResult> opt;
    EXPECT_FALSE(hasValidResult(opt));
}

// Test: const reference to optional
TEST_F(HasValidResultTest_1950, ConstOptionalWithValidValue_1950)
{
    const std::optional<AlwaysValidResult> opt = AlwaysValidResult{};
    EXPECT_TRUE(hasValidResult(opt));
}

TEST_F(HasValidResultTest_1950, ConstOptionalEmpty_1950)
{
    const std::optional<AlwaysValidResult> opt = std::nullopt;
    EXPECT_FALSE(hasValidResult(opt));
}
