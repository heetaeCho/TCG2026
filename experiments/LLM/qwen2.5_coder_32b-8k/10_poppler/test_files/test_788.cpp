#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



class AnnotTest : public ::testing::Test {

protected:

    PDFDoc* doc = nullptr;  // Assuming PDFDoc is a valid class in your context

    std::unique_ptr<PDFRectangle> rect = std::make_unique<PDFRectangle>();

    Annot annot{doc, rect.get()};

};



TEST_F(AnnotTest_788, GetFlags_ReturnsInitialValue_788) {

    unsigned int flags = annot.getFlags();

    EXPECT_EQ(flags, 0u);  // Assuming initial value of flags is 0

}



TEST_F(AnnotTest_788, SetFlagsAndGetFlags_UpdatesCorrectly_788) {

    unsigned int newFlags = 42;

    annot.setFlags(newFlags);

    unsigned int flags = annot.getFlags();

    EXPECT_EQ(flags, newFlags);

}



TEST_F(AnnotTest_788, GetRect_ReturnsInitialValue_788) {

    double x1, y1, x2, y2;

    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 0.0);  // Assuming initial rectangle values are (0, 0, 0, 0)

    EXPECT_DOUBLE_EQ(y1, 0.0);

    EXPECT_DOUBLE_EQ(x2, 0.0);

    EXPECT_DOUBLE_EQ(y2, 0.0);

}



TEST_F(AnnotTest_788, SetRectAndGetRect_UpdatesCorrectly_788) {

    double newX1 = 1.0, newY1 = 2.0, newX2 = 3.0, newY2 = 4.0;

    annot.setRect(newX1, newY1, newX2, newY2);

    double x1, y1, x2, y2;

    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, newX1);

    EXPECT_DOUBLE_EQ(y1, newY1);

    EXPECT_DOUBLE_EQ(x2, newX2);

    EXPECT_DOUBLE_EQ(y2, newY2);

}



TEST_F(AnnotTest_788, SetRectFromObjectAndGetRect_UpdatesCorrectly_788) {

    PDFRectangle newRect{1.0, 2.0, 3.0, 4.0};

    annot.setRect(newRect);

    double x1, y1, x2, y2;

    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, newRect.x1);

    EXPECT_DOUBLE_EQ(y1, newRect.y1);

    EXPECT_DOUBLE_EQ(x2, newRect.x2);

    EXPECT_DOUBLE_EQ(y2, newRect.y2);

}



TEST_F(AnnotTest_788, GetContents_ReturnsNullptrInitially_788) {

    const GooString* contents = annot.getContents();

    EXPECT_EQ(contents, nullptr);  // Assuming initial contents is nullptr

}



TEST_F(AnnotTest_788, SetContentsAndGetContents_UpdatesCorrectly_788) {

    auto newContents = std::make_unique<GooString>("New Content");

    const GooString* expectedContents = newContents.get();

    annot.setContents(std::move(newContents));

    const GooString* contents = annot.getContents();

    EXPECT_EQ(contents, expectedContents);

    EXPECT_STREQ(contents->getCString(), "New Content");

}



TEST_F(AnnotTest_788, SetModifiedAndGetModified_UpdatesCorrectly_788) {

    auto newModified = std::make_unique<GooString>("2023-10-05T14:48:00Z");

    const GooString* expectedModified = newModified.get();

    annot.setModified(std::move(newModified));

    const GooString* modified = annot.getModified();

    EXPECT_EQ(modified, expectedModified);

    EXPECT_STREQ(modified->getCString(), "2023-10-05T14:48:00Z");

}



TEST_F(AnnotTest_788, GetPageNum_ReturnsInitialValue_788) {

    int pageNum = annot.getPageNum();

    EXPECT_EQ(pageNum, 0);  // Assuming initial page number is 0

}



TEST_F(AnnotTest_788, GetName_ReturnsNullptrInitially_788) {

    const GooString* name = annot.getName();

    EXPECT_EQ(name, nullptr);  // Assuming initial name is nullptr

}



TEST_F(AnnotTest_788, GetAppearState_ReturnsNullptrInitially_788) {

    const GooString* appearState = annot.getAppearState();

    EXPECT_EQ(appearState, nullptr);  // Assuming initial appearance state is nullptr

}



TEST_F(AnnotTest_788, GetBorder_ReturnsNullptrInitially_788) {

    AnnotBorder* border = annot.getBorder();

    EXPECT_EQ(border, nullptr);  // Assuming initial border is nullptr

}



TEST_F(AnnotTest_788, GetColor_ReturnsNullptrInitially_788) {

    AnnotColor* color = annot.getColor();

    EXPECT_EQ(color, nullptr);  // Assuming initial color is nullptr

}



TEST_F(AnnotTest_788, IsOk_ReturnsTrueInitially_788) {

    bool ok = annot.isOk();

    EXPECT_TRUE(ok);  // Assuming the object is initially valid

}
