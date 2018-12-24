# Notes on shellcoding

shellcode - exploit instructions used once the system is hacked.

## strace ./helloworld
"""
[root@041e4d45e9cc shellcode]# strace ./helloworld
execve("./helloworld", ["./helloworld"], [/* 10 vars */]) = 0
brk(NULL)                               = 0x18fa000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fb75111b000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=13950, ...}) = 0
mmap(NULL, 13950, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fb751117000
close(3)                                = 0
open("/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P%\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2173512, ...}) = 0
mmap(NULL, 3981792, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fb750b2e000
mprotect(0x7fb750cf1000, 2093056, PROT_NONE) = 0
mmap(0x7fb750ef0000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c2000) = 0x7fb750ef0000
mmap(0x7fb750ef6000, 16864, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fb750ef6000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fb751116000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fb751114000
arch_prctl(ARCH_SET_FS, 0x7fb751114740) = 0
mprotect(0x7fb750ef0000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7fb75111c000, 4096, PROT_READ) = 0
munmap(0x7fb751117000, 13950)           = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fb75111a000
write(1, "hello, world!\n", 14hello, world!
)         = 14
exit_group(0)                           = ?
+++ exited with 0 +++
"""
