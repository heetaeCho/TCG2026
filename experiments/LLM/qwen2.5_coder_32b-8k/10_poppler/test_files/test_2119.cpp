#include <gtest/gtest.h>

#include "poppler-annot.h"

#include "glib/poppler-annot.h"



// Mock class to simulate PopplerAnnotStamp

class MockPopplerAnnotStamp : public _PopplerAnnotStamp {

public:

    MOCK_METHOD(const std::string&, getIcon, (), (const));

};



// Fixture for tests

class PopplerAnnotStampTest_2119 : public ::testing::Test {

protected:

    MockPopplerAnnotStamp* mock_stamp;



    void SetUp() override {

        mock_stamp = new MockPopplerAnnotStamp();

    }



    void TearDown() override {

        delete mock_stamp;

    }

};



TEST_F(PopplerAnnotStampTest_2119, GetIconUnknown_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return(""));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_UNKNOWN);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconApproved_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("Approved"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_APPROVED);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconAsIs_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("AsIs"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_AS_IS);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconConfidential_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("Confidential"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconFinal_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("Final"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_FINAL);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconExperimental_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("Experimental"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconExpired_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("Expired"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_EXPIRED);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconNotApproved_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("NotApproved"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconNotForPublicRelease_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("NotForPublicRelease"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconSold_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("Sold"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_SOLD);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconDepartmental_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("Departmental"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconForComment_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("ForComment"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconForPublicRelease_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("ForPublicRelease"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconTopSecret_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("TopSecret"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_TOP_SECRET);

}



TEST_F(PopplerAnnotStampTest_2119, GetIconNone_2119) {

    EXPECT_CALL(*mock_stamp, getIcon()).WillOnce(::testing::Return("SomeUnknownValue"));

    EXPECT_EQ(poppler_annot_stamp_get_icon(reinterpret_cast<PopplerAnnotStamp*>(mock_stamp)), POPPLER_ANNOT_STAMP_ICON_UNKNOWN);

}
