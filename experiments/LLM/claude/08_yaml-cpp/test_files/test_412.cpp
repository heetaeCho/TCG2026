#include <gtest/gtest.h>

// Include the header under test
#include "contrib/dragonbox.h"

// We need to understand the expected interface:
// - dummy<T> is a tag type wrapping a policy
// - detector_default_pair_list<...> holds detector-default pairs
// - Each pair has a kind_detector that is callable with dummy<Policy>
// - check_policy_validity returns true if any detector matches the policy

// Since we're dealing with template metaprogramming constructs that are part of
// the dragonbox implementation, we need to define test types that conform to
// the expected interface.

namespace YAML {
namespace jkj {
namespace dragonbox {
namespace detail {

// Test policy types
struct TestPolicyA {};
struct TestPolicyB {};
struct TestPolicyC {};

// A detector that always returns true for any policy
struct AlwaysTrueDetector {
    template <class T>
    constexpr bool operator()(dummy<T>) const noexcept {
        return true;
    }
};

// A detector that always returns false for any policy
struct AlwaysFalseDetector {
    template <class T>
    constexpr bool operator()(dummy<T>) const noexcept {
        return false;
    }
};

// A detector that returns true only for TestPolicyA
struct DetectorForA {
    constexpr bool operator()(dummy<TestPolicyA>) const noexcept {
        return true;
    }
    template <class T>
    constexpr bool operator()(dummy<T>) const noexcept {
        return false;
    }
};

// A detector that returns true only for TestPolicyB
struct DetectorForB {
    constexpr bool operator()(dummy<TestPolicyB>) const noexcept {
        return true;
    }
    template <class T>
    constexpr bool operator()(dummy<T>) const noexcept {
        return false;
    }
};

// Default type (not really used in detection logic, but needed for pair structure)
struct DefaultTypeX {};
struct DefaultTypeY {};

// Detector-default pairs conforming to the expected interface
struct PairAlwaysTrue {
    using kind_detector = AlwaysTrueDetector;
    using default_type = DefaultTypeX;
};

struct PairAlwaysFalse {
    using kind_detector = AlwaysFalseDetector;
    using default_type = DefaultTypeX;
};

struct PairDetectsA {
    using kind_detector = DetectorForA;
    using default_type = DefaultTypeX;
};

struct PairDetectsB {
    using kind_detector = DetectorForB;
    using default_type = DefaultTypeY;
};

} // namespace detail
} // namespace dragonbox
} // namespace jkj
} // namespace YAML

using namespace YAML::jkj::dragonbox::detail;

class CheckPolicyValidityTest_412 : public ::testing::Test {};

// Test: Single detector that always matches
TEST_F(CheckPolicyValidityTest_412, SingleAlwaysTrueDetector_ReturnsTrue_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyA>{},
        detector_default_pair_list<PairAlwaysTrue>{});
    EXPECT_TRUE(result);
}

// Test: Single detector that never matches
TEST_F(CheckPolicyValidityTest_412, SingleAlwaysFalseDetector_ReturnsFalse_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyA>{},
        detector_default_pair_list<PairAlwaysFalse>{});
    EXPECT_FALSE(result);
}

// Test: First detector matches in a list of two
TEST_F(CheckPolicyValidityTest_412, FirstDetectorMatchesInList_ReturnsTrue_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyA>{},
        detector_default_pair_list<PairDetectsA, PairAlwaysFalse>{});
    EXPECT_TRUE(result);
}

// Test: Second detector matches in a list of two
TEST_F(CheckPolicyValidityTest_412, SecondDetectorMatchesInList_ReturnsTrue_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyB>{},
        detector_default_pair_list<PairAlwaysFalse, PairDetectsB>{});
    EXPECT_TRUE(result);
}

// Test: No detector matches in a list of two
TEST_F(CheckPolicyValidityTest_412, NoDetectorMatchesInList_ReturnsFalse_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyC>{},
        detector_default_pair_list<PairDetectsA, PairDetectsB>{});
    EXPECT_FALSE(result);
}

// Test: Multiple detectors, all match
TEST_F(CheckPolicyValidityTest_412, AllDetectorsMatch_ReturnsTrue_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyA>{},
        detector_default_pair_list<PairAlwaysTrue, PairAlwaysTrue>{});
    EXPECT_TRUE(result);
}

// Test: Three detectors, only last matches
TEST_F(CheckPolicyValidityTest_412, ThreeDetectorsLastMatches_ReturnsTrue_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyB>{},
        detector_default_pair_list<PairDetectsA, PairAlwaysFalse, PairDetectsB>{});
    EXPECT_TRUE(result);
}

// Test: Three detectors, none match
TEST_F(CheckPolicyValidityTest_412, ThreeDetectorsNoneMatch_ReturnsFalse_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyC>{},
        detector_default_pair_list<PairDetectsA, PairAlwaysFalse, PairDetectsB>{});
    EXPECT_FALSE(result);
}

// Test: Constexpr evaluation works at compile time
TEST_F(CheckPolicyValidityTest_412, ConstexprEvaluation_412) {
    static_assert(
        check_policy_validity(
            dummy<TestPolicyA>{},
            detector_default_pair_list<PairDetectsA>{}),
        "PolicyA should be valid with DetectsA");
    static_assert(
        !check_policy_validity(
            dummy<TestPolicyC>{},
            detector_default_pair_list<PairDetectsA, PairDetectsB>{}),
        "PolicyC should not be valid with DetectsA and DetectsB");
    SUCCEED();
}

// Test: Mixed true/false with multiple pairs
TEST_F(CheckPolicyValidityTest_412, MixedDetectorsFalseTrue_ReturnsTrue_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyA>{},
        detector_default_pair_list<PairAlwaysFalse, PairDetectsA>{});
    EXPECT_TRUE(result);
}

// Test: Mixed true/false with first true
TEST_F(CheckPolicyValidityTest_412, MixedDetectorsTrueFalse_ReturnsTrue_412) {
    constexpr bool result = check_policy_validity(
        dummy<TestPolicyA>{},
        detector_default_pair_list<PairDetectsA, PairAlwaysFalse>{});
    EXPECT_TRUE(result);
}
