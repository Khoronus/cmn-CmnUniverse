#######################################################################
macro(CREATE_EXAMPLE NAME SOURCES LIBRARIES)
	set(srcs)
	set(flsrcs)
	foreach(src ${SOURCES})
		if("${src}" MATCHES ".fl$")
         list(APPEND flsrcs ${src})
		else()
			list(APPEND srcs ${src})
		endif("${src}" MATCHES ".fl$")
	endforeach(src)

        ######################################################################

	add_executable(${NAME} ${srcs})
	include_directories("${PROJ_COMMONLIBRARY_PATH}/module" "${PROJ_COMMONMATH_PATH}/module" ${PROJ_OPENCV_INCLUDES} ${Boost_INCLUDE_DIR})
	target_link_libraries(${NAME} ${LIBRARIES} ${PROJ_LIBRARIES_COMMON} ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})

	# ------------------------
	# DEFINITIONS
	# ------------------------

	add_definitions(-DUNICODE -D_UNICODE)

    install(TARGETS ${NAME}
      DESTINATION ${PREFIX_DOC}/examples
    )

    IF(MSVC)
	ADD_DEFINITIONS(/arch:SSE2)
	ADD_DEFINITIONS(-D__SSE2__)
    ENDIF(MSVC)

endmacro(CREATE_EXAMPLE NAME SOURCES LIBRARIES)

#######################################################################
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  "${CMAKE_SOURCE_DIR}/module"
  )

#######################################################################
if (BUILD_EXAMPLES)
CREATE_EXAMPLE(sample_codify_codifydata sample_codify_codifydata "codify")
CREATE_EXAMPLE(sample_codify_packunpackimages sample_codify_packunpackimages "codify")
CREATE_EXAMPLE(sample_cmnipcontainer_indextiming sample_cmnipcontainer_indextiming "cmnipcontainer")
CREATE_EXAMPLE(sample_cmnipcontainer_imagepointsassociation sample_cmnipcontainer_imagepointsassociation "cmnipcontainer")
CREATE_EXAMPLE(sample_cmnipcontainer_connectedpoints sample_cmnipcontainer_connectedpoints "cmnipcontainer")
CREATE_EXAMPLE(sample_draw_coloredrange sample_draw_coloredrange "draw")
CREATE_EXAMPLE(sample_draw_chartradar sample_draw_chartradar "draw")
CREATE_EXAMPLE(sample_draw_map2d sample_draw_map2d "draw")
CREATE_EXAMPLE(sample_draw_pairs sample_draw_pairs "draw;transform")
CREATE_EXAMPLE(sample_draw_opticalflowdrawer sample_draw_opticalflowdrawer "draw")
CREATE_EXAMPLE(sample_draw_histogram sample_draw_histogram "draw")
CREATE_EXAMPLE(sample_draw_hog2image sample_draw_hog2image "draw")
CREATE_EXAMPLE(sample_feature_lbp sample_feature_lbp "feature")
CREATE_EXAMPLE(sample_feature_featurematching sample_feature_featurematching "feature;draw;transform")
CREATE_EXAMPLE(sample_feature_pairpointsmanagement sample_feature_pairpointsmanagement "feature;CmnLib::CmnLib;CmnLib::string")
CREATE_EXAMPLE(sample_feature_densetemplatematching sample_feature_densetemplatematching "feature;draw;filter")
CREATE_EXAMPLE(sample_filter_filterlinear sample_filter_filterlinear "filter")
CREATE_EXAMPLE(sample_graph_treesearchpatrol2d sample_graph_treesearchpatrol2d "graph")
CREATE_EXAMPLE(sample_group_imagesorganized sample_group_imagesorganized "group;transform")
CREATE_EXAMPLE(sample_group_imagescombined sample_group_imagescombined "group;transform")
CREATE_EXAMPLE(sample_group_imagessplit sample_group_imagessplit "group;CmnLib::CmnLib;CmnLib::container")
CREATE_EXAMPLE(sample_group_roisdetection sample_group_roisdetection "group;CmnMath::CmnMath")
CREATE_EXAMPLE(sample_group_marker sample_group_marker "group")
CREATE_EXAMPLE(sample_histogram_equalizeimage sample_histogram_equalizeimage "histogram")
CREATE_EXAMPLE(sample_photo_focus sample_photo_focus "photo")
CREATE_EXAMPLE(sample_measure_information sample_measure_information "measure")
CREATE_EXAMPLE(sample_measure_similarity sample_measure_similarity "measure")
CREATE_EXAMPLE(sample_measure_templatematching sample_measure_templatematching "measure")
CREATE_EXAMPLE(sample_measure_imagematching sample_measure_imagematching "measure")
CREATE_EXAMPLE(sample_measure_phasecorrelation sample_measure_phasecorrelation "measure")
CREATE_EXAMPLE(sample_measure_moment sample_measure_moment "measure")
CREATE_EXAMPLE(sample_transform_colornormalization sample_transform_colornormalization "transform")
CREATE_EXAMPLE(sample_transform_transform sample_transform_transform "transform")
CREATE_EXAMPLE(sample_transform_color sample_transform_color "transform")
CREATE_EXAMPLE(sample_transform_fisheye2perspective sample_transform_fisheye2perspective "transform")
CREATE_EXAMPLE(sample_transform_fisheye2HammerAitoff sample_transform_fisheye2HammerAitoff "transform")
CREATE_EXAMPLE(sample_transform_fisheye2polar sample_transform_fisheye2polar "transform")
CREATE_EXAMPLE(sample_signal_noise sample_signal_noise "signal")
CREATE_EXAMPLE(test_image_deconvolution test_image_deconvolution "")
CREATE_EXAMPLE(test_opencv_homographyadjustment test_opencv_homographyadjustment "")
CREATE_EXAMPLE(test_opencv_kmean test_opencv_kmean "")
CREATE_EXAMPLE(test_opencv_pca test_opencv_pca "")
CREATE_EXAMPLE(test_opencv_wavelet test_opencv_wavelet "")
CREATE_EXAMPLE(test_path2d_gravitypoint test_path2d_gravitypoint "graph")
CREATE_EXAMPLE(test_opencv_camshift test_opencv_camshift "")
CREATE_EXAMPLE(test_opencv_opticalflow test_opencv_opticalflow "draw")
CREATE_EXAMPLE(test_opencv_kalman test_opencv_kalman "draw")
CREATE_EXAMPLE(test_opencv_lk test_opencv_lk "draw")
CREATE_EXAMPLE(test_opencv_quadtrees test_opencv_quadtrees "")
CREATE_EXAMPLE(test_opencv_segmentem test_opencv_segmentem "")
CREATE_EXAMPLE(test_opencv_gmm test_opencv_gmm "")
CREATE_EXAMPLE(test_opencv_poissonblending test_opencv_poissonblending "")
CREATE_EXAMPLE(test_opencv_filter2d test_opencv_filter2d "")
CREATE_EXAMPLE(devel_measure_templateregionsidentifier devel_measure_templateregionsidentifier "measure")
endif(BUILD_EXAMPLES)

#######################################################################
if (USE_STATIC)
  set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
endif (USE_STATIC)