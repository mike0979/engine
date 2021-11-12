#pragma once

#include "common.h"

class SnObject {
public:
    SnObject();
    uint64_t GetSN() const;
    void SetSN(uint64_t sn);

protected:
    uint64_t _sn;
};