#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



namespace Exiv2 {



class RemoteIoTest : public ::testing::Test {

protected:

    RemoteIo remoteIo;

};



TEST_F(RemoteIoTest_600, OpenReturnsZeroForNormalOperation_600) {

    EXPECT_EQ(remoteIo.open(), 0);

}



TEST_F(RemoteIoTest_600, OpenResetsIODevicePosition_600) {

    // Assuming that open resets the position to 0

    remoteIo.open();

    EXPECT_EQ(remoteIo.tell(), 0);

}



TEST_F(RemoteIoTest_600, OpenThrowsErrorForZeroFileLength_600) {

    // Assuming that open throws an error if file length is zero

    EXPECT_THROW(remoteIo.open(), Error);

}



// Mocking is not required as there are no external collaborators to mock.



}  // namespace Exiv2
