@echo off
set cur_path=%~dp0
set "cur_path=%cur_path:\=/%"
set GYP_TOOLS=%cur_path%tools/GYP-Tools/gyp
set ROOT_GYP=%cur_path%all.gyp
set GYP_DEFINES=PRO_ROOT=%cur_path% build_type=release

%GYP_TOOLS% --depth=. %ROOT_GYP%
