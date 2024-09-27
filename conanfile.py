from conan import ConanFile
from conan.tools.files import copy
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
    exports_sources = "conanfile.py", "CMakeLists.txt", "coco/*", "test/*"
    no_copy_source = True


    # check if we are cross compiling
    def cross(self):
        if hasattr(self, "settings_build"):
            return self.settings.os != self.settings_build.os
        return False

    def requirements(self):
        self.requires("coco/0.7.0", options={"platform": self.options.platform})

    def build_requirements(self):
        self.tool_requires("coco-toolchain/0.3.0", options={"platform": self.options.platform})

    keep_imports = True
    def imports(self):
        # copy dependent libraries into the build folder
        copy(self, "*", src="@bindirs", dst="bin")
        copy(self, "*", src="@libdirs", dst="lib")

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
        if platform == "nrf52840":
            self.cpp_info.components["nrf52dongle"].includedirs = ["include/coco/board/nrf52dongle"]
            self.cpp_info.components["nrf52dongle"].libs = ["nrf52dongle"]
            self.cpp_info.components["nrf52dongle"].exelinkflags = ["-Tnrf52dongle.ld"]
            self.cpp_info.components["nrf52dongle"].requires = ["coco::coco"]
        elif platform == "stm32f042x6":
            self.cpp_info.components["canable02"].includedirs = ["include/coco/board/canable02"]
            self.cpp_info.components["canable02"].libs = ["canable02"]
            self.cpp_info.components["canable02"].exelinkflags = ["-Tcanable02.ld"]
            self.cpp_info.components["canable02"].requires = ["coco::coco"]
        elif platform == "stm32f051x8":
            self.cpp_info.components["stm32f0discovery"].includedirs = ["include/coco/board/stm32f0discovery"]
            self.cpp_info.components["stm32f0discovery"].libs = ["stm32f0discovery"]
            self.cpp_info.components["stm32f0discovery"].exelinkflags = ["-Tstm32f0discovery.ld"]
            self.cpp_info.components["stm32f0discovery"].requires = ["coco::coco"]
        elif platform == "stm32f334x8":
            self.cpp_info.components["stm32f3348discovery"].includedirs = ["include/coco/board/stm32f3348discovery"]
            self.cpp_info.components["stm32f3348discovery"].libs = ["stm32f3348discovery"]
            self.cpp_info.components["stm32f3348discovery"].exelinkflags = ["-Tstm32f3348discovery.ld"]
            self.cpp_info.components["stm32f3348discovery"].requires = ["coco::coco"]
        elif platform == "stm32c031xx":
            self.cpp_info.components["stm32c031nucleo"].includedirs = ["include/coco/board/stm32c031nucleo"]
            self.cpp_info.components["stm32c031nucleo"].libs = ["stm32c031nucleo"]
            self.cpp_info.components["stm32c031nucleo"].exelinkflags = ["-Tstm32c031nucleo.ld"]
            self.cpp_info.components["stm32c031nucleo"].requires = ["coco::coco"]
        elif platform == "stm32f401xe":
            self.cpp_info.components["stm32f401nucleo"].includedirs = ["include/coco/board/stm32f401nucleo"]
            self.cpp_info.components["stm32f401nucleo"].libs = ["stm32f401nucleo"]
            self.cpp_info.components["stm32f401nucleo"].exelinkflags = ["-Tstm32f401nucleo.ld"]
            self.cpp_info.components["stm32f401nucleo"].requires = ["coco::coco"]
        elif platform == "stm32g431xx":
            self.cpp_info.components["stm32g431nucleo"].includedirs = ["include/coco/board/stm32g431nucleo"]
            self.cpp_info.components["stm32g431nucleo"].libs = ["stm32g431nucleo"]
            self.cpp_info.components["stm32g431nucleo"].exelinkflags = ["-Tstm32g431nucleo.ld"]
            self.cpp_info.components["stm32g431nucleo"].requires = ["coco::coco"]
        elif platform == "stm32g474xx":
            self.cpp_info.components["stm32g474nucleo"].includedirs = ["include/coco/board/stm32g474nucleo"]
            self.cpp_info.components["stm32g474nucleo"].libs = ["stm32g474nucleo"]
            self.cpp_info.components["stm32g474nucleo"].exelinkflags = ["-Tstm32g474nucleo.ld"]
            self.cpp_info.components["stm32g474nucleo"].requires = ["coco::coco"]
        else:
            # dummy board for native platforms (Windows, MacOS, Linux) with same name as platform
            p = str(platform)
            self.cpp_info.components[p].includedirs = [f"include/coco/board/native"]
            self.cpp_info.components[p].libs = [] # ["native"] # library is empty
            self.cpp_info.components[p].requires = ["coco::coco"]
