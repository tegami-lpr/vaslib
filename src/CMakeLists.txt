set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC             ON)
set(CMAKE_AUTORCC             ON)
set(CMAKE_AUTOUIC             ON)

# Qt's components
find_package(Qt5 COMPONENTS Core Gui Network Widgets Xml REQUIRED)
set(QT_DEPS_LIBRARIES Qt5:Core Qt5:Gui Qt5::Network Qt5:Widgets Qt5:Xml)

#file(GLOB HEADER_FILES *.h)
#file(GLOB SOURCE_FILES *.cpp)
#file(GLOB UI_FILES *.ui)
#file(GLOB RC_FILES *.rc)

if(WIN32)
    # Files to be included for P3D support
    file(GLOB P3D_SOURCES code_timer.cpp fsaccess_msfs.cpp fsuipc.cpp)
    file(GLOB P3D_HEADERS code_timer.h fsaccess_msfs.h fsuipc.h FSUIPC_User.h)
endif(WIN32)

if(XPLANE_SUPPORT)
    file(GLOB XPLANE_SOURCES fsaccess_xplane.cpp)
    file(GLOB XPLANE_HEADERS fsaccess_xplane_defines.h fsaccess_xplane.h canas.h)
endif(XPLANE_SUPPORT)

# Files to be included for reading XML
file(GLOB COMMONXML_SOURCES xml.model.cpp)
file(GLOB COMMONXML_HEADERS xml.model.h)

# Files to be included for vascharts
# XXX: not used anymore?
file(GLOB CHARTS_SOURCES chartwidget.cpp ge.cpp ge_projection.cpp ge_list.cpp ge_layers.cpp ge_rect.cpp
        ge_label.cpp ge_vor.cpp ge_ndb.cpp ge_airport.cpp ge_intersection.cpp ge_route.cpp treebase.cpp
        treebase_xml.cpp treebase_xml_chart.cpp chartmodel.cpp chart.xml.defines.cpp chart.elem.root.cpp
        chart.elem.info.cpp chart.elem.projection.cpp chart.elem.navaids.cpp chart.elem.routes.cpp chart.elem.texts.cpp
        chart.elem.navaid.cpp chart.elem.route.cpp chart.elem.text.cpp chart.elem.vor.cpp chart.elem.ndb.cpp
        chart.elem.airport.cpp chart.elem.intersection.cpp chartinfodlgimpl.cpp routedlgimpl.cpp ge_textrect.cpp
        waypointchoosedlgimpl.cpp textelemdlgimpl.cpp)
file(GLOB CHARTS_HEADERS chartwidget.h ge.h ge_projection.h ge_list.h ge_layers.h ge_rect.h ge_label.h
        ge_vor.h ge_ndb.h ge_airport.h ge_intersection.h ge_route.h treebase.h treebase_xml.h treebase_xml_chart.h
        chartmodel.h chart.xml.defines.h chart.elem.root.h chart.elem.info.h chart.elem.projection.h chart.elem.navaids.h
        chart.elem.routes.h chart.elem.texts.h chart.elem.navaid.h chart.elem.route.h chart.elem.text.h chart.elem.vor.h
        chart.elem.ndb.h chart.elem.airport.h chart.elem.intersection.h chartinfodlgimpl.h waypointchoosedlgimpl.h anchor_latlon.h
        termination_callback.h routedlgimpl.h ge_textrect.h waypointchoosedlgimpl.h textelemdlgimpl.h)
file(GLOB CHARTS_UI chart.info.dlg.ui)

# The files constituting vaslib itself
file(GLOB VASLIB_SOURCES assert.cpp config.cpp configwidget.cpp logger.cpp pushbutton.cpp mouse_input_area.cpp smoothing.cpp
        waypoint.cpp airport.cpp runway.cpp intersection.cpp ndb.cpp vor.cpp ils.cpp holding.cpp route.cpp airway.cpp procedure.cpp
        procedure_serialization.cpp sid.cpp star.cpp transition.cpp approach.cpp flightroute.cpp flightstatus.cpp fsaccess.cpp
        navcalc.cpp navdata.cpp geodata.cpp weather.cpp projection_mercator.cpp projection_greatcircle.cpp transport_layer_iface.cpp
        transport_layer_tcpclient.cpp transport_layer_tcpserver.cpp transport_layer_tcpserver_clientbuffer.cpp containerfactory.cpp
        containerbase.cpp infodlgimpl.cpp declination.cpp declination_geomag.cpp vroute.cpp vas_path.cpp controller_throttle.cpp
        controller_speed.cpp fly_by_wire.cpp flight_mode_tracker.cpp statistics.cpp aircraft_data.cpp noise_generator.cpp)
file(GLOB VASLIB_HEADERS ptrlist.h assert.h config.h configwidget.h logger.h meanvalue.h median.h pushbutton.h
        mouse_input_area.h smoothing.h waypoint.h waypoint_hdg_to_alt.h waypoint_hdg_to_intercept.h airport.h
        runway.h intersection.h ndb.h vor.h ils.h holding.h route.h airway.h procedure.h procedure_serialization.h
        sid.h star.h transition.h approach.h flightroute.h flightstatus.h fsaccess.h navcalc.h navdata.h gshhs.h
        geodata.h weather.h projection.h projection_mercator.h projection_greatcircle.h transport_layer_iface.h
        transport_layer_tcpclient.h transport_layer_tcpserver.h transport_layer_tcpserver_clientbuffer.h containerfactory.h
        containerbase.h infodlgimpl.h declination.h declination_geomag.h vroute.h vas_path.h trend.h controller_base.h
        controller_throttle.h controller_speed.h fly_by_wire.h flight_mode_tracker.h statistics.h aircraft_data.h serialization_iface.h
        fmc_data_provider.h bithandling.h noise_generator.h)
file(GLOB VASLIB_UI waypointchoosedlg.ui routedlg.ui infodlg.ui chart.info.dlg.ui latlonpointdlg.ui pbdpointdlg.ui textelemdlg.ui)

set_source_files_properties(${PROJECT_NAME}.rc PROPERTIES LANGUAGE RC)

add_library(${PROJECT_NAME} STATIC ${VASLIB_SOURCES} ${VASLIB_HEADERS} ${VASLIB_UI} ${P3D_HEADERS} ${P3D_SOURCES} ${UI_FILES} ${RC_FILES} )

#XXX: cmake don't want add some Qt5 includes to target includes...
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Xml_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    ${QT_DEPS_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


