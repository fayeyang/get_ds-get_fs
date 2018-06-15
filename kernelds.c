#include  <linux/kernel.h>
#include  <linux/module.h>
#include  <linux/init.h>
#include  <linux/fs.h>
#include  <linux/uaccess.h>
//#include  <linux/string.h>
//#include  <linux/device.h>

MODULE_AUTHOR( "faye" );
MODULE_LICENSE( "GPL" );

MODULE_DESCRIPTION( "get_ds/get_fs test" );

static int __init kernelds_init( void ){
	struct file *filp;
	mm_segment_t fs_bak;
	char buf[ 100 ];
	int tmp;
	loff_t pos;
	
	printk( "kernelds_init\n" );
		
	filp = NULL;
	filp = filp_open( "/home/faye/work/work_normal/gcc_test/KERNEL_DS/file1", O_RDWR, 0 );
	if( IS_ERR(filp) ){
		printk( "cannot open file\n" );
		return 1;
	}
		
	fs_bak = get_fs();
	set_fs( KERNEL_DS );
	
	for( tmp=0; tmp<100; tmp++ ){
		buf[ tmp ] = 0;
	}
	
	pos = 0;
	vfs_read( filp, buf, 100, &pos );
	printk( "%s\n", buf );
	set_fs( fs_bak );
	
	filp_close( filp, NULL );
	
	return 0;
}

static void __exit kernelds_exit( void ){
	printk( "kernelds_exit\n" );
}

module_init( kernelds_init );
module_exit( kernelds_exit );
