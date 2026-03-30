// TEST_ID: 517
// File: gfx_function_shading_getfunc_test_517.cpp

#include <gtest/gtest.h>

#include <array>
#include <memory>
#include <vector>

// Poppler headers
#include "poppler/GfxState.h"
#include "poppler/Function.h"

namespace {

// A minimal concrete Function implementation for testing pointer plumbing.
// We do NOT infer any GfxFunctionShading internals; we only need stable objects
// to store in the funcs vector and retrieve via getFunc(i).
class DummyFunction517 final : public Function {
public:
  explicit DummyFunction517(int id) : id_(id) {}

  Function *copy() override { return new DummyFunction517(id_); }
  int getType() override { return 12345; } // Arbitrary, not used by these tests.

  void transform(double * /*in*/, double * /*out*/) override {
    // Not used in these tests.
  }

  GBool isOk() override { return gTrue; }

  int id() const { return id_; }

private:
  int id_;
};

class GfxFunctionShadingTest_517 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxFunctionShading> MakeShading(std::vector<std::unique_ptr<Function>> &&funcs) {
    const double x0 = 0.0, y0 = 0.0, x1 = 100.0, y1 = 200.0;
    const std::array<double, 6> matrix = {1, 0, 0, 1, 0, 0};
    return std::make_unique<GfxFunctionShading>(x0, y0, x1, y1, matrix, std::move(funcs));
  }
};

} // namespace

TEST_F(GfxFunctionShadingTest_517, GetFuncReturnsSamePointerForEachIndex_517) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::make_unique<DummyFunction517>(1));
  funcs.push_back(std::make_unique<DummyFunction517>(2));
  funcs.push_back(std::make_unique<DummyFunction517>(3));

  auto shading = MakeShading(std::move(funcs));
  ASSERT_NE(shading, nullptr);

  const Function *f0 = shading->getFunc(0);
  const Function *f1 = shading->getFunc(1);
  const Function *f2 = shading->getFunc(2);

  ASSERT_NE(f0, nullptr);
  ASSERT_NE(f1, nullptr);
  ASSERT_NE(f2, nullptr);

  // Distinct stored functions should yield distinct addresses.
  EXPECT_NE(f0, f1);
  EXPECT_NE(f1, f2);
  EXPECT_NE(f0, f2);
}

TEST_F(GfxFunctionShadingTest_517, GetFuncFirstAndLastAreAccessible_517) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::make_unique<DummyFunction517>(10));
  funcs.push_back(std::make_unique<DummyFunction517>(20));
  funcs.push_back(std::make_unique<DummyFunction517>(30));
  funcs.push_back(std::make_unique<DummyFunction517>(40));

  auto shading = MakeShading(std::move(funcs));
  ASSERT_NE(shading, nullptr);

  const Function *first = shading->getFunc(0);
  const Function *last = shading->getFunc(3);

  EXPECT_NE(first, nullptr);
  EXPECT_NE(last, nullptr);
  EXPECT_NE(first, last);
}

TEST_F(GfxFunctionShadingTest_517, GetFuncCanReturnNullWhenStoredEntryIsNull_517) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::make_unique<DummyFunction517>(101));
  funcs.push_back(std::unique_ptr<Function>()); // Explicit null entry.
  funcs.push_back(std::make_unique<DummyFunction517>(303));

  auto shading = MakeShading(std::move(funcs));
  ASSERT_NE(shading, nullptr);

  const Function *f0 = shading->getFunc(0);
  const Function *f1 = shading->getFunc(1);
  const Function *f2 = shading->getFunc(2);

  EXPECT_NE(f0, nullptr);
  EXPECT_EQ(f1, nullptr); // Observable behavior through interface.
  EXPECT_NE(f2, nullptr);
}

TEST_F(GfxFunctionShadingTest_517, GetFuncIsStableAcrossMultipleCalls_517) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.push_back(std::make_unique<DummyFunction517>(7));
  funcs.push_back(std::make_unique<DummyFunction517>(8));

  auto shading = MakeShading(std::move(funcs));
  ASSERT_NE(shading, nullptr);

  const Function *a1 = shading->getFunc(1);
  const Function *a2 = shading->getFunc(1);

  // Same index should return the same stored object pointer (observable identity).
  EXPECT_EQ(a1, a2);
  EXPECT_NE(a1, nullptr);
}