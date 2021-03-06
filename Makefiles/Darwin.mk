$(warning Loading Darwin rules)

DISTRO := OSX
RELEASE := $(shell sw_vers -productVersion)

ifeq ($(RELEASE),10.11.6)
CODENAME := ElCapitan
endif

# Mac OSX package

distro_dependencies: release_dependencies
	@echo Check distro dependencies
	[ -x /usr/bin/xsltproc ]

distro_package: release_package
	@echo Generic Darwin packaging
	: fpm -s dir -t osxpkg -n $(PACKAGE) dist

distro_build: release_build
	@echo Generic Darwin build

distro_test: release_test
	@echo Generic Darwin test

distro_clean: release_clean
	@echo Generic Darwin clean

# VERSION := $(shell sw_vers -productVersion)
#  include Makefiles/Darwin$(VERSION).mk

include $(wildcard Makefiles/$(DISTRO).mk Makefiles/Darwin$(RELEASE).mk )
