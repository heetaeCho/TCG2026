// File: function_getoutputsize_unittest.cpp
// TEST_ID: 348

#include <gtest/gtest.h>

#include "poppler/Function.h"

namespace {

class FunctionTest_348 : public ::testing::Test {};

TEST_F(FunctionTest_348, GetOutputSize_CanBeCalledOnDefaultConstructedObject_348) {
  Function func;
  EXPECT_NO_THROW({
    volatile int outSize = func.getOutputSize();
    (void)outSize;
  });
}

TEST_F(FunctionTest_348, GetOutputSize_CanBeCalledOnConstObject_348) {
  const Function func;
  EXPECT_NO_THROW({
    volatile int outSize = func.getOutputSize();
    (void)outSize;
  });
}

TEST_F(FunctionTest_348, GetOutputSize_IsStableAcrossRepeatedCalls_348) {
  Function func;

  const int first = func.getOutputSize();
  const int second = func.getOutputSize();
  const int third = func.getOutputSize();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(FunctionTest_348, GetOutputSize_WorksViaReferenceAndPointer_348) {
  Function func;

  Function& ref = func;
  Function* ptr = &func;

  const int direct = func.getOutputSize();
  const int viaRef = ref.getOutputSize();
  const int viaPtr = ptr->getOutputSize();

  EXPECT_EQ(direct, viaRef);
  EXPECT_EQ(direct, viaPtr);
}

TEST_F(FunctionTest_348, GetOutputSize_WorksViaConstReferenceAndConstPointer_348) {
  Function func;

  const Function& cref = func;
  const Function* cptr = &func;

  const int direct = func.getOutputSize();
  const int viaCRef = cref.getOutputSize();
  const int viaCPtr = cptr->getOutputSize();

  EXPECT_EQ(direct, viaCRef);
  EXPECT_EQ(direct, viaCPtr);
}

}  // namespace