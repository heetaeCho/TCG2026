#include <glib.h>
#include <gtest/gtest.h>

// Forward declaration of the type and function
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

extern "C" {
PopplerCertificateInfo *poppler_certificate_info_new(void);
}

class PopplerCertificateInfoTest_2394 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any allocated resources
        for (auto ptr : allocated_ptrs) {
            g_free(ptr);
        }
        allocated_ptrs.clear();
    }

    std::vector<PopplerCertificateInfo *> allocated_ptrs;
};

TEST_F(PopplerCertificateInfoTest_2394, NewReturnsNonNull_2394)
{
    PopplerCertificateInfo *info = poppler_certificate_info_new();
    ASSERT_NE(info, nullptr);
    allocated_ptrs.push_back(info);
}

TEST_F(PopplerCertificateInfoTest_2394, NewReturnsZeroInitializedMemory_2394)
{
    PopplerCertificateInfo *info = poppler_certificate_info_new();
    ASSERT_NE(info, nullptr);

    // Since g_malloc0 is used, the memory should be zero-initialized
    // We can verify the first few bytes are zero
    unsigned char *raw = reinterpret_cast<unsigned char *>(info);
    // Check that at least the first sizeof(void*) bytes are zero
    // (the struct must have at least some content)
    for (size_t i = 0; i < sizeof(void *); i++) {
        EXPECT_EQ(raw[i], 0) << "Byte at offset " << i << " is not zero";
    }
    allocated_ptrs.push_back(info);
}

TEST_F(PopplerCertificateInfoTest_2394, MultipleAllocationsReturnDistinctPointers_2394)
{
    PopplerCertificateInfo *info1 = poppler_certificate_info_new();
    PopplerCertificateInfo *info2 = poppler_certificate_info_new();
    ASSERT_NE(info1, nullptr);
    ASSERT_NE(info2, nullptr);
    EXPECT_NE(info1, info2);
    allocated_ptrs.push_back(info1);
    allocated_ptrs.push_back(info2);
}

TEST_F(PopplerCertificateInfoTest_2394, CanAllocateMultipleTimes_2394)
{
    const int count = 100;
    std::vector<PopplerCertificateInfo *> infos;
    for (int i = 0; i < count; i++) {
        PopplerCertificateInfo *info = poppler_certificate_info_new();
        ASSERT_NE(info, nullptr) << "Allocation failed at iteration " << i;
        infos.push_back(info);
    }

    // Verify all pointers are unique
    std::set<PopplerCertificateInfo *> unique_ptrs(infos.begin(), infos.end());
    EXPECT_EQ(unique_ptrs.size(), static_cast<size_t>(count));

    for (auto ptr : infos) {
        allocated_ptrs.push_back(ptr);
    }
}

TEST_F(PopplerCertificateInfoTest_2394, AllocatedMemoryCanBeFreedWithGFree_2394)
{
    // This test verifies that the returned pointer can be freed with g_free
    // (since it was allocated with g_malloc0)
    PopplerCertificateInfo *info = poppler_certificate_info_new();
    ASSERT_NE(info, nullptr);
    // Directly free it - should not crash
    g_free(info);
    // Don't add to allocated_ptrs since we already freed it
}
