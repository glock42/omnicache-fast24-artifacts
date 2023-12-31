#ifndef DEVFSLIB_H
#define DEVFSLIB_H

#define USE_DEFAULT_PARAM 0
#define DEFAULT_SCHEDULER_POLICY 3

#ifdef __cplusplus
extern "C" {
	    int crfsinit(unsigned int qentry_count,
		        unsigned int dev_core_cnt, unsigned int sched_policy);
        int crfsinit_cxl_ns(unsigned int qentry_count,
		        unsigned int dev_core_cnt, unsigned int sched_policy, unsigned int cxl_ns_size);

        ssize_t crfswrite(int fd, const void *buf, size_t count);
        ssize_t crfspwrite(int fd, const void *buf, size_t count, off_t offset);

        int crfsopen(const char *pathname, int flags, mode_t mode);
        int crfsclose(int fd);
        int crfsexit(void);
        /* Leveldb related compound POSIX calls */
        size_t devfs_leveldb_checksum_write(int fd, const void* data, size_t data_len, char* meta,
                        size_t meta_len, int checksum_pos, int type_pos, uint8_t end, int cal_type, uint32_t type_crc);

        ssize_t devfs_leveldb_checksum_read(int fd, void *buf, size_t count, uint8_t end);

        ssize_t devfs_leveldb_checksum_pread(int fd, void *buf, size_t count, off_t offset, uint8_t end);

        /* used for shim library */
        size_t leveldb_checksum_write(int fd, const void* data, size_t data_len, char* meta,
                        size_t meta_len, int checksum_pos, int type_pos, uint8_t end, int cal_type, uint32_t type_crc);

        ssize_t leveldb_checksum_read(int fd, void *buf, size_t count, uint8_t end);

        ssize_t leveldb_checksum_pread(int fd, void *buf, size_t count, off_t offset, uint8_t end);
}
#else
int crfsinit(unsigned int qentry_count,
		unsigned int dev_core_cnt, unsigned int sched_policy);

int crfsinit_cxl_ns(unsigned int qentry_count,
		unsigned int dev_core_cnt, unsigned int sched_policy, unsigned int cxl_ns_size);
int crfsexit(void);

/* Leveldb related compound POSIX calls */
size_t devfs_leveldb_checksum_write(int fd, const void* data, size_t data_len, char* meta,
                size_t meta_len, int checksum_pos, int type_pos, uint8_t end, int cal_type, uint32_t type_crc);

ssize_t devfs_leveldb_checksum_read(int fd, void *buf, size_t count, uint8_t end);

ssize_t devfs_leveldb_checksum_pread(int fd, void *buf, size_t count, off_t offset, uint8_t end);

/* used for shim library */
size_t leveldb_checksum_write(int fd, const void* data, size_t data_len, char* meta,
                size_t meta_len, int checksum_pos, int type_pos, uint8_t end, int cal_type, uint32_t type_crc);

ssize_t leveldb_checksum_read(int fd, void *buf, size_t count, uint8_t end);

ssize_t leveldb_checksum_pread(int fd, void *buf, size_t count, off_t offset, uint8_t end);


#endif

ssize_t crfswrite(int fd, const void *buf, size_t count);
ssize_t crfsread(int fd, void *buf, size_t count);
ssize_t crfspwrite(int fd, const void *buf, size_t count, off_t offset);
ssize_t crfspread(int fd, void *buf, size_t count, off_t offset);
int crfsclose(int fd);
int crfslseek64(int fd, off_t offset, int whence);
int crfsopen(const char *pathname, int flags, mode_t mode);
int crfsunlink(const char *pathname);
int crfsfsync(int fd);
int crfsfallocate(int fd, int mode, off_t offset, off_t len);
int crfsftruncate(int fd, off_t length);
int crfsrename(const char *oldpath, const char *newpath);


/* Compound POSIX calls (containing computing along with I/O command) */
int devfsreadmodifywrite(int fd, const void *buf, size_t count, off_t offset);
size_t devfsreadmodifywrite_batch(int fd, const void **p, size_t count, off_t* offsets, size_t batch_size);
size_t devfsopenpwriteclose_batch(int fd, const void **p, size_t count, off_t* offsets, char* out_file, size_t batch_size);
size_t devfschecksumpwrite_batch(int fd, const void **p, size_t count, 
                off_t* offset, uint8_t crc_pos, size_t batch_size);
int devfsreadmodifyappend(int fd, const void *buf, size_t count);
int devfschecksumread(int fd, const void *buf, size_t count);
int devfschecksumwrite(int fd, const void *buf, size_t count);
int devfschecksumpread(int fd, const void *buf, size_t count, off_t offset);

int devfschecksumpwrite(int fd, const void *buf, size_t count, off_t offset);
int devfschecksumpwrite_cache_host(int fd, const void *buf, size_t count, off_t offset);
size_t devfsappendchksmpwrite_cache_kernel(int fd, const void *p, size_t count, off_t offset);
size_t devfsappendchksmpwrite_cache_hybrid(int fd, const void *p, size_t count, off_t offset);

size_t devfsreadchksmpwrite(int fd, const void *p, size_t count, off_t offset);
size_t devfsreadchksmpwrite_cache_host(int fd, const void *p, size_t count, off_t offset);
size_t devfsreadchksmpwrite_cache_kernel(int fd, const void *p, size_t count, off_t offset);
size_t devfsreadchksmpwrite_cache_hybrid(int fd, const void *p, size_t count, off_t offset);

int devfscompresswrite(int fd, const void *p, size_t count, char* in_file);
int devfscompresswrite_cache(int fd, const void *p, size_t count, char* in_file);

int devfsencryptwrite(int fd, const void *buf, size_t count);
int devfsencryptpwrite(int fd, const void *buf, size_t count, off_t offset);
int devfspreadencryptpwrite(int fd, const void *buf, size_t count, off_t offset);
int devfsopenpwriteclose(int fd, const void *buf, size_t count, off_t offset, char* out_file);
int devfsopenpreadclose(int fd, const void *buf, size_t count, off_t offset, char* filename);
ssize_t devfsreadappend(int fd, const void *buf, size_t count);

int crfschecksumwritecc(int fd, const void *buf, size_t count);
size_t devfs_readknnwrite(int fd, const void *p, size_t count, off_t offset);

/* Inject Crash calls */
int crfsinjectcrash(int fd, int crash_code);

#endif
