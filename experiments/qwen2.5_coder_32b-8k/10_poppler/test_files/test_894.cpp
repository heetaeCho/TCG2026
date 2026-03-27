#include <gtest/gtest.h>

#include "Form.h"

#include <memory>



class FormFieldTest_894 : public ::testing::Test {

protected:

    PDFDoc* docA;

    Object aobj;

    Ref aref;

    FormField* parent;

    std::set<int>* usedParents;

    FormFieldType fieldType;



    void SetUp() override {

        // Initialize necessary objects for testing

        docA = nullptr;  // Assuming PDFDoc is properly initialized elsewhere

        parent = nullptr;  // Assuming parent FormField is properly initialized elsewhere

        usedParents = new std::set<int>();

        fieldType = FormFieldType::PushButton;  // Example field type

    }



    void TearDown() override {

        delete usedParents;

    }

};



TEST_F(FormFieldTest_894, GetNoExport_DefaultValue_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    EXPECT_EQ(formField.getNoExport(), false);  // Assuming default value is false

}



TEST_F(FormFieldTest_894, SetReadOnly_NormalOperation_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    formField.setReadOnly(true);

    EXPECT_EQ(formField.isReadOnly(), true);  // Assuming isReadOnly() reflects the state

}



TEST_F(FormFieldTest_894, SetDefaultAppearance_NormalOperation_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    const std::string appearance = "/Helv 12 Tf";

    formField.setDefaultAppearance(appearance);

    EXPECT_STREQ(formField.getDefaultAppearance()->c_str(), appearance.c_str());

}



TEST_F(FormFieldTest_894, SetPartialName_NormalOperation_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    const GooString partialName("example");

    formField.setPartialName(partialName);

    EXPECT_STREQ(formField.getPartialName()->c_str(), "example");

}



TEST_F(FormFieldTest_894, GetFullyQualifiedName_NotNullPointer_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    const GooString* fullName = formField.getFullyQualifiedName();

    EXPECT_NE(fullName, nullptr);  // Assuming getFullyQualifiedName() never returns null

}



TEST_F(FormFieldTest_894, FindWidgetByRef_NotFound_ReturnsNull_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    Ref nonExistentRef;

    EXPECT_EQ(formField.findWidgetByRef(nonExistentRef), nullptr);  // Assuming findWidgetByRef returns null if not found

}



TEST_F(FormFieldTest_894, Reset_ExcludedFields_NormalOperation_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    const std::vector<std::string> excludedFields = {"field1", "field2"};

    EXPECT_NO_THROW(formField.reset(excludedFields));

}



TEST_F(FormFieldTest_894, FindFieldByRef_NotFound_ReturnsNull_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    Ref nonExistentRef;

    EXPECT_EQ(formField.findFieldByRef(nonExistentRef), nullptr);  // Assuming findFieldByRef returns null if not found

}



TEST_F(FormFieldTest_894, FindFieldByFullyQualifiedName_NotFound_ReturnsNull_894) {

    FormField formField(docA, std::move(aobj), aref, parent, usedParents, fieldType);

    const std::string nonExistentName = "nonexistent";

    EXPECT_EQ(formField.findFieldByFullyQualifiedName(nonExistentName), nullptr);  // Assuming findFieldByFullyQualifiedName returns null if not found

}
