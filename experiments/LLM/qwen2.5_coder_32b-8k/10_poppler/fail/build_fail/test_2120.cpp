#include <gtest/gtest.h>

#include "poppler-annot.h"

#include "Annot.h"



// Mock class to simulate AnnotStamp

class MockAnnotStamp : public AnnotStamp {

public:

    MOCK_METHOD(void, setIcon, (const std::string &new_icon), (override));

};



// Test fixture for PopplerAnnotStamp tests

class PopplerAnnotStampTest_2120 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_annot_stamp = new MockAnnotStamp();

        poppler_annot_stamp = static_cast<PopplerAnnotStamp*>(g_slice_alloc(sizeof(PopplerAnnotStamp)));

        POPPLER_ANNOT(poppler_annot_stamp)->annot.reset(mock_annot_stamp);

    }



    void TearDown() override {

        g_slice_free1(sizeof(PopplerAnnotStamp), poppler_annot_stamp);

    }



    PopplerAnnotStamp* poppler_annot_stamp;

    MockAnnotStamp* mock_annot_stamp;

};



TEST_F(PopplerAnnotStampTest_2120, SetIconToApproved_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("Approved"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_APPROVED);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToAsIs_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("AsIs"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_AS_IS);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToConfidential_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("Confidential"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_CONFIDENTIAL);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToFinal_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("Final"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_FINAL);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToExperimental_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("Experimental"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_EXPERIMENTAL);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToExpired_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("Expired"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_EXPIRED);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToNotApproved_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("NotApproved"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_NOT_APPROVED);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToNotForPublicRelease_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("NotForPublicRelease"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_NOT_FOR_PUBLIC_RELEASE);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToSold_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("Sold"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_SOLD);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToDepartmental_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("Departmental"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_DEPARTMENTAL);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToForComment_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("ForComment"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_FOR_COMMENT);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToForPublicRelease_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("ForPublicRelease"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_FOR_PUBLIC_RELEASE);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToTopSecret_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon("TopSecret"));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_TOP_SECRET);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToNone_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon(""));

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_NONE);

}



TEST_F(PopplerAnnotStampTest_2120, SetIconToUnknown_2120) {

    EXPECT_CALL(*mock_annot_stamp, setIcon).Times(0);

    poppler_annot_stamp_set_icon(poppler_annot_stamp, POPPLER_ANNOT_STAMP_ICON_UNKNOWN);

}
