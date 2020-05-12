from conans import ConanFile, CMake

class Project(ConanFile):
    name = 'mtl'
    version = '0.1.0'
    license = 'MIT'
    author = 'Matthew Peterson (matthew.se.peterson@gmail.com)'
    
    settings = 'os', 'compiler', 'arch', 'build_type'
    generators = 'cmake'
    
    exports_sources = 'CMakeLists.txt', 'include/*', 'tests/*'
    no_copy_source = True
    
    requires = [
        'fmt/6.2.0',
        'doctest/2.3.7'
    ]

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy('*.h')
    
    def package_id(self):
        self.info.header_only()