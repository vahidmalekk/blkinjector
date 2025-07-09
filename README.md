# 🧨 blkinjector

blkinjector is a Linux tool that replaces files within ext2/3/4 filesystems by directly writing to the block device or disk image using the libext2fs library. Its primary goal is to bypass auditd file watch mechanisms. While it operates below the typical file I/O level, it still uses system calls — making it a stealthier but not syscall-free method.

---

## 🎯 Overview

`blkinjector` is intended for low-level manipulation of ext-based filesystems for use in research, recovery, or red teaming scenarios. It allows replacing file contents without mounting the filesystem and without interacting with the Virtual Filesystem (VFS) layer.

---

## ✅ Features

- Writes directly to block devices or image files
- Targets ext2/ext3/ext4 filesystems
- Avoids VFS-level interactions (e.g., `open("/etc/passwd")`)
- More stealthy than traditional file operations


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
git clone git@github.com:vahidmalekk/blkinjector.git
cd blkinjector
gcc blkinjector.c -o blkinjector -lext2fs -lcom_err
run `lsblk` command for detecting block device
sudo ./blkinjector <device.img | /dev/sdX> <source_file> <target_path_in_fs>
example: ./blkinjector /dev/vda1 /tmp/passwd /etc/passwd
To clear the cache immediately, run the following command: echo 3 > /proc/sys/vm/drop_caches
```
```bash
OR you can download the binary and run it
wget https://github.com/vahidmalekk/blkinjector/releases/download/v/blkinjector
chmod +x blkinjector
lsblk
./blkinjector <device.img | /dev/sdX> <source_file> <target_path_in_fs>
example: ./blkinjector /dev/vda1 /tmp/a/passwd /etc/passwd
echo 3 > /proc/sys/vm/drop_caches
```

