#include <linux/module.h>
#include <linux/init.h>
#include <linux/kmod.h>
 
MODULE_LICENSE( "GPL" );

static int umh_test( void )
{
  char *argv[] = { "/usr/bin/logger", "HELLOOOOOO!", NULL };
  static char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
 
  return call_usermodehelper( argv[0], argv, envp, UMH_WAIT_PROC );
}
 
static int __init mod_entry_func( void )
{
  return umh_test();
}
 
 
static void __exit mod_exit_func( void )
{
  return;
}
 
module_init( mod_entry_func );
module_exit( mod_exit_func );