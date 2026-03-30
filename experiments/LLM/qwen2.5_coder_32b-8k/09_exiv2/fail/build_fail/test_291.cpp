#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include <memory>



using namespace Exiv2::Internal;



class TiffSubIfdTest : public ::testing::Test {

protected:

    uint16_t tag = 0x0111; // Example Tag value

    IfdId group = IfdId::ifdExif;

    IfdId newGroup = IfdId::ifdGps;



    std::unique_ptr<TiffSubIfd> tiffSubIfdPtr;



    void SetUp() override {

        tiffSubIfdPtr.reset(new TiffSubIfd(tag, group, newGroup));

    }

};



TEST_F(TiffSubIfdTest_291, CloneCreatesNewInstance_291) {

    auto cloned = tiffSubIfdPtr->doClone();

    EXPECT_NE(tiffSubIfdPtr.get(), cloned);

    delete cloned;

}



// No other public methods are visible to test directly in the given interface.

// The protected methods cannot be tested as they are not accessible.



TEST_F(TiffSubIfdTest_291, DestructorDoesNotThrow_291) {

    EXPECT_NO_THROW(tiffSubIfdPtr.reset());

}
