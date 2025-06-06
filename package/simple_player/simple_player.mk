################################################################################
#
# simple_player
#
################################################################################

SIMPLE_PLAYER_SITE =$(TOPDIR)/package/simple_player
SIMPLE_PLAYER_SITE_METHOD = local

SIMPLE_PLAYER_DEPENDENCIES = gstreamer1 gstreamer1-plugins-base 





SIMPLE_PLAYER_INSTALL_TARGET = YES

define SIMPLE_PLAYER_BUILD_CMDS
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) -o $(@D)/simple_player \
		$(@D)/simple_player.c `$(PKG_CONFIG_HOST_BINARY) --cflags --libs gstreamer-1.0`
endef

define SIMPLE_PLAYER_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/simple_player $(TARGET_DIR)/usr/bin/simple_player
endef

$(eval $(generic-package))

