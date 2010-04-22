// ==========================================================================
// Munin Types.
//
// Copyright (C) 2010 Matthew Chaplain, All Rights Reserved.
//
// Permission to reproduce, distribute, perform, display, and to prepare
// derivitive works from this file under the following conditions:
//
// 1. Any copy, reproduction or derivitive work of any part of this file 
//    contains this copyright notice and licence in its entirety.
//
// 2. The rights granted to you under this license automatically terminate
//    should you attempt to assert any patent claims against the licensor 
//    or contributors, which in any way restrict the ability of any party 
//    from using this software or portions thereof in any form under the
//    terms of this license.
//
// Disclaimer: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
//             KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
//             WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
//             PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
//             OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
//             OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
//             OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//             SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
// ==========================================================================
#ifndef MUNIN_TYPES_HPP_
#define MUNIN_TYPES_HPP_

#include "odin/types.hpp"
#include <iosfwd>

namespace munin {
    
struct point
{
    odin::u32 x;
    odin::u32 y;
};

bool operator==(point const &lhs, point const &rhs);
std::ostream& operator<<(std::ostream &out, point const &pt);

struct extent
{
    odin::u32 width;
    odin::u32 height;
};

bool operator==(extent const &lhs, extent const &rhs);
std::ostream& operator<<(std::ostream &out, extent const &ext);

struct rectangle
{
    point  origin;
    extent size;
};

bool operator==(rectangle const &lhs, rectangle const &rhs);
std::ostream& operator<<(std::ostream &out, rectangle const &rect);

}

#endif
