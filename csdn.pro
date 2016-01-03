#-------------------------------------------------
#
# Project created by QtCreator 2016-01-01T11:47:57
#
#-------------------------------------------------

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = csdn
TEMPLATE = app

CONFIG += c++0x
!msvc{
    QMAKE_CXXFLAGS += " -std=c++0x "
}

SOURCES += main.cpp\
        mainwindow.cpp \
    cdownload.cpp \
    cnumber.cpp

HEADERS  += mainwindow.h \
    cdownload.h \
    cnumber.h

FORMS    += mainwindow.ui

DISTFILES += \
    files.txt
 equals(QMAKE_HOST.os, Windows){
    isEmpty(QMAKE_SH){
        FILE = $$system_path($$PWD/files.txt)
    } else {
        FILE = $$PWD/files.txt
    }
}
copyfile.commands = \
    $${QMAKE_COPY} $$FILE $$OUT_PWD
copyfile.CONFIG += directory no_link no_clean no_check_exist
copyfile.target = copyfile
QMAKE_EXTRA_TARGETS += copyfile
POST_TARGETDEPS += copyfile

#####以下配置 pkg-config  
mingw{
    equals(QMAKE_HOST.os, Windows){
        PKG_CONFIG_PATH="$${THIRD_LIBRARY_PATH}/lib/pkgconfig;$${TARGET_PATH}/pkgconfig;$$(PKG_CONFIG_PATH)"
    } else {
        PKG_CONFIG_PATH="$${THIRD_LIBRARY_PATH}/lib/pkgconfig:$${TARGET_PATH}/pkgconfig"
        PKG_CONFIG_SYSROOT_DIR=$${THIRD_LIBRARY_PATH}
    }
} else : msvc {
    PKG_CONFIG_SYSROOT_DIR=$${THIRD_LIBRARY_PATH}
    PKG_CONFIG_LIBDIR="$${THIRD_LIBRARY_PATH}/lib/pkgconfig;$${TARGET_PATH}/pkgconfig"
} else : android {
    PKG_CONFIG_SYSROOT_DIR=$${THIRD_LIBRARY_PATH} 
    equals(QMAKE_HOST.os, Windows){
        PKG_CONFIG_LIBDIR=$${THIRD_LIBRARY_PATH}/lib/pkgconfig;$${THIRD_LIBRARY_PATH}/libs/$${ANDROID_TARGET_ARCH}/pkgconfig;$${TARGET_PATH}/pkgconfig
    } else {
        PKG_CONFIG_LIBDIR=$${THIRD_LIBRARY_PATH}/lib/pkgconfig:$${THIRD_LIBRARY_PATH}/libs/$${ANDROID_TARGET_ARCH}/pkgconfig:$${TARGET_PATH}/pkgconfig
    }
} else {
    PKG_CONFIG_PATH="$${THIRD_LIBRARY_PATH}/lib/pkgconfig:$${TARGET_PATH}/pkgconfig:$$(PKG_CONFIG_PATH)"
}

isEmpty(PKG_CONFIG) : PKG_CONFIG=$$(PKG_CONFIG)

isEmpty(PKG_CONFIG) {
    PKG_CONFIG = pkg-config 
}

CONFIG(static, static|shared) {
    PKG_CONFIG *= --static
}

sysroot.name = PKG_CONFIG_SYSROOT_DIR
sysroot.value = $$PKG_CONFIG_SYSROOT_DIR
libdir.name = PKG_CONFIG_LIBDIR
libdir.value = $$PKG_CONFIG_LIBDIR
path.name = PKG_CONFIG_PATH
path.value = $$PKG_CONFIG_PATH
qtAddToolEnv(PKG_CONFIG, sysroot libdir path, SYS)

equals(QMAKE_HOST.os, Windows): \
    PKG_CONFIG += 2> NUL
else: \
    PKG_CONFIG += 2> /dev/null

defineReplace(myPkgConfigExecutable) {
    return($$PKG_CONFIG)
}

defineTest(myPackagesExist) {
    pkg_config = $$myPkgConfigExecutable()

    for(package, ARGS) {
        !system($$pkg_config --exists $$package) {
            !msvc : message("Warring: package $$package is not exist.")
            return(false)
        }
    }

    return(true)
}


    myPackagesExist(libcurl) {
        DEFINES *= RABBITIM_USE_LIBCURL
        MYPKGCONFIG *= libcurl
    } else : msvc {
        DEFINES *= RABBITIM_USE_LIBCURL
        LIBS += -llibcurl
    }



    myPackagesExist(openssl) {
        DEFINES *= RABBITIM_USE_OPENSSL
        MYPKGCONFIG *= openssl
    } else : msvc {
        DEFINES *= RABBITIM_USE_OPENSSL
        LIBS += -llibeay32 -lssleay32 
    }


#用 pkg-config 机制增加第三方依赖库到 LIBS 和 QMAKE_CXXFLAGS  
PKG_CONFIG = $$myPkgConfigExecutable()
message("PKG_CONFIG:$$PKG_CONFIG")
# qmake supports no empty list elements, so the outer loop is a bit arcane
pkgsfx =
for(ever) {
    pkgvar = MYPKGCONFIG$$pkgsfx
    libvar = LIBS$$pkgsfx
    for(PKGCONFIG_LIB, $$list($$unique($$pkgvar))) {
        # don't proceed if the .pro asks for a package we don't have!
        !myPackagesExist($$PKGCONFIG_LIB): error("$$PKGCONFIG_LIB development package not found")

        PKGCONFIG_CFLAGS = $$system($$PKG_CONFIG --cflags $$PKGCONFIG_LIB)

        PKGCONFIG_INCLUDEPATH = $$find(PKGCONFIG_CFLAGS, ^-I.*)
        PKGCONFIG_INCLUDEPATH ~= s/^-I(.*)/\\1/g

        PKGCONFIG_DEFINES = $$find(PKGCONFIG_CFLAGS, ^-D.*)
        PKGCONFIG_DEFINES ~= s/^-D(.*)/\\1/g

        PKGCONFIG_CFLAGS ~= s/^-[ID].*//g

        INCLUDEPATH *= $$PKGCONFIG_INCLUDEPATH
        DEFINES *= $$PKGCONFIG_DEFINES

        QMAKE_CXXFLAGS += $$PKGCONFIG_CFLAGS
        QMAKE_CFLAGS += $$PKGCONFIG_CFLAGS
        $$libvar += $$system($$PKG_CONFIG --libs $$PKGCONFIG_LIB)
    }
    !isEmpty(pkgsfx): break()
    pkgsfx = _PRIVATE
}
