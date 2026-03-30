#include <gtest/gtest.h>

#include "XMPMeta.hpp"



class MigrateAudioCopyrightTest : public ::testing::Test {

protected:

    XMPMeta xmp;

    XMP_Node dmCopyright;



    void SetUp() override {

        dmCopyright = XMP_Node(nullptr, "copyright", "", 0);

    }

};



TEST_F(MigrateAudioCopyrightTest_1967, DC_Rights_Array_Not_Exist_1967) {

    MigrateAudioCopyright(&xmp, &dmCopyright);



    XMP_StringPtr value;

    XMP_StringLen size;

    ASSERT_TRUE(xmp.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default", nullptr, nullptr, &value, &size));

    EXPECT_STREQ(value, "\xA\xAdmValue");

}



TEST_F(MigrateAudioCopyrightTest_1967, DC_Rights_Array_Empty_1967) {

    XMP_Node dcSchema(nullptr, kXMP_NS_DC, 0);

    xmp.tree = dcSchema;



    MigrateAudioCopyright(&xmp, &dmCopyright);



    XMP_StringPtr value;

    XMP_StringLen size;

    ASSERT_TRUE(xmp.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default", nullptr, nullptr, &value, &size));

    EXPECT_STREQ(value, "\xA\xAdmValue");

}



TEST_F(MigrateAudioCopyrightTest_1967, DC_Rights_Array_No_XDefault_1967) {

    XMP_Node dcSchema(nullptr, kXMP_NS_DC, 0);

    xmp.tree = dcSchema;

    XMP_Node dcRightsArray(&dcSchema, "rights", 0);

    XMP_Node rightsValue(&dcRightsArray, "", "Existing Value", 0);

    dcRightsArray.children.push_back(&rightsValue);

    dcSchema.children.push_back(&dcRightsArray);



    MigrateAudioCopyright(&xmp, &dmCopyright);



    XMP_StringPtr value;

    XMP_StringLen size;

    ASSERT_TRUE(xmp.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default", nullptr, nullptr, &value, &size));

    EXPECT_STREQ(value, "Existing Value");

}



TEST_F(MigrateAudioCopyrightTest_1967, DC_Rights_Array_XDefault_Different_1967) {

    XMP_Node dcSchema(nullptr, kXMP_NS_DC, 0);

    xmp.tree = dcSchema;

    XMP_Node dcRightsArray(&dcSchema, "rights", 0);

    XMP_Node rightsValue(&dcRightsArray, "", "Existing Value\xA\xAOld Copyright", 0);

    dcRightsArray.children.push_back(&rightsValue);

    dcSchema.children.push_back(&dcRightsArray);



    MigrateAudioCopyright(&xmp, &dmCopyright);



    XMP_StringPtr value;

    XMP_StringLen size;

    ASSERT_TRUE(xmp.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default", nullptr, nullptr, &value, &size));

    EXPECT_STREQ(value, "Existing Value\xA\xAdmValue");

}



TEST_F(MigrateAudioCopyrightTest_1967, DC_Rights_Array_XDefault_Same_1967) {

    XMP_Node dcSchema(nullptr, kXMP_NS_DC, 0);

    xmp.tree = dcSchema;

    XMP_Node dcRightsArray(&dcSchema, "rights", 0);

    XMP_Node rightsValue(&dcRightsArray, "", "dmValue\xA\xAdmValue", 0);

    dcRightsArray.children.push_back(&rightsValue);

    dcSchema.children.push_back(&dcRightsArray);



    MigrateAudioCopyright(&xmp, &dmCopyright);



    XMP_StringPtr value;

    XMP_StringLen size;

    ASSERT_TRUE(xmp.GetLocalizedText(kXMP_NS_DC, "rights", "", "x-default", nullptr, nullptr, &value, &size));

    EXPECT_STREQ(value, "dmValue\xA\xAdmValue");

}



TEST_F(MigrateAudioCopyrightTest_1967, DM_Copyright_Deleted_1967) {

    MigrateAudioCopyright(&xmp, &dmCopyright);



    ASSERT_FALSE(xmp.DoesPropertyExist(kXMP_NS_DM, "copyright"));

}
