## FutosFS - Fuse Tiny OS FileSystem

FutosFS is a basic file system developed for an academic project. It uses the FUSE library to implement simple file system operations like mounting, reading directories, creating, reading, and writing files. The file system supports a maximum of 32 blocks (4KB each), with a straightforward inode structure.

# Features

Superblock: Contains information like block size, inodes, and the root inode number.
Inodes: Each inode corresponds to one data block, limiting the maximum file size to 4KB.
Basic file operations: Read, write, create files, and manage directories.

# Limitations

The project development faced a roadblock due to difficulties in understanding how to correctly access the dentry structure (for directory entries), which prevented further progress in implementing file and directory operations (readdir and lookup).

