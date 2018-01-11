PLUGIN_NAME = limiter

HEADERS = limiter.h

SOURCES = limiter.cpp\
          moc_limiter.cpp\

LIBS = 

### Do not edit below this line ###

include $(shell rtxi_plugin_config --pkgdata-dir)/Makefile.plugin_compile
