#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers are included for XMP_StringPtr, XMP_Throw, and other dependencies



namespace {

    void VerifyQualName(XMP_StringPtr qualName, XMP_StringPtr nameEnd);

}



class VerifyQualNameTest_1885 : public ::testing::Test {};



TEST_F(VerifyQualNameTest_1885, NormalOperation_ValidQualifiedName_1885) {

    const char* qualName = "prefix:name";

    EXPECT_NO_THROW(VerifyQualName(qualName, qualName + strlen(qualName)));

}



TEST_F(VerifyQualNameTest_1885, BoundaryCondition_EmptyQualifiedName_1885) {

    const char* qualName = "";

    EXPECT_THROW({

        try {

            VerifyQualName(qualName, qualName);

        } catch (const XMP_Error& e) {

            EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);

            throw;

        }

    }, XMP_Error);

}



TEST_F(VerifyQualNameTest_1885, BoundaryCondition_NoColonInQualifiedName_1885) {

    const char* qualName = "prefixname";

    EXPECT_THROW({

        try {

            VerifyQualName(qualName, qualName + strlen(qualName));

        } catch (const XMP_Error& e) {

            EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);

            throw;

        }

    }, XMP_Error);

}



TEST_F(VerifyQualNameTest_1885, BoundaryCondition_ColonAtStartOfQualifiedName_1885) {

    const char* qualName = ":name";

    EXPECT_THROW({

        try {

            VerifyQualName(qualName, qualName + strlen(qualName));

        } catch (const XMP_Error& e) {

            EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);

            throw;

        }

    }, XMP_Error);

}



TEST_F(VerifyQualNameTest_1885, BoundaryCondition_ColonAtEndOfQualifiedName_1885) {

    const char* qualName = "prefix:";

    EXPECT_THROW({

        try {

            VerifyQualName(qualName, qualName + strlen(qualName));

        } catch (const XMP_Error& e) {

            EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);

            throw;

        }

    }, XMP_Error);

}



TEST_F(VerifyQualNameTest_1885, ExceptionalCase_UnknownNamespacePrefix_1885) {

    const char* qualName = "unknown:name";

    EXPECT_THROW({

        try {

            VerifyQualName(qualName, qualName + strlen(qualName));

        } catch (const XMP_Error& e) {

            EXPECT_EQ(e.GetID(), kXMPErr_BadXPath);

            throw;

        }

    }, XMP_Error);

}
