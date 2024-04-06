cmake_minimum_required(VERSION 3.16)
project(aura_darwin CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_library.h
   appindicator.cpp
   appindicator.h
   _factory.cpp
   framework.cpp
   framework.h
   node.cpp
   node.h
   shell.cpp
   shell.h
   )


list(APPEND library_references
   acme
   acme_posix
   acme_darwin
   apex
   apex_posix
   apex_darwin
   aqua
   aura
   aura_posix
   )

#
#if(WITH_X11 OR WITH_XCB)
#
#
#   list(APPEND library_source
#           x11/_.h
#
#           x11/_.cpp
#      x11/_constant.h
#      x11/window.cpp
#      x11/window.h
#      x11/windowing.cpp
#      x11/windowing.h
#   )
#
#
##   if(WITH_X11)
#
#      list(APPEND library_source
#      x11/display_lock.cpp
#      x11/display_lock.h
#     x11/startup-notification.cpp
#     x11/startup-notification.h
#      x11/xim_keyboard.cpp
#      x11/xim_keyboard.h
#         )
#
# #  endif()
#
#endif()


#add_library(${PROJECT_NAME} SHARED ${library_source} user_notify_icon_bridge.h x11/desktop_environment.h x11/desktop_environment.cpp)
#add_library(static_${PROJECT_NAME} STATIC ${library_source} user_notify_icon_bridge.h x11/desktop_environment.h x11/desktop_environment.cpp)
add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})


#list(APPEND library_references
#        acme
#        acme_posix
#        acme_darwin
#        apex
#        apex_posix
#        apex_darwin
#        aura
#        aura_posix)

if (NOT ${NO_PRECOMPILED_HEADER})

   target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
   target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

endif ()



list(APPEND static_library_references ${library_references})

list(TRANSFORM static_library_references PREPEND static_)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)


   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})


elseif(${LINUX} OR ${FREEBSD} OR ${OPENBSD} OR ${NETBSD})


   list(APPEND extra_pkg_modules
      libstartup-notification-1.0
      )

if(WITH_XCB)


   list(APPEND extra_pkg_modules
               x11 x11-xcb
      )


else()


   list(APPEND extra_pkg_modules
               x11
      )


endif()


   if(NOT DONT_USE_PKG_CONFIG)
      pkg_check_modules(PKGCONFIG ${extra_pkg_modules})
   endif()
     target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_options(static_${PROJECT_NAME} PRIVATE -fpermissive)
   target_compile_definitions(static_${PROJECT_NAME} PRIVATE CUBE)


   target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${static_library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   # target_link_options(static_${PROJECT_NAME} PRIVATE --whole-archive)



endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_LIBRARY)



