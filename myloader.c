
int bsector;
int bmap, imap, iblk, blk, offset;
char buf[1024], buf1[1024], buf2[1024];


int mysearch(INODE *ip, char *name)
{
  int i;
  char c, *cp;
  DIR *dp;
  printf("search for %s: ", name);

  for (i = 0; i < 12; i++)
  {
    if (ip->i_block[i])
    {
      getblock(ip->i_block[i], buf2);
      dp = (DIR *)buf2;
      cp = buf2;
      while (cp < &buf2[1024])
      {
        c = dp->name[dp->name_len]; 

        dp->name[dp->name_len] = 0;
       

        if (strcmp(dp->name, name) == 0)
        {
          printf("found %s in %d\n", name,dp->inode);
          return (dp->inode);
        }
        dp->name[dp->name_len] = c;
        cp += dp->rec_len;
        dp = (DIR *)cp;
      }
    }
  }
  printf("serach failed\n");
}

int myload(char *filename, PROC *p)
{
  int i, ino, blk, iblk, count;
  char *cp, *name[2], *addr;
  u32 *up;
  GD *gp;
  INODE *ip;
  DIR *dp;

  name[0] = "bin";
  name[1] = filename;

  addr = (char *)(0x800000 + (p->pid - 1) * 0x100000);
  printf("loading %s: ", filename);

  getblock(2, buf1);
  gp = (GD *)buf1;
  iblk = (u16)gp->bg_inode_table;

  printf("iblk=%d ", iblk);

  getblock(iblk, buf1);   
  ip = (INODE *)buf1 + 1; 

  /* searches for bin and filename */
  for (i = 0; i < 2; i++)
  {
   ino= mysearch(ip, name[i]) - 1;
    printf("Search results: %d\n",ino);
    if (ino < 0){
     printf("search failed\n");
      return 0;
    }
    getblock(iblk + (ino / 8), buf1); 
    ip = (INODE *)buf1 + (ino % 8);
  }

  /* read indirect block into buf2 */
  if (ip->i_block[12]) 
    getblock(ip->i_block[12], buf2);

  count = 0;

  for (i = 0; i < 12; i++)
  {
    if (ip->i_block[i] == 0)
      break;
    
    getblock(ip->i_block[i], addr);
    kputc('*');
    addr += 1024;
    count += 1024;
  }

  if (ip->i_block[12])
  { 
    up = (u32 *)buf2;
    while (*up)
    {
      getblock(*up, addr);
      kputc('.');
      addr += 1024;
      up++;
      count += 1024;
    }
  }

  return 1;
}
