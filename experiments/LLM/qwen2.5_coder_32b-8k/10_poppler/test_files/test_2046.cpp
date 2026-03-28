#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



using ::testing::Eq;

using ::testing::IsNull;



class PopplerAnnotFileAttachmentTest_2046 : public ::testing::Test {

protected:

    std::shared_ptr<Annot> mockAnnot;



    void SetUp() override {

        mockAnnot = std::make_shared<Annot>();

    }

};



TEST_F(PopplerAnnotFileAttachmentTest_2046, CreateValidAnnotation_2046) {

    PopplerAnnot* result = _poppler_annot_file_attachment_new(mockAnnot);

    EXPECT_NE(result, nullptr);

}



TEST_F(PopplerAnnotFileAttachmentTest_2046, NullptrWhenNullAnnotPassed_2046) {

    PopplerAnnot* result = _poppler_annot_file_attachment_new(nullptr);

    EXPECT_EQ(result, nullptr);

}
