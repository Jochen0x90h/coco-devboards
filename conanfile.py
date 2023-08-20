from conans import ConanFile
from conan.tools.cmake import CMake


class Project(ConanFile):
    name = "coco-devboards"
    description = "Development Boards for CoCo"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "platform": [None, "ANY"]}
    default_options = {
        "platform": None}
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "conanfile.py", "CMakeLists.txt", "coco/*"
    no_copy_source = True
    requires = "coco/0.6.0"
    tool_requires = "coco-toolchain/0.2.0"


    # check if we are cross compiling
    def cross(self):
        if hasattr(self, "settings_build"):
            return self.settings.os != self.settings_build.os
        return False

    def configure(self):
        # pass platform option to dependencies
        self.options["coco"].platform = self.options.platform
        self.options["coco-toolchain"].platform = self.options.platform

    keep_imports = True
    def imports(self):
        # copy dependent libraries into the build folder
        self.copy("*", src="@bindirs", dst="bin")
        self.copy("*", src="@libdirs", dst="lib")

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
        platform = self.options.platform #self.user_info_build["coco-toolchain"].platform
        if platform == "native":
            self.cpp_info.components["native"].libs = ["coco-board-native"]
            self.cpp_info.components["native"].includedirs = ["include/coco/board/native"]
            self.cpp_info.components["native"].requires = ["coco::coco"]
        elif platform == "emu":
            self.cpp_info.components["emu"].libs = ["coco-board-emu"]
            self.cpp_info.components["emu"].includedirs = ["include/coco/board/emu"]
            self.cpp_info.components["emu"].requires = ["coco::coco"]
        elif platform == "nrf52840":
            self.cpp_info.components["nrf52dongle"].libs = ["coco-board-nrf52dongle"]
            self.cpp_info.components["nrf52dongle"].includedirs = ["include/coco/board/nrf52dongle"]
            self.cpp_info.components["nrf52dongle"].requires = ["coco::coco"]
        elif platform == "stm32f051x8":
            self.cpp_info.components["stm32f051discovery"].libs = ["coco-board-stm32f051discovery"]
            self.cpp_info.components["stm32f051discovery"].includedirs = ["include/coco/board/stm32f051discovery"]
            self.cpp_info.components["stm32f051discovery"].requires = ["coco::coco"]
        elif platform == "stm32g431xx":
            self.cpp_info.components["stm32g431nucleo"].libs = ["coco-board-stm32g431nucleo"]
            self.cpp_info.components["stm32g431nucleo"].includedirs = ["include/coco/board/stm32g431nucleo"]
            self.cpp_info.components["stm32g431nucleo"].requires = ["coco::coco"]
        elif platform == "stm32g474xx":
            self.cpp_info.components["stm32g474nucleo"].libs = ["coco-board-stm32g474nucleo"]
            self.cpp_info.components["stm32g474nucleo"].includedirs = ["include/coco/board/stm32g474nucleo"]
            self.cpp_info.components["stm32g474nucleo"].requires = ["coco::coco"]
        else:
            self.cpp_info.includedirs = []
