#include <gtest/gtest.h>

#include "Page.h"

#include "Object.h"



class PageAttrsTest_700 : public ::testing::Test {

protected:

    Dict dict;

    PageAttrs pageAttrs{nullptr, &dict};



    void SetUp() override {

        // Setup any state needed before each test.

    }



    void TearDown() override {

        // Cleanup after each test if necessary.

    }

};



TEST_F(PageAttrsTest_700, ReplaceResource_NormalOperation_700) {

    Object newObj{42};

    pageAttrs.replaceResource(std::move(newObj));

    EXPECT_TRUE(pageAttrs.getResourceDictObject()->isInt());

    EXPECT_EQ(42, pageAttrs.getResourceDictObject()->getInt());

}



TEST_F(PageAttrsTest_700, ReplaceResource_BoundaryCondition_EmptyObject_700) {

    Object newObj{};

    pageAttrs.replaceResource(std::move(newObj));

    EXPECT_TRUE(pageAttrs.getResourceDictObject()->isNone());

}



TEST_F(PageAttrsTest_700, ReplaceResource_ExceptionalCase_ErrorObject_700) {

    Object newObj = Object::error();

    pageAttrs.replaceResource(std::move(newObj));

    EXPECT_TRUE(pageAttrs.getResourceDictObject()->isError());

}
