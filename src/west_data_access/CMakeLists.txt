find_package(LibXml2 QUIET)
find_package(MDSplus QUIET)
find_package(LibTS QUIET)
find_package(HDF5 REQUIRED COMPONENTS C)

#find_package(uda QUIET)            # version moderne avec uda-config.cmake
#if(NOT uda_FOUND)
#    find_package(UDA REQUIRED)     # version ancienne avec FindUDA.cmake
#endif()

if(NOT LIBTS_FOUND)
    message(WARNING "Dépendance LibTS manquante → plugin WEST désactivé")
    return()
endif()

add_definitions(-Wno-error)

# ===================================================================
# 1. Librairie d'accès aux données WEST (remplace le plugin UDA)
# ===================================================================
add_library(west_access STATIC
        tsparse.cpp
        ts_rqparm.cpp
      #  west_plugin.cpp
     #   west_xml.cpp
        west_dynamic_data.cpp
        west_utilities.cpp
        west_dyn_data_utilities.cpp
        west_pf_active.cpp
        west_pf_passive.cpp
        west_static_data_utilities.cpp
        west_soft_x_rays.cpp
        west_summary.cpp
        west_lh_antennas.cpp          # ← on le garde ici (le main() sera ignoré grâce au #ifdef)
        west_ic_antennas.cpp
        west_barometry.cpp
        west_polaro_interf.cpp
        west_magnetics.cpp
        west_tf.cpp
)

target_include_directories(west_access PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBTS_INCLUDE_DIRS}
    #${LIBXML2_INCLUDE_DIR}
    #${MDSPLUS_INCLUDES}
)

target_link_libraries(west_access PUBLIC
    #${LIBXML2_LIBRARIES}
    #${MDSPLUS_LIBRARIES}
    ${LIBTS_LIBRARIES}
    ${LIBTSZSTD_LIBRARIES}
    #${UDA_CLIENT_LIBRARIES}
    #${UDA_PLUGINS_LIBRARIES}
    ${HDF5_LIBRARIES}
    m
)

set_target_properties(west_access PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ===================================================================
# 2. Exécutable de test standalone
# ===================================================================
option(BUILD_WEST_TEST "Construire l'exécutable de test west_test" OFF)

if(BUILD_WEST_TEST)

    add_executable(west_test
        # Tous les fichiers habituels
        tsparse.cpp
        ts_rqparm.cpp
      #  west_plugin.cpp
        west_xml.cpp
        west_dynamic_data.cpp
        west_utilities.cpp
        west_dyn_data_utilities.cpp
        west_pf_active.cpp
        west_pf_passive.cpp
        west_static_data_utilities.cpp
        west_soft_x_rays.cpp
        west_summary.cpp
        west_lh_antennas.cpp          # ← contient le main(), il sera utilisé ici
        west_ic_antennas.cpp
        west_barometry.cpp
        west_polaro_interf.cpp
        west_magnetics.cpp
        west_tf.cpp
        ../../tests/export_tests_data.cpp      # ← fichier spécifique au test standalone
    )

    target_include_directories(west_test PRIVATE
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${LIBTS_INCLUDE_DIRS}
            #${LIBXML2_INCLUDE_DIR}
            #${MDSPLUS_INCLUDES}
    )


    # L ink avec la lib client UDA (indispensable pour findStringValue, etc.)
    target_link_libraries(west_test
        PRIVATE
            #${LIBXML2_LIBRARIES}
            #${MDSPLUS_LIBRARIES}
            ${LIBTS_LIBRARIES}
            ${LIBTSZSTD_LIBRARIES}
            #${UDA_CLIENT_LIBRARIES}                  # ou ${UDA_CLIENT_LIBRARIES} si l'import target n'existe pas
            #${UDA_PLUGINS_LIBRARIES}
            ${HDF5_LIBRARIES} 
            m
    )

    # Très important : on désactive la partie "plugin" pour que le code se comporte en standalone
    target_compile_definitions(west_test PRIVATE WEST_STANDALONE_TEST)

endif()