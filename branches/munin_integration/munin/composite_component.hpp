// ==========================================================================
// Munin Composite Container.
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
#ifndef MUNIN_COMPOSITE_CONTAINER_HPP_
#define MUNIN_COMPOSITE_CONTAINER_HPP_

#include <munin/component.hpp>
#include <munin/container.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

namespace munin {

//* =========================================================================
/// \tparam ElementType the type of the smallest element that a graphical
/// component can display.
/// \brief Implements a component that simply forwards from and to an 
/// underlying container.
///
/// \par Purpose
/// Some components are implemented by composing together several pre-
/// existing components onto a container.  However, they should not be 
/// exposed as a container, but as a component.  By inheriting from this
/// class, which simply forwards functions and messages to and from the
/// underlying container, this can be achieved more easily.
//* =========================================================================
template <class ElementType>
class composite_component
    : public component<ElementType>
{
public :
    typedef component<ElementType> component_type;
    typedef container<ElementType> container_type;

    //* =====================================================================
    /// \brief Constructor
    /// \param underlying_container A container that this component will
    /// wrap.
    //* =====================================================================
    composite_component(
        boost::shared_ptr<container_type> underlying_container)
      : container_(underlying_container)
    {
        // Connect the underlying container's default signals to the signals
        // of this component with.
        container_->on_redraw.connect(boost::bind(
            &composite_component::on_redraw, this));

        container_->on_position_changed.connect(boost::bind(
            &composite_component::on_position_changed, this));

        container_->on_focus_set.connect(boost::bind(
            &composite_component::on_focus_set, this));

        container_->on_focus_lost.connect(boost::bind(
            &composite_component::on_focus_lost, this));

        container_->on_cursor_state_changed.connect(boost::bind(
            &composite_component::on_cursor_state_changed, this));

        container_->on_cursor_position_changed.connect(boost::bind(
            &composite_component::on_cursor_position_changed, this));
    }

    //* =====================================================================
    /// \brief Destructor
    //* =====================================================================
    virtual ~composite_component()
    {
    }

protected :
    //* =====================================================================
    /// \brief Retrieve the underlying container.
    //* =====================================================================
    boost::shared_ptr<container_type> get_container()
    {
        return container_;
    }

private :
    //* =====================================================================
    /// \brief Called by set_position().  Derived classes must override this
    /// function in order to set the position of the component in a custom
    /// manner.
    //* =====================================================================
    virtual void do_set_position(point const &position) 
    {
        container_->set_position(position);
    }
    
    //* =====================================================================
    /// \brief Called by get_position().  Derived classes must override this
    /// function in order to get the position of the component in a custom
    /// manner.
    //* =====================================================================
    virtual point do_get_position() const 
    {
        return container_->get_position();
    }
    
    //* =====================================================================
    /// \brief Called by set_size().  Derived classes must override this 
    /// function in order to set the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual void do_set_size(extent const &size) 
    {
        container_->set_size(size);
    }

    //* =====================================================================
    /// \brief Called by get_size().  Derived classes must override this
    /// function in order to get the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual extent do_get_size() const 
    {
        return container_->get_size();
    }

    //* =====================================================================
    /// \brief Called by get_preferred_size().  Derived classes must override
    /// this function in order to get the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual extent do_get_preferred_size() const 
    {
        return container_->get_preferred_size();
    }
    
    //* =====================================================================
    /// \brief Called by has_focus().  Derived classes must override this
    /// function in order to return whether this component has focus in a
    /// custom manner.
    //* =====================================================================
    virtual bool do_has_focus() const 
    {
        return container_->has_focus();
    }
    
    //* =====================================================================
    /// \brief Called by can_focus().  Derived classes must override this
    /// function in order to return whether this component can be focused in
    /// a custom manner.
    //* =====================================================================
    virtual bool do_can_focus() const 
    {
        return container_->can_focus();
    }
    
    //* =====================================================================
    /// \brief Called by set_focus().  Derived classes must override this
    /// function in order to set the focus to this component in a custom
    /// manner.
    //* =====================================================================
    virtual void do_set_focus() 
    {
        container_->set_focus();
    }
    
    //* =====================================================================
    /// \brief Called by lose_focus().  Derived classes must override this
    /// function in order to lose the focus from this component in a
    /// custom manner.
    //* =====================================================================
    virtual void do_lose_focus() 
    {
        container_->lose_focus();
    }
    
    //* =====================================================================
    /// \brief Called by focus_next().  Derived classes must override this
    /// function in order to move the focus in a custom manner.
    //* =====================================================================
    virtual void do_focus_next() 
    {
        container_->focus_next();
    }
    
    //* =====================================================================
    /// \brief Called by focus_previous().  Derived classes must override 
    /// this function in order to move the focus in a custom manner.
    //* =====================================================================
    virtual void do_focus_previous() 
    {
        container_->focus_previous();
    }
    
    //* =====================================================================
    /// \brief Called by get_focussed_component().  Derived classes must
    /// override this function in order to return the focussed component
    /// in a custom manner.
    //* =====================================================================
    virtual boost::shared_ptr<component_type> do_get_focussed_component() 
    {
        return container_->get_focussed_component();
    }
    
    //* =====================================================================
    /// \brief Called by get_cursor_state().  Derived classes must override
    /// this function in order to return the cursor state in a custom manner.
    //* =====================================================================
    virtual bool do_get_cursor_state() const 
    {
        return container_->get_cursor_state();
    }
    
    //* =====================================================================
    /// \brief Called by get_cursor_position().  Derived classes must
    /// override this function in order to return the cursor position in
    /// a custom manner.
    //* =====================================================================
    virtual point do_get_cursor_position() const 
    {
        return container_->get_cursor_position();
    }
    
    //* =====================================================================
    /// \brief Called by draw().  Derived classes must override this function
    /// in order to draw onto the passed canvas.  A component must only draw 
    /// the part of itself specified by the region.
    ///
    /// \param cvs the canvas in which the component should draw itself.
    /// \param offset the position of the parent component (if there is one)
    ///        relative to the canvas.  That is, (0,0) to this component
    ///        is actually (offset.x, offset.y) in the canvas.
    /// \param region the region relative to this component's origin that
    /// should be drawn.
    //* =====================================================================
    virtual void do_draw(
        canvas<element_type> &cvs
      , point const          &offset
      , rectangle const      &region) 
    {
        container_->draw(cvs, offset, region);
    }

    //* =====================================================================
    /// \brief Called by event().  Derived classes must override this 
    /// function in order to handle events in a custom manner.
    //* =====================================================================
    virtual void do_event(boost::any const &event) 
    {
        container_->event(event);
    }

    boost::shared_ptr<container_type> container_;
};

}

#endif