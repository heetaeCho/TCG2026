// Page_getPieceInfo_Test_718.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler/Page.h"

using ::testing::Return;
using ::testing::StrictMock;

// Forward declarations for minimal compilation in test context.
class PDFDoc;
class XRef;
class OutputDev;
class Annot;
class Links;
class FormPageWidgets;
class LinkAction;
class Gfx;
class Form;
class Annots;
class Stream;
class GooString;
class Ref;
class Object;
class PDFRectangle;

// Mock for Dict (used only as opaque pointer in interface)
class MockDict : public Dict {
};

// Mock PageAttrs to control getPieceInfo behavior
class MockPageAttrs : public PageAttrs {
public:
    MockPageAttrs() : PageAttrs(nullptr, nullptr) {}
    ~MockPageAttrs() override = default;

    MOCK_METHOD(Dict *, getPieceInfo, (), (override));
};

// Test fixture for TEST_ID 718
class PageTest_718 : public ::testing::Test {
protected:
    PDFDoc* dummyDoc = nullptr;
    int dummyNum = 1;
    Object dummyPageDict;
    Ref* dummyRefPtr = nullptr;

    std::unique_ptr<StrictMock<MockPageAttrs>> mockAttrs;
    Ref dummyRef;

    void SetUp() override {
        mockAttrs = std::make_unique<StrictMock<MockPageAttrs>>();
    }
};

// Normal operation: getPieceInfo forwards to PageAttrs and returns same pointer
TEST_F(PageTest_718, GetPieceInfo_ForwardsToAttrs_718) {
    auto expectedDict = new MockDict();

    EXPECT_CALL(*mockAttrs, getPieceInfo())
        .Times(1)
        .WillOnce(Return(expectedDict));

    Page page(dummyDoc,
              dummyNum,
              std::move(dummyPageDict),
              dummyRef,
              std::unique_ptr<PageAttrs>(mockAttrs.release()));

    Dict* result = page.getPieceInfo();

    EXPECT_EQ(result, expectedDict);

    delete expectedDict;
}

// Boundary condition: getPieceInfo returns nullptr if attrs returns nullptr
TEST_F(PageTest_718, GetPieceInfo_ReturnsNullWhenAttrsReturnsNull_718) {
    EXPECT_CALL(*mockAttrs, getPieceInfo())
        .Times(1)
        .WillOnce(Return(nullptr));

    Page page(dummyDoc,
              dummyNum,
              std::move(dummyPageDict),
              dummyRef,
              std::unique_ptr<PageAttrs>(mockAttrs.release()));

    Dict* result = page.getPieceInfo();

    EXPECT_EQ(result, nullptr);
}

// Exceptional/edge case: multiple calls consistently forward to attrs
TEST_F(PageTest_718, GetPieceInfo_MultipleCallsForwardEachTime_718) {
    auto firstDict = new MockDict();
    auto secondDict = new MockDict();

    EXPECT_CALL(*mockAttrs, getPieceInfo())
        .Times(2)
        .WillOnce(Return(firstDict))
        .WillOnce(Return(secondDict));

    Page page(dummyDoc,
              dummyNum,
              std::move(dummyPageDict),
              dummyRef,
              std::unique_ptr<PageAttrs>(mockAttrs.release()));

    Dict* result1 = page.getPieceInfo();
    Dict* result2 = page.getPieceInfo();

    EXPECT_EQ(result1, firstDict);
    EXPECT_EQ(result2, secondDict);

    delete firstDict;
    delete secondDict;
}