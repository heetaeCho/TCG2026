// TEST_ID: 509
// File: gfxunivariateshading_getdomain1_509_test.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <memory>
#include <utility>
#include <vector>

// Poppler headers (project-local)
#include "poppler/Function.h"
#include "poppler/GfxState.h"

namespace {

// A minimal concrete Function implementation so we can construct GfxUnivariateShading.
// This is an external collaborator of GfxUnivariateShading (passed-in dependency).
class DummyFunction final : public Function {
public:
  DummyFunction() = default;
  ~DummyFunction() override = default;

  DummyFunction(const DummyFunction&) = delete;
  DummyFunction& operator=(const DummyFunction&) = delete;

  // The exact virtual surface of Function can vary across Poppler versions.
  // Implement the common ones; if your Function.h differs, adjust these overrides
  // to match the pure-virtual interface in your tree.

  Function *copy() const override { return new DummyFunction(); }

  int getType() const override { return 0; }

  void transform(const double * /*in*/, double *out) const override {
    // Deterministic output; not testing transform here.
    out[0] = 0.0;
  }

  bool isOk() const override { return true; }

  // Some Poppler versions also require domain/range queries.
  // If these are not present in your Function.h, remove them.
  void getDomain(double * /*x0*/, double * /*x1*/) const override {}
  void getRange(double * /*y0*/, double * /*y1*/) const override {}
};

static std::unique_ptr<GfxUnivariateShading> MakeShading(double t0,
                                                        double t1,
                                                        bool extend0 = false,
                                                        bool extend1 = false) {
  std::vector<std::unique_ptr<Function>> funcs;
  funcs.emplace_back(std::make_unique<DummyFunction>());

  // typeA is shading type (e.g., 1/2/etc.); for these tests we only need that
  // construction succeeds.
  constexpr int kType = 1;
  return std::make_unique<GfxUnivariateShading>(kType, t0, t1, std::move(funcs), extend0, extend1);
}

class GfxUnivariateShadingTest_509 : public ::testing::Test {};

} // namespace

TEST_F(GfxUnivariateShadingTest_509, GetDomain1ReturnsConstructionValue_509) {
  auto shading = MakeShading(/*t0=*/0.0, /*t1=*/42.5);
  EXPECT_DOUBLE_EQ(shading->getDomain1(), 42.5);
}

TEST_F(GfxUnivariateShadingTest_509, GetDomain1WorksWithNegativeValue_509) {
  auto shading = MakeShading(/*t0=*/0.0, /*t1=*/-3.25);
  EXPECT_DOUBLE_EQ(shading->getDomain1(), -3.25);
}

TEST_F(GfxUnivariateShadingTest_509, GetDomain1WorksWithZero_509) {
  auto shading = MakeShading(/*t0=*/-10.0, /*t1=*/0.0);
  EXPECT_DOUBLE_EQ(shading->getDomain1(), 0.0);
}

TEST_F(GfxUnivariateShadingTest_509, GetDomain1WhenDomainIsReversed_509) {
  // Boundary case: t1 < t0. We only assert observable behavior via getDomain1.
  auto shading = MakeShading(/*t0=*/5.0, /*t1=*/2.0);
  EXPECT_DOUBLE_EQ(shading->getDomain1(), 2.0);
}

TEST_F(GfxUnivariateShadingTest_509, GetDomain1SupportsInfinity_509) {
  const double inf = std::numeric_limits<double>::infinity();
  auto shading = MakeShading(/*t0=*/0.0, /*t1=*/inf);
  EXPECT_TRUE(std::isinf(shading->getDomain1()));
  EXPECT_GT(shading->getDomain1(), 0.0);
}

TEST_F(GfxUnivariateShadingTest_509, GetDomain1SupportsNaN_509) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  auto shading = MakeShading(/*t0=*/0.0, /*t1=*/nan);
  EXPECT_TRUE(std::isnan(shading->getDomain1()));
}

TEST_F(GfxUnivariateShadingTest_509, CopyConstructorPreservesDomain1_509) {
  auto original = MakeShading(/*t0=*/1.0, /*t1=*/9.75);

  // Use the provided explicit copy-ctor taking a pointer.
  GfxUnivariateShading copy(original.get());
  EXPECT_DOUBLE_EQ(copy.getDomain1(), original->getDomain1());
}