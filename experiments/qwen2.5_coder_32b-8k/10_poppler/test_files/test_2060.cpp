#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.h"



using namespace testing;



class PopplerAnnotTest_2060 : public ::testing::Test {

protected:

    std::shared_ptr<Annot> mockAnnot;

    

    void SetUp() override {

        mockAnnot = std::make_shared<Annot>();

    }

};



TEST_F(PopplerAnnotTest_2060, CreateStampAnnotation_NormalOperation_2060) {

    PopplerAnnot* popplerAnnot = _poppler_annot_stamp_new(mockAnnot);

    EXPECT_NE(popplerAnnot, nullptr);

}



TEST_F(PopplerAnnotTest_2060, CreateStampAnnotation_NullptrAnnot_2060) {

    std::shared_ptr<Annot> nullAnnot;

    PopplerAnnot* popplerAnnot = _poppler_annot_stamp_new(nullAnnot);

    EXPECT_EQ(popplerAnnot, nullptr);

}



TEST_F(PopplerAnnotTest_2060, CreateStampAnnotation_BoundaryConditions_2060) {

    // Assuming boundary condition here is to test with a valid annot

    PopplerAnnot* popplerAnnot = _poppler_annot_stamp_new(mockAnnot);

    EXPECT_NE(popplerAnnot, nullptr);

}



// Since the function does not throw exceptions or have observable error cases,

// we do not need additional tests for exceptional cases.

```


