#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath ="home/yanuar/Downloads"

static int xmp_getdir(const char *path, fuse_dirh_t h, fuse_dirfil_t filler)
{
    DIR *dp;
    struct dirent *de;
    int res = 0;
    char fpath[1000];
    sprintf(fpath, "%s%s", dirpath, path);
    dp = opendir(fpath);
    if(dp == NULL)
        return -errno;

    while((de = readdir(dp)) != NULL)
    {
        res = filler(h, de->d_name, de->d_type);
        if(res != 0)
            break;
    }

    closedir(dp);
    return res;
}

static struct fuse_operations xmp_oper = {

    .getdir = xmp_getdir,

}

