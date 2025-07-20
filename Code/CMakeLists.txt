cmake_minimum_required(VERSION 3.10)

project(NewMillenium C)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
  am_map.c
  command.c
  d_clisrv.c
  d_main.c
  d_net.c
  d_netfil.c
  dehacked.c
  dstrings.c
  f_finale.c
  f_wipe.c
  g_input.c
  hu_stuff.c
  i_tcp.c
  m_argv.c
  m_bbox.c
  m_cheat.c
  m_fixed.c
  m_misc.c
  m_random.c
  p_ceilng.c
  p_doors.c
  p_lights.c
  p_map.c
  p_maputl.c
  p_saveg.c
  p_sight.c
  p_telept.c
  p_tick.c
  r_data.c
  r_draw.c
  r_draw16.c
  r_draw8.c
  r_main.c
  r_plane.c
  r_segs.c
  r_sky.c
  r_splats.c
  screen.c
  sounds.c
  st_stuff.c
  tables.c
  v_video.c
  w_wad.c
  wi_stuff.c
  z_zone.c
  console.c
  d_netcmd.c
  g_game.c
  info.c
  m_menu.c
  p_enemy.c
  p_fab.c
  p_floor.c
  p_inter.c
  p_mobj.c
  p_setup.c
  p_spec.c
  p_user.c
  r_bsp.c
  r_things.c
  s_sound.c
 
  sdl2/i_cdmus.c
  sdl2/i_main.c
  sdl2/i_net.c
  sdl2/i_sound.c
  sdl2/i_system.c
  sdl2/i_video.c
)



target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/../lib")

target_link_libraries(${PROJECT_NAME} PRIVATE 
	${SDL2_LIBRARIES}
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-DLINUX
    -fno-pie
    -Wno-int-conversion
    -fpermissive
    -g
    #-m486
    -O3
    -ffast-math
    -fomit-frame-pointer
)