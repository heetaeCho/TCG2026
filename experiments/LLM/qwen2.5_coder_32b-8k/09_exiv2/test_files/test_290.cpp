#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffDirectoryTest_290 : public ::testing::Test {

protected:

    TiffDirectory* tiffDir;



    void SetUp() override {

        tiffDir = new TiffDirectory(1, IfdId::root, true);

    }



    void TearDown() override {

        delete tiffDir;

    }

};



TEST_F(TiffDirectoryTest_290, CloneCreatesCopy_290) {

    TiffDirectory* clone = tiffDir->doClone();

    EXPECT_NE(clone, tiffDir);

    EXPECT_EQ(clone->hasNext(), tiffDir->hasNext());

    delete clone;

}



TEST_F(TiffDirectoryTest_290, HasNextReturnsTrue_290) {

    EXPECT_TRUE(tiffDir->hasNext());

}



TEST_F(TiffDirectoryTest_290, HasNextReturnsFalse_290) {

    TiffDirectory dir(1, IfdId::root, false);

    EXPECT_FALSE(dir.hasNext());

}



// Since the other methods are protected and not directly testable without a mock

// of the base class or internal state access, we limit tests to what is publicly accessible.

```


