// ==========================================================================
// Munin Button.
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
#ifndef MUNIN_BUTTON_HPP_
#define MUNIN_BUTTON_HPP_

#include "munin/composite_component.hpp"
#include <boost/signal.hpp>

namespace terminalpp {
    class string;
}

namespace munin {

//* =========================================================================
/// \brief A class that models a push-button.
//* =========================================================================
class MUNIN_EXPORT button
  : public munin::composite_component
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    button(terminalpp::string const &caption);

    //* =====================================================================
    /// \brief Destructor
    //* =====================================================================
    virtual ~button();

    //* =====================================================================
    /// \fn on_click
    /// \brief Connect to this signal to receive click events due to the
    /// button either being clicked, or having focus and receiving an
    /// enter or space keypress.
    //* =====================================================================
    boost::signal<void ()> on_click;

protected :
    //* =====================================================================
    /// \brief Called by event().  Derived classes must override this
    /// function in order to handle events in a custom manner.
    //* =====================================================================
    virtual void do_event(boost::any const &event);

    struct impl;
    std::shared_ptr<impl> pimpl_;
};

//* =========================================================================
/// \brief Returns a newly created button
//* =========================================================================
MUNIN_EXPORT
std::shared_ptr<button> make_button(terminalpp::string const &caption);

}

#endif
