// ==========================================================================
// Munin Basic Container.
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
#ifndef MUNIN_BASIC_CONTAINER_HPP_
#define MUNIN_BASIC_CONTAINER_HPP_

#include "munin/container.hpp"

namespace munin {

//* =========================================================================
/// \brief A default implementation of a container.
//* =========================================================================
class basic_container : public container
{
public :
    //* =====================================================================
    /// \brief Constructor
    //* =====================================================================
    basic_container();
    
    //* =====================================================================
    /// \brief Destructor
    //* =====================================================================
    virtual ~basic_container();
    
protected :    
    //* =====================================================================
    /// \brief Called by set_position().  Derived classes must override this
    /// function in order to set the position of the component in a custom
    /// manner.
    //* =====================================================================
    virtual void do_set_position(point const &position);
    
    //* =====================================================================
    /// \brief Called by get_position().  Derived classes must override this
    /// function in order to get the position of the component in a custom
    /// manner.
    //* =====================================================================
    virtual point do_get_position() const;
    
    //* =====================================================================
    /// \brief Called by set_size().  Derived classes must override this 
    /// function in order to set the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual void do_set_size(extent const &size);

    //* =====================================================================
    /// \brief Called by get_size().  Derived classes must override this
    /// function in order to get the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual extent do_get_size() const;
    
    //* =====================================================================
    /// \brief Called by set_parent().  Derived classes must override this
    /// function in order to set the parent of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual void do_set_parent(boost::shared_ptr<component> parent);
    
    //* =====================================================================
    /// \brief Called by get_parent().  Derived classes must override this
    /// function in order to get the parent of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual boost::shared_ptr<component> do_get_parent() const;

    //* =====================================================================
    /// \brief Called by get_preferred_size().  Derived classes must override
    /// this function in order to get the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual extent do_get_preferred_size() const;
    
    //* =====================================================================
    /// \brief Called by get_number_of_components().  Derived classes must
    /// override this function in order to retrieve the number of components
    /// in this basic_container in a custom manner.
    //* =====================================================================
    virtual odin::u32 do_get_number_of_components() const;
    
    //* =====================================================================
    /// \brief Called by add_component().  Derived classes must override
    /// this function in order to add a component to the basic_container in a
    /// custom manner.
    //* =====================================================================
    virtual void do_add_component(
        boost::shared_ptr<component> const &component
      , boost::any                   const &hint
      , odin::u32                           layer);
    
    //* =====================================================================
    /// \brief Called by remove_component().  Derived classes must override
    /// this function in order to add a component to the basic_container in a
    /// custom manner.
    //* =====================================================================
    virtual void do_remove_component(
        boost::shared_ptr<component> const &component);
    
    //* =====================================================================
    /// \brief Called by get_component().  Derived classes must override this
    /// function in order to retrieve a component in a custom manner.
    //* =====================================================================
    virtual boost::shared_ptr<component> do_get_component(
        odin::u32 index) const;
    
    //* =====================================================================
    /// \brief Called by get_component_hint().  Derived classes must
    /// override this function in order to retrieve a component hint in a
    /// custom manner.
    //* =====================================================================
    virtual boost::any do_get_component_hint(odin::u32 index) const;

    //* =====================================================================
    /// \brief Called by get_component_layer().  Derived classes must
    /// override this function in order to retrieve a component layer in a
    /// custom manner.
    //* =====================================================================
    virtual odin::u32 do_get_component_layer(odin::u32 index) const;
    
    //* =====================================================================
    /// \brief Called by set_layout.  Derived classes must override this
    /// function in order to set a layout in a custom manner.
    //* =====================================================================
    virtual void do_set_layout(
        boost::shared_ptr<munin::layout> const &lyt
      , odin::u32                               layer);
    
    //* =====================================================================
    /// \brief Called by get_layout.  Derived classes must override this
    /// function in order to get the basic_container's layout in a custom 
    /// manner.
    //* =====================================================================
    virtual boost::shared_ptr<munin::layout> do_get_layout(odin::u32 layer) const;

    //* =====================================================================
    /// \brief Called by get_layout_layers.  Derived classes must override 
    /// this function in order to get the container's layout in a custom 
    /// manner.
    //* =====================================================================
    virtual odin::runtime_array<odin::u32> do_get_layout_layers() const;
    
    //* =====================================================================
    /// \brief Called by has_focus().  Derived classes must override this
    /// function in order to return whether this component has focus in a
    /// custom manner.
    //* =====================================================================
    virtual bool do_has_focus() const;
    
    //* =====================================================================
    /// \brief Called by set_can_focus().  Derived classes must override this
    /// function in order to set whether this component can be focussed in
    /// a custom manner.
    //* =====================================================================
    virtual void do_set_can_focus(bool focus);

    //* =====================================================================
    /// \brief Called by can_focus().  Derived classes must override this
    /// function in order to return whether this component can be focused in
    /// a custom manner.
    //* =====================================================================
    virtual bool do_can_focus() const;
    
    //* =====================================================================
    /// \brief Called by set_focus().  Derived classes must override this
    /// function in order to set the focus to this component in a custom
    /// manner.
    //* =====================================================================
    virtual void do_set_focus();
    
    //* =====================================================================
    /// \brief Called by lose_focus().  Derived classes must override this
    /// function in order to lose the focus from this component in a
    /// custom manner.
    //* =====================================================================
    virtual void do_lose_focus();

    //* =====================================================================
    /// \brief Called by focus_next().  Derived classes must override this
    /// function in order to move the focus in a custom manner.
    //* =====================================================================
    virtual void do_focus_next();
    
    //* =====================================================================
    /// \brief Called by focus_previous().  Derived classes must override 
    /// this function in order to move the focus in a custom manner.
    //* =====================================================================
    virtual void do_focus_previous();
    
    //* =====================================================================
    /// \brief Called by get_focussed_component().  Derived classes must
    /// override this function in order to return the focussed component
    /// in a custom manner.
    //* =====================================================================
    virtual boost::shared_ptr<component> do_get_focussed_component();

    //* =====================================================================
    /// \brief Called by enable().  Derived classes must override this
    /// function in order to disable the component in a custom manner.
    //* =====================================================================
    virtual void do_enable();
    
    //* =====================================================================
    /// \brief Called by disable().  Derived classes must override this
    /// function in order to disable the component in a custom manner.
    //* =====================================================================
    virtual void do_disable();
    
    //* =====================================================================
    /// \brief Called by is_enabled().  Derived classes must override this
    /// function in order to return whether the component is disabled or not
    /// in a custom manner.
    //* =====================================================================
    virtual bool do_is_enabled() const;
    
    //* =====================================================================
    /// \brief Called by event().  Derived classes must override this 
    /// function in order to handle events in a custom manner.
    //* =====================================================================
    virtual void do_event(boost::any const &event);

    //* =====================================================================
    /// \brief Called by get_cursor_state().  Derived classes must override
    /// this function in order to return the cursor state in a custom manner.
    //* =====================================================================
    virtual bool do_get_cursor_state() const;

    //* =====================================================================
    /// \brief Called by get_cursor_position().  Derived classes must
    /// override this function in order to return the cursor position in
    /// a custom manner.
    //* =====================================================================
    virtual point do_get_cursor_position() const;

    //* =====================================================================
    /// \brief Called by set_cursor_position().  Derived classes must
    /// override this function in order to set the cursor position in
    /// a custom manner.
    //* =====================================================================
    virtual void do_set_cursor_position(point const &position);

    //* =====================================================================
    /// \brief Called by set_attribute().  Derived classes must override this
    /// function in order to set an attribute in a custom manner.
    //* =====================================================================
    virtual void do_set_attribute(
        std::string const &name, boost::any const &attr);
    
    //* =====================================================================
    /// \brief Called by layout().  Derived classes must override this 
    /// function in order to lay the component out.  If the component 
    /// contains subcomponents, these must also be laid out.
    //* =====================================================================
    virtual void do_layout();

private :
    struct impl;
    boost::shared_ptr<impl> pimpl_;
};
    
}

#endif
