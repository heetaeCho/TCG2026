// TEST_ID: 513
// File: gfx_univariate_shading_getfunc_test_513.cc

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

#include "poppler/GfxState.h"
#include "poppler/Function.h"

namespace {

// A minimal concrete Function implementation so we can pass non-null Functions into
// GfxUnivariateShading. This is only a test helper (external collaborator), not
// a re-implementation of GfxUnivariateShading logic.
class DummyFunction final : public Function {
public:
  DummyFunction(int inSize, int outSize) : inSize_(inSize), outSize_(outSize) {}
  ~DummyFunction() override = default;

  // Function API (Poppler's Function is abstract in typical builds).
  Function *copy() const override { return new DummyFunction(inSize_, outSize_); }
  int getInputSize() const override { return inSize_; }
  int getOutputSize() const override { return outSize_; }
  void transform(const double * /*in*/, double *out) const override {
    // Deterministic fill, not used by these tests, but keeps behavior defined.
    for (int i = 0; i < outSize_; ++i) out[i] = 0.0;
  }

private:
  int inSize_;
  int outSize_;
};

class GfxUnivariateShadingTest_513 : public ::testing::Test {
protected:
  static std::vector<std::unique_ptr<Function>> MakeFuncs() {
    std::vector<std::unique_ptr<Function>> funcs;
    funcs.emplace_back(nullptr); // index 0 is intentionally null
    funcs.emplace_back(std::make_unique<DummyFunction>(1, 3));
    funcs.emplace_back(std::make_unique<DummyFunction>(2, 1));
    return funcs;
  }
};

} // namespace

TEST_F(GfxUnivariateShadingTest_513, GetFuncReturnsExactPointerForInRangeIndices_513) {
  auto funcs = MakeFuncs();
  const Function *expected0 = funcs[0].get();
  const Function *expected1 = funcs[1].get();
  const Function *expected2 = funcs[2].get();

  GfxUnivariateShading shading(/*typeA=*/1,
                              /*t0A=*/0.0,
                              /*t1A=*/1.0,
                              std::move(funcs),
                              /*extend0A=*/false,
                              /*extend1A=*/true);

  ASSERT_EQ(shading.getNFuncs(), 3);

  EXPECT_EQ(shading.getFunc(0), expected0);
  EXPECT_EQ(shading.getFunc(1), expected1);
  EXPECT_EQ(shading.getFunc(2), expected2);
}

TEST_F(GfxUnivariateShadingTest_513, GetFuncReturnsNullWhenStoredFunctionIsNull_513) {
  auto funcs = MakeFuncs();
  ASSERT_EQ(funcs.size(), 3u);
  ASSERT_EQ(funcs[0].get(), nullptr); // sanity for the test input

  GfxUnivariateShading shading(/*typeA=*/1,
                              /*t0A=*/-5.0,
                              /*t1A=*/5.0,
                              std::move(funcs),
                              /*extend0A=*/true,
                              /*extend1A=*/false);

  EXPECT_EQ(shading.getNFuncs(), 3);
  EXPECT_EQ(shading.getFunc(0), nullptr);
}

TEST_F(GfxUnivariateShadingTest_513, GetFuncIsStableAcrossRepeatedCalls_513) {
  auto funcs = MakeFuncs();
  const Function *expected1 = funcs[1].get();
  const Function *expected2 = funcs[2].get();

  GfxUnivariateShading shading(/*typeA=*/1,
                              /*t0A=*/0.0,
                              /*t1A=*/10.0,
                              std::move(funcs),
                              /*extend0A=*/false,
                              /*extend1A=*/false);

  ASSERT_EQ(shading.getNFuncs(), 3);

  // Repeated calls should return the same observable pointer for the same index.
  EXPECT_EQ(shading.getFunc(1), expected1);
  EXPECT_EQ(shading.getFunc(1), expected1);
  EXPECT_EQ(shading.getFunc(2), expected2);
  EXPECT_EQ(shading.getFunc(2), expected2);
}

TEST_F(GfxUnivariateShadingTest_513, GetFuncWorksAtBoundaryIndices_513) {
  auto funcs = MakeFuncs();
  const Function *first = funcs.front().get();
  const Function *last = funcs.back().get();

  GfxUnivariateShading shading(/*typeA=*/1,
                              /*t0A=*/1.0,
                              /*t1A=*/2.0,
                              std::move(funcs),
                              /*extend0A=*/true,
                              /*extend1A=*/true);

  ASSERT_EQ(shading.getNFuncs(), 3);

  // Boundary indices: 0 and getNFuncs()-1.
  EXPECT_EQ(shading.getFunc(0), first);
  EXPECT_EQ(shading.getFunc(shading.getNFuncs() - 1), last);
}

// NOTE: We intentionally do not test out-of-range indices (e.g., i < 0 or i >= getNFuncs()).
// The provided interface does not specify error handling for invalid indices, and such calls
// may be undefined behavior depending on the actual implementation.