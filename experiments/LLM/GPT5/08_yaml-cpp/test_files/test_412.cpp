// File: ./TestProjects/yaml-cpp/test/dragonbox_check_policy_validity_test_412.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::check_policy_validity;
using YAML::jkj::dragonbox::detail::detector_default_pair_list;
using YAML::jkj::dragonbox::detail::dummy;

struct Policy412 {};

// Detector-default-pair types with nested kind_detector that is default-constructible
// and callable as: kind_detector{}(dummy<Policy>{}) -> bool.
struct PairAlwaysTrue_412 {
  static inline int calls = 0;

  struct kind_detector {
    template <class P>
    bool operator()(dummy<P>) const noexcept {
      ++PairAlwaysTrue_412::calls;
      return true;
    }
  };
};

struct PairAlwaysFalse_412 {
  static inline int calls = 0;

  struct kind_detector {
    template <class P>
    bool operator()(dummy<P>) const noexcept {
      ++PairAlwaysFalse_412::calls;
      return false;
    }
  };
};

struct PairTrueAfterFalse_412 {
  static inline int calls = 0;

  struct kind_detector {
    template <class P>
    bool operator()(dummy<P>) const noexcept {
      ++PairTrueAfterFalse_412::calls;
      return true;
    }
  };
};

class CheckPolicyValidityTest_412 : public ::testing::Test {
 protected:
  void SetUp() override {
    PairAlwaysTrue_412::calls = 0;
    PairAlwaysFalse_412::calls = 0;
    PairTrueAfterFalse_412::calls = 0;
  }
};

TEST_F(CheckPolicyValidityTest_412, ReturnsTrueWhenFirstDetectorMatches_412) {
  const bool result = check_policy_validity(
      dummy<Policy412>{},
      detector_default_pair_list<PairAlwaysTrue_412, PairAlwaysFalse_412>{});

  EXPECT_TRUE(result);
  EXPECT_EQ(PairAlwaysTrue_412::calls, 1);
  // Observable short-circuit: if the first detector returns true, the second should not run.
  EXPECT_EQ(PairAlwaysFalse_412::calls, 0);
}

TEST_F(CheckPolicyValidityTest_412, EvaluatesNextDetectorWhenFirstDoesNotMatch_412) {
  const bool result = check_policy_validity(
      dummy<Policy412>{},
      detector_default_pair_list<PairAlwaysFalse_412, PairTrueAfterFalse_412>{});

  EXPECT_TRUE(result);
  EXPECT_EQ(PairAlwaysFalse_412::calls, 1);
  EXPECT_EQ(PairTrueAfterFalse_412::calls, 1);
}

TEST_F(CheckPolicyValidityTest_412, ReturnsFalseWhenNoDetectorMatches_412) {
  const bool result = check_policy_validity(
      dummy<Policy412>{},
      detector_default_pair_list<PairAlwaysFalse_412, PairAlwaysFalse_412>{});

  EXPECT_FALSE(result);
  // Two distinct occurrences in the list may each be evaluated; we only assert the observable
  // final result and that at least one evaluation happened.
  EXPECT_GE(PairAlwaysFalse_412::calls, 1);
}

TEST_F(CheckPolicyValidityTest_412, SingleElementListTrue_412) {
  const bool result =
      check_policy_validity(dummy<Policy412>{}, detector_default_pair_list<PairAlwaysTrue_412>{});

  EXPECT_TRUE(result);
  EXPECT_EQ(PairAlwaysTrue_412::calls, 1);
}

TEST_F(CheckPolicyValidityTest_412, SingleElementListFalse_412) {
  const bool result =
      check_policy_validity(dummy<Policy412>{}, detector_default_pair_list<PairAlwaysFalse_412>{});

  EXPECT_FALSE(result);
  EXPECT_EQ(PairAlwaysFalse_412::calls, 1);
}

TEST_F(CheckPolicyValidityTest_412, IsNoexceptForGivenInputs_412) {
  static_assert(
      noexcept(check_policy_validity(dummy<Policy412>{},
                                     detector_default_pair_list<PairAlwaysFalse_412,
                                                                PairAlwaysTrue_412>{})),
      "check_policy_validity should be noexcept for these inputs");

  SUCCEED();
}

TEST_F(CheckPolicyValidityTest_412, WorksInConstantEvaluation_412) {
  // Uses detector types without observable state to allow constexpr evaluation.
  struct ConstexprFalsePair {
    struct kind_detector {
      template <class P>
      constexpr bool operator()(dummy<P>) const noexcept {
        return false;
      }
    };
  };
  struct ConstexprTruePair {
    struct kind_detector {
      template <class P>
      constexpr bool operator()(dummy<P>) const noexcept {
        return true;
      }
    };
  };

  static_assert(
      check_policy_validity(dummy<Policy412>{},
                            detector_default_pair_list<ConstexprFalsePair, ConstexprTruePair>{}),
      "Expected constexpr evaluation to produce true when a later detector matches");

  static_assert(
      !check_policy_validity(dummy<Policy412>{}, detector_default_pair_list<ConstexprFalsePair>{}),
      "Expected constexpr evaluation to produce false when no detector matches");

  SUCCEED();
}

}  // namespace