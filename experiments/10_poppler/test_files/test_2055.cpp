#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.cc"



// Mocking external collaborators if any are needed.

// In this case, we don't have any direct external collaborators to mock.



class PopplerAnnotCircleTest : public ::testing::Test {

protected:

    // Setup and teardown can be used if necessary.

    void SetUp() override {

        // Initialization code here if needed

    }



    void TearDown() override {

        // Cleanup code here if needed

    }

};



TEST_F(PopplerAnnotCircleTest_2055, CreateCircleAnnotation_ReturnsNonNullPointer_2055) {

    std::shared_ptr<Annot> mockAnnot = std::make_shared<Annot>(); // Assuming Annot is a valid class

    PopplerAnnot* circleAnnot = _poppler_annot_circle_new(mockAnnot);

    EXPECT_NE(circleAnnot, nullptr);

}



TEST_F(PopplerAnnotCircleTest_2055, CreateCircleAnnotation_WithNullSharedAnnot_ReturnsNonNullPointer_2055) {

    std::shared_ptr<Annot> nullAnnot = nullptr;

    PopplerAnnot* circleAnnot = _poppler_annot_circle_new(nullAnnot);

    EXPECT_NE(circleAnnot, nullptr);

}



// Assuming there are no exceptional or error cases observable through the interface

// as the function signature does not suggest any.



```


