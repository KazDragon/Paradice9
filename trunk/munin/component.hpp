// ==========================================================================
// Munin Component.
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
#ifndef MUNIN_COMPONENT_HPP_
#define MUNIN_COMPONENT_HPP_

#include "munin/types.hpp"
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>
#include <vector>

namespace munin {
    
template <class ElementType>
class container;

template <class ElementType>
class canvas;

//* =========================================================================
/// \brief An object capable of being drawn on a canvas.
/// \par
/// A component is a fundamental piece of the munin architecture and is the
/// base class for anything that is capable of being drawn in some way.  It
/// is closely attached to its canvas, with which it shares an
/// ElementType.  This type is the fundamental graphical unit, which could 
/// be a coloured pixel, or an attributed character, or something else. 
//* =========================================================================
template <class ElementType>
class component
{
public :
    typedef ElementType            element_type;
    typedef component<ElementType> component_type;

    //* =====================================================================
    /// \brief Destructor
    //* =====================================================================
    virtual ~component()
    {
    }
    
    //* =====================================================================
    /// \brief Sets the position of this component.  This does not cause a
    /// redraw, on the basis that the entity performing the move (usually
    /// a layout manager) knows about it, and is better informed about all
    /// regions redrawn.
    //* =====================================================================
    void set_position(point const &position)
    {
        do_set_position(position);
    }
    
    //* =====================================================================
    /// \brief Retrieve the position of this component.
    //* =====================================================================
    point get_position() const
    {
        return do_get_position();
    }
    
    //* =====================================================================
    /// \brief Sets the size of this component.  This does not cause a
    /// redraw, on the basis that the entity performing the resize (usually
    /// a layout manager) knows about it, and is better informed about all
    /// regions redrawn.
    //* =====================================================================
    void set_size(extent const &size)
    {
        do_set_size(size);
    }

    //* =====================================================================
    /// \brief Retreives the size of this component.
    //* =====================================================================
    extent get_size() const
    {
        return do_get_size();
    }
    
    //* =====================================================================
    /// \brief Retrieves the preferred size of this component.
    /// \par
    /// The preferred size of a component is the size at which all elements
    /// can be displayed with clarity.  For example, the preferred size of
    /// a static text control with the following text:
    /// \code
    /// This is a
    /// Static Text Box
    /// \endcode
    /// would be (15, 2).
    //* =====================================================================
    extent get_preferred_size() const
    {
        return do_get_preferred_size();
    }
    
    //* =====================================================================
    /// \brief Sets the parent of the component
    //* =====================================================================
    void set_parent(boost::shared_ptr< container<element_type> > const &parent)
    {
        do_set_parent(parent);
    }
    
    //* =====================================================================
    /// \brief Retrieves the parent of this component.
    //* =====================================================================
    boost::shared_ptr< container<element_type> > get_parent() const
    {
        return do_get_parent();
    }
    
    //* =====================================================================
    /// \brief Returns whether this component currently has focus.
    //* =====================================================================
    bool has_focus() const
    {
        return do_has_focus();
    }
    
    //* =====================================================================
    /// \brief Returns whether this component can be focused.
    //* =====================================================================
    bool can_focus() const
    {
        return do_can_focus();
    }
    
    //* =====================================================================
    /// \brief Sets this component to have the focus.
    //* =====================================================================
    void set_focus()
    {
        do_set_focus();
    }
    
    //* =====================================================================
    /// \brief Causes this component to lose its focus.
    //* =====================================================================
    void lose_focus()
    {
        do_lose_focus();
    }
    
    //* =====================================================================
    /// \brief If this component has subcomponents, causes the component to
    /// move the focus from the currently focused subcomponent to the next
    /// subcomponent.  If it is a leaf component, then it toggles its focus,
    /// simulating a container with one element.
    //* =====================================================================
    void focus_next()
    {
        do_focus_next();
    }
    
    //* =====================================================================
    /// \brief If this component has subcomponents, causes the component to
    /// move the focus from the currently focused subcomponent to the 
    /// previous subcomponent.  If it is a leaf component, then it toggles 
    /// its focus, simulating a container with one element.
    //* =====================================================================
    void focus_previous()
    {
        do_focus_previous();
    }
    
    //* =====================================================================
    /// \brief Returns component with focus at the deepest part of the
    /// component heirarchy, or an empty shared_ptr<> if no component has
    /// focus.
    //* =====================================================================
    boost::shared_ptr<component_type> get_focussed_component()
    {
        return do_get_focussed_component();
    }
    
    //* =====================================================================
    /// \brief Returns true if this component has a visible cursor, false
    /// otherwise.
    //* =====================================================================
    bool get_cursor_state() const
    {
        return do_get_cursor_state();
    }
    
    //* =====================================================================
    /// \brief Returns the cursor's current position within the component.
    //* =====================================================================
    point get_cursor_position() const
    {
        return do_get_cursor_position();
    }
    
    //* =====================================================================
    /// \brief Draws the component.
    ///
    /// \param cvs the canvas in which the component should draw itself.
    /// \param offset the position of the parent component (if there is one)
    ///        relative to the canvas.
    /// \param region the region relative to this component's origin that
    /// should be drawn.
    //* =====================================================================
    void draw(
        canvas<element_type> &cvs
      , point const          &offset
      , rectangle const      &region)
    {
        do_draw(cvs, offset, region);
    }
    
    //* =====================================================================
    /// \brief Send an event to the component.  This may be of any type.
    /// A component must specify the types of messages it may receive and
    /// what it will do with it.
    //* =====================================================================
    void event(boost::any const &event)
    {
        do_event(event);
    }
    
    //* =====================================================================
    /// \fn on_redraw
    /// \param regions The regions of the component that requires redrawing.
    /// \brief Connect to this signal in order to receive notifications about
    /// when the component should be redrawn.
    //* =====================================================================
    boost::signal
    <
        void (std::vector<rectangle> regions)
    > on_redraw;
    
    //* =====================================================================
    /// \fn on_position_changed
    /// \param from The position from which the component moved.
    /// \param to   The position to which the component moved.
    /// \brief Connect to this signal in order to receive notification about
    /// when the component changes position.
    //* =====================================================================
    boost::signal
    <
        void (point from, point to)
    > on_position_changed;
    
    //* =====================================================================
    /// \fn on_focus_set
    /// \brief Connect to this signal in order to receive notifications about
    /// when the component has gained focus.
    //* =====================================================================
    boost::signal<
        void ()
    > on_focus_set;
    
    //* =====================================================================
    /// \fn on_focus_lost
    /// \brief Connect to this signal in order to receive notifications about
    /// when the component has lost focus.
    //* =====================================================================
    boost::signal<
        void ()
    > on_focus_lost;
    
    //* =====================================================================
    /// \fn on_cursor_state_changed
    /// \brief Connect to this signal in order to receive notifications about
    /// when the component's cursor state changes.
    //* =====================================================================
    boost::signal<
        void (bool)
    > on_cursor_state_changed;
    
    //* =====================================================================
    /// \fn on_cursor_position_changed
    /// \brief Connect to this signal in order to receive notifications about
    /// when the component's cursor position changes.
    //* =====================================================================
    boost::signal<
        void (point)
    > on_cursor_position_changed;
    
private :
    //* =====================================================================
    /// \brief Called by set_position().  Derived classes must override this
    /// function in order to set the position of the component in a custom
    /// manner.
    //* =====================================================================
    virtual void do_set_position(point const &position) = 0;
    
    //* =====================================================================
    /// \brief Called by get_position().  Derived classes must override this
    /// function in order to get the position of the component in a custom
    /// manner.
    //* =====================================================================
    virtual point do_get_position() const = 0;
    
    //* =====================================================================
    /// \brief Called by set_size().  Derived classes must override this 
    /// function in order to set the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual void do_set_size(extent const &size) = 0;

    //* =====================================================================
    /// \brief Called by get_size().  Derived classes must override this
    /// function in order to get the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual extent do_get_size() const = 0;

    //* =====================================================================
    /// \brief Called by get_preferred_size().  Derived classes must override
    /// this function in order to get the size of the component in a custom 
    /// manner.
    //* =====================================================================
    virtual extent do_get_preferred_size() const = 0;
    
    //* =====================================================================
    /// \brief Called by set_parent().  Derived classes must override this
    /// function in order to set the parent of the component in a custom
    /// manner.
    //* =====================================================================
    virtual void do_set_parent(
        boost::shared_ptr< container<element_type> > const &parent) = 0;
    
    //* =====================================================================
    /// \brief Called by get_parent().  Derived classes must override this
    /// function in order to get the parent of the component in a custom
    /// manner.
    //* =====================================================================
    virtual boost::shared_ptr< 
        container<element_type> 
    > do_get_parent() const = 0;
    
    //* =====================================================================
    /// \brief Called by has_focus().  Derived classes must override this
    /// function in order to return whether this component has focus in a
    /// custom manner.
    //* =====================================================================
    virtual bool do_has_focus() const = 0;
    
    //* =====================================================================
    /// \brief Called by can_focus().  Derived classes must override this
    /// function in order to return whether this component can be focused in
    /// a custom manner.
    //* =====================================================================
    virtual bool do_can_focus() const = 0;
    
    //* =====================================================================
    /// \brief Called by set_focus().  Derived classes must override this
    /// function in order to set the focus to this component in a custom
    /// manner.
    //* =====================================================================
    virtual void do_set_focus() = 0;
    
    //* =====================================================================
    /// \brief Called by lose_focus().  Derived classes must override this
    /// function in order to lose the focus from this component in a
    /// custom manner.
    //* =====================================================================
    virtual void do_lose_focus() = 0;
    
    //* =====================================================================
    /// \brief Called by focus_next().  Derived classes must override this
    /// function in order to move the focus in a custom manner.
    //* =====================================================================
    virtual void do_focus_next() = 0;
    
    //* =====================================================================
    /// \brief Called by focus_previous().  Derived classes must override 
    /// this function in order to move the focus in a custom manner.
    //* =====================================================================
    virtual void do_focus_previous() = 0;
    
    //* =====================================================================
    /// \brief Called by get_focussed_component().  Derived classes must
    /// override this function in order to return the focussed component
    /// in a custom manner.
    //* =====================================================================
    virtual boost::shared_ptr<component_type> do_get_focussed_component() = 0;
    
    //* =====================================================================
    /// \brief Called by get_cursor_state().  Derived classes must override
    /// this function in order to return the cursor state in a custom manner.
    //* =====================================================================
    virtual bool do_get_cursor_state() const = 0;
    
    //* =====================================================================
    /// \brief Called by get_cursor_position().  Derived classes must
    /// override this function in order to return the cursor position in
    /// a custom manner.
    //* =====================================================================
    virtual point do_get_cursor_position() const = 0;
    
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
      , rectangle const      &region) = 0;

    //* =====================================================================
    /// \brief Called by event().  Derived classes must override this 
    /// function in order to handle events in a custom manner.
    //* =====================================================================
    virtual void do_event(boost::any const &event) = 0;
};
    
}

#endif