#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDocumentTest_326 : public ::testing::Test {

protected:

    void SetUp() override {

        doc = new XMLDocument();

    }



    void TearDown() override {

        delete doc;

    }



    XMLDocument* doc;

};



TEST_F(XMLDocumentTest_326, DepthTrackerConstructorIncreasesDepth_326) {

    int initialDepth = doc->_parsingDepth;

    {

        DepthTracker tracker(doc);

        EXPECT_EQ(doc->_parsingDepth, initialDepth + 1);

    }

}



TEST_F(XMLDocumentTest_326, DepthTrackerDestructorDecreasesDepth_326) {

    int initialDepth = doc->_parsingDepth;

    {

        DepthTracker tracker(doc);

    }

    EXPECT_EQ(doc->_parsingDepth, initialDepth);

}
