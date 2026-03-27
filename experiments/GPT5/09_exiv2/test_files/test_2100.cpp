// =================================================================================================
// XMPIterator_SetCurrSchema_2100.cpp
// Unit tests for static inline helper in XMPIterator.cpp: SetCurrSchema
//
// TEST_ID: 2100
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Include the implementation to access the TU-local `static inline` helper.
// This is intentional: the function is not externally linkable by design.
#include "TestProjects/exiv2/xmpsdk/src/XMPIterator.cpp"

namespace {

class SetCurrSchemaTest_2100 : public ::testing::Test {};

TEST_F(SetCurrSchemaTest_2100, SetsCurrSchemaToProvidedName_2100) {
  IterInfo info;

  const char* schema = "http://ns.adobe.com/xap/1.0/";
  SetCurrSchema(info, schema);

  EXPECT_EQ(info.currSchema, schema);
}

TEST_F(SetCurrSchemaTest_2100, OverwritesPreviousSchema_2100) {
  IterInfo info;

  const char* first = "http://ns.adobe.com/xap/1.0/";
  const char* second = "http://purl.org/dc/elements/1.1/";

  SetCurrSchema(info, first);
  ASSERT_EQ(info.currSchema, first);

  SetCurrSchema(info, second);
  EXPECT_EQ(info.currSchema, second);
}

TEST_F(SetCurrSchemaTest_2100, AcceptsEmptyString_2100) {
  IterInfo info;

  const char* empty = "";
  SetCurrSchema(info, empty);

  EXPECT_TRUE(info.currSchema.empty());
  EXPECT_EQ(info.currSchema, std::string{});
}

TEST_F(SetCurrSchemaTest_2100, HandlesLongSchemaName_2100) {
  IterInfo info;

  std::string longSchema(10'000, 'a');
  SetCurrSchema(info, longSchema.c_str());

  EXPECT_EQ(info.currSchema.size(), longSchema.size());
  EXPECT_EQ(info.currSchema, longSchema);
}

TEST_F(SetCurrSchemaTest_2100, DoesNotModifyOtherPublicState_2100) {
  IterInfo info;

  // Only rely on public, observable state.
  const XMPMeta* beforeXmpObj = reinterpret_cast<const XMPMeta*>(0x1234);
  info.xmpObj = beforeXmpObj;

  SetCurrSchema(info, "schema:one");

  EXPECT_EQ(info.currSchema, "schema:one");
  EXPECT_EQ(info.xmpObj, beforeXmpObj);
}

}  // namespace