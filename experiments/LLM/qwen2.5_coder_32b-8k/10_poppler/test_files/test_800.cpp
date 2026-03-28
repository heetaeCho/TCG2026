#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotMarkupTest_800 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotMarkup> annot_markup;



    void SetUp() override {

        // Assuming a mock PDFDoc and PDFRectangle are available or can be mocked

        // For simplicity, we assume nullptrs here as they are not used in the tests based on provided interface

        annot_markup = std::make_unique<AnnotMarkup>(nullptr, nullptr);

    }

};



TEST_F(AnnotMarkupTest_800, GetDate_ReturnsNullptr_WhenNotSet_800) {

    EXPECT_EQ(annot_markup->getDate(), nullptr);

}



TEST_F(AnnotMarkupTest_800, SetAndGetDate_CorrectlySetsAndReturnsDate_800) {

    auto date = std::make_unique<GooString>("2023-10-05");

    annot_markup->setDate(std::move(date));

    EXPECT_STREQ(annot_markup->getDate()->c_str(), "2023-10-05");

}



TEST_F(AnnotMarkupTest_800, SetAndGetDate_HandlesNullptr_800) {

    annot_markup->setDate(nullptr);

    EXPECT_EQ(annot_markup->getDate(), nullptr);

}
