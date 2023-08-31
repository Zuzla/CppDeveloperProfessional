#define BOOST_TEST_MODULE test_version

#include "lib.h"

#include <gtest/gtest.h>

TEST(VersionTestMoreZero, VersionTest) {
    EXPECT_TRUE(version() > 0);
}
