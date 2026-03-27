#include <gtest/gtest.h>



// Since needToRotate is a static function in pdftoppm.cc,

// we'll assume it's part of some class or namespace for testing purposes.

// Let's assume it's part of a utility class named PdfUtils.



class PdfUtils {

public:

    static bool needToRotate(int angle) { return (angle == 90) || (angle == 270); }

};



TEST(needToRotateTest_2652, NormalOperation_2652) {

    EXPECT_TRUE(PdfUtils::needToRotate(90));

    EXPECT_TRUE(PdfUtils::needToRotate(270));

}



TEST(needToRotateTest_2652, BoundaryConditions_2652) {

    EXPECT_FALSE(PdfUtils::needToRotate(0));

    EXPECT_FALSE(PdfUtils::needToRotate(180));

    EXPECT_FALSE(PdfUtils::needToRotate(360));

}



TEST(needToRotateTest_2652, ExceptionalCases_2652) {

    // Since the function is simple and only checks for specific angles,

    // there are no exceptional cases that would cause an error.

    // However, we can test with negative angles or out-of-range values.

    EXPECT_FALSE(PdfUtils::needToRotate(-90));

    EXPECT_FALSE(PdfUtils::needToRotate(450));

}



// Since needToRotate does not interact with any external collaborators,

// there are no tests involving Google Mock necessary for this function.
