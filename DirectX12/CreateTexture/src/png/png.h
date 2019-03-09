#pragma once
#include "../common/common.h"
#include <libpng/png.h>
#pragma comment(lib,"libpng16.lib")
#pragma comment(lib,"zlib.lib")

static constexpr std::size_t PNG_SIG_SIZE = 8;

bool PngApp(const char*);