#include <gtest/gtest.h>

#include "./TestProjects/poppler/qt5/src/poppler-document.cc"



using namespace Poppler;



TEST_F(PopplerDocumentTest_1360, IsOverprintPreviewAvailable_ReturnsTrue_1360) {

    EXPECT_TRUE(isOverprintPreviewAvailable());

}
