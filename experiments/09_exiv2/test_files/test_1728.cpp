#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

    struct mimeType {

        public:

            int comp;

            const char * type;

            bool operator==(int c) const;

    };

}



using namespace Exiv2;



class MimeTypeTest_1728 : public ::testing::Test {

protected:

    MimeTypeTest_1728() {}

    virtual ~MimeTypeTest_1728() {}



    mimeType testMime;

};



TEST_F(MimeTypeTest_1728, OperatorEqualReturnsTrueForMatchingComp_1728) {

    testMime.comp = 42;

    EXPECT_TRUE(testMime == 42);

}



TEST_F(MimeTypeTest_1728, OperatorEqualReturnsFalseForNonMatchingComp_1728) {

    testMime.comp = 42;

    EXPECT_FALSE(testMime == 43);

}



TEST_F(MimeTypeTest_1728, OperatorEqualBoundaryConditionZero_1728) {

    testMime.comp = 0;

    EXPECT_TRUE(testMime == 0);

}



TEST_F(MimeTypeTest_1728, OperatorEqualBoundaryConditionNegative_1728) {

    testMime.comp = -1;

    EXPECT_TRUE(testMime == -1);

}
