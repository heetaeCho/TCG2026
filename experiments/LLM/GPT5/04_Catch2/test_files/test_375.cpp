// File: convert_into_optional_tests_375.cpp

#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <utility>

// ---- Minimal scaffolding to make the interface testable (dependencies) ----
#define CATCH_MOVE(x) std::move(x)
#define CLARA_CONFIG_OPTIONAL_TYPE std::optional

namespace Catch { namespace Clara { namespace Detail {

// A minimal ParserResult with boolean semantics, as required by the interface.
struct ParserResult {
    bool ok = false;
    explicit operator bool() const { return ok; }
};

// The function-under-test (copied exactly from the provided snippet).
template <typename T>
auto convertInto(std::string const& source, CLARA_CONFIG_OPTIONAL_TYPE<T>& target) -> ParserResult {
    T temp;
    auto result = convertInto(source, temp);  // calls the collaborator overload
    if (result)
        target = CATCH_MOVE(temp);
    return result;
}

// --- Test collaborator type + overload ---
// We provide a simple type and an overload of convertInto(source, T&)
// to act as the external collaborator that the function-under-test invokes.
struct Box {
    std::string s;
    bool operator==(const Box& other) const { return s == other.s; }
};

// Collaborator behavior (observable to our tests only via the optional target):
// * On source == "<fail>", parsing fails.
// * Otherwise, it writes the source into Box::s and succeeds.
inline auto convertInto(std::string const& source, Box& out) -> ParserResult {
    if (source == "<fail>") return {false};
    out.s = source;
    return {true};
}

}}} // namespace Catch::Clara::Detail

using namespace Catch::Clara::Detail;

// ------------------------- Test Fixture -------------------------
class ConvertIntoOptionalTest_375 : public ::testing::Test {};

// --------------------------- Tests ------------------------------

// Normal operation: successful parse assigns the optional target.
TEST_F(ConvertIntoOptionalTest_375, AssignsTargetOnSuccess_375) {
    CLARA_CONFIG_OPTIONAL_TYPE<Box> target; // disengaged
    ParserResult result = convertInto(std::string("hello"), target);

    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_TRUE(target.has_value());
    EXPECT_EQ(target->s, "hello");
}

// Boundary: target already engaged, success should overwrite it (via move/assign).
TEST_F(ConvertIntoOptionalTest_375, OverwritesExistingValueOnSuccess_375) {
    CLARA_CONFIG_OPTIONAL_TYPE<Box> target{Box{"old"}};
    ParserResult result = convertInto(std::string("new"), target);

    EXPECT_TRUE(static_cast<bool>(result));
    ASSERT_TRUE(target.has_value());
    EXPECT_EQ(target->s, "new"); // observable overwrite
}

// Error case: parse fails; disengaged target remains disengaged and unmodified.
TEST_F(ConvertIntoOptionalTest_375, LeavesDisengagedTargetUnchangedOnFailure_375) {
    CLARA_CONFIG_OPTIONAL_TYPE<Box> target; // disengaged
    ParserResult result = convertInto(std::string("<fail>"), target);

    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_FALSE(target.has_value());
}

// Error case: parse fails; an already-engaged target remains unchanged.
TEST_F(ConvertIntoOptionalTest_375, LeavesEngagedTargetUnchangedOnFailure_375) {
    CLARA_CONFIG_OPTIONAL_TYPE<Box> target{Box{"keep"}};
    ParserResult result = convertInto(std::string("<fail>"), target);

    EXPECT_FALSE(static_cast<bool>(result));
    ASSERT_TRUE(target.has_value());
    EXPECT_EQ(target->s, "keep"); // unchanged
}

// Sanity: the returned ParserResult reflects the collaborator’s outcome.
TEST_F(ConvertIntoOptionalTest_375, ReturnsUnderlyingResult_375) {
    CLARA_CONFIG_OPTIONAL_TYPE<Box> t1, t2;

    ParserResult ok = convertInto(std::string("ok"), t1);
    EXPECT_TRUE(static_cast<bool>(ok));
    EXPECT_TRUE(t1.has_value());

    ParserResult fail = convertInto(std::string("<fail>"), t2);
    EXPECT_FALSE(static_cast<bool>(fail));
    EXPECT_FALSE(t2.has_value());
}
