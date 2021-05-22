cmake_minimum_required(VERSION 3.1)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(game main.cpp archer.cpp archerdec.cpp dragon.cpp dragondec.cpp giant.cpp giantdec.cpp rider.cpp riderdec.cpp fraction.cpp game.cpp village unit.cpp attackvisitor.cpp upgradevisitor.cpp iterator.cpp mergevisitor.cpp logic.cpp PlayCommand.cpp PrintWCommand.cpp)

target_link_libraries(game ${CURSES_LIBRARIES})
