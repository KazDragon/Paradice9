// ==========================================================================
// Paradice9 Application
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
#ifndef PARADICE9_HPP_
#define PARADICE9_HPP_

#include <boost/asio/io_service.hpp>
#include <memory>

//* =========================================================================
/// \brief A class that implements the main engine for the Paradice9 server.
/// \param io_service - The engine will be run within using the dispatch
///        mechanisms of this object.
/// \brief work - A "work" object.  While this is not reset, the threads'
///        run() methods will not terminate.  Resetting this work object
///        is part of the shutdown protocol.
/// \brief port - The server will be set up on this port number.
//* =========================================================================
class paradice9
{
public :
    paradice9(
        boost::asio::io_service                        &io_service
      , std::shared_ptr<boost::asio::io_service::work>  work
      , unsigned int                                    port);
    
private :
    struct impl;
    std::shared_ptr<impl> pimpl_;
};

#endif

