#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Page.h"



using namespace testing;



class MockDict : public Dict {

public:

    MOCK_METHOD(Dict*, getGroup, (), (override));

};



class PageTest_716 : public Test {

protected:

    std::unique_ptr<MockDict> mockDict;

    std::unique_ptr<PageAttrs> attrs;

    Page* page;



    void SetUp() override {

        mockDict = std::make_unique<MockDict>();

        attrs = std::make_unique<PageAttrs>(nullptr, mockDict.get());

        page = new Page(nullptr, 1, Object(), Ref(0, 0), std::move(attrs));

    }



    void TearDown() override {

        delete page;

    }

};



TEST_F(PageTest_716, GetGroup_ReturnsExpectedValue_716) {

    Dict* expectedGroup = mockDict.get();

    EXPECT_CALL(*mockDict, getGroup()).WillOnce(Return(expectedGroup));



    Dict* actualGroup = page->getGroup();



    EXPECT_EQ(actualGroup, expectedGroup);

}



TEST_F(PageTest_716, GetGroup_ReturnsNullPtrWhenNoGroup_716) {

    EXPECT_CALL(*mockDict, getGroup()).WillOnce(Return(nullptr));



    Dict* actualGroup = page->getGroup();



    EXPECT_EQ(actualGroup, nullptr);

}
