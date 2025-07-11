# TOTEM

![geigeigeist/totem](https://imgur.com/a/2efW2Tp)

TOTEM is a 38 key column-staggered choc split keyboard.

- Keyboard Maintainer: [Syringus](https://github.com/Syringus)
- Hardware Supported: Totem Wired rev0.3
- Hardware Availability: [github:geigeigeist/totem](https://github.com/geigeigeist/totem)

Make example for this keyboard (after setting up your build environment):

    make geigeigeist/totem:default

or

    qmk compile -j 0 -kb geigeigeist/totem -km default

Flashing example for this keyboard:

    make geigeigeist/totem:default:flash

or for the left halve:

    qmk flash -j 0 -kb geigeigeist/totem -km default -bl uf2-split-left

and for the right halve:

    qmk flash -j 0 -kb geigeigeist/totem -km default -bl uf2-split-right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

- **Physical reset button**: Double press the RESET button on the back of the keyboard.
