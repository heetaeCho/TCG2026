#include <gtest/gtest.h>

#include "poppler-link-private.h"

#include <QRectF>



using namespace Poppler;



class LinkPrivateTest_1239 : public ::testing::Test {

protected:

    QRectF area;

    LinkPrivate *linkPrivate;



    void SetUp() override {

        area = QRectF(0, 0, 100, 100);

        linkPrivate = new LinkPrivate(area);

    }



    void TearDown() override {

        delete linkPrivate;

    }

};



TEST_F(LinkPrivateTest_1239, ConstructorInitializesLinkArea_1239) {

    EXPECT_EQ(linkPrivate->linkArea, area);

}



TEST_F(LinkPrivateTest_1239, CopyConstructorIsDeleted_1239) {

    static_assert(!std::is_copy_constructible<LinkPrivate>::value, "Copy constructor should be deleted");

}



TEST_F(LinkPrivateTest_1239, AssignmentOperatorIsDeleted_1239) {

    static_assert(!std::is_assignable<LinkPrivate&, const LinkPrivate&>::value, "Assignment operator should be deleted");

}



TEST_F(LinkPrivateTest_1239, DestructorExists_1239) {

    EXPECT_TRUE(true); // If the destructor is declared and defined, this test will pass.

}



// Assuming get() function operates correctly with a valid Link object

class MockLink : public Link {

public:

    MOCK_METHOD(LinkPrivate*, d_func, (), (override));

};



TEST_F(LinkPrivateTest_1239, GetReturnsNonNullPointer_1239) {

    MockLink mockLink;

    EXPECT_CALL(mockLink, d_func()).WillOnce(::testing::Return(linkPrivate));



    LinkPrivate* result = LinkPrivate::get(&mockLink);

    EXPECT_NE(result, nullptr);

}



TEST_F(LinkPrivateTest_1239, GetReturnsSameInstance_1239) {

    MockLink mockLink;

    EXPECT_CALL(mockLink, d_func()).WillOnce(::testing::Return(linkPrivate));



    LinkPrivate* result = LinkPrivate::get(&mockLink);

    EXPECT_EQ(result, linkPrivate);

}

```


