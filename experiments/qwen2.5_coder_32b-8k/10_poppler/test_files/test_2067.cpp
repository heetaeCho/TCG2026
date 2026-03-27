#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.cc"



using namespace ::testing;



class PopplerAnnotTest_2067 : public Test {

protected:

    struct _PopplerAnnot* poppler_annot;



    void SetUp() override {

        // Mock the creation of a valid PopplerAnnot object

        poppler_annot = reinterpret_cast<struct _PopplerAnnot*>(g_malloc(sizeof(struct _PopplerAnnot)));

        poppler_annot->annot = std::make_shared<Annot>();

    }



    void TearDown() override {

        g_free(poppler_annot);

    }

};



TEST_F(PopplerAnnotTest_2067, GetFlagsReturnsDefaultFlag_2067) {

    // Assuming the default flag is 0 if not set otherwise

    EXPECT_EQ(poppler_annot_get_flags(poppler_annot), static_cast<PopplerAnnotFlag>(0));

}



TEST_F(PopplerAnnotTest_2067, GetFlagsReturnsSetFlag_2067) {

    // Assuming we can modify the internal state for testing purposes

    poppler_annot->annot->setFlags(1); // Hypothetical method to set flags for testing

    EXPECT_EQ(poppler_annot_get_flags(poppler_annot), static_cast<PopplerAnnotFlag>(1));

}



TEST_F(PopplerAnnotTest_2067, GetFlagsWithNullPointer_2067) {

    EXPECT_EQ(poppler_annot_get_flags(nullptr), static_cast<PopplerAnnotFlag>(0));

}



TEST_F(PopplerAnnotTest_2067, GetFlagsWithInvalidObject_2067) {

    // Assuming there's a way to create an invalid object for testing

    struct _PopplerAnnot* invalid_poppler_annot = reinterpret_cast<struct _PopplerAnnot*>(g_malloc(sizeof(struct _PopplerAnnot)));

    EXPECT_EQ(poppler_annot_get_flags(invalid_poppler_annot), static_cast<PopplerAnnotFlag>(0));

    g_free(invalid_poppler_annot);

}

```


