#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Annot.h"

#include "poppler/GooString.h"



class AnnotMarkupTest_797 : public ::testing::Test {

protected:

    AnnotMarkup* annotMarkup;



    void SetUp() override {

        // Assuming a mock PDFDoc and PDFRectangle are available or can be created

        // For the purpose of this test, we will not create them as they are not relevant to the interface being tested

        annotMarkup = new AnnotMarkup(nullptr, nullptr);

    }



    void TearDown() override {

        delete annotMarkup;

    }

};



TEST_F(AnnotMarkupTest_797, GetLabel_ReturnsNullptrByDefault_797) {

    EXPECT_EQ(annotMarkup->getLabel(), nullptr);

}



TEST_F(AnnotMarkupTest_797, SetLabelAndGetLabel_ReturnsCorrectValue_797) {

    std::unique_ptr<GooString> label = std::make_unique<GooString>("Test Label");

    annotMarkup->setLabel(std::move(label));

    EXPECT_STREQ(annotMarkup->getLabel()->c_str(), "Test Label");

}



TEST_F(AnnotMarkupTest_797, SetLabelWithNullptr_GetLabelReturnsNullptr_797) {

    std::unique_ptr<GooString> label = nullptr;

    annotMarkup->setLabel(std::move(label));

    EXPECT_EQ(annotMarkup->getLabel(), nullptr);

}
