#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/status.h"



using namespace leveldb;



namespace {

    TEST(SaveErrorTest_218, NoError_ReturnsFalse_218) {

        char* errptr = nullptr;

        Status s = Status::OK();

        EXPECT_FALSE(SaveError(&errptr, s));

        EXPECT_EQ(errptr, nullptr);

    }



    TEST(SaveErrorTest_218, ExistingError_ReplacesWithError_218) {

        char* errptr = strdup("Existing error message");

        Status s = Status::NotFound("New error message");

        EXPECT_TRUE(SaveError(&errptr, s));

        EXPECT_STREQ(errptr, "Not found: New error message");

        std::free(errptr);

    }



    TEST(SaveErrorTest_218, NullPtrErrptr_AssertionFailure_218) {

        Status s = Status::NotFound("Some error");

#ifdef NDEBUG

        EXPECT_DEATH(SaveError(nullptr, s), "");

#else

        EXPECT_THROW({ SaveError(nullptr, s); }, std::exception);

#endif

    }



    TEST(SaveErrorTest_218, DifferentErrors_SetsCorrectMessages_218) {

        char* errptr = nullptr;



        Status notFoundStatus = Status::NotFound("Not found message");

        EXPECT_TRUE(SaveError(&errptr, notFoundStatus));

        EXPECT_STREQ(errptr, "Not found: Not found message");

        std::free(errptr);



        Status corruptionStatus = Status::Corruption("Corruption message");

        EXPECT_TRUE(SaveError(&errptr, corruptionStatus));

        EXPECT_STREQ(errptr, "Corruption: Corruption message");

        std::free(errptr);



        Status ioErrorStatus = Status::IOError("IO error message");

        EXPECT_TRUE(SaveError(&errptr, ioErrorStatus));

        EXPECT_STREQ(errptr, "IO error: IO error message");

        std::free(errptr);

    }

}
