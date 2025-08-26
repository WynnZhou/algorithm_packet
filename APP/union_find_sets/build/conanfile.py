from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout, CMakeToolchain
from conan.tools.microsoft import is_msvc

class UnionFindSetsAlgorithm(ConanFile):
    name = "union_find_sets"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    exports_sources = "../src/*", "../CMakeLists.txt"
    
    def requirements(self):
        # 使用本地已安装的CMake
        pass
    
    def configure(self):
        if self.settings.os == "Windows":
            if self.settings.compiler == "msvc":
                self.settings.compiler.cppstd = "17"
                self.settings.compiler.runtime = "dynamic"
                self.settings.compiler.runtime_type = "Release"
            elif self.settings.compiler == "gcc":
                self.settings.compiler.cppstd = "gnu17"
                self.settings.compiler.version = "15"
    
    def layout(self):
        cmake_layout(self)
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        
    def package(self):
        self.copy("*.h", dst="include", src="../src")
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        
    def package_info(self):
        self.cpp_info.libs = ["union_find_sets"]
        
    def test(self):
        if not is_msvc(self):
            self.run(f"ctest --output-on-failure -C {self.settings.build_type}")
