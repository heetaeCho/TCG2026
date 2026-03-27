#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



namespace Exiv2 {

namespace Internal {



class TiffMnEntryTest_292 : public ::testing::Test {

protected:

    TiffMnEntry* entry;



    TiffMnEntryTest_292() {

        entry = new TiffMnEntry(1, ifdExif, ifdInteroperability);

    }



    ~TiffMnEntryTest_292() {

        delete entry;

    }

};



TEST_F(TiffMnEntryTest_292, DoCloneReturnsNullptr_292) {

    EXPECT_EQ(entry->doClone(), nullptr);

}



// Since the other methods are protected and there is no public interface to invoke them,

// we cannot directly test doAddPath, doAddChild, doAddNext, doAccept, doEncode, doWrite, doCount, and doSize.

// However, if these were accessible or had public wrappers, tests could be written for them as well.



}  // namespace Internal

}  // namespace Exiv2
