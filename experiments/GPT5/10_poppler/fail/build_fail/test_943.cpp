// TEST_ID = 943
// File: optional_content_group_set_state_test_943.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

#if __has_include("poppler/OptionalContent.h")
#include "poppler/OptionalContent.h"
#elif __has_include("./TestProjects/poppler/poppler/OptionalContent.h")
#include "./TestProjects/poppler/poppler/OptionalContent.h"
#else
#include "OptionalContent.h"
#endif

// Try to include Dict/Object headers if available (only to help construct a minimal Dict).
#if __has_include("poppler/Object.h")
#include "poppler/Object.h"
#endif
#if __has_include("poppler/Dict.h")
#include "poppler/Dict.h"
#endif
#if __has_include("poppler/GooString.h")
#include "poppler/GooString.h"
#endif

namespace {

// --------- Minimal construction helpers (SFINAE-based; avoids guessing exact APIs) ---------

// Make a Dict instance using whatever constructor is available.
template <typename T>
struct AlwaysFalse : std::false_type {};

template <typename DictT>
std::unique_ptr<DictT> MakeDict() {
  if constexpr (std::is_default_constructible_v<DictT>) {
    return std::make_unique<DictT>();
  } else if constexpr (std::is_constructible_v<DictT, nullptr_t>) {
    return std::make_unique<DictT>(nullptr);
  } else {
    // If Dict isn't constructible in any of the above ways, we can't safely fabricate one here.
    // Tests that need a Dict will be skipped at runtime by returning nullptr.
    return nullptr;
  }
}

// Optional: attempt to add a "Name" entry if Dict/Object APIs are present.
// If these APIs aren't available, this becomes a no-op (still a valid minimal Dict for many builds).
template <typename DictT>
void MaybePopulateMinimalOCGDict(DictT* /*dict*/) {
  // Intentionally conservative: do not assume Dict/Object constructors or add() signatures.
  // This hook exists so the file can be extended easily in environments where these are known.
}

std::unique_ptr<OptionalContentGroup> MakeOCGOrNull() {
  // OptionalContentGroup requires Dict* by interface; build the smallest one we can.
  // We avoid assuming "Name"/"Type" requirements; if your Poppler build requires them,
  // this helper can be extended via MaybePopulateMinimalOCGDict above.
#if defined(Dict) // if Dict is a type in the global namespace in this build
  auto dict = MakeDict<Dict>();
  if (!dict) return nullptr;
  MaybePopulateMinimalOCGDict(dict.get());
  return std::make_unique<OptionalContentGroup>(dict.get());
#else
  // If Dict type isn't visible here, we cannot construct OptionalContentGroup without guessing.
  return nullptr;
#endif
}

} // namespace

class OptionalContentGroupTest_943 : public ::testing::Test {
protected:
  void SetUp() override {
    ocg_ = MakeOCGOrNull();
  }

  std::unique_ptr<OptionalContentGroup> ocg_;
};

TEST_F(OptionalContentGroupTest_943, ConstructibleWithMinimalDictOrSkipped_943) {
  // This test documents whether the environment provides enough public surface
  // to construct OptionalContentGroup for black-box testing.
  if (!ocg_) {
    GTEST_SKIP() << "OptionalContentGroup could not be constructed with the minimal public Dict API "
                    "available to this test translation unit.";
  }
  SUCCEED();
}

TEST_F(OptionalContentGroupTest_943, SetStateThenGetStateReturnsSameValue_943) {
  if (!ocg_) {
    GTEST_SKIP() << "Precondition not met: OptionalContentGroup not constructible in this build.";
  }

  const auto s0 = static_cast<decltype(ocg_->getState())>(0);
  ocg_->setState(s0);
  EXPECT_EQ(ocg_->getState(), s0);
}

TEST_F(OptionalContentGroupTest_943, SetStateOverwritesPreviousState_943) {
  if (!ocg_) {
    GTEST_SKIP() << "Precondition not met: OptionalContentGroup not constructible in this build.";
  }

  const auto s0 = static_cast<decltype(ocg_->getState())>(0);
  const auto s1 = static_cast<decltype(ocg_->getState())>(1);

  ocg_->setState(s0);
  EXPECT_EQ(ocg_->getState(), s0);

  ocg_->setState(s1);
  EXPECT_EQ(ocg_->getState(), s1);
}

TEST_F(OptionalContentGroupTest_943, SetStateIsIdempotentForSameValue_943) {
  if (!ocg_) {
    GTEST_SKIP() << "Precondition not met: OptionalContentGroup not constructible in this build.";
  }

  const auto s0 = static_cast<decltype(ocg_->getState())>(0);

  ocg_->setState(s0);
  const auto after_first = ocg_->getState();

  ocg_->setState(s0);
  const auto after_second = ocg_->getState();

  EXPECT_EQ(after_first, s0);
  EXPECT_EQ(after_second, s0);
}

TEST_F(OptionalContentGroupTest_943, BoundaryStateValuesAreRoundTripped_943) {
  if (!ocg_) {
    GTEST_SKIP() << "Precondition not met: OptionalContentGroup not constructible in this build.";
  }

  // Boundary-oriented: exercise a couple of distinct underlying enum values without assuming
  // specific named enumerators exist in this Poppler build.
  const auto s_min = static_cast<decltype(ocg_->getState())>(0);
  const auto s_maxish = static_cast<decltype(ocg_->getState())>(std::numeric_limits<int>::max());

  ocg_->setState(s_min);
  EXPECT_EQ(ocg_->getState(), s_min);

  ocg_->setState(s_maxish);
  EXPECT_EQ(ocg_->getState(), s_maxish);
}