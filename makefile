CC           = g++
AR           = ar -r
RM           = rm -f
MAKE         = make -C
DEBUG        = #-ggdb
OPTIM        = -O2 -DNDEBUG
PROF         = #-pg
CRYPT        = -DPARADICE_USE_CRYPTOPP
D_FLAGS      = -D_WIN32_WINNT=0x0501 -D__USE_W32_SOCKETS
C_FLAGS      = -ansi -pedantic -Wall $(D_FLAGS) $(DEBUG) $(OPTIM) $(PROF) \
               $(CRYPT)
NAME_IS      = -o
I_DIRS       = -I.
NOLINK       = -c
L_DIRS       = -L.
G_LIBS       = -lmunin -lodin -lboost_program_options -lboost_system \
               -lboost_signals -lws2_32 -lwsock32
LIBS         = -lparadice -lhugin -lmunin -lodin -lboost_program_options \
               -lboost_filesystem -lboost_system -lboost_signals \
               -lboost_serialization -lcryptopp \
               -lws2_32 -lwsock32 
E_NAME       = paradice.exe
G_NAME       = guibuilder.exe

ODIN_NAMES        = ansi/protocol \
                    net/socket \
                    telnet/client_option \
                    telnet/command_router \
                    telnet/input_visitor \
                    telnet/negotiation_router \
                    telnet/protocol \
                    telnet/server_option \
                    telnet/subnegotiation_router \
                    telnet/stream \
                    telnet/options/naws_client \
                    telnet/options/terminal_type_client \
                    tokenise
ODIN_O_FILES      = $(ODIN_NAMES:%=odin/%.o)
ODIN_LIB          = libodin.a

MUNIN_NAMES       = algorithm \
                    aligned_layout \
                    ansi/protocol \
                    attribute \
                    basic_component \
                    basic_container \
                    button \
                    canvas \
                    card \
                    compass_layout \
                    component \
                    composite_component \
                    container \
                    edit \
                    frame \
                    framed_component \
                    glyph \
                    grid_layout \
                    horizontal_scroll_bar \
                    horizontal_squeeze_layout \
                    horizontal_strip_layout \
                    image \
                    layout \
                    named_frame \
                    solid_frame \
                    text_area \
                    text/default_multiline_document \
                    text/default_singleline_document \
                    text/document \
                    types \
                    vertical_scroll_bar \
                    vertical_squeeze_layout \
                    viewport \
                    window
MUNIN_O_FILES     = $(MUNIN_NAMES:%=munin/%.o)
MUNIN_LIB         = libmunin.a

HUGIN_NAMES       = account_creation_screen \
                    character_creation_screen \
                    character_selection_screen \
                    command_prompt \
                    intro_screen \
                    main_screen \
                    password_change_screen \
                    user_interface \
                    wholist
HUGIN_O_FILES     = $(HUGIN_NAMES:%=hugin/%.o)
HUGIN_LIB         = libhugin.a

GUIBUILDER_NAMES  = client \
                    main \
                    server \
                    socket \
                    ui
GUIBUILDER_O_FILES= $(GUIBUILDER_NAMES:%=guibuilder/%.o)

PARADICE_NAMES    = account \
                    admin \
                    character \
                    client \
                    communication \
                    configuration \
                    connection \
                    cryptography \
                    dice_roll_parser \
                    help \
                    random \
                    rules \
                    server \
                    utility \
                    who
PARADICE_O_FILES  = $(PARADICE_NAMES:%=paradice/%.o)
PARADICE_LIB      = libparadice.a

PARADICE9_NAMES   = context_impl paradice9 main
PARADICE9_O_FILES = $(PARADICE9_NAMES:%=paradice9/%.o)

TEST_L_DIRS       = -L.
TEST_LIBS         = -lparadice -lmunin -lodin -lcppunit -lboost_signals \
                    -lboost_system -lboost_system -lws2_32 -lwsock32
TEST_L_FLAGS      = --enable-auto-import
TEST_FIXTURES     = ansi_parser \
                    dice_parser \
                    router \
                    runtime_array \
                    small_buffer \
                    telnet_client_option \
                    telnet_command_router \
                    telnet_generator \
                    telnet_negotiation_router \
                    telnet_options_echo_client \
                    telnet_options_naws_client \
                    telnet_options_subnegotiationless_client \
                    telnet_options_subnegotiationless_server \
                    telnet_options_suppress_goahead_client \
                    telnet_options_suppress_goahead_server \
                    telnet_options_terminal_type_client \
                    telnet_parser \
                    telnet_server_option \
                    telnet_stream \
                    telnet_subnegotiation_router \
                    telnet_input_visitor
TEST_NAMES        = paradice_test $(TEST_FIXTURES:%=%_fixture)
TEST_O_FILES      = $(TEST_NAMES:%=test/%.o)
TEST_EXE          = paradice_test.exe

$(E_NAME): $(ODIN_LIB) $(MUNIN_LIB) $(HUGIN_LIB) $(PARADICE_LIB) \
           $(TEST_EXE) $(PARADICE9_O_FILES)
	$(CC) $(NAME_IS) $@ $(PARADICE9_O_FILES) $(L_DIRS) $(LIBS)
    
$(G_NAME): $(ODIN_LIB) $(MUNIN_LIB) $(GUIBUILDER_O_FILES)
	$(CC) $(NAME_IS) $@ $(GUIBUILDER_O_FILES) $(L_DIRS) $(G_LIBS)
	
clean: 
	$(RM) $(E_NAME) $(PARADICE9_O_FILES) \
	      $(G_NAME) $(GUIBUILDER_O_FILES) \
          $(PARADICE_LIB) $(PARADICE_O_FILES) \
          $(HUGIN_LIB) $(HUGIN_O_FILES) \
          $(MUNIN_LIB) $(MUNIN_O_FILES) \
          $(ODIN_LIB) $(ODIN_O_FILES) \
          $(TEST_EXE) $(TEST_O_FILES)
    
libodin.a: $(ODIN_O_FILES)
	$(AR) $@ $(ODIN_O_FILES)

libmunin.a: $(MUNIN_O_FILES)
	$(AR) $@ $(MUNIN_O_FILES)

libhugin.a: $(HUGIN_O_FILES)
	$(AR) $@ $(HUGIN_O_FILES)

libparadice.a: $(PARADICE_O_FILES)
	$(AR) $@ $(PARADICE_O_FILES)

$(TEST_EXE): $(TEST_O_FILES) $(ODIN_LIB) $(PARADICE_LIB) \
             $(MUNIN_LIB) $(HUGIN_LIB)
	$(CC) $(NAME_IS) $@ $(TEST_O_FILES) $(TEST_L_DIRS) $(TEST_LIBS)
	./$@    
    
%.o: %.cpp
	$(CC) $(NAME_IS) $@ $(NOLINK) $(C_FLAGS) $(I_DIRS) $<

