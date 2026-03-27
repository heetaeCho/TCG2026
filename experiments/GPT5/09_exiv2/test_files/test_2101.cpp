// =================================================================================================
// UNIT TESTS for SetCurrSchema (XMPIterator.cpp)
// TEST_ID: 2101
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// Include the header for IterInfo / XMP_VarString.
// (Path matches the prompt-provided project layout.)
#include "./TestProjects/exiv2/xmpsdk/src/XMPIterator.hpp"

// NOTE:
// SetCurrSchema is a file-scope `static inline` function defined in XMPIterator.cpp.
// To test it without altering production code, we include the .cpp directly so the
// function is visible in this translation unit.
#include "./TestProjects/exiv2/xmpsdk/src/XMPIterator.cpp"

namespace {

class SetCurrSchemaTest_2101 : public ::testing::Test {
protected:
  static IterInfo MakeInfo() {
    // Prefer the public constructor if available; fall back to default.
    // (We intentionally do not depend on internal state.)
    return IterInfo(0, nullptr);
  }
};

// Normal operation: assigns info.currSchema to schemaName.
TEST_F(SetCurrSchemaTest_2101, SetsCurrSchemaToProvidedSchemaName_2101) {
  IterInfo info = MakeInfo();

  XMP_VarString schemaName("http://ns.adobe.com/xap/1.0/");
  SetCurrSchema(info, schemaName);

  EXPECT_EQ(info.currSchema, schemaName);
}

// Boundary: empty schema string.
TEST_F(SetCurrSchemaTest_2101, AcceptsEmptySchemaName_2101) {
  IterInfo info = MakeInfo();

  XMP_VarString schemaName;
  schemaName.clear();

  SetCurrSchema(info, schemaName);

  EXPECT_TRUE(info.currSchema.empty());
  EXPECT_EQ(info.currSchema, schemaName);
}

// Boundary: large schema string.
TEST_F(SetCurrSchemaTest_2101, HandlesLargeSchemaName_2101) {
  IterInfo info = MakeInfo();

  // Create a large-ish schema string without relying on internal limits.
  std::string large(64 * 1024, 'a');
  large.replace(0, 8, "http://"); // make it look like a URI-ish schema
  XMP_VarString schemaName(large.c_str());

  SetCurrSchema(info, schemaName);

  EXPECT_EQ(info.currSchema.size(), schemaName.size());
  EXPECT_EQ(info.currSchema, schemaName);
}

// Verifies the input reference is not modified (observable through the interface).
TEST_F(SetCurrSchemaTest_2101, DoesNotModifySchemaNameArgument_2101) {
  IterInfo info = MakeInfo();

  XMP_VarString schemaName("http://ns.adobe.com/exif/1.0/");
  const XMP_VarString original = schemaName;

  SetCurrSchema(info, schemaName);

  EXPECT_EQ(schemaName, original);
  EXPECT_EQ(info.currSchema, original);
}

// Boundary: self-assignment scenario (passing info.currSchema itself).
TEST_F(SetCurrSchemaTest_2101, SupportsSelfAssignment_2101) {
  IterInfo info = MakeInfo();

  info.currSchema = "http://ns.adobe.com/tiff/1.0/";

  // Pass the same object as the source argument.
  SetCurrSchema(info, info.currSchema);

  EXPECT_EQ(info.currSchema, "http://ns.adobe.com/tiff/1.0/");
}

} // namespace