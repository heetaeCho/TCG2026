#include <gtest/gtest.h>

#include "Annot.h"



class AnnotLineTest_829 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotLine> annot_line;



    void SetUp() override {

        // Assuming a mock PDFDoc and PDFRectangle are available or can be constructed

        // For the sake of this example, we will assume they are provided or can be mocked if necessary.

        // Since we cannot access private members, we will focus on public methods and their observable behavior.

        annot_line = std::make_unique<AnnotLine>(nullptr, nullptr);

    }

};



TEST_F(AnnotLineTest_829, GetCaption_DefaultValue_829) {

    EXPECT_EQ(annot_line->getCaption(), false);

}



TEST_F(AnnotLineTest_829, SetCaption_Toggle_829) {

    annot_line->setCaption(true);

    EXPECT_EQ(annot_line->getCaption(), true);



    annot_line->setCaption(false);

    EXPECT_EQ(annot_line->getCaption(), false);

}



TEST_F(AnnotLineTest_829, SetCaption_MultipleTimes_829) {

    annot_line->setCaption(true);

    annot_line->setCaption(true);

    EXPECT_EQ(annot_line->getCaption(), true);



    annot_line->setCaption(false);

    annot_line->setCaption(false);

    EXPECT_EQ(annot_line->getCaption(), false);

}
