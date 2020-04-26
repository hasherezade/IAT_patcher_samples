cmake_minimum_required (VERSION 2.8)
project ( IAT_patcher_libs )

# modules:
set ( M_BOT_MON "BotMon" )
set ( M_CH_COLORS "ChangeColors" )

# Add sub-directories
#
add_subdirectory( ${M_BOT_MON} )
add_subdirectory( ${M_CH_COLORS} )
