# use cmd.exe instead of sh:
set shell := ["cmd.exe", "/c"]

build-left:
    # '-' ignores error in the command
    -qmk flash -j 0 -km default -bl uf2-split-left
    mv geigeigeist_totem_default.uf2 geigeigeist_totem_default_left.uf2

build-right:
    # '-' ignores error in the command
    -qmk flash -j 0 -km default -bl uf2-split-right
    mv geigeigeist_totem_default.uf2 geigeigeist_totem_default_right.uf2

build:
    just build-left build-right
