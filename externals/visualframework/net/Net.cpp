/*==============================================================================

	Net.cpp

	visualframework: a simple 2d graphics framework
  
	Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "Net.h"

namespace visual {

bool Net::_bSetup = false;
std::string Net::_error = "";

bool Net::init()
{
    if(_bSetup)
        return true;    // already setup

    if(SDLNet_Init() < 0)
    {
        LOG_ERROR << "Net: Could not init SDL_net: " << SDLNet_GetError() << std::endl;
        return false;
    }

    _bSetup = true;

    return false;
}

void Net::quit()
{
    if(!_bSetup)
        return;     // not setup

    SDLNet_Quit();
}
/*
bool Net::allocatePacket(UDPpacket* packet, unsigned int length)
{
    // clear existing packet
    freePacket(packet);

    // allocate packet memory
    packet = SDLNet_AllocPacket(length);
    if(packet == NULL)
    {
        LOG_ERROR << "Net: Could not allocate packet:" << SDLNet_GetError() << std::endl;
        return false;
    }

    return true;
}

void Net::freePacket(UDPpacket* packet)
{
    if(packet != NULL)
    {
        SDLNet_FreePacket(packet);
    }
}
*/
std::string Net::getError()
{
    _error = SDLNet_GetError();
    return _error;
}

} // namespace
