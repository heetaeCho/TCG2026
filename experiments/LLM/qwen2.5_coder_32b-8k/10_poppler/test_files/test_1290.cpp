#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-private.cc"



using namespace Poppler;

using ::testing::NiceMock;



// Mock FormField class for testing

class MockFormField : public FormField {

public:

    MOCK_CONST_METHOD0(m_formData, FormFieldData*());

};



// Mock DocumentData class for testing

class MockDocumentData : public DocumentData {};



// Mock Page class for testing

class MockPage : public ::Page {};



// Mock FormWidget class for testing

class MockFormWidget : public ::FormWidget {};



TEST_F(FormFieldDataTest_1290, GetFormWidget_ReturnsCorrectFormWidget_1290) {

    auto mockFormField = std::make_unique<NiceMock<MockFormField>>();

    auto mockDocumentData = std::make_unique<MockDocumentData>();

    auto mockPage = std::make_unique<MockPage>();

    auto expectedFormWidget = new MockFormWidget();



    FormFieldData formFieldData(mockDocumentData.get(), mockPage.get(), expectedFormWidget);



    EXPECT_CALL(*mockFormField, m_formData()).WillOnce(testing::Return(&formFieldData));



    FormWidget* result = formFieldData.getFormWidget(mockFormField.get());



    EXPECT_EQ(result, expectedFormWidget);

}



TEST_F(FormFieldDataTest_1290, GetFormWidget_ReturnsNullIfFormDataIsNull_1290) {

    auto mockFormField = std::make_unique<NiceMock<MockFormField>>();

    

    FormFieldData* formFieldData = nullptr;



    EXPECT_CALL(*mockFormField, m_formData()).WillOnce(testing::Return(formFieldData));



    FormWidget* result = formFieldData->getFormWidget(mockFormField.get());



    EXPECT_EQ(result, nullptr);

}

```


