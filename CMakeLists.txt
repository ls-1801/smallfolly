cmake_minimum_required(VERSION 3.22)
project(smallfolly)

set(CMAKE_CXX_STANDARD 20)

# Currently there is a dependency on BOOST-MPL
find_package(Boost REQUIRED)

add_library(smallfolly
        folly/folly/SharedMutex.cpp
        folly/folly/ScopeGuard.cpp
        folly/folly/concurrency/CacheLocality.cpp
        folly/folly/detail/Futex.cpp
        folly/folly/detail/ThreadLocalDetail.cpp
        folly/folly/detail/StaticSingletonManager.cpp
        folly/folly/detail/AtFork.cpp
        folly/folly/system/ThreadId.cpp
        folly/folly/synchronization/ParkingLot.cpp
        folly/folly/synchronization/SanitizeThread.cpp

        # Required for MPMC
        folly/folly/synchronization/AsymmetricMemoryBarrier.cpp
        folly/folly/synchronization/Hazptr.cpp
        folly/folly/detail/MemoryIdler.cpp
        folly/folly/detail/UniqueInstance.cpp
        folly/folly/executors/QueuedImmediateExecutor.cpp
        folly/folly/Executor.cpp
        folly/folly/portability/SysMembarrier.cpp
        folly/folly/memory/MallctlHelper.cpp
)

target_compile_features(smallfolly PRIVATE cxx_std_20)

target_include_directories(smallfolly PUBLIC
        ${Boost_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/folly>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/config>)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Config
configure_package_config_file(cmake/config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake # cmake-build-debug/
        INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME} NO_SET_AND_CHECK_MACRO) # share/

# Version
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        VERSION 0.0.1
        COMPATIBILITY SameMajorVersion)

# Install Config & Version
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake # cmake-build-debug/
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake # cmake_build-debug/
        DESTINATION
        ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}) # share/

# Create export set to enable import in other CMake Projects
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets # create export set
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib/
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib/
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include/
)
# Install Export Set
install(EXPORT ${PROJECT_NAME}-targets
        NAMESPACE smallfolly::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})


set(header_path "folly/folly")
set(header
        ${header_path}/SharedMutex.h
        ${header_path}/Synchronized.h
        ${header_path}/MPMCQueue.h
        ${header_path}/Function.h
        ${header_path}/Traits.h
        ${header_path}/CppAttributes.h
        ${header_path}/Portability.h
        ${header_path}/SingletonThreadLocal.h
        ${header_path}/CPortability.h
        ${header_path}/Indestructible.h
        ${header_path}/Preprocessor.h
        ${header_path}/Utility.h
        ${header_path}/Likely.h
        ${header_path}/Hash.h
        ${header_path}/Memory.h
        ${header_path}/ConstexprMath.h
        ${header_path}/Unit.h
        ${header_path}/Optional.h
        ${header_path}/Executor.h
        ${header_path}/Range.h
        ${header_path}/CpuId.h
        ${header_path}/ThreadLocal.h
        ${header_path}/ScopeGuard.h
        ${header_path}/Exception.h
        ${header_path}/Conv.h
        ${header_path}/FBString.h
)


set(header_path "folly/folly/portability")
set(portability
        ${header_path}/Config.h
        ${header_path}/Builtins.h
        ${header_path}/Malloc.h
        ${header_path}/Asm.h
        ${header_path}/Unistd.h
        ${header_path}/SysResource.h
        ${header_path}/Constexpr.h
        ${header_path}/PThread.h
        ${header_path}/SysTypes.h
)


set(header_path "folly/folly/memory")
set(memory
        ${header_path}/Malloc.h
)

set(header_path "folly/folly/memory/detail")
set(memory_detail
        ${header_path}/MallocImpl.h
)

set(header_path "folly/folly/concurrency")
set(concurrency
        ${header_path}/CacheLocality.h
        ${header_path}/UnboundedQueue.h
        ${header_path}/DynamicBoundedQueue.h
)

set(header_path "folly/folly/functional")
set(functional
        ${header_path}/Invoke.h
        ${header_path}/ApplyTuple.h
)

set(header_path "folly/folly/lang")
set(lang
        ${header_path}/CustomizationPoint.h
        ${header_path}/StaticConst.h
        ${header_path}/Align.h
        ${header_path}/Exception.h
        ${header_path}/SafeAssert.h
        ${header_path}/CArray.h
        ${header_path}/CString.h
        ${header_path}/TypeInfo.h
        ${header_path}/Thunk.h
        ${header_path}/Bits.h
        ${header_path}/Assume.h
        ${header_path}/Assume-inl.h
        ${header_path}/CheckedMath.h
        ${header_path}/UncaughtExceptions.h
)

set(header_path "folly/folly/detail")
set(detail
        ${header_path}/StaticSingletonManager.h
        ${header_path}/Singleton.h
        ${header_path}/TurnSequencer.h
        ${header_path}/Futex.h
        ${header_path}/MemoryIdler.h
        ${header_path}/Iterators.h
        ${header_path}/UniqueInstance.h
        ${header_path}/ThreadLocalDetail.h
        ${header_path}/RangeCommon.h
        ${header_path}/AtFork.h
        ${header_path}/RangeSse42.h
        ${header_path}/Futex-inl.h
)


set(header_path "folly/folly/synchronization")
set(synchronization
        ${header_path}/RelaxedAtomic.h
        ${header_path}/ParkingLot.h
        ${header_path}/Lock.h
        ${header_path}/AtomicStruct.h
        ${header_path}/Hazptr.h
        ${header_path}/Hazptr-fwd.h
        ${header_path}/HazptrDomain.h
        ${header_path}/HazptrObj.h
        ${header_path}/HazptrObjLinked.h
        ${header_path}/HazptrHolder.h
        ${header_path}/HazptrRec.h
        ${header_path}/HazptrThrLocal.h
        ${header_path}/SanitizeThread.h
        ${header_path}/MicroSpinLock.h
        ${header_path}/SaturatingSemaphore.h
        ${header_path}/AsymmetricMemoryBarrier.h
        ${header_path}/WaitOptions.h
        ${header_path}/AtomicUtil.h
        ${header_path}/AtomicUtil-inl.h
)

set(header_path "folly/folly/synchronization/detail")
set(synchronization_detail
        ${header_path}/Sleeper.h
        ${header_path}/AtomicUtils.h
        ${header_path}/HazptrUtils.h
        ${header_path}/Spin.h
)

set(header_path "folly/folly/hash")
set(hash
        ${header_path}/Hash.h
        ${header_path}/SpookyHashV1.h
        ${header_path}/SpookyHashV2.h
)

set(header_path "folly/folly/executors")
set(executors
        ${header_path}/QueuedImmediateExecutor.h
        ${header_path}/InlineExecutor.h
)
set(header_path "folly/folly/container")
set(container
        ${header_path}/Foreach.h
        ${header_path}/Foreach-inl.h
        ${header_path}/Access.h
)
set(header_path "folly/folly/system")
set(system
        ${header_path}/ThreadId.h
)
set(header_path "folly/folly/chrono")
set(chrono
        ${header_path}/Hardware.h
)

# Install Headers
set(include_dest ${CMAKE_INSTALL_INCLUDEDIR}/folly)
# in src/CMakeLists.txt
install(FILES ${header} DESTINATION "${include_dest}")
install(FILES ${hash} DESTINATION "${include_dest}/hash")
install(FILES ${portability} DESTINATION "${include_dest}/portability")
install(FILES ${concurrency} DESTINATION "${include_dest}/concurrency")
install(FILES ${functional} DESTINATION "${include_dest}/functional")
install(FILES ${lang} DESTINATION "${include_dest}/lang")
install(FILES ${memory} DESTINATION "${include_dest}/memory")
install(FILES ${detail} DESTINATION "${include_dest}/detail")
install(FILES ${synchronization} DESTINATION "${include_dest}/synchronization")
install(FILES ${synchronization_detail} DESTINATION "${include_dest}/synchronization/detail")
install(FILES ${executors} DESTINATION "${include_dest}/executors")
install(FILES ${container} DESTINATION "${include_dest}/container")
install(FILES ${system} DESTINATION "${include_dest}/system")
install(FILES ${chrono} DESTINATION "${include_dest}/chrono")
install(FILES ${memory_detail} DESTINATION "${include_dest}/memory/detail")
install(FILES "config/folly/folly-config.h" DESTINATION "${include_dest}")
install(FILES "folly/folly/stub/logging.h" DESTINATION "${include_dest}/stub")
