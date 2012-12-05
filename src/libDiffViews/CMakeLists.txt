
PROJECT( libDiffViews )

QT_PREPARE( Core Gui Widgets )

INCLUDE_DIRECTORIES(
    ${DIFFVIEWS_SOURCE_DIR}
    ${libDiffViews_SOURCE_DIR}
    ${libDiffViews_BINARY_DIR}
)

SET( SRC_FILES

    Model/Hunk.cpp
    Model/HunkPart.cpp
    Model/DiffLines.cpp
    Model/TextFilePatch.cpp
    Model/BinaryFilePatch.cpp
    Model/FilePatch.cpp
    Model/Patch.cpp

    Views/Raw/RawView.cpp
    Views/Raw/RawHighlighter.cpp
)

SET( PUB_HDR_FILES

    DiffViewsApi.hpp

    Model/Hunk.hpp
    Model/HunkPart.hpp
    Model/DiffLines.hpp
    Model/FilePatch.hpp
    Model/BinaryFilePatch.hpp
    Model/TextFilePatch.hpp
    Model/Patch.hpp

    Views/Raw/RawView.hpp
)

SET( PRIV_HDR_FILES

    Views/Raw/RawHighlighter.hpp
)


SET( HIC_FILES

)

SET( UI_FILES
)

SET( HDR_FILES ${PRIV_HDR_FILES} ${PUB_HDR_FILES} )

QT_MOC( MOC_FILES ${HDR_FILES} )
HIC( HIC_FILES ${HID_FILES} )

ADD_QT_LIBRARY(
    DiffViews SHARED

    ${SRC_FILES}
    ${HDR_FILES}
    ${MOC_FILES}
    ${HIC_FILES}
)
