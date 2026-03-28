#include <gtest/gtest.h>

#include "Annot.h"

#include <memory>



// Mock classes or dependencies if needed (none required in this case)



class AnnotTest : public ::testing::Test {

protected:

    std::unique_ptr<Annot> annot;



    void SetUp() override {

        // Assuming a default constructor is available for testing purposes

        // If not, adjust accordingly based on actual constructors

        annot = std::make_unique<Annot>(nullptr, nullptr);

    }

};



// Test cases



TEST_F(AnnotTest_776, IsOk_ReturnsTrueByDefault_776) {

    EXPECT_TRUE(annot->isOk());

}



TEST_F(AnnotTest_776, GetRect_DefaultValuesAreZero_776) {

    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    annot->getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(0.0, x1);

    EXPECT_DOUBLE_EQ(0.0, y1);

    EXPECT_DOUBLE_EQ(0.0, x2);

    EXPECT_DOUBLE_EQ(0.0, y2);

}



TEST_F(AnnotTest_776, SetRectAndGetRect_CorrectValues_776) {

    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;

    annot->setRect(x1, y1, x2, y2);

    double rx1 = 0, ry1 = 0, rx2 = 0, ry2 = 0;

    annot->getRect(&rx1, &ry1, &rx2, &ry2);

    EXPECT_DOUBLE_EQ(x1, rx1);

    EXPECT_DOUBLE_EQ(y1, ry1);

    EXPECT_DOUBLE_EQ(x2, rx2);

    EXPECT_DOUBLE_EQ(y2, ry2);

}



TEST_F(AnnotTest_776, SetContentsAndGetContents_CorrectValues_776) {

    auto content = std::make_unique<GooString>("Sample Content");

    annot->setContents(std::move(content));

    const GooString* retrievedContent = annot->getContents();

    EXPECT_EQ("Sample Content", retrievedContent->c_str());

}



TEST_F(AnnotTest_776, SetModifiedAndGetModified_CorrectValues_776) {

    auto modifiedDate = std::make_unique<GooString>("2023-10-05T14:48:00Z");

    annot->setModified(std::move(modifiedDate));

    const GooString* retrievedModifiedDate = annot->getModified();

    EXPECT_EQ("2023-10-05T14:48:00Z", retrievedModifiedDate->c_str());

}



TEST_F(AnnotTest_776, SetFlagsAndGetFlags_CorrectValues_776) {

    unsigned int flags = 0x1F;

    annot->setFlags(flags);

    EXPECT_EQ(flags, annot->getFlags());

}



TEST_F(AnnotTest_776, InRect_Outside_ReturnsFalse_776) {

    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;

    annot->setRect(x1, y1, x2, y2);

    EXPECT_FALSE(annot->inRect(0.0, 0.0));

}



TEST_F(AnnotTest_776, InRect_Inside_ReturnsTrue_776) {

    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;

    annot->setRect(x1, y1, x2, y2);

    EXPECT_TRUE(annot->inRect(2.0, 3.0));

}



TEST_F(AnnotTest_776, InRect_Boundary_ReturnsTrue_776) {

    double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;

    annot->setRect(x1, y1, x2, y2);

    EXPECT_TRUE(annot->inRect(1.0, 2.0));

    EXPECT_TRUE(annot->inRect(3.0, 4.0));

}



TEST_F(AnnotTest_776, GetPageNum_DefaultValueIsZero_776) {

    EXPECT_EQ(0, annot->getPageNum());

}
