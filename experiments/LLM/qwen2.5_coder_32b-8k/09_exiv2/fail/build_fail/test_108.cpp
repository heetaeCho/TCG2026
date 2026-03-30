#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/rw2image_int.hpp"



using namespace Exiv2::Internal;



class Rw2HeaderTest_108 : public ::testing::Test {

protected:

    Rw2Header header;

};



TEST_F(Rw2HeaderTest_108, WriteReturnsNonEmptyDataBuf_108) {

    DataBuf result = header.write();

    EXPECT_FALSE(result.empty());

}



TEST_F(Rw2HeaderTest_108, WriteReturnsConsistentDataBuf_108) {

    DataBuf firstResult = header.write();

    DataBuf secondResult = header.write();

    EXPECT_EQ(firstResult, secondResult);

}



// Boundary conditions and error cases are not applicable here as the write() method does not take any parameters

// and its observable behavior is limited to returning a DataBuf.

```


