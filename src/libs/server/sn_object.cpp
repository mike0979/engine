#include "sn_object.h"
#include "global.h"

SnObject::SnObject() {
    _sn = Global::GetInstance()->GenerateSN();
}

uint64_t SnObject::GetSN() const {
    return _sn;
}

void SnObject::SetSN(uint64_t sn)
{
    _sn = sn;
}
