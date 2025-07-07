#include <stdio.h>
#include <stdlib.h>
#include <ext2fs/ext2fs.h>

void die(const char *msg, errcode_t err) {
    if (err)
        fprintf(stderr, "%s: %s\n", msg, error_message(err));
    else
        perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <device> <source_file> <target_path_in_fs>\n", argv[0]);
        return 1;
    }

    const char *device = argv[1];
    const char *src_path = argv[2];
    const char *dst_path = argv[3];

    // Read source file
    FILE *src = fopen(src_path, "rb");
    if (!src) die("Failed to open source file", 0);
    fseek(src, 0, SEEK_END);
    long size = ftell(src);
    fseek(src, 0, SEEK_SET);

    char *buf = malloc(size);
    if (!buf) die("malloc failed", 0);
    if (fread(buf, 1, size, src) != size) die("fread failed", 0);
    fclose(src);

    // Open filesystem
    ext2_filsys fs;
    errcode_t err = ext2fs_open(device, EXT2_FLAG_RW, 0, 0, unix_io_manager, &fs);
    if (err) die("ext2fs_open", err);

    // Read bitmaps
    if ((err = ext2fs_read_inode_bitmap(fs))) die("read_inode_bitmap", err);
    if ((err = ext2fs_read_block_bitmap(fs))) die("read_block_bitmap", err);

    // Find the inode of the destination file
    ext2_ino_t ino;
    err = ext2fs_namei(fs, EXT2_ROOT_INO, EXT2_ROOT_INO, dst_path, &ino);
    if (err) die("ext2fs_namei (file not found in fs)", err);

    // Open the inode for writing
    ext2_file_t file;
    err = ext2fs_file_open(fs, ino, EXT2_FILE_WRITE, &file);
    if (err) die("ext2fs_file_open", err);

    // Truncate the file first
    err = ext2fs_file_set_size(file, 0);
    if (err) die("truncate failed", err);

    // Write data
    unsigned int written = 0;
    err = ext2fs_file_write(file, buf, size, &written);
    if (err || written != size) die("ext2fs_file_write failed", err);

    ext2fs_file_close(file);
    ext2fs_close(fs);
    free(buf);

    printf("✅ Replaced file %s in %s with %s (%ld bytes).\n", dst_path, device, src_path, size);
    return 0;
}
