// ==========================================================================
// Munin Named Frame.
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
#ifndef MUNIN_NAMED_FRAME_HPP_
#define MUNIN_NAMED_FRAME_HPP_

#include "munin/basic_frame.hpp"
#include <terminalpp/string.hpp>
#include <string>
#include <vector>

namespace munin {

//* =========================================================================
/// \brief An object that represents a frame that has a title on its
/// northern edge.
//* =========================================================================
class MUNIN_EXPORT named_frame : public basic_frame
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    named_frame();

    //* =====================================================================
    /// \brief Destructor
    //* =====================================================================
    virtual ~named_frame();

    //* =====================================================================
    /// \brief Sets the name displayed on the top border of the frame.
    //* =====================================================================
    void set_name(terminalpp::string const &name);

    //* =====================================================================
    /// \brief Sets whether the frame is 'closeable' or not.  That is,
    /// whether it has a close icon that can be clicked.
    //* =====================================================================
    void set_closeable(bool closeable);

    //* =====================================================================
    /// \fn on_close
    /// \brief A signal that is raised whenever the close icon is clicked.
    //* =====================================================================
    boost::signal<
        void ()
    > on_close;

protected :
    //* =====================================================================
    /// \brief Called by event().  Derived classes must override this
    /// function in order to handle events in a custom manner.
    //* =====================================================================
    virtual void do_event(boost::any const &event);

private :
    struct impl;
    std::shared_ptr<impl> pimpl_;
};

//* =========================================================================
/// \brief Returns a newly created named frame
//* =========================================================================
MUNIN_EXPORT
std::shared_ptr<named_frame> make_named_frame(terminalpp::string const &name);

}

#endif
