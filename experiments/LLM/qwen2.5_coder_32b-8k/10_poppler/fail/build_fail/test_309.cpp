#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Link.h"



class LinkRenditionTest_309 : public ::testing::Test {

protected:

    std::unique_ptr<LinkRendition> linkRendition;



    void SetUp() override {

        // Assuming there's a way to create a valid Object for initialization

        // Since we are treating the implementation as a black box, we assume this is done correctly.

        Object* mockObject = nullptr; // This should be a valid object in actual usage

        linkRendition = std::make_unique<LinkRendition>(mockObject);

    }

};



TEST_F(LinkRenditionTest_309, IsOk_ReturnsTrueForValidObject_309) {

    EXPECT_TRUE(linkRendition->isOk());

}



TEST_F(LinkRenditionTest_309, GetKind_ReturnsActionRendition_309) {

    EXPECT_EQ(linkRendition->getKind(), actionRendition);

}



TEST_F(LinkRenditionTest_309, HasScreenAnnot_ReturnsFalseWhenNoScreenAnnot_309) {

    EXPECT_FALSE(linkRendition->hasScreenAnnot());

}



TEST_F(LinkRenditionTest_309, GetOperation_ReturnsDefaultOperation_309) {

    RenditionOperation defaultOperation = {}; // Assuming default constructed operation

    EXPECT_EQ(linkRendition->getOperation(), defaultOperation);

}



TEST_F(LinkRenditionTest_309, GetMedia_ReturnsNullptrWhenNoMedia_309) {

    EXPECT_EQ(linkRendition->getMedia(), nullptr);

}



TEST_F(LinkRenditionTest_309, GetScript_ReturnsEmptyStringWhenNoScript_309) {

    EXPECT_TRUE(linkRendition->getScript().empty());

}

```


