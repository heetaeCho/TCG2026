#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers and namespaces are included

extern "C" {

    PopplerAnnot *_poppler_annot_square_new(const std::shared_ptr<Annot> &annot);

}



class PopplerAnnotTest_2057 : public ::testing::Test {

protected:

    // Setup and teardown can be added if necessary in the future

};



TEST_F(PopplerAnnotTest_2057, CreateSquareAnnotation_NormalOperation_2057) {

    std::shared_ptr<Annot> annot = std::make_shared<Annot>(); // Assuming Annot is a valid class

    PopplerAnnot* squareAnnot = _poppler_annot_square_new(annot);

    

    EXPECT_NE(squareAnnot, nullptr);

}



TEST_F(PopplerAnnotTest_2057, CreateSquareAnnotation_NullptrInput_2057) {

    std::shared_ptr<Annot> annot = nullptr;

    PopplerAnnot* squareAnnot = _poppler_annot_square_new(annot);

    

    EXPECT_EQ(squareAnnot, nullptr); // Assuming a nullptr input results in a nullptr output

}



TEST_F(PopplerAnnotTest_2057, CreateSquareAnnotation_MultipleCalls_2057) {

    std::shared_ptr<Annot> annot1 = std::make_shared<Annot>();

    std::shared_ptr<Annot> annot2 = std::make_shared<Annot>();



    PopplerAnnot* squareAnnot1 = _poppler_annot_square_new(annot1);

    PopplerAnnot* squareAnnot2 = _poppler_annot_square_new(annot2);



    EXPECT_NE(squareAnnot1, nullptr);

    EXPECT_NE(squareAnnot2, nullptr);

    EXPECT_NE(squareAnnot1, squareAnnot2); // Assuming different inputs produce different outputs

}



// Additional test cases can be added based on observable behavior and requirements
