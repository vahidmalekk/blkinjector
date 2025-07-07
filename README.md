# 🧨 blkinjector

**blkinjector** is a Linux tool that replaces files inside ext2/3/4 filesystems by directly writing to the block device or image using the `libext2fs` library. While it operates below the typical file I/O level, it still uses system calls — making it a stealthier but not syscall-free method.

---

## 🎯 Overview

`blkinjector` is intended for low-level manipulation of ext-based filesystems for use in research, recovery, or red teaming scenarios. It allows replacing file contents without mounting the filesystem and without interacting with the Virtual Filesystem (VFS) layer.

---

## ✅ Features

- Writes directly to block devices or image files
- Targets ext2/ext3/ext4 filesystems
- Avoids VFS-level interactions (e.g., `open("/etc/passwd")`)
- More stealthy than traditional file operations
- Useful for forensic testing, malware emulation, and recovery

---

## ⚠️ Limitations

- Uses standard C and `libext2fs` functions — **does not eliminate syscalls**
- Not undetectable: tools monitoring `/dev` access or `auditd` rules on block devices may still log activity but i havent seen that yet.
- Does not bypass LSM (e.g., SELinux) if monitoring `/dev` directly

---

## ⚠️ Legal Notice

This tool is provided for **educational and authorized security testing only**.  
Use only on systems you own or have explicit permission to test.

---

## 💻 Usage

```bash
sudo ./blkinjector <device.img | /dev/sdX> <source_file> <target_path_in_fs>
