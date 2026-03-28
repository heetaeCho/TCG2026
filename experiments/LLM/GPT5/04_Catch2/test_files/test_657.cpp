// TEST_ID: 657

#include <gtest/gtest.h>

// Include the public interface under test
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::BoundFlagRef;
using Catch::Clara::Detail::ParseResultType; // Only for compile/reference if needed
// ParserResult is expected to be defined by the included headers (e.g., BasicResult<ParseResultType>)

class BoundFlagRefTest_657 : public ::testing::Test {
protected:
    bool flag_{false}; // fresh per test via fixture re-instantiation
    BoundFlagRef makeRef() { return BoundFlagRef(flag_); }
};

// Normal operation: setting true updates the referenced flag and reports success.
TEST_F(BoundFlagRefTest_657, SetFlagTrue_SetsRefAndReturnsOk_657) {
    auto ref = makeRef();
    ASSERT_FALSE(flag_) << "Precondition: flag_ should start false";

    auto result = ref.setFlag(true);

    EXPECT_TRUE(flag_) << "setFlag(true) must update the referenced bool to true";
    EXPECT_TRUE(static_cast<bool>(result)) << "Successful result should be truthy via operator bool()";
    // Empty error message on success (observable via public API)
    EXPECT_TRUE(result.errorMessage().empty());
}

// Normal operation: setting false updates the referenced flag and reports success.
TEST_F(BoundFlagRefTest_657, SetFlagFalse_SetsRefAndReturnsOk_657) {
    flag_ = true; // start from true to observe change to false
    auto ref = makeRef();

    auto result = ref.setFlag(false);

    EXPECT_FALSE(flag_) << "setFlag(false) must update the referenced bool to false";
    EXPECT_TRUE(static_cast<bool>(result)) << "Successful result should be truthy via operator bool()";
    EXPECT_TRUE(result.errorMessage().empty());
}

// Boundary/Idempotency: setting to the same value is allowed and still reports success.
TEST_F(BoundFlagRefTest_657, IdempotentWhenSettingSameValue_657) {
    flag_ = true;
    auto ref = makeRef();

    auto result = ref.setFlag(true);

    EXPECT_TRUE(flag_) << "The referenced bool should remain true when setting true again";
    EXPECT_TRUE(static_cast<bool>(result)) << "Even idempotent set should be considered successful";
    EXPECT_TRUE(result.errorMessage().empty());
}

// Additional observable contract: consecutive calls can flip the value reliably and each call succeeds.
TEST_F(BoundFlagRefTest_657, ConsecutiveCallsFlipAndSucceed_657) {
    auto ref = makeRef();

    auto r1 = ref.setFlag(true);
    EXPECT_TRUE(flag_);
    EXPECT_TRUE(static_cast<bool>(r1));
    EXPECT_TRUE(r1.errorMessage().empty());

    auto r2 = ref.setFlag(false);
    EXPECT_FALSE(flag_);
    EXPECT_TRUE(static_cast<bool>(r2));
    EXPECT_TRUE(r2.errorMessage().empty());
}
