#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLTextTest_64 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLText* xmlText;



    void SetUp() override {

        xmlText = new XMLText(&doc);

    }



    void TearDown() override {

        delete xmlText;

    }

};



TEST_F(XMLTextTest_64, InitialCDataStateIsFalse_64) {

    EXPECT_FALSE(xmlText->CData());

}



TEST_F(XMLTextTest_64, SetCDataToTrueAndGetTrue_64) {

    xmlText->SetCData(true);

    EXPECT_TRUE(xmlText->CData());

}



TEST_F(XMLTextTest_64, SetCDataToFalseAndGetFalse_64) {

    xmlText->SetCData(false);

    EXPECT_FALSE(xmlText->CData());

}



TEST_F(XMLTextTest_64, ToggleCDataMultipleTimes_64) {

    xmlText->SetCData(true);

    EXPECT_TRUE(xmlText->CData());



    xmlText->SetCData(false);

    EXPECT_FALSE(xmlText->CData());



    xmlText->SetCData(true);

    EXPECT_TRUE(xmlText->CData());

}
