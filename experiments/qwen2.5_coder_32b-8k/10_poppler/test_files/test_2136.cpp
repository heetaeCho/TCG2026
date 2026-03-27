#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming PopplerAnnot and Annot are defined in some header file

class PopplerAnnot {

public:

    virtual ~PopplerAnnot() = default;

};



class Annot {

public:

    virtual ~Annot() = default;

};



extern "C" {

    PopplerAnnot* _poppler_annot_ink_new(const std::shared_ptr<Annot> &annot);

}



class PopplerAnnotTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(PopplerAnnotTest_2136, NewInkAnnotationReturnsNonNullPointer_2136) {

    auto annot = std::make_shared<Annot>();

    PopplerAnnot* poppler_annot = _poppler_annot_ink_new(annot);

    ASSERT_NE(poppler_annot, nullptr);

}



TEST_F(PopplerAnnotTest_2136, NewInkAnnotationWithNullAnnotReturnsNullPointer_2136) {

    std::shared_ptr<Annot> annot = nullptr;

    PopplerAnnot* poppler_annot = _poppler_annot_ink_new(annot);

    ASSERT_EQ(poppler_annot, nullptr);

}



// Additional test cases can be added here if there are more observable behaviors

```


