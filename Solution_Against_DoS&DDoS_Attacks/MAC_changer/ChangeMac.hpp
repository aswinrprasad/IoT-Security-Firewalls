#ifndef CHANGE_MAC_HPP
#define CHANGE_MAC_HPP

#include <cstdint>

void
makeRandomMac(uint8_t mac[6]);

bool
changeMac(const uint8_t mac[6]);

#endif // CHANGE_MAC_HPP
