# Embedded Media Player on ARM (Buildroot + GStreamer)
A lightweight embedded media player targeting ARM architecture, built with Buildroot and GStreamer.  
This project demonstrates how to cross-compile a GStreamer-based video player and deploy it on a minimal Linux environment (QEMU).
- ARM target system built with Buildroot
- Cross-compilation with external toolchain
- GStreamer integration for video playback (H.264, MP4)
- Custom root filesystem overlay (preloaded sample video)
- Runs on QEMU (vexpress-a9)
```
├── package/
│   └── simple_player/             # Custom Buildroot package
│       ├── simple_player.c
│       ├── simple_player.mk
│       └── Config.in
├── board/
│   └── qemu/
│       └── arm-vexpress/
│           └── rootfs_overlay/
│               └── usr/share/sample.mp4
├── README.md
```
1. Install dependencies
sudo apt update
sudo apt install build-essential git qemu-system-arm

2. Clone Buildroot
git clone https://git.buildroot.net/buildroot
cd buildroot

3. Apply defconfig
make qemu_arm_vexpress_defconfig

4. Add custom player
Put simple_player.c, .mk, and Config.in into package/simple_player/
custom player : Add `source "package/simple_player/Config.in"` to package/Config.in
![image](https://github.com/user-attachments/assets/0f6f51d3-cb92-40ef-bdb8-e0caa16cc0fe)

<p align="center">
  <img src="https://github.com/user-attachments/assets/0f6f51d3-cb92-40ef-bdb8-e0caa16cc0fe" width="600">
</p>


5. Configure packages
make menuconfig
```
 Target Packages → Multimedia → GStreamer1 → Enable:
#     [*] gstreamer1
#     [*] gstreamer1-plugins-base
#         [*] playback
#         [*] videoconvert
#         [*] typefind
#         [*] app
#     [*] gstreamer1-plugins-good
#     [*] gstreamer1-plugins-libav
#     [*] simple_player
```
Filesystem images → Root filesystem overlay
(board/qemu/arm-vexpress/rootfs_overlay)
<p align="center">
  <img src="https://github.com/user-attachments/assets/ef7dc73d-a32b-41be-8233-8bf0604d3c0b" width="600">
</p>


6. Build the system
make
<p align="center">
  <img src="https://github.com/user-attachments/assets/51c8009b-0999-4ad2-97bc-7ea65f8dec1c" width="600">
</p>


8. Launch QEMU
qemu-system-arm \
  -M vexpress-a9 \
  -m 256M \
  -kernel output/images/zImage \
  -dtb output/images/vexpress-v2p-ca9.dtb \
  -drive file=output/images/rootfs.ext2,if=sd,format=raw \
  -append "root=/dev/mmcblk0 console=ttyAMA0" \
  -nographic
<p align="center">
  <img src="https://github.com/user-attachments/assets/b51e791a-673c-4180-9c01-d7229858786b" width="600">
</p>


- Buildroot internals: defconfig, overlay, package integration
- Cross-compilation workflow for embedded Linux
- Integrating and debugging GStreamer plugins
- Rootfs overlay injection for file placement (e.g., video)
- Running and testing embedded software in QEMU without hardware

  ### Status

- System booted successfully on QEMU ARM (vexpress-a9)
- Custom `simple_player` binary is deployed and executable
- GStreamer pipeline fails to initialize `playbin` element due to missing plugin in Buildroot configuration

