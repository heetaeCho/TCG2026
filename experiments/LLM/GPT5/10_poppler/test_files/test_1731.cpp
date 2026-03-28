// CairoOutputDev_setLogicalStructure_1731_test.cc
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the real header from the codebase.
#include "CairoOutputDev.h"

namespace {

class CairoOutputDevTest_1731 : public ::testing::Test {};

TEST_F(CairoOutputDevTest_1731, SignatureIsVoidAndTakesBool_1731) {
  // Compile-time verification of the public interface (no behavior inference).
  using MethodPtr = decltype(&CairoOutputDev::setLogicalStructure);
  static_assert(std::is_same_v<MethodPtr, void (CairoOutputDev::*)(bool)>,
                "CairoOutputDev::setLogicalStructure must be: void(bool)");
}

TEST_F(CairoOutputDevTest_1731, AcceptsTrueAndDoesNotThrow_1731) {
  CairoOutputDev dev;

  EXPECT_NO_THROW(dev.setLogicalStructure(true));
}

TEST_F(CairoOutputDevTest_1731, AcceptsFalseAndDoesNotThrow_1731) {
  CairoOutputDev dev;

  EXPECT_NO_THROW(dev.setLogicalStructure(false));
}

TEST_F(CairoOutputDevTest_1731, CanBeCalledRepeatedlyIdempotentInTermsOfStability_1731) {
  CairoOutputDev dev;

  // We cannot inspect internal state (no getters; protected/private state is off-limits),
  // so we validate only observable behavior: the calls are well-formed and stable.
  EXPECT_NO_THROW(dev.setLogicalStructure(true));
  EXPECT_NO_THROW(dev.setLogicalStructure(true));
  EXPECT_NO_THROW(dev.setLogicalStructure(false));
  EXPECT_NO_THROW(dev.setLogicalStructure(false));
  EXPECT_NO_THROW(dev.setLogicalStructure(true));
}

TEST_F(CairoOutputDevTest_1731, CanBeCalledOnExistingObjectMultipleTimesAcrossScopes_1731) {
  CairoOutputDev dev;

  EXPECT_NO_THROW(dev.setLogicalStructure(false));
  {
    EXPECT_NO_THROW(dev.setLogicalStructure(true));
  }
  EXPECT_NO_THROW(dev.setLogicalStructure(false));
}

}  // namespace