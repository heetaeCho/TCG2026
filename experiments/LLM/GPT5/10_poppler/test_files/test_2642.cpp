// ImageOutputDev_enableCCITT_test_2642.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <memory>
#include <string>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

class ImageOutputDevTest_2642 : public ::testing::Test {
protected:
  static std::unique_ptr<ImageOutputDev> MakeDev(const std::string &root,
                                                 bool pageNames,
                                                 bool listImages) {
    // ImageOutputDev takes a non-const char*. Provide a stable, mutable buffer.
    auto buf = std::make_unique<char[]>(root.size() + 1);
    std::memcpy(buf.get(), root.c_str(), root.size() + 1);

    // Many Poppler classes copy the input; if it does not, this buffer must outlive the dev.
    // To keep things safe without relying on implementation details, store the buffer
    // alongside the dev in the fixture when needed. For these tests, we keep it alive
    // by leaking ownership into a static store (per-test allocation).
    //
    // If ImageOutputDev copies the string, this is harmless; if it doesn't, this prevents UAF.
    static std::vector<std::unique_ptr<char[]>> s_buffers;
    s_buffers.push_back(std::move(buf));
    char *fileRootA = s_buffers.back().get();

    return std::make_unique<ImageOutputDev>(fileRootA, pageNames, listImages);
  }
};

} // namespace

TEST_F(ImageOutputDevTest_2642, EnableCCITT_CanBeCalledWithFalse_2642) {
  auto dev = MakeDev("imgoutdev_test_root", /*pageNames=*/false, /*listImages=*/false);

  // Observable behavior for this interface: method should be callable without crashing.
  dev->enableCCITT(false);

  // Additional observable check: other public methods remain callable.
  (void)dev->isOk();
}

TEST_F(ImageOutputDevTest_2642, EnableCCITT_CanBeCalledWithTrue_2642) {
  auto dev = MakeDev("imgoutdev_test_root", /*pageNames=*/true, /*listImages=*/false);

  dev->enableCCITT(true);

  (void)dev->isOk();
}

TEST_F(ImageOutputDevTest_2642, EnableCCITT_ToggleMultipleTimes_2642) {
  auto dev = MakeDev("imgoutdev_test_root", /*pageNames=*/false, /*listImages=*/true);

  // Boundary-ish usage: repeated toggles should be safe and not require ordering guarantees.
  dev->enableCCITT(false);
  dev->enableCCITT(true);
  dev->enableCCITT(false);
  dev->enableCCITT(true);

  (void)dev->isOk();
}

TEST_F(ImageOutputDevTest_2642, EnableCCITT_RepeatedSameValueIsSafe_2642) {
  auto dev = MakeDev("imgoutdev_test_root", /*pageNames=*/false, /*listImages=*/false);

  dev->enableCCITT(true);
  dev->enableCCITT(true);
  dev->enableCCITT(true);

  dev->enableCCITT(false);
  dev->enableCCITT(false);

  (void)dev->isOk();
}