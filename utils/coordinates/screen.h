#pragma once

#include "../vector.h"
#include "tile.h"

namespace utils::coordinates {

    struct world;
    struct screen : public vector<float> {
        using vector<float>::vector;
        operator world() const noexcept;
        operator tile() const noexcept;
    };
}