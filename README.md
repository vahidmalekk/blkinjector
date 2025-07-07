# 🧨 blkinjector

### 🔓 Write files directly to ext2/3/4 block devices — bypassing Auditd, syscall logging, and all that noise.

blkinjector is a low-level Linux utility that injects file content into a filesystem image or block device directly via raw access — no open(), no write(), no unlink(), and **no trace for Auditd** to catch.

---

## 🧠 Why?

Because sometimes, stealth is everything.

Auditd, EDRs, and syscall monitors watch everything you do — unless...  
you **never use a syscall** to begin with.

With blkinjector, you:
- Replace files on-disk without mounting the FS
- Avoid Auditd and file access logs
- Act like debugfs, but fully scriptable and weaponized

---

## ⚠️ Disclaimer

**This tool is for educational and authorized security research only.**  
Don’t use it on live systems you don’t own.

---

## 💻 Usage

bash
sudo ./blkinjector <device.img or /dev/sdX> <source_file> 
