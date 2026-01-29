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
        self.requires("coco/0.8.0", options={"platform": self.options.platform})

    def build_requirements(self):
        self.tool_requires("coco-toolchain/0.4.0", options={"platform": self.options.platform})

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
        elif platform == "stm32f042x6": # CANable 0.2
            self.cpp_info.components["canable02"].includedirs = ["include/coco/board/canable02"]
            self.cpp_info.components["canable02"].libs = ["canable02"]
            self.cpp_info.components["canable02"].exelinkflags = ["-Tcanable02.ld"]
            self.cpp_info.components["canable02"].requires = ["coco::coco"]
        elif platform == "stm32f051x8":
            self.cpp_info.components["stm32f0discovery"].includedirs = ["include/coco/board/stm32f0discovery"]
            self.cpp_info.components["stm32f0discovery"].libs = ["stm32f0discovery"]
            self.cpp_info.components["stm32f0discovery"].exelinkflags = ["-Tstm32f0discovery.ld"]
            self.cpp_info.components["stm32f0discovery"].requires = ["coco::coco"]
        elif platform == "stm32c031xx":
            self.cpp_info.components["nucleo-c031c6"].includedirs = ["include/coco/board/nucleo-c031c6"]
            self.cpp_info.components["nucleo-c031c6"].libs = ["nucleo-c031c6"]
            self.cpp_info.components["nucleo-c031c6"].exelinkflags = ["-Tnucleo-c031c6.ld"]
            self.cpp_info.components["nucleo-c031c6"].requires = ["coco::coco"]
        elif platform == "stm32f334x8":
            self.cpp_info.components["stm32f3348discovery"].includedirs = ["include/coco/board/stm32f3348discovery"]
            self.cpp_info.components["stm32f3348discovery"].libs = ["stm32f3348discovery"]
            self.cpp_info.components["stm32f3348discovery"].exelinkflags = ["-Tstm32f3348discovery.ld"]
            self.cpp_info.components["stm32f3348discovery"].requires = ["coco::coco"]
        elif platform == "stm32f401xe":
            self.cpp_info.components["nucleo-f401re"].includedirs = ["include/coco/board/nucleo-f401re"]
            self.cpp_info.components["nucleo-f401re"].libs = ["nucleo-f401re"]
            self.cpp_info.components["nucleo-f401re"].exelinkflags = ["-Tnucleo-f401re.ld"]
            self.cpp_info.components["nucleo-f401re"].requires = ["coco::coco"]
        elif platform == "stm32g0b1xx":
            self.cpp_info.components["nucleo-g0b1re"].includedirs = ["include/coco/board/nucleo-g0b1re"]
            self.cpp_info.components["nucleo-g0b1re"].libs = ["nucleo-g0b1re"]
            self.cpp_info.components["nucleo-g0b1re"].exelinkflags = ["-Tnucleo-g0b1re.ld"]
            self.cpp_info.components["nucleo-g0b1re"].requires = ["coco::coco"]
        elif platform == "stm32g431xx":
            self.cpp_info.components["nucleo-g431rb"].includedirs = ["include/coco/board/nucleo-g431rb"]
            self.cpp_info.components["nucleo-g431rb"].libs = ["nucleo-g431rb"]
            self.cpp_info.components["nucleo-g431rb"].exelinkflags = ["-Tnucleo-g431rb.ld"]
            self.cpp_info.components["nucleo-g431rb"].requires = ["coco::coco"]
        elif platform == "stm32g474xx":
            self.cpp_info.components["nucleo-g474re"].includedirs = ["include/coco/board/nucleo-g474re"]
            self.cpp_info.components["nucleo-g474re"].libs = ["nucleo-g474re"]
            self.cpp_info.components["nucleo-g474re"].exelinkflags = ["-Tnucleo-g474re.ld"]
            self.cpp_info.components["nucleo-g474re"].requires = ["coco::coco"]
        elif platform == "stm32g491xx":
            self.cpp_info.components["nucleo-g491re"].includedirs = ["include/coco/board/nucleo-g491re"]
            self.cpp_info.components["nucleo-g491re"].libs = ["nucleo-g491re"]
            self.cpp_info.components["nucleo-g491re"].exelinkflags = ["-Tnucleo-g491re.ld"]
            self.cpp_info.components["nucleo-g491re"].requires = ["coco::coco"]
        elif platform == "stm32h503xx":
            self.cpp_info.components["nucleo-h503rb"].includedirs = ["include/coco/board/nucleo-h503rb"]
            self.cpp_info.components["nucleo-h503rb"].libs = ["nucleo-h503rb"]
            self.cpp_info.components["nucleo-h503rb"].exelinkflags = ["-Tnucleo-h503rb.ld"]
            self.cpp_info.components["nucleo-h503rb"].requires = ["coco::coco"]
        elif platform == "stm32h563xx":
            self.cpp_info.components["nucleo-h563zi"].includedirs = ["include/coco/board/nucleo-h563zi"]
            self.cpp_info.components["nucleo-h563zi"].libs = ["nucleo-h563zi"]
            self.cpp_info.components["nucleo-h563zi"].exelinkflags = ["-Tnucleo-h563zi.ld"]
            self.cpp_info.components["nucleo-h563zi"].requires = ["coco::coco"]
        elif platform == "stm32u385xx":
            self.cpp_info.components["nucleo-u385rg-q"].includedirs = ["include/coco/board/nucleo-u385rg-q"]
            self.cpp_info.components["nucleo-u385rg-q"].libs = ["nucleo-u385rg-q"]
            self.cpp_info.components["nucleo-u385rg-q"].exelinkflags = ["-Tnucleo-u385rg-q.ld"]
            self.cpp_info.components["nucleo-u385rg-q"].requires = ["coco::coco"]
        else:
            # dummy board for native platforms (Windows, MacOS, Linux) with same name as platform
            p = str(platform)
            self.cpp_info.components[p].includedirs = [f"include/coco/board/native"] # contains empty config file
            self.cpp_info.components[p].libs = [] # ["native"] # library is empty, therefore no linking needed
            self.cpp_info.components[p].requires = ["coco::coco"]
