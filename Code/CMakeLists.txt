cmake_minimum_required(VERSION 3.10)

project(NewMillennium C)

if(BUILDTARGET STREQUAL "SDL2")
find_package(SDL2 REQUIRED)

find_package(SDL2_mixer REQUIRED)
endif()

set(SOURCES
  am_map.c
  command.c
  console.c
  d_clisrv.c
  d_items.c
  d_main.c
  d_net.c
  d_netcmd.c
  d_netfil.c
  dehacked.c
  dstrings.c
  f_finale.c
  f_wipe.c
  g_game.c
  g_state.c
  g_input.c
  hu_stuff.c
  i_tcp.c
  info.c
  m_argv.c
  m_bbox.c
  m_cheat.c
  m_fixed.c
  m_menu.c
  m_misc.c
  m_random.c
  p_ceilng.c
  p_doors.c
  p_enemy.c
  p_fab.c
  p_floor.c
  p_inter.c
  p_lights.c
  p_map.c
  p_maputl.c
  p_mobj.c
  p_plats.c
  p_pspr.c
  p_saveg.c
  p_sight.c
  p_setup.c
  p_spec.c
  p_switch.c
  p_telept.c
  p_tick.c
  p_user.c
  r_bsp.c
  r_data.c
  r_draw.c
  r_draw16.c
  r_draw8.c
  r_main.c
  r_plane.c
  r_segs.c
  r_sky.c
  r_splats.c
  r_things.c
  s_sound.c
  screen.c
  sounds.c
  st_lib.c
  st_stuff.c
  tables.c
  v_video.c
  w_wad.c
  wi_stuff.c
  z_zone.c
)

if(BUILDTARGET STREQUAL "SDL2")
# SDL2 build, the usual for Windows/Linux
  list(APPEND SOURCES
    sdl2/dosstr.c
    sdl2/i_cdmus.c
    sdl2/i_main.c
    sdl2/i_net.c
    sdl2/i_sound.c
    sdl2/i_system.c
    sdl2/i_video.c
  )
elseif(BUILDTARGET STREQUAL "CTR")
# 3DS target
  list(APPEND SOURCES
    CTR/i_cdmus.c
    CTR/i_main.c
    CTR/i_net.c
    CTR/i_sound.c
    CTR/i_system.c
    CTR/i_video.c
  )
endif()

add_executable(${PROJECT_NAME}
	${SOURCES}
)

if(BUILDTARGET STREQUAL "SDL2")
include_directories(
  ${SDL2_INCLUDE_DIRS} 
  ${SDL_MIXER_INCLUDE_DIRS}
)

set(LIBARIES
	${SDL2_LIBRARIES}
	SDL2_mixer::SDL2_mixer
	m
)

elseif(BUILDTARGET STREQUAL "CTR")
target_link_libraries(${PROJECT_NAME} PRIVATE "-lm")
endif()

if(BUILDTARGET STREQUAL "SDL2")
target_link_libraries(${PROJECT_NAME} PRIVATE 
	${LIBRARIES}
)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
	set(CFLAGS
		-fPIE
		-Wno-int-conversion
		-fpermissive
		-g
		#-m486
		-O0
		-ffast-math
		-fomit-frame-pointer
	)
	if(BUILDTARGET STREQUAL "SDL2")
		list(APPEND CFLAGS
			-DLINUX
			-HAVE_SDL
		)
	elseif(BUILDTARGET STREQUAL "CTR")
		list(APPEND CFLAGS -DCTR)
	endif()
else()
# Assume we're using MSVC, as I doubt too many people are seriously using the Intel compiler or OpenWatcom or something to compile this
	set(CFLAGS
		/DHAVE_SDL 
		/wd4244 
		/Zi 
		/Od 
		/fp:fast 
		/Oy 
		/arch:IA32
	)
endif()


target_compile_options(${PROJECT_NAME} PRIVATE
	${CFLAGS}
)

# Make sure the CTR build has a different extension than the Linux/Unix build
if(BUILDTARGET STREQUAL "CTR")
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "NewMillennium"
    SUFFIX ".elf"
)
endif()