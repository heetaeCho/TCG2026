#include <gtest/gtest.h>

#include "Form.h"



using namespace std;



class FormFieldTest_887 : public ::testing::Test {

protected:

    PDFDoc *docA;

    Object aobj;

    Ref aref;

    FormField *parent;

    set<int> usedParentsSet;

    int usedParentsInt;

    FormFieldType type;



    void SetUp() override {

        docA = nullptr; // Assuming PDFDoc is a pointer and we don't need to initialize it for this test

        parent = nullptr; // Similarly, FormField* parent is not needed for the tests based on the interface provided

        usedParentsSet.clear();

        usedParentsInt = 0;

        type = formUnknown; // Default type

    }



    void TearDown() override {

        delete parent;

        parent = nullptr;

    }

};



TEST_F(FormFieldTest_887, GetPartialName_ReturnsNullptrWhenNotSet_887) {

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    EXPECT_EQ(field.getPartialName(), nullptr);

}



TEST_F(FormFieldTest_887, SetAndGetPartialName_Functionality_887) {

    GooString expected("testPartialName");

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    field.setPartialName(expected);



    const GooString *result = field.getPartialName();

    EXPECT_NE(result, nullptr);

    EXPECT_STREQ(result->getCString(), expected.getCString());

}



TEST_F(FormFieldTest_887, SetAndGetPartialName_MultipleTimes_887) {

    GooString name1("name1");

    GooString name2("name2");



    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    field.setPartialName(name1);



    EXPECT_STREQ(field.getPartialName()->getCString(), name1.getCString());



    field.setPartialName(name2);

    EXPECT_STREQ(field.getPartialName()->getCString(), name2.getCString());

}



TEST_F(FormFieldTest_887, SetReadOnly_Functionality_887) {

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    

    field.setReadOnly(true);

    EXPECT_TRUE(field.isReadOnly());



    field.setReadOnly(false);

    EXPECT_FALSE(field.isReadOnly());

}



TEST_F(FormFieldTest_887, SetDefaultAppearance_Functionality_887) {

    string appearance("testAppearance");

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    

    field.setDefaultAppearance(appearance);

    EXPECT_STREQ(field.getDefaultAppearance()->getCString(), appearance.c_str());

}



TEST_F(FormFieldTest_887, FindWidgetByRef_ReturnsNullptrWhenNoWidgets_887) {

    Ref someRef;

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    

    EXPECT_EQ(field.findWidgetByRef(someRef), nullptr);

}



TEST_F(FormFieldTest_887, FindFieldByFullyQualifiedName_ReturnsNullptrWhenNotFound_887) {

    string name("nonExistentField");

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);



    EXPECT_EQ(field.findFieldByFullyQualifiedName(name), nullptr);

}



TEST_F(FormFieldTest_887, GetNumWidgets_ReturnsZeroWhenNoWidgets_887) {

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    

    EXPECT_EQ(field.getNumWidgets(), 0);

}



TEST_F(FormFieldTest_887, GetWidget_OutOfBoundsReturnsNullptr_887) {

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);



    EXPECT_EQ(field.getWidget(0), nullptr); // Assuming there are no widgets

}



TEST_F(FormFieldTest_887, GetNumChildren_ReturnsZeroWhenNoChildren_887) {

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    

    EXPECT_EQ(field.getNumChildren(), 0);

}



TEST_F(FormFieldTest_887, GetChildren_OutOfBoundsReturnsNullptr_887) {

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);



    EXPECT_EQ(field.getChildren(0), nullptr); // Assuming there are no children

}



TEST_F(FormFieldTest_887, GetNoExport_ReturnsFalseByDefault_887) {

    FormField field(docA, move(aobj), aref, parent, &usedParentsSet, type);

    

    EXPECT_FALSE(field.getNoExport());

}
