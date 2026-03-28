// TEST_ID: 352
#include <gtest/gtest.h>

#if __has_include("poppler/Function.h")
#include "poppler/Function.h"
#elif __has_include("Function.h")
#include "Function.h"
#else
#error "Cannot find Function.h"
#endif

namespace {

class TestFunction_352 : public Function {
public:
  TestFunction_352() = default;

  // Test helper: provide a way to set up preconditions for the getter.
  // This is only used to set values for observable verification via getRangeMax().
  void setRangeMaxForTest(int i, double v) { range[i][1] = v; }
};

} // namespace

TEST(FunctionTest_352, GetRangeMax_ReturnsSetValueAtZeroIndex_352) {
  TestFunction_352 f;
  f.setRangeMaxForTest(0, 123.456);

  EXPECT_DOUBLE_EQ(f.getRangeMax(0), 123.456);
}

TEST(FunctionTest_352, GetRangeMax_ReturnsSetValueAtMiddleIndex_352) {
  TestFunction_352 f;
  f.setRangeMaxForTest(5, -7.25);

  EXPECT_DOUBLE_EQ(f.getRangeMax(5), -7.25);
}

TEST(FunctionTest_352, GetRangeMax_ReturnsSetValueAtMaxSupportedIndex_352) {
  TestFunction_352 f;

  // Per provided header snippet: range is double[32][2], valid indices are 0..31.
  constexpr int kLast = 31;
  f.setRangeMaxForTest(kLast, 0.0);

  EXPECT_DOUBLE_EQ(f.getRangeMax(kLast), 0.0);
}

TEST(FunctionTest_352, GetRangeMax_CanBeCalledOnConstObject_352) {
  TestFunction_352 f;
  f.setRangeMaxForTest(1, 3.14159);

  const Function& cf = f;
  EXPECT_DOUBLE_EQ(cf.getRangeMax(1), 3.14159);
}