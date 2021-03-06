// ==========================================================================
// Paradice Context Implementation
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
#ifndef PARADICE9_CONTEXT_IMPL_HPP_
#define PARADICE9_CONTEXT_IMPL_HPP_

#include "paradice/context.hpp"
#include "odin/net/server.hpp"
#include <boost/asio/io_service.hpp>

//* =========================================================================
/// \brief Describes the context in which a Paradice server runs.
//* =========================================================================
class context_impl : public paradice::context
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    context_impl(
        boost::asio::io_service                       &io_service
      , std::shared_ptr<odin::net::server>             server
      , std::shared_ptr<boost::asio::io_service::work> work);
    
    //* =====================================================================
    /// \brief Denstructor
    //* =====================================================================
    virtual ~context_impl();
    
    //* =====================================================================
    /// \brief Retrieves a list of clients currently connected to Paradice.
    //* =====================================================================
    virtual std::vector< 
        std::shared_ptr<paradice::client> 
    > get_clients();

    //* =====================================================================
    /// \brief Adds a client to the list of clients currently connected
    /// to Paradice.
    //* =====================================================================
    virtual void add_client(std::shared_ptr<paradice::client> const &cli);

    //* =====================================================================
    /// \brief Removes a client from the list of clients currently
    /// connected to Paradice.
    //* =====================================================================
    virtual void remove_client(std::shared_ptr<paradice::client> const &cli);
    
    //* =====================================================================
    /// \brief For all clients, updates their lists of names.
    //* =====================================================================
    virtual void update_names();

    //* =====================================================================
    /// \brief Returns how a character appears to others, including prefix
    /// and suffix.
    //* =====================================================================
    virtual std::string get_moniker(
        std::shared_ptr<paradice::character> const &ch);

    //* =====================================================================
    /// \brief Loads an account from a specific account name and returns it.
    /// Returns an empty shared_ptr<> if there was no account with that name
    /// found.
    //* =====================================================================
    virtual std::shared_ptr<paradice::account> load_account(
        std::string const &name);

    //* =====================================================================
    /// \brief Saves an account.
    //* =====================================================================
    virtual void save_account(std::shared_ptr<paradice::account> const &acct);

    //* =====================================================================
    /// \brief Loads a character that is identified by the passed name and
    /// returns it.  Returns an empty shared_ptr<> if there was no character
    /// with that name found.
    //* =====================================================================
    virtual std::shared_ptr<paradice::character> load_character(
        std::string const &name);

    //* =====================================================================
    /// \brief Saves a character.
    //* =====================================================================
    virtual void save_character(std::shared_ptr<paradice::character> const &ch);
    
    //* =====================================================================
    /// \brief Enacts a server shutdown.
    //* =====================================================================
    virtual void shutdown();
    
    //* =====================================================================
    /// \brief Gets the currently active encounter
    //* =====================================================================
    virtual std::shared_ptr<paradice::active_encounter> get_active_encounter();

    //* =====================================================================
    /// \brief Sets the currently active encounter
    //* =====================================================================
    virtual void set_active_encounter(
        std::shared_ptr<paradice::active_encounter> const &enc);

    //* =====================================================================
    /// \brief Gets the visibility of the encounter.
    //* =====================================================================
    virtual bool is_active_encounter_visible() const;

    //* =====================================================================
    /// \brief Sets the visibility of the encounter for all players.
    //* =====================================================================
    virtual void set_active_encounter_visible(bool visibility);

    //* =====================================================================
    /// \brief Informs the context that changes have been made to the
    /// active encounter and that any related views should be updated.
    //* =====================================================================
    virtual void update_active_encounter();

private :
    struct impl;
    std::shared_ptr<impl> pimpl_;
};

#endif
