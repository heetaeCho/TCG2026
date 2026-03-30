#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "StructTreeRoot.h"

#include "StructElement.h"



using namespace testing;



// Mock class for StructElement to control its behavior in tests.

class MockStructElement : public StructElement {

public:

    MOCK_CONST_METHOD0(isOk, bool());

};



TEST_F(StructTreeRootTest_1719, AppendChild_NormalOperation_1719) {

    MockStructElement element;

    EXPECT_CALL(element, isOk()).WillOnce(Return(true));



    StructTreeRoot treeRoot(nullptr, Dict());



    treeRoot.appendChild(&element);



    ASSERT_EQ(treeRoot.getNumChildren(), 1);

}



TEST_F(StructTreeRootTest_1719, AppendChild_ElementIsNull_1719) {

    StructTreeRoot treeRoot(nullptr, Dict());

    treeRoot.appendChild(nullptr);



    ASSERT_EQ(treeRoot.getNumChildren(), 0);

}



TEST_F(StructTreeRootTest_1719, AppendChild_ElementNotOk_1719) {

    MockStructElement element;

    EXPECT_CALL(element, isOk()).WillOnce(Return(false));



    StructTreeRoot treeRoot(nullptr, Dict());

    treeRoot.appendChild(&element);



    ASSERT_EQ(treeRoot.getNumChildren(), 0);

}



TEST_F(StructTreeRootTest_1719, GetChild_NormalOperation_1719) {

    MockStructElement element;

    EXPECT_CALL(element, isOk()).WillOnce(Return(true));



    StructTreeRoot treeRoot(nullptr, Dict());

    treeRoot.appendChild(&element);



    const auto* retrievedElement = treeRoot.getChild(0);

    ASSERT_EQ(retrievedElement, &element);

}



TEST_F(StructTreeRootTest_1719, GetChild_OutOfBounds_1719) {

    StructTreeRoot treeRoot(nullptr, Dict());



    const auto* retrievedElement = treeRoot.getChild(0);

    ASSERT_EQ(retrievedElement, nullptr);

}
