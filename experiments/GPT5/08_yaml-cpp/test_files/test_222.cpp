// TEST_ID: 222
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

namespace YAML {
namespace detail {

class NodeRefSetNullTest_222 : public ::testing::Test {
protected:
  node_ref ref_;
};

TEST_F(NodeRefSetNullTest_222, DefaultConstructedCanBeSetToNull_222) {
  EXPECT_NO_THROW(ref_.set_null());
  EXPECT_EQ(ref_.type(), NodeType::Null);
}

TEST_F(NodeRefSetNullTest_222, SetNullIsIdempotent_222) {
  ref_.set_null();
  EXPECT_EQ(ref_.type(), NodeType::Null);

  EXPECT_NO_THROW(ref_.set_null());
  EXPECT_EQ(ref_.type(), NodeType::Null);
}

TEST_F(NodeRefSetNullTest_222, SetNullOverridesPreviousScalarState_222) {
  ref_.set_scalar("hello");
  ASSERT_EQ(ref_.type(), NodeType::Scalar);

  ref_.set_null();
  EXPECT_EQ(ref_.type(), NodeType::Null);
}

TEST_F(NodeRefSetNullTest_222, SetNullAfterOtherTypeChangeResultsInNull_222) {
  // Use only public interface; we don't assume how other types behave internally.
  ref_.set_type(NodeType::Sequence);
  ASSERT_EQ(ref_.type(), NodeType::Sequence);

  ref_.set_null();
  EXPECT_EQ(ref_.type(), NodeType::Null);
}

TEST_F(NodeRefSetNullTest_222, SetNullPropagatesThroughSharedDataViaSetData_222) {
  node_ref a;
  node_ref b;

  a.set_scalar("value");
  ASSERT_EQ(a.type(), NodeType::Scalar);

  // b now references the same underlying data as a (observable via later effects).
  b.set_data(a);

  b.set_null();

  // Observable behavior: both should now report Null.
  EXPECT_EQ(b.type(), NodeType::Null);
  EXPECT_EQ(a.type(), NodeType::Null);
}

TEST_F(NodeRefSetNullTest_222, SetDataToSelfThenSetNullDoesNotCrash_222) {
  // Defensive/error-ish case: self-assignment via set_data should not break set_null.
  EXPECT_NO_THROW(ref_.set_data(ref_));
  EXPECT_NO_THROW(ref_.set_null());
  EXPECT_EQ(ref_.type(), NodeType::Null);
}

}  // namespace detail
}  // namespace YAML