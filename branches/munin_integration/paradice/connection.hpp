// ==========================================================================
// Paradice Connection
//
// Copyright (C) 2009 Matthew Chaplain, All Rights Reserved.
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
#ifndef PARADICE_CONNECTION_HPP_
#define PARADICE_CONNECTION_HPP_

#include "odin/types.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <string>
#include <utility>

namespace paradice {

class socket;

//* =========================================================================
/// \brief An connection to a socket that abstracts away details about the
/// protocols used.
//* =========================================================================
class connection
{
public :
    //* =====================================================================
    /// \brief Create a connection object that uses the passed socket as
    /// a communications point, and calls the passed function whenever data
    /// is received.
    //* =====================================================================
    connection(
        boost::shared_ptr<socket>           connection_socket
      , boost::function<void (std::string)> data_callback);
    
    //* =====================================================================
    /// \brief Destructor.
    //* =====================================================================
    ~connection();
    
    //* =====================================================================
    /// \brief Write some text to the connection.
    //* =====================================================================
    void write(std::string const &text);

    //* =====================================================================
    /// \brief Returns the window size of the client that is connected.
    //* =====================================================================
    std::pair<odin::u16, odin::u16> get_window_size() const;

    //* =====================================================================
    /// \brief Sets a callback function to be called if the window size
    /// of the client changes.
    //* =====================================================================
    void on_window_size_changed(boost::function<
        void (odin::u16 width, odin::u16 height)> const &callback);
    
    //* =====================================================================
    /// \brief Sends a pulse of no data.  Useful for keeping a connection
    /// from dropping due to inactivity.
    //* =====================================================================
    void keepalive();
    
    //* =====================================================================
    /// \brief Disconnects the socket.
    //* =====================================================================
    void disconnect();

    //* =====================================================================
    /// \brief Reconnects a new socket to this connection.
    //* =====================================================================
    void reconnect(boost::shared_ptr<socket> connection_socket);
    
private :
    struct impl;
    boost::shared_ptr<impl> pimpl_;
};

}

#endif
