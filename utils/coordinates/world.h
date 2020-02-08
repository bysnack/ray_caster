#pragma once

#include "tile.h"
#include "../vector.h"

namespace utils::coordinates {

    struct screen;
    struct world : public vector<float> {
        using vector<float>::vector;
        operator screen() const noexcept;
        operator tile() const noexcept;
    };
}