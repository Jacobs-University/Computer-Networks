# Properties -> C/C++ -> General -> Additional Include Directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# ================================================= DayTime TCP Client =================================================
add_executable(Daytime_TCP_Client "Daytime TCP Client.cpp")

set_target_properties(Daytime_TCP_Client PROPERTIES PROJECT_LABEL "Daytime TCP Client")						# in Visual Studio
set_target_properties(Daytime_TCP_Client PROPERTIES OUTPUT_NAME "time-clinet")
set_target_properties(Daytime_TCP_Client PROPERTIES FOLDER "Demos")

# Properties->Linker->Input->Additional Dependencies
if(WIN32)
target_link_libraries(Daytime_TCP_Client wsock32 ws2_32)
endif(WIN32)

# ================================================= DayTime TCP Server =================================================
add_executable(Daytime_TCP_Server "Daytime TCP Server.cpp")

set_target_properties(Daytime_TCP_Server PROPERTIES PROJECT_LABEL "Daytime TCP Server")						# in Visual Studio
set_target_properties(Daytime_TCP_Server PROPERTIES OUTPUT_NAME "time-server")
set_target_properties(Daytime_TCP_Server PROPERTIES FOLDER "Demos")

# Properties->Linker->Input->Additional Dependencies
if(WIN32)
target_link_libraries(Daytime_TCP_Server wsock32 ws2_32)
endif(WIN32)

# ================================================= DayTime HTTP Server =================================================
add_executable(Daytime_HTTP_Server "Daytime HTTP Server.cpp")

set_target_properties(Daytime_HTTP_Server PROPERTIES PROJECT_LABEL "Daytime HTTP Server")						# in Visual Studio
set_target_properties(Daytime_HTTP_Server PROPERTIES OUTPUT_NAME "http-time-server")
set_target_properties(Daytime_HTTP_Server PROPERTIES FOLDER "Demos")

# Properties->Linker->Input->Additional Dependencies
if(WIN32)
target_link_libraries(Daytime_HTTP_Server wsock32 ws2_32)
endif(WIN32)
