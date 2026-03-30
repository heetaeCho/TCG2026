#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.hpp"

#include "exif.hpp" // Assuming Exiv2::ExifData and related types are defined here



namespace {

    using namespace Exiv2;

    using namespace Exiv2::Internal;



    struct TagDetails {

        int id_;

        const char* label_;

    };



    constexpr TagDetails tagArray[] = {

        { 1, "Tag1" },

        { 2, "Tag2" }

    };



    TEST_F(WriteBatchTest_181, PutExistingValue_ReturnsLabel_181) {

        Value val;

        val.setValue(1);

        std::ostringstream os;

        printTagNoError<2>(os, val, nullptr);

        EXPECT_EQ(os.str(), "Tag1");

    }



    TEST_F(WriteBatchTest_181, PutNonExistingValue_ReturnsValue_181) {

        Value val;

        val.setValue(3);

        std::ostringstream os;

        printTagNoError<2>(os, val, nullptr);

        EXPECT_EQ(os.str(), "3");

    }



    TEST_F(WriteBatchTest_181, PutExistingTag_ReturnsLabel_181) {

        int tag = 2;

        std::ostringstream os;

        printTagNoError<2>(os, tag, nullptr);

        EXPECT_EQ(os.str(), "Tag2");

    }



    TEST_F(WriteBatchTest_181, PutNonExistingTag_ReturnsValue_181) {

        int tag = 4;

        std::ostringstream os;

        printTagNoError<2>(os, tag, nullptr);

        EXPECT_EQ(os.str(), "4");

    }



    TEST_F(WriteBatchTest_181, BoundaryCondition_ZeroLengthArray_ShouldNotCompile_181) {

        // This test is commented out because it will not compile due to static_assert.

        // Value val;

        // val.setValue(1);

        // std::ostringstream os;

        // printTagNoError<0>(os, val, nullptr); // Should not compile

    }



    TEST_F(WriteBatchTest_181, BoundaryCondition_EmptyValue_ReturnsEmptyString_181) {

        Value val;

        std::ostringstream os;

        printTagNoError<2>(os, val, nullptr);

        EXPECT_EQ(os.str(), "");

    }

}
