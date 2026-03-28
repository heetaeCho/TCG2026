#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include "Object.h"

#include "XRef.h"



using namespace testing;



class MockXRef : public XRef {

public:

    MOCK_METHOD1(fetch, Object(Ref));

    MOCK_METHOD2(setModifiedObject, void(const Object*, Ref));

    MOCK_METHOD1(removeIndirectObject, void(Ref));

};



class OutlineItem {

public:

    virtual ~OutlineItem() = default;

    virtual Ref getRef() const = 0;

};



class MockOutlineItem : public OutlineItem {

public:

    MOCK_CONST_METHOD0(getRef, Ref());

};



TEST_F(TestFixture_1923, RemoveChildHelper_NormalOperation_1923) {

    MockXRef mockXRef;

    std::vector<MockOutlineItem*> items;

    items.push_back(new NiceMock<MockOutlineItem>());

    items.push_back(new NiceMock<MockOutlineItem>());



    Ref parentRef(1, 0);

    Ref itemRef1(2, 0);

    Ref itemRef2(3, 0);



    EXPECT_CALL(*items[0], getRef()).WillOnce(Return(itemRef1));

    EXPECT_CALL(*items[1], getRef()).WillRepeatedly(Return(itemRef2));



    Object parentDict;

    parentDict.dictSet("Count", Object(2));

    parentDict.dictSet("First", Object(itemRef1));

    parentDict.dictSet("Last", Object(itemRef2));



    Object itemDict1;

    itemDict1.dictSet("Parent", Object(parentRef));

    itemDict1.dictSet("Next", Object(itemRef2));



    Object itemDict2;

    itemDict2.dictSet("Parent", Object(parentRef));

    itemDict2.dictSet("Prev", Object(itemRef1));



    EXPECT_CALL(mockXRef, fetch(itemRef1)).WillOnce(Return(itemDict1));

    EXPECT_CALL(mockXRef, fetch(itemRef2)).WillOnce(Return(itemDict2));

    EXPECT_CALL(mockXRef, fetch(parentRef)).WillOnce(Return(parentDict));



    EXPECT_CALL(mockXRef, setModifiedObject(An<const Object*>(), parentRef))

        .Times(3); // Three times: decrement count, update First, remove Last

    EXPECT_CALL(mockXRef, removeIndirectObject(itemRef1));

    EXPECT_CALL(mockXRef, fetch(itemRef2, _)).WillOnce(Return(Object::null()));



    removeChildHelper(0, &mockXRef, items);



    ASSERT_EQ(items.size(), 1);

    delete items[0];

}



TEST_F(TestFixture_1923, RemoveChildHelper_BoundaryCondition_FirstItem_1923) {

    MockXRef mockXRef;

    std::vector<MockOutlineItem*> items;

    items.push_back(new NiceMock<MockOutlineItem>());



    Ref parentRef(1, 0);

    Ref itemRef(2, 0);



    EXPECT_CALL(*items[0], getRef()).WillOnce(Return(itemRef));



    Object parentDict;

    parentDict.dictSet("Count", Object(1));

    parentDict.dictSet("First", Object(itemRef));

    parentDict.dictSet("Last", Object(itemRef));



    Object itemDict;

    itemDict.dictSet("Parent", Object(parentRef));



    EXPECT_CALL(mockXRef, fetch(itemRef)).WillOnce(Return(itemDict));

    EXPECT_CALL(mockXRef, fetch(parentRef)).WillOnce(Return(parentDict));



    EXPECT_CALL(mockXRef, setModifiedObject(An<const Object*>(), parentRef))

        .Times(3); // Three times: decrement count, remove First, remove Last

    EXPECT_CALL(mockXRef, removeIndirectObject(itemRef));



    removeChildHelper(0, &mockXRef, items);



    ASSERT_EQ(items.size(), 0);

}



TEST_F(TestFixture_1923, RemoveChildHelper_BoundaryCondition_LastItem_1923) {

    MockXRef mockXRef;

    std::vector<MockOutlineItem*> items;

    items.push_back(new NiceMock<MockOutlineItem>());



    Ref parentRef(1, 0);

    Ref itemRef(2, 0);



    EXPECT_CALL(*items[0], getRef()).WillOnce(Return(itemRef));



    Object parentDict;

    parentDict.dictSet("Count", Object(1));

    parentDict.dictSet("First", Object(itemRef));

    parentDict.dictSet("Last", Object(itemRef));



    Object itemDict;

    itemDict.dictSet("Parent", Object(parentRef));



    EXPECT_CALL(mockXRef, fetch(itemRef)).WillOnce(Return(itemDict));

    EXPECT_CALL(mockXRef, fetch(parentRef)).WillOnce(Return(parentDict));



    EXPECT_CALL(mockXRef, setModifiedObject(An<const Object*>(), parentRef))

        .Times(3); // Three times: decrement count, remove First, remove Last

    EXPECT_CALL(mockXRef, removeIndirectObject(itemRef));



    removeChildHelper(0, &mockXRef, items);



    ASSERT_EQ(items.size(), 0);

}



TEST_F(TestFixture_1923, RemoveChildHelper_ErrorCase_EmptyItems_1923) {

    MockXRef mockXRef;

    std::vector<MockOutlineItem*> items;



    removeChildHelper(0, &mockXRef, items);



    ASSERT_EQ(items.size(), 0);

}



TEST_F(TestFixture_1923, RemoveChildHelper_ErrorCase_OutOfBoundsPosition_1923) {

    MockXRef mockXRef;

    std::vector<MockOutlineItem*> items;

    items.push_back(new NiceMock<MockOutlineItem>());



    removeChildHelper(1, &mockXRef, items);



    ASSERT_EQ(items.size(), 1);

    delete items[0];

}
