/**
 * Importacion de las dependencias 
*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h> 
#include <asm/uaccess.h> 
#include <linux/hugetlb.h>

/**
 * Definiciones
*/
#define PROCESZ "memo_201513700"
#define BUFSIZE  100

/**
 * Informacion sobre el modulo que estamos construyendo
*/
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo para obtener informacion del estado de la memoria.");
MODULE_AUTHOR("ChristianReal-201513700");
/**
 * Fin descripcion del modulo
*/

/**
 * ESCRIBIR ARCHIVO
*/
struct sysinfo i;

static int mostrar_informacion_show(struct seq_file *m, void *v) {
	#define S(x) ((x) << (PAGE_SHIFT -10))
	si_meminfo(&i);
        seq_printf(m, "+---------------------------+\n");
        seq_printf(m, "+------ MODULO MEMORIA -----+\n");
        seq_printf(m, "+---------------------------+\n");
        seq_printf(m, "| 201513700\n");
        seq_printf(m, "| Christian Real\n");
        seq_printf(m, "| Debian 9 Stretch\n");
        seq_printf(m, "| Total ram MB: %8lu\n",S(i.totalram)/1024);
        seq_printf(m, "| Memoria libre MB: %8lu\n",S(i.freeram)/1024);
        seq_printf(m, "| Porcentaje memoria utilizada: %8lu \n",S(i.freeram)*100/S(i.totalram));
        seq_printf(m, "+---------------------------\n");
        return 0;
}

static int hello_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, mostrar_informacion_show, NULL);
}
 
static struct file_operations myops =
{
        .owner = THIS_MODULE,
        .open = hello_proc_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release,
};
/**
 * FIN ESCRIBIR ARCHIVO
*/

static int procedimiento_inicial(void)
{
    proc_create(PROCESZ,0,NULL,&myops);
    printk(KERN_INFO "201513700\n");
        return 0;
}
 
static void procedimiento_final(void)
{
  remove_proc_entry(PROCESZ,NULL);
  printk(KERN_INFO "Sistemas Operativos 1 [Segundo Semestre 2019]\n");
}
 
module_init(procedimiento_inicial);
module_exit(procedimiento_final); 
