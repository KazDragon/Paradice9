set (MUNIN_SOURCE_FILES
    src/text/default_multiline_document.cpp
    src/text/default_singleline_document.cpp
    src/text/document.cpp
    src/algorithm.cpp
    src/aligned_layout.cpp
    src/background_fill.cpp
    src/basic_component.cpp
    src/basic_container.cpp
    src/basic_frame.cpp
    src/button.cpp
    src/card.cpp
    src/clock.cpp
    src/compass_layout.cpp
    src/component.cpp
    src/composite_component.cpp
    src/container.cpp
    src/context.cpp
    src/dropdown_list.cpp
    src/edit.cpp
    src/filled_box.cpp
    src/frame.cpp
    src/framed_component.cpp
    src/grid_layout.cpp
    src/horizontal_scroll_bar.cpp
    src/horizontal_squeeze_layout.cpp
    src/horizontal_strip_layout.cpp
    src/image.cpp
    src/layout.cpp
    src/list.cpp
    src/named_frame.cpp
    src/rectangle.cpp
    src/scroll_pane.cpp
    src/solid_frame.cpp
    src/status_bar.cpp
    src/tabbed_frame.cpp
    src/tabbed_panel.cpp
    src/text_area.cpp
    src/toggle_button.cpp
    src/vertical_scroll_bar.cpp
    src/vertical_squeeze_layout.cpp
    src/vertical_strip_layout.cpp
    src/viewport.cpp
    src/window.cpp
)

set (MUNIN_INCLUDE_FILES
    include/munin/algorithm.hpp
    include/munin/aligned_layout.hpp
    include/munin/background_fill.hpp
    include/munin/basic_component.hpp
    include/munin/basic_container.hpp
    include/munin/basic_frame.hpp
    include/munin/button.hpp
    include/munin/card.hpp
    include/munin/clock.hpp
    include/munin/compass_layout.hpp
    include/munin/component.hpp
    include/munin/composite_component.hpp
    include/munin/container.hpp
    include/munin/context.hpp
    include/munin/dropdown_list.hpp
    include/munin/edit.hpp
    include/munin/export.hpp
    include/munin/filled_box.hpp
    include/munin/framed_component.hpp
    include/munin/frame.hpp
    include/munin/grid_layout.hpp
    include/munin/horizontal_scroll_bar.hpp
    include/munin/horizontal_squeeze_layout.hpp
    include/munin/horizontal_strip_layout.hpp
    include/munin/image.hpp
    include/munin/layout.hpp
    include/munin/list.hpp
    include/munin/named_frame.hpp
    include/munin/rectangle.hpp
    include/munin/sco_glyphs.hpp
    include/munin/scroll_pane.hpp
    include/munin/solid_frame.hpp
    include/munin/status_bar.hpp
    include/munin/tabbed_frame.hpp
    include/munin/tabbed_panel.hpp
    include/munin/text_area.hpp
    include/munin/toggle_button.hpp
    include/munin/vertical_scroll_bar.hpp
    include/munin/vertical_squeeze_layout.hpp
    include/munin/vertical_strip_layout.hpp
    include/munin/view.hpp
    include/munin/viewport.hpp
    include/munin/unicode_glyphs.hpp
    include/munin/window.hpp
    include/munin/text/default_multiline_document.hpp
    include/munin/text/default_singleline_document.hpp
    include/munin/text/document.hpp
)

add_library(munin
    ${MUNIN_SOURCE_FILES}
    ${MUNIN_INCLUDE_FILES}
)

set_target_properties(munin
    PROPERTIES
        CXX_VISIBILITY_PRESET hidden)

target_include_directories(munin
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(munin
    PUBLIC
        odin
        terminalpp
        ${Boost_SIGNALS_LIBRARY}
)

#Remove when we move to signals2 or some other mechanism.
target_compile_definitions(munin
    PRIVATE BOOST_SIGNALS_NO_DEPRECATION_WARNING
)

target_compile_features(munin
    PRIVATE 
        cxx_auto_type
        cxx_strong_enums
        cxx_generic_lambdas
)

generate_export_header(munin
    EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/munin/export.hpp"
)
