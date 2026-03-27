#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-ps-converter.cc"

#include "./TestProjects/poppler/poppler/Annot.h"



using namespace Poppler;

using namespace Annot;



class AnnotDisplayDecideCbkTest : public ::testing::Test {

protected:

    void SetUp() override {

        user_data = new bool(true);

        annot = new MockAnnot();

    }



    void TearDown() override {

        delete user_data;

        delete annot;

    }



    bool* user_data;

    MockAnnot* annot;



    class MockAnnot : public Annot {

    public:

        MOCK_METHOD(AnnotSubtype, getType, (), (const, override));

    };

};



TEST_F(AnnotDisplayDecideCbkTest, WidgetAnnotationNeverHidden_1339) {

    EXPECT_CALL(*annot, getType()).WillOnce(::testing::Return(typeWidget));

    *user_data = false; // This should be ignored for typeWidget



    bool result = annotDisplayDecideCbk(annot, user_data);

    EXPECT_TRUE(result);

}



TEST_F(AnnotDisplayDecideCbkTest, NonWidgetAnnotationRespectsUserData_1339) {

    EXPECT_CALL(*annot, getType()).WillOnce(::testing::Return(typeText));

    *user_data = false;



    bool result = annotDisplayDecideCbk(annot, user_data);

    EXPECT_FALSE(result);

}



TEST_F(AnnotDisplayDecideCbkTest, NonWidgetAnnotationShownWhenUserDataTrue_1339) {

    EXPECT_CALL(*annot, getType()).WillOnce(::testing::Return(typeText));

    *user_data = true;



    bool result = annotDisplayDecideCbk(annot, user_data);

    EXPECT_TRUE(result);

}



TEST_F(AnnotDisplayDecideCbkTest, BoundaryConditionWithNullUserData_1339) {

    EXPECT_CALL(*annot, getType()).WillOnce(::testing::Return(typeText));



    bool* null_user_data = nullptr;

    bool result = annotDisplayDecideCbk(annot, null_user_data);

    EXPECT_FALSE(result); // Undefined behavior, assuming false for safety

}
