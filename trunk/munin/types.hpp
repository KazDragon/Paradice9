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

#include "munin/attribute.hpp"
#include "munin/glyph.hpp"
#include "odin/types.hpp"
#include <iosfwd>
#include <utility>

namespace munin {
    
//* =========================================================================
/// \brief The type of an element in an ANSI component.  Each element is a
/// character glyph and a set of attributes (such as boldness, colour, etc.).
//* =========================================================================
struct element_type
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs an element with a character of '\0' in the default locale
    /// and character set, with no special attributes.
    //* =====================================================================
    element_type();
    
    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs the element with the given parameters.
    //* =====================================================================
    explicit element_type(
        munin::glyph gly
      , munin::attribute attr = munin::attribute());
    
    munin::glyph     glyph_;
    munin::attribute attribute_;
};

//* =========================================================================
/// \brief Equality Operator
//* =========================================================================
bool operator==(element_type const &lhs, element_type const &rhs);

//* =========================================================================
/// \brief Output stream operator
//* =========================================================================
std::ostream &operator<<(std::ostream &out, element_type const &element);


    
//* =========================================================================
/// \brief A class that represents a position in space.
/// \par
/// A class that represents a position in space, where x is the co-ordinate 
/// along the horizontal axis and y being the co-ordinate along the vertical 
/// axis.
//* =========================================================================
struct point
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs a point, leaving the values uninitialised.
    //* =====================================================================
    point();
    
    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs a point from a passed in x co-ordinate and a passed in
    /// y co-ordinate.
    //* =====================================================================
    point(odin::s32 x_coordinate, odin::s32 y_coordinate);
    
    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    point &operator+=(point const &rhs);
    
    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    point &operator-=(point const &rhs);
    
    odin::s32 x;
    odin::s32 y;
};

bool operator==(point const &lhs, point const &rhs);
bool operator!=(point const &lhs, point const &rhs);
point operator+(point lhs, point const &rhs);
point operator-(point lhs, point const &rhs);
std::ostream& operator<<(std::ostream &out, point const &pt);

//* =========================================================================
/// \brief A class that represents a direction with distance in space
/// (a vector).
/// \par
/// A class that represents a direction in space, with width being the
/// extent in the horizontal axis, and height being the extent in the
/// vertical axis.
//* =========================================================================
struct extent
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs an extent, leaving the width and height uninitialised.
    //* =====================================================================
    extent();

    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs an extent with width and height being set to the passed-in
    /// arguments.
    //* =====================================================================
    extent(odin::s32 width, odin::s32 height);
    
    //* =====================================================================
    /// \brief Addition
    //* =====================================================================
    extent &operator+=(extent const &rhs);

    //* =====================================================================
    /// \brief Subtraction
    //* =====================================================================
    extent &operator-=(extent const &rhs);
    
    odin::s32 width;
    odin::s32 height;
};

bool operator==(extent const &lhs, extent const &rhs);
bool operator!=(extent const &lhs, extent const &rhs);
extent operator+(extent lhs, extent const &rhs);
extent operator-(extent lhs, extent const &rhs);
std::ostream& operator<<(std::ostream &out, extent const &ext);

//* =========================================================================
/// \brief A class that represents a rectangle in space.
//* =========================================================================
struct rectangle
{
    //* =====================================================================
    /// \brief Default Constructor
    /// \par
    /// Constructs the rectangle, leaving the origin and size uninitialised.
    //* =====================================================================
    rectangle();
    
    //* =====================================================================
    /// \brief Constructor
    /// \par
    /// Constructs the rectangle, using the specified origin and size.
    //* =====================================================================
    rectangle(point origin, extent size);
    
    point  origin;
    extent size;
};

bool operator==(rectangle const &lhs, rectangle const &rhs);
bool operator!=(rectangle const &lhs, rectangle const &rhs);
rectangle operator+(point const &pt, extent const &ext);
std::ostream& operator<<(std::ostream &out, rectangle const &rect);

// Finally, some common attribute names.

// Changing the glyph attribute will change some elements' glyphs.
static const std::string ATTRIBUTE_GLYPH = "Glyph";

// Changing the penattribute will change some elements' attributes.
static const std::string ATTRIBUTE_PEN = "Pen";

}

#endif
