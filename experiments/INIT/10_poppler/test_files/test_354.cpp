// TEST_ID: 354
// File: Function_test.cpp
//
// Unit tests for:
//   File name : ./TestProjects/poppler/poppler/Function.h
//   class Function { public: virtual bool hasDifferentResultSet(const Function * /*func*/) const { return false; } };
//
// Constraints respected:
// - Treat implementation as black box
// - Only use public interface
// - Use gMock only for external interactions (virtual override call verification)

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Function.h"

namespace {

// Helper derived type to verify virtual dispatch and external interaction.
class MockFunction : public Function {
public:
  MOCK_METHOD(bool, hasDifferentResultSet, (const Function* func), (const, override));
};

class FunctionTest_354 : public ::testing::Test {};

TEST_F(FunctionTest_354, DefaultImplementationReturnsFalseForNull_354) {
  Function f;
  EXPECT_FALSE(f.hasDifferentResultSet(nullptr));
}

TEST_F(FunctionTest_354, DefaultImplementationReturnsFalseForSelfPointer_354) {
  Function f;
  EXPECT_FALSE(f.hasDifferentResultSet(&f));
}

TEST_F(FunctionTest_354, DefaultImplementationReturnsFalseForOtherFunctionPointer_354) {
  Function f1;
  Function f2;
  EXPECT_FALSE(f1.hasDifferentResultSet(&f2));
}

TEST_F(FunctionTest_354, VirtualDispatchInvokesOverrideAndPassesArgument_354) {
  using ::testing::_;
  using ::testing::Return;

  MockFunction mock;
  Function other;

  // Verify external interaction: the overridden method is invoked with the same pointer.
  EXPECT_CALL(mock, hasDifferentResultSet(&other)).Times(1).WillOnce(Return(true));

  // Call through base reference to ensure virtual dispatch.
  const Function& base_ref = mock;
  EXPECT_TRUE(base_ref.hasDifferentResultSet(&other));
}

TEST_F(FunctionTest_354, VirtualDispatchCanBeCalledWithNullAndIsForwarded_354) {
  using ::testing::Return;

  MockFunction mock;

  EXPECT_CALL(mock, hasDifferentResultSet(nullptr)).Times(1).WillOnce(Return(false));

  const Function& base_ref = mock;
  EXPECT_FALSE(base_ref.hasDifferentResultSet(nullptr));
}

}  // namespace