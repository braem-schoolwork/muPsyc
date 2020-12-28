#pragma once
#include <random>

#define MAKE_INT_DIST(name, lower, upper) const std::uniform_int_distribution<int> name(lower, upper)
#define MAKE_REAL_DIST(name, lower, upper) const std::uniform_real_distribution<double> name(lower, upper)

#define GEN_RAND_INT(lower, upper, out) \
{ \
    std::uniform_int_distribution<int> dist(lower, upper); \
    (out) = dist(g_MT); \
} \

static std::random_device g_RD;
static std::mt19937 g_MT(g_RD());
static MAKE_INT_DIST(g_BoolDist, 0, 1);
static MAKE_REAL_DIST(g_DblDist, 0.0, 1.0);
