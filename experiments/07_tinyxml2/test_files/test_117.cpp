#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <memory>



using namespace tinyxml2;



class XMLDocumentTest_117 : public ::testing::Test {

protected:

    std::unique_ptr<XMLDocument> doc1;

    std::unique_ptr<XMLDocument> doc2;



    void SetUp() override {

        doc1 = std::make_unique<XMLDocument>();

        doc2 = std::make_unique<XMLDocument>();

    }

};



TEST_F(XMLDocumentTest_117, ShallowEqual_ReturnsFalseForDifferentObjects_117) {

    EXPECT_FALSE(doc1->ShallowEqual(doc2.get()));

}



TEST_F(XMLDocumentTest_117, ShallowEqual_ReturnsTrueForSameObject_117) {

    EXPECT_TRUE(doc1->ShallowEqual(doc1.get()));

}
