#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "client-glue/WXMP_Common.hpp"

#include "./TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"



extern void WXMPMeta_DoesPropertyExist_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr propName, WXMP_Result * wResult);



class WXMPMetaTest : public ::testing::Test {

protected:

    virtual void SetUp() override {

        // Initialize any necessary resources here if needed

        m_xmpRef = new XMPMeta();

    }



    virtual void TearDown() override {

        // Clean up any resources here if needed

        delete m_xmpRef;

    }



    XMPMeta* m_xmpRef;

};



TEST_F(WXMPMetaTest_2019, DoesPropertyExist_NormalCase_2019) {

    WXMP_Result result = {};

    WXMPMeta_DoesPropertyExist_1(m_xmpRef, "http://example.com/schema", "property", &result);

    EXPECT_EQ(result.int32Result, 0); // Assuming property does not exist initially

}



TEST_F(WXMPMetaTest_2019, DoesPropertyExist_EmptySchemaNamespace_2019) {

    WXMP_Result result = {};

    EXPECT_THROW(WXMPMeta_DoesPropertyExist_1(m_xmpRef, nullptr, "property", &result), XMP_Error);

}



TEST_F(WXMPMetaTest_2019, DoesPropertyExist_EmptyPropertyName_2019) {

    WXMP_Result result = {};

    EXPECT_THROW(WXMPMeta_DoesPropertyExist_1(m_xmpRef, "http://example.com/schema", nullptr, &result), XMP_Error);

}



TEST_F(WXMPMetaTest_2019, DoesPropertyExist_EmptyBothParameters_2019) {

    WXMP_Result result = {};

    EXPECT_THROW(WXMPMeta_DoesPropertyExist_1(m_xmpRef, nullptr, nullptr, &result), XMP_Error);

}
