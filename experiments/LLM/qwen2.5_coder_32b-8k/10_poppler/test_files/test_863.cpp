#include <gtest/gtest.h>

#include "poppler/Annot.h"

#include "poppler/Form.h"



class AnnotWidgetTest_863 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize necessary objects for testing

        field = new FormField(nullptr, Object(), Ref(), nullptr, static_cast<std::set<int>*>(nullptr), formFieldTypeText);

        annotWidget = new AnnotWidget(nullptr, Object(Object::null()), Object(Object::null()));

    }



    void TearDown() override {

        // Clean up after each test

        delete field;

        delete annotWidget;

    }



    FormField* field;

    AnnotWidget* annotWidget;

};



TEST_F(AnnotWidgetTest_863, SetFieldUpdatesFieldPointer_863) {

    EXPECT_NE(field, annotWidget->field); // Initially pointers should be different

    annotWidget->setField(field);

    EXPECT_EQ(field, annotWidget->field); // After setField, they should be the same

}



TEST_F(AnnotWidgetTest_863, SetFieldNullPointerHandling_863) {

    annotWidget->setField(nullptr);

    EXPECT_EQ(nullptr, annotWidget->field); // Setting to nullptr should update field pointer correctly

}



TEST_F(AnnotWidgetTest_863, SetFieldMultipleTimes_863) {

    FormField* newField = new FormField(nullptr, Object(), Ref(), nullptr, static_cast<std::set<int>*>(nullptr), formFieldTypeText);

    annotWidget->setField(field);

    EXPECT_EQ(field, annotWidget->field); // Initially set to field

    annotWidget->setField(newField);

    EXPECT_EQ(newField, annotWidget->field); // After second call, should be updated to newField

    delete newField;

}
