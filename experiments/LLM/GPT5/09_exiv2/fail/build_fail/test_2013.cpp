// =================================================================================================
// TEST_ID: 2013
// Unit tests for WXMPMeta_SetStructField_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <memory>
#include <string>

#include "XMP.hpp"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// Wrapper under test (defined in WXMPMeta.cpp)
extern "C" {
void WXMPMeta_SetStructField_1(XMPMetaRef xmpRef,
                              XMP_StringPtr schemaNS,
                              XMP_StringPtr structName,
                              XMP_StringPtr fieldNS,
                              XMP_StringPtr fieldName,
                              XMP_StringPtr fieldValue,
                              XMP_OptionBits options,
                              WXMP_Result* wResult);
} // extern "C"

namespace {

class WXMPMetaSetStructField1Test_2013 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // Many XMP SDK entry points require initialization.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

protected:
  static constexpr XMP_StringPtr kSchemaNS = "http://ns.example.com/xmp/sdk/test/2013/";
  static constexpr XMP_StringPtr kPrefix = "t2013";

  void SetUp() override {
    // Ensure namespace is registered (some SDK builds require this for custom schemas).
    // If already registered, this should be benign.
    XMPMeta::RegisterNamespace(kSchemaNS, kPrefix);
  }

  static XMPMetaRef ToRef(XMPMeta* meta) { return reinterpret_cast<XMPMetaRef>(meta); }

  static bool HasError(const WXMP_Result& r) { return r.errMessage != nullptr && *r.errMessage != 0; }
};

constexpr XMP_StringPtr WXMPMetaSetStructField1Test_2013::kSchemaNS;
constexpr XMP_StringPtr WXMPMetaSetStructField1Test_2013::kPrefix;

} // namespace

TEST_F(WXMPMetaSetStructField1Test_2013, SetsStructFieldAndCanReadBack_2013) {
  auto meta = std::make_unique<XMPMeta>();
  WXMP_Result wr;

  const char* structName = "MyStruct";
  const char* fieldNS = kSchemaNS;
  const char* fieldName = "myField";
  const char* fieldValue = "hello";

  EXPECT_NO_THROW(WXMPMeta_SetStructField_1(ToRef(meta.get()), kSchemaNS, structName, fieldNS, fieldName,
                                           fieldValue, /*options=*/0, &wr));
  EXPECT_FALSE(HasError(wr));

  XMP_StringPtr gotValue = nullptr;
  XMP_StringLen gotLen = 0;
  XMP_OptionBits gotOpts = 0;

  // Observable behavior through public interface: the field exists and value matches.
  EXPECT_TRUE(meta->GetStructField(kSchemaNS, structName, fieldNS, fieldName, &gotValue, &gotLen, &gotOpts));
  ASSERT_NE(gotValue, nullptr);
  EXPECT_EQ(std::string(gotValue, static_cast<size_t>(gotLen)), std::string(fieldValue));
}

TEST_F(WXMPMetaSetStructField1Test_2013, NullSchemaNSReportsError_2013) {
  auto meta = std::make_unique<XMPMeta>();
  WXMP_Result wr;

  EXPECT_NO_THROW(WXMPMeta_SetStructField_1(ToRef(meta.get()),
                                           /*schemaNS=*/nullptr,
                                           /*structName=*/"S",
                                           /*fieldNS=*/kSchemaNS,
                                           /*fieldName=*/"F",
                                           /*fieldValue=*/"V",
                                           /*options=*/0, &wr));
  EXPECT_TRUE(HasError(wr));
}

TEST_F(WXMPMetaSetStructField1Test_2013, EmptySchemaNSReportsError_2013) {
  auto meta = std::make_unique<XMPMeta>();
  WXMP_Result wr;

  EXPECT_NO_THROW(WXMPMeta_SetStructField_1(ToRef(meta.get()),
                                           /*schemaNS=*/"",
                                           /*structName=*/"S",
                                           /*fieldNS=*/kSchemaNS,
                                           /*fieldName=*/"F",
                                           /*fieldValue=*/"V",
                                           /*options=*/0, &wr));
  EXPECT_TRUE(HasError(wr));
}

TEST_F(WXMPMetaSetStructField1Test_2013, NullStructNameReportsError_2013) {
  auto meta = std::make_unique<XMPMeta>();
  WXMP_Result wr;

  EXPECT_NO_THROW(WXMPMeta_SetStructField_1(ToRef(meta.get()),
                                           /*schemaNS=*/kSchemaNS,
                                           /*structName=*/nullptr,
                                           /*fieldNS=*/kSchemaNS,
                                           /*fieldName=*/"F",
                                           /*fieldValue=*/"V",
                                           /*options=*/0, &wr));
  EXPECT_TRUE(HasError(wr));
}

TEST_F(WXMPMetaSetStructField1Test_2013, EmptyFieldNameReportsError_2013) {
  auto meta = std::make_unique<XMPMeta>();
  WXMP_Result wr;

  EXPECT_NO_THROW(WXMPMeta_SetStructField_1(ToRef(meta.get()),
                                           /*schemaNS=*/kSchemaNS,
                                           /*structName=*/"S",
                                           /*fieldNS=*/kSchemaNS,
                                           /*fieldName=*/"",
                                           /*fieldValue=*/"V",
                                           /*options=*/0, &wr));
  EXPECT_TRUE(HasError(wr));
}