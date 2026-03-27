#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Form.h"



class MockFormField : public FormField {

public:

    MOCK_METHOD(int, getNumChildren, (), (const override));

    MOCK_METHOD(FormField*, getChildren, (int), (const override));

    MOCK_METHOD(FormFieldType, getType, (), (const override));

};



using ::testing::Return;

using ::testing::ElementsAre;



class PDFDocTest_1855 : public ::testing::Test {

protected:

    MockFormField* formFieldMock;

    

    void SetUp() override {

        formFieldMock = new MockFormField();

    }



    void TearDown() override {

        delete formFieldMock;

    }

};



TEST_F(PDFDocTest_1855, NoChildrenNoSignatureField_1855) {

    std::vector<FormFieldSignature*> result;

    EXPECT_CALL(*formFieldMock, getNumChildren()).WillOnce(Return(0));

    EXPECT_CALL(*formFieldMock, getType()).WillOnce(Return(formText));



    addSignatureFieldsToVector(formFieldMock, result);



    EXPECT_TRUE(result.empty());

}



TEST_F(PDFDocTest_1855, NoChildrenWithSignatureField_1855) {

    std::vector<FormFieldSignature*> result;

    EXPECT_CALL(*formFieldMock, getNumChildren()).WillOnce(Return(0));

    EXPECT_CALL(*formFieldMock, getType()).WillOnce(Return(formSignature));



    addSignatureFieldsToVector(formFieldMock, result);



    EXPECT_EQ(result.size(), 1);

}



TEST_F(PDFDocTest_1855, SingleChildNotSignature_1855) {

    std::vector<FormFieldSignature*> result;

    auto* childMock = new MockFormField();

    EXPECT_CALL(*formFieldMock, getNumChildren()).WillOnce(Return(1));

    EXPECT_CALL(*formFieldMock, getChildren(0)).WillOnce(Return(childMock));

    EXPECT_CALL(*childMock, getType()).WillOnce(Return(formText));



    addSignatureFieldsToVector(formFieldMock, result);



    EXPECT_TRUE(result.empty());

}



TEST_F(PDFDocTest_1855, SingleChildIsSignature_1855) {

    std::vector<FormFieldSignature*> result;

    auto* childMock = new MockFormField();

    EXPECT_CALL(*formFieldMock, getNumChildren()).WillOnce(Return(1));

    EXPECT_CALL(*formFieldMock, getChildren(0)).WillOnce(Return(childMock));

    EXPECT_CALL(*childMock, getType()).WillOnce(Return(formSignature));



    addSignatureFieldsToVector(formFieldMock, result);



    EXPECT_EQ(result.size(), 1);

}



TEST_F(PDFDocTest_1855, MultipleChildrenWithMixedTypes_1855) {

    std::vector<FormFieldSignature*> result;

    auto* childMock1 = new MockFormField();

    auto* childMock2 = new MockFormField();

    EXPECT_CALL(*formFieldMock, getNumChildren()).WillOnce(Return(2));

    EXPECT_CALL(*formFieldMock, getChildren(0)).WillOnce(Return(childMock1));

    EXPECT_CALL(*formFieldMock, getChildren(1)).WillOnce(Return(childMock2));

    EXPECT_CALL(*childMock1, getType()).WillOnce(Return(formText));

    EXPECT_CALL(*childMock2, getType()).WillOnce(Return(formSignature));



    addSignatureFieldsToVector(formFieldMock, result);



    EXPECT_EQ(result.size(), 1);

}



TEST_F(PDFDocTest_1855, MultipleChildrenAllSignatures_1855) {

    std::vector<FormFieldSignature*> result;

    auto* childMock1 = new MockFormField();

    auto* childMock2 = new MockFormField();

    EXPECT_CALL(*formFieldMock, getNumChildren()).WillOnce(Return(2));

    EXPECT_CALL(*formFieldMock, getChildren(0)).WillOnce(Return(childMock1));

    EXPECT_CALL(*formFieldMock, getChildren(1)).WillOnce(Return(childMock2));

    EXPECT_CALL(*childMock1, getType()).WillOnce(Return(formSignature));

    EXPECT_CALL(*childMock2, getType()).WillOnce(Return(formSignature));



    addSignatureFieldsToVector(formFieldMock, result);



    EXPECT_EQ(result.size(), 2);

}



TEST_F(PDFDocTest_1855, NestedChildrenWithSignatures_1855) {

    std::vector<FormFieldSignature*> result;

    auto* childMock1 = new MockFormField();

    auto* grandChildMock = new MockFormField();

    EXPECT_CALL(*formFieldMock, getNumChildren()).WillOnce(Return(1));

    EXPECT_CALL(*formFieldMock, getChildren(0)).WillOnce(Return(childMock1));

    EXPECT_CALL(*childMock1, getNumChildren()).WillOnce(Return(1));

    EXPECT_CALL(*childMock1, getChildren(0)).WillOnce(Return(grandChildMock));

    EXPECT_CALL(*grandChildMock, getType()).WillOnce(Return(formSignature));



    addSignatureFieldsToVector(formFieldMock, result);



    EXPECT_EQ(result.size(), 1);

}
