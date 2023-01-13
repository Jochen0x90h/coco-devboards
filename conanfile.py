import os, shutil
from conans import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake


class Project(ConanFile):
    name = "coco-devboards"
    description = "Development Boards for CoCo"
    url = "https://github.com/Jochen0x90h/coco-devboards"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "platform": "ANY"}
    default_options = {
        "platform": None}
    generators = "CMakeDeps"
    exports_sources = "conanfile.py", "CMakeLists.txt", "coco/*"
    no_copy_source = True
    requires = "coco/0.3.0"


    # check if we are cross compiling
    def cross(self):
        if hasattr(self, "settings_build"):
           return self.settings.os != self.settings_build.os
        return False

    def configure(self):
        # pass platform option to dependencies
        self.options["coco"].platform = self.options.platform

    keep_imports = True
    def imports(self):
        # copy dependent libraries into the build folder
        self.copy("*", src="@bindirs", dst="bin")
        self.copy("*", src="@libdirs", dst="lib")

    def generate(self):
        # generate "conan_toolchain.cmake"
        toolchain = CMakeToolchain(self)
        toolchain.variables["PLATFORM"] = self.options.platform

        # cross compile to a platform if platform option is set
        # https://github.com/conan-io/conan/blob/develop/conan/tools/cmake/toolchain/blocks.py
        if self.cross():
            toolchain.blocks["generic_system"].values["cmake_system_name"] = "Generic"
            toolchain.blocks["generic_system"].values["cmake_system_processor"] = self.settings.arch
            toolchain.variables["CMAKE_TRY_COMPILE_TARGET_TYPE"] = "STATIC_LIBRARY"
            toolchain.variables["CMAKE_FIND_ROOT_PATH_MODE_PROGRAM"] = "NEVER"
            toolchain.variables["CMAKE_FIND_ROOT_PATH_MODE_LIBRARY"] = "ONLY"
            toolchain.variables["CMAKE_FIND_ROOT_PATH_MODE_INCLUDE"] = "ONLY"
            toolchain.variables["GENERATE_HEX"] = self.env.get("GENERATE_HEX", None)

        # bake CC and CXX from profile into toolchain
        cc = self.env.get("CC", None)
        if cc != None:
            toolchain.variables["CMAKE_C_COMPILER "] = cc
        cxx = self.env.get("CXX", None)
        if cxx != None:
            toolchain.variables["CMAKE_CXX_COMPILER "] = cxx

        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

        # run unit tests if CONAN_RUN_TESTS environment variable is set to 1
        #if os.getenv("CONAN_RUN_TESTS") == "1" and self.settings.os == self.settings_build.os:
        #    cmake.test()

    def package(self):
        # install from build directory into package directory
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        if self.options.platform == "native":
            self.cpp_info.components["native"].libs = ["coco-board-native"]
            self.cpp_info.components["native"].includedirs = ["include/coco/board/native"]
            self.cpp_info.components["native"].requires = ["coco::coco"]
        elif self.options.platform == "nrf52840":
            self.cpp_info.components["nrf52dongle"].libs = ["coco-board-nrf52dongle"]
            self.cpp_info.components["nrf52dongle"].includedirs = ["include/coco/board/nrf52dongle"]
            self.cpp_info.components["nrf52dongle"].requires = ["coco::coco"]
        elif self.options.platform == "stm32f051x8":
            self.cpp_info.components["stm32f051discovery"].libs = ["coco-board-stm32f051discovery"]
            self.cpp_info.components["stm32f051discovery"].includedirs = ["include/coco/board/stm32f051discovery"]
            self.cpp_info.components["stm32f051discovery"].requires = ["coco::coco"]
        else:
            self.cpp_info.includedirs = []
