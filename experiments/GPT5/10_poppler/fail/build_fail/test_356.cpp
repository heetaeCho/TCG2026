// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for IdentityFunction (Poppler)
// File: IdentityFunction_test_356.cpp

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <limits>
#include <memory>
#include <type_traits>

#include "poppler/Function.h"

// NOTE:
// - We treat IdentityFunction as a black box.
// - We only assert behavior observable through the public interface.
// - We avoid assumptions about internal sizes / number of inputs/outputs.
// - For transform(), we use in/out buffers sized to Poppler's documented maxima
//   (funcMaxInputs/funcMaxOutputs) to stay safely within any expected access.

namespace {

constexpr int kInSize = funcMaxInputs;
constexpr int kOutSize = funcMaxOutputs;

class IdentityFunctionTest_356 : public ::testing::Test {
protected:
  void SetUp() override { func = std::make_unique<IdentityFunction>(); }

  std::unique_ptr<IdentityFunction> func;
};

TEST_F(IdentityFunctionTest_356, GetTypeIsIdentity_356) {
  ASSERT_NE(func, nullptr);
  EXPECT_EQ(func->getType(), Function::Type::Identity);
}

TEST_F(IdentityFunctionTest_356, IsOkReturnsTrue_356) {
  ASSERT_NE(func, nullptr);
  // Observable contract: isOk() reports whether the function is usable.
  EXPECT_TRUE(func->isOk());
}

TEST_F(IdentityFunctionTest_356, CopyProducesNonNullFunctionWithSameType_356) {
  ASSERT_NE(func, nullptr);

  std::unique_ptr<Function> copied = func->copy();
  ASSERT_NE(copied, nullptr);
  EXPECT_EQ(copied->getType(), Function::Type::Identity);

  // Also verify it behaves like a Function object (polymorphic delete safety).
  // (No direct assertion needed; ownership exit will delete.)
}

TEST_F(IdentityFunctionTest_356, TransformDoesNotCrashWithValidBuffers_356) {
  ASSERT_NE(func, nullptr);

  std::array<double, kInSize> in{};
  std::array<double, kOutSize> out{};
  // Fill with a pattern to make sure output is writable.
  for (int i = 0; i < kInSize; ++i) {
    in[i] = static_cast<double>(i) + 0.25;
  }
  for (int i = 0; i < kOutSize; ++i) {
    out[i] = -12345.0;
  }

  // Primary observable requirement here: no exception, no crash, writes are allowed.
  EXPECT_NO_THROW(func->transform(in.data(), out.data()));
}

TEST_F(IdentityFunctionTest_356, TransformPreservesSpecialValues_356) {
  ASSERT_NE(func, nullptr);

  std::array<double, kInSize> in{};
  std::array<double, kOutSize> out{};

  // Boundary / exceptional floating-point values
  in[0] = 0.0;
  in[1] = -0.0;
  in[2] = std::numeric_limits<double>::infinity();
  in[3] = -std::numeric_limits<double>::infinity();
  in[4] = std::numeric_limits<double>::quiet_NaN();
  in[5] = std::numeric_limits<double>::denorm_min();
  in[6] = std::numeric_limits<double>::max();
  in[7] = std::numeric_limits<double>::lowest();

  // Initialize output with a different pattern.
  for (int i = 0; i < kOutSize; ++i) {
    out[i] = 42.0;
  }

  func->transform(in.data(), out.data());

  // Identity-like observable behavior: first elements should match input in a value-preserving way.
  // We don't assume it writes beyond what's required, but it should at least produce outputs
  // consistent with its semantics.
  EXPECT_EQ(out[0], in[0]);
  EXPECT_EQ(std::signbit(out[1]), std::signbit(in[1])); // preserve -0 sign
  EXPECT_TRUE(std::isinf(out[2]) && out[2] > 0);
  EXPECT_TRUE(std::isinf(out[3]) && out[3] < 0);
  EXPECT_TRUE(std::isnan(out[4]));
  EXPECT_EQ(out[5], in[5]);
  EXPECT_EQ(out[6], in[6]);
  EXPECT_EQ(out[7], in[7]);
}

TEST_F(IdentityFunctionTest_356, TransformMatchesInputForSeveralPositions_356) {
  ASSERT_NE(func, nullptr);

  std::array<double, kInSize> in{};
  std::array<double, kOutSize> out{};

  // Fill inputs with distinct values; outputs with sentinel.
  for (int i = 0; i < kInSize; ++i) {
    in[i] = (i % 2 == 0) ? (static_cast<double>(i) + 0.5) : -(static_cast<double>(i) + 0.5);
  }
  for (int i = 0; i < kOutSize; ++i) {
    out[i] = -9999.0;
  }

  func->transform(in.data(), out.data());

  // We don't know how many outputs are semantically meaningful for this Function,
  // but IdentityFunction should map "in -> out" directly at least for overlapping indices.
  const int n = std::min(kInSize, kOutSize);
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(out[i], in[i]) << "index " << i;
  }
}

TEST_F(IdentityFunctionTest_356, CopyIsIndependentObject_356) {
  ASSERT_NE(func, nullptr);

  std::unique_ptr<Function> copied = func->copy();
  ASSERT_NE(copied, nullptr);

  // Independence check via observable behavior: running transform on both should be fine,
  // and neither call should affect the other.
  std::array<double, kInSize> in{};
  std::array<double, kOutSize> out1{};
  std::array<double, kOutSize> out2{};

  for (int i = 0; i < kInSize; ++i) {
    in[i] = static_cast<double>(i) * 3.0;
  }
  for (int i = 0; i < kOutSize; ++i) {
    out1[i] = 1.0;
    out2[i] = 2.0;
  }

  EXPECT_NO_THROW(func->transform(in.data(), out1.data()));
  EXPECT_NO_THROW(copied->transform(in.data(), out2.data()));

  const int n = std::min(kInSize, kOutSize);
  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(out1[i], in[i]) << "original index " << i;
    EXPECT_EQ(out2[i], in[i]) << "copy index " << i;
  }
}

} // namespace