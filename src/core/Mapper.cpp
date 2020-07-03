#include "Mapper.h"

Mapper::Mapper(uint8_t numPRGBanks, uint8_t numCHRBanks)
{
    this->numPRGBanks = numPRGBanks;
    this->numCHRBanks = numCHRBanks;
}

Mapper::~Mapper()
{

}