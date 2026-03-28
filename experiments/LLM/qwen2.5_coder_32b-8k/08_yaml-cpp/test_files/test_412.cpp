#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail;



// Mock classes and functions if needed

template <class Policy>

struct DummyPolicy {};



template <class KindDetector, class DefaultValue>

struct DetectorDefaultPair {

    using kind_detector = KindDetector;

};



template <class... DetectorDefaultPairs>

struct DetectorDefaultPairList {};



template <class T>

struct AlwaysTrueDetector {

    bool operator()(T) const noexcept { return true; }

};



template <class T>

struct AlwaysFalseDetector {

    bool operator()(T) const noexcept { return false; }

};



// Test fixture

class DragonboxPolicyValidityTest_412 : public ::testing::Test {

protected:

    using Policy = DummyPolicy<void>;

    using TruePair = DetectorDefaultPair<AlwaysTrueDetector<dummy<Policy>>, void>;

    using FalsePair = DetectorDefaultPair<AlwaysFalseDetector<dummy<Policy>>, void>;

};



// Test cases

TEST_F(DragonboxPolicyValidityTest_412, SingleTrueDetector_412) {

    constexpr auto result = check_policy_validity(

        dummy<Policy>{},

        detector_default_pair_list<TruePair>{}

    );

    EXPECT_TRUE(result);

}



TEST_F(DragonboxPolicyValidityTest_412, SingleFalseDetector_412) {

    constexpr auto result = check_policy_validity(

        dummy<Policy>{},

        detector_default_pair_list<FalsePair>{}

    );

    EXPECT_FALSE(result);

}



TEST_F(DragonboxPolicyValidityTest_412, MultipleDetectorsFirstTrue_412) {

    constexpr auto result = check_policy_validity(

        dummy<Policy>{},

        detector_default_pair_list<TruePair, FalsePair>{}

    );

    EXPECT_TRUE(result);

}



TEST_F(DragonboxPolicyValidityTest_412, MultipleDetectorsAllFalse_412) {

    constexpr auto result = check_policy_validity(

        dummy<Policy>{},

        detector_default_pair_list<FalsePair, FalsePair>{}

    );

    EXPECT_FALSE(result);

}



TEST_F(DragonboxPolicyValidityTest_412, MultipleDetectorsLastTrue_412) {

    constexpr auto result = check_policy_validity(

        dummy<Policy>{},

        detector_default_pair_list<FalsePair, TruePair>{}

    );

    EXPECT_TRUE(result);

}
