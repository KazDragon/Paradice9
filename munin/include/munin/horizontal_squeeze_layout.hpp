// ==========================================================================
// Munin Horizontal Squeeze Layout.
//
// Copyright (C) 2011 Matthew Chaplain, All Rights Reserved.
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
#ifndef MUNIN_HORIZONTAL_SQUEEZE_LAYOUT_HPP_
#define MUNIN_HORIZONTAL_SQUEEZE_LAYOUT_HPP_

#include "munin/layout.hpp"

namespace munin {

//* =========================================================================
/// \brief A class that knows how to lay components out in a container in
/// horizontal strips.  Each component is given a roughly even amount of space.
///
///  +--------+
///  |        |
///  +--------+
///  |        |
///  +--------+
//* =========================================================================
class MUNIN_EXPORT horizontal_squeeze_layout
    : public layout
{
protected :
    //* =====================================================================
    /// \brief Called by get_preferred_size().  Derived classes must override
    /// this function in order to retrieve the preferred size of the layout
    /// in a custom manner.
    //* =====================================================================
    virtual terminalpp::extent do_get_preferred_size(
        std::vector<std::shared_ptr<component>> const &components
      , std::vector<boost::any>                 const &hints) const;

    //* =====================================================================
    /// \brief Called by operator().  Derived classes must override this
    /// function in order to lay a container's components out in a custom
    /// manner.
    //* =====================================================================
    virtual void do_layout(
        std::vector<std::shared_ptr<component>> const &components
      , std::vector<boost::any>                 const &hints
      , terminalpp::extent                             size);
};

//* =========================================================================
/// \brief Returns a newly created horizontal squeeze layout layout
//* =========================================================================
MUNIN_EXPORT
std::unique_ptr<layout> make_horizontal_squeeze_layout();

}

#endif
