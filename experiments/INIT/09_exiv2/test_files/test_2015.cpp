// =================================================================================================
// UNIT TESTS for WXMPMeta_DeleteProperty_1
// TEST_ID: 2015
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>

#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper under test (implemented in WXMPMeta.cpp).
extern "C" void WXMPMeta_DeleteProperty_1(XMPMetaRef xmpRef,
                                         XMP_StringPtr schemaNS,
                                         XMP_StringPtr propName,
                                         WXMP_Result* wResult);

namespace {

class WXMPMeta_DeleteProperty_1_Test_2015 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a real XMPMeta object and pass it as XMPMetaRef (opaque ref in the wrapper).
    meta_ = new XMPMeta();
    xmpRef_ = reinterpret_cast<XMPMetaRef>(meta_);
  }

  void TearDown() override {
    delete meta_;
    meta_ = nullptr;
    xmpRef_ = nullptr;
  }

  // Helper that accepts either observable behavior style:
  //  - wrapper throws XMP_Error
  //  - wrapper catches and sets wResult->errMessage
  void ExpectBadParamBehavior(XMP_StringPtr schemaNS,
                              XMP_StringPtr propName,
                              XMP_Int32 expectedErrID) {
    WXMP_Result w;
    bool threw = false;

    try {
      WXMPMeta_DeleteProperty_1(xmpRef_, schemaNS, propName, &w);
    } catch (const XMP_Error& e) {
      threw = true;
      EXPECT_EQ(e.GetID(), expectedErrID);
    } catch (...) {
      threw = true;
      FAIL() << "Unexpected exception type thrown by wrapper.";
    }

    if (!threw) {
      // If the wrapper swallows exceptions, it should report an error message via wResult.
      ASSERT_NE(w.errMessage, nullptr);
      EXPECT_NE(*w.errMessage, '\0');
    }
  }

  static constexpr XMP_StringPtr kSchema = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kProp = "CreatorTool";
  static constexpr XMP_StringPtr kValue = "UnitTest";

  XMPMeta* meta_{nullptr};
  XMPMetaRef xmpRef_{nullptr};
};

}  // namespace

TEST_F(WXMPMeta_DeleteProperty_1_Test_2015, DeletesExistingProperty_2015) {
  // Arrange: create a property via the public XMPMeta interface.
  meta_->SetProperty(kSchema, kProp, kValue, 0);
  ASSERT_TRUE(meta_->DoesPropertyExist(kSchema, kProp));

  WXMP_Result w;

  // Act: delete via the wrapper.
  EXPECT_NO_THROW(WXMPMeta_DeleteProperty_1(xmpRef_, kSchema, kProp, &w));

  // Assert: property is gone (observable via public interface).
  EXPECT_FALSE(meta_->DoesPropertyExist(kSchema, kProp));
}

TEST_F(WXMPMeta_DeleteProperty_1_Test_2015, DeletingMissingPropertyIsNoOp_2015) {
  // Arrange: ensure property does not exist.
  ASSERT_FALSE(meta_->DoesPropertyExist(kSchema, kProp));

  WXMP_Result w;

  // Act/Assert: deleting a missing property should not create it and should not throw.
  EXPECT_NO_THROW(WXMPMeta_DeleteProperty_1(xmpRef_, kSchema, kProp, &w));
  EXPECT_FALSE(meta_->DoesPropertyExist(kSchema, kProp));

  // Repeat delete to cover idempotence.
  EXPECT_NO_THROW(WXMPMeta_DeleteProperty_1(xmpRef_, kSchema, kProp, &w));
  EXPECT_FALSE(meta_->DoesPropertyExist(kSchema, kProp));
}

TEST_F(WXMPMeta_DeleteProperty_1_Test_2015, NullSchemaNSReportsBadSchema_2015) {
  ExpectBadParamBehavior(/*schemaNS=*/nullptr, /*propName=*/kProp, kXMPErr_BadSchema);
}

TEST_F(WXMPMeta_DeleteProperty_1_Test_2015, EmptySchemaNSReportsBadSchema_2015) {
  ExpectBadParamBehavior(/*schemaNS=*/"", /*propName=*/kProp, kXMPErr_BadSchema);
}

TEST_F(WXMPMeta_DeleteProperty_1_Test_2015, NullPropNameReportsBadXPath_2015) {
  ExpectBadParamBehavior(/*schemaNS=*/kSchema, /*propName=*/nullptr, kXMPErr_BadXPath);
}

TEST_F(WXMPMeta_DeleteProperty_1_Test_2015, EmptyPropNameReportsBadXPath_2015) {
  ExpectBadParamBehavior(/*schemaNS=*/kSchema, /*propName=*/"", kXMPErr_BadXPath);
}

TEST_F(WXMPMeta_DeleteProperty_1_Test_2015, PropertyUnchangedWhenSchemaInvalid_2015) {
  // Arrange: set a property.
  meta_->SetProperty(kSchema, kProp, kValue, 0);
  ASSERT_TRUE(meta_->DoesPropertyExist(kSchema, kProp));

  // Act: call with invalid schema, which should fail without deleting the property.
  ExpectBadParamBehavior(/*schemaNS=*/"", /*propName=*/kProp, kXMPErr_BadSchema);

  // Assert: still exists.
  EXPECT_TRUE(meta_->DoesPropertyExist(kSchema, kProp));
}

TEST_F(WXMPMeta_DeleteProperty_1_Test_2015, PropertyUnchangedWhenPropNameInvalid_2015) {
  // Arrange: set a property.
  meta_->SetProperty(kSchema, kProp, kValue, 0);
  ASSERT_TRUE(meta_->DoesPropertyExist(kSchema, kProp));

  // Act: call with invalid prop name, which should fail without deleting the property.
  ExpectBadParamBehavior(/*schemaNS=*/kSchema, /*propName=*/"", kXMPErr_BadXPath);

  // Assert: still exists.
  EXPECT_TRUE(meta_->DoesPropertyExist(kSchema, kProp));
}