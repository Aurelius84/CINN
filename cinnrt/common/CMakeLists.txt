core_gather_headers()
set(core_includes "${core_includes};cinnrt/common/dtype.def" CACHE INTERNAL "")

core_gather_srcs(SRCS
    dtype.cc
    global.cc
    )
