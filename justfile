# use cmd.exe instead of sh:
set shell := ["cmd.exe", "/c"]

# Genereate compile_commands.json with correct includes and defines for clangd
# (see https://docs.qmk.fm/other_vscode#configuring-vs-code).
precompile:
    qmk compile -j 0 -km default --compiledb

# '-' ignores error in the command
build-left:
    -qmk flash -j 0 -km default -bl uf2-split-left
    mv geigeigeist_totem_default.uf2 geigeigeist_totem_default_left.uf2

# '-' ignores error in the command
build-right:
    -qmk flash -j 0 -km default -bl uf2-split-right
    mv geigeigeist_totem_default.uf2 geigeigeist_totem_default_right.uf2

build:
    just build-left build-right
