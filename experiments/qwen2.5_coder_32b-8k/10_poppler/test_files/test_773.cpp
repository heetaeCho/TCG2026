#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"



using namespace poppler;



class AnnotAppearanceCharacsTest : public ::testing::Test {

protected:

    Dict* dict;

    std::unique_ptr<AnnotAppearanceCharacs> annotAppearanceCharacs;



    void SetUp() override {

        dict = new Dict();

        annotAppearanceCharacs = std::make_unique<AnnotAppearanceCharacs>(dict);

    }



    void TearDown() override {

        delete dict;

    }

};



TEST_F(AnnotAppearanceCharacsTest_773, GetPositionDefault_773) {

    EXPECT_EQ(annotAppearanceCharacs->getPosition(), AnnotAppearanceCharacsTextPos::defaultPosition);

}



TEST_F(AnnotAppearanceCharacsTest_773, CopyConstructorDeleted_773) {

    EXPECT_FALSE(std::is_copy_constructible<AnnotAppearanceCharacs>::value);

}



TEST_F(AnnotAppearanceCharacsTest_773, AssignmentOperatorDeleted_773) {

    EXPECT_FALSE(std::is_assignable<AnnotAppearanceCharacs&, AnnotAppearanceCharacs&>::value);

}

```


