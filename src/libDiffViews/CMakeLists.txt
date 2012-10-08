
PROJECT( libDiffViews )

QT_PREPARE( Core Gui Widgets )

SET( SRC_FILES

    Model/Hunk.cpp
    Model/HunkPart.cpp
    Model/DiffLines.cpp
    Model/TextFilePatch.cpp
    Model/BinaryFilePatch.cpp
    Model/FilePatch.cpp
    Model/Patch.cpp
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
)

SET( PRIV_HDR_FILES
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
