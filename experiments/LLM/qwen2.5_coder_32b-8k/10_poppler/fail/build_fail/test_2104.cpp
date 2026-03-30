#include <gtest/gtest.h>

#include "poppler-annot.h"

#include "gmock/gmock.h"



using namespace testing;



// Mock class for PopplerAttachment to verify interactions

class MockPopplerAttachment {

public:

    MOCK_METHOD0(getFileName, const GooString*());

};



TEST_F(PopplerAnnotFileAttachmentTest_2104, GetAttachmentNormalOperation_2104) {

    // Arrange

    AnnotFileAttachment annot(nullptr, nullptr);

    Object file;

    EXPECT_CALL(annot, getFile()).WillOnce(Return(&file));

    

    PopplerAnnotFileAttachment poppler_annot = {};

    static_cast<PopplerAnnot*>(&poppler_annot)->annot.reset(&annot);



    // Act

    PopplerAttachment* attachment = poppler_annot_file_attachment_get_attachment(&poppler_annot);



    // Assert

    ASSERT_NE(attachment, nullptr);

}



TEST_F(PopplerAnnotFileAttachmentTest_2104, GetAttachmentNullInput_2104) {

    // Arrange

    PopplerAnnotFileAttachment* poppler_annot = nullptr;



    // Act & Assert

    EXPECT_EQ(poppler_annot_file_attachment_get_attachment(poppler_annot), nullptr);

}



TEST_F(PopplerAnnotFileAttachmentTest_2104, GetAttachmentInvalidType_2104) {

    // Arrange

    struct _PopplerAnnot poppler_annot = {};

    

    // Act & Assert

    EXPECT_EQ(poppler_annot_file_attachment_get_attachment(reinterpret_cast<PopplerAnnotFileAttachment*>(&poppler_annot)), nullptr);

}



TEST_F(PopplerAnnotFileAttachmentTest_2104, GetAttachmentValidFileObject_2104) {

    // Arrange

    AnnotFileAttachment annot(nullptr, nullptr);

    Object file;

    EXPECT_CALL(annot, getFile()).WillOnce(Return(&file));

    

    PopplerAnnotFileAttachment poppler_annot = {};

    static_cast<PopplerAnnot*>(&poppler_annot)->annot.reset(&annot);



    // Act

    PopplerAttachment* attachment = poppler_annot_file_attachment_get_attachment(&poppler_annot);



    // Assert

    ASSERT_NE(attachment, nullptr);

    EXPECT_TRUE(attachment->isOk());

}



TEST_F(PopplerAnnotFileAttachmentTest_2104, GetAttachmentInvalidFileObject_2104) {

    // Arrange

    AnnotFileAttachment annot(nullptr, nullptr);

    Object file;

    EXPECT_CALL(annot, getFile()).WillOnce(Return(&file));

    

    PopplerAnnotFileAttachment poppler_annot = {};

    static_cast<PopplerAnnot*>(&poppler_annot)->annot.reset(&annot);



    // Act

    PopplerAttachment* attachment = poppler_annot_file_attachment_get_attachment(&poppler_annot);



    // Assert

    ASSERT_NE(attachment, nullptr);

    EXPECT_TRUE(attachment->isOk());

}
