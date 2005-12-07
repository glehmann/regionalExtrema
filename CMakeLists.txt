#Change PROJECT_NAME to the name of your project
PROJECT(regionalExtrema)

# set the name of the input image used to run the test
SET(INPUT_IMAGE "")

#include some macros from another file...
INCLUDE(IJMacros.txt)

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE(Dart)

#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
SET(Required_Packages
  ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

#Set any libraries that your project depends on.
#examples: ITKCommon, VTKRendering, etc
SET(Libraries
  ITKCommon
  ITKBasicFilters
  ITKIO
)

#the following block of code is an example of how to build an executable in
#cmake.  Unmodified, it will add an executable called "MyExe" to the project.
#MyExe will be built using the files MyClass.h and MyClass.cxx, and it will
#be linked to all the libraries you specified above. 
#You can build more than one executable per project
SET(CurrentExe "vrmin")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "vrmax")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "rmin")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "rmin3D")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "rmax")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "rmax3D")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "perf3D")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "frmin")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "frmax")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "exceptions")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

#the following line is an example of how to add a test to your project.
#Testname is the title for this particular test.  ExecutableToRun is the
#program which will be running this test.  It can either be a part of this
#project or an external executable.  After that list any args that are needed
#for this test.  Include as many tests as you like.  If your project doesn't have
#any tests you can comment out or delete the following line.
# ADD_TEST(Testname ExecutableToRun arg1 arg2 arg3)

ADD_TEST(VRMinF vrmin 1 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-vrminF.png cthead1-vrminF-ref.png)
ADD_TEST(VRMinFCompare ImageCompare cthead1-vrminF.png cthead1-vrminF-ref.png)

ADD_TEST(VRMinf vrmin 0 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-vrminf.png cthead1-vrminf-ref.png)
ADD_TEST(VRMinfCompare ImageCompare cthead1-vrminf.png cthead1-vrminf-ref.png)


ADD_TEST(VRMaxF vrmax 1 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-vrmaxF.png cthead1-vrmaxF-ref.png)
ADD_TEST(VRMaxFCompare ImageCompare cthead1-vrmaxF.png cthead1-vrmaxF-ref.png)

ADD_TEST(VRMaxf vrmax 0 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-vrmaxf.png cthead1-vrmaxf-ref.png)
ADD_TEST(VRMaxfCompare ImageCompare cthead1-vrmaxf.png cthead1-vrmaxf-ref.png)


ADD_TEST(RMinF rmin 1 1 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-rminF.png cthead1-rminF-ref.png)
ADD_TEST(RMinFCompare ImageCompare cthead1-rminF.png cthead1-rminF-ref.png)

ADD_TEST(RMinf rmin 0 1 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-rminf.png cthead1-rminf-ref.png)
ADD_TEST(RMinfCompare ImageCompare cthead1-rminf.png cthead1-rminf-ref.png)

ADD_TEST(RMaxF rmax 1 1 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-rmaxF.png cthead1-rmaxF-ref.png)
ADD_TEST(RMaxFCompare ImageCompare cthead1-rmaxF.png cthead1-rmaxF-ref.png)

ADD_TEST(RMaxf rmax 0 1 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-rmaxf.png cthead1-rmaxf-ref.png)
ADD_TEST(RMaxfCompare ImageCompare cthead1-rmaxf.png cthead1-rmaxf-ref.png)


ADD_TEST(RMaxBlackM rmax 0 1 ${CMAKE_SOURCE_DIR}/black.png black-rmaxfM.png dummy.png)
ADD_TEST(RMaxBlackMCompare ImageCompare black-rmaxfM.png ${CMAKE_SOURCE_DIR}/white.png)

ADD_TEST(RMaxBlackm rmax 0 0 ${CMAKE_SOURCE_DIR}/black.png black-rmaxfm.png dummy.png)
ADD_TEST(RMaxBlackmCompare ImageCompare black-rmaxfm.png ${CMAKE_SOURCE_DIR}/black.png)

ADD_TEST(RMaxWhiteM rmax 0 1 ${CMAKE_SOURCE_DIR}/white.png white-rmaxf.png dummy.png)
ADD_TEST(RMaxWhiteMCompare ImageCompare white-rmaxf.png ${CMAKE_SOURCE_DIR}/white.png)

ADD_TEST(RMaxWhitem rmax 0 0 ${CMAKE_SOURCE_DIR}/white.png white-rmaxf.png dummy.png)
ADD_TEST(RMaxWhitemCompare ImageCompare white-rmaxf.png ${CMAKE_SOURCE_DIR}/black.png)


ADD_TEST(RMinBlackM rmin 0 1 ${CMAKE_SOURCE_DIR}/black.png black-rminfM.png dummy.png)
ADD_TEST(RMinBlackMCompare ImageCompare black-rminfM.png ${CMAKE_SOURCE_DIR}/white.png)

ADD_TEST(RMinBlackm rmin 0 0 ${CMAKE_SOURCE_DIR}/black.png black-rminfm.png dummy.png)
ADD_TEST(RMinBlackmCompare ImageCompare black-rminfm.png ${CMAKE_SOURCE_DIR}/black.png)

ADD_TEST(RMinWhiteM rmin 0 1 ${CMAKE_SOURCE_DIR}/white.png white-rminf.png dummy.png)
ADD_TEST(RMinWhiteMCompare ImageCompare white-rminf.png ${CMAKE_SOURCE_DIR}/white.png)

ADD_TEST(RMinWhitem rmin 0 0 ${CMAKE_SOURCE_DIR}/white.png white-rminf.png dummy.png)
ADD_TEST(RMinWhitemCompare ImageCompare white-rminf.png ${CMAKE_SOURCE_DIR}/black.png)


# ADD_TEST(RMin3DF rmin3D 1 ${CMAKE_SOURCE_DIR}/ESCells.img ESCells-rminF.tif ESCells-rminF-ref.tif)
# ADD_TEST(RMin3DFCompare ImageCompare ESCells-rminF.tif ESCells-rminF-ref.tif)

ADD_TEST(RMin3Df rmin3D 0 ${CMAKE_SOURCE_DIR}/ESCells.img ESCells-rminf.tif ESCells-rminf-ref.tif)
ADD_TEST(RMin3DfCompare ImageCompare ESCells-rminf.tif ESCells-rminf-ref.tif)

# ADD_TEST(RMax3DF rmax3D 1 ${CMAKE_SOURCE_DIR}/ESCells.img ESCells-rmaxF.tif ESCells-rmaxF-ref.tif)
# ADD_TEST(RMax3DFCompare ImageCompare ESCells-rmaxF.tif ESCells-rmaxF-ref.tif)

ADD_TEST(RMax3Df rmax3D 0 ${CMAKE_SOURCE_DIR}/ESCells.img ESCells-rmaxf.tif ESCells-rmaxf-ref.tif)
ADD_TEST(RMax3DfCompare ImageCompare ESCells-rmaxf.tif ESCells-rmaxf-ref.tif)


ADD_TEST(FloatRMinF frmin 1 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-rminF.png cthead1-rminF-float.png)
ADD_TEST(FloatRMinFCompare ImageCompare cthead1-rminF.png cthead1-rminF-float.png)

ADD_TEST(FloatRMinf frmin 0 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-rminf.png cthead1-rminf-float.png)
ADD_TEST(FloatRMinfCompare ImageCompare cthead1-rminf.png cthead1-rminf-float.png)

ADD_TEST(FloatRMaxF frmax 1 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-rmaxF.png cthead1-rmaxF-float.png)
ADD_TEST(FloatRMaxFCompare ImageCompare cthead1-rmaxF.png cthead1-rmaxF-float.png)

ADD_TEST(FloatRMaxf frmax 0 ${CMAKE_SOURCE_DIR}/cthead1.png cthead1-rmaxf.png cthead1-rmaxf-float.png)
ADD_TEST(FloatRMaxfCompare ImageCompare cthead1-rmaxf.png cthead1-rmaxf-float.png)


ADD_TEST(Exceptions exceptions)
