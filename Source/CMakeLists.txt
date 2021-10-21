set(CPP_COMMON_TARGET CPPCommon)

set(BASE_SOURCE_CODE
        base/Configuration.h
        base/BaseDefs.h
        base/win/DllLoader.h base/ClearAction.h base/process/ProcessUtils.cpp base/process/ProcessUtils.h base/process/ProcessDefs.h)

set(UI_SOURCE_CODE
        ui/display/DisplayInfo.h
        ui/display/DisplayInfo.cpp
        ui/Rect.h
        )

add_library(${CPP_COMMON_TARGET} ${BASE_SOURCE_CODE} ${UI_SOURCE_CODE})