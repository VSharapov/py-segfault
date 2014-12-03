from distutils.core import setup, Extension

my_module = Extension('segfault', ['segfault.c'])
setup(
        name='segfault',
        version='1.0',
        description = 'lol, it segfaults',
        ext_modules=[my_module]
        )
