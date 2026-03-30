#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external collaborators if needed

class MockPopplerAnnot {

public:

    MOCK_METHOD(PopplerColor*, poppler_annot_geometry_get_interior_color, (PopplerAnnot*), ());

};



extern "C" {

    struct _PopplerAnnotCircle { };

    typedef struct _PopplerAnnotCircle PopplerAnnotCircle;



    struct _PopplerColor { };

    typedef struct _PopplerColor PopplerColor;



    extern PopplerColor* poppler_annot_geometry_get_interior_color(PopplerAnnot*);

}



// Test fixture

class PopplerAnnotCircleTest : public ::testing::Test {

protected:

    MockPopplerAnnot mock_poppler_annot;

    PopplerAnnotCircle* annot_circle;



    void SetUp() override {

        annot_circle = reinterpret_cast<PopplerAnnotCircle*>(new _PopplerAnnotCircle());

    }



    void TearDown() override {

        delete reinterpret_cast<_PopplerAnnotCircle*>(annot_circle);

    }

};



// Test cases

TEST_F(PopplerAnnotCircleTest, GetInteriorColor_ReturnsValidColor_2115) {

    PopplerColor expected_color;

    EXPECT_CALL(mock_poppler_annot, poppler_annot_geometry_get_interior_color(POPPLER_ANNOT(annot_circle)))

        .WillOnce(::testing::Return(&expected_color));



    PopplerColor* result = poppler_annot_circle_get_interior_color(annot_circle);

    ASSERT_EQ(result, &expected_color);

}



TEST_F(PopplerAnnotCircleTest, GetInteriorColor_ReturnsNullForInvalidAnnot_2115) {

    EXPECT_CALL(mock_poppler_annot, poppler_annot_geometry_get_interior_color(::testing::_))

        .Times(0);



    PopplerColor* result = poppler_annot_circle_get_interior_color(nullptr);

    ASSERT_EQ(result, nullptr);

}



// Assuming no exceptional or boundary conditions are observable through the interface for this function

```


