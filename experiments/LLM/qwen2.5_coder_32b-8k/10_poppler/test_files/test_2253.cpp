#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming PopplerPSFile and its class are declared somewhere in the header files.

class PopplerPSFile;

struct _PopplerPSFileClass;



namespace {



TEST(PopplerPSFileTest_2253, InitializationDoesNotCrash_2253) {

    // This test checks that the initialization of PopplerPSFile does not cause a crash.

    GType type = g_type_register_static(G_TYPE_OBJECT, "PopplerPSFile", nullptr, (GTypeFlags)0);

    g_assert_true(type != 0);

}



TEST(PopplerPSFileTest_2253, ClassInitSetsFinalizeFunction_2253) {

    // This test checks that the class initialization sets the finalize function correctly.

    PopplerPSFileClass *klass = (PopplerPSFileClass *)g_type_class_ref(g_type_register_static(G_TYPE_OBJECT, "PopplerPSFile", nullptr, (GTypeFlags)0));

    ASSERT_NE(klass, nullptr);

    EXPECT_EQ(klass->finalize, poppler_ps_file_finalize);

    g_type_class_unref(klass);

}



}  // namespace
