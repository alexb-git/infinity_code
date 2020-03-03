/****************************************************************************
** Filename:    - my_ext2_test.c
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - understand file system ex4
** Date:        - 11/2/2018
** Version:     - 2
*****************************************************************************/
/*
 * ext2super.c
 *
 * Reads the super-block from a Ext2 floppy disk.
 *
 * Questions?
 * Emanuele Altieri
 * ealtieri@hampshire.edu
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_ext2_fs.h"


/****************************************************************************
    Helpful colors
*****************************************************************************/
#define YLL	 "\x1b[93m"
#define GRE	 "\x1b[92m"
#define RED	 "\x1b[91m"
#define WHI	 "\x1B[37m"
#define CYA	 "\x1B[36m"
#define BLU	 "\x1B[34m"
#define YEL	 "\x1b[33m"
#define RES	 "\x1b[0m"
#define BLD  "\x1B[1m"
#define UDL  "\x1b[4m"

/****************************************************************************
    Helpful defines
*****************************************************************************/
#define PrintHeader(X)      printf( BLU "\n\t------------"\
                                    "  This is a test for: "\
                                    X" ------------\n" RES)

#define PrintInYellow(X)  ( printf(YEL X RES) )
#define PrintInGreen(X)   ( printf(GRE X RES) )
#define PrintInRed(X)     ( printf(RED X RES) )
#define PrintOK           ( printf(GRE "%s" RES, "-OK") )
#define PrintERR          ( printf(RED "%s" RES, "-ERR"))
#define PrintOKorERR(X)   ( (X)?(PrintOK):(PrintERR) )
#define SizeArr(X)        ( sizeof(X)/sizeof(X[0]) )

/****************************************************************************
    Helpful defines and function declarations for this program
*****************************************************************************/
#define BASE_OFFSET 1024       /* locates beginning of the super block (first group) */
#define FD_DEVICE "/dev/ram0"  /* the floppy disk device */
#define BLOCK_OFFSET(block) (BASE_OFFSET+(block-1)*block_size)

static unsigned int block_size = 0;        /* block size (to be calculated) */

static void read_dir(int, const struct ext2_inode*, const struct ext2_group_desc*);
static void read_inode(int, int, const struct ext2_group_desc*, struct ext2_inode*);


/*===============================  THE MAIN  ==============================*/
int main(void)
{
	struct ext2_super_block super;
	int fd;

	/* open floppy device */

	if ((fd = open(FD_DEVICE, O_RDONLY)) < 0)
    {
		perror(FD_DEVICE);
		exit(1);  /* error while opening the floppy device */
	}

    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, &super, sizeof(super));

	if (super.s_magic != EXT2_SUPER_MAGIC)
    {
		fprintf(stderr, "Not a Ext2 filesystem\n");
		exit(1);
	}

    block_size = 1024 << super.s_log_block_size;
    PrintInYellow("\nSuper block info\n");
	printf("Reading super-block from device " FD_DEVICE ":\n"
	       "Inodes count            : %u\n"
	       "Blocks count            : %u\n"
	       "Reserved blocks count   : %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "First data block        : %u\n"
	       "Block size              : %u\n"
	       "Blocks per group        : %u\n"
	       "Inodes per group        : %u\n"
	       "Creator OS              : %u\n"
	       "First non-reserved inode: %u\n"
	       "Size of inode structure : %hu\n"
	       ,
	       super.s_inodes_count,
	       super.s_blocks_count,
	       super.s_r_blocks_count,     /* reserved blocks count */
	       super.s_free_blocks_count,
	       super.s_free_inodes_count,
	       super.s_first_data_block,
	       block_size,
	       super.s_blocks_per_group,
	       super.s_inodes_per_group,
	       super.s_creator_os,
	       super.s_first_ino,          /* first non-reserved inode */
	       super.s_inode_size);


    struct ext2_group_desc group;
    lseek(fd, BASE_OFFSET + block_size, SEEK_SET);
    read( fd, &group, sizeof(group));

	PrintInYellow("\nGroup block info\n");
	printf("Reading first group-descriptor from device " FD_DEVICE ":\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n"
	       ,
	       group.bg_block_bitmap,
	       group.bg_inode_bitmap,
	       group.bg_inode_table,
	       group.bg_free_blocks_count,
	       group.bg_free_inodes_count,
	       group.bg_used_dirs_count);    /* directories count */

    struct ext2_inode inode;

    read_inode(fd, 2, &group, &inode);   /* read inode 2 (root directory) */
    PrintInYellow("\ni-node\n");
    printf( "Reading root inode\n"
            "File mode: %hu\n"
            "Owner UID: %hu\n"
            "Size     : %u bytes\n"
            "Blocks   : %u\n"
            ,
            inode.i_mode,
            inode.i_uid,
            inode.i_size,
            inode.i_blocks);

    PrintInYellow("\n");
    int i = 0;
   	for( i = 0 ; i < EXT2_N_BLOCKS ; i++)
    {
   		if (i < EXT2_NDIR_BLOCKS)         /* direct blocks */
        {
   			printf("Block %2u : %u\n", i, inode.i_block[i]);
        }
   		else if (i == EXT2_IND_BLOCK)     /* single indirect block */
        {
   			printf("Single   : %u\n", inode.i_block[i]);
        }
   		else if (i == EXT2_DIND_BLOCK)    /* double indirect block */
        {
   			printf("Double   : %u\n", inode.i_block[i]);
        }
   		else if (i == EXT2_TIND_BLOCK)    /* triple indirect block */
        {
   			printf("Triple   : %u\n", inode.i_block[i]);
        }
    }

    PrintInYellow("\nRead Dir\n");
	read_dir(fd, &inode, &group);


    /* find the file according name */


    close(fd);

	exit(0);
} /* main() */


static
void read_inode( int fd                              ,
                 int inode_no                        ,
                 const struct ext2_group_desc *group ,
                 struct ext2_inode            *inode )
{
	lseek(fd,
          BLOCK_OFFSET(group->bg_inode_table)
           +
         (inode_no-1)*sizeof(struct ext2_inode)
          ,
	      SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
} /* read_inode() */


static void read_dir( int fd                                ,
                      const struct ext2_inode      *inode   ,
                      const struct ext2_group_desc *group   )
{
	void *block;

	if (S_ISDIR(inode->i_mode))
    {
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		if ((block = malloc(block_size)) == NULL)
        {
            /* allocate memory for the data block */
			fprintf(stderr, "Memory error\n");
			close(fd);
			exit(1);
		}

		lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
		read( fd, block, block_size);  /* read block from disk*/

        /* first entry in the directory */
		entry = (struct ext2_dir_entry_2 *) block;

        /* Notice that the list may be terminated with a NULL
           entry (entry->inode == NULL)*/
		while(     (size < inode->i_size)
                && (entry->inode) )
        {
			char file_name[EXT2_NAME_LEN + 1];
			memcpy(file_name, entry->name, entry->name_len);

            /* append null character to the file name */
			file_name[entry->name_len] = '\0';
            if( strcmp(file_name, "Two") == 0 )
            {
                printf(RED "%10u %s\n" RES, entry->inode, file_name);
            }
            else
            {
                printf("%10u %s\n", entry->inode, file_name);
            }


			entry = (void*) entry + entry->rec_len;
			size += entry->rec_len;
		}

		free(block);
	}
} /* read_dir() */
