// TEST_ID: 54
// File: SignatureInfo_test.cpp
//
// Unit tests for poppler::SignatureInfo (partial interface provided).
// Constraints respected:
// - Treat implementation as a black box.
// - Use only public interface / observable behavior.
// - No private state access, no inferred internal logic.

#include <gtest/gtest.h>

// Include the class under test.
#include "SignatureInfo.h"

namespace {

// Note: If SignatureInfo lives in a namespace in your codebase (e.g., poppler),
// adjust this alias accordingly (e.g., using poppler::SignatureInfo).
using ::SignatureInfo;

class SignatureInfoTest_54 : public ::testing::Test {
protected:
  SignatureInfo info;
};

TEST_F(SignatureInfoTest_54, DefaultSubfilterSupportIsDeterministic_54) {
  // Observable behavior: calling const getter should be stable across calls.
  const bool first = info.isSubfilterSupported();
  const bool second = info.isSubfilterSupported();
  const bool third = info.isSubfilterSupported();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(SignatureInfoTest_54, SetSubFilterSupportTrueMakesGetterReturnTrue_54) {
  info.setSubFilterSupport(true);
  EXPECT_TRUE(info.isSubfilterSupported());

  // Stability check after set.
  EXPECT_TRUE(info.isSubfilterSupported());
}

TEST_F(SignatureInfoTest_54, SetSubFilterSupportFalseMakesGetterReturnFalse_54) {
  info.setSubFilterSupport(false);
  EXPECT_FALSE(info.isSubfilterSupported());

  // Stability check after set.
  EXPECT_FALSE(info.isSubfilterSupported());
}

TEST_F(SignatureInfoTest_54, ToggleSubFilterSupportReflectsLastSetValue_54) {
  info.setSubFilterSupport(true);
  EXPECT_TRUE(info.isSubfilterSupported());

  info.setSubFilterSupport(false);
  EXPECT_FALSE(info.isSubfilterSupported());

  info.setSubFilterSupport(true);
  EXPECT_TRUE(info.isSubfilterSupported());
}

TEST_F(SignatureInfoTest_54, RepeatedSettingSameValueKeepsStateConsistent_54) {
  info.setSubFilterSupport(false);
  EXPECT_FALSE(info.isSubfilterSupported());

  // Boundary-ish: multiple redundant calls shouldn't cause inconsistency.
  info.setSubFilterSupport(false);
  info.setSubFilterSupport(false);
  EXPECT_FALSE(info.isSubfilterSupported());

  info.setSubFilterSupport(true);
  EXPECT_TRUE(info.isSubfilterSupported());

  info.setSubFilterSupport(true);
  info.setSubFilterSupport(true);
  EXPECT_TRUE(info.isSubfilterSupported());
}

TEST(SignatureInfoStandaloneTest_54, GetterDoesNotMutateAndIsCallableOnConst_54) {
  SignatureInfo local;
  const SignatureInfo &cref = local;

  // Compile-time / API behavior: callable on const.
  const bool v1 = cref.isSubfilterSupported();
  const bool v2 = cref.isSubfilterSupported();
  EXPECT_EQ(v1, v2);
}

}  // namespace