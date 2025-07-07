# 🧨 blkinjector

**blkinjector** is a low-level Linux utility that enables direct file injection into ext2/3/4 filesystems via raw block access. By avoiding standard system calls (`open()`, `write()`, `unlink()`), it evades syscall-based monitoring tools such as Auditd and EDR solutions—making it an ideal tool for stealth operations and security research.

---

## 🎯 Purpose

Modern security solutions monitor system calls to detect malicious or unauthorized activity. `blkinjector` bypasses these mechanisms by operating entirely at the disk level, enabling forensic, Red Team, or research use cases where stealth and minimal footprint are essential.

---

## ✅ Key Features

- 🔒 **Syscall-Free File Injection** – Avoids `open()`, `write()`, and other detectable syscalls
- 💾 **Supports ext2, ext3, ext4** – Works directly with standard Linux filesystems
- 🧱 **Raw Disk or Image Targeting** – Operates on both live devices (`/dev/sdX`) and image files
- ⚙️ **Scriptable Interface** – Designed for automation in Red Team tooling or research pipelines
- 🛑 **No Filesystem Mounting Required**

---

## ⚠️ Disclaimer

This tool is intended **strictly for authorized security testing and educational use**.  
Use only on systems you own or have explicit permission to analyze. Misuse may violate laws and ethical guidelines.

---

## 💻 Usage

```bash
sudo ./blkinjector <device.img | /dev/sdX> <source_file> <target_path_in_fs>
