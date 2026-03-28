// TEST_ID = 935
#include <gtest/gtest.h>

#include "Form.h"

namespace {

class FormTest_935 : public ::testing::Test {
protected:
  // Use nullptr as we only exercise getCalculateOrder(), which is a const accessor.
  // If the real implementation requires a non-null PDFDoc, these tests will reveal that.
  FormTest_935() : form_(nullptr) {}

  Form form_;
};

TEST_F(FormTest_935, GetCalculateOrder_InitiallyEmpty_935) {
  const std::vector<Ref> &order = form_.getCalculateOrder();
  EXPECT_TRUE(order.empty());
  EXPECT_EQ(order.size(), 0u);
}

TEST_F(FormTest_935, GetCalculateOrder_ReturnsStableReferenceAcrossCalls_935) {
  const std::vector<Ref> &order1 = form_.getCalculateOrder();
  const std::vector<Ref> &order2 = form_.getCalculateOrder();

  // Same object reference across calls (no copy).
  EXPECT_EQ(&order1, &order2);
}

TEST_F(FormTest_935, GetCalculateOrder_CanBeCalledOnConstForm_935) {
  const Form &cform = form_;
  const std::vector<Ref> &order = cform.getCalculateOrder();

  EXPECT_TRUE(order.empty());
  EXPECT_EQ(order.size(), 0u);
}

TEST_F(FormTest_935, GetCalculateOrder_ReferenceRemainsValidAcrossMultipleReads_935) {
  const std::vector<Ref> *first_addr = &form_.getCalculateOrder();

  for (int i = 0; i < 10; ++i) {
    const std::vector<Ref> &order = form_.getCalculateOrder();
    EXPECT_EQ(&order, first_addr);
    EXPECT_TRUE(order.empty());
  }
}

// Compile-time check: accessor returns a const reference.
static_assert(std::is_same_v<decltype(std::declval<const Form &>().getCalculateOrder()),
                            const std::vector<Ref> &>,
              "Form::getCalculateOrder() must return const std::vector<Ref>&");

} // namespace