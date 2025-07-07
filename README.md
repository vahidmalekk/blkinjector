# blkinjector
Inject files directly into ext2/3/4 block devices or images via raw disk access. Bypasses Auditd and syscall logging by avoiding open/write/unlink syscalls. Replace files on-disk stealthily without mounting the filesystem. For authorized security research and educational use only.
