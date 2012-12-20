
PROJECT( libDiffViews )

SET( libDiffViews_includes
    ${CMAKE_CURRENT_LIST_DIR}/src
    CACHE INTERNAL "libDiffViews include directories"
)

ADD_SUBDIRECTORY( src )
